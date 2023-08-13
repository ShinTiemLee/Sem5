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
typedef struct
{
    int buf[256];
    int size;
    int pid;
} ex1;
int main()
{
    int len, size, result, sockfd, n = 1;
    struct sockaddr_in address;
    ex1 t;
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
    // You can now read and write via sockfd (Logic for problem mentioned here)
    printf("\nENTER size\t");
    scanf("%d", &(t.size));
    for (int i = 0; i < t.size; i++)
    {
        scanf("%d", &t.buf[i]);
    }
    write(sockfd, &t, sizeof(ex1));
    printf("ARRAY SENT BACK FROM SERVER IS ..... ");
    while (n)
    {
        n = read(sockfd, &t, sizeof(t));
    }
    for (int i = 0; i < t.size; i++)
    {
        printf(" %d ", t.buf[i]);
    }
    printf(" process id = %d ", t.pid);
}
