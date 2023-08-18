#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
int main()
{
int sd,p=0;
char buf[100],temp[100];
char str[5000];
struct sockaddr_in sadd,cadd;
//Create a UDP socket
sd=socket(AF_INET,SOCK_DGRAM,0);
//Construct the address for use with sendto/recvfrom... */
sadd.sin_family=AF_INET;
sadd.sin_addr.s_addr=inet_addr("127.0.0.1");//**
sadd.sin_port=htons(9704);
int result=bind(sd,(struct sockaddr *)&sadd,sizeof(sadd));
int len=sizeof(cadd);
int m=recvfrom(sd,buf,sizeof(buf),0,(struct sockaddr *)&cadd,&len);
strcpy(temp,"echo -en \'");
strcat(temp,buf);
strcat(temp," | nc ");
recvfrom(sd,buf,sizeof(buf),0,(struct sockaddr *)&cadd,&len);
strcat(temp,buf);
strcat(temp," 80 > sample.txt");
system(str);
FILE *fp;
fp=fopen("samle.txt","r");
char c;
c=fgetc(fp);
while(c!=EOF){
	str[p]=c;
	c=fgetc(fp);
}
puts(str);
int n=sendto(sd,str,sizeof(str),0,(struct sockaddr *)&cadd,len);
return 0;
}