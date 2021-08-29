%{
#include<stdio.h>
%}

keyword (bool|int|float|char|cin|cout|using|namespace|if|else)
digit	[0-9]
letter	[a-zA-Z]
 


%%
[\n]+									{printf("\n");}
["].*["]								{printf(" { %s String} ", yytext);}
[\/]{2}[^\n]*							{}
[\b]+									{}
[\t]+									{}
{keyword}								{printf(" { %s KeyWord} ", yytext);}
[+|'-'|*|/|%|'|'|&|>>|<<]?=							{printf(" { %s Assignment Operators} ", yytext);}
[+|'-'|<|>|'|'|&|]{2}							{printf(" { %s Special Operators} ", yytext);}
[+'-'*/%<>:]{1}						{printf(" { %s Arith/Logical operators} ", yytext);}
{letter}({letter}|{digit}|_)*				{printf(" { %s Identifier} ", yytext);}
[-]?{digit}+(["."]{digit}+)?		{printf(" { %s Number} ", yytext);}
[,.;]+ 									{printf(" { %s Punctuation} ", yytext);}
[!#@&()<>{}\[\]]							{printf(" { %s Special Chars.} ", yytext);}
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

