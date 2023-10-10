#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "ex3shm.h"

int main()
{
int running = 1;
int num;
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
for(int i=0;i<3;i++){
	for(int j=0;j<3;j++){
		printf("\t%d",shared_stuff->tt[i][j]);
	}
	printf("\n");
}
printf("Enter cell {1-9} ");
scanf("%d",&num);
switch(num){
case 1: shared_stuff->tt[0][0]=1;
		break;
case 2: shared_stuff->tt[0][1]=1;
		break;
case 3: shared_stuff->tt[0][2]=1;
		break;
case 4: shared_stuff->tt[1][0]=1;
		break;
case 5: shared_stuff->tt[1][1]=1;
		break;
case 6: shared_stuff->tt[1][2]=1;
		break;
case 7: shared_stuff->tt[2][0]=1;
		break;
case 8: shared_stuff->tt[2][1]=1;
		break;
case 9: shared_stuff->tt[2][2]=1;
		break;
default:printf("Invalid i/p");
}

for(int i=0;i<3;i++){
	for(int j=0;j<3;j++){
		printf("\t%d",shared_stuff->tt[i][j]);
	}
	printf("\n");
}
shared_stuff->written_by_you=0;
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