#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define F "./file.txt"

int main(int argc, char const *argv[])
{
	pid_t ret = 0;
	int fd=0;
	char msg[20]={0};
	ret = fork();
	if(ret >0){
		sprintf(msg,"parent pid %d\n",getpid());
		fd=open(F,O_RDWR|O_CREAT,0644);
		while(1){
			write(fd,msg,strlen(msg));
			sleep(1);
		}
		
	}else if(ret == 0){
		sprintf(msg,"child  pid %d\n",getpid());
		fd=open(F,O_RDWR|O_CREAT,0644);
		while(1){
			write(fd,msg,strlen(msg));
			sleep(1);
		}
		
	}
	return 0;
}
