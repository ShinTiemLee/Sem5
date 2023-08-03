#include<stdio.h>
#include<stdlib.h>

int main(){
	FILE *fa,*fb;
	char c;
	long int count;
	fa=fopen("sample1.txt","r");
	fb=fopen("sample2.txt","w");
	if (fa == NULL){
		printf("Cannot open 1st file \n");
		exit(0);
	}
	if (fb == NULL){
		printf("Cannot open 2nd file \n");
		exit(0);
	}
	fseek(fa, 0, SEEK_END);
	count=ftell(fa);
	printf("size=%ld",count);
	for(int i=1;i<=count+1;i++){
		c=fgetc(fa);
		if(c!=EOF)
			fputc(c,fb);
		fseek(fa,0-i, SEEK_END);
	}
	fclose(fa);
	fclose(fb);
	return 0;
}