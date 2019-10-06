#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

static void cleanup_func(void *p){
    puts(p);
}

static void *fun(void *p){
    puts("pthread runing");
    pthread_cleanup_push(cleanup_func,"cleanup1");
    pthread_cleanup_push(cleanup_func,"cleanup2");
    pthread_cleanup_push(cleanup_func,"cleanup3");

    puts("push over");

    pthread_cleanup_pop(1); //弹栈并执行
    pthread_cleanup_pop(0);//只弹
    pthread_cleanup_pop(0);
    //如果pop写在了exit后，会全部当做参数为1 处理
    pthread_exit(NULL);
}
int main(){
    pthread_t tid;
    int err;
    puts("Begin");

    err=pthread_create(&tid,NULL,fun,NULL);
    if(err){
        fprintf(stderr,"pthread_create():%s\n",strerror(err));
    }
    //回收等待
    pthread_join(tid,NULL);
    puts("end");
    return 0;
}