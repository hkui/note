#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glob.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc,char **argv){
    pid_t pid;
    if(argc<3){
        fprintf(stderr,"usage ..");
        exit(1);
    }
    pid=fork();
    if(pid<0){
        perror("fork");
        exit(1);
    }
    if(pid==0){
        setuid(atoi(argv[1]));
        execvp(argv[2],argv+2);
        perror(" execvp ");
        exit(1);
    }
    wait(NULL);
    return  0;
}
//make mysu
// chmod u+s mysu



