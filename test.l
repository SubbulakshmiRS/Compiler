%{

#include <stdio.h>
#include <string.h>

#include "AST.h"
#include "test.tab.h"
extern union _NODE_ yylval;

void showError();
%}


numbers     ([0-9])+
alpha       ([a-zA-Z])+

%%
"$"     {return (STOP);}
"="     {return (EQUAL);}
"?"     {return (QMARK);}
":"     {return (COLON);}
","     {return (COMMA);}
"("     {return (BOPEN);}
")"     {return (BCLOSE);}
"["     {return (SBOPEN);}
"]"     {return (SBCLOSE);}
"{"     {return (CBOPEN);}
"}"     {return (CBCLOSE);}
"<"|">"|">="|"<="|"=="  {sscanf(yytext, "%s", yylval.roperator);return (ROP);}
"+"|"-"  {sscanf(yytext, "%s", yylval.aoperator); return (AOP);}   
"*"|"/"   {sscanf(yytext, "%s", yylval.aboperator); return (ABOP);}
"&&"|"||"   {sscanf(yytext, "%s", yylval.boperator); return (BOP);}  
"!"  {sscanf(yytext, "%s", yylval.uoperator);return (UOP);}
int|bool|void  {sscanf(yytext, "%s", yylval.dtype); return (DTYPE);}
while   {return (WHILE);}
for     {return (FOR);}
if      {return (IF);}
else    {return (WHILE);}   
input   {return (INPUT);}
output  {return (OUTPUT);}
return  {return (RETURN);}
break   {return (BREAK);}
continue    {return (CONTINUE);}
true|false  { yylval.bvalue=0; if(yytext=="true") yylval.bvalue = 1; return (BOOL);}
{alpha}			   {sscanf(yytext, "%s", yylval.name); return (STRING);}
{numbers}      {yylval.number = atoi(yytext); return (INT);}
";"      		   {return (SEMICOLON);}
[ \t\n]+          /* eat up whitespace */
.      		     {printf("unrecognized: %s\n",yytext);showError(); return(OTHER);}

%%


void showError(){
    printf("\nerror\n");
}
