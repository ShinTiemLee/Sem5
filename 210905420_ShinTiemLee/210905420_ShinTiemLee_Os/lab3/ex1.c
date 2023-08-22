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
		printf("Error:Fork failed");
		break;
	case 0:
		printf("Child process\n");
		exit(0);
		break;
	default:
		wait(&status);
		printf("Child process terminated\n");
		printf("parent process\n");
		//exit(0);
	}
	return 0;
}