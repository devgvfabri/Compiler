#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "util.h"
#include "parser.tab.h"
#include "geradordequadrupla.h"

FILE *codigoIntermediario;


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
			fprintf(codigoIntermediario, "(TESTE,-,-,-)\n");
			break;
		case VarK:
			fprintf(codigoIntermediario, "(TESTE,-,-,-)\n");
			break;
		case FunK:
			fprintf(codigoIntermediario, "(TESTE,-,-,-)\n");
			break;
		case CallK:
			fprintf(codigoIntermediario, "(TESTE,-,-,-)\n");
			break;
		case ParamK:
			fprintf(codigoIntermediario, "(TESTE,-,-,-)\n");
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
			fprintf(codigoIntermediario, "(TESTE,-,-,-)\n");
			break;
		case TypeK:
			fprintf(codigoIntermediario, "(TESTE,-,-,-)\n");
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
	for (i=0;i<3;i++)
		 cGen(t->child[i]);
	t = t->sibling;
	}
}

void generateCode(TreeNode *t) {
    if (t == NULL) return;
	codigoIntermediario = fopen("codqua.txt", "w");
    cGen(t);




}
