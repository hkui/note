#include "file_lock.h"

void print_err(char *str,int line,int err_no){
	printf("%d,%s:%s\n",line,str,strerror(err_no) );
	exit(-1);
}

int main(int argc, char const *argv[])
{
	int fd =-1;
	int ret= 0;

	fd =open("./file",O_RDWR|O_CREAT|O_TRUNC,0664); 
	if(fd == -1) print_err("open fail",__LINE__,errno);

	ret =fork();
	if(ret > 0){
		while(1){
			SET_WRFLCK_W(fd,SEEK_SET,0,0);
			write(fd,"php",3);
			write(fd,"java\n",5);
			UNLCK(fd,SEEK_SET,0,0);
		}
	}else if(ret == 0){
		while(1){
			SET_WRFLCK_W(fd,SEEK_SET,0,0);
			write(fd,"js",2);
			write(fd,"css\n",3);
			UNLCK(fd,SEEK_SET,0,0);
		}
	}
	return 0;
}