#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(){
	char** arr=(char**)malloc(50*sizeof(char*));
	for(int i=0;i<50;i++){
		arr[i]=(char*)malloc(50*sizeof(char));
	}
	arr[0]="if";
	arr[1]="else";
	arr[2]="while";
	arr[3]="do";
	arr[4]="return";
	arr[5]="break";
	arr[6]="char";
	arr[7]="int";

	FILE *fa;
	fa=fopen("sample3.c","r");
	char c=fgetc(fa);
	int i=0,j=0;
	while(c != EOF){
		int p=0;
		char str[50]="\0";
		while(c>96 && c<123){
			str[p]=c;
			p++;
			c=fgetc(fa);
		}
		for(i=0;i<sizeof(arr);i++){
			if(strcmp(str,arr[i])==0){
				int k=0;
				while(str[k]) {
      			putchar (toupper(str[k]));
      			k++;
   				}
   				printf("\n");
			}
		}
		c=fgetc(fa);
	}
	fclose(fa);  
}
