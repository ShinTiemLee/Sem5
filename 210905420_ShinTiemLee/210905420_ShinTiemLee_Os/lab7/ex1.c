#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
int buf[20];
sem_t mutex,full,empty;


void *produce(void *arg)
{
int i,r;
for(int i=0;i<10;i++){
buf[(++r)%20]=i;
printf("produced item is %d\n",i);
}
sleep(1);
for(i=10;i<20;)
{
sem_wait(&empty);
sem_wait(&mutex);
buf[(++r)%20]=i;
printf("produced item is %d\n",i);
sleep(1);
sem_post(&mutex);
sem_post(&full);
i=(i+1)%20;
//printf("full %u\n",full);
}
printf("buf producer index:%d",r%20);


}





void *consume(void *arg)
{
int item,i,f;
for(i=0;i<20;)
{
sem_wait(&full);
//printf("full %u\n",full);
sem_wait(&mutex);
item=buf[(++f)%20];
printf("consumed item is %d\n",item);
sem_post(&mutex);
sem_post(&empty);
i=(i+1)%20;
}
printf("buf consumer index:%d",f%20);

}




int main()
{
pthread_t tid1,tid2;
sem_init(&mutex,0,1);
sem_init(&full,0,1);
sem_init(&empty,0,1);
pthread_create(&tid1,NULL,&produce,NULL);
pthread_create(&tid2,NULL,&consume,NULL);
pthread_join(tid1,NULL);
pthread_join(tid2,NULL);
}