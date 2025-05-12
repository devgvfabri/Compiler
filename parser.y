%{
#define YYPARSER

#include <stdio.h>
#include "util.h"
#include "global.h"
#include "symtab.h"
#include "semantico.h"
#include "geradordequadrupla.h"
void yyerror(char *);
#define YYDEBUG 1    //Para exibir na tela os passos da análise sintática quando o parser é executado
extern "C"
{
  int yylex(void);
  void abrirArq();

}
#define YYSTYPE TreeNode *
int numline = 1;
static char * savedNameFun;
static char * savedNameVar;
static char * savedNameAtiv;
static int savedLineNo;
static TreeNode* savedTree;
static int location = 0;
static char *currentFunctionName = "global";
ErroSintatico *listaErrosSintaticos = NULL;  // Ponteiro global para a lista de erros

%}

%start programa
%token NUM ID ELSE WHILE IF RETURN VOID INT SOM SUB MUL DIV MAI MEN MIG MEI IGU DIF ATR PEV VIR APA FPA ACO FCO ACH FCH ERRO FIM  FIMLIN ERROR OUTRO

//Para mostrar o valor semântico to token quando for debugar o parser
%printer { fprintf (yyoutput, "’%d’", $$); } NUM

%%
// programa aceito pela gramática
programa : declaracoes   { printf("Programa finalizado com sucesso\n"); 
				savedTree = $1;
				YYACCEPT; }
        ;
// lista de declarações
declaracoes : declaracaoLista  { $$ = $1; }
           ;
// Cria nós irmãos para cada declaração de função/ variavel
declaracaoLista	:	declaracaoLista declaracao 
			{	
			    TreeNode * t = $1;
			    if (t != NULL) {
				while (t->sibling != NULL) t = t->sibling;
				t->sibling = $2;
				$$ = $1;
			    } else {
				$$ = $2;
			    }
			}
			| declaracao { $$ = $1; }
			
		;
declaracao	:	varDeclaracao { $$ = $1;}
			| funDeclaracao { $$ = $1;}
		;
// Declaração de variável cria nó com tipo, id, escopo, e insere na tabela de símbolos
varDeclaracao	:	tipoEspecificador ID PEV 
			{ 
					$$ = newExpNode(TypeK);
               				$$->type = $1->type;
					TreeNode *id = newExpNode(IdK);
					id->attr.name = copyString(tokenString);
                			$$->attr.name = id->attr.name;
                			$$->child[0] = id;
                			id->nodekind = StmtK;
                			id->kind.stmt = VarK;
                			id->type = $1->type;
					id->escopo = copyString(currentFunctionName);
                			st_insert(location++, id->attr.name, currentFunctionName , "var",$1->type, numline, 1);
    			}
			| tipoEspecificador ID 
			// Declaração de variável vetor cria nó com tipo, id, escopo, e insere na tabela de símbolos, salva id em uma variavel global para gerar a arvore e a tabela
			{
			savedNameVar = copyString(tokenString);
			}
    			ACO NUM FCO PEV 
			{ 
				$$ = newExpNode(TypeK);
                $$->type = $1->type;
				TreeNode *id = newExpNode(IdK);
				id->attr.name = copyString(savedNameVar);
				$$->attr.name = $1->attr.name;
				$$->child[0] = id;
				id->nodekind = ExpK;
				id->kind.exp = VetK;
				id->type = $1->type;
				id->child[0] = newExpNode(ConstK);
				id->child[0]->attr.val = atoi(tokenString);
				id->child[0]->type = Integer;
				id->child[0]->numline = numline;
				id->attr.vetor = 1;
				id->escopo = copyString(currentFunctionName);
				st_insert(location++, id->attr.name, currentFunctionName, "var", $1->type, numline, 1);
    			}
				| tipoEspecificador error PEV
			{
				yyerrok;
				$$ = NULL;
			}
			;

			// Declaração de função vetor cria nó com tipo, id, escopo, e insere na tabela de símbolos, salva id em uma variavel global para gerar a arvore e a tabela

