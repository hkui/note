#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc ,char **argv){
     FILE *fp;
    char *lineptr;
    size_t n;

    if(argc<2){
        fprintf(stderr,"Usage...\n");
        exit(1);
    }
    fp=fopen(argv[1],"r");
    if(fp==NULL){
        perror("fopen ");
        exit(1);
    }
    lineptr=NULL;
    n=0;

    while(1){
        if(getline(&lineptr, &n, fp)<0){
            break;
        }
        fprintf(stdout,"lineptr=%d,n=%d\n", strlen(lineptr),n);
    }
    fclose(fp);
    return 0;

}
