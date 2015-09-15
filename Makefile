all: compiler

parser.tab.c parser.tab.h:	parser.y
	bison -d parser.y

lex.yy.c: lexical_analyser.l parser.tab.h
	flex lexical_analyser.l

compiler: lex.yy.c parser.tab.c parser.tab.h
	gcc -o compiler parser.tab.c lex.yy.c -lfl

clean:
	rm compiler parser.tab.c lex.yy.c parser.tab.h
