#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(){
    puts("Begin");
    fflush(NULL);
    execl("/bin/date" ,"date","+%s",NULL);
    perror("execl");
    exit(1);

}






