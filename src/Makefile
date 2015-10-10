CC=g++
CFLAGS=-Wall -g -std=c++11

all: clean syntax_analyser

parser.tab.c parser.tab.h:	parser.y
	bison -d -Wconflicts-sr -Wconflicts-rr --verbose parser.y

lex.yy.c: lexical_analyser.l parser.tab.h
	flex -d lexical_analyser.l

syntax_analyser: lex.yy.c parser.tab.c parser.tab.h
	$(CC) $(CFLAGS) -o syntax_analyser parser.tab.c lex.yy.c AST.cpp Visitor.cpp -lfl

clean:
	rm -f AST.h.gch syntax_analyser parser.tab.c lex.yy.c parser.tab.h parser.output

clean_all:
	rm -f AST.h.gch syntax_analyser parser.tab.c lex.yy.c parser.tab.h parser.output XML_visitor.txt flex_output.txt bison_output.txt