#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

//主线程，次线程阻塞读取键盘鼠标

void print_err(char *str,int line,int err_no){
	printf("%d,%s:%s\n",line,str,strerror(err_no) );
	exit(-1);
}

//次线程读取键盘
void *pth_fun(void *pth_arg){
	char buf[100]={0};
	int ret=0;
	while(1){
			printf("keyword read start\n");
			ret =read(0,buf,sizeof(buf));  //读键盘
			if(ret >0 )printf("%s", buf);
			printf("keyword read end\n");
	}
	return NULL;
}
int main(int argc, char const *argv[])
{
	int coord;
	int mousefd =-1;
	pthread_t tid=0;
	int ret= 0;

	ret = pthread_create(&tid,NULL,pth_fun,NULL);
	if(ret !=0) print_err("pthread_attr_init error ",__LINE__,ret);

	mousefd =open("/dev/input/mouse1",O_RDONLY); //可能Mouse0或2
	if(mousefd == -1) print_err("open mouse0 fail",__LINE__,errno);
	//主线程读取鼠标
	while(1){
		printf("begin\n");
		ret = read(mousefd,&coord,sizeof(coord)); //读鼠标
		if(ret >0 )printf("%u\n", coord);
		
		printf("end\n");
	}
	return 0;
}