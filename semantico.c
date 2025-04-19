#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "util.h"
#include "symtab.h"
#include "semantico.h"
#include "parser.tab.h"
/* ########################### Analisador Semântico ######################################*/

/* Lista encadeada para armazenar as mensagens de erros */

typedef struct Erro {
    char mensagem[256];  // Armazena a mensagem de erro
    struct Erro *prox;   // Ponteiro para o próximo erro
} Erro;

Erro *listaErros = NULL;  // Ponteiro global para a lista de erros

/* Gera erro semântico para variável já existente */
void errorSemanticoVariavelExistente(char *name, int numline) 
{

    Erro *novoErro = (Erro *)malloc(sizeof(Erro));
    if (!novoErro) 
    {
        printf("Erro de alocação de memória!\n");
    }


    snprintf(novoErro->mensagem, sizeof(novoErro->mensagem), 
             "ERRO SEMÂNTICO: %s LINHA: %d, ID já declarado.\n", name, numline);

    novoErro->prox = listaErros;  // Adicionar ao início da lista
    listaErros = novoErro;
}

/* Gera erro semântico para variável não declarada */
void errorSemanticoVariavelNaoDeclarada(char *name, int numline)
{
    Erro *novoErro = (Erro *)malloc(sizeof(Erro));
    if (!novoErro) 
    {
        printf("Erro de alocação de memória!\n");
        return;
    }

    snprintf(novoErro->mensagem, sizeof(novoErro->mensagem), 
             "ERRO SEMÂNTICO: %s LINHA: %d, ID não declarado antes do uso.\n", name, numline);

    novoErro->prox = listaErros;
    listaErros = novoErro;
}
/* Função para imprimir erros da lista encadeada*/
void imprimirErros() 
{
    Erro *atual = listaErros;
    while (atual) 
    {
        printf("%s", atual->mensagem);
        atual = atual->prox;
    }
}



/* Função para imprimir erros*/
void typeError(TreeNode * t, char * message)
{ 
	printf("ERRO SEMÂNTICO NA LINHA %d: %s\n",t->numline,message);
	return;
}