funDeclaracao	: 	tipoEspecificador ID 
			{
				savedNameFun = copyString(tokenString);
				savedLineNo = numline;
				currentFunctionName = savedNameFun;
				setCurrentFunction(copyString(tokenString));
			}
			APA params FPA compostoDecl 
			{ 
				$$ = newExpNode(TypeK);
                		$$->type = $1->type;
				TreeNode *id = newExpNode(IdK);
				id->attr.name = copyString(savedNameFun);
				$$->attr.name = id->attr.name;
				$$->child[0] = id;
				id->child[0] = $5;
				id->child[1] = $7;
				id->nodekind = StmtK;
				id->kind.stmt = FunK;
				id->type = $1->type;
				id->escopo = copyString("global");
				st_insert(location++, id->attr.name, "global","funcao", $1->type, savedLineNo, 1);
				currentFunctionName = "global";
			}
			| tipoEspecificador error APA
			{
				yyerrok;
				$$ = NULL;
			}
		;
// Envia lista de parametros para função
params		: 	paramLista {$$ = $1;
				}

			| VOID
			{	
				$$ = newExpNode(TypeK);
				$$->type = Void;
				$$->child[0] = NULL;
			}
		;
// Cria uma lista de parametros com nós irmãos
paramLista	: 	paramLista VIR param
			{	
			    TreeNode * t = $1;
			    if (t != NULL) {
				while (t->sibling != NULL) t = t->sibling;
				t->sibling = $3;
				$$ = $1;
			    } else {
				$$ = $3;
			    }
			}
 			| param {$$ = $1;}
			| paramLista error param
			{
				yyerrok;
				$$ = NULL;
			}
		;
// Cria nó com tipo especificador para funções e variáveis
tipoEspecificador: 	INT 
			{	
				$$ = newExpNode(TypeK);
				$$->type = Integer;
			}
			| VOID
			{	
				$$ = newExpNode(TypeK);
				$$->type = Void;
			}
		;
// Cria nó com parametro de função
param		: 	tipoEspecificador ID 
			{ 
				TreeNode *paramNode = newStmtNode(ParamK);
				paramNode->attr.name = copyString(tokenString); // Nome do parâmetro
				$$->child[0] = paramNode;
				paramNode->type = $1->type; // Tipo do parâmetro
				paramNode->escopo = copyString(currentFunctionName); // Escopo do parâmetro
				st_insert(location++, paramNode->attr.name, currentFunctionName, "param", $1->type, numline, 1);
				$$ = $1;
    			}
			| tipoEspecificador ID 
			{
				savedNameVar = copyString(tokenString);
			}ACO FCO
			{ 
				TreeNode *paramNode = newStmtNode(ParamK);
				paramNode->attr.name = copyString(savedNameVar); // Nome do parâmetro
				$$->child[0] = paramNode;
				paramNode->type = IntegerVetorK; // Tipo do parâmetro (vetor)
				paramNode->escopo = copyString(currentFunctionName); // Escopo do parâmetro
				st_insert(location++, paramNode->attr.name, currentFunctionName, "param", IntegerVetorK, numline, 1);
				$$ = $1;
    			}
    			| tipoEspecificador error VIR
    			{
    				yyerrok;
    				$$ = NULL;
    			}
		;
// Cria os nós com declarações da função
compostoDecl	: 	ACH localDeclaracoes statementLista FCH 
			{
				TreeNode* t = $2;
				if(t != NULL){
				  while(t->sibling != NULL)
				  t = t->sibling;
				  t->sibling = $3;
				  $$ = $2;
				} 
				else $$ = $3;
             		 }
		;
// Cria declarações locais
localDeclaracoes: 	/*Vazio*/ { $$ = NULL; }
			| localDeclaracoes varDeclaracao 
			{
				TreeNode *t = $1;
				if (t != NULL) {
				    while (t->sibling != NULL) t = t->sibling;
				    t->sibling = $2;
				    $$ = $1;
				} else {
				    $$ = $2;
				}
			 }
		;
