EXEC = acc

LEX = lexico.l
YACC = parser.y
UTIL = util.c
SYMTAB = symtab.c
SEMANTICO = semantico.c
GERADORDEQUADRUPLA = geradordequadrupla.c

LEX_C = lex.yy.c
YACC_C = parser.tab.c
YACC_H = parser.tab.h

LEX_O = lex.yy.o
UTIL_O = util.o
SYMTAB_O = symtab.o
SEMANTICO_O = semantico.o
GERADORDEQUADRUPLA_O = geradordequadrupla.o

all: $(EXEC)

$(YACC_C) $(YACC_H): $(YACC)
	bison -d $(YACC)

$(LEX_C): $(LEX)
	flex $(LEX)

$(LEX_O): $(LEX_C) $(YACC_H)
	gcc -c $(LEX_C)

$(UTIL_O): $(UTIL)
	gcc -c $(UTIL)

$(SYMTAB_O): $(SYMTAB)
	gcc -c $(SYMTAB)

$(SEMANTICO_O): $(SEMANTICO)
	gcc -c $(SEMANTICO)
	
$(GERADORDEQUADRUPLA_O): $(GERADORDEQUADRUPLA)
	gcc -c $(GERADORDEQUADRUPLA)

$(EXEC): $(LEX_O) $(UTIL_O) $(SYMTAB_O) $(SEMANTICO_O) $(GERADORDEQUADRUPLA_O) $(YACC_C)
	g++ -o $(EXEC) $(YACC_C) $(UTIL) $(LEX_O) $(SYMTAB) $(SEMANTICO) $(GERADORDEQUADRUPLA) -lfl

run: $(EXEC)
	./$(EXEC)

clean:
	rm -f $(LEX_C) $(YACC_C) $(YACC_H) $(LEX_O) $(UTIL_O) $(SYMTAB_O) $(SEMANTICO_O) $(GERADORDEQUADRUPLA_O) $(EXEC)
