CC = gcc
CFLAGS = -Wall -Wextra -g -I.

all: compiler

compiler: lex.yy.c parser.tab.c semantic/symboltable.c codegen/codegen.c controller/compiler_controller.c main.c
	$(CC) $(CFLAGS) -o compiler lex.yy.c parser.tab.c semantic/symboltable.c codegen/codegen.c controller/compiler_controller.c main.c

parser.tab.c: parser/parser.y
	bison -d parser/parser.y -o parser.tab.c

lex.yy.c: lexer/lexer.l parser.tab.c
	flex -o lex.yy.c lexer/lexer.l

clean:
	rm -f compiler.exe compiler lex.yy.c parser.tab.c parser.tab.h output.c
