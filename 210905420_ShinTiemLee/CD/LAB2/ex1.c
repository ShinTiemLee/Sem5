#include<stdio.h>

int main(){
	FILE *fa,*fb;
	char c1;
	fa=fopen("sample1.txt","r");
	fb=fopen("sample2.txt","w");
	c1=fgetc(fa);
	while(c1 != EOF){
		if(c1==' ' || c1=='\t'){
			fputc(' ',fb);
			c1=fgetc(fa);
			while(c1 == ' ' || c1 == '\t')
				c1=fgetc(fa);
		}
		fputc(c1,fb);
		c1=fgetc(fa);
	}
	fclose(fa);
	fclose(fb);
	return 0;
}