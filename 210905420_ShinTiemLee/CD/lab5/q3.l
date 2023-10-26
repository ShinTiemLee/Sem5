%{
	int positive_number = 0;
	int negative_number = 0;
	int positive_floating = 0;
	int negative_floating = 0;
%}

%%
\+?[0-9]+ { positive_number++; }
-[0-9]+ {negative_number++;}
\+?[0-9]+\.[0-9]+ { positive_floating++; }
-[0-9]+\.[0-9]+ {negative_floating++;}
%%

main(int argc, char **argv) {
	yyin = fopen("input1.txt", "r");
	yylex();
	printf("+ve whole numbers:%d,-ve whole numbers:%d,+ve floating:%d,-ve floating:%d\n", positive_number, negative_number, positive_floating, negative_floating); 
}
int yywrap() {
	return 1;
}
