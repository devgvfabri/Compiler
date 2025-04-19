#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "global.h"
#include "util.h"
#include "symtab.h"
#include "semantico.h"
#include "parser.tab.h"
/* ########################### Tabela  de símbolos ######################################*/

FILE *save_symTable;


/* retorna a função atual para o analisador semantico*/
char *getCurrentFunction() {
    return currentFunction;
}

void setCurrentFunction(char *funcName) {
    currentFunction = funcName;
}

/* Função hash para a tabela de símbolos */

int hash(char * key)
{
  int temp = 0;
  int i = 0;
  while (key[i] != '\0')
  {
    temp = ((temp << 4) + key[i]) % 211;
    ++i;
  }
  return temp;
}

/* Lista de linhas em que determinado id aparece no código*/

/* Procura variável por nome e escopo na tabela*/
int st_lookup ( char * name, char *escopo )
{ 
	int h = hash(name);
	  BucketList l =  hashTable[h];
		while ((l != NULL) && !(strcmp(name, l->name) == 0 && strcmp(escopo, l->escopo) == 0))
	    l = l->next;
	  if (l == NULL) return -1;
	  else return l->memloc;
}

/* Imprime a tabeala de símbolos com a anotação formatada*/
void printSymTab()
{
	 int i;
	 save_symTable = fopen("table_generate.txt", "w");
	  fprintf(save_symTable, "Location   Variable Name Escopo Tipo ID Tipo Dado Line Numbers\n");
	  fprintf(save_symTable, "--------   ------------- ------ ------- --------- ------------\n");
	  for (i=0;i<211;++i)
	  { 
	  if (hashTable[i] != NULL)
	    { 
	    BucketList l = hashTable[i];
	      while (l != NULL)
	      { 
	      	LineList t = l->lines;
	      	fprintf(save_symTable, "%-8d  ",l->memloc);
		fprintf(save_symTable, "%-14s ",l->name);
		fprintf(save_symTable, "%-6s  ",l->escopo);
		fprintf(save_symTable, "%-8s  ",l->tipoID);
		fprintf(save_symTable, "%-9d  ",l->tipoDado);
		while (t != NULL)
		{ 
		  fprintf(save_symTable, "%4d ",t->numline);
		  t = t->next;
		}
		fprintf(save_symTable, "\n");
		l = l->next;
	      }
	    }
  	  }
}

/* Insere elementos na tabela de simbolos, primeiro verifica se a variável já existe no mesmo escopo, 
 depois verifica se é uma declaração, se a variável já foi declarada no mesmo escopo gera erro,
 se não insere a nova variável na tabela como declaração, se não for declaração, primeiro verifica se a variável, 
 existe no escopo local, depois verifica se existe no global, depois verifica se é uma chamada recursiva, 
 se não for nenhum dos erros apenas verifica se já foi registrado naquela linha */



void st_insert(int loc, char *name, char *escopo, char *tipoID, int tipoDado, int numline, int isDeclaration) {
    int h = hash(name);
    BucketList l = hashTable[h];
  
    // Verificar se a variável já existe no mesmo escopo
    while (l != NULL) {
        if (strcmp(name, l->name) == 0 && strcmp(escopo, l->escopo) == 0) {
            break;
        }
        l = l->next;
    }
  
    if (isDeclaration) { 
        if (l != NULL) {
            // Variável já declarada no mesmo escopo  gera erro
            errorSemanticoVariavelExistente(name, numline);
        } else { 
            // Inserir nova variável na tabela de símbolos
            l = (BucketList)malloc(sizeof(struct BucketListRec));
            l->name = strdup(name);
            l->escopo = strdup(escopo);
            l->tipoID = strdup(tipoID);
            l->tipoDado = tipoDado;
            l->lines = (LineList)malloc(sizeof(struct LineListRec));
            l->lines->numline = numline;
            l->lines->next = NULL;
            l->memloc = loc;
            l->next = hashTable[h];
            hashTable[h] = l;
        }
    } else {  
        // Se não for declaração, verificar se existe no escopo local ou global
        BucketList temp = hashTable[h];
        BucketList globalVar = NULL;
        int isFunctionCall = 0;
  
        while (temp != NULL) {
            if (strcmp(name, temp->name) == 0) {
                if (strcmp(escopo, temp->escopo) == 0) {
                    break;  // Encontrado no escopo local
                } else if (strcmp("global", temp->escopo) == 0) {
                    globalVar = temp;  // Identificador global encontrado
                }
            }
            temp = temp->next;
        }
  
        // Se não encontrou no escopo local, usa a variável global (se existir)
        if (temp == NULL) {
            temp = globalVar;
        }
  
        // Se a variável não foi encontrada, verificar se é uma chamada recursiva
        if (temp == NULL) {
            if (strcmp(name, escopo) == 0 && strcmp(tipoID, "funcao") == 0) {
                return;  // Chamada recursiva válida, não gera erro
            } else if(strcmp(tipoID, "funcao") != 0) {
                    errorSemanticoVariavelNaoDeclarada(name, numline);
                    return;
                
            }else if (strcmp(tipoID, "funcao") == 0) {
                    errorSemanticoFuncaoNaoDeclarada(name, numline);
                    return;  // Chamada de função não encontrada
                }
            }
        
  
        // Se for chamada de função, marcar como tal
        if (strcmp(temp->tipoID, "funcao") == 0) {
            isFunctionCall = 1;
        }
  
        // Verificar se a linha já foi registrada para evitar duplicação
        LineList t = temp->lines;
        while (t != NULL) {
            if (t->numline == numline) {
                return;  // Linha já registrada
            }
            if (t->next == NULL) break;
            t = t->next;
        }
  
        // Adicionar nova referência da linha
        t->next = (LineList)malloc(sizeof(struct LineListRec));
        t->next->numline = numline;
        t->next->next = NULL;
    }
  }

   /* Função para procurar um identificador na tabela de símbolos*/
   BucketList st_lookup_entry(char *name, char *escopo) {
    if (name == NULL || escopo == NULL) {
        return NULL;  // Retorna nulo se os parâmetros forem inválidos
    }
    int h = hash(name);
    BucketList l = hashTable[h]; 
  
    while (l != NULL) {
        if (l->name != NULL && l->escopo != NULL && strcmp(name, l->name) == 0 && strcmp(escopo, l->escopo) == 0) {
            break;
        }
        l = l->next;
    }
    return l;  
  }
  
  /* Função para procurar um identificador função na tabela de símbolos*/
  
  BucketList st_lookup_entryFun(char *name, char *escopo, char *tipoID){
    if (name == NULL || escopo == NULL) {
        return NULL;  // Retorna nulo se os parâmetros forem inválidos
    }
    int h = hash(name);
    BucketList l = hashTable[h]; 
  
    while (l != NULL) {
        if (l->name != NULL && l->escopo != NULL && l->tipoID != NULL && 
            strcmp(name, l->name) == 0 && strcmp(escopo, l->escopo) == 0 && strcmp(tipoID, l->tipoID) == 0) {
            break;
        }
        l = l->next;
    }
    return l;  
  }
  
  ExpType st_lookup_type(char *name, char *escopo) {
        BucketList entry = st_lookup_entry(name, escopo);
        return (entry != NULL) ? (ExpType) entry->tipoDado : Undefined;  // 🔹 Converte para ExpType
  }

