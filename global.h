#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef YYPARSER

#include "parser.tab.h"
#endif

#define MAXRESERVED 6
#define MAXCHILDREN 3




typedef enum {StmtK,ExpK} NodeKind;
typedef enum {IfK,WhileK,returnK, AtrK, VarK, FunK, CallK, ParamK} StmtKind;
typedef enum {OpK,ConstK,IdK, TypeK, VetK} ExpKind;
typedef enum {Void,Integer, Undefined, IntegerVetorK} ExpType;

typedef int TokenType; 

extern int numline;

extern char tokenString[256];

typedef struct treeNode
   { struct treeNode * child[MAXCHILDREN];
     struct treeNode * sibling;
     int numline;
     NodeKind nodekind;
     union { StmtKind stmt; ExpKind exp;} kind;
     struct { TokenType op;
             int val;
             char * name;
             int vetor;
            } attr;
     ExpType type; 
     char *escopo;
   } TreeNode;
   


TreeNode *newStmtNode(StmtKind kind);
TreeNode *newExpNode(ExpKind kind);
void printTree(TreeNode *tree);

char *copyString(char *s);
void checkNode(TreeNode * t);
void typeError(TreeNode * t, char * message);
void noop(TreeNode *t);
void semanticCheck(TreeNode *syntaxTree);
void traverse(TreeNode * t,
  void (* preProc) (TreeNode *),
  void (* postProc) (TreeNode *));


#endif
