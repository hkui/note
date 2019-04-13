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
#define SEM_NUMS 1 //信号量数量


typedef struct pthread_arg{
	pthread_t tid;
	int pthno;
	int fd;
}ptharg;

//全局变量定义后，默认初始化为0
struct global_va{
	ptharg pth_arg[SECON_PTH_NUMS]; //结构体数组，每个元素会被当做参数传递给对应的次线程
	sem_t sem[1];

} glbva;

void print_err(char *str,int line,int err_no){
	printf("%d,%s:%s\n",line,str,strerror(err_no) );
	exit(-1);
}
void signal_fun(int signo){
		int ret =0;
		ret = sem_destroy(&glbva.sem[0]);
		if(ret != 0) print_err("sem_destory err",__LINE__,errno);
		exit(0);
}

void *pth_fun(void *pth_arg){
	int fd= ((ptharg *)pth_arg)->fd;
	
	while(1){
		sem_wait(&glbva.sem[0]);
		write(fd,"php",3);
		write(fd,"java\n",5);
		sem_post(&glbva.sem[0]);
	}
	return NULL;
}



int main(int argc, char const *argv[])
{
	
	int i=0;
	int ret =0;
	int fd =0;
	signal(SIGINT,signal_fun);

	fd=open("./file",O_RDWR|O_CREAT|O_TRUNC,0664);
	if(fd ==-1) print_err("open file fail",__LINE__,errno);

	//初始化信号量
	ret = sem_init(&glbva.sem[0],0,1);
	if(ret != 0) print_err("open sem_init err",__LINE__,errno);

	for(i=0;i<SECON_PTH_NUMS;i++){
		glbva.pth_arg[i].fd =fd;
		glbva.pth_arg[i].pthno=i;
		ret= pthread_create(&glbva.pth_arg[i].tid,NULL,pth_fun,(void *)&glbva.pth_arg[i]);
		if(ret !=0 ) print_err("pthread_creat err",__LINE__,ret);
		

	}

	while(1){
		sem_wait(&glbva.sem[0]);
		write(fd,"js",2);
		write(fd,"css\n",4);
		sem_post(&glbva.sem[0]);
	}
	return 0;
}
