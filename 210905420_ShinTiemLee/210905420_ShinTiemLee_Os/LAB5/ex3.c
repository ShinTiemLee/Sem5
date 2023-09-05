#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#define BUFFER_SIZE PIPE_BUF
#define FIFO_NAME "/tmp/my_fifo"
int main(int argc, char *argv[])
{
int pipe_fd;
int res;

pid_t cpid;
char buf[BUFFER_SIZE+1];

cpid = fork();
if (cpid == -1) { perror("fork");
exit(EXIT_FAILURE); }

if (cpid == 0) {
	int open_mode=O_RDONLY;
memset(buf, '\0', sizeof(buf));
printf("Process %d opening FIFO O_RDONLY\n", getpid());
pipe_fd = open(FIFO_NAME, open_mode);
printf("Process %d result %d\n", getpid(), pipe_fd);
if (pipe_fd != -1) {
res = read(pipe_fd, buf, BUFFER_SIZE);
printf("%s",buf);
(void)close(pipe_fd);
}
else {
exit(EXIT_FAILURE);
}
printf("Process %d finished,\n", getpid());
exit(EXIT_SUCCESS);

}
else{
int open_mode=O_WRONLY;
if (access(FIFO_NAME, F_OK) == -1) {
res = mkfifo(FIFO_NAME, 0777);
if (res != 0) {
fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME);
exit(EXIT_FAILURE);
}
}
printf("Process %d opening FIFO O_WRONLY\n", getpid());
pipe_fd = open(FIFO_NAME, open_mode);
printf("Process %d result %d\n", getpid(), pipe_fd);
if (pipe_fd != -1) {
strcpy(buf,"hello");
res = write(pipe_fd, buf, BUFFER_SIZE);
if (res == -1) {
fprintf(stderr, "Write error on pipe\n");
exit(EXIT_FAILURE);
}

(void)close(pipe_fd);
}
else {
exit(EXIT_FAILURE);
}
printf("Process %d finished\n", getpid());
exit(EXIT_SUCCESS);
} 


}