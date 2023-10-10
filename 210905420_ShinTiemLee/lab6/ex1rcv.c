#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX_TEXT 512
struct my_msg_st {
long int my_msg_type;
char text[BUFSIZ];
};
int main()
{
	int running =1;
	struct my_msg_st data;
	int msgid;
	int start,end,flag;
	long int msg_to_receive = 0;
	msgid = msgget((key_t)4321, 0666 | IPC_CREAT);
	if (msgid == -1) {
	fprintf(stderr, "msgget failed with error: %d\n", errno);
	exit(EXIT_FAILURE);
	}
	while(running) {
				if (msgrcv(msgid, (void *)&data, BUFSIZ,
		msg_to_receive, 0) == -1) {
		fprintf(stderr, "msgrcv failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
		}
		if (strncmp(data.text, "end", 3) == 0) {
		running = 0;
		}
		start=0;
		end=strlen(data.text)-2;
		flag=0;
		while(start<end){
			
			if(data.text[start]!=data.text[end]){
				flag=1;
				break;
			}
			start++;
			end--;
		}
		if(flag==0){
			printf("\n%s is palindrome",data.text);
		}
		else{
			printf("\n%s is not palindrome",data.text);
		}
		
		}
		if (msgctl(msgid, IPC_RMID, 0) == -1) {
		fprintf(stderr, "msgctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
			}
		exit(EXIT_SUCCESS);
}
