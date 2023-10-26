%{ 
#include <stdio.h>
#include <string.h>
int chars = 0;
int words = 0;
int lines = 0;
int blanks = 0;
%}
%%
[a-zA-Z]+ { words++; chars += strlen(yytext); }
[\n] { chars++; lines++; }
[ ] { blanks++; }
. { chars++; }
%%
int yywrap(){
return 1;
}
int main()
{
    char str[20];
    printf("Enter input string\n");
    yylex();
    printf("Number of lines is: %d\n", lines); 
    printf("Number of words is: %d\n", words); 
    printf("Number of characters is: %d\n", chars); 
    printf("Number of blanks is: %d\n", blanks); 
}