#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
int main(){
    FILE *fp;
    fp=fopen("tmp","r");
    if(fp==NULL){
        fprintf(stderr,"fopen() failed errno=%d\n",errno);
        fprintf(stderr,"fopen() failed err=%s\n",strerror(errno));
        perror("fopen() failed:");
        exit(1);
    }
    puts("success");
    return 0;
}


