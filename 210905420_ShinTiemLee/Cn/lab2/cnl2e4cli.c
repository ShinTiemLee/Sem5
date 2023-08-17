// ShinTiemLee-210905420
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
int main()
{
    int len, result, sockfd, n = 1, pid;
    struct sockaddr_in address;
    time_t ticks;
    char buf[256];
    // Create a socket for the client
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // Name the socket as agreed with the server
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1"); //**
    address.sin_port = htons(10200);
    len = sizeof(address);
    // Connect your socket to the server’s socket
    result = connect(sockfd, (struct sockaddr *)&address, len);
    if (result == -1)
    {
        perror("\nCLIENT ERROR");
        exit(1);
    }
    while (1)
    {
        // You can now read and write via sockfd (Logic for problem mentioned here)
        printf("\nENTER string:\t");
        gets(buf);
        if (strcmp(buf, "Stop") == 0)
            exit(0);
        n = write(sockfd, buf, sizeof(buf));
        printf("STRING FROM SERVER IS ..... ");

        read(sockfd, buf, sizeof(buf));

        printf("\n%s", buf);
    }
    return 0;
}