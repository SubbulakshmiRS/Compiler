%{

#include <stdio.h>
#include <string.h>

#include "test.tab.h"
void showError();
%}


numbers     ([0-9])+
alpha       ([a-zA-Z])+

%%
"="     {return (EQUAL);}
"?"     {return (QMARK);}
":"     {return (COLON);}
","     {return (COMMA);}
"("     {printf("dw ");return (BOPEN);}
")"     {return (BCLOSE);}
"["     {return (SBOPEN);}
"]"     {return (SBCLOSE);}
"{"     {return (CBOPEN);}
"}"     {return (CBCLOSE);}
"<"|">"|">="|"<=" {return (ROP);}
"&&"|"||"   {return (COP);}
"+"|"-"|"*"|"/"     {yylval.operator = yytext[0]; return (OP);}
int|char|string|void  {sscanf(yytext, "%s", yylval.dtype); return (DTYPE);}
while   { return (WHILE);}
for     {return (FOR);}
if      {printf("djabs ");return (IF);}
else    {return (WHILE);}   
input   {return (INPUT);}
output  {return (OUTPUT);}
return  {return (RETURN);}
{alpha}			   {sscanf(yytext, "%s", yylval.name); return (STRING);}
{numbers}      {yylval.number = atoi(yytext); return (NUM);}
";"      		   {return (SEMICOLON);}
[ \t\n]+          /* eat up whitespace */
.      		     {printf("what is it: %s\n",yytext);showError(); return(OTHER);}

%%


void showError(){
    printf("Other input");
}

// void findBOp(string text)
// {
//     switch(text)
//     {
//         case "+":

//                 Break;
//         case "-":
//                 Block-2;
//                 Break;
//         case "/":
//                 Block-n;
//                 Break;
//         case "*":
//                 Block-n;
//                 Break;              
//         default:
//                 Block-1;
//                 Break;
//     }
// }