#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(){
    pid_t pid;
    printf("%d begin\n",getpid());
    fflush(NULL);
    pid=fork();
    if(pid<0){
        perror("fork ");
        exit(1);
    }
    if(0==pid){
        execl("./exec_son" ,"a","b",NULL);
        perror("execl");
    }
    wait(NULL);
    printf("%d end\n",getpid());
    exit(1);
}






