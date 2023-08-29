#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include<time.h>
int main (int argc, char *argv[])
{
struct stat sb;
int ret;
if (argc < 2) {
fprintf (stderr, "usage: %s <file>\n", argv[0]);
return 1;}
ret = stat (argv[1], &sb);
if (ret) {
perror ("stat");
return 1;
}
printf ("File: %s\nDevice ID: %ld\nInode no: %ld\nPermissions: %d\nNo. of hard links: %ld\nUserID: %d\nGroupID: %d\nDeviceID(if special file): %ld\nSize: %ld\nBlocksize: %ld\nNo. of blocks: %ld\nAccess time: %s\nModification Time: %s\nStatus change time: %s", argv[1],sb.st_dev,sb.st_ino,sb.st_mode,sb.st_nlink,sb.st_uid,sb.st_gid,sb.st_rdev,sb.st_size,sb.st_blksize,sb.st_blocks,ctime(&sb.st_atime),ctime(&sb.st_mtime),ctime(&sb.st_ctime));
return 0;
}