// Cria lista de declaracao
statementLista	: 	/*Vazio*/ { $$ = NULL; }
			| statementLista statement 
			{
				TreeNode *t = $1;
				if (t != NULL) {
				    while (t->sibling != NULL) t = t->sibling;
				    t->sibling = $2;
				    $$ = $1;
				} else {
				    $$ = $2;
				}
			    }
		;
// Reduz para tipos de declarações
statement	: 	expressaoDecl  {$$ = $1;}
			| compostoDecl {$$ = $1;}
			| selecaoDecl  {$$ = $1;}
			| iteracaoDecl {$$ = $1;}
			| retornoDecl  {$$ = $1;}
			| error PEV
			{
				yyerrok;
				$$ = NULL;
			}
		;
// Expressao simples
expressaoDecl	: 	expressao PEV {$$ = $1;}
			| PEV 

		;
// Declaração de IFS
selecaoDecl	: 	IF  APA expressao FPA statement 
			{  $$ = newStmtNode(IfK);
	                   $$->child[0] = $3;
	                   $$->child[1] = $5;
	                 }
			| IF APA expressao FPA statement ELSE statement 
			{  $$ = newStmtNode(IfK);
	                   $$->child[0] = $3;
	                   $$->child[1] = $5;
	                   $$->child[2] = $7;
	                 }
		;
// Iterações com While
iteracaoDecl	: 	WHILE APA expressao FPA statement 
			{  $$ = newStmtNode(WhileK);
	                   $$->child[0] = $3;
	                   $$->child[1] = $5;
	                 }
		;
// Nós com retornos de chamadas de funções/vazio
retornoDecl	: 	RETURN PEV 
			{
				$$ = newStmtNode(returnK);
				$$->escopo = currentFunctionName;
				$$->type = Void;
			}
			| RETURN expressao PEV 
			{  
				$$ = newStmtNode(returnK);
	                   	$$->child[0] = $2;
				$$->type = Integer;
				$$->child[0]->type = Integer;
				$$->escopo = currentFunctionName;
	                }
		;
// Cria nós com expressões
expressao	: 	var ATR expressao 
			{ 
				$$ = newStmtNode(AtrK);
				$$->attr.name = $1->attr.name;
				$$->attr.op = ATR;
				$$->child[0] = $1;
				$$->child[1] = $3;
			}
			| simplesExpressao {$$ = $1;}
			
		;
// Cria nós de variaveis já declaradas
var 		: 	ID 
			{
				$$ = newExpNode(IdK);
				$$->attr.name = copyString(tokenString);
				$$->type = Integer;
				st_insert(location++, tokenString, currentFunctionName, "var", NULL, numline, 0);
			}
			| ID {	savedNameVar = copyString(tokenString); }
			ACO expressao FCO 
			{
				$$ = newExpNode(IdK);
				$$->attr.name = copyString(savedNameVar);
				$$->child[0] = $4;
				$$->kind.exp = VetK;
				$$->type = Integer;
				st_insert(location++, savedNameVar, currentFunctionName, "var", NULL, numline, 0);
			}
		;

simplesExpressao: 	somaExpressao relacional somaExpressao 
			{
				$$ = $2;
				$$->child[0] = $1;
				$$->child[1] = $3;
			}
			| somaExpressao {$$ = $1;}
		;
// Operadores válidos para linguagem
relacional	: 	MEI 
			{ 
				$$ = newExpNode(OpK);
				$$->attr.op = MEI;
			}
			| MEN 
			{ 
				$$ = newExpNode(OpK);
				$$->attr.op = MEN;
			}
			| MAI 
			{ 
				$$ = newExpNode(OpK);
				$$->attr.op = MAI;
			}
			| MIG
			{ 
				$$ = newExpNode(OpK);
				$$->attr.op = MIG;
			} 
			| IGU
			{ 
				$$ = newExpNode(OpK);
				$$->attr.op = IGU;
			} 
			| DIF
			{ 
				$$ = newExpNode(OpK);
				$$->attr.op = DIF;
			}
		;
