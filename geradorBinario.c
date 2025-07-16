#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "util.h"
#include "parser.tab.h"
#include "geradorAssembly.h"

FILE *codigoBinario;

typedef enum{
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



int get_register_number(const char *reg) {
    if (reg[0] != '$') return -1;

    // Casos especiais primeiro
    if (strcmp(reg, "$gp") == 0) return 29;
    if (strcmp(reg, "$30") == 0) return 30;
    if (strcmp(reg, "$31") == 0) return 31;
    if (strcmp(reg, "$62") == 0) return 62;
    if (strcmp(reg, "$0") == 0) return 63;

    int num;
    char prefix;

    if (sscanf(reg, "$%c%d", &prefix, &num) != 2)
        return -1;

    if (prefix == 't') {
        if (num >= 0 && num <= 29) return num;        // $t0-$t29 → 0-29
        if (num >= 32 && num <= 53) return num;       // $t32-$t53 → 32-53
    }

    if (prefix == 'a') {
        if (num >= 0 && num <= 7) return 55 + num;    // $a0-$a7 → 55-61
    }
   fprintf(codigoBinario, "invalido");
    return -1; 
}


void to_binary6(int numreg, char *out) {
    for (int i = 5; i >= 0; i--)
        out[5 - i] = (numreg& (1 << i)) ? '1' : '0';
    out[6] = '\0';
}

void imediato_para_bin14(int valor, char *saida) {
    if (valor < -8192 || valor > 8191) {
        strcpy(saida, "VALOR_INVALIDO");
        return;
    }

    unsigned short int convertido;

    if (valor >= 0)
        convertido = valor;
    else
        convertido = (1 << 14) + valor;  // complemento de 2

    for (int i = 13; i >= 0; i--)
        saida[13 - i] = (convertido & (1 << i)) ? '1' : '0';

    saida[14] = '\0';
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
            fprintf(codigoBinario, "00000000000000000000000000000000\n");
            break;
        case inst_add:
        {
            fprintf(codigoBinario, "000000");
            char *reg1 = (char *)malloc(20 * sizeof(char)), *reg2 = (char *)malloc(20 * sizeof(char)) , *reg3 = (char *)malloc(20 * sizeof(char));
            sscanf(listaCodAssebly->mensagem, "%d: %s %[^,], %[^,], %[^,]", &linha, operacao, reg1, reg2, reg3);
            char bin[7];
            int numreg= get_register_number(reg2);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
            numreg= get_register_number(reg3);
            to_binary6(numreg, bin);
            fprintf(codigoBinario, "%s", bin);
            numreg= get_register_number(reg1);
            to_binary6(numreg, bin);
            fprintf(codigoBinario, "%s00000000\n", bin);
            break;
        }
        case inst_sub:
        {
           fprintf(codigoBinario, "000001");
            char *reg1 = (char *)malloc(20 * sizeof(char)), *reg2 = (char *)malloc(20 * sizeof(char)) , *reg3 = (char *)malloc(20 * sizeof(char));
            sscanf(listaCodAssebly->mensagem, "%d: %s %[^,], %[^,], %[^,]", &linha, operacao, reg1, reg2, reg3);
            char bin[7];
            int numreg= get_register_number(reg2);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
            numreg= get_register_number(reg3);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
            numreg= get_register_number(reg1);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s00000000\n", bin);
            break;
        }
        case inst_mul:
        {
           fprintf(codigoBinario, "000010");
            char *reg1 = (char *)malloc(20 * sizeof(char)), *reg2 = (char *)malloc(20 * sizeof(char)) , *reg3 = (char *)malloc(20 * sizeof(char));
            sscanf(listaCodAssebly->mensagem, "%d: %s %[^,], %[^,], %[^,]", &linha, operacao, reg1, reg2, reg3);
            char bin[7];
            int numreg= get_register_number(reg2);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
            numreg= get_register_number(reg3);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
            numreg= get_register_number(reg1);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s00000000\n", bin);
            break;
        }
        case inst_div:
        {
           fprintf(codigoBinario, "000011");
            char *reg1 = (char *)malloc(20 * sizeof(char)), *reg2 = (char *)malloc(20 * sizeof(char)) , *reg3 = (char *)malloc(20 * sizeof(char));
            sscanf(listaCodAssebly->mensagem, "%d: %s %[^,], %[^,], %[^,]", &linha, operacao, reg1, reg2, reg3);
            char bin[7];
            int numreg= get_register_number(reg2);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
            numreg= get_register_number(reg3);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
            numreg= get_register_number(reg1);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s00000000\n", bin);
            break;
        }
        case inst_addi:
        {
           fprintf(codigoBinario, "000100");
            char *reg1 = (char *)malloc(20 * sizeof(char)), *reg2 = (char *)malloc(20 * sizeof(char)), *imedi = (char *)malloc(20 * sizeof(char));
            sscanf(listaCodAssebly->mensagem, "%d: %s %[^,], %[^,], %[^,]", &linha, operacao, reg1, reg2, imedi);
            char bin[7];
            int numreg= get_register_number(reg1);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
            numreg= get_register_number(reg2);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
            char imediate[15];
            imediato_para_bin14(atoi(imedi), imediate);
           fprintf(codigoBinario, "%s\n", imediate);
            break;
        }
        case inst_subi:
        {
           fprintf(codigoBinario, "000101");
            char *reg1 = (char *)malloc(20 * sizeof(char)), *reg2 = (char *)malloc(20 * sizeof(char)), *imedi = (char *)malloc(20 * sizeof(char));
            sscanf(listaCodAssebly->mensagem, "%d: %s %[^,], %[^,], %[^,]", &linha, operacao, reg1, reg2, imedi);
            char bin[7];
            int numreg= get_register_number(reg2);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
            numreg= get_register_number(reg1);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
            char imediate[15];
            imediato_para_bin14(atoi(imedi), imediate);
           fprintf(codigoBinario, "%s\n", imediate);
            break;
        }
        case inst_halt:
           fprintf(codigoBinario, "00111000000000000000000000000000\n");
            return;
        case inst_jr:
           fprintf(codigoBinario, "01000101111100000000000000000000\n");
            break;
        case inst_lw:
        {
           fprintf(codigoBinario, "001001");
            char *reg1 = (char *)malloc(20 * sizeof(char)), *reg2 = (char *)malloc(20 * sizeof(char)), *imedi = (char *)malloc(20 * sizeof(char));
            sscanf(listaCodAssebly->mensagem, "%d: %s %[^,], %[^,], %[^,]", &linha, operacao, reg1, reg2, imedi);
            char bin[7];
            int numreg= get_register_number(reg1);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
            numreg= get_register_number(reg2);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
            char imediate[15];
            imediato_para_bin14(atoi(imedi), imediate);
           fprintf(codigoBinario, "%s\n", imediate);
            break;
        }
        case inst_sw:
        {
           fprintf(codigoBinario, "001010");
            char *reg1 = (char *)malloc(20 * sizeof(char)), *reg2 = (char *)malloc(20 * sizeof(char)), *imedi = (char *)malloc(20 * sizeof(char));
            sscanf(listaCodAssebly->mensagem, "%d: %s %[^,], %[^,], %[^,]", &linha, operacao, reg1, reg2, imedi);
            char bin[7];
            int numreg= get_register_number(reg1);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
            numreg= get_register_number(reg2);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
            char imediate[15];
            imediato_para_bin14(atoi(imedi), imediate);
           fprintf(codigoBinario, "%s\n", imediate);
            break;
        }
        case inst_beq:
        {
           fprintf(codigoBinario, "010101");
            char *reg1 = (char *)malloc(20 * sizeof(char)), *reg2 = (char *)malloc(20 * sizeof(char)), *imedi = (char *)malloc(20 * sizeof(char));
            sscanf(listaCodAssebly->mensagem, "%d: %s %[^,], %[^,], %[^,]", &linha, operacao, reg1, reg2, imedi);
            char bin[7];
            int numreg= get_register_number(reg1);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
            numreg= get_register_number(reg2);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
            char imediate[15];
            imediato_para_bin14(atoi(imedi), imediate);
           fprintf(codigoBinario, "%s\n", imediate);
            break;
        }
        case inst_bne:
        {
           fprintf(codigoBinario, "010101");
            char *reg1 = (char *)malloc(20 * sizeof(char)), *reg2 = (char *)malloc(20 * sizeof(char)), *imedi = (char *)malloc(20 * sizeof(char));
            sscanf(listaCodAssebly->mensagem, "%d: %s %[^,], %[^,], %[^,]", &linha, operacao, reg1, reg2, imedi);
            char bin[7];
            int numreg= get_register_number(reg1);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
            numreg= get_register_number(reg2);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
            char imediate[15];
            imediato_para_bin14(atoi(imedi), imediate);
           fprintf(codigoBinario, "%s\n", imediate);
            break;
        }
        case inst_slte:
        {
           fprintf(codigoBinario, "010111");
            char *reg1 = (char *)malloc(20 * sizeof(char)), *reg2 = (char *)malloc(20 * sizeof(char)) , *reg3 = (char *)malloc(20 * sizeof(char));
            sscanf(listaCodAssebly->mensagem, "%d: %s %[^,], %[^,], %[^,]", &linha, operacao, reg1, reg2, reg3);
            char bin[7];
            int numreg= get_register_number(reg2);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
            numreg= get_register_number(reg3);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
            numreg= get_register_number(reg1);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s00000000\n", bin);
            break;
        }
        case inst_slt:
        {
           fprintf(codigoBinario, "010100");
            char *reg1 = (char *)malloc(20 * sizeof(char)), *reg2 = (char *)malloc(20 * sizeof(char)) , *reg3 = (char *)malloc(20 * sizeof(char));
            sscanf(listaCodAssebly->mensagem, "%d: %s %[^,], %[^,], %[^,]", &linha, operacao, reg1, reg2, reg3);
            char bin[7];
            int numreg= get_register_number(reg2);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
            numreg= get_register_number(reg3);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
            numreg= get_register_number(reg1);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s00000000\n", bin);
            break;
        }
        case inst_move:
        {
           fprintf(codigoBinario, "001100");
            char *reg1 = (char *)malloc(20 * sizeof(char)), *reg2 = (char *)malloc(20 * sizeof(char));
            sscanf(listaCodAssebly->mensagem, "%d: %s %[^,], %s", &linha, operacao, reg1, reg2);
            char bin[7];
            int numreg= get_register_number(reg1);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
            numreg= get_register_number(reg2);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
           fprintf(codigoBinario, "00000000000000\n");
            break;
        }
        case inst_jump:
        {
           fprintf(codigoBinario, "010011000000000000");
            char *imedi = (char *)malloc(20 * sizeof(char));
            sscanf(listaCodAssebly->mensagem, "%d: %s %s", &linha, operacao, imedi);
            char imediate[15];
            imediato_para_bin14(atoi(imedi), imediate);
           fprintf(codigoBinario, "%s\n", imediate);
            break;
        }
        case inst_jal:
        {
           fprintf(codigoBinario, "010010111111011111");
            char *imedi = (char *)malloc(20 * sizeof(char));
            sscanf(listaCodAssebly->mensagem, "%d: %s %s", &linha, operacao, imedi);
            char imediate[15];
            imediato_para_bin14(atoi(imedi), imediate);
           fprintf(codigoBinario, "%s\n", imediate);
            break;
        }
        case inst_label:
           fprintf(codigoBinario, "00000000000000000000000000000000\n");
            break;
        case inst_input:
        {
           fprintf(codigoBinario, "001111111111");
            char *reg1 = (char *)malloc(20 * sizeof(char));
            sscanf(listaCodAssebly->mensagem, "%d: %s %[^.].", &linha, operacao, reg1);
            char bin[7];
            int numreg= get_register_number(reg1);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
           fprintf(codigoBinario, "00000000000000\n");
            break;
        }
        case inst_output:
        {
           fprintf(codigoBinario, "010000");
            char *reg1 = (char *)malloc(20 * sizeof(char));
            sscanf(listaCodAssebly->mensagem, "%d: %s %[^.].", &linha, operacao, reg1);
            char bin[7];
            int numreg= get_register_number(reg1);
            to_binary6(numreg, bin);
           fprintf(codigoBinario, "%s", bin);
           fprintf(codigoBinario, "11111100000000000000\n");
            break;
        }
        default:
            break;
    }
    genBinary(listaCodAssebly->prox);
    return;
}

