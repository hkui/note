//多个进程处理任务 不带回收子进程
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


#define LEFT    30000000
#define RIGHT   30000200

int main(){
    pid_t pid;
    int i,mark,j;
    for(i=LEFT;i<=RIGHT;i++){
        pid=fork();
        if(pid<0){
            perror("fork()");
            exit(1);
        }
        if(0==pid){
            mark=1;
            for(j=2;j<i/2;j++){
                if(i%j==0){
                    mark=0;
                    break;
                }
            }
            if(mark){
                printf("%d is a primer\n",i);
            }
            exit(1);
        }
    }

    return 0;
}
//make fork_primer
// time ./fork_timer

