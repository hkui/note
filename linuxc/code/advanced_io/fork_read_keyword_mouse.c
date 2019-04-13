#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
 #include <unistd.h>
//多进程方式同时读取鼠标和键盘
void print_err(char *str,int line,int err_no){
	printf("%d,%s:%s\n",line,str,strerror(err_no) );
	exit(-1);
}

int main(int argc, char const *argv[])
{
	int coord;
	int mousefd =-1;

	char buf[100]={0};
	int ret= 0;
	pid_t fd=0;

	ret=fork();
	//父进程读鼠标
	if(ret >0){
		mousefd =open("/dev/input/mouse1",O_RDONLY); //可能Mouse0或2
		if(mousefd == -1) print_err("open mouse0 fail",__LINE__,errno);
		while(1){
			printf("--begin read mouse--\n");
			ret = read(mousefd,&coord,sizeof(coord)); //读鼠标
			if(ret >0 )printf("coord=%u\n", coord);
			printf("--end mouse--\n");
		}

	}else if(ret ==0 ){   //子进程读键盘
		while(1){
			printf("--keyword read start--\n");
			ret =read(0,buf,sizeof(buf));  //读键盘
			if(ret >0 )printf("buf=%s", buf);
			printf("--keyword read end--\n");
		}
		
	}else{
		printf("fork err\n" );
		exit(0);
	}

	
	return 0;
}