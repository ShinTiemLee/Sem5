#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/stat.h>
#include<stdlib.h>

void ex1(char* dir){
	DIR* dp;
	struct stat statbuf;
	struct dirent *entry;
	if((dp = opendir(dir)) == NULL){
		fprintf(stderr,"Cannot print directory");
		exit(0);
	}
	chdir(dir);
	while((entry=readdir(dp))!= NULL){
	lstat(entry->d_name,&statbuf);
	if(!(S_ISDIR(statbuf.st_mode))){
		if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
			continue;
		printf("%s",entry->d_name);
		printf((statbuf.st_mode & S_IRUSR) ? "-r-" : "");
		printf((statbuf.st_mode & S_IWUSR) ? "-w-" : "");
		printf((statbuf.st_mode & S_IXUSR) ? "-x-" : "");
		printf((statbuf.st_mode & S_IRGRP) ? "-r-" : "");
		printf((statbuf.st_mode & S_IWGRP) ? "-w-" : "");
		printf((statbuf.st_mode & S_IXGRP) ? "-x-" : "");
		printf((statbuf.st_mode & S_IROTH) ? "-r-" : "");
		printf((statbuf.st_mode & S_IWOTH) ? "-w-" : "");
		printf((statbuf.st_mode & S_IXOTH) ? "-x-" : "");
		printf("\n");
	}
}

}

void main(int argc, char* argv[]){
	ex1(argv[1]);
}