#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "util.h"
#include "parser.tab.h"
#include "geradorAssembly.h"

FILE *codigoAssembly;

#define MAX_ARGS 10

Quadrupla *argumentos[MAX_ARGS];
int num_argumentos = 0;
static int indice_parametro = 0;

void empilhaArgumento(Quadrupla *arg) {
    if (num_argumentos < MAX_ARGS) {
        argumentos[num_argumentos++] = arg;
    }
}

void limpaArgumentos() {
    num_argumentos = 0;
}

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
        indice_parametro = 0;
        if(strcmp(operand2, "main") == 0)
            printf("funcao: %s\n", operand2);
        else
        {
            printf("funcao: %s\n", operand2);
            printf("sw $62, $31, 0 \n");
        }
        break;
    case quad_argumento:
        printf("lw %s, $fp, %d\n", argumentos[num_argumentos], 2 + num_argumentos - 1); 
        num_argumentos--;
        break;
    case quad_parametro:
                if (indice_parametro < 4)
                printf("move %s, $a%d\n", operand1, indice_parametro);
            else
                printf("lw %s, $fp, %d\n", operand1, 2 + (indice_parametro - 4));
            empilhaArgumento(listaCodInt);
            indice_parametro++;
        break;
    case quad_alloc:
        printf("subi $62, $62, 1\n");
        break;
    case quad_load:
        printf("lw $62, %s, offset \n", operand1);
        break;
    case quad_loadaddr:
        printf("lw* $62, %s, offset\n", operand1);
        break;
    case quad_store:
        printf("sw $62, %s, offset \n", operand2);
        break;
    case quad_assign:
        printf("move %s, %s\n", operand1, operand2);
        break;
    case quad_call:
    {
        if(strcmp(operand2, "input") == 0)
            printf("input %s\n", operand1);
        else if(strcmp(operand2, "output") == 0)
            printf("output %s\n", operand1);
        else
        {
            printf("subi $62, $62, 2 \n");
            printf("sw $62, $30, 1 \n");
            printf("move $30, $62 \n");
            printf("jal %d\n", operand3);
            printf("move $62, $30 \n");
            printf("lw $30, $62, 0 \n");
            printf("lw $31, $62, 1 \n");
            printf("addi $62, $62, 2\n");
        }
        break;
    }
    case quad_iff:
        printf("bne %s, $0, offset\n", operand1);
        break;
    case quad_label:
        printf("label %s\n", operand1);
        break;
    case quad_goto:
        printf("jump %s\n", operand1);
        break;
    case quad_return:
        printf("move %s, $gp\n", operand1);
        break;
    case quad_add:
        printf("add %s, %s, %s\n", operand1, operand2, operand3);
        break;
    case quad_sub:
        printf("sub %s, %s, %s\n", operand1, operand2, operand3);
        break;
    case quad_mul:
        printf("mul %s, %s, %s\n", operand1, operand2, operand3);
        break;
    case quad_div:
        printf("div %s, %s, %s\n", operand1, operand2, operand3);
        break;
    case quad_maior:
        printf("slt %s, %s, %s\n", operand1, operand3, operand2);
        break;
    case quad_menor:
        printf("slt %s, %s, %s\n", operand1, operand2, operand3);
        break;
    case quad_maiorigual:
        printf("slte %s, %s, %s\n", operand1, operand3, operand2);
        break;
    case quad_menorigual:
        printf("slte %s, %s, %s\n", operand1, operand2, operand3);
        break;
    case quad_igual:
    {
        printf("bne %s, %s, offset\n", operand2, operand3);
        listaCodInt = listaCodInt->prox;
        break;
    }    
    case quad_diferente:
    {
        printf("beq %s, %s, offset\n", operand2, operand3);
        listaCodInt = listaCodInt->prox;
        break;
    }
    case quad_end:
        if(strcmp(operand1, "main") != 0)
        {
            printf("lw $30, $31, 0\n");
            printf("jr $31\n");
        }
        break;
    case quad_hlt:
        printf("halt\n");
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