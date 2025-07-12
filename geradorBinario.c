#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "util.h"
#include "parser.tab.h"
#include "geradorAssembly.h"

FILE *codigoBinario;

typedef enum {
    inst_add,
    inst_sub,
    inst_mul,
    inst_div,
    inst_addi,
    inst_subi,
    inst_halt,
    inst_jr,
    inst_lw,
    inst_sw,
    inst_beq,
    inst_bne,
    inst_slte,
    inst_slt,
    inst_move,
    inst_jump,
    inst_jal,
    inst_label,
    inst_input,
    inst_output,
    inst_funcao
} operacao;

operacao converteStringAssembly(char *stringOp)
{
    if(strcmp(stringOp, "add") == 0) return inst_add;
    if(strcmp(stringOp, "sub") == 0) return inst_sub;
    if(strcmp(stringOp, "mul") == 0) return inst_mul;
    if(strcmp(stringOp, "div") == 0) return inst_div;
    if(strcmp(stringOp, "addi") == 0) return inst_addi;
    if(strcmp(stringOp, "subi") == 0) return inst_subi;
    if(strcmp(stringOp, "halt") == 0) return inst_halt;
    if(strcmp(stringOp, "jr") == 0) return inst_jr;
    if(strcmp(stringOp, "lw") == 0) return inst_lw;
    if(strcmp(stringOp, "sw") == 0) return inst_sw;
    if(strcmp(stringOp, "beq") == 0) return inst_beq;
    if(strcmp(stringOp, "bne") == 0) return inst_bne;
    if(strcmp(stringOp, "slte") == 0) return inst_slte;
    if(strcmp(stringOp, "slt") == 0) return inst_slt;
    if(strcmp(stringOp, "move") == 0) return inst_move;
    if(strcmp(stringOp, "jump") == 0) return inst_jump;
    if(strcmp(stringOp, "jal") == 0) return inst_jal;
    if(strcmp(stringOp, "label") == 0) return inst_label;
    if(strcmp(stringOp, "input") == 0) return inst_input;
    if(strcmp(stringOp, "output") == 0) return inst_output;
    if(strcmp(stringOp, "funcao") == 0) return inst_funcao;
}

void genBinary(CodAssembly *listaCodAssebly)
{
    char *operacao;
    int linha;
    operacao = (char *)malloc(20 * sizeof(char));
    sscanf(listaCodAssebly->mensagem, "%d: %s", &linha, operacao);
    switch (converteStringAssembly(operacao))
    {
        case inst_funcao:
            break;
        case inst_add:
            printf("000000");
            break;
        case inst_sub:
            printf("000001");
            break;
        case inst_mul:
            printf("000010");
            break;
        case inst_div:
            printf("000011");
            break;
        case inst_addi:
            printf("000100");
            break;
        case inst_subi:
            printf("000101");
            break;
        case inst_halt:
            printf("001110");
            return;
        case inst_jr:
            printf("010001");
            break;
        case inst_lw:
            printf("001001");
            break;
        case inst_sw:
            printf("001010");
            break;
        case inst_beq:
            printf("010101");
            break;
        case inst_bne:
            printf("010110");
            break;
        case inst_slte:
            printf("010111");
            break;
        case inst_slt:
            printf("010100");
            break;
        case inst_move:
            printf("001100");
            break;
        case inst_jump:
            printf("010011");
            break;
        case inst_jal:
            printf("010010");
            break;
        case inst_label:
            printf("");
            break;
        case inst_input:
            printf("001111");
            break;
        case inst_output:
            printf("010000");
            break;
        default:
            break;
    }
    genBinary(listaCodAssebly->prox);
    return;
}


void generate_Binary(CodAssembly  *listaCodAssebly)
{
    printf("Generating binary code...\n");
    if (listaCodAssebly == NULL) return;
    codigoBinario = fopen("codigoBinario.txt", "w");
    genBinary(listaCodAssebly);
    return;
}