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
int sum=0,i=0;

while(i < d->n){
	sum=d->start+sum;
	d->start++;
	i++;
}
return (void *)sum;
}
int main()
{
	int num;
	printf("Enter num: ");
	scanf("%d",&num);
pthread_t thread[2];
int return_value[2];
for ( int i=0; i<2; i++ )
{
	data *d=(data*)malloc(sizeof(data));
d->n=num/2;
d->start=d->n*i+1;
pthread_create( &thread[i], 0, &child_thread, (void*)d );
}
for ( int i=0; i<2; i++ )
{
pthread_join( thread[i], (void**)&return_value[i] );
}

int sum=0;
for(int i=0;i<2;i++){
	//printf("%d\t",return_value[i]);
	sum+=return_value[i];
}
printf("%d",sum);
}