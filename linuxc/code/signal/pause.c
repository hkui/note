#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

static volatile loop=1;
static void alrm_handler(int signo){
	fprintf(stdout,"signo come \n");
    loop=1;
    alarm(1);
}

int main(){
	int i=0;
	signal(SIGALRM,alrm_handler);
    alarm(1);

	while(1){
		while(!loop){
			fprintf(stdout,"before loop=%d\n",loop);
			pause();
			fprintf(stdout,"after loop=%d\n",loop);
		}
		loop=0;
		i++;
		fprintf(stdout,"i=%d,loop=%d\n",i,loop);
	}
	
}