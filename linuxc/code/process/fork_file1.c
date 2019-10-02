//父子进程共用同一个fd 对文件进行操作

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define F "./file1.txt"

int main(int argc, char const *argv[])
{
	pid_t ret = 0;
	int fd=0;
	char msg[20]={0};
	fd=open(F,O_RDWR|O_CREAT|O_TRUNC,0644);
	ret = fork();
	if(ret >0){
		sprintf(msg,"parent pid %d\n",getpid());
		while(1){
			write(fd,msg,strlen(msg));
			sleep(1);
		}
		
	}else if(ret == 0){
		sprintf(msg,"child  pid %d\n",getpid());
		while(1){
			write(fd,msg,strlen(msg));
			sleep(1);
		}
		
	}
	return 0;
}
