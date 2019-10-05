#include <stdio.h>
#include <stdlib.h>
#include "anytimer.h"

void f1(){
    printf("f1\n");
}
int main(){
    int job1,job2,job3;
    job1=at_addjob(5,f1,"aaa");
    if(job1<0){
        fprintf(stderr,"at_addjob():%s\n",strerr(-job));
        exit(1);
    }

    while(1){

    }
    return  0;

}

