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
    char nome[50];      
    int offset;         
    char escopo[50];    
    int tamanho;        
} Simbolo;

Simbolo tabela_simbolos[MAX_SIMBOLOS];
int num_simbolos = 0;
int offset_global = 511;  
int offset_local = -1;    

void limpaTabelaSimbolos() {
    int j = 0;
    for (int i = 0; i < num_simbolos; i++) {
        if (strcmp(tabela_simbolos[i].escopo, "global") == 0) {
            if (i != j) tabela_simbolos[j] = tabela_simbolos[i];
            j++;
        }
    }
    num_simbolos = j;
    offset_local = -1;
}

Simbolo *buscaSimbolo(const char *nome) {
    for (int i = 0; i < num_simbolos; i++) {
        if (strcmp(tabela_simbolos[i].nome, nome) == 0) {
            return &tabela_simbolos[i];
        }
    }
    return NULL;
}

int simboloEhGlobal(const char *nome) {
    Simbolo *simb = buscaSimbolo(nome);
    return simb && strcmp(simb->escopo, "global") == 0;
}

void insereSimbolo(const char *nome, const char *escopo, int tamanho) {
    if (num_simbolos >= MAX_SIMBOLOS) return;

    // Verifica se o símbolo já existe no mesmo escopo
    for (int i = 0; i < num_simbolos; i++) {
        if (strcmp(tabela_simbolos[i].nome, nome) == 0 && 
            strcmp(tabela_simbolos[i].escopo, escopo) == 0) {
            return;  // Evita duplicatas
        }
    }

    // Insere o novo símbolo
    strcpy(tabela_simbolos[num_simbolos].nome, nome);
    strcpy(tabela_simbolos[num_simbolos].escopo, escopo);
    tabela_simbolos[num_simbolos].tamanho = tamanho;  // Para vetores

    // Define o offset conforme o escopo
    if (strcmp(escopo, "global") == 0) {
        tabela_simbolos[num_simbolos].offset = offset_global;
        offset_global -= (tamanho > 0) ? tamanho : 1;  // Aloca espaço para vetores
    } 
    else {  // Escopo local (ex: "minloc")
        tabela_simbolos[num_simbolos].offset = offset_local;
        offset_local -= (tamanho > 0) ? tamanho : 1;
    }

    num_simbolos++;
}


