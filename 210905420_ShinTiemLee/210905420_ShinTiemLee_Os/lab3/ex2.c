#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
int main(){
	pid_t pid;
	int status;

	pid=fork();
	switch(pid){
	case -1:
		printf("Error:Fork failed");\
		break;
	case 0:
		printf("child2 process\n");
		execl("ex1","./ex1",NULL);
		//exit(0);
	default:
		wait(NULL);
		printf("Parent2 process\n");
		
	}

	return 0;
}