#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h>
typedef struct
{
char token_name[10];
int index;
unsigned int row,col; //Line numbers.
} token;

token gettoken(FILE* fp){
	static int i=1,j=1,id=1;
	int p=0;
	token temp;
	char c;
	char buf[20];
	buf[0]='\0';
	char key[10][10]={"int","float","double","break","continue","char","long","short","return","unsigned"};
	c=fgetc(fp);
	if(c==EOF)
		exit(0);
	if(c=='#'){
		i++;
		while(c!='\n')
			c=fgetc(fp);
		c=fgetc(fp);
	}
	
	while(c==' '){
		c=fgetc(fp);
		j++;
	}
	while(c=='\n'){
		i++;
		j=1;
		c=fgetc(fp);
	}
	while(c==' '){
		c=fgetc(fp);
		j++;
	}
	switch(c){
	case '(':
		strcpy(temp.token_name,"(");
			temp.index=-1;
			temp.row=i;
			temp.col=j;
			j++;
			return temp;
	case ')':
		strcpy(temp.token_name,")");
			temp.index=-1;
			temp.row=i;
			temp.col=j;
			j++;
			return temp;
	case '{':
		strcpy(temp.token_name,"{");
			temp.index=-1;
			temp.row=i;
			temp.col=j;
			j++;
			return temp;
	case '}':
		strcpy(temp.token_name,"}");
			temp.index=-1;
			temp.row=i;
			temp.col=j;
			j++;
			return temp;	
	case '[':
		strcpy(temp.token_name,"[");
			temp.index=-1;
			temp.row=i;
			temp.col=j;
			j++;
			return temp;
	case ']':
		strcpy(temp.token_name,"]");
			temp.index=-1;
			temp.row=i;
			temp.col=j;
			j++;
			return temp;
	case '*':
		strcpy(temp.token_name,"*");
			temp.index=-1;
			temp.row=i;
			temp.col=j;
			j++;
			return temp;
	case '/':
		strcpy(temp.token_name,"/");
			temp.index=-1;
			temp.row=i;
			temp.col=j;
			j++;
			return temp;
	case '%':
		strcpy(temp.token_name,"%");
			temp.index=-1;
			temp.row=i;
			temp.col=j;
			j++;
			return temp;
	case ';':
		strcpy(temp.token_name,";");
			temp.index=-1;
			temp.row=i;
			temp.col=j;
			j++;
			return temp;
	case ',':
		strcpy(temp.token_name,",");
			temp.index=-1;
			temp.row=i;
			temp.col=j;
			j++;
			return temp;
	case '=':
		buf[p++]=c;
		c=fgetc(fp);
		if(c=='='){
			buf[p++]=c;
			buf[p]='\0';
		}
		else
		{
			buf[p]='\0';
			fseek(fp,-1,SEEK_CUR);
		}
		strcpy(temp.token_name,buf);
			temp.index=-1;
			temp.row=i;
			temp.col=j;
			j+=strlen(buf);
			return temp;
	case '>':
		buf[p++]=c;
		c=fgetc(fp);
		if(c=='='){
			buf[p++]=c;
			buf[p]='\0';
		}
		else
		{
			buf[p]='\0';
			fseek(fp,-1,SEEK_CUR);
		}
		strcpy(temp.token_name,buf);
			temp.index=-1;
			temp.row=i;
			temp.col=j;
			j+=strlen(buf);
			return temp;
	case '<':
		buf[p++]=c;
		c=fgetc(fp);
		if(c=='='){
			buf[p++]=c;
			buf[p]='\0';
		}
		else
		{
			buf[p]='\0';
			fseek(fp,-1,SEEK_CUR);
		}
		strcpy(temp.token_name,buf);
			temp.index=-1;
			temp.row=i;
			temp.col=j;
			j+=strlen(buf);
			return temp;
	case '!':
		buf[p++]=c;
		c=fgetc(fp);
		if(c=='='){
			buf[p++]=c;
			buf[p]='\0';
		}
		else
		{
			buf[p]='\0';
			fseek(fp,-1,SEEK_CUR);
		}
		strcpy(temp.token_name,buf);
			temp.index=-1;
			temp.row=i;
			temp.col=j;
			j+=strlen(buf);
			return temp;
	}
	while(isalpha(c)){
		buf[p++]=c;
		c=fgetc(fp);
	}
	buf[p]='\0';
	for(int x=0;x<10;x++){
		if(strcmp(buf,key[x])==0){
			fseek(fp,-1,SEEK_CUR);
			strcpy(temp.token_name,key[x]);
			temp.index=-1;
			temp.row=i;
			temp.col=j;
			j+=strlen(buf);
			return temp;
		}
	}
	if(buf[0]!='\0'){
		fseek(fp,-1,SEEK_CUR);
	strcpy(temp.token_name,"id");
			temp.index=id++;
			temp.row=i;
			temp.col=j;
			j+=strlen(buf);
			return temp;
	}
	if(c=='\"'){
		buf[p++]=c;
		c=fgetc(fp);
		while(c!='\"'){
			buf[p++]=c;
		c=fgetc(fp);
		}
		buf[p]='\0';
		strcpy(temp.token_name,"str");
			temp.index=-1;
			temp.row=i;
			temp.col=j;
			j+=strlen(buf);
			return temp;
	}
	if(c=='\''){
		buf[p++]=c;
		c=fgetc(fp);
		while(c!='\''){
			buf[p++]=c;
		c=fgetc(fp);
		buf[p]='\0';
		}
		strcpy(temp.token_name,"str");
			temp.index=-1;
			temp.row=i;
			temp.col=j;
			j+=strlen(buf);
			return temp;
	}
	while(isdigit(c)){
		buf[p++]=c;
		c=fgetc(fp);
	}
	buf[p]='\0';
	if(buf[0]!='\0'){
		fseek(fp,-1,SEEK_CUR);
	strcpy(temp.token_name,"num");
			temp.index=-1;
			temp.row=i;
			temp.col=j;
			j+=strlen(buf);
			return temp;
}
}


int main()
{
char c,buf[10];
FILE *fp=fopen("digit.c","r");
token k;
while(1){
	k=gettoken(fp);
	printf("<%s,%d,%d>\n",k.token_name,k.row,k.col);
}
return 0;
}