// Expressoa com soma, cria um nó pai de soma e dois filhos
somaExpressao	: 	somaExpressao soma termo
			{
				$$ = $2;
				$$->child[0] = $1;
				$$->child[1] = $3;
			} 
			| termo {$$ = $1;}
		;
soma		: 	SOM
			{ 
				$$ = newExpNode(OpK);
				$$->attr.op = SOM;
			} 
			| SUB
			{ 
				$$ = newExpNode(OpK);
				$$->attr.op = SUB;
			}
		;
// Expressoa com multiplicação, cria um nó pai de soma e dois filhos
termo		: 	termo mult fator 
			{
				$$ = $2;
				$$->child[0] = $1;
				$$->child[1] = $3;	
			}

			| fator {$$ = $1;}
		;

mult		: 	MUL 
			{ 
				$$ = newExpNode(OpK);
				$$->attr.op = MUL;
			}
			| DIV
			{ 
				$$ = newExpNode(OpK);
				$$->attr.op = DIV;
			}
		;
// fator pode ser reduzido a expressao, variavel, numero, ou ativação de função 
fator		: 	APA expressao FPA {$$ = $2;} 
			| var  {$$ = $1;}
			| ativacao {$$ = $1;}
			| NUM 
			{
				$$ = newExpNode(ConstK);
				$$->attr.val = atoi(tokenString);
  			}
		;
// ativação de função
ativacao	: 	idAtiv APA args FPA 
			{
				$$ = $1;
				$$->child[0] = $3;
				$$->nodekind = StmtK;
				$$->kind.stmt = CallK;
				$$->numline = numline;
				$$->attr.name = $1->attr.name;
			}
		;
idAtiv		: 	ID
			{
				$$ = newExpNode(IdK);
				$$->attr.name = copyString(tokenString);
				$$->numline = numline;
				if(strcmp("output", tokenString) != 0 && strcmp("input", tokenString) && strcmp("main", tokenString) )
				st_insert(location++, tokenString, currentFunctionName, "funcao", NULL, numline, 0);
			}
		;	
args		: 	/*Vazio*/ { $$ = NULL; }
			| argLista {$$ = $1;}
		;

argLista	: 	argLista VIR expressao 
			{	
			    TreeNode * t = $1;
			    if (t != NULL) {
				while (t->sibling != NULL) t = t->sibling;
				t->sibling = $3;
				$$ = $1;
			    } else {
				$$ = $3;
			    }
			}
			| expressao {$$ = $1;}
		;


%%


void imprimirErrosSintaticos() 
{
	ErroSintatico *atual = listaErrosSintaticos;
	while (atual) 
	{
		printf("%s", atual->mensagem);
		atual = atual->prox;
	}
}

int main()
{
  extern int yydebug;
  yydebug = 1;
  printf("\nParser em execução...\n");
  abrirArq();
  
  yyparse(); 
  if (savedTree != NULL) {
      printTreeArq(savedTree);  
  } else {
      printf("\nErro ao construir a árvore sintática.\n");
  }
  imprimirErros();
  imprimirErrosSintaticos();
  imprimirErrosLexicos();
  semanticCheck(savedTree);
  printSymTab();
  generateCode(savedTree);
  return 0;
}

void yyerror(char * msg)
{
  extern char* yytext;
  extern int yychar;
    ErroSintatico *novoErroSintatico = (ErroSintatico *)malloc(sizeof(ErroSintatico));
	snprintf(novoErroSintatico->mensagem, sizeof(novoErroSintatico->mensagem), 
             "ERRO SINTÁTICO: %s LINHA: %d\n", yytext, numline);

    novoErroSintatico->prox = listaErrosSintaticos;  // Adicionar ao início da lista
    listaErrosSintaticos = novoErroSintatico;
  printf("\n\n\n\tERRO SINTÁTICO: %s, Token: ", msg);
  printToken(yychar, yytext);
  printf(" LINHA: %d\n\n\n", numline);

  
}

