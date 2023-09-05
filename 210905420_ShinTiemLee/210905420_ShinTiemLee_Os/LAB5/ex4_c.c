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
#include<time.h>
#define LIM 0
int main()
{
int pipe_fd;
int i,res;
int open_mode = O_RDWR;
int bytes_read = 0;
memset(&i, 0, sizeof(int));
printf("Process %d opening FIFO O_WRONLY\n", getpid());
pipe_fd = open(FIFO_NAME, open_mode);
printf("Process %d result %d\n", getpid(), pipe_fd);
if (pipe_fd != -1) {
	res = read(pipe_fd,&i, sizeof(int));
	while(10){
while (i>LIM) {
	i--;
	printf("\tconsumer consumed, count=%d",i);
	res=write(pipe_fd,&i,sizeof(int));
	sleep(1000);
res = read(pipe_fd,&i, sizeof(int));

} }
(void)close(pipe_fd);
}
else {
exit(EXIT_FAILURE);
}
printf("Process %d finished, %d bytes read\n", getpid(), bytes_read);
exit(EXIT_SUCCESS);
}