int buscaOffset(const char *nome) {
    Simbolo *simb = buscaSimbolo(nome);
    if (!simb) {
        printf("Erro: Símbolo '%s' não encontrado!\n", nome);
        return 0;
    }
    return simb->offset;
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
    quad_hlt,
    quad_allocvet,
    quad_loadvet,
    quad_storevet,
    quad_move,
    quad_loadcall,
    quad_loadret
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
    if(strcmp(stringOp, "ALLOCVET") == 0) return quad_allocvet;
    if(strcmp(stringOp, "LOADVET") == 0) return quad_loadvet;
    if(strcmp(stringOp, "STOREVET") == 0) return quad_storevet;
    if(strcmp(stringOp, "MOVE") == 0) return quad_move;
    if(strcmp(stringOp, "LOADCALL") == 0) return quad_loadcall;
    if(strcmp(stringOp, "LOADRET") == 0) return quad_loadret;
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
        insereSimbolo(operand2, operand3, 1);
        num_lines++;
        fprintf(codigoAssembly, "%d: subi $62, $62, 1\n", num_lines);
        snprintf(assembly, sizeof(char) * 256, "%d: subi $62, $62, 1\n", num_lines);
        save_assembly(assembly);
        num_lines++;
        fprintf(codigoAssembly, "%d: sw $30, $a%d, %d\n", num_lines , indice_parametro, buscaOffset(operand2)); 
        snprintf(assembly, sizeof(char) * 256, "%d: sw $30, $a%d, %d\n", num_lines , indice_parametro, buscaOffset(operand2));
        save_assembly(assembly);
        indice_parametro++;
        break;
    case quad_parametro:
    {
                if (indice_parametro < 4)
                {
                    num_lines++;
                    int imediato;
                    if(sscanf(operand1, "$t%d", &imediato) != 1){
                        imediato = atoi(operand1);
                        fprintf(codigoAssembly, "%d: addi $a%d, $0, %d\n", num_lines, indice_parametro, imediato );
                        snprintf(assembly, sizeof(char) * 256, "%d: addi $a%d, $0, %d\n", num_lines, indice_parametro, imediato);
                        save_assembly(assembly);
                    }
                    else
                    {
                        fprintf(codigoAssembly, "%d: move %s, $a%d\n", num_lines , operand1, indice_parametro);
                        snprintf(assembly, sizeof(char) * 256, "%d: move %s, $a%d\n", num_lines , operand1, indice_parametro);
                        save_assembly(assembly);
                    }
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
    }
    case quad_alloc:
        indice_parametro = 0;
        insereSimbolo(operand1, operand3, 0);
        num_lines++;
        fprintf(codigoAssembly, "%d: subi $62, $62, 1\n", num_lines);
        snprintf(assembly, sizeof(char) * 256, "%d: subi $62, $62, 1\n", num_lines);
        save_assembly(assembly);
        break;
    case quad_load:
        num_lines++;
        if(simboloEhGlobal(operand2))
        {
            fprintf(codigoAssembly, "%d: addi %s, $0, %d \n", num_lines, operand1, buscaOffset(operand2));
            snprintf(assembly, sizeof(char) * 256, "%d: addi %s, $0, %d \n", num_lines, operand1, buscaOffset(operand2));
            save_assembly(assembly);
        }
        else if(strcmp(operand2, "gb") == 0)
        {
            fprintf(codigoAssembly, "%d: lw %s, $gb, 0 \n", num_lines , operand1);
            snprintf(assembly, sizeof(char) * 256, "%d: lw %s, $gb, 0 \n", num_lines , operand1);
            save_assembly(assembly);
        }
        else
        {
        fprintf(codigoAssembly, "%d: lw $30, %s, %d \n", num_lines , operand1, buscaOffset(operand2));
        snprintf(assembly, sizeof(char) * 256, "%d: lw $30, %s, %d \n", num_lines , operand1, buscaOffset(operand2));
        save_assembly(assembly);
        }
        break;
    case quad_loadcall:
    {
        num_lines++;
            fprintf(codigoAssembly, "%d: subi $62, $62, 1 \n", num_lines);
            snprintf(assembly, sizeof(char) * 256, "%d: subi $62, $62, 1 \n", num_lines);
            save_assembly(assembly);
        num_lines++;
            fprintf(codigoAssembly, "%d: sw $62, %s, 0 \n", num_lines, operand1 );
            snprintf(assembly, sizeof(char) * 256, "%d: sw $62, %s, 0 \n", num_lines, operand1 );
            save_assembly(assembly);
        break;   
    }
    case quad_loadaddr:
    {
        num_lines++;
        if(simboloEhGlobal(operand2))
        {
            fprintf(codigoAssembly, "%d: addi %s, $0, %d \n", num_lines, operand1, buscaOffset(operand2));
            snprintf(assembly, sizeof(char) * 256, "%d: addi %s, $0, %d \n", num_lines, operand1, buscaOffset(operand2));
            save_assembly(assembly);
        }
        else
        {
        fprintf(codigoAssembly, "%d: lw $30, %s, %d \n", num_lines, operand1, buscaOffset(operand2));
        snprintf(assembly, sizeof(char) * 256, "%d: lw $30, %s, %d \n", num_lines, operand1, buscaOffset(operand2));
        save_assembly(assembly);
        }
        break;
    }
    case quad_loadret:
    {
        num_lines++;
        fprintf(codigoAssembly, "%d: lw $62, %s, 0 \n", num_lines, operand1 );
        snprintf(assembly, sizeof(char) * 256, "%d: lw $62, %s, 0 \n", num_lines, operand1 );
        save_assembly(assembly);
        break;
    }
    case quad_loadvet:
    {
        num_lines++;
        if(simboloEhGlobal(operand3))
        {
            fprintf(codigoAssembly, "%d: lw %s, %s, 0 \n", num_lines , operand1, operand2);
            snprintf(assembly, sizeof(char) * 256, "%d: lw %s, %s, 0 \n", num_lines , operand1, operand2);
            save_assembly(assembly);
        }
        else
        {
        fprintf(codigoAssembly, "%d: lw %s, %s, 0 \n", num_lines, operand1, operand2);
        snprintf(assembly, sizeof(char) * 256, "%d: lw %s, %s, 0 \n", num_lines, operand1, operand2);
        save_assembly(assembly);
        }
        break;
    }
    case quad_storevet:
    {
        num_lines++;
        if(simboloEhGlobal(operand1))
        {
            fprintf(codigoAssembly, "%d: sw %s, %s, 0 \n", num_lines, operand3, operand2);
            snprintf(assembly, sizeof(char) * 256, "%d: sw %s, %s, 0 \n", num_lines, operand3, operand2);
            save_assembly(assembly);
        }
        else
        {
            fprintf(codigoAssembly, "%d: sw %s, %s, 0 \n", num_lines, operand3, operand2);
            snprintf(assembly, sizeof(char) * 256, "%d: sw %s, %s, 0 \n", num_lines, operand3, operand2);
            save_assembly(assembly);
        }
        break;
    }
    case quad_store:
        num_lines++;
        if(simboloEhGlobal(operand1))
        {
            fprintf(codigoAssembly, "%d: sw $gb, %s, 0 \n", num_lines, operand2);
            snprintf(assembly, sizeof(char) * 256, "%d: sw $gb, %s, 0 \n", num_lines, operand2);
            save_assembly(assembly);
        }
        else
        {
            fprintf(codigoAssembly, "%d: sw $30, %s, %d \n", num_lines, operand2, buscaOffset(operand1));
            snprintf(assembly, sizeof(char) * 256, "%d: sw $30, %s, %d \n", num_lines, operand2, buscaOffset(operand1));
            save_assembly(assembly);
        }
        break;
    case quad_assign:
    {
        int imediato = 0;
        num_lines++;
        if(sscanf(operand2, "$t%d", &imediato) != 1){
            imediato = atoi(operand2);
            fprintf(codigoAssembly, "%d: addi %s, $0, %d\n", num_lines, operand1, imediato);
            snprintf(assembly, sizeof(char) * 256, "%d: addi %s, $0, %d\n", num_lines, operand1, imediato);
            save_assembly(assembly);
        }
        else
        {
            fprintf(codigoAssembly, "%d: move %s, %s\n", num_lines, operand2, operand1);
            snprintf(assembly, sizeof(char) * 256, "%d: move %s, %s\n", num_lines, operand2, operand1);
            save_assembly(assembly);
        }
        break;
    }
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

            fprintf(codigoAssembly, "%d: output $a0.\n", num_lines );
            snprintf(assembly, sizeof(char) * 256, "%d: output $a0.\n", num_lines);
            save_assembly(assembly);
        }
        else
        {
            num_lines++;
            fprintf(codigoAssembly, "%d: sw $62, $62, -1 \n", num_lines);
                snprintf(assembly, sizeof(char) * 256, "%d: sw $62, $62, -1 \n", num_lines);
                save_assembly(assembly);
            num_lines++;
            fprintf(codigoAssembly, "%d: subi $62, $62, 3 \n", num_lines);
                snprintf(assembly, sizeof(char) * 256, "%d: subi $62, $62, 3 \n", num_lines);
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
            fprintf(codigoAssembly, "%d: lw $30, $62, 2 \n", num_lines);
                snprintf(assembly, sizeof(char) * 256, "%d: lw $30, $62, 2 \n", num_lines);
                save_assembly(assembly);
            num_lines++;
            fprintf(codigoAssembly, "%d: lw $30, $30, 1 \n", num_lines);
                snprintf(assembly, sizeof(char) * 256, "%d: lw $30, $30, 1 \n", num_lines);
                save_assembly(assembly);
            num_lines++;
            fprintf(codigoAssembly, "%d: move $v0, %s\n", num_lines, operand1);
                snprintf(assembly, sizeof(char) * 256, "%d: move $v0, %s\n", num_lines, operand1);
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
                    indice_parametro = 0;
        break;
    case quad_goto:
        num_lines++;
        fprintf(codigoAssembly, "%d: jump %s\n", num_lines, operand1);
            snprintf(assembly, sizeof(char) * 256, "%d: jump %s\n", num_lines, operand1);
            save_assembly(assembly);
        break;
    case quad_return:
    {
        num_lines++;
        int imediato;
        if(sscanf(operand1, "$t%d", &imediato) != 1){
            imediato = atoi(operand1);
            fprintf(codigoAssembly, "%d: addi $v0, $0, %d\n", num_lines, imediato);
            snprintf(assembly, sizeof(char) * 256, "%d: addi $v0, $0, %d\n", num_lines, imediato);
            save_assembly(assembly);
        }
        else
        {
        fprintf(codigoAssembly, "%d: move %s, $v0\n", num_lines, operand1);
            snprintf(assembly, sizeof(char) * 256, "%d: move %s, $v0\n", num_lines, operand1);
            save_assembly(assembly);
        }
        break;
    }
    case quad_add:
    {
        num_lines++;
        int imediato;
        if(sscanf(operand3, "$t%d", &imediato) != 1){
            imediato = atoi(operand3);
            fprintf(codigoAssembly, "%d: addi %s, %s, %d\n", num_lines, operand1, operand2, imediato);
            snprintf(assembly, sizeof(char) * 256, "%d: addi %s, %s, %d\n", num_lines, operand1, operand2, imediato);
            save_assembly(assembly);
        }
        else
        {
        fprintf(codigoAssembly, "%d: add %s, %s, %s\n", num_lines, operand1, operand2, operand3);
            snprintf(assembly, sizeof(char) * 256, "%d: add %s, %s, %s\n", num_lines, operand1, operand2, operand3);
            save_assembly(assembly);
        }
        break;
    }
    case quad_sub:
        num_lines++;
        int imediato;
        if(sscanf(operand3, "$t%d", &imediato) != 1){
            imediato = atoi(operand3);
            fprintf(codigoAssembly, "%d: subi %s, %s, %d\n", num_lines, operand1, operand2, imediato);
            snprintf(assembly, sizeof(char) * 256, "%d: subi %s, %s, %d\n", num_lines, operand1, operand2, imediato);
            save_assembly(assembly);
        }
        else
        {
        fprintf(codigoAssembly, "%d: sub %s, %s, %s\n", num_lines, operand1, operand2, operand3);
            snprintf(assembly, sizeof(char) * 256, "%d: sub %s, %s, %s\n", num_lines, operand1, operand2, operand3);
            save_assembly(assembly);
        }
        break;
    case quad_mul:
        num_lines++;
        fprintf(codigoAssembly, "%d: mul %s, %s, %s\n", num_lines, operand1, operand2, operand3);
            snprintf(assembly, sizeof(char) * 256, "%d: mul %s, %s, %s\n", num_lines, operand1, operand2, operand3);
            save_assembly(assembly);
        break;
    case quad_div:
    {
        num_lines++;
        int imediato;
        if(sscanf(operand3, "$t%d", &imediato) != 1){
            imediato = atoi(operand3);
            fprintf(codigoAssembly, "%d: addi %s, $0, %d\n", num_lines, operand1, imediato);
            snprintf(assembly, sizeof(char) * 256, "%d: addi %s, $0, %d\n", num_lines, operand1, imediato);
            save_assembly(assembly);
            num_lines++;
            fprintf(codigoAssembly, "%d: div %s, %s, %s\n", num_lines, operand1, operand2, operand1);
            snprintf(assembly, sizeof(char) * 256, "%d: div %s, %s, %s\n", num_lines, operand1, operand2, operand1);
            save_assembly(assembly);
        }
        else
        {
            fprintf(codigoAssembly, "%d: div %s, %s, %s\n", num_lines, operand1, operand2, operand3);
            snprintf(assembly, sizeof(char) * 256, "%d: div %s, %s, %s\n", num_lines, operand1, operand2, operand3);
            save_assembly(assembly);
        }
    }
    break;
    case quad_maior:
    {
        num_lines++;
        int imediato;
        if(sscanf(operand3, "$t%d", &imediato) != 1){
            imediato = atoi(operand3);
            fprintf(codigoAssembly, "%d: addi %s, $0, %d\n", num_lines, operand1, imediato);
            snprintf(assembly, sizeof(char) * 256, "%d: addi %s, $0, %d\n", num_lines, operand1, imediato);
            save_assembly(assembly);
            num_lines++;
            fprintf(codigoAssembly, "%d: slt %s, %s, %s\n", num_lines, operand1, operand1, operand2);
            snprintf(assembly, sizeof(char) * 256, "%d: slt %s, %s, %s\n", num_lines, operand1, operand1, operand2);
            save_assembly(assembly);
        }
        else
        {
            fprintf(codigoAssembly, "%d: slt %s, %s, %s\n", num_lines, operand1, operand3, operand2);
            snprintf(assembly, sizeof(char) * 256, "%d: slt %s, %s, %s\n", num_lines, operand1, operand3, operand2);
            save_assembly(assembly);
        }
            break;
    }
    case quad_menor:
    {
        num_lines++;
        int imediato;
        if(sscanf(operand3, "$t%d", &imediato) != 1){
            imediato = atoi(operand3);
            fprintf(codigoAssembly, "%d: addi %s, $0, %d\n", num_lines, operand1, imediato);
            snprintf(assembly, sizeof(char) * 256, "%d: addi %s, $0, %d\n", num_lines, operand1, imediato);
            save_assembly(assembly);
            num_lines++;
            fprintf(codigoAssembly, "%d: slt %s, %s, %s\n", num_lines, operand1, operand2, operand1);
            snprintf(assembly, sizeof(char) * 256, "%d: slt %s, %s, %s\n", num_lines, operand1, operand2, operand1);
            save_assembly(assembly);
        }
        else
        {
            fprintf(codigoAssembly, "%d: slt %s, %s, %s\n", num_lines, operand1, operand2, operand3);
            snprintf(assembly, sizeof(char) * 256, "%d: slt %s, %s, %s\n", num_lines, operand1, operand2, operand3);
            save_assembly(assembly);
        }
        break;
    }
    case quad_maiorigual:
    {
        num_lines++;
        int imediato;
        if(sscanf(operand3, "$t%d", &imediato) != 1){
            imediato = atoi(operand3);
            fprintf(codigoAssembly, "%d: addi %s, $0, %d\n", num_lines, operand1, imediato);
            snprintf(assembly, sizeof(char) * 256, "%d: addi %s, $0, %d\n", num_lines, operand1, imediato);
            save_assembly(assembly);
            num_lines++;
            fprintf(codigoAssembly, "%d: slte %s, %s, %s\n", num_lines, operand1, operand1, operand2);
            snprintf(assembly, sizeof(char) * 256, "%d: slte %s, %s, %s\n", num_lines, operand1, operand1, operand2);
            save_assembly(assembly);
        }
        else
        {
        fprintf(codigoAssembly, "%d: slte %s, %s, %s\n", num_lines, operand1, operand3, operand2);
            snprintf(assembly, sizeof(char) * 256, "%d: slte %s, %s, %s\n", num_lines, operand1, operand3, operand2);
            save_assembly(assembly);
        break;
        }
    }
    case quad_menorigual:
    {
        num_lines++;
        int imediato;
        if(sscanf(operand3, "$t%d", &imediato) != 1){
            imediato = atoi(operand3);
            fprintf(codigoAssembly, "%d: addi %s, $0, %d\n", num_lines, operand1, imediato);
            snprintf(assembly, sizeof(char) * 256, "%d: addi %s, $0, %d\n", num_lines, operand1, imediato);
            save_assembly(assembly);
            num_lines++;
            fprintf(codigoAssembly, "%d: slte %s, %s, %s\n", num_lines, operand1, operand2, operand1);
            snprintf(assembly, sizeof(char) * 256, "%d: slte %s, %s, %s\n", num_lines, operand1, operand2, operand1);
            save_assembly(assembly);
        }
        else
        {
        fprintf(codigoAssembly, "%d: slte %s, %s, %s\n", num_lines, operand1, operand2, operand3);
            snprintf(assembly, sizeof(char) * 256, "%d: slte %s, %s, %s\n", num_lines, operand1, operand2, operand3);
            save_assembly(assembly);
        }
        break;
    }
    case quad_igual:
    {
        num_lines++;
        int imediato;
        if(sscanf(operand3, "$t%d", &imediato) != 1){
            imediato = atoi(operand3);
            fprintf(codigoAssembly, "%d: addi %s, $0, %d\n", num_lines, operand1, imediato);
            snprintf(assembly, sizeof(char) * 256, "%d: addi %s, $0, %d\n", num_lines, operand1, imediato);
            save_assembly(assembly);
            num_lines++;
            fprintf(codigoAssembly, "%d: bne %s, %s,", num_lines, operand2, operand1);
            listaCodInt = listaCodInt->prox;
            char *aux = (char *)malloc(256 * sizeof(char));
            snprintf(aux, sizeof(char) * 256, "%d: bne %s, %s, ", num_lines,operand2, operand1);
            sscanf(listaCodInt->mensagem, " ( %[^,], %[^,], %[^,], %[^)] )", operacao, operand1, operand2, operand3);
            fprintf(codigoAssembly, "%s\n", operand2);
            snprintf(assembly, sizeof(char) * 256, "%s %s\n", aux, operand2);
                save_assembly(assembly);
        }
        else
        {
        fprintf(codigoAssembly, "%d: bne %s, %s,", num_lines, operand2, operand3);
        listaCodInt = listaCodInt->prox;
        char *aux = (char *)malloc(256 * sizeof(char));
        snprintf(aux, sizeof(char) * 256, "%d: bne %s, %s, ", num_lines,operand2, operand3);
        sscanf(listaCodInt->mensagem, " ( %[^,], %[^,], %[^,], %[^)] )", operacao, operand1, operand2, operand3);
        fprintf(codigoAssembly, "%s\n", operand2);
        snprintf(assembly, sizeof(char) * 256, "%s %s\n", aux, operand2);
            save_assembly(assembly);
        }
        break;
    }    
    case quad_diferente:
    {

        int imediato;
        if(sscanf(operand3, "$t%d", &imediato) != 1){
            imediato = atoi(operand3);
            fprintf(codigoAssembly, "%d: addi %s, $0, %d\n", num_lines, operand1, imediato);
            snprintf(assembly, sizeof(char) * 256, "%d: addi %s, $0, %d\n", num_lines, operand1, imediato);
            save_assembly(assembly);
            num_lines++;
            fprintf(codigoAssembly, "%d: beq %s, %s,", num_lines, operand2, operand1);
            listaCodInt = listaCodInt->prox;
            char *aux = (char *)malloc(256 * sizeof(char));
            snprintf(aux, sizeof(char) * 256, "%d: beq %s, %s, ", num_lines,operand2, operand1);
            sscanf(listaCodInt->mensagem, " ( %[^,], %[^,], %[^,], %[^)] )", operacao, operand1, operand2, operand3);
            fprintf(codigoAssembly, "%s\n", operand2);
            snprintf(assembly, sizeof(char) * 256, "%s %s\n", aux, operand2);
                save_assembly(assembly);
        }
        else
        {
        fprintf(codigoAssembly, "%d: beq %s, %s, ", num_lines, operand2, operand3);
        listaCodInt = listaCodInt->prox;
        char *aux = (char *)malloc(256 * sizeof(char));
        snprintf(aux, sizeof(char) * 256, "%d: beq %s, %s,", num_lines,operand2, operand3);
        sscanf(listaCodInt->mensagem, " ( %[^,], %[^,], %[^,], %[^)] )", operacao, operand1, operand2, operand3);
        fprintf(codigoAssembly, "%s\n", operand2);
        snprintf(assembly, sizeof(char) * 256, "%s %s\n", aux, operand2);
            save_assembly(assembly);
        }

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
    case quad_allocvet:
        num_lines++;
        insereSimbolo(operand1, operand2, 10);
        fprintf(codigoAssembly, "%d: subi $gsp, $gsp, %d \n", num_lines, atoi(operand3));
                snprintf(assembly, sizeof(char) * 256, "%d: subi $gsp, $gsp, %d \n", num_lines, atoi(operand3));
                save_assembly(assembly);
        break;
    case quad_move:
    fprintf(codigoAssembly, "%d: move %s, %s\n", num_lines, operand2, operand1);
            snprintf(assembly, sizeof(char) * 256, "%d: move %s, %s\n", num_lines, operand2, operand1);
            save_assembly(assembly);
    num_lines++;
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
    char main[20];
    
    // 1. Find the line number of main function
    while (atual != NULL) {
        if (sscanf(atual->mensagem, "%d: funcao : %19s", &linha, main) == 2) {
            if (strcmp(main, "main") == 0) {
                linha_main = linha;
                break;
            }
        }
        atual = atual->prox;
    }

    if (linha_main == -1) {
        printf("Erro: função main não encontrada!\n");
        return;
    }

    // 2. Find the insertion point (after global vars, before first function)
    int insertion_line = 1;
    atual = listaCodAssebly;
    CodAssembly *anterior = NULL;
    
    while (atual != NULL) {
        // Check if this is a function declaration
        if (sscanf(atual->mensagem, "%d: funcao : %19s", &linha, main) == 2) {
            // Found first function - insert before this
            break;
        }
        // Not a function - could be global var allocation
        insertion_line = linha + 1; // Keep track of last line number
        anterior = atual;
        atual = atual->prox;
    }

    // 3. Update line numbers for all subsequent lines (+1)
    CodAssembly *temp = atual;
    while (temp != NULL) {
        char *codigo = strchr(temp->mensagem, ':');
        if (codigo != NULL) {
            int old_linha;
            sscanf(temp->mensagem, "%d:", &old_linha);
            char nova[256];
            snprintf(nova, sizeof(nova), "%d:%s", old_linha + 1, codigo + 1);
            strcpy(temp->mensagem, nova);
        }
        temp = temp->prox;
    }

    // 4. Create and insert the new jump instruction
    CodAssembly *novo = (CodAssembly *)malloc(sizeof(CodAssembly));
    if (novo == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    
    snprintf(novo->mensagem, sizeof(novo->mensagem), "%d: jump %d\n", insertion_line, linha_main);
    
    // Insert the new node at the correct position
    if (anterior == NULL) {
        // Insert at beginning
        novo->prox = listaCodAssebly;
        listaCodAssebly = novo;
    } else {
        // Insert after global variables
        novo->prox = anterior->prox;
        anterior->prox = novo;
    }

    num_lines++;  // Update total line count
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