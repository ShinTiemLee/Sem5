#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex, wrt;
int readcount=0;

void *writer(void* param){
	for(int i=0;i<5;i++){
	sem_wait(&wrt);
	printf("\nWriter is writing");
	sem_post(&wrt);
	sleep(2);
	}
}

void *reader(void* param){

	for(int i=0;i<5;i++){
	sem_wait(&mutex);
	readcount++;
	if(readcount==1)
		sem_wait(&wrt);
	sem_post(&mutex);
	printf("\nReader is reading");
	sem_wait(&mutex);
	readcount--;
	if(readcount==0)
		sem_post(&wrt);
	sleep(1);
	sem_post(&mutex);
}
	
}

int main(){
pthread_t tid1,tid2;
sem_init(&mutex,0,1);
sem_init(&wrt,0,1);
pthread_create(&tid1,NULL,reader,NULL);
pthread_create(&tid2,NULL,writer,NULL);
pthread_join(tid1,NULL);
pthread_join(tid2,NULL);
return 0;
}