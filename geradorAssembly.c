#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "util.h"
#include "parser.tab.h"
#include "geradorAssembly.h"

FILE *codigoAssembly;

CodAssembly *listaCodAssebly = NULL;

void save_assembly(char *msg)
{
	CodAssembly *newQuad = (CodAssembly *)malloc(sizeof(CodAssembly));

	snprintf(newQuad->mensagem, sizeof(newQuad->mensagem), "%s", msg);

	newQuad->prox = NULL;
	if (listaCodAssebly == NULL)
		listaCodAssebly = newQuad;
	else
	{
		CodAssembly *aux = listaCodAssebly;
		while (aux->prox != NULL)
			aux = aux->prox;
		aux->prox = newQuad;
	}
}

void imprimirAssembly()
{
	CodAssembly *atual = listaCodAssebly;
	while (atual)
	{
		printf("%s", atual->mensagem);
		atual = atual->prox;
	}
}

#define MAX_ARGS 10

#define MAX_SIMBOLOS 100

int num_lines = 0;

typedef struct {
    char nome[32];
    int offset;
} Simbolo;

Simbolo tabela_simbolos[MAX_SIMBOLOS];
int num_simbolos = 0;
int offset_atual = -1;

void limpaTabelaSimbolos() {
    num_simbolos = 0;
    offset_atual = -1;
}

void insereSimbolo(const char *nome) {
    if (num_simbolos >= MAX_SIMBOLOS) return;

    for (int i = 0; i < num_simbolos; i++) {
        if (strcmp(tabela_simbolos[i].nome, nome) == 0) return;
    }

    strcpy(tabela_simbolos[num_simbolos].nome, nome);
    tabela_simbolos[num_simbolos].offset = offset_atual--;
    num_simbolos++;
}

int buscaOffset(const char *nome) {
    for (int i = 0; i < num_simbolos; i++) {
        if (strcmp(tabela_simbolos[i].nome, nome) == 0)
            return tabela_simbolos[i].offset;
    }
    return 0; 
}

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

