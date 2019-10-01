//空洞文件
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc,char **argv){
    int fd;
    if(argc<2){
        fprintf(stdout,"uasge :2");
        exit(1);
    }
    fd=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0600);
    if(fd<0){
        perror("fopen ");
        exit(1);
    }
    lseek(fd,5LL*1024LL*1024LL*1024LL-1LL,SEEK_SET);
    write(fd,"",1);
    close(fd);

    return 0;

}



