#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
int main(){
	pid_t pid;
	pid=fork();
	switch(pid){
	case -1:
		printf("Error:Fork failed");\
		break;
	case 0:
		printf("child process:%d\n",getpid());
		exit(0);
	default:
		printf("Parent process:%d\n",getpid());
		sleep(10);
		break;
	}

	return 0;
}