#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm_com.h"
int main()
{

	if(fork()==0){
		int running = 1;
		void *shared_memory = (void *)0;
		struct shared_use_st *shared_stuff;
		int shmid;
		srand((unsigned int)getpid());
		shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
		if (shmid == -1) {
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
		}
		shared_memory = shmat(shmid, (void *)0, 0);
		if (shared_memory == (void *)-1) {
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
		}
		printf("Memory attached at %X\n",(int) shared_memory);
		shared_stuff = (struct shared_use_st *)shared_memory;
		shared_stuff->written_by_you = 0;
		while(running) {
		if (shared_stuff->written_by_you) {
		shared_stuff->some_text[0]+=1;
		sleep( rand() % 4 ); /* make the other process wait for us ! */
		shared_stuff->written_by_you = 0;
		running = 0;
		}
		}
		if (shmdt(shared_memory) == -1) {
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
		}
		if (shmctl(shmid, IPC_RMID, 0) == -1) {
		fprintf(stderr, "shmctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else{


		int running = 1;
		void *shared_memory = (void *)0;
		struct shared_use_st *shared_stuff;
		char buffer[BUFSIZ];
		int shmid;
		shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
		if (shmid == -1) {
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
		}
		shared_memory = shmat(shmid, (void *)0, 0);
		if (shared_memory == (void *)-1) {
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
		}
		printf("Memory attached at %X\n", (int)shared_memory);
		shared_stuff = (struct shared_use_st *)shared_memory;
		while(running) {
		while(shared_stuff->written_by_you == 1) {
		sleep(1);
		printf("waiting for child...\n");
		}
		printf("Enter some text:");
		fgets(buffer, BUFSIZ, stdin);
		strncpy(shared_stuff->some_text, buffer, TEXT_SZ);
		shared_stuff->written_by_you = 1;
		while(shared_stuff->written_by_you == 1) {
		sleep(1);
		printf("waiting for child...\n");
		}
		printf("%s",shared_stuff->some_text);
		running=0;
		}
		
		if (shmdt(shared_memory) == -1) {
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
		}
