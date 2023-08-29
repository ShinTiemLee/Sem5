#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include<stdlib.h>
int main (int argc, char *argv[])
{
int ret;
if (argc < 2) {
fprintf (stderr, "usage: %s <file>\n", argv[0]);
return 1;}
char* str=(char*)malloc(sizeof(char)*100);
printf("Enter link path: ");
fgets(str,100,stdin);
fputs(str,stdout);
//ret = symlink(argv[1],str);
ret = unlink(argv[1]);
return 0;
}