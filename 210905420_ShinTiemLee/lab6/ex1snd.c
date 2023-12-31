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
char text[MAX_TEXT];
};
int main()
{
	int running =1;
	struct my_msg_st data;
	int msgid;
	char buffer[BUFSIZ];
	msgid = msgget((key_t)4321, 0666 | IPC_CREAT);
	if (msgid == -1) {
	fprintf(stderr, "msgget failed with error: %d\n", errno);
	exit(EXIT_FAILURE);
}
	while(running) {
		printf("Enter number:");
		fgets(buffer, BUFSIZ, stdin);
		data.my_msg_type = 1;
		strcpy(data.text, buffer);
		if (msgsnd(msgid, (void *)&data, MAX_TEXT, 0) == -1) {
		fprintf(stderr, "msgsnd failed\n");
		exit(EXIT_FAILURE);
		}
		if (strncmp(buffer, "end", 3) == 0) {
		running = 0;
		}
	}
	exit(EXIT_SUCCESS);
}