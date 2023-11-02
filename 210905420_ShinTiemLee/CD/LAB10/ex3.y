%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
int yyerror();
extern FILE* yyin;
%}
%token NUMBER ID NL
%left '+'
%left '*'
%%
stmt : exp NL { printf("Valid Expression"); exit(0);}
;
exp : exp '+' term
| term
term: term '*' factor
|factor
factor: ID
| NUMBER
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
yyin=fopen("in.txt","r");
do{
if(yyparse())
{
	printf("\nFailure");
	exit(0);
}}while(feof(yyin));
printf("success");
}