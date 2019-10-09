#include "../include/apue.h"

//获取之前的 然后加上要设置的falgs,再设置进去
void set_fl(int fd, int flags)
{
    int val;

    if ((val = fcntl(fd, F_GETFL, 0)) < 0) {
        printf("fcntl F_GETFL error\n");
        exit(1);
    }

    val |= flags;

    if (fcntl(fd, F_SETFL, val) < 0) {
        printf("fcntl F_SETFL error\n");
        exit(1);
    }
}
//去掉某个flags
void clr_fl(int fd, int flags)
{
    int val;

    if ((val = fcntl(fd, F_GETFL, 0)) == -1) {
        printf("fcntl F_GETFL error\n");
        exit(1);
    }

    val &= ~flags;

    if (fcntl(fd, F_SETFL, val) == -1) {
        printf("fcntl F_SETFL error\n");
        exit(1);
    }
}


