#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex;
typedef struct data{
	int allocation[10][10];
int max[10][10];
int available[10];
int finish[10];
int f;
int flag;
}data;

void* child_thread( void * param )
{
	sem_wait(&mutex);
	printf( "Start child thread\n" );
data *d=(data*)param;
for(int j=0;j<n;j++){

	if(d->available[j]<(d->max[i][j]-d->allocation[i][j])){		
		d->f=1;
	}
	
	}
	if(d->f==0){
		d->finish[i]=1;
		d->flag=0;
		for(int j=0;j<m;j++)
			d->available[j]+=d->allocation[i][j];	
	}
	sem_post(&mutex);
}
int checkstate(int num,int m,int n){
	pthread_t thread[m];
	int d->flag=0;
	int d->f=0;
	d->finish[num]=1;
	while(d->flag==0){
	d->flag=1;
	for(int i=0;i<m;i++){
	if(d->finish[i]==1)
		continue;
	else{
		pthread_create( &thread[i], 0, &child_thread, (void*)d);
	}
	}
}
for(int j=0;j<m;j++){
		if(d->finish[j]==0)
			return 0;

		printf("Safe state:\t");
		return 1;
}
}

int main(){
	sem_init(&mutex,0,1);
	data *d=(data*)malloc(sizeof(data));
	d->f=0;
	d->flag=0;
int num;
int m,n;
printf("Enter number of processes:");
scanf("%d",&m);
printf("Enter number of resource types:");
scanf("%d",&n);
int request[n];
printf("Enter d->allocation mat:\n");
for(int i=0;i<m;i++){
	for(int j=0;j<n;j++){
		scanf("%d",&d->allocation[i][j]);
	}
}
printf("Enter d->max mat:\n");
for(int i=0;i<m;i++){
	for(int j=0;j<n;j++){
		scanf("%d",&d->max[i][j]);
	}
}
printf("Enter d->available array:\n");
for(int j=0;j<n;j++){
		scanf("%d",&d->available[j]);
	}
for(int j=0;j<m;j++){
		d->finish[j]=0;
	}
printf("Enter process that requests:");
scanf("%d",&num);
printf("Enter request:");
for(int i=0;i<n;i++){
	scanf("%d",&request[i]);
	d->available[i]-=request[i];
	if(d->available[i]<0){
		printf("Unsafe state");
	return 0;
	}
}

if(checkstate(num,m,n)==0)
	printf("Unsafe state");
	return 0;
	
}