typedef struct LabelMap {
    char nome[50];
    int linha;
    struct LabelMap *prox;
} LabelMap;

LabelMap *label_map = NULL;

void adicionar_label(const char *nome, int linha) {
    LabelMap *novo = (LabelMap *)malloc(sizeof(LabelMap));
    strcpy(novo->nome, nome);
    novo->linha = linha;
    novo->prox = label_map;
    label_map = novo;
}

int obter_linha_label(const char *nome) {
    for (LabelMap *it = label_map; it != NULL; it = it->prox)
        if (strcmp(it->nome, nome) == 0) return it->linha;
    return -1;
}

void substituir_labels_por_linhas(CodAssembly *lista) {
    CodAssembly *atual = lista;
    int linha;
    char operacao[20];

    // Passagem 1: coletar labels
    while (atual != NULL) {
        sscanf(atual->mensagem, "%d: %s", &linha, operacao);
        if (strcmp(operacao, "label") == 0 || strcmp(operacao, "funcao") == 0) {
            char nome[50];
            if (strcmp(operacao, "label") == 0)
                sscanf(atual->mensagem, "%d: %*s %s", &linha, nome);
            else
                sscanf(atual->mensagem, "%d: %*s : %s", &linha, nome);
            adicionar_label(nome, linha-1);
        }
        atual = atual->prox;
    }

    // Passagem 2: substituir
    atual = lista;
    while (atual != NULL) {
        sscanf(atual->mensagem, "%d: %s", &linha, operacao);

        if (strcmp(operacao, "jump") == 0 || strcmp(operacao, "jal") == 0) {
            char nome[50];
            sscanf(atual->mensagem, "%d: %s %s", &linha, operacao, nome);
            int destino = obter_linha_label(nome);
            if (destino != -1) {
                sprintf(atual->mensagem, "%d: %s %d", linha, operacao, destino);
            }
        } else if (strcmp(operacao, "bne") == 0 || strcmp(operacao, "beq") == 0) {
            char reg1[20], reg2[20], nome[50];
            sscanf(atual->mensagem, "%d: %s %[^,], %[^,], %s", &linha, operacao, reg1, reg2, nome);
            int destino = obter_linha_label(nome);
            destino -= linha;
            if (destino != -1) {
                sprintf(atual->mensagem, "%d: %s %s, %s, %d", linha, operacao, reg1, reg2, destino);
            }
        }
        atual = atual->prox;
    }
}

void generate_Binary(CodAssembly  *listaCodAssebly)
{
   printf("Generating binary code...\n");
    if (listaCodAssebly == NULL) return;
    substituir_labels_por_linhas(listaCodAssebly);
    codigoBinario = fopen("codigoBinario.txt", "w");
    genBinary(listaCodAssebly);
    return;
}