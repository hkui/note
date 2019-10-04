#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigHandler(int signalNum){
    printf(" sign  = %d\n",signalNum);
}
int main(){
    int i;
//    signal(SIGINT,SIG_IGN); //一直按ctrl+c 执行还是规定的时间

    signal(SIGINT,sigHandler); //一直按ctrl+c 执行小于规定的时间

    for(i=0;i<10;i++){
        write(1,"*",1);
        sleep(1);
    }

    return 0;
}

