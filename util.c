#include "util.h"
#include "parser.tab.h"
#include "global.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* ########################### Arvore Sintática Abstrata ######################################*/

extern ErroLexico *listaErrosLexicos;
FILE *save_tree;

void imprimirErrosLexicos()
{
	ErroLexico *atual = listaErrosLexicos;
	while (atual)
	{
		printf("%s", atual->mensagem);
		atual = atual->prox;
	}
}

/* ########################## Imprime tokens e lexemas correspondentes ####################################*/
void printToken(TokenType token, const char *tokenString)
{
	switch (token)
	{
	case IF:
		printf("IF");
		break;
	case ELSE:
		printf("ELSE");
		break;
	case VOID:
		printf("VOID");
		break;
	case WHILE:
		printf("WHILE");
		break;
	case RETURN:
		printf("RETURN");
		break;
	case INT:
		printf("INT");
		break;
	case SOM:
		printf("SOM = +");
		break;
	case SUB:
		printf("SUB = -");
		break;
	case MUL:
		printf("MUL = *");
		break;
	case DIV:
		printf("DIV = /");
		break;
	case MAI:
		printf("MAI = >");
		break;
	case MEN:
		printf("MEN = <");
		break;
	case MIG:
		printf("MIG = >=");
		break;
	case MEI:
		printf("MEI = <=");
		break;
	case IGU:
		printf("IGU = ==");
		break;
	case DIF:
		printf("DIF = !=");
		break;
	case ATR:
		printf("ATR = =");
		break;
	case PEV:
		printf("PEV = ;");
		break;
	case VIR:
		printf("VIR = ,");
		break;
	case APA:
		printf("APA = (");
		break;
	case FPA:
		printf("FPA = )");
		break;
	case ACO:
		printf("ACO = [");
		break;
	case FCO:
		printf("FCO = ]");
		break;
	case ACH:
		printf("ACH = {");
		break;
	case FCH:
		printf("FCH = }");
		break;
	case NUM:
		printf("NUM, val= %s", tokenString);
		break;
	case ID:
		printf("ID, name= %s", tokenString);
		break;
	case ERRO:
		printf("ERROR: %s", tokenString);
		break;
	default: /* should never happen */
		printf("Unknown token: %d", token);
	}
}

void printTokenExternFile(TokenType token, const char *tokenString)
{
	switch (token)
	{
	case IF:
		break;
	case ELSE:
		break;
	case VOID:
		break;
	case WHILE:
		break;
	case RETURN:
		break;
	case INT:
		fprintf(save_tree, "INT");
		break;
	case SOM:
		fprintf(save_tree, "SOM = +");
		break;
	case SUB:
		fprintf(save_tree, "SUB = -");
		break;
	case MUL:
		fprintf(save_tree, "MUL = *");
		break;
	case DIV:
		fprintf(save_tree, "DIV = /");
		break;
	case MAI:
		fprintf(save_tree, "MAI = >");
		break;
	case MEN:
		fprintf(save_tree, "MEN = <");
		break;
	case MIG:
		fprintf(save_tree, "MIG = >=");
		break;
	case MEI:
		fprintf(save_tree, "MEI = <=");
		break;
	case IGU:
		fprintf(save_tree, "IGU = ==");
		break;
	case DIF:
		fprintf(save_tree, "DIF = !=");
		break;
	case ATR:
		fprintf(save_tree, "ATR = =");
		break;
	case PEV:
		fprintf(save_tree, "PEV = ;");
		break;
	case VIR:
		fprintf(save_tree, "VIR = ,");
		break;
	case APA:
		fprintf(save_tree, "APA = (");
		break;
	case FPA:
		fprintf(save_tree, "FPA = )");
		break;
	case ACO:
		fprintf(save_tree, "ACO = [");
		break;
	case FCO:
		fprintf(save_tree, "FCO = ]");
		break;
	case ACH:
		fprintf(save_tree, "ACH = {");
		break;
	case FCH:
		fprintf(save_tree, "FCH = }");
		break;
	case NUM:
		fprintf(save_tree, "NUM, val= %s", tokenString);
		break;
	case ID:
		fprintf(save_tree, "ID, name= %s", tokenString);
		break;
	case ERRO:
		fprintf(save_tree, "ERROR: %s", tokenString);
		break;
	default: /* should never happen */
		fprintf(save_tree, "Unknown token: %d", token);
	}
}

