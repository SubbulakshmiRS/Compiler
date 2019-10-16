# PARSER

Parser created by flex and bison is used to check a given code ending with $. When code accepted, parser prints "Successful parsing". Some acceptable codes are written down.


## Usage

```
make
./test
```

## Examples
a=1; $

int a=2; $

if(1){ ; } $

if(i>1){ output(i) ;} $

for(i=1;i<2;i=i+1;){ int a=1;a=a+1;} $

int add(int a , int b){ return (a+b) ;}$

add(1 , 2 , 3); $

int add(int a , int b){ return add(a , 0); } $