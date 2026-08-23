/*
Gabriel Fabri do Carmo - 163756
*/

%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"
#include <ctype.h>
#include <string.h>
#include "global.h"



extern YYSTYPE yylval;
void abrirArq();
void erroLexico();
void contLine();

extern int numline;
char tokenString[256];
ErroLexico *listaErrosLexicos = NULL;  // Ponteiro global para a lista de erros


%}

NUMERO [0-9]
LETRA [a-zA-Z]
OUTRO [^a-zA-Z0-9\+\-\*\/=<>!\()\{\}\[\];,\n\t ]

%%
"/*"([^*]|(\*+[^*/]))*"*/"	      {contLine();}	               
int                                   {return INT;}
else                                  {return ELSE;}
while                                 {return WHILE;}
if                                    {return IF;}
return                                {return RETURN;}
void                                  {return VOID;}
"+"                                   {return SOM;}
"-"                                   {return SUB;}
"*"                                   {return MUL;}
"/"                                   {return DIV;}
">"                                   {return MAI;}
"<"                                   {return MEN;}
">="                                  {return MIG;}
"<="                                  {return MEI;}
"=="                                  {return IGU;}
"!="                                  {return DIF;}
"="                                   {return ATR;}
";"                                   {return PEV;}
","                                   {return VIR;}
"("                                   {return APA;}
")"                                   {return FPA;}
"["                                   {return ACO;}
"]"                                   {return FCO;}
"{"                                   {return ACH;}
"}"                                   {return FCH;}
{LETRA}+                              {strcpy(tokenString, yytext); return ID;}
{NUMERO}+                             {strcpy(tokenString, yytext);return NUM;}
\n				                      numline++;
\t
{OUTRO}+                              {erroLexico(); return(OUTRO);};
<<EOF>>                               return FIM;					
%%


/* Função para imprimir erros */
void erroLexico()
{
    ErroLexico *novoErroLexico = (ErroLexico *)malloc(sizeof(ErroLexico));
	snprintf(novoErroLexico->mensagem, sizeof(novoErroLexico->mensagem), 
             "ERRO LÉXICO: %s LINHA: %d\n", yytext, numline);

    novoErroLexico->prox = listaErrosLexicos;  // Adicionar ao início da lista
    listaErrosLexicos = novoErroLexico;
	printf("ERRO LÉXICO: %s LINHA: %d\n", yytext, numline);

}



/* Função para contar linhas em um comentário */
void contLine() {
    char *p = yytext;
    while (*p) {
        if (*p == '\n') {
            numline++;
        }
        p++;
    }
}
/* Função para abrir arquivo */
void abrirArq()
{
  yyin = fopen("code.txt", "r");
}
