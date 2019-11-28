all: test

test.tab.c test.tab.h:	test.y AST.cpp AST.h
	bison -vd test.y

lex.yy.c: test.l test.tab.h AST.cpp AST.h
	flex test.l

AST.o: AST.cpp AST.h traverse.cpp traverse.h codegen.h codegen.cpp
	g++ -g -std=c++14 -c AST.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core`

test: lex.yy.c test.tab.c test.tab.h AST.o
	g++ -g -std=c++14 -o test test.tab.c lex.yy.c AST.o -lfl `llvm-config --cxxflags --ldflags --system-libs --libs core`

clean:
	rm test test.tab.c lex.yy.c test.tab.h AST.o 
