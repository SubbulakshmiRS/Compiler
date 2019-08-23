%{
  #include <iostream>
  using namespace std;
  extern int yylex();
%}
%%
[ \t\n]          ;
[w][h][i][l][e][\(] { cout << "Found a while loop: " << yytext << endl; }
[f][o][r][\(]   { cout << "Found a for loop: " << yytext << endl; }
[i][f][\{]      { cout << "Found an if construct: " << yytext << endl; }
[e][l][s][e][\{]    { cout << "Found an else construct: " << yytext << endl; }
[i][n][p][u][t][\(][\)]     { cout << "Found an input() function: " << yytext << endl; }
[p][r][i][n][t][\(]     { cout << "Found a print function: " << yytext << endl; }
[\=|\+|\-|\*|\<|\>]     { cout << "Found an arithmetic operator: " << yytext << endl; }
[\&|\!|\|]     {cout << "Found a binary operator: " << yytext << endl; }
[0-9]+           { cout << "Found an integer:" << yytext << endl; }
[a-zA-Z0-9]+     { cout << "Found a string: " << yytext << endl; }
[\{|\}|\[|\]|\(|\)]     {cout<< "Found brace: "<<yytext<<endl; }
.      {cout<<"error - not scannable\n";}          ;
%%
int main(int, char**) {
  
  // open a file handle to a particular file:
  FILE *myfile = fopen("a.snazzle.file", "r");
  // make sure it's valid:
  if (!myfile) {
    cout << "I can't open a.snazzle.file!" << endl;
    return -1;
  }
  // set lex to read from it instead of defaulting to STDIN:
  yyin = myfile;
  
  // lex through the input:
  while(yylex());
}