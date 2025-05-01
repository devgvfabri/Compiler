#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "util.h"
#include "parser.tab.h"
#include "geradordequadrupla.h"

FILE *codigoIntermediario;

void cGen(TreeNode *t);

int tempVarNum = 0;

char* newLabel() {
	char* name = (char*)malloc(sizeof(char) * 10);
	sprintf(name, "L%d", tempVarNum++);
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
			fprintf(codigoIntermediario, "(TESTE,-,-,-)\n");
			break;
		case WhileK:
			fprintf(codigoIntermediario, "(TESTE,-,-,-)\n");
			break;
		case returnK:
			fprintf(codigoIntermediario, "(TESTE,-,-,-)\n");
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
			fprintf(codigoIntermediario, "(FUN,%d,%s,-)\n", tree->type, tree->attr.name);
			cGen(tree->child[0]);
			cGen(tree->child[1]);
			fprintf(codigoIntermediario, "(END,-,-,-)\n");
			break;
		case CallK:
			tree->temp = newTemp();
			fprintf(codigoIntermediario, "(CALL,%s,%s,-)\n", tree->temp, tree->attr.name);
			break;
		case ParamK:
			fprintf(codigoIntermediario, "(ARG,%d,%s,%s)\n", tree->type, tree->attr.name, tree->escopo);
			break;
		default:
			break;

	}
}

void genExp(TreeNode *tree)
{
	int loc;
	switch(tree->kind.exp)
	{
		case OpK:
			fprintf(codigoIntermediario, "(TESTE,-,-,-)\n");
			break;
		case ConstK:
			fprintf(codigoIntermediario, "(TESTE,-,-,-)\n");
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
}
