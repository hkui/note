//指定fork 固定进程数 处理多个任务(交叉分配)
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


#define LEFT    30000000
#define RIRHT   30000200
#define PROCESS_NUM 3 //进程数

int main(){
    pid_t pid;
    int i,mark,j;
    int status;
    int pn;
    for(pn=0;pn<PROCESS_NUM;pn++){
        pid=fork();
        if(pid<0){
            perror("fork ()");
            //todo 把fork出的都回收了
            exit(1);
        }
        if(0==pid){
            for(i=LEFT+pn;i<=RIRHT;i+=PROCESS_NUM){
                mark=1;
                for(j=2;j<i/2;j++){
                    if(i%j==0){
                        mark=0;
                        break;
                    }
                }
                if(mark) printf("%d say %d is  primer\n",pn,i);
            }
            exit(0);
        }
    }

    for(i=0;i<PROCESS_NUM;i++){
       pid= wait(NULL);
       printf("waited %d\n",pid);
    }
   exit(1);
}


