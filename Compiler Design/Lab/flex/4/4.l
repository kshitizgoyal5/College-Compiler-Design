%{
#include<stdio.h>
int count = 2;
%}

%%
["\n"] {printf("\n%d: ",count++);}
. {printf("%s", yytext);}
%%

int yywrap(){}

int main(){
 FILE *fp;
 char filename[50] = "input.txt";\
 fp = fopen(filename,"r");
 yyin = fp;
  printf("1: ");
yylex();
printf("\nTotal lines - %d\n", count-1);
return 0;
}

