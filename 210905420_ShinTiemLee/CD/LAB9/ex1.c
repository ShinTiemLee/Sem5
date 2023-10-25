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

TOKEN t[500];
int c = 0;
void invalid()
{
    printf("-----------------ERROR!----------------\n");
}

void valid()
{
    printf("----------------SUCCESS!---------------\n");
    exit(0);
}
void Program();
void declarations();
void identifier_list();
void identifier_list_prime();
void identifier_list_prime2();
void assign_stat();
void statement_list();
void statement();
void data_type();
void expn();
void eprime();
void simple_exp();
void seprime();
void term();
void tprime();
void factor();
void relop();
void addop();
void mulop();
void decision_stat();
void looping_stat();

TOKEN getnexttoken(FILE *fa);

void Program()
{
    if (strcmp(t[c++].name, "main") == 0)
    {

        if (strcmp(t[c++].id, "(") == 0)
        {
            if (strcmp(t[c++].id, ")") == 0)
            {
                if (strcmp(t[c++].id, "{") == 0)
                {
                    declarations();

                    statement_list();

                    if (strcmp(t[c++].id, "}") == 0)
                    {

                        if (strcmp(t[c++].name, "EOF") == 0)
                            valid();
                        else
                        {
                            invalid();
                            printf("row:%d col:%d\t Expected: EOF", t[c - 1].r, t[c - 1].c);
                            exit(0);
                        }
                    }
                    else
                    {
                        invalid();
                        printf("row:%d col:%d\t Expected: }", t[c - 1].r, t[c - 1].c);
                        exit(0);
                    }
                }
                else
                {
                    invalid();
                    printf("row:%d col:%d\t Expected: {", t[c - 1].r, t[c - 1].c);
                    exit(0);
                }
            }
            else
            {
                invalid();
                printf("row:%d col:%d\t Expected: )", t[c - 1].r, t[c - 1].c);
                exit(0);
            }
        }
        else
        {
            invalid();
            printf("row:%d col:%d\t Expected: (", t[c - 1].r, t[c - 1].c);
            exit(0);
        }
    }
    else
    {
        invalid();
        printf("row:%d col:%d\t Expected: main", t[c - 1].r, t[c - 1].c);
        exit(0);
    }
}

void declarations()
{
    if (strcmp(t[c].id, "int") == 0 || strcmp(t[c].id, "char") == 0)
    {
        data_type();
        identifier_list();
        if (strcmp(t[c++].id, ";") == 0)
        {
            declarations();
        }
        else
        {
            invalid();
            printf("row:%d col:%d\t Expected: ;", t[c - 1].r, t[c - 1].c);
            exit(0);
        }
    }
}

void identifier_list()
{
    if (strcmp(t[c++].id, "id") == 0)
    {
        identifier_list_prime();
    }
    else
    {
        invalid();
        printf("row:%d col:%d\t Expected: id", t[c - 1].r, t[c - 1].c);
        exit(0);
    }
}

void identifier_list_prime()
{

    if (strcmp(t[c].id, ",") == 0)
    {
        c++;
        identifier_list();
    }
    else if (strcmp(t[c].id, "[") == 0)
    {
        c++;
        if (strcmp(t[c++].id, "num") == 0)
        {
            if (strcmp(t[c++].id, "]") == 0)
            {
                identifier_list_prime2();
            }
            else
            {
                invalid();
                printf("row:%d col:%d\t Expected: ]", t[c - 1].r, t[c - 1].c);
                exit(0);
            }
        }
        else
        {
            invalid();
            printf("row:%d col:%d\t Expected: num", t[c - 1].r, t[c - 1].c);
            exit(0);
        }
    }
}

void identifier_list_prime2()
{
    if (strcmp(t[c].id, ",") == 0)
    {
        c++;
        identifier_list();
    }
}

void statement_list()
{
    if (strcmp(t[c].id, "id") == 0 || strcmp(t[c].id, "if") == 0 || strcmp(t[c].id, "for") == 0 || strcmp(t[c].id, "while") == 0)
    {
        statement();
        statement_list();
    }
}

void statement()
{
    if (strcmp(t[c].id, "id") == 0)
    {
        assign_stat();
        if (strcmp(t[c].id, ";") == 0)
        {
            c++;
        }
        else
        {
            invalid();
            printf("row:%d col:%d\t Expected: ;", t[c - 1].r, t[c - 1].c);
            exit(0);
        }
    }
    else if (strcmp(t[c].id, "if") == 0)
    {
        decision_stat();
    }
    else if (strcmp(t[c].id, "for") == 0 || strcmp(t[c].id, "while") == 0)
    {
        looping_stat();
    }
}

