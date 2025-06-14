#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "util.h"
#include "parser.tab.h"
#include "geradorAssembly.h"

FILE *codigoAssembly;

typedef enum {
    quad_funcao,
    quad_argumento,
    quad_parametro,
    quad_alloc,
    quad_load,
    quad_loadaddr,
    quad_store,
    quad_assign,
    quad_call,
    quad_iff,
    quad_label,
    quad_goto,
    quad_return,
    quad_add,
    quad_sub,
    quad_mul,
    quad_div,
    quad_maior,
    quad_menor,
    quad_maiorigual,
    quad_menorigual,
    quad_igual,
    quad_diferente,
    quad_end,
    quad_hlt
} operacao;

operacao converteString(char *stringOp)
{
    if(strcmp(stringOp, "FUN") == 0) return quad_funcao;
    if(strcmp(stringOp, "ARG") == 0) return quad_argumento;
    if(strcmp(stringOp, "PARAM") == 0) return quad_parametro;
    if(strcmp(stringOp, "ALLOC") == 0) return quad_alloc;
    if(strcmp(stringOp, "LOAD") == 0) return quad_load;
    if(strcmp(stringOp, "LOADADDR") == 0) return quad_loadaddr;
    if(strcmp(stringOp, "STORE") == 0) return quad_store;
    if(strcmp(stringOp, "ASSIGN") == 0) return quad_assign;
    if(strcmp(stringOp, "CALL") == 0) return quad_call;
    if(strcmp(stringOp, "IFF") == 0) return quad_iff;
    if(strcmp(stringOp, "LAB") == 0) return quad_label;
    if(strcmp(stringOp, "GOTO") == 0) return quad_goto;
    if(strcmp(stringOp, "RET") == 0) return quad_return;
    if(strcmp(stringOp, "ADD") == 0) return quad_add;
    if(strcmp(stringOp, "SUB") == 0) return quad_sub;
    if(strcmp(stringOp, "MUL") == 0) return quad_mul;
    if(strcmp(stringOp, "DIV") == 0) return quad_div;
    if(strcmp(stringOp, "GREATER") == 0) return quad_maior;
    if(strcmp(stringOp, "LESS") == 0) return quad_menor;
    if(strcmp(stringOp, "GE") == 0) return quad_maiorigual;
    if(strcmp(stringOp, "LE") == 0) return quad_menorigual;
    if(strcmp(stringOp, "EQUAL") == 0) return quad_igual;
    if(strcmp(stringOp, "NOTEQUAL") == 0) return quad_diferente;
    if(strcmp(stringOp, "END") == 0) return quad_end;
    if(strcmp(stringOp, "HALT") == 0) return quad_hlt;
}

void genAssembly(Quadrupla *listaCodInt)
{
    char *operacao, *operand1, *operand2, *operand3;
    operacao = (char *)malloc(20 * sizeof(char));
    operand1 = (char *)malloc(20 * sizeof(char));
    operand2 = (char *)malloc(20 * sizeof(char));
    operand3 = (char *)malloc(20 * sizeof(char));
    sscanf(listaCodInt->mensagem, " ( %[^,], %[^,], %[^,], %[^)] )", operacao, operand1, operand2, operand3);
    switch (converteString(operacao))
    {
    case quad_funcao:
        printf("Generating assembly for function: %s\n", operand1);
        break;
    case quad_argumento:
        printf("addi $30, $30, 1\n");
        break;
    case quad_parametro:
        printf("Generating assembly for parameter: %s\n", operand1);
        break;
    case quad_alloc:
        printf("addi $30, $30, 1\n");
        break;
    case quad_load:
        printf("lw $29,  \n");
        break;
    case quad_loadaddr:
        printf("Generating assembly for load address: %s into %s\n", operand1, operand2);
        break;
    case quad_store:
        printf("Generating assembly for store: %s into %s\n", operand1, operand2);
        break;
    case quad_assign:
        printf("Generating assembly for assignment: %s = %s\n", operand1, operand2);
        break;
    case quad_call:
        printf("Generating assembly for call: %s with %s\n", operand1, operand2);
        break;
    case quad_iff:
        printf("Generating assembly for if: %s then %s\n", operand1, operand2);
        break;
    case quad_label:
        printf("Generating assembly for label: %s\n", operand1);
        break;
    case quad_goto:
        printf("Generating assembly for goto: %s\n", operand1);
        break;
    case quad_return:
        printf("Generating assembly for return: %s\n", operand1);
        break;
    case quad_add:
        printf("Generating assembly for addition: %s = %s + %s\n", operand1, operand2, operand3);
        break;
    case quad_sub:
        printf("Generating assembly for subtraction: %s = %s - %s\n", operand1, operand2, operand3);
        break;
    case quad_mul:
        printf("Generating assembly for multiplication: %s = %s * %s\n", operand1, operand2, operand3);
        break;
    case quad_div:
        printf("Generating assembly for division: %s = %s / %s\n", operand1, operand2, operand3);
        break;
    case quad_maior:
        printf("Generating assembly for greater than: %s = %s > %s\n", operand1, operand2, operand3);
        break;
    case quad_menor:
        printf("Generating assembly for less than: %s = %s < %s\n", operand1, operand2, operand3);
        break;
    case quad_maiorigual:
        printf("Generating assembly for greater than or equal: %s = %s >= %s\n", operand1, operand2, operand3);
        break;
    case quad_menorigual:
        printf("Generating assembly for less than or equal: %s = %s <= %s\n", operand1, operand2, operand3);
        break;
    case quad_igual:
        printf("Generating assembly for equality: %s = %s == %s\n", operand1, operand2, operand3);
        break;
    case quad_diferente:
        printf("Generating assembly for inequality: %s = %s != %s\n", operand1, operand2, operand3);
        break;
    case quad_end:
        printf("Generating assembly for end of code\n");
        break;
    case quad_hlt:
        printf("Generating assembly for halt\n");
        return;
    default:
        break;
    }
    genAssembly(listaCodInt->prox);
}

void generate_assembly(Quadrupla  *listaCodInt)
{
    printf("Generating assembly code...\n");
    if (listaCodInt == NULL) return;
    codigoAssembly = fopen("codAssembly.txt", "w");
    genAssembly(listaCodInt);
    return;
}