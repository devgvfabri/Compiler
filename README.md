Projeto apresentado à Universidade Federal
de São Paulo como parte dos requisitos para
aprovação na disciplina de Laboratório de
Sistemas Computacionais: Compiladores.



# Compilador-C-minus
Compilador C minus
Comandos:
bison -d parser.y
flex lexico.l
gcc -c lex.yy.c
gcc -c util.c
g++ -o acc util.c lex.yy.o parser.tab.c -lfl
./acc
