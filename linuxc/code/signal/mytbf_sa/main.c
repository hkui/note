#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include "mytbf.h"

#define CPS 10
#define BUFSIZE 1024
#define BURST 100
int main(int argc,char **argv){
    int sfd;
    int len,pos;
    int size;
    size_t ret;
    mytbf_t *tbf;
    char buf[BUFSIZE];

    if(argc<2){
        fprintf(stderr,"Usage:%s <src_file>\n",argv[0]);
        exit(1);
    }
    tbf=mytbf_init(CPS,BURST);
    do{
        sfd=open(argv[1],O_RDONLY);
        if(sfd<0){
            if(errno==EINTR){
                continue;
            }
            perror("open ");
            exit(1);
        }
    }while(sfd<0);


    while(1){
        size=mytbf_fetchtoken(tbf,BUFSIZE);
        if(size<0){
            fprintf(stderr,"mytbf_fetchtoekn():%s\n ",strerror(-size));
            exit(1);
        }
        while((len=read(sfd,buf,size))<0){
            if(errno==EINTR){
                continue;
            }
            perror("read");
            break;
        }
        if(len==0) break;
        if(size-len>0){
            mytbf_returntoken(tbf,size-len);
        }
        pos=0;
        while(len>0){
            ret=fprintf(stdout,buf);
            pos+=ret;
            len-=ret;
        }
    }
    close(sfd);
    mytbf_destory(tbf);
    return 0;
}
//make
