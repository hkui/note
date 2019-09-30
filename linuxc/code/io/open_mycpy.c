#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 1024

int main(int argc,char **argv){
    int sfd,dfd;
    int len,pos;
    size_t ret;
    char buf[BUFSIZE];

    if(argc<3){
       fprintf(stderr,"Usage:%s <src_file> <dst_file>\n",argv[0]);
       exit(1);
    }
    sfd=open(argv[1],O_RDONLY);
    if(sfd<0){
        perror("open ");
        exit(1);
    }
    dfd=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0644);
    if(dfd <0){
        close(sfd);
        perror("open ()");
        exit(1);
    }
    while(1){
       len=read(sfd,buf,BUFSIZE);
       if(len<0){
           perror("read");
           exit(1);
       }
       if(len==0) break;
       pos=0;
       while(len>0){
           ret=write(dfd,buf+pos,len);
           if(ret<0){
               perror("write");
               exit(1);
           }
           pos+=ret;
           len-=ret;
       }
    }
    close(sfd);
    close(dfd);
    return 0;
}

