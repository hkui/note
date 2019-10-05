//实时信号版 信号驱动
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define MYSIG (SIGRTMIN+6)


void sigHandler(int signalNum){
    write(1,"|",1);
}
int main(){
    int i,j;
    sigset_t set,oset,saveset;

    signal(MYSIG,sigHandler);
    sigemptyset(&set); //64位全部置为0
    sigaddset(&set,MYSIG);//将变量set中，SIGINT 对应的那一位设置为1(屏蔽了sigint)，其它位不变
    sigprocmask(SIG_UNBLOCK,&set,&saveset); //屏蔽字=屏蔽字&(~set)，并把之前的保存在saveset
    sigprocmask(SIG_BLOCK,&set,&oset); //把屏蔽某个信号 屏蔽字=屏蔽字 | set
    for(j=0;j<1000;j++){

        for(i=0;i<5;i++){
            write(1,"*",1);
            sleep(1);
        }
        write(1,"\n",1);
        /*
         * 中间按ctrl+c 信号恢复，pause()还是得不到中间按的信号
        sigset_t tmpset;
        sigprocmask(SIG_SETMASK,&oset,&tmpset);
        pause();
        sigprocmask(SIG_SETMASK,&tmpset,NULL);
        */
        //类似上面的原子操作
        sigsuspend(&oset);

    }
    sigprocmask(SIG_SETMASK,&saveset,NULL);
    return 0;
}
//kill -40 18335

