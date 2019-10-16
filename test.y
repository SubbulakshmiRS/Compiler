%{
#include <stdio.h>
#include <stdbool.h>

int yylex();
int yyerror(char *s);

%}

%token STRING NUM OTHER SEMICOLON OP ROP COP BREAK 
%token CONTINUE RETURN INPUT BOPEN BCLOSE
%token OUTPUT CBOPEN CBCLOSE DTYPE QMARK
%token COLON EQUAL COMMA IF ELSE WHILE FOR SBOPEN SBCLOSE
%type <name> STRING
%type <number> NUM
%type <operator> OP 

%union{
	  char name[20];
    int number;
    char operator;
    char dtype[20];
}

%%

prog:
  stmts{
      printf("\nSuccessful parsing1\n");
  }
;

stmts:
    stmt stmts{
        printf("\nSuccessful parsing2\n");
    }
    |   stmt{
        printf("\nSuccessful parsing3\n");
    }

;

stmt:
    function_decl
    |   variable_decl
    |   assignStmt
    |   functionCall 
    |   ifStmt{
        printf("if statement\n");
    }
    |   whileStmt
    |   forStmt{
        printf("for statement\n");
    }
    |   BREAK SEMICOLON
    |   CONTINUE SEMICOLON
    |   RETURN SEMICOLON
    |   RETURN expr SEMICOLON
    |   INPUT BOPEN STRING BCLOSE SEMICOLON
    |   OUTPUT BOPEN STRING BCLOSE SEMICOLON
    |   SEMICOLON
;

block:
    CBOPEN stmts CBCLOSE{
        printf("block\n");
    }
;

function_decl:
    DTYPE STRING BOPEN param_list BCLOSE block SEMICOLON
;
variable_decl:
    DTYPE STRING SEMICOLON
;

expr:  
    BOPEN expr BCLOSE
    |   expr COP expr
    |   expr OP expr
    |   expr ROP expr
    |   expr QMARK expr COLON expr
    |   functionCall
    |   STRING
    |   NUM{
        printf("num\n");
    }
;

assignStmt: 
    STRING EQUAL expr SEMICOLON{
        printf("assign here");
    }
    | DTYPE STRING EQUAL expr SEMICOLON
;

functionCall:
    STRING BOPEN param_list BCLOSE SEMICOLON
    |   STRING EQUAL STRING BOPEN param_list BCLOSE SEMICOLON
    |   RETURN STRING BOPEN param_list BCLOSE SEMICOLON
;

ifStmt:
    IF BOPEN expr BCLOSE block{
        printf("no else\n");
    } 
    |   IF BOPEN expr BCLOSE block ELSE block
;

whileStmt:
    WHILE BOPEN expr BCLOSE block
;

forStmt:
    FOR BOPEN assignStmt expr SEMICOLON assignStmt BCLOSE block
    {
        printf("here\n");
    }
;

param_list:
    param COMMA param_list  
    |   param
;

param:
    DTYPE STRING 
;

%%

int yyerror(char *s)
{
	printf("Syntax Error on line %s\n", s);
	return 0;
}

int main()
{
    yyparse();
    return 0;
}