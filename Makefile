TARGET=P2
OBJS= \
main.o \
Env.o \
SymbolTable.o \
Node.o \
lex.yy.o \
y.tab.o 	
	
REBUILDABLES=$(OBJS)$(TARGET)

CC= gcc
CCFLAGS=-o
LEX = lex
YACC = yacc
CFLAG = -c
YFLAGS = -d
DEGUGFLAGS= -Wall -g -o

$(TARGET): $(OBJS)
	$(CC) $(CCFLAGS) $@ $^


main.o: main.c y.tab.c
	$(CC) $(CFLAG) $^

SymbolTable.o: SymbolTable.c
	$(CC) $(CFLAG) $^

Env.o: Env.c
	$(CC) $(CFLAG) $^

Node.o: Node.c
	$(CC) $(CFLAG) $^

lex.yy.o: lex.yy.c y.tab.c
	$(CC) $(CFLAG) $^

y.tab.o: y.tab.c
	$(CC) $(CFLAG) $^

lex.yy.c: cscan.l 
	$(LEX) $^

y.tab.c: cparse.y
	$(YACC) $(YFLAGS) $^

debug: $(OBJS)
	$(CC) $(DEBUGFLAGS) $@ $^

clean: 
	rm -f $(REBUILDABLES) lex.yy.c y.tab.? Input.txt output.ast
