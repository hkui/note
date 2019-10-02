#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc,char **argv){
    printf("Begin son=%d,parent=%d  \n",getpid(),getppid());
    int i;
    for (i=0;i<argc;i++){
        printf("argv[%d]=%s\n",i,argv[i]);
    }
    printf("End son=%d,parent=%d  \n",getpid(),getppid());
    exit(1);

}






