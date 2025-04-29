#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"global.h"
#include"util.h"


void genStmt(TreeNode *tree)
{
	int loc;
	switch(tree->kind.stmt)
	{
		case IfK:
			break;
		case WhileK:
			break;
		case returnK:
			break;
		case AtrK:
			break;
		case Vark:
			break;
		case FunK:
			break;
		case CallK:
			break;
		case ParamK:
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
			break;
		case ConstK:
			break;
		case IdK:
			break;
		case TypeK:
			break;
		case VetK:
			break;
		default:
			break;
	}

}
void cGen(TreeNode *t)
{
	switch(t->nodeKind)
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

char *generateCode(TreeNode *t) {
    if (t == NULL) return NULL;

    cGen(t);



}