void assign_stat()
{
    if (strcmp(t[c++].id, "id") == 0)
    {
        if (strcmp(t[c++].id, "=") == 0)
            expn();
        else
        {
            invalid();
            printf("%s", t[c - 1].id);
            printf("row:%d col:%d\t Expected: =", t[c - 1].r, t[c - 1].c);
            exit(0);
        }
    }
    else
    {
        invalid();
        printf("row:%d col:%d\t Expected: id", t[c - 1].r, t[c - 1].c);
        // printf("%s",t[c-1].name);
        exit(0);
    }
}

void data_type()
{
    if (strcmp(t[c].id, "int") != 0 && strcmp(t[c].id, "char") != 0)
    {
        invalid();
        printf("row:%d col:%d\t Expected: int or char", t[c].r, t[c].c);
        exit(0);
    }
    else
    {
        c++;
    }
}

void expn()
{
    simple_exp();
    eprime();
}

void eprime()
{
    if (strcmp(t[c].name, "roperator") == 0)
    {
        relop();
        simple_exp();
    }
}

void simple_exp()
{
    term();
    seprime();
}

void seprime()
{
    if (strcmp(t[c].id, "+") == 0 || strcmp(t[c].id, "-") == 0)
    {
        addop();
        term();
        seprime();
    }
}

void term()
{
    factor();
    tprime();
}

void tprime()
{
    if (strcmp(t[c].id, "*") == 0 || strcmp(t[c].id, "/") == 0 || strcmp(t[c].id, "%") == 0)
    {
        mulop();
        factor();
        tprime();
    }
}

void factor()
{
    if (strcmp(t[c].id, "id") == 0 || strcmp(t[c].id, "num") == 0)
        c++;
    else
    {
        invalid();
        printf("row:%d col:%d\t Expected: id or num", t[c].r, t[c].c);
        exit(0);
    }
}

void relop()
{
    if (strcmp(t[c].id, "==") == 0)
        c++;
    else if (strcmp(t[c].id, "!=") == 0)
        c++;
    else if (strcmp(t[c].id, "<") == 0)
        c++;
    else if (strcmp(t[c].id, ">") == 0)
        c++;
    else if (strcmp(t[c].id, ">=") == 0)
        c++;
    else if (strcmp(t[c].name, "<=") == 0)
        c++;
    else
    {
        invalid();
        printf("row:%d col:%d\t Expected: relational operator", t[c].r, t[c].c);
        exit(0);
    }
}

void addop()
{
    if (strcmp(t[c].id, "+") != 0 && strcmp(t[c].id, "-") != 0)
    {
        invalid();
        printf("row:%d col:%d\t Expected: + or -", t[c].r, t[c].c);
    }
    else
        c++;
}

void mulop()
{
    if (strcmp(t[c].id, "*") != 0 && strcmp(t[c].id, "/") != 0 && strcmp(t[c].id, "%") != 0)
    {
        invalid();
        printf("row:%d col:%d\t Expected: * or / or modulus", t[c].r, t[c].c);
    }
    else
        c++;
}

void decision_stat()
{
    if (strcmp(t[c++].id, "if") == 0)
    {
        if (strcmp(t[c++].id, "(") == 0)
        {
            expn();
            if (strcmp(t[c++].id, ")") == 0)
            {
                if (strcmp(t[c++].id, "{") == 0)
                {
                    statement_list();
                    if (strcmp(t[c++].id, "}") != 0)
                    {
                        invalid();
                        printf("row:%d col:%d\t Expected: }", t[c - 1].r, t[c - 1].c);
                        exit(0);
                    }
                    // if(strcmp(t[c++].id,"}")==0){
                    // dprime();
                    // }
                    // else{
                    // invalid();
                    // printf("row:%d col:%d\t Expected: }", t[c-1].r, t[c-1].c);
                    // exit(0);
                    //}
                }
                else
                {
                    invalid();
                    printf("row:%d col:%d\t Expected: {", t[c - 1].r, t[c - 1].c);
                    exit(0);
                }
            }
            else
            {
                invalid();
                printf("row:%d col:%d\t Expected: )", t[c - 1].r, t[c - 1].c);
                exit(0);
            }
        }
        else
        {
            invalid();
            printf("row:%d col:%d\t Expected: (", t[c - 1].r, t[c - 1].c);
            exit(0);
        }
    }
    else
    {
        invalid();
        printf("row:%d col:%d\t Expected: if", t[c - 1].r, t[c - 1].c);
        exit(0);
    }
}

