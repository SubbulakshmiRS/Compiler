%{
#include <stdio.h>
#include <stdbool.h>

#include "AST.h"

extern FILE *yyin;
int yylex (void);
void yyerror (char const *s);

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
%type<variable_0D>variable_0D
%type<paramD_list>paramD_list
%type<param_list>param_list
%type<paramD>paramD
%type<param>param

%token <name> STRING
%token <number> INT
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
        printf("\nstmts");
    }
    |stmt{
        $$ = new AST_stmts();
        $$->push_back($1);
        printf("\nstmt");
    }

;

stmt:
    function_decl{
        $$ = $1;
        printf("\nfunction_decl");
    }
    |variable_decl{
        $$ = $1;
        printf("\nvariable_decl");
    }
    |assignStmt{
        $$ = $1;
        printf("\nassignStmt");
    }
    |ifStmt{
        $$ = $1;
        printf("\nifStmt");
    }
    |whileStmt{
        $$ = $1;
        printf("\nwhileStmt");
    }
    |forStmt{
        $$ = $1;
        printf("\nforStmt");
    }
    |keyword SEMICOLON{
        $$ = $1;
        printf("\nkeyword");
    }
    |RETURN expr SEMICOLON{
        $$ = new AST_returnStmt($2);
        printf("\nreturnStmt");
    }
    |INPUT BOPEN variable BCLOSE SEMICOLON{
        $$ = new AST_inputStmt($3);
        printf("\ninputStmt");
    }
    |OUTPUT BOPEN variable BCLOSE SEMICOLON{
        $$ = new AST_outputStmt($3);
        printf("\noutputStmt");
    }
    |SEMICOLON{
        //need a hack 
        $$ = new AST_semicolon();
        printf("\nsemicolon");
    }
;

keyword:
    BREAK{
        $$ = new AST_keyword("BREAK");
        printf("\nbreak");
    }
    |CONTINUE{
        $$ = new AST_keyword("CONTINUE");
        printf("\ncontinue");
    }
    |RETURN{
        $$ = new AST_keyword("RETURN");
        printf("\nreturn");
    }
;

function_decl:
    DTYPE STRING BOPEN paramD_list BCLOSE CBOPEN stmts CBCLOSE{
        $$ = new AST_function_decl($1,string($2),$4 , $7);
        printf("\nfunction_decl");
    }
;

variable_decl:
    DTYPE variable SEMICOLON{
        $$ = new AST_variable_decl(string($1),$2);
        printf("\nvariable_decl");
    }
;

expr: 
    UOP expr %prec UOP{
        $$ = new AST_expr_unary("UOP",$2);
        printf("\n%s",$1);
    }
    |expr BOP expr %prec BOP{
        $$ = new AST_expr_binary($1,"BOP",$3);
        printf("\n%s",$2);
    }
    |expr QMARK expr COLON expr %prec QMARK{
        $$ = new AST_expr_ternary($1,$3,$5);
        printf("\n?:");
    }
    |expr ROP expr{
        $$ = new AST_expr_binary($1,"ROP",$3);
        printf("\n%s",$2);
    }
    |expr AOP expr{
        $$ = new AST_expr_binary($1,"AOP",$3);
        printf("\n%s",$2);
    }
    |expr ABOP expr{
        $$ = new AST_expr_binary($1,"ABOP",$3);
        printf("\n%s",$2);
    }
    |BOPEN expr BCLOSE{
        $$ = $2;
    }
    |AOP expr %prec U{
        $$ = new AST_expr_unary("AOP",$2);
        printf("\n%s",$1);
    }
    |param{
        $$ = $1;
        printf("\nparam");
    }
    |functionCall{
        $$ = $1;
        printf("\nfuntionCall");
    }
;

assignStmt: 
    variable EQUAL expr SEMICOLON{
        $$ = new AST_assignStmt_old($1,$3);
        printf("\nassignStmt_Old");
    }
    |DTYPE variable EQUAL expr SEMICOLON{
        $$ = new AST_assignStmt_new(string($1),$2,$4);
        printf("\nassignStmt_new");
    }
