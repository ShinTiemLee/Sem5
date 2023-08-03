#include<stdio.h>
#include<stdlib.h>

int main(){
	FILE* fa;
	char c;
	int cchar=0,cline=1;
	fa=fopen("sample.txt","r");
	if (fa == NULL){
		printf("Cannot open file \n");
		exit(0);
	}
	c=fgetc(fa);
	while(c!=EOF){
		cchar++;
		if(c=='\n')
			cline++;
		c=fgetc(fa);
	}
	fclose(fa);
	printf("No.of char=%d, No.of lines=%d",cchar,cline);
	return 0;
}