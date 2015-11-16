CC=g++
CFLAGS=-g -std=c++11
#CFLAGS=-Wall  -g

all: clean syntax_analyser

parser.tab.c parser.tab.h:	parser.y
	bison -d -v -Wother -Wconflicts-sr -Wconflicts-rr --verbose parser.y

lex.yy.c: lexical_analyser.l parser.tab.h
	flex -d lexical_analyser.l

syntax_analyser: lex.yy.c parser.tab.c parser.tab.h AST.cpp Visitor.cpp 
	$(CC) $(CFLAGS) -o syntax_analyser  parser.tab.c AST.cpp Visitor.cpp lex.yy.c `llvm-config --libs core vectorize jit native --cxxflags` `llvm-config --ldflags` -lfl  -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS -DCURSES_LIBRARY=/usr/lib/x86_64-linux-gnu/libncurses.so 

clean:
	rm -f AST.h.gch syntax_analyser parser.tab.c lex.yy.c parser.tab.h parser.output

clean_all:
	rm -f AST.h.gch syntax_analyser parser.tab.c lex.yy.c parser.tab.h parser.output XML_visitor.txt flex_output.txt bison_output.txt
