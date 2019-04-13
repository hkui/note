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
pthread_cond_t cond; //定义条件变量
pthread_mutex_t mutex =  PTHREAD_MUTEX_INITIALIZER;

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
		pthread_mutex_lock(&mutex);
		//防止休眠后导致锁没解开，使得其它线程无法加锁，使用该函数检查cond没有被设置时，将其解锁，使其它线程可用
		pthread_cond_wait(&cond,&mutex);
		
		printf("va=%d\n",va);
		va=0;
		
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}
void signal_fun(int signo){
		 pthread_cond_destroy(&cond);
		 pthread_mutex_destroy(&mutex);
		 exit(0);
	
}


int main(int argc, char const *argv[])
{
	int i=0;
	int ret =0;
	pthread_t tid;
	signal(SIGINT,signal_fun);
	//初始化条件变量
	ret = pthread_cond_init(&cond,NULL);
	if(ret !=0 ) print_err("pthread_cond_init err",__LINE__,ret);

	ret= pthread_create(&tid,NULL,pth_fun,NULL);
	if(ret !=0 ) print_err("pthread_creat err",__LINE__,ret);

	while(1){
		pthread_mutex_lock(&mutex);
		va =va+1;
		if(va == 5){
			pthread_cond_signal(&cond);
		}
		printf("%d\n",va );
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	return 0;
}