/* Função para verificar o tipo de nó da árvore sintática*/
void checkNode(TreeNode * t) { 
    if (t == NULL) return;
  
    switch (t->nodekind) { 
        case ExpK:
            switch (t->kind.exp) { 
          /* Verifica se o filho da esquerda ou da direita de uma operação é uma função, se for verifica se há operação de função que retorna void e variável do tipo int*/	
              case OpK:
              /*Verifica se o filho da esquerda é uma função, verificando pelo escopo global, se for verifica o tipo e depois verifica se 
              a função for do tipo void está fazendo operação com inteiro*/
              if(t->child[0] != NULL)
              {
                if(t->child[0]->attr.name != NULL && strcmp(t->child[0]->attr.name, "output") != 0 && strcmp(t->child[0]->attr.name, "input") != 0)
                {
                  t->child[0]->type = st_lookup_type(t->child[0]->attr.name, "global");
                }
                if(t->child[0]->type != Integer && t->child[0]->kind.stmt == CallK){
                  typeError(t, "Operação inválida, variável inteira e função com retorno Void");
                }
              }
              /*Verifica se o filho da direita é uma função, verificando pelo escopo global, se for verifica o tipo e depois verifica se 
              a função for do tipo void está fazendo operação com inteiro*/
              if(t->child[1] != NULL)
              {
                if(t->child[1]->attr.name != NULL && strcmp(t->child[1]->attr.name, "output") != 0 && strcmp(t->child[1]->attr.name, "input") != 0)
                {
                  t->child[1]->type = st_lookup_type(t->child[1]->attr.name, "global");
                }
                if(t->child[1]->type != Integer && t->child[1]->kind.stmt == CallK){
                  typeError(t, "Operação inválida, variável inteira e função com retorno Void");
                }
              }
              break;
  
                default:
                    // Ignora outros casos de ExpK
                    break;
              
            }
            break;
  
        case StmtK:
            switch (t->kind.stmt) {   
                case VarK:
                    // Verifica se o tipo da variável é void
                    if (t->attr.name != NULL && t->escopo != NULL) {
                      BucketList entry = st_lookup_entryFun(t->attr.name, "global", "funcao");
                      if (entry != NULL) {
            
                        // Verifica se o identificador é uma função para verificar conflitos de nomes com funções
                        if (strcmp(entry->tipoID, "funcao") == 0) {
                            typeError(t, "Nome de variável conflita com nome de função");
                        }
                    } 
                    // Verifica se o tipo da variável é void
                    if (t->type == Void) {
                      typeError(t, "Variável não pode ser do tipo void");
                  }
                  }
               break;
  
                case ParamK:
                    // Verifica se o tipo do parâmetro é void
                    if (t->attr.name != NULL && t->escopo != NULL) {
                        t->type = st_lookup_type(t->attr.name, t->escopo);
                        if (t->type == Void) {
                            typeError(t, "Parâmetro não pode ser do tipo void");
                        }
                    }
                    break;
  
                case returnK: 
                    // Verifica se o tipo de retorno é void
                    if (t->child[0] != NULL) {
                        char *funcaoAtual = t->escopo;
                        if (funcaoAtual != NULL) {
                            int type = st_lookup_type(funcaoAtual, "global");
                            if (type == Void && t->child[0]->type != Void) {
                                typeError(t, "Função void não pode retornar um valor");
                            } 
                        }
                    }
                    // Verifica se a função int retorna um valor
                    else
                    {
                      char *funcaoAtual = t->escopo;
                        if (funcaoAtual != NULL) {
                            int type = st_lookup_type(funcaoAtual, "global");
                           if (type != Void) {
                                typeError(t, "Função não-void deve retornar um valor");
                            }
                        }
                    }
                    break;
                
                case AtrK:
                if (t->child[0] != NULL && t->child[1] != NULL) {
                  // Verifica se os tipos são compatíveis
                  
              
                  // Verifica se o lado direito é uma chamada de função
                  if (t->child[1]->kind.stmt == CallK) {
                      // Verifica se o nome da função não é "input" ou "output"
                      if (t->child[1]->attr.name != NULL && strcmp(t->child[1]->attr.name, "output") != 0 && strcmp(t->child[1]->attr.name, "input") != 0) {
                          // Obtém o tipo da função na tabela de símbolos
                          t->child[1]->type = st_lookup_type(t->child[1]->attr.name, "global");
                          if(t->child[1]->type != Undefined){
                          // Verifica se a função foi encontrada na tabela de símbolos
                          if (t->child[1]->type == Void) {
                              typeError(t, "Atribuição inválida, variável inteira e função com retorno Void");
                          } 
                        }
                      }
                  }
              }
                  break;
  
                case CallK:
                /*Insere recursões na tabela de símbolos*/
                if(strcmp(t->attr.name, "output") != 0 || strcmp(t->attr.name, "input") != 0){
                st_insert(0, t->attr.name, "global","funcao", t->type, t->numline, 0);
                }
                break;
                default:
                    // Ignora outros casos de StmtK
                    break;
            }
            break;
  
        default:
            // Ignora outros casos de nodekind
            break;
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
  
  
  /* Função para percorrer a árvore sintática e chamar a função de verificação de nós*/
  void traverse(TreeNode * t,
    void (* preProc) (TreeNode *),
    void (* postProc) (TreeNode *)) {
  if (t != NULL) {
  preProc(t);  // Executa antes de percorrer os filhos (pré-ordem)
  
  for (int i = 0; i < MAXCHILDREN; i++) {
  traverse(t->child[i], preProc, postProc);
  }
  
  postProc(t);  // Executa depois de percorrer os filhos (pós-ordem)
  traverse(t->sibling, preProc, postProc); // Percorre os irmãos
  }
  }
  
  void noop(TreeNode *t) { /* Não faz nada */ }
  
  /* Analisador Semântico*/
  void semanticCheck(TreeNode *syntaxTree) {
    traverse(syntaxTree, noop, checkNode);
    if (st_lookup("main", "global") == -1) {
      typeError(syntaxTree, "Função main não declarada");
    }
  }
  