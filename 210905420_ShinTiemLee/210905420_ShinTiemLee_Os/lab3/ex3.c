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
		printf("Process:%d\n",getpid());
		printf("Parent process:%d\n",getppid());
			break;
	default:
		printf("parent process:%d\n",getppid());
		printf("process:%d\n",getpid());
		printf("child process:%d\n",pid);
		break;
	}

	return 0;
}