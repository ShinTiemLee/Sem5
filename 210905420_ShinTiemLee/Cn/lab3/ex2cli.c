#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
int main()
{
    int sd, n, result;
    char buf[10000];
    struct sockaddr_in address;
    sd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("142.250.190.142");
    address.sin_port = htons(80);
    int len = sizeof(address);
    result = connect(sd, (struct sockaddr *)&address, len);
    if (result == -1)
    {
        perror("\nCLIENT ERROR");
        exit(1);
    }
    char req[] = "GET /index.html HTTP/1.1\r\n\r\n";

    write(sd, req, strlen(req));

    n = read(sd, buf, sizeof(buf));

    printf("Received : %s", buf);
    return 0;
}
