#### 用户和权限
```
user/checkpass  验证用户名密码
```
#### 进程
```
process/fork            注意fork前父进程要刷新缓冲区
process/fork_file   父子进程分别打开 相同文件，各自不同的fd
process/fork_file1  父子进程打开文件fd,子进程继承，然后操作fd
process/fork_primer     父进程fork多个子进程来判断质数
process/fork_primer_wait 父进程fork多个子进程来判断质数,带回收子进程
process/fork_primer_num  指定fork 固定进程数 处理多个任务(交叉分配)

process/mysh.c  shell内部命令实现部分
process/mysu    sudo
process/daemon  守护

process/exec/exec 基本execl
process/exec/exec_fork
process/exec/exec_son   exec_fork里fork后装载的子程序
```
#### 信号
```
signal/signal  信号基本
signal/alarm
signal/pause
signal/slowcat  通过alarm 逐渐输出版本的cat，漏桶
signal/slowcat_setitimer  通过setitimer 逐渐输出版本的cat，漏桶
signal/slowcat2  令牌桶
signal/mytbf   令牌桶封装
signal/mytbf_sa    signal/mytbf升级版 区分信号来源是不是内核 sigaction,setitimer替换alarm,signal
signal/sigprocmask  信号屏蔽字操作
signal/sigsuspend  信号驱动程序
signal/sigsuspend_mysig  实时信号驱动程序

```



