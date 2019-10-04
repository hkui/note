#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#define CPS 10
#define BUFSIZE CPS
#define BURST 100
static volatile int token=0;  //gcc alarm.c -O1  优化时会到真正存储的地方取值

static void alrm_handler(int signo){
    if(token>BURST){
        token=BURST;
    }else{
        token++;
    }
    alarm(1);

}

int main(int argc,char **argv){
    int sfd;
    int len,pos;
    size_t ret;
    char buf[BUFSIZE];

    if(argc<2){
       fprintf(stderr,"Usage:%s <src_file>\n",argv[0]);
       exit(1);
    }
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

    signal(SIGALRM,alrm_handler);
    alarm(1);

    while(1){
        //token大于0 就无需等待
        while(token<=0){
            pause();
        }
        token--;
        //当读的设备没数据时，令牌token一直在积攒，来数据了拿积攒的令牌桶 去读数据
        while((len=read(sfd,buf,BUFSIZE))<0){
            if(errno==EINTR){
                continue;
            }
            perror("read");
            break;
        }
        if(len==0) break;
        pos=0;
        while(len>0){
            ret=fprintf(stdout,buf);
            pos+=ret;
            len-=ret;
        }
    }
    close(sfd);
    return 0;
}

