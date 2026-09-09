#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "util.h"
#include "parser.tab.h"
#include "geradordequadrupla.h"

FILE *codigoIntermediario;

 Quadrupla *listaCodInt = NULL; // Ponteiro global para a lista de codInt

/* Realiza traversia percorrendo irmãos do nó atual*/
void cGen(TreeNode *t);

/* Percorre a arvore sem passar para o nós irmãos usado para chamadas de funções*/
void cGen_noSibling(TreeNode *t);

/* Contadores de registradores e labels*/
int tempVarNum = 0;
int tempLabelNum = 0;
int varConstainsCall = 0;
int flagCall = 0;
char *savetemp;
/* Estrutura para armazenar os parâmetros de uma função*/
typedef struct parametros
{
	char *name;
	struct parametros *prox;
} parametros;

parametros *parametrosLista = NULL;

/* Gera  novo label*/
char *newLabel()
{
	char *name = (char *)malloc(sizeof(char) * 10);
	sprintf(name, "L%d", tempLabelNum++);
	return name;
}

/* Gera um novo temporário*/
char *newTemp()
{
	char *name = (char *)malloc(sizeof(char) * 10);
	if(tempVarNum == 30) tempVarNum += 2;
	else if(tempVarNum == 50) tempVarNum = 0;
	sprintf(name, "$t%d", tempVarNum);
	tempVarNum++;
	return name;
}

void save_List(char *msg)
{
	Quadrupla *newQuad = (Quadrupla *)malloc(sizeof(Quadrupla));

	snprintf(newQuad->mensagem, sizeof(newQuad->mensagem), "%s", msg);

	newQuad->prox = NULL;
	if (listaCodInt == NULL)
		listaCodInt = newQuad;
	else
	{
		Quadrupla *aux = listaCodInt;
		while (aux->prox != NULL)
			aux = aux->prox;
		aux->prox = newQuad;
	}
}

void imprimirQuadruplas()
{
	Quadrupla *atual = listaCodInt;
	while (atual)
	{
		printf("%s", atual->mensagem);
		atual = atual->prox;
	}
}

void constainsCall(TreeNode *tree)
{

	if(tree->child[0] == NULL || tree->child[1] == NULL ) return;

	if(tree->child[0]->kind.stmt == CallK && (tree->child[1]->kind.stmt == CallK))
	varConstainsCall = 1;
	return;
}

