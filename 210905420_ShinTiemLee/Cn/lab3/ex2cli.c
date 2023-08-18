#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h> 
int main()
{
int sd;
struct sockaddr_in address;
sd=socket(AF_INET,SOCK_DGRAM,0);
address.sin_family=AF_INET;
address.sin_addr.s_addr=inet_addr("127.0.0.1");//**
address.sin_port=htons(9704);
int len=sizeof(address);
char buf[5000];
printf("Enter HTTP request:\n");
scanf("%s",buf);
sendto(sd,buf,sizeof(buf),0,(struct sockaddr *)&address, len);
printf("Enter website:\n");
scanf("%s",buf);
sendto(sd,buf,sizeof(buf),0,(struct sockaddr *)&address, len);

recvfrom(sd,buf,sizeof(buf),0,(struct sockaddr *)&address,&len);
printf("the server output is:\n");
puts(buf);
return 0;
}