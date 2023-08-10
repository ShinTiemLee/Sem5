#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <ctype.h>
#define PORTNO 10200

void dup(char *buf)
{
    char word[50];
    int i = 0, j = 0, k = 0, count = 1, x, flag = 0, p;
    while (buf[i] != '\0')
    {
        while (isalpha(buf[i]))
        {
            word[j] = buf[i];
            i++;
            j++;
            word[j] = '\0';
        }
        puts(word);
        k = 0;
        x = i;
        while (buf[x] != '\0')
        {
            while (word[k] == buf[x])
            {
                if (k == j - 1 && !(isalpha(buf[x + 1])))
                {
                    count++;
                    p = x + 1;
                    while (buf[p] != '\0')
                    {
                        buf[p - k - 1] = buf[p];
                        p++;
                    }
                    buf[p - k - 1] = '\0';
                    flag = 1;
                    break;
                }
                printf(" %d %d ", k, x);
                k++;
                x++;
            }
            x++;
        }
        if (flag == 1)
        {
            printf("%s : %d", word, count);
            count = 1;
        }
        flag = 0;
        j = 0;
        i++;
    }
    puts(buf);
}

int main()
{

    char temp[256] = "hi hi how are you how";
    dup(temp);
}