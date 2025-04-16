#include "util.h"
#include "parser.tab.h"
#include "global.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* ########################### Arvore Sintática Abstrata ######################################*/

/* Lista encadeada para armazenar as mensagens de erros */

typedef struct Erro {
    char mensagem[256];  // Armazena a mensagem de erro
    struct Erro *prox;   // Ponteiro para o próximo erro
} Erro;

Erro *listaErros = NULL;  // Ponteiro global para a lista de erros

FILE *save_tree;
FILE *save_symTable;

/* ########################## Imprime tokens e lexemas correspondentes ####################################*/
void printToken( TokenType token, const char* tokenString )
{ switch (token)
  { case IF:  printf("IF"); 	 	break;
    case ELSE: printf("ELSE");   	break;
    case VOID: printf("VOID");  	break;
    case WHILE: printf("WHILE"); 	break;
    case RETURN: printf("RETURN");	break;
    case INT: printf("INT"); 		break;
    case SOM: printf("SOM = +"); 	break;
    case SUB: printf("SUB = -"); 	break;
    case MUL: printf("MUL = *"); 	break;
    case DIV: printf("DIV = /"); 	break;
    case MAI: printf("MAI = >"); 	break;
    case MEN: printf("MEN = <"); 	break;
    case MIG: printf("MIG = >="); 	break;
    case MEI: printf("MEI = <="); 	break;
    case IGU: printf("IGU = =="); 	break;
    case DIF: printf("DIF = !="); 	break;
    case ATR: printf("ATR = ="); 	break;
    case PEV: printf("PEV = ;"); 	break;
    case VIR: printf("VIR = ,"); 	break;
    case APA: printf("APA = ("); 	break;
    case FPA: printf("FPA = )"); 	break;
    case ACO: printf("ACO = ["); 	break;
    case FCO: printf("FCO = ]"); 	break;
    case ACH: printf("ACH = {"); 	break;
    case FCH: printf("FCH = }"); 	break;                
    case NUM:
      printf("NUM, val= %s",tokenString);
      break;
    case ID:
      printf("ID, name= %s",tokenString);
      break;
    case ERRO:
      printf("ERROR: %s",tokenString);
      break;
    default: /* should never happen */
      printf("Unknown token: %d",token);
  }
}

void printTokenExternFile( TokenType token, const char* tokenString )
{ 
	   switch (token)
	    { 
	    case IF:      			      break;
	    case ELSE:    			      break;
	    case VOID:    			      break;
	    case WHILE:   			      break;
	    case RETURN:  			      break;
	    case INT: fprintf(save_tree, "INT");      break;
	    case SOM: fprintf(save_tree, "SOM = +");  break;
	    case SUB: fprintf(save_tree, "SUB = -");  break;
	    case MUL: fprintf(save_tree, "MUL = *");  break;
	    case DIV: fprintf(save_tree, "DIV = /");  break;
	    case MAI: fprintf(save_tree, "MAI = >");  break;
	    case MEN: fprintf(save_tree, "MEN = <");  break;
	    case MIG: fprintf(save_tree, "MIG = >="); break;
	    case MEI: fprintf(save_tree, "MEI = <="); break;
	    case IGU: fprintf(save_tree, "IGU = =="); break;
	    case DIF: fprintf(save_tree, "DIF = !="); break;
	    case ATR: fprintf(save_tree, "ATR = =");  break;
	    case PEV: fprintf(save_tree, "PEV = ;");  break;
	    case VIR: fprintf(save_tree, "VIR = ,");  break;
	    case APA: fprintf(save_tree, "APA = (");  break;
	    case FPA: fprintf(save_tree, "FPA = )");  break;
	    case ACO: fprintf(save_tree, "ACO = [");  break;
	    case FCO: fprintf(save_tree, "FCO = ]");  break;
	    case ACH: fprintf(save_tree, "ACH = {");  break;
	    case FCH: fprintf(save_tree, "FCH = }");  break;                
	    case NUM:
	      fprintf(save_tree, "NUM, val= %s",tokenString);
	      break;
	    case ID:
	      fprintf(save_tree, "ID, name= %s",tokenString);
	      break;
	    case ERRO:
	      fprintf(save_tree, "ERROR: %s",tokenString);
	      break;
	    default: /* should never happen */
	      fprintf(save_tree, "Unknown token: %d",token);
	  }
}


