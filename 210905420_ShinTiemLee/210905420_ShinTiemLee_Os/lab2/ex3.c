#include<unistd.h>
#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>

void printdir(char *dir, int depth,char **str)
{ 
	int i=0;
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
/* Recurse at a new indent level */
printdir(entry->d_name,depth+4,str);
}
else {
	strcpy(str[i],entry->d_name);
	i++;
}
}
chdir("..");
closedir(dp);
}

void sort(char** str){
	char * temp=(char*)malloc(50*sizeof(char));
	for(int i=0;i<sizeof(str)-1;i++){
		for(int j=i;j<sizeof(str)-1;j++){
			if(strcmp(str[i],str[j+1])>0){
				strcpy(temp,str[i]);
				strcpy(str[i],str[j+1]);
				strcpy(str[j+1],temp);
			}
		}
	}
}

void main(){
	char **str=(char**)malloc(50*sizeof(char*));
	for(int i=0;i<50;i++)
		str[i]=(char*)malloc(50*sizeof(char));
	printdir("..",0,str);
	sort(str);
	for(int i=0;i<sizeof(str);i++){
		printf("%s\n",str[i]);
	}
}