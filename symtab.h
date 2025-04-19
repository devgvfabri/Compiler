#ifndef SYMTAB_H
#define SYMTAB_H

#include <stdio.h>
#include "global.h"
#include "util.h"
#include "semantico.h"
/* ########################### Tabela  de símbolos ######################################*/

/* Lista de linhas em que determinado id aparece no código*/
typedef struct LineListRec
{ 
   	int numline;
   	struct LineListRec *next;
} * LineList;

typedef struct BucketListRec 
{ 
   	char * name;
     	LineList lines;
     	int memloc ;
     	char * escopo;
     	char * tipoID;
     	int  tipoDado; 
     	struct BucketListRec * next;
} * BucketList;
   
static BucketList hashTable[211];

static char *currentFunction = "global";  // Inicializa como global

BucketList st_lookup_entry(char *name, char *escopo);

BucketList st_lookup_entryFun(char *name, char *escopo, char *tipoID);

/* Protótipo da função */
void printToken(TokenType token, const char* tokenString);

int hash(char * key);

void st_insert(int loc, char *name, char *escopo, char *tipoID, int tipoDado, int numline, int isDeclaration);

int st_lookup ( char * name, char * escopo );

void printSymTab();

void imprimirErros();

char *getCurrentFunction();
void setCurrentFunction(char *funcName);

#endif /* SYMTAB_H */