#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct linkedlist ll;
typedef struct
{
    char token_name[10];
    int index;
    char datatype[10];
    char tokentype[10];
    char returntype[10];
    int args;
    unsigned int row, col; // Line numbers.
} token;

typedef struct linkedlist{
	token item;
	ll *next;
}ll;

token gettoken(FILE *fp,ll list[],int *id)
{
    static int i = 1, j = 1;
    int p = 0;
    token temp;
    char c;
    char buf[20];
    buf[0] = '\0';
    char key[10][10] = {"int", "float", "double", "break", "continue", "char", "long", "short", "return", "unsigned"};
    c = fgetc(fp);
    if (c == EOF)
        exit(0);
    if (c == '#')
    {
        i++;
        while (c != '\n')
            c = fgetc(fp);
        c = fgetc(fp);
    }

    while (c == ' ')
    {
        c = fgetc(fp);
        j++;
    }
    if (c == '\n' || c == 13)
    {
        while (c == '\n' || c == 13)
        {
            if (c == '\n')
                i++;
            j = 1;
            c = fgetc(fp);
            printf("\n");
        }
    }
    while (c == ' ')
    {
        c = fgetc(fp);
        j++;
    }
    switch (c)
    {
    case '(':
        strcpy(temp.token_name, "(");
        temp.index = -1;
        temp.row = i;
        temp.col = j;
        j++;
        return temp;
    case ')':
        strcpy(temp.token_name, ")");
        temp.index = -1;
        temp.row = i;
        temp.col = j;
        j++;
        return temp;
    case '{':
        strcpy(temp.token_name, "{");
        temp.index = -1;
        temp.row = i;
        temp.col = j;
        j++;
        return temp;
    case '}':
        strcpy(temp.token_name, "}");
        temp.index = -1;
        temp.row = i;
        temp.col = j;
        j++;
        return temp;
    case '[':
        strcpy(temp.token_name, "[");
        temp.index = -1;
        temp.row = i;
        temp.col = j;
        j++;
        return temp;
    case ']':
        strcpy(temp.token_name, "]");
        temp.index = -1;
        temp.row = i;
        temp.col = j;
        j++;
        return temp;
    case '*':
        strcpy(temp.token_name, "*");
        temp.index = -1;
        temp.row = i;
        temp.col = j;
        j++;
        return temp;
    case '/':
        strcpy(temp.token_name, "/");
        temp.index = -1;
        temp.row = i;
        temp.col = j;
        j++;
        return temp;
    case '%':
        strcpy(temp.token_name, "%");
        temp.index = -1;
        temp.row = i;
        temp.col = j;
        j++;
        return temp;
    case ';':
        strcpy(temp.token_name, ";");
        temp.index = -1;
        temp.row = i;
        temp.col = j;
        j++;
        return temp;
    case ',':
        strcpy(temp.token_name, ",");
        temp.index = -1;
        temp.row = i;
        temp.col = j;
        j++;
        return temp;
    case '=':
        buf[p++] = c;
        c = fgetc(fp);
        if (c == '=')
        {
            buf[p++] = c;
            buf[p] = '\0';
        }
        else
        {
            buf[p] = '\0';
            fseek(fp, -1, SEEK_CUR);
        }
        strcpy(temp.token_name, buf);
        temp.index = -1;
        temp.row = i;
        temp.col = j;
        j += strlen(buf);
        return temp;
    case '>':
        buf[p++] = c;
        c = fgetc(fp);
        if (c == '=')
        {
            buf[p++] = c;
            buf[p] = '\0';
        }
        else
        {
            buf[p] = '\0';
            fseek(fp, -1, SEEK_CUR);
        }
        strcpy(temp.token_name, buf);
        temp.index = -1;
        temp.row = i;
        temp.col = j;
        j += strlen(buf);
        return temp;
    case '<':
        buf[p++] = c;
        c = fgetc(fp);
        if (c == '=')
        {
            buf[p++] = c;
            buf[p] = '\0';
        }
        else
        {
            buf[p] = '\0';
            fseek(fp, -1, SEEK_CUR);
        }
        strcpy(temp.token_name, buf);
        temp.index = -1;
        temp.row = i;
        temp.col = j;
        j += strlen(buf);
        return temp;
    case '!':
        buf[p++] = c;
        c = fgetc(fp);
        if (c == '=')
        {
            buf[p++] = c;
            buf[p] = '\0';
        }
        else
        {
            buf[p] = '\0';
            fseek(fp, -1, SEEK_CUR);
        }
        strcpy(temp.token_name, buf);
        temp.index = -1;
        temp.row = i;
        temp.col = j;
        j += strlen(buf);
        return temp;
    }
    while (isalpha(c))
    {
        buf[p++] = c;
        c = fgetc(fp);
    }
    buf[p] = '\0';
    for (int x = 0; x < 10; x++)
    {
        if (strcmp(buf, key[x]) == 0)
        {
            fseek(fp, -1, SEEK_CUR);
            strcpy(temp.token_name, key[x]);
            temp.index = -1;
            temp.row = i;
            temp.col = j;
            j += strlen(buf);
            return temp;
        }
    }
    
    if (buf[0] != '\0')
    {	
    	int x=strlen(buf)%10;
    	ll *ptr;
    	ptr=list;
    	for(int o=1;o<x;o++)
    		ptr++;
    	
    	int flag=0;
    	
    	while(ptr!=NULL){
    		if(strcmp(ptr->item.token_name,buf)==0){
    			flag=1;
    			break;
    		}
    		ptr=ptr->next;
    	}
    
    	if(c=='('){
    		strcpy(temp.tokentype,"func");
    	}
    	else
    		strcpy(temp.tokentype,"var");
        fseek(fp, -1, SEEK_CUR);
        if (flag==1)
        	temp.index=ptr->item.index;
        else
        	temp.index = (*id)++;
        strcpy(temp.token_name, buf);
        temp.row = i;
        temp.col = j;
        j += strlen(buf);
        return temp;
    }
    if (c == '\"')
    {
        buf[p++] = c;
        c = fgetc(fp);
        while (c != '\"')
        {
            buf[p++] = c;
            c = fgetc(fp);
        }
        buf[p] = '\0';
        strcpy(temp.token_name, "str");
        temp.index = -1;
        temp.row = i;
        temp.col = j;
        j += strlen(buf);
        return temp;
    }
    if (c == '\'')
    {
        buf[p++] = c;
        c = fgetc(fp);
        while (c != '\'')
        {
            buf[p++] = c;
            c = fgetc(fp);
            buf[p] = '\0';
        }
        strcpy(temp.token_name, "str");
        temp.index = -1;
        temp.row = i;
        temp.col = j;
        j += strlen(buf);
        return temp;
    }
    while (isdigit(c))
    {
        buf[p++] = c;
        c = fgetc(fp);
    }
    buf[p] = '\0';
    if (buf[0] != '\0')
    {
        fseek(fp, -1, SEEK_CUR);
        strcpy(temp.token_name, "num");
        temp.index = -1;
        temp.row = i;
        temp.col = j;
        j += strlen(buf);
        return temp;
    }
}

int main()
{
    char c, buf[10];
    int *id=(int*)malloc(sizeof(int));
    *id=1;
    FILE *fp = fopen("digit.c", "r");
    token t;
    ll list[10];
    ll *temp;
    ll *ptr;
    int p=0,flag=0;
    while (1)
    {
    	int s=*id;
        t = gettoken(fp,list,id);
        
        //printf("<%s,%d,%d>", t.token_name, t.row, t.col);
        if(*id<=s){
        	continue;
        }
        
        int index=strlen(t.token_name)%10;
        *ptr=list[index];
       
        while(ptr->next!=NULL){
        	ptr=ptr->next;
        }

        temp=(ll*)malloc(sizeof(ll));
        temp->item=t;
        temp->next=NULL;
        ptr->next=temp;
        if(s<(*id)){
        //printf("\n%d\t%s\t%s\t%s\t%s\t%d",t.index,t.token_name,t.returntype,t.datatype,t.tokentype,t.args);
         printf("\n%d\t%s\t%s",t.index,t.token_name,t.tokentype);
    }
    }
    return 0;
}