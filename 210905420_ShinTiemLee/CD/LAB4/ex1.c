#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct t
{
    char name[100];
    char id[10];
    int r;
    int c;
} TOKEN;

typedef struct node
{
    int index;
    char name[100];
    char data_type[50];
    char token_type[50];
    char return_type[50];
    int aug;
    struct node *next;
} NODE;

char keywords[][50] = {"void", "int", "float", "char", "double", "break", "if", "while", "do", "else", "continue", "static"};

int hash(char buf[])
{
    int i = 0, sum = 0;
    while (buf[i] != '\0')
    {
        sum += buf[i];
        i++;
    }
    return sum % 10;
}
int checklist(char buf[], char **list)
{

    if (!list[0])
    {
        list[0] = (char *)malloc(sizeof(char) * 50);
        strcpy(list[0], buf);
        return -1;
    }
    else
    {
        int p = 0;
        while (list[p])
        {
            if (strcmp(list[p], buf) == 0)
            {

                return p + 1;
            }
            p++;
        }

        list[p] = (char *)malloc(sizeof(char) * 50);
        strcpy(list[p], buf);
        return -1;
    }
}

int checkkey(char buf[])
{
    for (int p = 0; p < 12; p++)
    {
        if (strcmp(keywords[p], buf) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int symboltable(NODE *ll[], TOKEN t[], int c)
{
    static int in = 1;
    char buf[50];
    for (int i = 0; i < c; i++)
    {
        if (t[i].name[0] == '\0' || strcmp(t[i].name, "symbol") == 0 || strcmp(t[i].name, "operator") == 0)
            continue;
        else if (strcmp(t[i].id, "str") == 0 || strcmp(t[i].id, "num") == 0)
        {
            continue;
        }
        else if (checkkey(t[i].name))
        {
            strcpy(buf, t[i].name);
        }
        else
        {
            int hashkey = hash(t[i].name);
            NODE *ptr = ll[hashkey];
            if (!ptr)
            {
                ptr = (NODE *)malloc(sizeof(NODE));
                ptr->next = NULL;
            }
            else
            {
                while (ptr->next)
                {
                    if (strcmp(ptr->name, t[i].name) == 0)
                    {
                        break;
                    }
                    ptr = ptr->next;
                }
                if (strcmp(ptr->name, t[i].name) == 0)
                    continue;
            }

            NODE *temp = (NODE *)malloc(sizeof(NODE));
            temp->index = in++;
            if (strcmp(t[i + 1].id, "(") == 0)
            {
                strcpy(temp->name, t[i].name);
                strcpy(temp->return_type, buf);
                strcpy(temp->token_type, "func");
                strcpy(temp->data_type, "-");
                int x = 1, count = 1;
                if (strcmp(t[i + 1].id, ")") == 0)
                    count = 0;
                while (strcmp(t[i + x].id, ")") != 0)
                {
                    if (strcmp(t[i + x].id, ",") == 0)
                        count++;
                    x++;
                }
                temp->aug = count;
                temp->next = NULL;
                ptr->next = temp;
            }
            else
            {
                strcpy(temp->name, t[i].name);
                strcpy(temp->return_type, "-");
                strcpy(temp->token_type, "var");
                strcpy(temp->data_type, buf);
                temp->aug = -1;
                temp->next = NULL;
                ptr->next = temp;
            }
        }
    }
    return in - 1;
}

TOKEN getnexttoken(FILE *fa, char **list)
{
    char c, ca;
    static int i = 1, j = 1, index = 1;
    TOKEN temp;

    c = fgetc(fa);
    if (c == EOF)
    {
        strcpy(temp.name, "EOF");
        return temp;
    }
    // remove preprocessor directives
    if (c == '#')
    {
        while (c != '\n')
        {
            c = fgetc(fa);
        }
        i++;
        j = 1;
        temp.name[0] = '\0';
        return temp;
    }
    // remove comments; operators:/=,/
    if (c == '/')
    {
        ca = fgetc(fa);
        if (ca == '/')
        {
            while (ca != '\n')
            {
                ca = fgetc(fa);
            }
            i++;
            j = 1;
            temp.name[0] = '\0';
            return temp;
        }
        else if (ca == '*')
        {
            while (c != '*')
            {
                c = fgetc(fa);
                if (c == '\n')
                {
                    i++;
                    j = 1;
                }
                if (c == '*')
                {
                    ca = fgetc(fa);
                    if (ca == '/')
                        break;
                }
            }
            temp.name[0] = '\0';
            return temp;
        }
        else if (ca == '=')
        {
            strcpy(temp.name, "operator");
            strcpy(temp.id, "/=");
            temp.r = i;
            temp.c = j;
            j += 2;
            return temp;
        }
        else
        {
            fseek(fa, -1, SEEK_CUR);
            strcpy(temp.name, "operator");
            strcpy(temp.id, "/");
            temp.r = i;
            temp.c = j;
            j += 1;
            return temp;
        }
    }

    if (c == '\n' || c == '\r')
    {
        i++;
        j = 1;
        temp.name[0] = '\0';
        return temp;
    }
    if (c == ' ')
    {
        j++;
        temp.name[0] = '\0';
        return temp;
    }
    // operators:==,=
    if (c == '=')
    {
        ca = fgetc(fa);
        if (ca == '=')
        {
            strcpy(temp.name, "operator");
            strcpy(temp.id, "==");
            temp.r = i;
            temp.c = j;
            j += 2;
            return temp;
        }
        else
        {
            fseek(fa, -1, SEEK_CUR);
            strcpy(temp.name, "operator");
            strcpy(temp.id, "=");
            temp.r = i;
            temp.c = j;
            j += 1;
            return temp;
        }
    }
    // operators:++,+=,+
    if (c == '+')
    {
        ca = fgetc(fa);
        if (ca == '+')
        {
            strcpy(temp.name, "operator");
            strcpy(temp.id, "++");
            temp.r = i;
            temp.c = j;
            j += 2;
            return temp;
        }
        else if (ca == '=')
        {
            strcpy(temp.name, "operator");
            strcpy(temp.id, "+=");
            temp.r = i;
            temp.c = j;
            j += 2;
            return temp;
        }
        else
        {
            fseek(fa, -1, SEEK_CUR);
            strcpy(temp.name, "operator");
            strcpy(temp.id, "+");
            temp.r = i;
            temp.c = j;
            j += 1;
            return temp;
        }
    }

    // operators:--,-=,-
    if (c == '-')
    {
        ca = fgetc(fa);
        if (ca == '-')
        {
            strcpy(temp.name, "operator");
            strcpy(temp.id, "--");
            temp.r = i;
            temp.c = j;
            j += 2;
            return temp;
        }
        else if (ca == '=')
        {
            strcpy(temp.name, "operator");
            strcpy(temp.id, "-=");
            temp.r = i;
            temp.c = j;
            j += 2;
            return temp;
        }
        else
        {
            fseek(fa, -1, SEEK_CUR);
            strcpy(temp.name, "operator");
            strcpy(temp.id, "-");
            temp.r = i;
            temp.c = j;
            j += 1;
            return temp;
        }
    }
    // operators:*,*=
    if (c == '*')
    {
        ca = fgetc(fa);
        if (ca == '=')
        {
            strcpy(temp.name, "operator");
            strcpy(temp.id, "*=");
            temp.r = i;
            temp.c = j;
            j += 2;
            return temp;
        }
        else
        {
            fseek(fa, -1, SEEK_CUR);
            strcpy(temp.name, "operator");
            strcpy(temp.id, "*");
            temp.r = i;
            temp.c = j;
            j += 1;
            return temp;
        }
    }
    // operators:|,||
    if (c == '|')
    {
        ca = fgetc(fa);
        if (ca == '|')
        {
            strcpy(temp.name, "operator");
            strcpy(temp.id, "||");
            temp.r = i;
            temp.c = j;
            j += 2;
            return temp;
        }
        else
        {
            fseek(fa, -1, SEEK_CUR);
            strcpy(temp.name, "operator");
            strcpy(temp.id, "|");
            temp.r = i;
            temp.c = j;
            j += 1;
            return temp;
        }
    }
    // operators:&,&&
    if (c == '&')
    {
        ca = fgetc(fa);
        if (ca == '&')
        {
            strcpy(temp.name, "operator");
            strcpy(temp.id, "&&");
            temp.r = i;
            temp.c = j;
            j += 2;
            return temp;
        }
        else
        {
            fseek(fa, -1, SEEK_CUR);
            strcpy(temp.name, "operator");
            strcpy(temp.id, "&");
            temp.r = i;
            temp.c = j;
            j += 1;
            return temp;
        }
    }
    // operators:%,%=
    if (c == '%')
    {
        ca = fgetc(fa);
        if (ca == '=')
        {
            strcpy(temp.name, "operator");
            strcpy(temp.id, "%=");
            temp.r = i;
            temp.c = j;
            j += 2;
            return temp;
        }
        else
        {
            fseek(fa, -1, SEEK_CUR);
            strcpy(temp.name, "operator");
            strcpy(temp.id, "%");
            temp.r = i;
            temp.c = j;
            j += 1;
            return temp;
        }
    }
    // operators:!,!=
    if (c == '!')
    {
        ca = fgetc(fa);
        if (ca == '=')
        {
            strcpy(temp.name, "operator");
            strcpy(temp.id, "!=");
            temp.r = i;
            temp.c = j;
            j += 2;
            return temp;
        }
        else
        {
            fseek(fa, -1, SEEK_CUR);
            strcpy(temp.name, "operator");
            strcpy(temp.id, "!");
            temp.r = i;
            temp.c = j;
            j += 1;
            return temp;
        }
    }
    // symbols
    if (c == ',')
    {
        strcpy(temp.name, "symbol");
        strcpy(temp.id, ",");
        temp.r = i;
        temp.c = j;
        j += 1;
        return temp;
    }
    if (c == ';')
    {
        strcpy(temp.name, "symbol");
        strcpy(temp.id, ";");
        temp.r = i;
        temp.c = j;
        j += 1;
        return temp;
    }
    // brackets
    if (c == '(')
    {
        strcpy(temp.name, "symbol");
        strcpy(temp.id, "(");
        temp.r = i;
        temp.c = j;
        j += 1;
        return temp;
    }
    if (c == ')')
    {
        strcpy(temp.name, "symbol");
        strcpy(temp.id, ")");
        temp.r = i;
        temp.c = j;
        j += 1;
        return temp;
    }
    if (c == '[')
    {
        strcpy(temp.name, "symbol");
        strcpy(temp.id, "[");
        temp.r = i;
        temp.c = j;
        j += 1;
        return temp;
    }
    if (c == ']')
    {
        strcpy(temp.name, "symbol");
        strcpy(temp.id, "]");
        temp.r = i;
        temp.c = j;
        j += 1;
        return temp;
    }
    if (c == '{')
    {
        strcpy(temp.name, "symbol");
        strcpy(temp.id, "{");
        temp.r = i;
        temp.c = j;
        j += 1;
        return temp;
    }
    if (c == '}')
    {
        strcpy(temp.name, "symbol");
        strcpy(temp.id, "}");
        temp.r = i;
        temp.c = j;
        j += 1;
        return temp;
    }
    // string
    if (c == '\"')
    {
        char buf[100];
        int p = 0;
        buf[p++] = c;
        c = fgetc(fa);
        while (c != '\"')
        {
            buf[p++] = c;
            c = fgetc(fa);
        }
        buf[p++] = '\"';
        buf[p] = '\0';
        strcpy(temp.name, buf);
        strcpy(temp.id, "str");
        temp.r = i;
        temp.c = j;
        j += p;
        return temp;
    }

    if (c == '\'')
    {
        char buf[100];
        int p = 0;
        buf[p++] = c;
        c = fgetc(fa);
        while (c != '\'')
        {
            buf[p++] = c;
            c = fgetc(fa);
        }
        buf[p++] = '\'';
        buf[p] = '\0';
        strcpy(temp.name, buf);
        strcpy(temp.id, "str");
        temp.r = i;
        temp.c = j;
        j += p;
        return temp;
    }

    // numbers
    if (isdigit(c))
    {
        char buf[50];
        int p = 0;
        while (isdigit(c) || c == '.')
        {
            if (isdigit(c))
                buf[p++] = c + '0';
            else
                buf[p++] = c;
            c = fgetc(fa);
        }
        buf[p] = '\0';
        fseek(fa, -1, SEEK_CUR);
        strcpy(temp.name, buf);
        strcpy(temp.id, "num");
        temp.r = i;
        temp.c = j;
        j += p;
        return temp;
    }

    // var,func
    if (isalpha(c))
    {
        char buf[50];
        int p = 0;
        while (isalpha(c) || c == '_')
        {
            buf[p++] = c;
            c = fgetc(fa);
        }
        buf[p] = '\0';

        fseek(fa, -1, SEEK_CUR);
        strcpy(temp.name, buf);
        if (checkkey(buf))
        {
            strcpy(temp.id, buf);
            temp.r = i;
            temp.c = j;
            j += p;
            return temp;
        }
        int chk = checklist(temp.name, list);
        if (chk != -1)
            sprintf(temp.id, "id%d", chk);
        else
            sprintf(temp.id, "id%d", index++);
        temp.r = i;
        temp.c = j;
        j += p;
        return temp;
    }
}

void printtoken(TOKEN t[], int c)
{
    for (int i = 0; i < c; i++)
    {
        if (i != 0)
        {
            if (t[i - 1].r != t[i].r)
                printf("\n");
        }
        printf("<%s,%d,%d>", t[i].id, t[i].r, t[i].c);
    }
}

void printsymboltable(NODE *ll[], int k)
{
    printf("\n| Index | Lexeme name | Return type |   Data type |  Token type | Number of args|\n");
    NODE *ptr;
    for (int i = 1; i <= k; i++)
    {
        for (int j = 0; j < 10; j++)
        {

            ptr = ll[j];
            while (ptr)
            {
                if (ptr->index == i)
                {
                    printf("%d\t\t%s\t\t%s\t\t%s\t\t%s\t\t%d\n", ptr->index, ptr->name, ptr->return_type, ptr->data_type, ptr->token_type, ptr->aug);
                }
                ptr = ptr->next;
            }
        }
    }
}

int main()
{
    char **list = (char **)malloc(50 * sizeof(char *));
    TOKEN t[200];
    TOKEN temp;
    int c = 0;
    FILE *fa = fopen("digit.c", "r");
    temp = getnexttoken(fa, list);
    while (strcmp(temp.name, "EOF") != 0)
    {
        if (temp.name[0] != '\0')
        {
            t[c++] = temp;
        }
        temp = getnexttoken(fa, list);
    }
    printtoken(t, c);
    NODE *ll[10];
    for (int i = 0; i < 10; i++)
    {
        ll[i] = (NODE *)malloc(sizeof(NODE));
    }
    int k = symboltable(ll, t, c);
    printsymboltable(ll, k);
}
