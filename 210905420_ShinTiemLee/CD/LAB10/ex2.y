%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
int yyerror();
extern FILE* yyin;
%}
%token NUMBER ID RELOP IF ELSE
%%
start: stmt	{ printf("Valid Expression"); exit(0);}
	;
stmt : IF '('exp')' '{' code '}' 
		| IF '(' exp')''{'code'}' ELSE'{'code'}'
	;
exp :  ID RELOP NUMBER
	|	ID RELOP ID
	|	NUMBER RELOP NUMBER
	|	NUMBER RELOP ID
	;
code: ID '=' assign';' code
	|
	;
assign: NUMBER  
	| ID 
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
yyin=fopen("in2.txt","r");
do{
if(yyparse())
{
	printf("\nFailure");
	exit(0);
}}while(feof(yyin));
printf("success");
}