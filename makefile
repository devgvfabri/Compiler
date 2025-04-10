EXEC = acc

LEX = lexico.l
YACC = parser.y
UTIL = util.c

LEX_C = lex.yy.c
YACC_C = parser.tab.c
YACC_H = parser.tab.h
LEX_O = lex.yy.o
UTIL_O = util.o

all: $(EXEC)

$(YACC_C) $(YACC_H): $(YACC)
	bison -d $(YACC)

$(LEX_C): $(LEX)
	flex $(LEX)

$(LEX_O): $(LEX_C) $(YACC_H)
	gcc -c $(LEX_C)

$(UTIL_O): $(UTIL)
	gcc -c $(UTIL)

$(EXEC): $(LEX_O) $(UTIL_O) $(YACC_C)
	g++ -o $(EXEC) $(UTIL) $(LEX_O) $(YACC_C) -lfl

run: $(EXEC)
	./$(EXEC)

clean:
	rm -f $(LEX_C) $(YACC_C) $(YACC_H) $(LEX_O) $(UTIL_O) $(EXEC)
