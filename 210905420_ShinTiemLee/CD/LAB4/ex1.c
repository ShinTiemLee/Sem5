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

typedef struct linkedlist
{
    token item;
    ll *next;
} ll;

token gettoken(FILE *fp, ll list[], int *id)
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
    {
        temp.index = -2;
        return temp;
    }
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
        strcpy(temp.tokentype, ",");
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
            strcpy(temp.tokentype, "keyword");
            temp.index = -1;
            temp.row = i;
            temp.col = j;
            j += strlen(buf);
            return temp;
        }
    }
    if (buf[0] != '\0')
    {
        int x = strlen(buf) % 10;
        ll *ptr;
        ptr = (list + x);

        int flag = 0;

        while (ptr != NULL)
        {

            if (strcmp(ptr->item.token_name, buf) == 0)
            {

                flag = 1;
                break;
            }
            ptr = ptr->next;
        }

        if (c == '(')
        {
            strcpy(temp.tokentype, "func");
        }
        else
            strcpy(temp.tokentype, "var");
        fseek(fp, -1, SEEK_CUR);
        if (flag == 1)
            temp.index = ptr->item.index;
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
    token arr[50];
    int num = 0, s = 0, count = 0;
    int *id = (int *)malloc(sizeof(int));
    *id = 1;
    FILE *fp = fopen("digit.c", "r");
    token t;
    ll *list = (ll *)malloc(10 * sizeof(ll));
    ll *temp;
    ll *ptr;
    int p = 0, flag = 0;
    char key[10][10] = {"int", "float", "double", "char", "long", "short"};
    while (1)
    {   
        t = gettoken(fp, list, id);
        if (t.index == -2)
            break;
        flag=0;
        if (strcmp(t.token_name, ";") == 0) 
            flag=1;
        if(strcmp(t.token_name, "{") == 0)
           flag=1;
        if(flag==1)  
        {
            num = 0;
            for (int y = 0; y <= count; y++)
            {

                for (int x = 0; x < 6; x++)
                {

                    if (strcmp(arr[y].token_name, key[x]) == 0)
                    {
                        strcpy(buf, arr[y].token_name);
                    }
                }
                if ((strcmp(arr[y].tokentype, "var") == 0 || strcmp(arr[y].tokentype, "func") == 0) && arr[y].index >= s)
                {

                    int index = strlen(arr[y].token_name) % 10;
                    ptr = list + index;

                    while (ptr->next != NULL)
                    {
                        ptr = ptr->next;
                    }

                    temp = (ll *)malloc(sizeof(ll));
                    temp->item = arr[y];

                    temp->next = NULL;
                    if (strcmp(arr[y].tokentype, "var") == 0)
                    {
                        strcpy(temp->item.returntype, "-");
                        temp->item.args = -1;
                        strcpy(temp->item.datatype, buf);
                        ptr->next = temp;
                    }
                    else if(strcmp(arr[y].tokentype, "func") == 0)
                    {
                        strcpy(temp->item.datatype, "-");
                       
                        for (int y = 0; y <= count; y++)
                        {
                            if (strcmp(arr[y].token_name, "(") == 0)
                            {
                                 int co = 0;
                                while (strcmp(arr[++y].token_name, ")") != 0)
                                {
                                    if (strcmp(arr[y].tokentype, "var") == 0 || strcmp(arr[y].token_name,"str")==0)
                                    {
                                        co++;
                                        
                                    }
                                    
                                }
                               
                                temp->item.args = co;
                                strcpy(temp->item.returntype, buf);
                                ptr->next = temp;
                            }
                        }
                        

                        
                    }
                    
                    s++;
                }
            }
        }
        else
        {
            arr[num++] = t;
            count = num;
            continue;
        }
    }
    for (int x = 1; x < *id; x++)
    {
        for (int u = 0; u < 10; u++)
        {

            ptr = list + u;
            while (ptr != NULL)
            {
                if (ptr->item.index == x)
                {
                    printf("\n%d\t%s\t%s\t%s\t%s\t%d", ptr->item.index, ptr->item.token_name, ptr->item.returntype, ptr->item.datatype, ptr->item.tokentype, ptr->item.args);
                    break;
                }
                ptr = ptr->next;
            }
        }
    }
    return 0;
}
