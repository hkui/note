#include "../include/apue.h"

char buf[500000];

int main(){
    int ntowrite,nwite,errno;
    char *ptr;

    ntowrite=read(STDIN_FILENO,buf, sizeof(buf));

    fprintf(stderr,"read %d bytes\n",ntowrite);

    set_fl(STDOUT_FILENO,O_NONBLOCK); //设置非阻塞

    ptr=buf;

    while (ntowrite > 0) {
        errno = 0;
        //写进入的长度
        nwite = write(STDOUT_FILENO, ptr, ntowrite);
        fprintf(stderr, "nwrite=%d,errno=%d\n", nwite, errno);

        if (nwite > 0) {
            ptr += nwite;
            ntowrite -= nwite;
        }

    }
    clr_fl(STDOUT_FILENO,O_NONBLOCK); //清除noblock
    exit(0);
}

