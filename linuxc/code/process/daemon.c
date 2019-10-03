#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>

#define FNAME "/tmp/out"

 static int daemonize(){
    pid_t pid;
    int fd;
    pid=fork();
    if(pid<0){
        return -1;
    }
    if(pid>0) exit(0);
    fd=open("/dev/null",O_RDWR);
    if(fd<0){
        return -2;
    }
    dup2(fd,0);
    dup2(fd,1);
    dup2(fd,2);
    if(fd>2){
        close(fd);
    }
    setsid();
    chdir("/");
    umask(0);
    return 0;
}

int main(){
    int i;
    FILE *fp;
    openlog("daemon",LOG_PID,LOG_DAEMON);
    if(daemonize()){
        syslog(LOG_ERR,"daemonize() failed!");
        exit(1);
    }
    fp=fopen(FNAME,"w");
    if(fp==NULL){
        syslog(LOG_ERR,"open %s failed",FNAME);
        exit(1);
    }
    syslog(LOG_INFO,"%s was opened",FNAME);
    for(i=0;;i++){
        fprintf(fp,"%d\n",i);
        fflush(fp);
        syslog(LOG_DEBUG,"%d was printed",i);
        sleep(1);
    }
    fclose(fp);
    return 0;
}
//tail -f /var/log/messages   查看日志
/**
[root@hkui process]# ps --pid 25365 -o pid,ppid,pgid,sid
  PID  PPID  PGID   SID
25365     1 25365 25365
 */
