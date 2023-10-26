%{
    #include <stdio.h>
    int vowels = 0;
    int consonants = 0;
%}

%%
[a,e,i,o,u,A,E,I,O,U] {vowels++;}
[a-zA-Z] {consonants++;}
%%

int main() {
    printf("Enter a string\n");
    yylex();
    printf("The number of vowels is: %d and number of consonants is: %d\n", vowels, consonants);
}

int yywrap() { 
    return 1;
}