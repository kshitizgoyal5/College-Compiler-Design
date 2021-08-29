%{
#include<stdio.h>
int count = 0;
%}

%%
[-]?[0-9]+(["."][0-9]+)? {printf("%s\n", yytext);count++;}
.|\n ;		
%%

int yywrap(){}

int main(){
 FILE *fp;
 char filename[50] = "input.txt";\
 fp = fopen(filename,"r");
 yyin = fp;
yylex();
printf("\nTotal numbers - %d\n", count);
return 0;
}