void looping_stat()
{
    if (strcmp(t[c].id, "while") == 0)
    {
        c++;
        if (strcmp(t[c++].id, "(") == 0)
        {
            expn();
            if (strcmp(t[c++].id, ")") == 0)
            {
                if (strcmp(t[c++].id, "{") == 0)
                {
                    statement_list();
                    if (strcmp(t[c++].id, "}") != 0)
                    {
                        invalid();
                        printf("row:%d col:%d\t Expected: }", t[c - 1].r, t[c - 1].c);
                        exit(0);
                    }
                }
                else
                {
                    invalid();
                    printf("row:%d col:%d\t Expected: {", t[c - 1].r, t[c - 1].c);
                    exit(0);
                }
            }
            else
            {
                invalid();
                printf("row:%d col:%d\t Expected: )", t[c - 1].r, t[c - 1].c);
                exit(0);
            }
        }
        else
        {
            invalid();
            printf("row:%d col:%d\t Expected: (", t[c - 1].r, t[c - 1].c);
            exit(0);
        }
    }
    else if (strcmp(t[c].id, "for") == 0)
    {
        c++;
        if (strcmp(t[c++].id, "(") == 0)
        {
            assign_stat();
            if (strcmp(t[c++].id, ";") == 0)
            {
                expn();
                if (strcmp(t[c++].id, ";") == 0)
                {
                    assign_stat();
                    if (strcmp(t[c++].id, ")") != 0)
                    {
                        invalid();
                        printf("row:%d col:%d\t Expected: )", t[c - 1].r, t[c - 1].c);
                        exit(0);
                    }
                }
                else
                {
                    invalid();
                    printf("row:%d col:%d\t Expected: ;", t[c - 1].r, t[c - 1].c);
                    exit(0);
                }
            }
            else
            {
                invalid();
                printf("row:%d col:%d\t Expected: ;", t[c - 1].r, t[c - 1].c);
                exit(0);
            }
        }
        else
        {
            invalid();
            printf("row:%d col:%d\t Expected: (", t[c - 1].r, t[c - 1].c);
            exit(0);
        }
    }
    else
    {
        invalid();
        printf("row:%d col:%d\t Expected: while or for", t[c].r, t[c].c);
        exit(0);
    }
}

char keywords[][50] = {"void", "int", "float", "char", "double", "break", "if", "while", "do", "else", "continue", "for"};

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

TOKEN getnexttoken(FILE *fa)
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

    if (c == '\n')
    {
        i++;
        j = 1;
        temp.name[0] = '\0';
        return temp;
    }
    if (c == '\r')
    {
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
            strcpy(temp.name, "roperator");
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
            strcpy(temp.name, "roperator");
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
    // operators:<,<=
    if (c == '<')
    {
        ca = fgetc(fa);
        if (ca == '=')
        {
            strcpy(temp.name, "roperator");
            strcpy(temp.id, "<=");
            temp.r = i;
            temp.c = j;
            j += 2;
            return temp;
        }
        else
        {
            fseek(fa, -1, SEEK_CUR);
            strcpy(temp.name, "roperator");
            strcpy(temp.id, "<");
            temp.r = i;
            temp.c = j;
            j += 1;
            return temp;
        }
    }
    // operators:>,>=
    if (c == '>')
    {
        ca = fgetc(fa);
        if (ca == '=')
        {
            strcpy(temp.name, "roperator");
            strcpy(temp.id, ">=");
            temp.r = i;
            temp.c = j;
            j += 2;
            return temp;
        }
        else
        {
            fseek(fa, -1, SEEK_CUR);
            strcpy(temp.name, "roperator");
            strcpy(temp.id, ">");
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
        else
            strcpy(temp.id, "id");

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
                    printf("%d\t%s\t\t%s\t\t%s\t\t%s\t\t%d\n", ptr->index, ptr->name, ptr->return_type, ptr->data_type, ptr->token_type, ptr->aug);
                }
                ptr = ptr->next;
            }
        }
    }
}

int main()
{
    TOKEN temp;
    FILE *fa = fopen("input.c", "r");
    temp = getnexttoken(fa);
    while (strcmp(temp.name, "EOF") != 0)
    {
        if (temp.name[0] != '\0')
        {
            t[c++] = temp;
        }
        temp = getnexttoken(fa);
    }
    t[c] = temp;
    c = 0;
    Program(t);
}
