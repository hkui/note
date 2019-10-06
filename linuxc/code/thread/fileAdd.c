//多个线程计算质数
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define FNAME "/tmp/out"

#define THRNUM  20
#define LINESIZE 1024

static void *thr_add(void *p){
    FILE *fp;
    char linebuf[LINESIZE] ;
    fp=fopen(FNAME,"r+");
    if(fp==NULL){
        perror("fopen()");
        exit(1);
    }
    fgets(linebuf,LINESIZE,fp);
    fseek(fp,0,SEEK_SET);
    fprintf(fp,"%d",atoi(linebuf)+1);
    fclose(fp);

    pthread_exit(NULL);
}

int main() {
    int i,err;
    pthread_t tid[THRNUM];

    for (i = 0; i < THRNUM; i++) {
        err = pthread_create(tid+i, NULL, thr_add, NULL);
        if (err) {
            fprintf(stderr, "pthread_create %s\n", strerror(err));
            //todo 把创建的都回收了
            exit(1);
        }
    }
    for (i = 0; i < THRNUM; i++) {
        pthread_join(tid[i],NULL);
    }
    return 0;
}





