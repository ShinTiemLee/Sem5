#include <pthread.h>
#include <stdio.h>
#include<stdlib.h>
typedef struct data{
	int *arr;
	int n;
}data;

void* child_thread( void * param )
{
data *d = (data*)param;
int sum=0;

if(d->n==0){
	for(int i=0;i<10;i++){
		if(d->arr[i]%2==0)
			sum+=d->arr[i];
	}
}
else{
	for(int i=0;i<10;i++){
		if(d->arr[i]%2==1)
			sum+=d->arr[i];
	}
}
return (void *)sum;
}
int main()
{
pthread_t thread[2];
int return_value[2];
int a[10]={1,2,3,4,5,6,7,8,9,10};

data *d=(data*)malloc(sizeof(data));
d->arr=a;

d->n=0;
pthread_create( &thread[0], 0, &child_thread, (void*)d );


pthread_join( thread[0], (void**)&return_value[0] );
d=(data*)malloc(sizeof(data));
d->arr=a;
d->n=1;
pthread_create( &thread[1], 0, &child_thread, (void*)d );


pthread_join( thread[1], (void**)&return_value[1] );


int sum=0;
for(int i=0;i<2;i++){
	//printf("%d\t",return_value[i]);
	sum+=return_value[i];
}
printf("%d",sum);
}