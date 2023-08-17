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
            n = read(newsockfd, buf, sizeof(buf));
            if (strcmp(buf, "yes") == 0)
            {
                ticks = time(NULL);
                pid = getpid();
                n = write(newsockfd, &ticks, sizeof(time_t));
                n = write(newsockfd, &pid, sizeof(pid));
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