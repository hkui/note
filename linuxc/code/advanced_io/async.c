#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

int mousefd=0;
void print_err(char *str,int line,int err_no){
	printf("%d,%s:%s\n",line,str,strerror(err_no) );
	exit(-1);
}

void signal_fun(int signo){
	int buf;
	int ret=0;
	if(SIGIO == signo){
		bzero(&buf,sizeof(buf));
		ret=read(mousefd,&buf,sizeof(buf));
		if(ret>0) printf("coord=%d\n",buf );
	}
}

int main(int argc, char const *argv[])
{

	char buf[100]={0};
	int ret= 0;

	mousefd =open("/dev/input/mouse0",O_RDONLY); //可能Mouse1或2
	if(mousefd == -1) print_err("open mouse0 fail",__LINE__,errno);
	//设置捕获函数
	signal(SIGIO,signal_fun);
	//告诉鼠标驱动，他发送的sigio信号由当前进程接收
	fcntl(mousefd,F_SETOWN,getpid());
	//
	int flg=fcntl(mousefd,F_GETFL);
	flg|=O_ASYNC;
	fcntl(mousefd,F_SETFL,flg);


	while(1){
		bzero(buf,sizeof(buf));
		ret= read(0,buf,sizeof(buf));
		if(ret>0) printf("buf=%s",buf );

	}
	return 0;
}