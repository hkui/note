#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

static void *fun(void *p){
    puts("pthread runing");
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
    exit(1);
}