operacao converteString(char *stringOp)//convert str
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
    char *assembly = (char *)malloc(sizeof(char) * 256);
    sscanf(listaCodInt->mensagem, " ( %[^,], %[^,], %[^,], %[^)] )", operacao, operand1, operand2, operand3);
    switch (converteString(operacao))
    {
    case quad_funcao:
        indice_parametro = 0;
        limpaTabelaSimbolos();
        if(strcmp(operand2, "main") == 0)
        {
            num_lines++;
            fprintf(codigoAssembly, "%d: funcao : %s\n", num_lines, operand2);
            snprintf(assembly, sizeof(char) * 256, "%d: funcao : %s\n", num_lines, operand2);
            save_assembly(assembly);
        }
        else
        {
            num_lines++;
            fprintf(codigoAssembly, "%d: funcao : %s\n", num_lines, operand2);
            snprintf(assembly, sizeof(char) * 256, "%d: funcao : %s\n", num_lines, operand2);
            save_assembly(assembly);
            num_lines++;
            fprintf(codigoAssembly, "%d: sw $62, $31, 0 \n", num_lines);
            snprintf(assembly, sizeof(char) * 256, "%d: sw $62, $31, 0 \n", num_lines);
            save_assembly(assembly);
        }
        break;
    case quad_argumento:
        insereSimbolo(operand2);
        num_lines++;
        fprintf(codigoAssembly, "%d: subi $62, $62, 1\n", num_lines);
        snprintf(assembly, sizeof(char) * 256, "%d: subi $62, $62, 1\n", num_lines);
        save_assembly(assembly);
        num_lines++;
        fprintf(codigoAssembly, "%d: sw $30, $a%d, %d\n", num_lines , num_argumentos, buscaOffset(operand2)); 
        snprintf(assembly, sizeof(char) * 256, "%d: sw $30, $a%d, %d\n", num_lines , num_argumentos, buscaOffset(operand2));
        save_assembly(assembly);
        num_argumentos++;
        break;
    case quad_parametro:
                if (indice_parametro < 4)
                {
                    num_lines++;
                    fprintf(codigoAssembly, "%d: move %s, $a%d\n", num_lines , operand1, indice_parametro);
                    snprintf(assembly, sizeof(char) * 256, "%d: move %s, $a%d\n", num_lines , operand1, indice_parametro);
                    save_assembly(assembly);
                }           
                else
                {
                    num_lines++;
                    fprintf(codigoAssembly, "%d: lw %s, $fp, %d\n", num_lines , operand1, 2 + (indice_parametro - 4));
                    snprintf(assembly, sizeof(char) * 256, "%d: lw %s, $fp, %d\n", num_lines , operand1, 2 + (indice_parametro - 4));
                    save_assembly(assembly);
                }           
            empilhaArgumento(listaCodInt);
            indice_parametro++;
        break;
    case quad_alloc:
        insereSimbolo(operand1);
        num_lines++;
        fprintf(codigoAssembly, "%d: subi $62, $62, 1\n", num_lines);
        snprintf(assembly, sizeof(char) * 256, "%d: subi $62, $62, 1\n", num_lines);
        save_assembly(assembly);
        break;
    case quad_load:
        num_lines++;
        fprintf(codigoAssembly, "%d: lw $30, %s, %d \n", num_lines , operand1, buscaOffset(operand2));
        snprintf(assembly, sizeof(char) * 256, "%d: lw $30, %s, %d \n", num_lines , operand1, buscaOffset(operand2));
        save_assembly(assembly);
        break;
    case quad_loadaddr:
        num_lines++;
        fprintf(codigoAssembly, "%d: lw* $62, %s, offset\n", num_lines, operand1);
        snprintf(assembly, sizeof(char) * 256, "%d: lw* $62, %s, offset\n", num_lines, operand1);
        save_assembly(assembly);
        break;
    case quad_store:
        num_lines++;
        fprintf(codigoAssembly, "%d: sw $30, %s, %d \n", num_lines, operand2, buscaOffset(operand1));
        snprintf(assembly, sizeof(char) * 256, "%d: sw $30, %s, %d \n", num_lines, operand2, buscaOffset(operand1));
        save_assembly(assembly);
        break;
    case quad_assign:
        num_lines++;
        fprintf(codigoAssembly, "%d: move %s, %s\n", num_lines, operand2, operand1);
        snprintf(assembly, sizeof(char) * 256, "%d: move %s, %s\n", num_lines, operand2, operand1);
        save_assembly(assembly);
        break;
    case quad_call:
    {
        if(strcmp(operand2, "input") == 0)
        {
            num_lines++;
            fprintf(codigoAssembly, "%d: input %s.\n", num_lines, operand1);
            snprintf(assembly, sizeof(char) * 256, "%d: input %s.\n", num_lines, operand1);
            save_assembly(assembly);
        }
        else if(strcmp(operand2, "output") == 0)
        {
            num_lines++;
            fprintf(codigoAssembly, "%d: output $gp.\n", num_lines);
            snprintf(assembly, sizeof(char) * 256, "%d: output $gp.\n", num_lines);
            save_assembly(assembly);
        }
        else
        {
            num_lines++;
            fprintf(codigoAssembly, "%d: subi $62, $62, 2 \n", num_lines);
                snprintf(assembly, sizeof(char) * 256, "%d: subi $62, $62, 2 \n", num_lines);
                save_assembly(assembly);
            num_lines++;
            fprintf(codigoAssembly, "%d: sw $62, $30, 1 \n", num_lines);
                snprintf(assembly, sizeof(char) * 256, "%d: sw $62, $30, 1 \n", num_lines);
                save_assembly(assembly);
            num_lines++;
            fprintf(codigoAssembly, "%d: move $62, $30 \n", num_lines);
                snprintf(assembly, sizeof(char) * 256, "%d: move $62, $30 \n", num_lines);
                save_assembly(assembly);
            num_lines++;
            fprintf(codigoAssembly, "%d: jal %s\n", num_lines, operand2);
                snprintf(assembly, sizeof(char) * 256, "%d: jal %s\n", num_lines, operand2);
                save_assembly(assembly);
            num_lines++;
            fprintf(codigoAssembly, "%d: lw $30, $30, 1 \n", num_lines);
                snprintf(assembly, sizeof(char) * 256, "%d: lw $30, $30, 1 \n", num_lines);
                save_assembly(assembly);
            num_lines++;
            fprintf(codigoAssembly, "%d: move $30, $62 \n", num_lines);
                snprintf(assembly, sizeof(char) * 256, "%d: move $30, $62 \n", num_lines);
                save_assembly(assembly);
            num_lines++;
            fprintf(codigoAssembly, "%d: addi $62, $62, 1\n", num_lines);
                snprintf(assembly, sizeof(char) * 256, "%d: addi $62, $62, 1\n", num_lines);
                save_assembly(assembly);
            num_lines++;
            fprintf(codigoAssembly, "%d: move $gp, %s\n", num_lines, operand1);
                snprintf(assembly, sizeof(char) * 256, "%d: move $gp, %s\n", num_lines, operand1);
                save_assembly(assembly);
            indice_parametro = 0;
        }
        break;
    }
    case quad_iff:
        num_lines++;
        fprintf(codigoAssembly, "%d: bne %s, $0, %s\n", num_lines, operand1, operand2);
            snprintf(assembly, sizeof(char) * 256, "%d: bne %s, $0, %s\n", num_lines, operand1, operand2);
            save_assembly(assembly);
        break;
    case quad_label:
        num_lines++;
        fprintf(codigoAssembly, "%d: label %s\n", num_lines, operand1);
            snprintf(assembly, sizeof(char) * 256, "%d: label %s\n", num_lines, operand1);
            save_assembly(assembly);
        break;
    case quad_goto:
        num_lines++;
        fprintf(codigoAssembly, "%d: jump %s\n", num_lines, operand1);
            snprintf(assembly, sizeof(char) * 256, "%d: jump %s\n", num_lines, operand1);
            save_assembly(assembly);
        break;
    case quad_return:
        num_lines++;
        fprintf(codigoAssembly, "%d: move %s, $gp\n", num_lines, operand1);
            snprintf(assembly, sizeof(char) * 256, "%d: move %s, $gp\n", num_lines, operand1);
            save_assembly(assembly);
        break;
    case quad_add:
        num_lines++;
        fprintf(codigoAssembly, "%d: add %s, %s, %s\n", num_lines, operand1, operand2, operand3);
            snprintf(assembly, sizeof(char) * 256, "%d: add %s, %s, %s\n", num_lines, operand1, operand2, operand3);
            save_assembly(assembly);
        break;
    case quad_sub:
        num_lines++;
        fprintf(codigoAssembly, "%d: sub %s, %s, %s\n", num_lines, operand1, operand2, operand3);
            snprintf(assembly, sizeof(char) * 256, "%d: sub %s, %s, %s\n", num_lines, operand1, operand2, operand3);
            save_assembly(assembly);
        break;
    case quad_mul:
        num_lines++;
        fprintf(codigoAssembly, "%d: mul %s, %s, %s\n", num_lines, operand1, operand2, operand3);
            snprintf(assembly, sizeof(char) * 256, "%d: mul %s, %s, %s\n", num_lines, operand1, operand2, operand3);
            save_assembly(assembly);
        break;
    case quad_div:
        num_lines++;
        fprintf(codigoAssembly, "%d: div %s, %s, %s\n", num_lines, operand1, operand2, operand3);
            snprintf(assembly, sizeof(char) * 256, "%d: div %s, %s, %s\n", num_lines, operand1, operand2, operand3);
            save_assembly(assembly);
        break;
    case quad_maior:
        num_lines++;
        fprintf(codigoAssembly, "%d: slt %s, %s, %s\n", num_lines, operand1, operand3, operand2);
            snprintf(assembly, sizeof(char) * 256, "%d: slt %s, %s, %s\n", num_lines, operand1, operand3, operand2);
            save_assembly(assembly);
        break;
    case quad_menor:
        num_lines++;
        fprintf(codigoAssembly, "%d: slt %s, %s, %s\n", num_lines, operand1, operand2, operand3);
            snprintf(assembly, sizeof(char) * 256, "%d: slt %s, %s, %s\n", num_lines, operand1, operand2, operand3);
            save_assembly(assembly);
        break;
    case quad_maiorigual:
        num_lines++;
        fprintf(codigoAssembly, "%d: slte %s, %s, %s\n", num_lines, operand1, operand3, operand2);
            snprintf(assembly, sizeof(char) * 256, "%d: slte %s, %s, %s\n", num_lines, operand1, operand3, operand2);
            save_assembly(assembly);
        break;
    case quad_menorigual:
        num_lines++;
        fprintf(codigoAssembly, "%d: slte %s, %s, %s\n", num_lines, operand1, operand2, operand3);
            snprintf(assembly, sizeof(char) * 256, "%d: slte %s, %s, %s\n", num_lines, operand1, operand2, operand3);
            save_assembly(assembly);
        break;
    case quad_igual:
    {
        num_lines++;
        fprintf(codigoAssembly, "%d: bne %s, %s,", num_lines, operand2, operand3);
        listaCodInt = listaCodInt->prox;
        char *aux = (char *)malloc(256 * sizeof(char));
        snprintf(aux, sizeof(char) * 256, "%d: bne %s, %s, ", num_lines,operand2, operand3);
        sscanf(listaCodInt->mensagem, " ( %[^,], %[^,], %[^,], %[^)] )", operacao, operand1, operand2, operand3);
        fprintf(codigoAssembly, "%s\n", operand2);
        snprintf(assembly, sizeof(char) * 256, "%s %s\n", aux, operand2);
            save_assembly(assembly);
        break;
    }    
    case quad_diferente:
    {
        num_lines++;
        fprintf(codigoAssembly, "%d: beq %s, %s, ", num_lines, operand2, operand3);
        listaCodInt = listaCodInt->prox;
        char *aux = (char *)malloc(256 * sizeof(char));
        snprintf(aux, sizeof(char) * 256, "%d: beq %s, %s,", num_lines,operand2, operand3);
        sscanf(listaCodInt->mensagem, " ( %[^,], %[^,], %[^,], %[^)] )", operacao, operand1, operand2, operand3);
        fprintf(codigoAssembly, "%s\n", operand2);
        snprintf(assembly, sizeof(char) * 256, "%s %s\n", aux, operand2);
            save_assembly(assembly);

        break;
    }
    case quad_end:
        if(strcmp(operand1, "main") != 0)
        {
            num_lines++;
            fprintf(codigoAssembly, "%d: lw $30, $31, 0\n", num_lines);
                snprintf(assembly, sizeof(char) * 256, "%d: lw $30, $31, 0\n", num_lines);
                save_assembly(assembly);
            num_lines++;
            fprintf(codigoAssembly, "%d: jr $31\n", num_lines);
                snprintf(assembly, sizeof(char) * 256, "%d: jr $31\n", num_lines);
                save_assembly(assembly);
        }
        break;
    case quad_hlt:
        num_lines++;
        fprintf(codigoAssembly, "%d: halt \n", num_lines);
                snprintf(assembly, sizeof(char) * 256, "%d: halt \n", num_lines);
                save_assembly(assembly);
        return;
    default:
        break;
    }
    genAssembly(listaCodInt->prox);
}

