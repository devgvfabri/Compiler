#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include "global.h"
/* Definição do tipo TokenType */
typedef int TokenType;

/* Declaração de variável externa */
extern FILE* listing;

/* Protótipo da função */
void printToken(TokenType token, const char* tokenString);

int hash(char * key);

void st_insert(int loc, char *name, char *escopo, char *tipoID, int tipoDado, int numline, int isDeclaration);

int st_lookup ( char * name, char * escopo );

void printSymTab();

void imprimirErros();

ExpType st_lookup_type(char *name, char *escopo);

char *getCurrentFunction();
void setCurrentFunction(char *funcName);

#endif /* UTIL_H */

