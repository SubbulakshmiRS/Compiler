%{
#include <stdio.h>
#include <stdbool.h>

int yylex();
int yyerror(char *s);

%}

%token STRING INT OTHER SEMICOLON BOP UOP ROP BREAK 
%token CONTINUE RETURN INPUT BOPEN BCLOSE STOP
%token OUTPUT CBOPEN CBCLOSE DTYPE QMARK BOOL FLOAT
%token COLON EQUAL COMMA IF ELSE WHILE FOR SBOPEN SBCLOSE
%type <name> STRING
%type <number> INT
%type <fnumber> FLOAT
%type <bvalue> BOOL
%type <boperator> BOP 
%type <uoperator> UOP 
%type <roperator> ROP



%union{
	  char name[20];
    int number;
    float fnumber;
    int bvalue;
    char boperator[3];
    char uoperator[3];
    char roperator[3];
    char dtype[20];
}

%%

prog:
  stmts STOP{
      printf("\nSuccessful parsing\n");
  }
;

stmts:
    stmt stmts
    |   stmt

;

stmt:
    function_decl
    |   variable_decl
    |   assignStmt
    |   functionCall 
    |   ifStmt
    |   whileStmt
    |   forStmt
    |   BREAK SEMICOLON
    |   CONTINUE SEMICOLON
    |   RETURN SEMICOLON
    |   RETURN expr SEMICOLON
    |   INPUT BOPEN STRING BCLOSE SEMICOLON
    |   OUTPUT BOPEN STRING BCLOSE SEMICOLON
    |   SEMICOLON
;

block:
    CBOPEN stmts CBCLOSE
;

function_decl:
    DTYPE STRING BOPEN paramD_list BCLOSE block
;
variable_decl:
    DTYPE STRING SEMICOLON
;

expr:  
    BOPEN expr BCLOSE
    |   expr BOP expr
    |   UOP expr
    |   expr QMARK expr COLON expr
    |   expr ROP expr
    |   functionCall
    |   STRING
    |   INT
    |   BOOL
    |   FLOAT
;

assignStmt: 
    STRING EQUAL expr SEMICOLON
    | DTYPE STRING EQUAL expr SEMICOLON
;

functionCall:
    STRING BOPEN param_list BCLOSE SEMICOLON
    |   STRING EQUAL STRING BOPEN param_list BCLOSE SEMICOLON
    |   RETURN STRING BOPEN param_list BCLOSE SEMICOLON
;

ifStmt:
    IF BOPEN expr BCLOSE block
    |   IF BOPEN expr BCLOSE block ELSE block
;

whileStmt:
    WHILE BOPEN expr BCLOSE block
;

forStmt:
    FOR BOPEN assignStmt expr SEMICOLON assignStmt BCLOSE block
;

param_list:
    param COMMA param_list  
    |   param
;

param:
    STRING
    |   INT
    |   BOOL
    |   FLOAT
;

paramD_list:
    paramD COMMA paramD_list  
    |   paramD
;
$

paramD:
    DTYPE param 
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