void inserir_jump_para_main_assembly() {
    CodAssembly *atual = listaCodAssebly;
    int linha_main = -1;
    int linha;
    char *main = (char *)malloc(20 * sizeof(char));
    // Encontrar linha da main
    while (atual != NULL) {
            sscanf(atual->mensagem, "%d: funcao : %s", &linha, main);
            if(strcmp(main, "main") == 0) {
            linha_main = linha;
            break;
            }
        atual = atual->prox;
    }

    if (linha_main == -1) {
        printf("Erro: função main não encontrada!\n");
        return;
    }

    // Atualizar numeração: +1
    atual = listaCodAssebly;
    while (atual != NULL) {
        char nova[256];
        char *codigo = strchr(atual->mensagem, ':') + 1;
        sscanf(atual->mensagem, "%d:", &linha);
        snprintf(nova, sizeof(nova), "%d:%s", linha + 1, codigo);
        strcpy(atual->mensagem, nova);
        atual = atual->prox;
    }

    // Criar novo nó jump 0
    CodAssembly *novo = (CodAssembly *)malloc(sizeof(CodAssembly));
    snprintf(novo->mensagem, sizeof(novo->mensagem), "1: jump %d\n", linha_main);
    novo->prox = listaCodAssebly;
    listaCodAssebly = novo;

    num_lines++;  // importante: avança contagem total
}

void generate_assembly(Quadrupla  *listaCodInt)
{
    printf("Generating assembly code.. \n");
    if (listaCodInt == NULL) return;
    codigoAssembly = fopen("codAssembly.txt", "w");
    genAssembly(listaCodInt);
    inserir_jump_para_main_assembly();
    imprimirAssembly();
    return;
}