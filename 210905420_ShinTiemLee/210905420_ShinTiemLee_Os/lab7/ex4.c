#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

sem_t barber, AvailableSeats,spot;
int seatcount=0;

void *C(void* param){
	while(1){
		if(seatcount==0){
			sem_wait(&barber);
			seatcount++;
			printf("\nBarber is cutting");
			sleep(2);
			printf("\nBarber is done cutting");
			sem_post(&barber);
		}
		else if(seatcount<=2){
			sem_wait(&AvailableSeats);
			seatcount++;
			printf("\nWaiting in waitroom at index%d",seatcount-1);
			sem_wait(&barber);
			seatcount--;
			sem_post(&AvailableSeats);
			printf("\nBarber is cutting");
			sleep(2);
			sem_post(&barber);
		}
		else{
			sleep(2);
			printf("\nCustomer leaves as not spot in waiting room");
			
			}
		}
	}



int main(){
pthread_t tid2[4];
sem_init(&barber,0,1);
sem_init(&AvailableSeats,0,2);
pthread_create(&tid2[0],NULL,C,NULL);
pthread_create(&tid2[1],NULL,C,NULL);
pthread_create(&tid2[2],NULL,C,NULL);
pthread_create(&tid2[3],NULL,C,NULL);

pthread_join(tid2[0],NULL);
pthread_join(tid2[1],NULL);
pthread_join(tid2[2],NULL);
pthread_join(tid2[3],NULL);
return 0;
}