/* Gera código intermediário para expressões e comandos*/
void genStmt(TreeNode *tree)
{
	int loc;
	switch (tree->kind.stmt)
	{
	/*Gera código para nó tipo If, percorre em pós ordem, primeiro ao filho mais a esquerda, volta gerando código cria um
	label para o caminho do segundo filho e um para o terceiro filho, passa por todos os filhos em pós ordem*/
	case IfK:
	{
		char *labelAux1 = (char *)malloc(sizeof(char) * 10);
		char *labelAux2 = (char *)malloc(sizeof(char) * 10);
		char *newQuad = (char *)malloc(sizeof(char) * 256);
		cGen(tree->child[0]);
		labelAux1 = newLabel();
		fprintf(codigoIntermediario, "(IFF, %s, %s, -)\n", tree->child[0]->temp, labelAux1);
		snprintf(newQuad, sizeof(char) * 256,
				 "(IFF, %s, %s, -)\n", tree->child[0]->temp, labelAux1);
		save_List(newQuad);
		cGen(tree->child[1]);
		labelAux2 = newLabel();
		fprintf(codigoIntermediario, "(GOTO, %s, -, -)\n", labelAux2);
		snprintf(newQuad, sizeof(char) * 256,
				 "(GOTO, %s, -, -)\n", labelAux2);
		save_List(newQuad);
		fprintf(codigoIntermediario, "(LAB, %s, -, -)\n", labelAux1);
		snprintf(newQuad, sizeof(char) * 256,
				 "(LAB, %s, -, -)\n", labelAux1);
		save_List(newQuad);
		cGen(tree->child[2]);
		fprintf(codigoIntermediario, "(GOTO, %s, -, -)\n", labelAux2);
		snprintf(newQuad, sizeof(char) * 256,
				 "(GOTO, %s, -, -)\n", labelAux2);
		save_List(newQuad);
		fprintf(codigoIntermediario, "(LAB, %s, -, -)\n", labelAux2);
		snprintf(newQuad, sizeof(char) * 256,
				 "(LAB, %s, -, -)\n", labelAux2);
		save_List(newQuad);
	}
	break;
	case WhileK:
	{
		char *labelAux1 = (char *)malloc(sizeof(char) * 10);
		char *labelAux2 = (char *)malloc(sizeof(char) * 10);
		char *newQuad = (char *)malloc(sizeof(char) * 256);
		labelAux1 = newLabel();
		fprintf(codigoIntermediario, "(LAB, %s, -, -)\n", labelAux1);
		snprintf(newQuad, sizeof(char) * 256,
				 "(LAB, %s, -, -)\n", labelAux1);
		save_List(newQuad);
		cGen(tree->child[0]);
		labelAux2 = newLabel();
		fprintf(codigoIntermediario, "(IFF, %s, %s, -)\n", tree->child[0]->temp, labelAux2);
		snprintf(newQuad, sizeof(char) * 256,
				 "(IFF, %s, %s, -)\n", tree->child[0]->temp, labelAux2);
		save_List(newQuad);
		cGen(tree->child[1]);
		fprintf(codigoIntermediario, "(GOTO, %s, -, - )\n", labelAux1);
		snprintf(newQuad, sizeof(char) * 256,
				 "(GOTO, %s, -, - )\n", labelAux1);
		save_List(newQuad);
		fprintf(codigoIntermediario, "(LAB, %s, -, -)\n", labelAux2);
		snprintf(newQuad, sizeof(char) * 256,
				 "(LAB, %s, -, -)\n", labelAux2);
		save_List(newQuad);
		break;
	}
	/* Gera quadrupla para returns, apenas visita os filhos e imprime uma quadrupla do tipo retorno com temporario do filho*/
	case returnK:
	{
		char *newQuad = (char *)malloc(sizeof(char) * 256);
		cGen(tree->child[0]);
		fprintf(codigoIntermediario, "(RET, %s, -, -)\n", tree->child[0]->temp);
		snprintf(newQuad, sizeof(char) * 256,
				 "(RET, %s, -, -)\n", tree->child[0]->temp);
		save_List(newQuad);
		break;
	}
	/* Gera quadrupla para atribuições, visita os filhos e imprime uma quadrupla do tipo atribuição com os temporarios dos filhos,
	depois carrega com um store o valor a atribuição na memória*/
	case AtrK:
	{
		char *newQuad = (char *)malloc(sizeof(char) * 256);
		cGen(tree->child[0]);
		cGen(tree->child[1]);
		fprintf(codigoIntermediario, "(ASSIGN, %s, %s, -)\n", tree->child[0]->temp, tree->child[1]->temp);
		snprintf(newQuad, sizeof(char) * 256,
				 "(ASSIGN, %s, %s, -)\n", tree->child[0]->temp, tree->child[1]->temp);
		save_List(newQuad);
		if(tree->child[0]->kind.stmt == VetK)
		{
			fprintf(codigoIntermediario, "(STOREVET, %s, %s, %s)\n", tree->child[0]->attr.name, tree->child[0]->temp, tree->child[0]->enderevet);
			snprintf(newQuad, sizeof(char) * 256,
				 "(STOREVET, %s, %s, %s)\n", tree->child[0]->attr.name, tree->child[0]->temp, tree->child[0]->enderevet);
			save_List(newQuad);
		}
		else
		{
		fprintf(codigoIntermediario, "(STORE, %s, %s, -)\n", tree->child[0]->attr.name, tree->child[0]->temp);
		snprintf(newQuad, sizeof(char) * 256,
				 "(STORE, %s, %s, -)\n", tree->child[0]->attr.name, tree->child[0]->temp);
		save_List(newQuad);
		}
		break;
	}
	/* Gera quadrupla para leitura, apenas visita a variavel e imprime uma quadrupla do tipo leitura com o nome e escopo*/
	case VarK:
	{
		char *newQuad = (char *)malloc(sizeof(char) * 256);
		fprintf(codigoIntermediario, "(ALLOC, %s, %s, -)\n", tree->attr.name, tree->escopo);
		snprintf(newQuad, sizeof(char) * 256,
				 "(ALLOC, %s, %s, -)\n", tree->attr.name, tree->escopo);
		save_List(newQuad);
		break;
	}
	/* Gera quadrupla para funções, apenas visita o filho e imprime uma quadrupla do tipo escrita com o temporario do filho*/
	case FunK:
	{
		char *newQuad = (char *)malloc(sizeof(char) * 256);
		fprintf(codigoIntermediario, "(FUN, %s, %s, -)\n", tree->type == 0 ? "void" : "int", tree->attr.name);
		snprintf(newQuad, sizeof(char) * 256,
				 "(FUN, %s, %s, -)\n", tree->type == 0 ? "void" : "int", tree->attr.name);
		save_List(newQuad);
		cGen(tree->child[0]);
		while (parametrosLista != NULL)
		{
			char *temp = newTemp();
			fprintf(codigoIntermediario, "(LOAD, %s, %s, -)\n", temp, parametrosLista->name);
			snprintf(newQuad, sizeof(char) * 256,
					 "(LOAD, %s, %s, -)\n", temp, parametrosLista->name);
			save_List(newQuad);
			parametrosLista = parametrosLista->prox;
		}
		cGen(tree->child[1]);
		fprintf(codigoIntermediario, "(END, %s, -, -)\n", tree->attr.name);
		snprintf(newQuad, sizeof(char) * 256,
				 "(END, %s, -, -)\n", tree->attr.name);
		tempVarNum = 0;
				 save_List(newQuad);
		break;
	}
	/*Gera quadruplas para chamadas de funções visita o filho sendo o primeiro argumento da função e os irmãos desse argumento,
	para cada argumento gera um parametro temporário*/
	case CallK:
	{
		char *newQuad = (char *)malloc(sizeof(char) * 256);
		TreeNode *arg = tree->child[0];
		int argCount = 0;
		
		// Gera código e PARAM para cada argumento
		while (arg != NULL)
		{
			cGen_noSibling(arg); // Gera código da expressão
			fprintf(codigoIntermediario, "(PARAM, %s, -, -)\n", arg->temp);
			snprintf(newQuad, sizeof(char) * 256,
					 "(PARAM, %s, -, -)\n", arg->temp);
			save_List(newQuad);
			argCount++;
			arg = arg->sibling;
		}

		if((strcmp(tree->attr.name, "output") == 0) && tree->child[0]->kind.exp == VetK)
		{	
			fprintf(codigoIntermediario, "(MOVE, $gp, $gb, -)\n");
			snprintf(newQuad, sizeof(char) * 256,
				 "(MOVE, $gp, $gb, -)\n");
			save_List(newQuad);
			fprintf(codigoIntermediario, "(CALL, %s, %s, %d)\n", tree->temp, tree->attr.name, argCount);
			snprintf(newQuad, sizeof(char) * 256,
				 "(CALL, %s, %s, %d)\n", tree->temp, tree->attr.name, argCount);
			save_List(newQuad);
		}
		else if((strcmp(tree->attr.name, "output") == 0))
		{
			fprintf(codigoIntermediario, "(CALL, %s, %s, %d)\n", tree->child[0]->temp, tree->attr.name, argCount);
			snprintf(newQuad, sizeof(char) * 256,
				 "(CALL, %s, %s, %d)\n", tree->child[0]->temp, tree->attr.name, argCount);
			save_List(newQuad);
		}
		else if(varConstainsCall == 1)
		{
			tree->temp = newTemp();
			fprintf(codigoIntermediario, "(CALL, %s, %s, %d)\n", tree->temp, tree->attr.name, argCount);
			snprintf(newQuad, sizeof(char) * 256,
				 "(CALL, %s, %s, %d)\n", tree->temp, tree->attr.name, argCount);
			save_List(newQuad);
			fprintf(codigoIntermediario, "(LOADCALL, %s, -, -)\n", tree->temp);
			snprintf(newQuad, sizeof(char) * 256,
				 "(LOADCALL, %s, -, -)\n", tree->temp);
			save_List(newQuad);
			flagCall = 1;
			varConstainsCall = 0;
			savetemp = (char *)malloc(sizeof(char) * 4);
			strcpy(savetemp, tree->temp);
		}
		else if(flagCall == 1)
		{
			tree->temp = newTemp();
			fprintf(codigoIntermediario, "(CALL, %s, %s, %d)\n", tree->temp, tree->attr.name, argCount);
			snprintf(newQuad, sizeof(char) * 256,
				 "(CALL, %s, %s, %d)\n", tree->temp, tree->attr.name, argCount);
			save_List(newQuad);
			fprintf(codigoIntermediario, "(LOADRET, %s, -, -)\n", savetemp);
			snprintf(newQuad, sizeof(char) * 256,
					 "(LOADRET, %s, -, -)\n", savetemp);
			save_List(newQuad);
			flagCall = 0;
			strcpy(savetemp, "");
		}
		else
		{
		tree->temp = newTemp();
		fprintf(codigoIntermediario, "(CALL, %s, %s, %d)\n", tree->temp, tree->attr.name, argCount);
		snprintf(newQuad, sizeof(char) * 256,
				 "(CALL, %s, %s, %d)\n", tree->temp, tree->attr.name, argCount);
		save_List(newQuad);

		}
		break;
	}
	/* Gera quadrupla para escrita, apenas visita o filho e imprime uma quadrupla do tipo escrita com o temporario do filho*/
	case ParamK:
	{
		char *newQuad = (char *)malloc(sizeof(char) * 256);
		fprintf(codigoIntermediario, "(ARG, %s, %s, %s)\n", tree->type == 0 ? "void" : "int", tree->attr.name, tree->escopo);
		snprintf(newQuad, sizeof(char) * 256,
				 "(ARG, %s, %s, %s)\n", tree->type == 0 ? "void" : "int", tree->attr.name, tree->escopo);
		save_List(newQuad);
		parametros *param = (struct parametros *)malloc(sizeof(struct parametros));
		param->name = tree->attr.name;
		param->prox = NULL;
		if (parametrosLista == NULL)
			parametrosLista = param;
		else
		{
			parametros *aux = parametrosLista;
			while (aux->prox != NULL)
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
	switch (token)
	{
	case SOM:
		return "ADD";
	case SUB:
		return "SUB";
	case MUL:
		return "MUL";
	case DIV:
		return "DIV";
	case MAI:
		return "GREATER";
	case MEN:
		return "LESS";
	case MIG:
		return "GE";
	case MEI:
		return "LE";
	case IGU:
		return "EQUAL";
	case DIF:
		return "NOTEQUAL";
	default:
		return "UNKNOWN";
	}
}
/*Gera código intermediário para nós do tipo expressão */
void genExp(TreeNode *tree)
{
	int loc;
	switch (tree->kind.exp)
	{
	/* Gera nós de operadores com a operação e cada temporário do filho do nó*/
	case OpK:
	{
		constainsCall(tree);
		char *newQuad = (char *)malloc(sizeof(char) * 256);
		cGen(tree->child[0]);
		cGen(tree->child[1]);
		tree->temp = newTemp();
		fprintf(codigoIntermediario, "(%s, %s, %s, %s)\n", genOperator(tree->attr.op), tree->temp, tree->child[0]->temp, tree->child[1]->temp);
		snprintf(newQuad, sizeof(char) * 256,
				 "(%s, %s, %s, %s)\n", genOperator(tree->attr.op), tree->temp, tree->child[0]->temp, tree->child[1]->temp);
		
		save_List(newQuad);
		break;
	}
	/* Gera nós de operadores unários com a constante armazenada*/
	case ConstK:
	{
		tree->temp = (char *)malloc(sizeof(char *) * 12);
		if (tree->temp != NULL)
		{
			snprintf(tree->temp, 12, "%d", tree->attr.val);
		}
		break;
	}
	/*Gera quadruplas carregando váriaveis da memória*/
	case IdK:
	{
		char *newQuad = (char *)malloc(sizeof(char) * 256);
		tree->temp = newTemp();
		fprintf(codigoIntermediario, "(LOAD, %s, %s, -)\n", tree->temp, tree->attr.name);
		snprintf(newQuad, sizeof(char) * 256,
				 "(LOAD, %s, %s, -)\n", tree->temp, tree->attr.name);
		save_List(newQuad);
		break;
	}
	/*Usado para percorrer a arvore em pós ordem*/
	case TypeK:
		cGen(tree->child[0]);
		break;
	/* Gera quadruplas para vetores */
	case VetK:
	{
		char *aux = (char *)malloc(sizeof(char *) * 12);
		char *add = (char *)malloc(sizeof(char *) * 12);
		char *newQuad = (char *)malloc(sizeof(char) * 256);
		cGen(tree->child[0]);
		if (tree->child[0]->kind.exp == ConstK)
		{
			aux = tree->child[0]->temp;
			tree->child[0]->temp = newTemp();
			fprintf(codigoIntermediario, "(ASSIGN, %s, %s, -)\n", tree->child[0]->temp, aux);
			snprintf(newQuad, sizeof(char) * 256,
					 "(ASSIGN, %s, %s, -)\n", tree->child[0]->temp, aux);
			save_List(newQuad);
		}
		aux = newTemp();
		fprintf(codigoIntermediario, "(LOADADDR, %s, %s, %s)\n", aux, tree->attr.name, tree->escopo);
		snprintf(newQuad, sizeof(char) * 256,
				 "(LOADADDR, %s, %s, %s)\n", aux, tree->attr.name, tree->escopo);
		save_List(newQuad);
		add = newTemp();
		fprintf(codigoIntermediario, "(SUB, %s, %s, %s)\n", add, aux, tree->child[0]->temp);
		snprintf(newQuad, sizeof(char) * 256,
				 "(SUB, %s, %s, %s)\n", add, aux, tree->child[0]->temp);
		save_List(newQuad);
		tree->temp = newTemp();
		if(tree->escopo != NULL)
		{
		if(strcmp(tree->escopo, "global") == 0)
		{
			fprintf(codigoIntermediario, "(LOAD, %s, %s, -)\n", add, "gb");
			snprintf(newQuad, sizeof(char) * 256,
				 "(LOAD, %s, %s, -)\n", add, "gb");
			save_List(newQuad);
		}
		}
		else
		{
			fprintf(codigoIntermediario, "(LOADVET, %s, %s, %s)\n", add, tree->temp, tree->attr.name);
			snprintf(newQuad, sizeof(char) * 256,
				 "(LOADVET, %s, %s, %s)\n", add, tree->temp, tree->attr.name);
			save_List(newQuad);
		}
		tree->enderevet = add;
		break;
	}
	case VetIdK:
	{
		char *aux = (char *)malloc(sizeof(char *) * 12);
		char *add = (char *)malloc(sizeof(char *) * 12);
		char *newQuad = (char *)malloc(sizeof(char) * 256);
		cGen(tree->child[0]);
		if (tree->child[0]->kind.exp == ConstK)
		{
			fprintf(codigoIntermediario, "(ALLOCVET, %s, %s, %s)\n", tree->attr.name, tree->escopo, tree->child[0]->temp);
			snprintf(newQuad, sizeof(char) * 256,
					 "(ALLOCVET, %s, %s, %s)\n", tree->attr.name, tree->escopo, tree->child[0]->temp);
			save_List(newQuad);
		}
		break;
	}
	default:
		break;
	}
}
/* Percorre em pós ordem sem passar pelos irmãos*/
void cGen_noSibling(TreeNode *t)
{
	if (t != NULL)
	{
		switch (t->nodekind)
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
	if (t != NULL)
	{
		switch (t->nodekind)
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
void generateCode(TreeNode *t)
{
	if (t == NULL)
		return;
	codigoIntermediario = fopen("codqua.txt", "w");
	cGen(t);
	char *newQuad = (char *)malloc(sizeof(char) * 256);
	fprintf(codigoIntermediario, "(HALT, -, -, -)\n");
	snprintf(newQuad, sizeof(char) * 256,
				 "(HALT, -, -, -)\n");
		save_List(newQuad);
}

