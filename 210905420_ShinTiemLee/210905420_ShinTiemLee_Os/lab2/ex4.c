#include<unistd.h>
#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>
void printdir(char *dir, int depth)
{
char * str=(char*)malloc(50*sizeof(char));
DIR *dp;
struct dirent *entry;
struct stat statbuf;
if((dp = opendir(dir)) == NULL) {
fprintf(stderr,"cannot open directory: %s\n", dir);
return;
}
chdir(dir);
while((entry = readdir(dp)) != NULL) {
lstat(entry->d_name,&statbuf);
if(!(S_ISDIR(statbuf.st_mode))) {
/* Found a directory, but ignore . and .. */
if(strcmp(".",entry->d_name) == 0 ||
strcmp("..",entry->d_name) == 0)
continue;
printf("%*s%s/\n",depth,"",entry->d_name);
printf("Delete yes or no");
scanf("%s",str);
if(strcmp("yes",str)==0){
	if((remove(entry->d_name))==0)
		printf("removed file");
}
}
}
closedir(dp);
}

void main(){
	printdir("/home/OS_Student/Documents/210905420_ShinTiemLee_Os/lab2",0);
}