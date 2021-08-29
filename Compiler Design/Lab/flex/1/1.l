%{
#include<stdio.h>
%}

%%
[A-Z] {printf("%c", (*yytext-'A'+'a'));}
.     {printf("%s", yytext);}
%%
int yywrap(){}

int main(){
 FILE *fp;
 char filename[50] = "input.txt";
 fp = fopen(filename,"r");
 yyin = fp;
  
yylex();
  
return 0;
}
