#ifndef SYMTAB_H
#define SYMTAB_H

#include <stdio.h>
#include "global.h"
#include "util.h"
#include "semantico.h"
/* ########################### Tabela  de símbolos ######################################*/

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