/* Cria um nó da arvore do tipo statement cria o nó e retorna para o parser*/
TreeNode *newStmtNode(StmtKind kind)
{
	TreeNode *t = (TreeNode *)malloc(sizeof(TreeNode));
	int i;
	if (t == NULL)
		printf("Out of memory error at line %d\n", numline);
	else
	{
		for (i = 0; i < MAXCHILDREN; i++)
			t->child[i] = NULL;
		t->sibling = NULL;
		t->nodekind = StmtK;
		t->kind.stmt = kind;
		t->numline = numline;
		t->attr.vetor = 0;
	}
	return t;
}

/* Cria um nó da arvore do tipo expressao cria o nó e retorna para o parser*/
TreeNode *newExpNode(ExpKind kind)
{
	TreeNode *t = (TreeNode *)malloc(sizeof(TreeNode));
	int i;
	if (t == NULL)
		printf("Out of memory error at line %d\n", numline);
	else
	{
		for (i = 0; i < MAXCHILDREN; i++)
			t->child[i] = NULL;
		t->sibling = NULL;
		t->nodekind = ExpK;
		t->kind.exp = kind;
		t->numline = numline;
		t->type = Void;
		t->attr.vetor = 0;
	}
	return t;
}

/* Copia uma string para outra variável*/
char *copyString(char *s)
{
	int n;
	char *t;
	if (s == NULL)
		return NULL;
	n = strlen(s) + 1;
	t = (char *)malloc(n);
	if (t == NULL)
		printf("Out of memory error at line %d\n", numline);
	else
		strcpy(t, s);
	return t;
}

static int indentno = 0;

/* Identação para imprimir a arvore sintatica abstrata*/
#define INDENT indentno += 2
#define UNINDENT indentno -= 2

static void printSpaces(void)
{
	int i;
	for (i = 0; i < indentno; i++)
		fprintf(save_tree, " ");
}

/* Imprime todos os nós da árvore*/
void printTree(TreeNode *tree)
{
	int i;
	INDENT;
	while (tree != NULL)
	{
		printSpaces();
		if (tree->nodekind == StmtK)
		{
			switch (tree->kind.stmt)
			{
			case IfK:
				fprintf(save_tree, "If\n");
				break;
			case WhileK:
				fprintf(save_tree, "While\n");
				break;
			case returnK:
				fprintf(save_tree, "return\n");
				break;
			case AtrK:
				fprintf(save_tree, "Atribuicao\n");
				break;
			case VarK:
				fprintf(save_tree, "Var: %s\n", tree->attr.name);
				break;
			case FunK:
				fprintf(save_tree, "Fun: %s\n", tree->attr.name);
				break;
			case CallK:
				fprintf(save_tree, "Chamada: %s\n", tree->attr.name);
				break;
			case ParamK:
				fprintf(save_tree, "Parametro: %s\n", tree->attr.name);
				break;
			default:
				fprintf(save_tree, "Unknown ExpNode kind\n");
				break;
			}
		}
		else if (tree->nodekind == ExpK)
		{
			switch (tree->kind.exp)
			{
			case OpK:
				fprintf(save_tree, "Op: ");
				printTokenExternFile(tree->attr.op, "\0");
				fprintf(save_tree, "\n");
				break;
			case ConstK:
				fprintf(save_tree, "Const: %d\n", tree->attr.val);
				break;
			case IdK:
				fprintf(save_tree, "Id: %s\n", tree->attr.name);
				break;
			case TypeK:
				fprintf(save_tree, "Type: %d\n", tree->type);
				break;
			case VetK:
				fprintf(save_tree, "Vetor: %s\n", tree->attr.name);
				break;
			case VetIdK:
				fprintf(save_tree, "Var Vet: %s\n", tree->attr.name);
				break;
			default:
				fprintf(save_tree, "Unknown ExpNode kind\n");
				break;
			}
		}
		else
			fprintf(save_tree, "Unknown node kind\n");
		for (i = 0; i < MAXCHILDREN; i++)
			printTree(tree->child[i]);
		tree = tree->sibling;
	}
	UNINDENT;
}

void printTreeArq(TreeNode *tree)
{
	save_tree = fopen("tree_generate.txt", "w");
	printTree(tree);
}
