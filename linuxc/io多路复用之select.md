# 1、IO多路复用之select
> 比如在同时读取键盘和鼠标时，默认情况下都是阻塞的，那么如何同时读取键盘和鼠标呢，当他们有值时能及时读取出来呢
### 1.1、现在一般的方案有以下几种
* 多进程实现
* 多线程
* 将“读鼠标”和“读键盘”设置为非阻塞实现	
* 多路IO

#### 这里主要说的是多路IO,另外几种稍后奉上
![马上就到](https://note.youdao.com/yws/api/personal/file/7F31778A55EF4FB4A1064C1A56FFA4B7?method=download&shareKey=ea424e593e0667a0f235f373300264fc)
## **多路IO的工作原理**
* 使用多路IO时,不需要多进程、多线程以“多线任务”方式实现，也不需要用到非阻塞
* 以阻塞读为例 
![select](https://note.youdao.com/yws/api/personal/file/E9FE9D0A57954E51802445CC40EBD576?method=download&shareKey=1bfa35462b2d5e364a4e43a7bd013089)
> 如果是阻塞写的话，需要将文件描述符加入写集合，不过我们说过对于99%的情况来说，写操作不会阻塞，所以一般情况下对于写来说，使用多路Io没有意义

> 注意：对于多路io来说，只有操作阻塞的fd才有意义，如果文件描述符不是阻塞的，使用多路IO没有意义

### 多路IO有什么优势
* 比如以同时读写鼠标、读键盘为例，如果使用
* 多进程实现: 开销太大，绝对不建议这么做。
* 非阻塞方式: cpu空转，耗费cpu资源，不建议
* 多线程: 常用方法，不过多路IO也是一个不错的方法

### 多路IO
　　**使用多路IO时，多路IO机制由于在监听时如果没有动静的话，监听会休眠，因此开销也很低，相比多进程和非阻塞来说，多路IO机制也是很不错的方式**
### select和poll 多路IO有两种实现方式，分别是poll和select，其中select会比poll更常用些

## 多路io之select机制
### select函数
#### 函数原型
```c
#include <sys/select.h>
int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
```
#### 功能
* 监听集合中的描述符有没有动静，如果没有动静就阻塞
* 如果有动静就成功返回，返回值为集合中有动静的fd的数量
> 什么是动静:比如以读为例，如果fd有数据来了需要被read时，这就是动静
#### 参数
##### nfds：
 * nfds = readfds, writefds, exceptfds这三个集合中值最大的那个描述符+1。
 * nfds用于说明需要关心描述符的范围，这个范围必须覆盖所有集合中的文件描述符。
 * 比如“读集合”中包含0,3,6这三个文件描述符，写集合和异常集合为NULL（没有）nfds==6+1
 * 表示监听范围包含7描述符，描述符因为是从0算起的，所以监听范围所包含的描述符为0、1、 2、 3、 4、 5、 6

> 疑问：集合中只包含了0、3、6三个，但是为什么需要监听的有这么多，只能说人家select机制就是这么实现的，这个没办法
![无奈](https://note.youdao.com/yws/api/personal/file/48EF191800634C738F7023E63711850E?method=download&shareKey=d2d24057b39d5de74662df3f031506f0)
##### readfds、writefds、exceptfds：读、写、异常集合
* readfds：读结合，放读会阻塞的文件描述符
* writefds：写集合，放写会阻塞的描述符。
* exceptfds：放会异常出错的文件描述符。

> 常用的是读集合，写集合和异常集合基本用不到，所以这里不做介绍，写、异常集合不用时就写NULL

###### 至于如何将文件描述符放入集合中，可使用如下带参宏来实现

```c
void FD_CLR(int fd, fd_set *set)：将fd从集合set中清除，这个宏不常用
int FD_ISSET(int fd, fd_set *set)：判断是不是set中的fd有动静了
void FD_SET(int fd, fd_set *set)：将fd放到集合set中
void FD_ZERO(fd_set *set)：将整个集合全部清空
#比如：
fd_set readfds;//定义一个读集合
FD_ZERO(&readfds); //把集合全部清空
FD_SET(fd, &readfs);//将fd放到readfds集合

```

##### timeout：用于设置阻塞超的时间
* select函数监听集合时，如果没有任何动静的话就阻塞（休眠）
* 如果timeout被设置为NULL的话，select会永远阻塞下去，直到被信号中断或者集合中的某些文件描述符有动静了

> 如果你不想休眠太久的话，就可以设置超时时间，如果时间到了但是集合中的fd还没有任何动静，select就返回，然后不再阻塞，超时时的返回的值为0。

###### 成员结构如下

```c
struct timeval 
{
long tv_sec; /* seconds（秒） */
long tv_usec; /* microseconds （微秒）*/
};

```

* tv_sec：设置秒
* tv_usec：设置微妙
> 时间精度为微妙，也就是说可以设置一个精度为微妙级别的超时时间 由于select函数有超时功能，实际上可以使用select模拟出一个微妙级精度的定时器

#### 返回值
*  -1：说明函数调用失败，errno被设置
> select调用出错的情况有很多种，比如select在阻塞时被信号唤醒从而导致出错返回，
　　errno被设置为EINTR错误号，这个错误号表示函数是被信号中断而出错返回的。

##### 如果不想被信号中断
* 我们可以自己忽略、屏蔽这些信号
* 手动重启select的调用
```c
　  lable:	ret = select(...);
　　if(ret==-1 && errno==EINTR) goto lable;
　　else if(ret == -1) print_err(...);
```
　
* 0：超时时间到并且集合中没有一个描述符有响应时,就返回0
* \>0：集合中fd有动静时，函数返回有动静的文件描述符的数量
> 注意：select每次重新监听时需要重新设置“集合”和“超时时间”，因为每次select监听结束时会清空“集合”和“超时时间”
```c
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
#include <sys/time.h>  
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
                if(ret>0) printf("%s\n",buf );
            }
            if(FD_ISSET(mousefd, &readfds)){
                bzero(&coord,sizeof(coord));
                ret =read(mousefd,&coord,sizeof(coord));
                if(ret>0) printf("%u\n",coord);
            }
        }else if(ret ==0){
            printf("timeover\n");
        }

    }
    return 0;
}
```







