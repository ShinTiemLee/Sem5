#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
typedef struct{
int arr[10][10];
}ex1; 
int main()
{
int sd;
int n,m;
ex1 t;
struct sockaddr_in sadd,cadd;
//Create a UDP socket
sd=socket(AF_INET,SOCK_DGRAM,0);
//Construct the address for use with sendto/recvfrom... */
sadd.sin_family=AF_INET;
sadd.sin_addr.s_addr=inet_addr("127.0.0.1");//**
sadd.sin_port=htons(9704);
int result=bind(sd,(struct sockaddr *)&sadd,sizeof(sadd));
int len=sizeof(cadd);
recvfrom(sd,&n,sizeof(n),0,(struct sockaddr *)&cadd,&len);
recvfrom(sd,&m,sizeof(m),0,(struct sockaddr *)&cadd,&len);

for(int i=0;i<n;i++){
	recvfrom(sd,t.arr[i],sizeof(t.arr[i]),0,(struct sockaddr *)&cadd,&len);
}
for(int i=0;i<n;i++){
	for(int j=0;j<m;j++){
		printf("%d ",t.arr[i][j]);
	}
	printf("\n"); 
}
sendto(sd,&t,sizeof(t),0,(struct sockaddr *)&cadd,len);
return 0;
}