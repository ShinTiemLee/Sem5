//ShiTiemLee-210905420
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#define PORTNO 10200
typedef struct{
	int buf[256];
	int size;
	int pid;
}ex1;
int main()
{
int sockfd,newsockfd,portno,clilen,n=1,p;
struct sockaddr_in seraddr,cliaddr;
int i,value;
sockfd = socket(AF_INET,SOCK_STREAM,0);
seraddr.sin_family = AF_INET;
seraddr.sin_addr.s_addr = inet_addr("172.16.59.43"); //**
seraddr.sin_port = htons(PORTNO);
bind(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr));
// Create a connection queue, ignore child exit details, and wait for clients
listen(sockfd,5);
ex1 *t=(ex1*)malloc(sizeof(ex1));
while(1){
//Accept the connection
clilen = sizeof(clilen);
newsockfd=accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);
//Fork to create a process for this client and perform a test to see whether
//you’re the parent or the child:
puts("no");
if(fork()==0){
puts("yes");
// If you’re the child, you can now read/write to the client on newsockfd.
n = read(newsockfd,t,sizeof(t));
printf(" \nArray from Client  \n");
puts("no");
for(p=0;p<t->size;p++){
	puts("yes");
	printf("\t%d ",t->buf[p]);
}
int i,j,temp;
	for(i=0;i<(t->size-1);i++){
		for(j=0;j<(t->size-1-i);j++){
			if(t->buf[j]>t->buf[j+1]){
				temp=t->buf[j+1];
				t->buf[j+1]=t->buf[j];
				t->buf[j]=temp;
			}
		}
	}
t->pid=getpid();
n = write(newsockfd,t,sizeof(t));
close(newsockfd);
exit(0);
}
//Otherwise, you must be the parent and your work for this client is finished
else{
	printf(" %d ",getpid());
}
close(newsockfd);
}
}