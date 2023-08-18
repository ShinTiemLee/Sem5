#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
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
struct sockaddr_in address;
sd=socket(AF_INET,SOCK_DGRAM,0);
address.sin_family=AF_INET;
address.sin_addr.s_addr=inet_addr("127.0.0.1");//**
address.sin_port=htons(9704);
int len=sizeof(address);
ex1 t;
int *temp;
int n,m;
printf("Enter n and m of matrix:\n");
scanf("%d",&n);
scanf("%d",&m);
sendto(sd,&n,sizeof(n),0,(struct sockaddr *)&address, len);
sendto(sd,&m,sizeof(m),0,(struct sockaddr *)&address, len);

temp=malloc(m*sizeof(int));
for(int i=0;i<n;i++){
	printf("\nEnter row:%d\n",i);
	for(int j=0;j<m;j++){
		scanf("%d",&temp[j]);
	}
	sendto(sd,temp,sizeof(temp),0,(struct sockaddr *)&address, len);
}
recvfrom(sd,&t,sizeof(t),0,(struct sockaddr *)&address,&len);
printf("the server matrix is:\n");
for(int i=0;i<n;i++){
	for(int j=0;j<m;j++){
		printf("%d ",t.arr[i][j]);
	}
	printf("\n"); 
}
return 0;
}