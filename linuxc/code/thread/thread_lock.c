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

#define SECON_PTH_NUMS 2

#define PTHEXIT -1



typedef struct pthread_arg{
	pthread_t tid;
	int pthno;
	int fd;
}ptharg;

//全局变量定义后，默认初始化为0
struct global_va{
	ptharg pth_arg[SECON_PTH_NUMS]; //结构体数组，每个元素会被当做参数传递给对应的次线程
	int pth_exit_flag[SECON_PTH_NUMS];//退出的状态
	pthread_attr_t attr; //存放线程新属性
	pthread_mutex_t mutex;//互斥锁

} glbva;

void print_err(char *str,int line,int err_no){
	printf("%d,%s:%s\n",line,str,strerror(err_no) );
	exit(-1);
}

//线程退出处理函数

void pth_exit_deal(void *arg){
	pthread_t tid=((ptharg *)arg)->tid;
	printf("pthread %lu exit!\n",tid );
}
void *pth_fun(void *pth_arg){
	//pthread_detach(pthread_self());//在次线程里分离
	//注册线程处理函数
	pthread_cleanup_push(pth_exit_deal,pth_arg);

	int fd= ((ptharg *)pth_arg)->fd;
	int pthno=((ptharg *)pth_arg)->pthno;

	pthread_t tid = ((ptharg *)pth_arg)->tid;
	printf("pthno=%d,pthread_id=%lu\n",pthno,tid);
	
	while(1){
		pthread_mutex_lock(&glbva.mutex);//加锁
		write(fd,"php",3);
		write(fd,"java\n",5);
		pthread_mutex_unlock(&glbva.mutex);//解锁
		//检测退出状态
		if(glbva.pth_exit_flag[pthno] == PTHEXIT) break;
		
	}
	pthread_cleanup_pop(!0);
	printf("tid=%lu\n",pthread_self());
	//pthread_exit(NULL);
	return (void *)10;
}
void signal_fun(int signo){
	if(SIGALRM == signo){
		int i =0;
		for (;i<SECON_PTH_NUMS;i++){
			//pthread_cancel(glbva.pth_arg[i].tid);
			glbva.pth_exit_flag[i]=PTHEXIT; //设置为退出状态
		}
	}else if(SIGINT == signo){
		exit(0);
	}
}
void process_exit_deal(void){
	//销毁线程的属性设置
	int ret=0;
	ret=pthread_attr_destroy(&glbva.attr);
	if(ret !=0) print_err("pthread_attr_destroy error ",__LINE__,ret);

	//销毁互斥锁
	ret = pthread_mutex_destroy(&glbva.mutex);
	if(ret !=0) print_err("pthread_mutex_destroy error ",__LINE__,ret);
	printf("\nprocess exit\n");
}

int main(int argc, char const *argv[])
{
	pthread_t tid=0;
	int i=0;
	int ret =0;
	int fd =0;
	//注册进程退出函数.exit正常终止时，弹栈调用
	atexit(process_exit_deal);
	//初始化互斥锁
	ret = pthread_mutex_init(&glbva.mutex,NULL);
	if(ret !=0) print_err("pthread_mutex_init error ",__LINE__,ret);
	
	signal(SIGALRM,signal_fun);
	

	fd=open("./file",O_RDWR|O_CREAT|O_TRUNC,0664);
	if(fd ==-1) print_err("open file fail",__LINE__,errno);

	//初始化attr设置一些基本的初始值
	ret =pthread_attr_init(&glbva.attr);
	if(ret !=0) print_err("pthread_attr_init error ",__LINE__,ret);
	//设置分离属性
	ret=pthread_attr_setdetachstate(&glbva.attr, PTHREAD_CREATE_DETACHED);
	if(ret !=0) print_err("pthread_attr_setdetachstate error ",__LINE__,ret);

	for(;i<SECON_PTH_NUMS;i++){
		glbva.pth_arg[i].fd =fd;
		glbva.pth_arg[i].pthno=i;
		ret= pthread_create(&glbva.pth_arg[i].tid,&glbva.attr,pth_fun,(void *)&glbva.pth_arg[i]);
		if(ret !=0 ) print_err("pthread_creat err",__LINE__,ret);
		//pthread_detach(glbva.pth_arg[i].tid); //或者在次线程里写

	}
	signal(SIGINT,signal_fun);
	
	alarm(5);//不会阻塞的
	#if 0
	void *retval =NULL;

	for(i=0;i<SECON_PTH_NUMS;i++){
		pthread_join(glbva.pth_arg[i].tid,&retval);//阻塞等待次线程结束，接收返回值
		printf("retval =%ld\n",(long)retval );
	}
	#endif

	while(1){
		pthread_mutex_lock(&glbva.mutex);//加锁
		write(fd,"js",2);
		write(fd,"css\n",4);
		pthread_mutex_unlock(&glbva.mutex); //解锁
		
	}
	return 0;
}