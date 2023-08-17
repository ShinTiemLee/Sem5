// ShiTiemLee-210905420
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#define PORTNO 10200
void dupe(char *str)
{
    char twoD[20][30];
    int i = 0, j = 0, k = 0, len1 = 0, len2 = 0, l = 0;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ' ')
        {
            twoD[k][j] = '\0';
            k++;
            j = 0;
        }
        else
        {
            twoD[k][j] = str[i];
            j++;
        }
    }

    twoD[k][j] = '\0';

    j = 0;
    for (i = 0; i < k; i++)
    {
        int present = 0;
        for (l = 1; l < k + 1; l++)
        {
            if (twoD[l][j] == '\0' || l == i)
            {
                continue;
            }

            if (strcmp(twoD[i], twoD[l]) == 0)
            {
                twoD[l][j] = '\0';
                present = present + 1;
            }
        }
        if (twoD[i][j] == '\0')
            continue;
        else
            printf(" %s : %d ", twoD[i], present);
    }

    j = 0;
    strcpy(str, "\0");
    for (i = 0; i < k + 1; i++)
    {
        if (twoD[i][j] == '\0')
            continue;
        else
            strcat(str, twoD[i]);
        strcat(str, " ");
    }
    puts(str);
}
int main()
{
    char buf[256];
    int sockfd, newsockfd, portno, clilen, n = 1, pid;
    struct sockaddr_in seraddr, cliaddr;
    int i, value;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //**
    seraddr.sin_port = htons(PORTNO);
    bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
    // Create a connection queue, ignore child exit details, and wait for clients
    listen(sockfd, 5);
    // Accept the connection
    while (1)
    {
        clilen = sizeof(clilen);
        newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
        time_t ticks;
        // Fork to create a process for this client and perform a test to see whether
        // you’re the parent or the child:
        if (fork() == 0)
        {
            // If you’re the child, you can now read/write to the client on newsockfd.
            while (1)
            {
                n = read(newsockfd, buf, sizeof(buf));
                if (strcmp("Stop", buf) != 0)
                {
                    dupe(buf);
                }
                else
                    exit(0);
                write(newsockfd, buf, sizeof(buf));
            }
            close(newsockfd);
            exit(0);
        }
        // Otherwise, you must be the parent and your work for this client is finished
        else
        {
            printf(" %d ", getpid());
        }
        close(newsockfd);
    }
}