/* Cria um nó da arvore do tipo statement cria o nó e retorna para o parser*/
TreeNode *newStmtNode(StmtKind kind)
{ 
	TreeNode *t = (TreeNode*) malloc(sizeof(TreeNode));
	  int i;
	  if (t==NULL)
	    printf("Out of memory error at line %d\n",numline);
	  else {
	    for (i=0; i < MAXCHILDREN; i++) t->child[i] = NULL;
	    t->sibling = NULL;
		t->nodekind = StmtK;
		t->kind.stmt = kind;
		t->numline = numline;
		t->attr.vetor = 0;
	  }
	  return t;
}

/* Cria um nó da arvore do tipo expressao cria o nó e retorna para o parser*/
TreeNode *newExpNode(ExpKind kind)
{ 
	TreeNode *t = (TreeNode*) malloc(sizeof(TreeNode));
	  int i;
	  if (t==NULL)
	    printf("Out of memory error at line %d\n", numline);
	  else {
	    for (i=0; i<MAXCHILDREN ; i++) t->child[i] = NULL;
	    t->sibling = NULL;
		t->nodekind = ExpK;
		t->kind.exp = kind;
		t->numline = numline;
		t->type = Void;
		t->attr.vetor = 0;
	  }
	  return t;
}

/* Copia uma string para outra variável*/
char *copyString(char * s)
{ 
	int n;
	  char * t;
	  if (s == NULL) return NULL;
	  n = strlen(s) + 1;
	  t = (char*)malloc(n);
	  if (t==NULL)
	    printf("Out of memory error at line %d\n",numline);
	  else strcpy(t,s);
	  return t;
}

static int indentno = 0;


/* Identação para imprimir a arvore sintatica abstrata*/
#define INDENT indentno+=2
#define UNINDENT indentno-=2

static void printSpaces(void)
{ int i;
  for (i=0;i<indentno;i++)
    fprintf(save_tree, " ");
}

/* Imprime todos os nós da árvore*/
void printTree( TreeNode *tree )
{ 
	int i;
	  INDENT;
	  while (tree != NULL) {
	    printSpaces();
	    if (tree->nodekind==StmtK)
	    { switch (tree->kind.stmt) {
		case IfK:
		  fprintf(save_tree, "If\n");
		  break;
		case WhileK:
		  fprintf(save_tree, "While\n");
		  break;
		case returnK:
		  fprintf(save_tree, "return\n");
		  break;
		case AtrK:
			fprintf(save_tree, "Atribuicao\n");
			break;
		case VarK:
			fprintf(save_tree, "Var: %s\n", tree->attr.name);
			break;
		case FunK:
			fprintf(save_tree, "Fun: %s\n", tree->attr.name);
			break;
		case CallK:
			fprintf(save_tree, "Chamada: %s\n", tree->attr.name);
			break;
		case ParamK:
			fprintf(save_tree, "Parametro: %s\n", tree->attr.name);
			break;
		default:
		  fprintf(save_tree, "Unknown ExpNode kind\n");
		  break;
	      }
	    }
	    else if (tree->nodekind==ExpK)
	    { switch (tree->kind.exp) {
		case OpK:
		  fprintf(save_tree, "Op: ");
		  printTokenExternFile(tree->attr.op,"\0");
      			fprintf(save_tree, "\n");
		  break;
		case ConstK:
		  fprintf(save_tree, "Const: %d\n",tree->attr.val);
		  break;
		case IdK:
		  fprintf(save_tree, "Id: %s\n",tree->attr.name);
		  break;
		case TypeK:
		  fprintf(save_tree, "Type: %d\n", tree->type);
			break;
		case VetK:
			fprintf(save_tree, "Vetor: %s\n", tree->attr.name);
		break;
		default:
		  fprintf(save_tree, "Unknown ExpNode kind\n");
		  break;
	      }
	    }
	    else fprintf(save_tree, "Unknown node kind\n");
	    for (i=0;i<MAXCHILDREN;i++)
		 printTree(tree->child[i]);
	    tree = tree->sibling;
	  }
	  UNINDENT;
}


void printTreeArq(TreeNode *tree)
{
	save_tree = fopen("tree_generate.txt", "w");
	printTree(tree);
}

/* ########################### Tabela  de símbolos ######################################*/

#define SIZE 211 
#define SHIFT 4

