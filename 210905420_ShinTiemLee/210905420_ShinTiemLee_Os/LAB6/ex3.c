#include <pthread.h>
#include <stdio.h>
#include<stdlib.h>
typedef struct data{
	int start;
	int n;
}data;

void* child_thread( void * param )
{
data *d = (data*)param;
int i=d->start;
int flag=1;
while(i <= d->n){
	flag=1;
	for(int j=2;j<i;j++){
	if(i%j==0){
		flag=0;
		break;
	}
}
if (flag==1){
	printf("%d\t",i);
}

	i++;
}
return;
}
int main()
{
	int num;
	printf("Enter num: ");
	scanf("%d",&num);
pthread_t thread[2];
int return_value[2];
data *d=(data*)malloc(sizeof(data));
d->n=num/2;
d->start=2;
pthread_create( &thread[0], 0, &child_thread, (void*)d );
pthread_join( thread[0],0 );
d=(data*)malloc(sizeof(data));
d->n=num;
d->start=num/2+1;
pthread_create( &thread[1], 0, &child_thread, (void*)d );
pthread_join( thread[1], 0 );


}