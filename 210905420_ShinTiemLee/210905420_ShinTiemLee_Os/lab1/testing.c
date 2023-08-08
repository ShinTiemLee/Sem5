#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include<string.h>
#include<stdio.h>
int main(int argc,char **argv)
{
if (argc!=3){
    printf("Insufficient arguments");
    exit(0);
}
int i=1;
char c[50];
char str[100];
char *arr=malloc(100*sizeof(char));
strcpy(arr,"");
int in, size,count=0;
in = open(argv[2], O_RDONLY);
strcpy(c,argv[1]);
size=strlen(c);
while(read(in,str,1) == 1){
    printf("%s",str);
   arr=strstr(str,c);
   if (strstr(str,c)==c)
     printf("Line:%d     %s",i,str);
//}
//if(strcmp(strstr(),\n)==0){
//strcpy(str,"");
i++;
//}
}
return 0;
}