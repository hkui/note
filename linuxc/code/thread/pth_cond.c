#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>


#define SECON_PTH_NUMS 1   //次线程数

int va=0;

typedef struct pthread_arg{
	pthread_t tid;
	int pthno;
	int fd;
}ptharg;


void print_err(char *str,int line,int err_no){
	printf("%d,%s:%s\n",line,str,strerror(err_no) );
	exit(-1);
}

void *pth_fun(void *pth_arg){
	while(1){
		usleep(800000);
		if(va == 5){
			printf("va=%d\n",va);
			va=0;
		}else{
			printf("va=%d\n",va);
		}
	}
	return NULL;
}


int main(int argc, char const *argv[])
{
	int i=0;
	int ret =0;
	pthread_t tid;

	ret= pthread_create(&tid,NULL,pth_fun,NULL);
	if(ret !=0 ) print_err("pthread_creat err",__LINE__,ret);

	while(1){
		va =va+1;
		sleep(1);
	}
	return 0;
}