static char *currentFunction = "global";  // Inicializa como global

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
    temp = ((temp << SHIFT) + key[i]) % SIZE;
    ++i;
  }
  return temp;
}
/* Lista de linhas em que determinado id aparece no código*/
typedef struct LineListRec
   { int numline;
     struct LineListRec * next;
   } * LineList;

/* Lista de linhas em que determinado id aparece no código*/

   typedef struct BucketListRec 
   { char * name;
     LineList lines;
     int memloc ;
     char * escopo;
     char * tipoID;
     int  tipoDado; 
     struct BucketListRec * next;
   } * BucketList;
   
   static BucketList hashTable[SIZE];
   
   
   
   
   
   
   

/* ########################### Analisador Semântico ######################################*/

void errorSemanticoVariavelExistente(char *name, int numline);
void errorSemanticoVariavelNaoDeclarada(char *name, int numline);
BucketList st_lookup_entry(char *name, char *escopo);
BucketList st_lookup_entryFun(char *name, char *escopo, char *tipoID);

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
          } else {
              errorSemanticoVariavelNaoDeclarada(name, numline);
              return;
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

/* Gera erro semântico para variável já existente */
void errorSemanticoVariavelExistente(char *name, int numline) {

    Erro *novoErro = (Erro *)malloc(sizeof(Erro));
    if (!novoErro) {
        printf("Erro de alocação de memória!\n");
    }


    snprintf(novoErro->mensagem, sizeof(novoErro->mensagem), 
             "ERRO SEMÂNTICO: %s LINHA: %d, ID já declarado.\n", name, numline);

    novoErro->prox = listaErros;  // Adicionar ao início da lista
    listaErros = novoErro;
}

/* Gera erro semântico para variável não declarada */
void errorSemanticoVariavelNaoDeclarada(char *name, int numline) {
    Erro *novoErro = (Erro *)malloc(sizeof(Erro));
    if (!novoErro) {
        printf("Erro de alocação de memória!\n");
        return;
    }

    snprintf(novoErro->mensagem, sizeof(novoErro->mensagem), 
             "ERRO SEMÂNTICO: %s LINHA: %d, ID não declarado antes do uso.\n", name, numline);

    novoErro->prox = listaErros;
    listaErros = novoErro;
}
/* Função para imprimir erros da lista encadeada*/
void imprimirErros() {
    Erro *atual = listaErros;
    while (atual) {
        printf("%s", atual->mensagem);
        atual = atual->prox;
    }
}

/* Procura variável por nome e escopo na tabela*/
int st_lookup ( char * name, char *escopo )
{ int h = hash(name);
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
	  for (i=0;i<SIZE;++i)
	  { if (hashTable[i] != NULL)
	    { BucketList l = hashTable[i];
	      while (l != NULL)
	      { LineList t = l->lines;
	      	fprintf(save_symTable, "%-8d  ",l->memloc);
		fprintf(save_symTable, "%-14s ",l->name);
		fprintf(save_symTable, "%-6s  ",l->escopo);
		fprintf(save_symTable, "%-8s  ",l->tipoID);
		fprintf(save_symTable, "%-9d  ",l->tipoDado);
		while (t != NULL)
		{ fprintf(save_symTable, "%4d ",t->numline);
		  t = t->next;
		}
		fprintf(save_symTable, "\n");
		l = l->next;
	      }
	    }
  }
}
/* Função para imprimir erros*/
void typeError(TreeNode * t, char * message)
{ printf("ERRO SEMÂNTICO NA LINHA %d: %s\n",t->numline,message);
}

/* Função para verificar o tipo de nó da árvore sintática*/
void checkNode(TreeNode * t) { 
  if (t == NULL) return;

  switch (t->nodekind) { 
      case ExpK:
          switch (t->kind.exp) { 
            case IdK:
            t->type = Integer;
            break;

            case OpK:
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
                      // Verifica se o tipo da variável é void
                      if (t->type == Void) {
                          typeError(t, "Variável não pode ser do tipo void");
                      }
          
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
                    if (t->child[1]->attr.name != NULL &&
                        strcmp(t->child[1]->attr.name, "output") != 0 &&  
                        strcmp(t->child[1]->attr.name, "input") != 0) {
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
      if (l->name != NULL && l->escopo != NULL && 
          strcmp(name, l->name) == 0 && strcmp(escopo, l->escopo) == 0) {
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
