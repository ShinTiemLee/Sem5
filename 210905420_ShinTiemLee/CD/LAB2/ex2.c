#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main(){
	FILE *fa,*fb;
	char c1;
	char *ch=(char*)malloc(sizeof(char));
	printf("Enter file name : ");
	gets(ch);
	fa=fopen(ch,"r");
	fb=fopen("sample2.txt","w");
	c1=fgetc(fa);
	while(c1 != EOF){
		if(c1=='#'){
			c1=fgetc(fa);
			while(c1>96 && c1<123)
				c1=fgetc(fa);
		}
		fputc(c1,fb);
		c1=fgetc(fa);
	}
	fclose(fa);
	fclose(fb);
	return 0;
}