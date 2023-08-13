#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <ctype.h>
#define PORTNO 10200
int main()
{
    int sockfd, newsockfd, portno, clilen, n = 1;
    struct sockaddr_in seraddr, cliaddr;
    int i, value;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // Name the socket
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("172.21.87.167"); // **
    seraddr.sin_port = htons(PORTNO);
    bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
    // Create a connection queue and wait for clients
    listen(sockfd, 5);
    while (1)
    {
        char buf[256], word[50];
        printf("server waiting");
        // Accept a connection
        clilen = sizeof(clilen);
        newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
        // Read and write to client on client_sockfd (Logic for problem mentioned here)
        n = read(newsockfd, buf, sizeof(buf));
        buf[strlen(buf)] = '\0';
        if (strcmp("Stop", buf) == 0)
        {
            exit(0);
        }
        int count = 1, i = 0;
        while (buf[i] != '\0')
        {
            if (buf[i] == ' ' || buf[i] == '\t')
            {
                i++;
                continue;
            }
            int k = 0, x;
            while (isalpha(buf[i]))
            {
                word[k] = buf[i];
                k++;
                i++;
            }
            word[k] = '\0';
            int p = i;
            while (buf[p] != '\0')
            {
                int j = 0;
                while (buf[p] == word[j])
                {
                    if (j == (k - 1) && (buf[p + 1] == ' ' || buf[p + 1] == '\0'))
                    {
                        count++;
                        for (x = p + 1; x < strlen(buf); x++)
                        {
                            buf[x - k] = buf[x];
                        }
                        buf[x] = '\0';
                        printf(" %s ", buf);
                    }
                    printf(" %d %d %d %d %d ", j, p, x, k, i);
                    j++;
                    p++;
                }
                p++;
            }
            printf("%s : %d", word, count);
            count = 1;
        }

        printf(" \nMessage from Client %s \n", buf);
        n = write(newsockfd, buf, sizeof(buf));
    }
}