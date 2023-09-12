#include <pthread.h>
#include <stdio.h>
#include<stdlib.h>
typedef struct data{
	int return_value[100];
	int n;
}data;
void* child_thread( void * param )
{
	printf( "Start child thread\n" );
data *d=(data*)param;
int start=0,next=1,temp=0;
int i=0;
while(i<d->n){
if(i==0)
	d->return_value[i++]=next;
else{
    temp=next;
    next+=start;
	d->return_value[i++]=next;
	start=temp;
	}
}


return (void*)d;
}


int main(int argc,char*argv[])
{
pthread_t thread;
data *d=(data*)malloc(sizeof(data));
d->n=atoi(argv[1]);
pthread_create( &thread, 0, &child_thread, (void*)d);
pthread_join( thread, 0);

for(int i=0;i<d->n;i++){
	printf("\t%d",d->return_value[i]);
}


}