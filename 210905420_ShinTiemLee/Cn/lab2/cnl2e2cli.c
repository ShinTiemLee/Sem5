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
    int a;
    int b;
    char op;
    int pid;
    int flag;
    float res;
} ex2;
int main()
{
    int len, result, sockfd, n = 1;
    struct sockaddr_in address;
    ex2 t;
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
    printf("\nENTER operand1:\t");
    scanf("%d", &(t.a));
    printf("\nENTER operator:\t");
    scanf(" %c", &(t.op));
    printf("\nENTER operand2:\t");
    scanf("%d", &(t.b));
    write(sockfd, &t, sizeof(ex2));
    printf("RESULT BACK FROM SERVER IS ..... ");
    t.flag = 1;
    while (n)
    {
        n = read(sockfd, &t, sizeof(ex2));
    }
    if (t.flag == 0)
    {
        printf("Error.Invalid operator!");
    }
    else
        printf(" %f ", t.res);
    printf(" process id = %d ", t.pid);
    return 0;
}