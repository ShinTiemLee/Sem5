%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
int yyerror();
extern FILE* yyin;
%}
%token NUMBER ID DATATYPE NL
%%
stmt : exp ';' NL { printf("Valid Expression"); exit(0);}
		|
	;
exp :  DATATYPE ' ' ID exp
	| ','ID exp
	| DATATYPE ' ' ID '[' NUMBER']' exp
	| ',' ID '[' NUMBER']' exp
	|
	;

%%
int yyerror(char *msg)
{
printf("Invalid Expression\n");
exit(0);
}
void main ()
{
printf("Enter the expression\n");
yyin=fopen("in1.txt","r");
do{
if(yyparse())
{
	printf("\nFailure");
	exit(0);
}}while(feof(yyin));
printf("success");
}