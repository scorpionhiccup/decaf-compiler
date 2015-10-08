CC=g++
CFLAGS=-Wall -ansi -g -std=c++11

all: syntax_analyser

parser.tab.c parser.tab.h:	parser.y
	bison -d -Wconflicts-sr -Wconflicts-rr --verbose parser.y

lex.yy.c: lexical_analyser.l parser.tab.h
	flex -d lexical_analyser.l

syntax_analyser: lex.yy.c parser.tab.c parser.tab.h
	$(CC) $(CFLAGS) -o syntax_analyser parser.tab.c lex.yy.c -lfl

clean:
	rm -f syntax_analyser parser.tab.c lex.yy.cc parser.tab.h parser.output
