#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <shadow.h>
#include <unistd.h>
#include <string.h>

int main(int argc,char **argv){
    char *input_pass;
    char *crypted_pass;
    struct spwd *shadowline;
    if(argc<2){
        fprintf(stderr," need 2 args");
        exit(1);
    }
    input_pass=getpass("passwd:");
    shadowline=getspnam(argv[1]);
    crypted_pass=crypt(input_pass,shadowline->sp_pwdp);

    if(strcmp(shadowline->sp_pwdp,crypted_pass) == 0){
        puts("ok!");
    }else{
        puts("fail!");
    }
    return 0;
}



