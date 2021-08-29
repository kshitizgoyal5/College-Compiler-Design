%{
#include<stdio.h>
int count = 0;
%}

%%
[a-zA-Z]+ { count++;printf("%s", yytext);}
%%

int yywrap(){}

int main(){
 FILE *fp;
 char filename[50] = "input.txt";\
 fp = fopen(filename,"r");
 yyin = fp;
  
yylex();
printf("\nTotal words - %d\n", count);
return 0;
}

