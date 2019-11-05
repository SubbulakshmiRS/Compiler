all: test

test.tab.c test.tab.h:	test.y
	bison -v test.y

lex.yy.c: test.l test.tab.h
	flex test.l

test: lex.yy.c test.tab.c test.tab.h
	gcc -o test test.tab.c lex.yy.c -lfl

clean:
	rm test test.tab.c lex.yy.c test.tab.h
