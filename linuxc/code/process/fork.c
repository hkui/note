#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    pid_t pid;
    printf("%d:Begin\n",getpid());
    //特别重要，如果不加，写到文件里会有2个begin
    fflush(NULL);
    pid=fork();
    if(pid<0){
        perror("fork()");
        exit(1);
    }
    if(pid>0){
        printf("%d: parent working \n",getpid());
    }else{
        printf("%d: son working \n",getpid());
    }
    printf("%d:end\n",getpid());
    return 0;
}
