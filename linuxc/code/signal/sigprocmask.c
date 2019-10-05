#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigHandler(int signalNum){
    write(1,"|",1);

}
int main(){
    int i,j;
    sigset_t set,oset,saveset;

    signal(SIGINT,sigHandler); //一直按ctrl+c 执行小于规定的时间
    sigemptyset(&set);
    sigaddset(&set,SIGINT);

    sigprocmask(SIG_UNBLOCK,&set,&saveset);

    for(j=0;j<1000;j++){
        sigprocmask(SIG_BLOCK,&set,NULL);
        for(i=0;i<5;i++){
            write(1,"*",1);
            sleep(1);
        }
        write(1,"\n",1);
        sigprocmask(SIG_UNBLOCK,&set,NULL);
    }
    sigprocmask(SIG_SETMASK,&saveset,NULL);
    return 0;
}

