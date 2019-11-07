%{
#include <stdio.h>
#include <stdbool.h>

#include "AST.h"

int yylex (void);
int yyerror (char *s);

FILE * flex_output;
FILE * bison_output;

extern union _NODE_ yylval;
AST_prog * main_program;

%}

%type<prog> prog
%type<stmts> stmts
%type<stmt> stmt
%type<keyword> keyword
%type<function_decl> function_decl
%type<variable_decl> variable_decl
%type<expr>expr
%type<assignStmt>assignStmt
%type<functionCall>functionCall
%type<ifStmt>ifStmt
%type<whileStmt>whileStmt
%type<forStmt>forStmt
%type<variable>variable
%type<paramD_list>paramD_list
%type<param_list>param_list
%type<paramD>paramD
%type<param>param

%token <name> STRING
%token <number> INT
%token <fnumber> FLOAT
%token <bvalue> BOOL
%token <boperator> BOP 
%token <uoperator> UOP 
%token <aoperator> AOP
%token <aboperator> ABOP
%token <roperator> ROP
%token <dtype> DTYPE

%left ROP
%left AOP
%left ABOP
%right U
%right QMARK
%right UOP
%right BOP

%token OTHER SEMICOLON BREAK 
%token CONTINUE RETURN INPUT BOPEN BCLOSE STOP
%token OUTPUT CBOPEN CBCLOSE QMARK
%token COLON EQUAL COMMA IF ELSE ENDIF WHILE FOR SBOPEN SBCLOSE

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
    $$ = $1;
    main_program = $$;
    printf("\nSuccessful parsing\n");
  }
;

stmts:
    stmts stmt{
        $$->push_back($2);
    }
    |stmt{
        $$ = new AST_stmts();
        $$->push_back($1);
    }

;

stmt:
    function_decl{
        $$ = $1;
    }
    |variable_decl{
        $$ = $1;
    }
    |assignStmt{
        $$ = $1;
    }
    |functionCall SEMICOLON{
        $$ = $1;
    }
    |ifStmt{
        $$ = $1;
    }
    |whileStmt{
        $$ = $1;
    }
    |forStmt{
        $$ = $1;
    }
    |keyword SEMICOLON{
        $$ = $1;
    }
    |RETURN expr SEMICOLON{
        $$ = new AST_returnStmt($2);
    }
    |INPUT BOPEN variable BCLOSE SEMICOLON{
        $$ = new AST_inputStmt($3);
    }
    |OUTPUT BOPEN variable BCLOSE SEMICOLON{
        $$ = new AST_outputStmt($3);
    }
    |SEMICOLON{
        $$ = new AST_int(1);
    }
;

keyword:
    BREAK{
        $$ = new AST_keyword("BREAK");
    }
    |CONTINUE{
        $$ = new AST_keyword("CONTINUE");
    }
    |RETURN{
        $$ = new AST_keyword("RETURN");
    }
;

function_decl:
    DTYPE STRING BOPEN paramD_list BCLOSE CBOPEN stmts CBCLOSE{
        $$ = new AST_function_decl($1,string($2),$4 , $7);
    }

;
variable_decl:
    DTYPE variable SEMICOLON{
        $$ = new AST_variable_decl(string($1),$2);
    }
;

expr: 
    UOP expr %prec UOP{
        $$ = new AST_expr_unary("UOP",$2);
    }
    |expr BOP expr %prec BOP{
        $$ = new AST_expr_binary($1,"BOP",$3);
    }
    |expr QMARK expr COLON expr %prec QMARK{
        $$ = new AST_expr_ternary($1,$3,$5);
    }
    |expr ROP expr{
        $$ = new AST_expr_binary($1,"ROP",$3);
    }
    |expr AOP expr{
        $$ = new AST_expr_binary($1,"AOP",$3);
    }
    |expr ABOP expr{
        $$ = new AST_expr_binary($1,"ABOP",$3);
    }
    |BOPEN expr BCLOSE{
        $$ = $2;
    }
    |AOP expr %prec U{
        $$ = new AST_expr_unary("AOP",$2);
    }
    |param{
        $$ = $1;
    }
    |functionCall{
        $$ = $1;
    }
