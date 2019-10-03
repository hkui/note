```
fork            注意fork前父进程要刷新缓冲区
fork_file   父子进程分别打开 相同文件，各自不同的fd
fork_file1  父子进程打开文件fd,子进程继承，然后操作fd
fork_primer     父进程fork多个子进程来判断质数
fork_primer_wait 父进程fork多个子进程来判断质数,带回收子进程
fork_primer_num  指定fork 固定进程数 处理多个任务(交叉分配)
```

```
exec/exec 基本execl
exec/exec_fork
exec/exec_son   exec_fork里fork后装载的子程序
```

```
mysh.c  shell内部命令实现部分
mysu    sudo
daemon  守护

```

