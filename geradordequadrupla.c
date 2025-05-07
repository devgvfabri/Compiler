#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "util.h"
#include "parser.tab.h"
#include "geradordequadrupla.h"

FILE *codigoIntermediario;

/* Realiza traversia percorrendo irmãos do nó*/
void cGen(TreeNode *t);

/* Percorre a arvore sem passar para o nós irmãos usado para chamadas de funções*/
void cGen_noSibling(TreeNode *t);

/* Contadores de registradores e labels*/
int tempVarNum = 0;
int tempLabelNum = 0;

/* Estrutura para armazenar os parâmetros de uma função*/
typedef struct parametros {
	char *name;
	struct parametros *prox;
} parametros;

parametros *parametrosLista = NULL;

/* Gera um novo label*/
char* newLabel() {
	char* name = (char*)malloc(sizeof(char) * 10);
	sprintf(name, "L%d", tempLabelNum++);
	return name;
}

/* Gera um novo temporário*/
char* newTemp() {
    char *name = (char*)malloc(sizeof(char) * 10);
    sprintf(name, "$t%d", tempVarNum++);
    return name;
}

/* Gera código intermediário para expressões e comandos*/
void genStmt(TreeNode *tree)
{
	int loc;
	switch(tree->kind.stmt)
	{
		/*Gera código para nó tipo If, percorre em pós ordem, primeiro ao filho mais a esquerda, volta gerando código cria um
		label para o caminho do segundo filho e um para o terceiro filho, passa por todos os filhos em pós ordem*/
		case IfK:
		{
			char *labelAux1 = (char*)malloc(sizeof(char) * 10);
			char *labelAux2 = (char*)malloc(sizeof(char) * 10);
			cGen(tree->child[0]);
			labelAux1 = newLabel();
			fprintf(codigoIntermediario, "(IFF, %s, %s, -)\n", tree->child[0]->temp, labelAux1);
			cGen(tree->child[1]);
			labelAux2= newLabel();
			fprintf(codigoIntermediario, "(GOTO, %s, -, -)\n",labelAux2);
			fprintf(codigoIntermediario, "(LAB, %s, -, -)\n", labelAux1);
			cGen(tree->child[2]);
			fprintf(codigoIntermediario, "(GOTO, %s, -, -)\n",labelAux2);
			fprintf(codigoIntermediario, "(LAB, %s, -, -)\n", labelAux2);
		}
			break;
		case WhileK:
			cGen(tree->child[0]);
			cGen(tree->child[1]);
			fprintf(codigoIntermediario, "teste\n");
			break;
		/* Gera quadrupla para returns, apenas visita os filhos e imprime uma quadrupla do tipo retorno com temporario do filho*/
		case returnK:
			cGen(tree->child[0]);
			fprintf(codigoIntermediario, "(RET, %s, -, -)\n", tree->child[0]->temp);
			break;
		/* Gera quadrupla para atribuições, visita os filhos e imprime uma quadrupla do tipo atribuição com os temporarios dos filhos,
		depois carrega com um store o valor a atribuição na memória*/
		case AtrK:
			cGen(tree->child[0]);
			cGen(tree->child[1]);
			fprintf(codigoIntermediario, "(ASSIGN, %s, %s, -)\n", tree->child[0]->temp, tree->child[1]->temp);
			fprintf(codigoIntermediario, "(STORE, %s, %s, -)\n", tree->child[0]->attr.name, tree->child[0]->temp);
			break;
		/* Gera quadrupla para leitura, apenas visita a variavel e imprime uma quadrupla do tipo leitura com o nome e escopo*/
		case VarK:
			fprintf(codigoIntermediario, "(ALLOC, %s, %s, -)\n", tree->attr.name, tree->escopo);
			break;
		/* Gera quadrupla para funções, apenas visita o filho e imprime uma quadrupla do tipo escrita com o temporario do filho*/
		case FunK:
		{
			fprintf(codigoIntermediario, "(FUN, %s, %s, -)\n", tree->type == 0 ? "void" : "int", tree->attr.name);
			cGen(tree->child[0]);
			while (parametrosLista != NULL) {
				char *temp = newTemp();
				fprintf(codigoIntermediario, "(LOAD, %s, %s, -)\n", temp,parametrosLista->name);
				parametrosLista = parametrosLista->prox;
			}
			cGen(tree->child[1]);
			fprintf(codigoIntermediario, "(END, %s, -, -)\n", tree->attr.name);
			break;
		}
		/*Gera quadruplas para chamadas de funções visita o filho sendo o primeiro argumento da função e os irmãos desse argumento, 
		para cada argumento gera um parametro temporário*/
		case CallK: {
				TreeNode *arg = tree->child[0];
				int argCount = 0;
				
				// Gera código e PARAM para cada argumento
				while (arg != NULL) {
					cGen_noSibling(arg); // Gera código da expressão
					fprintf(codigoIntermediario, "(PARAM, %s, -, -)\n", arg->temp);
					argCount++;
					arg = arg->sibling;
				}
			
				tree->temp = newTemp();
				fprintf(codigoIntermediario, "(CALL, %s, %s, %d)\n", tree->temp, tree->attr.name, argCount);
				break;
			}
		/* Gera quadrupla para escrita, apenas visita o filho e imprime uma quadrupla do tipo escrita com o temporario do filho*/
		case ParamK:
			{
				fprintf(codigoIntermediario, "(ARG, %s, %s, %s)\n", tree->type == 0 ? "void" : "int", tree->attr.name, tree->escopo);
				parametros *param = (struct parametros*)malloc(sizeof(struct parametros));
				param->name = tree->attr.name;
				param->prox = NULL;
				if(parametrosLista == NULL) parametrosLista = param;
				else
				{
					parametros *aux = parametrosLista;
					while(aux->prox != NULL)
						aux = aux->prox;
					aux->prox = param;
				}
				break;
			}
		default:
			break;

	}
}
/*Gera operadores para as quadruplas de operação de acordo com o token salvo na arvore*/
char *genOperator(TokenType token)
{
	switch(token)
	{
		case SOM: return "ADD";
		case SUB: return "SUB";
		case MUL: return "MUL";
		case DIV: return "DIV";
		case MAI: return "GREATER";
		case MEN: return "LESS";
		case MIG: return "GE";
		case MEI: return "LE";
		case IGU: return "EQUAL";
		case DIF: return "NOTEQUAL";
		default: return "UNKNOWN";
	}
}
/*Gera código intermediário para nós do tipo expressão */
void genExp(TreeNode *tree)
{
	int loc;
	switch(tree->kind.exp)
	{
		/* Gera nós de operadores com a operação e cada temporário do filho do nó*/
		case OpK:
			cGen(tree->child[0]);
			cGen(tree->child[1]);
			tree->temp = newTemp();
			fprintf(codigoIntermediario, "(%s, %s, %s, %s)\n", genOperator(tree->attr.op), tree->temp, tree->child[0]->temp, tree->child[1]->temp);
			break;
		/* Gera nós de operadores unários com a constante armazenada*/
		case ConstK:
			tree->temp = (char*)malloc(sizeof(char*)*12);
			if (tree->temp != NULL) {
				snprintf(tree->temp, 12, "%d", tree->attr.val);
			}
			break;
		/*Gera quadruplas carregando váriaveis da memória*/
		case IdK:
			tree->temp = newTemp();
			fprintf(codigoIntermediario, "(LOAD, %s, %s, -)\n", tree->temp, tree->attr.name);
			break;
		/*Usado para percorrer a arvore em pós ordem*/
		case TypeK:
			cGen(tree->child[0]);
			break;
		/* Gera quadruplas para vetores */
		case VetK:
		{
			char *aux = (char*)malloc(sizeof(char*)*12);
			char *add = (char*)malloc(sizeof(char*)*12);
			cGen(tree->child[0]);
			if(tree->child[0]->kind.exp == ConstK){
				aux = tree->child[0]->temp;
				tree->child[0]->temp = newTemp();
				fprintf(codigoIntermediario, "(ASSIGN, %s, %s, -)\n", tree->child[0]->temp, aux);
			}
			tree->temp = newTemp();
			fprintf(codigoIntermediario, "(MUL, %s, %s, 4)\n", tree->temp, tree->child[0]->temp);
			aux = newTemp();
			fprintf(codigoIntermediario, "(LOADADDR, %s, %s, -)\n", aux, tree->attr.name);
			add = newTemp();
			fprintf(codigoIntermediario, "(ADD, %s, %s, %s)\n", add, aux, tree->temp);
			tree->temp = newTemp();
			fprintf(codigoIntermediario, "(LOAD, %s, %s, -)\n", tree->temp, add);
		}	
			break;
		default:
			break;
	}

}
/* Percorre em pós ordem sem passar pelos irmãos*/
void cGen_noSibling(TreeNode *t)
{
	if (t != NULL){
		switch(t->nodekind)
		{
			case StmtK:
				genStmt(t);
				break;
			case ExpK:
				genExp(t);
				break;
			default:
				break;
		}
	}
}
/* Função para realizar traversia da arvore*/
void cGen(TreeNode *t)
{
	int i;
	if (t != NULL){
	switch(t->nodekind)
	{
		case StmtK:
			genStmt(t);
			break;
		case ExpK:
			genExp(t);
			break;
		default:
			break;
	}
	cGen(t->sibling);
	}
}
/* Função inicial chamada na main para gerar código, abre o arquivo .txt para escrita*/
void generateCode(TreeNode *t) {
    if (t == NULL) return;
	codigoIntermediario = fopen("codqua.txt", "w");
    cGen(t);
	fprintf(codigoIntermediario, "(HALT,-,-,-)\n");
}
