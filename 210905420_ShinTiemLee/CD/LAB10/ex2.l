%{
#include "ex1.tab.h"
//filename.tab.h : here both flex and bison
%}
%%
[0-9]+ {return NUMBER; }
"int" {  return DATATYPE;}
"float" {  return DATATYPE;}
"char" { return DATATYPE;}
[a-zA-Z][a-zA-Z0-9_]* { return ID; }
\n	{return NL;}
 ["if"]  {return IF; }
 ["else"]  {return ELSE; }
[+,-]	{return OP;}
[<=,<,>,>=,==,!=]	 {return RELOP;}
[;,{,},(,),=]	{return yytext[0];}
%%

int yywrap(){
	return 1;
}