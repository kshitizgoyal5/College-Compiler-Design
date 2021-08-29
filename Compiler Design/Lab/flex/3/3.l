%{
#include<stdio.h>
#include<string.h>
int count = 0;
int length = -1;
%}

%%
\n	;
[a-zA-Z]+ { length = strlen(yytext);	
			if(length > 10){
				for(int i=0; i<10; i++){
					printf("%c", *(yytext+i));
				}
				count++;
				printf("\n");
			}
		}
.		;
%%

int yywrap(){}

int main(){
 FILE *fp;
 char filename[50] = "input.txt";
 fp = fopen(filename,"r");
 yyin = fp;
  
yylex();
printf("\nTotal words - %d\n", count);
return 0;
}

