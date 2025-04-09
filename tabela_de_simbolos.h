#ifndef _TABELA_DE_SIMBOLOS_H
#define _TABELA_DE_SIMBOLOS_H

int hash(char * key);

void st_insert( char * name, int numline, int loc );

int st_lookup ( char * name );

void printSymTab();
#endif