;

functionCall:
    STRING BOPEN BCLOSE{
        $$ = new AST_functionCall_noargs(string($1));
        printf("\nfuntionCall_noargs");
    }
    |STRING BOPEN param_list BCLOSE{
        $$ = new AST_functionCall_args(string($1),$3);
        printf("\nfunctionCall_args");
    }
;

ifStmt:
    IF BOPEN expr BCLOSE CBOPEN stmts CBCLOSE ELSE CBOPEN stmts CBCLOSE SEMICOLON{
        $$ = new AST_ifElseStmt($3, $6, $10);
        printf("\nifElseStmt");
    }
    |IF BOPEN expr BCLOSE CBOPEN stmts CBCLOSE SEMICOLON{
        $$ = new AST_ifWEStmt($3, $6);
        printf("\nifWEStmt");
    }
;

whileStmt:
    WHILE BOPEN expr BCLOSE CBOPEN stmts CBCLOSE{
        $$ = new AST_whileStmt($3, $6);
        printf("\nwhileStmt");
    }
;

forStmt:
    FOR BOPEN variable EQUAL variable SEMICOLON variable SEMICOLON variable SEMICOLON BCLOSE CBOPEN stmts CBCLOSE{
        $$ = new AST_forStmt($3, $5, $7,$9 , $13 );
        printf("\nforStmt");
    }
;

variable:
    STRING SBOPEN INT SBCLOSE SBOPEN INT SBCLOSE{
        $$ = new AST_variable_2D_ii(string($1),int($3),int($6));
        printf("\nvariable_2d");
    }
    |STRING SBOPEN INT SBCLOSE SBOPEN variable_0D SBCLOSE{
        $$ = new AST_variable_2D_iv(string($1),int($3),$6);
        printf("\nvariable_2d");                       
    }
    |STRING SBOPEN variable_0D SBCLOSE SBOPEN INT SBCLOSE{
        $$ = new AST_variable_2D_vi(string($1),$3,int($6));
        printf("\nvariable_2d");
    }
    |STRING SBOPEN variable_0D SBCLOSE SBOPEN variable_0D SBCLOSE{
        $$ = new AST_variable_2D_vv(string($1),$3,$6);
        printf("\nvariable_2d");
    }
    |STRING SBOPEN INT SBCLOSE{
        $$ = new AST_variable_1D_i(string($1),int($3));
        printf("\nvariable_1d");
    }
    |STRING SBOPEN variable_0D SBCLOSE{
        $$ = new AST_variable_1D_v(string($1),$3);
        printf("\nvariable_2d");
    }
    |variable_0D{
        $$ = $1;
        printf("\nvariable");
    }
;

variable_0D:
    STRING{
            $$ = new AST_variable_0D(string($1));
            printf("\nvariable_0d");
        }
;

param_list:
    param_list COMMA param{
        $$->push_back($3);
        printf("\nparam_list");
    } 
    |param{
        $$ = new AST_param_list();
        $$->push_back($1);
        printf("\nparam");       
    }
;

param:
    variable{
        $$ = $1;
        printf("\nvariable");
    }
    |INT{
        $$ = new AST_int($1);
        printf("\nint");
    }
    |BOOL{
        $$ = new AST_bool($1);
        printf("\nbool");
    }
;

paramD_list:
    paramD_list COMMA paramD {
        $$->push_back($3);
        printf("\nparamD_list");
    }  
    |paramD{
        $$ = new AST_paramD_list();
        $$->push_back($1);
        printf("\nparamD");
    }
;


paramD:
    DTYPE variable{
        $$ = new AST_paramD(string($1),$2);
        printf("\nparam");
    }
;



%%

void yyerror (char const *s)
{
        fprintf (stderr, "----------------ERROR----------------\n");
        fprintf (stderr, "%s\n", s);
        fprintf (stderr, "----------------ERROR----------------\n");
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


    yyin = fopen(argv[1], "r");
	int return_val = yyparse();
    printf("\nRETURN VALUE : %d\n", return_val);

    /*Traverse v;
    main_program->accept(v);*/
    return 0;
}