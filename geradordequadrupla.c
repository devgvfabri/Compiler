#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "util.h"
#include "parser.tab.h"
#include "geradordequadrupla.h"

FILE *codigoIntermediario;

void cGen(TreeNode *t);
void cGen_noSibling(TreeNode *t);
int tempVarNum = 0;
int tempLabelNum = 0;

typedef struct parametros {
	char *name;
	struct parametros *prox;
} parametros;

parametros *parametrosLista = NULL;

char* newLabel() {
	char* name = (char*)malloc(sizeof(char) * 10);
	sprintf(name, "L%d", tempLabelNum++);
	return name;
}

char* newTemp() {
    char *name = (char*)malloc(sizeof(char) * 10);
    sprintf(name, "$t%d", tempVarNum++);
    return name;
}

void genStmt(TreeNode *tree)
{
	int loc;
	switch(tree->kind.stmt)
	{
		case IfK:
			cGen(tree->child[0]);
			tree->child[1]->label = newLabel();
			fprintf(codigoIntermediario, "(IFF,%s,%s,-)\n", tree->child[0]->temp, tree->child[1]->label);
			cGen(tree->child[1]);
			tree->child[2]->label = newLabel();
			fprintf(codigoIntermediario, "(GOTO,%s,-,-)\n",tree->child[2]->label);
			fprintf(codigoIntermediario, "(LAB,%s,-,-)\n", tree->child[1]->label);
			cGen(tree->child[2]);
			fprintf(codigoIntermediario, "(GOTO,%s,-,-)\n",tree->child[2]->label);
			fprintf(codigoIntermediario, "(LAB,%s,-,-)\n", tree->child[2]->label);
			break;
		case WhileK:
			fprintf(codigoIntermediario, "(TESTE,-,-,-)\n");
			break;
		case returnK:
			cGen(tree->child[0]);
			fprintf(codigoIntermediario, "(RET,%s,-,-)\n", tree->child[0]->temp);
			break;
		case AtrK:
			cGen(tree->child[0]);
			cGen(tree->child[1]);
			fprintf(codigoIntermediario, "(ASSIGN,%s,%s,-)\n", tree->child[0]->temp, tree->child[1]->temp);
			fprintf(codigoIntermediario, "(STORE,%s,%s,-)\n", tree->child[0]->attr.name, tree->child[0]->temp);
			break;
		case VarK:
			fprintf(codigoIntermediario, "(ALLOC,%s,%s,-)\n", tree->attr.name, tree->escopo);
			break;
		case FunK:
		{
			fprintf(codigoIntermediario, "(FUN,%s,%s,-)\n", tree->type == 0 ? "void" : "int", tree->attr.name);
			cGen(tree->child[0]);
			while (parametrosLista != NULL) {
				char *temp = newTemp();
				fprintf(codigoIntermediario, "(LOAD,%s,%s,-)\n", temp,parametrosLista->name);
				parametrosLista = parametrosLista->prox;
			}
			cGen(tree->child[1]);
			fprintf(codigoIntermediario, "(END,%s,-,-)\n", tree->attr.name);
			break;
		}
		case CallK: {
				TreeNode *arg = tree->child[0];
				int argCount = 0;
				
				// Gera código e PARAM para cada argumento
				while (arg != NULL) {
					cGen_noSibling(arg); // Gera código da expressão
					fprintf(codigoIntermediario, "(PARAM,%s,-,-)\n", arg->temp);
					argCount++;
					arg = arg->sibling;
				}
			
				tree->temp = newTemp();
				fprintf(codigoIntermediario, "(CALL,%s,%s,%d)\n", tree->temp, tree->attr.name, argCount);
				break;
			}
		case ParamK:
			{
				fprintf(codigoIntermediario, "(ARG,%d,%s,%s)\n", tree->type, tree->attr.name, tree->escopo);
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

void genExp(TreeNode *tree)
{
	int loc;
	switch(tree->kind.exp)
	{
		case OpK:
			cGen(tree->child[0]);
			cGen(tree->child[1]);
			tree->temp = newTemp();
			fprintf(codigoIntermediario, "(%s,%s,%s,%s)\n", genOperator(tree->attr.op), tree->temp, tree->child[0]->temp, tree->child[1]->temp);
			break;
		case ConstK:
			tree->temp = (char*)malloc(sizeof(char*)*12);
			if (tree->temp != NULL) {
				snprintf(tree->temp, 12, "%d", tree->attr.val);
			}
			break;
		case IdK:
			tree->temp = newTemp();
			fprintf(codigoIntermediario, "(LOAD,%s,%s,-)\n", tree->temp, tree->attr.name);
			break;
		case TypeK:
			cGen(tree->child[0]);
			break;
		case VetK:
			fprintf(codigoIntermediario, "(TESTE,-,-,-)\n");
			break;
		default:
			break;
	}

}

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

void generateCode(TreeNode *t) {
    if (t == NULL) return;
	codigoIntermediario = fopen("codqua.txt", "w");
    cGen(t);
	fprintf(codigoIntermediario, "(HALT,-,-,-)\n");
}
