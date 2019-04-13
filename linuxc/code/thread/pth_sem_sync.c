#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <semaphore.h>
#include <unistd.h>

#define SECON_PTH_NUMS 2

#define PTHEXIT -1
#define SEM_NUMS SECON_PTH_NUMS+1 //信号量数量,主线程占用一个


typedef struct pthread_arg{
	pthread_t tid;
	int pthno;
	int fd;
}ptharg;

//全局变量定义后，默认初始化为0
struct global_va{
	ptharg pth_arg[SECON_PTH_NUMS]; //结构体数组，每个元素会被当做参数传递给对应的次线程
	sem_t sem[SEM_NUMS];

} glbva;

void print_err(char *str,int line,int err_no){
	printf("%d,%s:%s\n",line,str,strerror(err_no) );
	exit(-1);
}
void signal_fun(int signo){
		int i= 0;
		int ret =0;
		for (i=0;i<SEM_NUMS;i++){
			ret = sem_destroy(&glbva.sem[i]);
			if(ret != 0) print_err("sem_destory err",__LINE__,errno);

		}
		exit(0);
	
}

void *pth_fun1(void *pth_arg){
	
	while(1){
		sem_wait(&glbva.sem[0]);
		printf("111111\n");
		sleep(1);
		sem_post(&glbva.sem[1]);
	}
	return NULL;
}
void *pth_fun2(void *pth_arg){
	
	while(1){
		sem_wait(&glbva.sem[1]);
		printf("222222\n");
		sleep(1);
		sem_post(&glbva.sem[2]);
	}
	return NULL;
}



int main(int argc, char const *argv[])
{
	
	int i=0;
	int ret =0;
	void *(*pth_fun_buf[])(void *)={pth_fun1,pth_fun2};


	signal(SIGINT,signal_fun);

	#if 1

	//初始化信号量

	for(i=0;i<SEM_NUMS;i++){
		if(i == 0) ret = sem_init(&glbva.sem[i],0,1);
		else ret = sem_init(&glbva.sem[i],0,0);
		if(ret != 0) print_err("open sem_init err",__LINE__,errno);
	}
	#endif

	for(i=0;i<SECON_PTH_NUMS;i++){
		ret= pthread_create(&glbva.pth_arg[i].tid,NULL,pth_fun_buf[i],NULL);
		if(ret !=0 ) print_err("pthread_creat err",__LINE__,ret);
		

	}

	while(1){
		sem_wait(&glbva.sem[2]);
		printf("33333\n");
		sleep(1);
		sem_post(&glbva.sem[0]);
		
	}
	return 0;
}
