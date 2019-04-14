#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <sys/select.h> 
#include <unistd.h>

void print_err(char *str,int line,int err_no){
	printf("%d,%s:%s\n",line,str,strerror(err_no) );
	exit(-1);
}

int main(int argc, char const *argv[])
{
	int coord=0;
	int mousefd =-1;
	fd_set readfds;

	char buf[100]={0};
	int ret= 0;

	struct timeval timeover;
	

	mousefd =open("/dev/input/mouse1",O_RDONLY); //可能Mouse0或2
	if(mousefd == -1) print_err("open mouse0 fail",__LINE__,errno);
	

	while(1){
		/*将0，mousefd加入读集合*/
		FD_ZERO(&readfds); //把集合全部清空
		FD_SET(0, &readfds);//将fd放到readfds集合中
		FD_SET(mousefd, &readfds);
		// 设置超时时间
		timeover.tv_sec=3;
		timeover.tv_usec=0;
		// 如果集合没动静就阻塞
		label:ret=select(mousefd+1,&readfds,NULL,NULL,&timeover);
		if(ret == -1 && errno == EINTR) goto label;
		else if(ret ==-1) print_err("select fail",__LINE__,errno);
		else if(ret >0){
			if(FD_ISSET(0, &readfds)){
				bzero(buf,sizeof(buf));
				ret =read(0,buf,sizeof(buf));
				if(ret>0) printf("buf=%s-\n",buf );
			}
			if(FD_ISSET(mousefd, &readfds)){
				bzero(&coord,sizeof(coord));
				ret =read(mousefd,&coord,sizeof(coord));
				if(ret>0) printf("coord=%u\n",coord);
			}
		}else if(ret ==0){
			printf("timeover\n");
		}

	}
	return 0;
}