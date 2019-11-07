# PARSER

Parser created by flex and bison is used to check a given code ending with $. When code accepted, parser prints "Successful parsing". AST tree construction is also done and a recursive tree is created. The tree traversal is also printed. Some acceptable codes are written down.

#

## LANGAUGE
The language follows the below features 

**Data Types:** int, float, char, string, bool, 1D and 2D arrays.

**Arithmetic Operations:** add, sub, mul, div

**Boolean Operations:** and, or, not

**Relational Operations:** >, <, >=, <= 

**Control Statements:** if, if-else, for loop, while loop, cond?opt1:opt2

**Functions:** Call by Value parameter passing mechanism, recursion support

**I/O Routines:** Output, Input

#

## FILES

**input.txt** : contains the code to be scanned, parsed and the AST tree is constructed and its traversal printed

**AST.cpp** : AST construction with all definitions of classes

**AST.h** : AST construction header file with all class declarations

**test.l** : Flex file for my language (contains Micro syntax)

**test.y** : Bison file for my language (contains Macro syntax)

**Makefile** : Makefile containing all commands to run the parser
#

## USAGE

```
make
./test input.txt
```
#

## EXAMPLES CODES
a=-1; $

a=1; $

a[1][2] = 1; $

int a[2][2] ; $

int a=2; $

a=(a+1); $

b = ++a; $

if(1){ ; } $

if(i>1){ output(i) ;} $

for(i=1;i<2;i=i+1;){ int a=1;a=a+1;} $

int add(int a , int b){ return (a+b) ;}$

int sum = add(1 , 2 , 3); $

int add(int a , int b){ return add(a , 0); } $
#


## EXAMPLE OUTPUT
### Input : a=-1; $

variable_0d

variable

int

param

-

assignStmt_Old

assignStmt

stmt

Successful parsing


RETURN VALUE : 0