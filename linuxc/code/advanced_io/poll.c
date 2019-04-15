#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <sys/time.h>  
#include <unistd.h>
#include <poll.h>




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
	struct pollfd fds[2];
	
	

	mousefd =open("/dev/input/mouse1",O_RDONLY); //可能Mouse0或2
	if(mousefd == -1) print_err("open mouse0 fail",__LINE__,errno);

	 fds[0].fd=0;
	 fds[0].events=POLLIN;
	 fds[1].fd=mousefd;
	 fds[1].events=POLLIN;
	
	while(1){
		 label:ret =poll(fds,2,3000);
		 	   if(ret == -1 && errno == EINTR) goto label;
		 	   else if(ret == -1) printf("poll fail",__LINE__,errno);
		 	   else if(ret>0){
		 	   		if(fds[0].events == fds[0].revents){
		 	   			bzero(buf,sizeof(buf));
		 	   			ret = read(fds[0].fd,buf,sizeof(buf));
		 	   			if(ret>0) printf("buf=%s\n",buf);
		 	   		}
		 	   		if(fds[1].events == fds[1].revents){
		 	   			bzero(&coord,sizeof(coord));
		 	   			ret = read(fds[1].fd,&coord,sizeof(coord));
		 	   			if(ret>0) printf("coord=%u\n",coord);
		 	   		}
		 	   }else if(ret ==0){
		 	   		printf("time out\n");
		 	   }


	}
	return 0;
}