;

assignStmt: 
    variable EQUAL expr SEMICOLON{
        $$ = new AST_assignStmt($1,$3);
    }
    |DTYPE variable EQUAL expr SEMICOLON{
        $$ = new AST_assignStmt_new(string($1),$2,$4);
    }
;

functionCall:
    STRING BOPEN BCLOSE{
        $$ = new AST_functionCall(string($1));
    }
    |STRING BOPEN param_list BCLOSE{
        $$ = new AST_functionCall(string($1),$3);
    }
;

ifStmt:
    IF BOPEN expr BCLOSE CBOPEN stmts CBCLOSE ENDIF{
        $$ = new AST_ifStmt($3, $6);
    }
    |IF BOPEN expr BCLOSE CBOPEN stmts CBCLOSE ELSE CBOPEN stmts CBCLOSE ENDIF{
        $$ = new AST_ifElseStmt($3, $6, $10);
    }
;

whileStmt:
    WHILE BOPEN expr BCLOSE CBOPEN stmts CBCLOSE{
        $$ = new AST_whileStmt($3, $6);
    }
;

forStmt:
    FOR BOPEN assignStmt expr SEMICOLON assignStmt BCLOSE CBOPEN stmts CBCLOSE{
        $$ = new AST_forStmt($3,$4,$6,$9);
    }
;

variable:
    STRING SBOPEN INT SBCLOSE SBOPEN INT SBCLOSE{
        $$ = new AST_variable_2D_ii(string($1),int($3),int($6));
    }
    |STRING SBOPEN INT SBCLOSE SBOPEN STRING SBCLOSE{
        $$ = new AST_variable_2D_is(string($1),int($3),string($6));                       
    }
    |STRING SBOPEN STRING SBCLOSE SBOPEN INT SBCLOSE{
        $$ = new AST_variable_2D_si(string($1),string($3),int($6));
    }
    |STRING SBOPEN STRING SBCLOSE SBOPEN STRING SBCLOSE{
        $$ = new AST_variable_2D_ss(string($1),string($3),string($6));
    }
    |STRING SBOPEN INT SBCLOSE{
        $$ = new AST_variable_1D_i(string($1),int($3));
    }
    |STRING SBOPEN STRING SBCLOSE{
        $$ = new AST_variable_1D_s(string($1),string($3));
    }
    |STRING{
        $$ = new AST_variable_0D(string($1));
    }
;

param_list:
    param COMMA param_list{
        $$->push_back($1);
    } 
    |param{
        $$ = new AST_param_list();
        $$->push_back($1);       
    }
;

param:
    variable{
        $$ = $1;
    }
    |INT{
        $$ = new AST_int($1);
    }
    |BOOL{
        $$ = new AST_bool($1);
    }
    |FLOAT{
        $$ = new AST_float($1);
    }
;

paramD_list:
    paramD COMMA paramD_list{
        $$->push_back($1);
    }  
    |paramD{
        $$ = new AST_paramD_list();
        $$->push_back($1);
    }
;


paramD:
    DTYPE param{
        $$ = new AST_paramD(string($1),$2);
    }
;



%%

int yyerror(char *s)
{
	printf("Syntax Error on line %s\n", s);
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc == 1 ) {
		fprintf(stderr, "Correct usage: bcc filename\n");
		return 1;
	}

	if (argc > 2) {
		fprintf(stderr, "Passing more arguments than necessary.\n");
		fprintf(stderr, "Correct usage: bcc filename\n");
	}


    flex_output = fopen("flex_output.txt", "w");
    bison_output = fopen("bison_output.txt", "w");

	int return_val = yyparse();
    fprintf(bison_output, "\nRETURN VALUE : %d\n", return_val);

    /*Traverse v;
    main_program->accept(v);*/
    return 0;
}