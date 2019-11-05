%{
#include <stdio.h>
#include <stdbool.h>

int yylex();
int yyerror(char *s);

%}

%token STRING INT OTHER SEMICOLON AOP ABOP BOP UOP ROP BREAK 
%token CONTINUE RETURN INPUT BOPEN BCLOSE STOP
%token OUTPUT CBOPEN CBCLOSE DTYPE QMARK BOOL FLOAT
%token COLON EQUAL COMMA IF ELSE  ENDIF WHILE FOR SBOPEN SBCLOSE
%type <name> STRING
%type <number> INT
%type <fnumber> FLOAT
%type <bvalue> BOOL
%type <boperator> BOP 
%type <uoperator> UOP 
%type <aoperator> AOP
%type <aboperator> ABOP

%left <roperator> ROP
%left AOP
%left ABOP
%right U
%right QMARK
%right UOP
%right BOP

%union{
	  char name[20];
    int number;
    float fnumber;
    int bvalue;
    char boperator[3];
    char uoperator[3];
    char roperator[3];
    char aoperator[3];
    char aboperator[3];
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
    |stmt

;

stmt:
    function_decl
    |variable_decl
    |assignStmt
    |functionCall SEMICOLON
    |ifStmt
    |whileStmt
    |forStmt
    |BREAK SEMICOLON
    |CONTINUE SEMICOLON
    |RETURN SEMICOLON
    |RETURN expr SEMICOLON
    |INPUT BOPEN variable BCLOSE SEMICOLON
    |OUTPUT BOPEN variable BCLOSE SEMICOLON
    |SEMICOLON
;

block:
    CBOPEN stmts CBCLOSE
;

function_decl:
    DTYPE STRING BOPEN paramD_list BCLOSE block
;
variable_decl:
    DTYPE variable SEMICOLON
;

expr: 
    UOP expr %prec UOP
    |expr BOP expr %prec BOP
    |expr QMARK expr COLON expr %prec QMARK
    |expr ROP expr
    |expr AOP expr
    |expr ABOP expr
    |BOPEN expr BCLOSE
    |AOP expr %prec U
    |param
    |functionCall
;

assignStmt: 
    variable EQUAL expr SEMICOLON
    |DTYPE variable EQUAL expr SEMICOLON
;

functionCall:
    STRING BOPEN BCLOSE
    |STRING BOPEN param_list BCLOSE
;

ifStmt:
    IF BOPEN expr BCLOSE block ENDIF
    |IF BOPEN expr BCLOSE block ELSE block ENDIF
;

whileStmt:
    WHILE BOPEN expr BCLOSE block
;

forStmt:
    FOR BOPEN assignStmt expr SEMICOLON assignStmt BCLOSE block
;

variable:
    STRING SBOPEN INT SBCLOSE SBOPEN INT SBCLOSE
    |STRING SBOPEN INT SBCLOSE SBOPEN STRING SBCLOSE
    |STRING SBOPEN STRING SBCLOSE SBOPEN INT SBCLOSE
    |STRING SBOPEN STRING SBCLOSE SBOPEN STRING SBCLOSE 
    |STRING SBOPEN INT SBCLOSE 
    |STRING SBOPEN STRING SBCLOSE 
    |STRING
;

param_list:
    param COMMA param_list  
    |param
;

param:
    variable
    |INT
    |BOOL
    |FLOAT
;

paramD_list:
    paramD COMMA paramD_list  
    |paramD
;


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