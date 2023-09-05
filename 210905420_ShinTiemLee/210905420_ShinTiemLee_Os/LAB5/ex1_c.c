#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#define FIFO_NAME "/tmp/my_fifo"
#define BUFFER_SIZE PIPE_BUF
int main()
{
int pipe_fd;
int lim=4,res;
int open_mode = O_RDONLY;
int temp;
int bytes_read = 0;
memset(&temp, 0, sizeof(temp));
printf("Process %d opening FIFO O_RDONLY\n", getpid());
pipe_fd = open(FIFO_NAME, open_mode);
printf("Process %d result %d\n", getpid(), pipe_fd);
if (pipe_fd != -1) {
do {
res = read(pipe_fd,&temp, sizeof(int));
lim--;
printf("\t%d",temp);
} while (lim > 0);
(void)close(pipe_fd);
}
else {
exit(EXIT_FAILURE);
}
printf("Process %d finished, %d bytes read\n", getpid(), bytes_read);
exit(EXIT_SUCCESS);
}