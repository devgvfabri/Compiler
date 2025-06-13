#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "util.h"
#include "parser.tab.h"
#include "geradorAssembly.h"

FILE *codigoAssembly;

void genAssembly(Quadrupla *listaCodInt)
{
    switch (listaCodInt->mensagem)
    {
    case:
        /* code */
        break;
    
    default:
        break;
    }
}

void generate_assembly(Quadrupla  *listaCodInt)
{
    if (listaCodInt == NULL) return;
    codigoAssembly = fopen("codAssembly.txt", "w");
    genAssembly(listaCodInt);
}