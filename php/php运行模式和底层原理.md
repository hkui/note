# 1.php运行的模式
> SAPI:Server Application Programming Interface 服务器端应用编程端口。
它就是PHP与其它应用交互的接口，PHP脚本要执行有很多种方式，通过Web服务
器，或者直接在命令行下，也可以嵌入在其他程序中
SAPI 提供了一个和外部通信的接口, 常见的有五大运行模式

* cgi (通用网关接口Common Gateway Interface)
* fast-cgi (fast-cgi 是cgi的升级版本 比如php-fpm)
* cli (Command Line Interface)
* isapi (Internet Server Application Program Interface，是微软提供的一套面向Internet服务的API接口)
* apache2handler (将php作为apache的模块, nginx类似)
* 其他(continuity, embed, litespeed, milter等)

### CLI模式
> Command Line Interface的简称，即PHP命令行接口，在windows和linux下
都支持PHP-CLI模式,它可以直接在命令行下运行,那就意味着完全可以不要任何
http容器. 例如 php test.php
##### 应用场景
* 定时任务
* 开发桌面应用就是使用PHP-CLI和GTK包
* 开发shell脚本
##### 优点和缺点
> 利用crontab去跑php，可以给服务器减压，当然在这里有一个条件，就是实时性要
求不高的场景,无法为普通用户提供http服务
```php
print_r($argv);
print_r($argc);
```
```
[root@centos1 web]# php md.php a b 1 2
Array
(
    [0] => md.php
    [1] => a
    [2] => b
    [3] => 1
    [4] => 2
)
5
```

### CGI模式
> CGI即通用网关接口( Common Gateway Interface )，它是一段程序, 通俗的讲
CGI就象是一座桥，把网页和WEB服务器中的执行程序连接起来，它把http服务器
接收的指令传递给执行程序，再把执行程序的结果返还给http服务器。CGI 的跨
平台性能极佳，几乎可以在任何操作系统上实现

#### 执行过程
* http服务器接受到用户请求后, 例如 index.php,会通过它配置的CGI服务来执行
* 生成一个php-cgi.exe的进程,并执行php程序
* 执行的返回结果交给http服务器
#### 应用场景
* 提供http服务
##### 优点和缺点
* 跨平台,几乎可以在任何操作系统上实现.
* web和server是独立的,结构清晰,可控性强
* 性能比较差,来一个请求,fork一个进程,100个请求就会fork100进程,消耗资源较多(fork-and-execute 模式),最近几年已经很少见到使用这种模式了

### FASTCGI模式
> 快速通用网关接口（ Fast Common Gateway Interface／FastCGI ）是一种让交
互程序与Web服务器通信的协议。FastCGI是早期通用网关接口（CGI）的增强版
本。FastCGI致力于减少Web服务器与CGI程序之间互动的开销，从而使服务器可
以同时处理更多的网页请求

##### 执行过程
+ web服务器启动时 ,载入FastCGI进程管理器
+ FastCGI进程管理器会启动多个CGI进程等待web服务器的链接.
+ 当客户端请求到达Web Server时，FastCGI进程管理器选择并连接到一个CGI解释
器。Web server将环境变量和标准输入发送到FastCGI子进程php-cgi
+ FastCGI子进程完成处理后将标准输出和错误信息从同一连接返回Web Server。当
FastCGI子进程关闭连接时，请求便告处理完成。FastCGI子进程接着等待并处理来
自FastCGI进程管理器(运行在Web Server中)的下一个连接。 在CGI模式中，
php-cgi在此便退出了。
##### 应用场景
* 提供http服务
#### 优点和缺点
* 跨平台,几乎可以在任何操作系统上实现.
* web和server是独立的,结构清晰,可控性强,并不需要web升级而变化
* 支持大并发
* 多进程,消耗较多内存

### 模块运行模式(mod-php)
> 模块模式指将php作为web服务器的一个模块运行
##### 应用场景
* 提供http服务
##### 优点和缺点
* 安装配置方便，不需要安装代码解析程序
* 支持多线程，占用资源少
* 支持大并发(不如fast-cgi)
# 2.服务器网络模型


# 3.PHP运行机制与原理


# 4.PHP底层源码分析

