#include<stdio.h>
#include<stdlib.h>

int main(){
	FILE *fa,*fb,*fc;
	char ca,cb;
	int count=0;
	fa=fopen("sample1.txt","r");
	fb=fopen("sample2.txt","r");
	fc=fopen("sample3.txt","w");
	if (fa == NULL){
		printf("Cannot open 1st file \n");
		exit(0);
	}
	if (fb == NULL){
		printf("Cannot open 2nd file \n");
		exit(0);
	}
	ca=fgetc(fa);
	cb=fgetc(fb);
	while(ca!=EOF && cb!=EOF){
		count=0;
			while(count<2 && ca!=EOF){
				if(ca!='\n' && ca!=EOF)
					fputc(ca,fc);
				else{
					fputc('\n',fc);
					count++;
				}
				ca=fgetc(fa);
			}
			if(ca==EOF){
				fputc('\n',fc);
				break;
			}
			count=0;
			while(count<2 && cb!=EOF){
				if(cb!='\n' && cb!=EOF)
					fputc(cb,fc);
				else{
					fputc('\n',fc);
					count++;
				}
				cb=fgetc(fb);
			}
			if(cb==EOF){
				fputc('\n',fc);
				break;
			}
	}
	while(ca!=EOF){
		fputc(ca,fc);
		ca=fgetc(fa);
	}
	while(cb!=EOF){
		fputc(cb,fc);
		cb=fgetc(fb);
	}
	fclose(fa);
	fclose(fb);
	fclose(fc);
	return 0;
}