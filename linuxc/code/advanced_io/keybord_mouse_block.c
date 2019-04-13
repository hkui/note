#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

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

	mousefd =open("/dev/input/mouse1",O_RDONLY); //可能Mouse0或2
	if(mousefd == -1) print_err("open mouse0 fail",__LINE__,errno);

	while(1){
		printf("-----begin-----\n");
		ret = read(mousefd,&coord,sizeof(coord)); //读鼠标

		//ret =read(0,buf,sizeof(buf));  //读键盘
		if(ret >0 )printf("%u\n", coord);
		printf("-----end-----\n");

	}
	return 0;
}