#ifndef H_FILELOCK_H
#define H_FILELOCK_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

//非阻塞设置写锁
#define SET_WRFLCK(fd,l_whence,l_offset,l_len)\
		set_filelock(fd,F_SETLK,F_WRLCK,l_whence,l_offset,l_len)
//阻塞设置写锁
#define SET_WRFLCK_W(fd,l_whence,l_offset,l_len)\
		set_filelock(fd,F_SETLKW,F_WRLCK,l_whence,l_offset,l_len)
//非阻塞设置读锁
#define SET_RDFLCK(fd,l_whence,l_offset,l_len)\
		set_filelock(fd,F_SETLK,F_RDLCK,l_whence,l_offset,l_len)

//阻塞设置读锁
#define SET_RDFLCK_W(fd,l_whence,l_offset,l_len)\
		set_filelock(fd,F_SETLKW,F_RDLCK,l_whence,l_offset,l_len)

//解锁
#define UNLCK(fd,l_whence,l_offset,l_len)\
		set_filelock(fd,F_SETLK,F_UNLCK,l_whence,l_offset,l_len)


static void set_filelock(int fd,int ifwait,int l_type,int l_whence,int l_offset,int l_len){
	int ret =0;
	struct flock flck;

	flck.l_type=l_type;
	flck.l_whence=l_whence;
	flck.l_start=l_offset;
	flck.l_len=l_len;

	ret = fcntl(fd,ifwait,&flck);
	if(ret == -1){
		perror("fcntl fail");
		exit(-1);
	}


}
#endif











