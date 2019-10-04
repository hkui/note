#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

//static int loop=1; ////gcc alarm.c -O1 优化时会发现 loop在循环体里没改变 会到内存里取，导致死循环
static volatile loop=1;  //gcc alarm.c -O1  优化时会到真正存储的地方取值

static void alrm_handler(int signo){
    loop=0;
}
int main(){
    int64_t count=0;

    alarm(5);
    signal(SIGALRM,alrm_handler);

    while(loop){
        count++;
    }
    printf("%ld\n",count);
    return 0;
}
