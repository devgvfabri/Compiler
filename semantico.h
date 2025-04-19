#ifndef SEMANTICO_H
#define SEMANTICO_H

#include <stdio.h>
#include "global.h"
#include "util.h"
#include "symtab.h"


 /* Declarações de funções para impressão de erros e verificação na tabela*/

 void errorSemanticoVariavelExistente(char *name, int numline);

 void errorSemanticoVariavelNaoDeclarada(char *name, int numline);

 void errorSemanticoFuncaoNaoDeclarada(char *name, int numline);


 #endif /* SEMANTICO_H */