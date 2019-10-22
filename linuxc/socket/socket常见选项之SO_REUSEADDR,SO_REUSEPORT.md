###### 目录
* [SO_REUSEADDR](#SO_REUSEADDR)
    * [time-wait](#time-wait) 
* [SO_REUSEPORT](#SO_REUSEPORT)

##### <div id='SO_REUSEADDR'>SO_REUSEADDR</div>
一般来说，一个端口释放后会等待两分钟之后才能再被使用，SO_REUSEADDR是让端口释放后立即就可以被再次使用

```SO_REUSEADDR```用于对TCP套接字处于TIME_WAIT状态下的socket，才可以重复绑定使用        
server程序总是应该在<b>调用bind()之前设置SO_REUSEADDR套接字选项</b>   
TCP，先调用close()的一方会进入TIME_WAIT状态

#### SO_REUSEADDR提供如下四个功能：
* 允许启动一个监听服务器并捆绑其众所周知端口，即使以前建立的将此端口用做他们的本地端口的连接仍存在。这通常是重启监听服务器时出现，若不设置此选项，则bind时将出错
* 允许在同一端口上启动同一服务器的多个实例，只要每个实例捆绑一个不同的本地IP地址即可。对于TCP，我们根本不可能启动捆绑相同IP地址和相同端口号的多个服务器。
* 允许单个进程捆绑同一端口到多个套接口上，只要每个捆绑指定不同的本地IP地址即可。这一般不用于TCP服务器。
* SO_REUSEADDR允许完全重复的捆绑：      
    当一个IP地址和端口绑定到某个套接口上时，还允许此IP地址和端口捆绑到另一个套接口上。一般来说，这个特性仅在支持多播的系统上才有，而且只对UDP套接口而言（TCP不支持多播）。

###### SO_REUSEPORT选项有如下语义：
此选项允许完全重复捆绑，但仅在想捆绑相同IP地址和端口的套接口都指定了此套接口选项才行。

如果被捆绑的IP地址是一个多播地址，则SO_REUSEADDR和SO_REUSEPORT等效。

使用这两个套接口选项的建议：        
* 在所有TCP服务器中，在调用bind之前设置SO_REUSEADDR套接口选项；       
* 当编写一个同一时刻在同一主机上可运行多次的多播应用程序时，设置SO_REUSEADDR选项，并将本组的多播地址作为本地IP地址捆绑

#### <div id='time-wait'>time-wait</div>
##### TIME_WAIT状态有两个存在的理由：
* (1)可靠地实现TCP全双工连接的终止
* (2)允许老的重复分节在网络中消逝
![](https://note.youdao.com/yws/api/personal/file/15F9C69E8B9A47D3A4DD0CA857ACC1C6?method=download&shareKey=b442ee3b55a776456a5e63515f0b847f)

> 如图所示,在主机A的4次挥手过程中，如果最后的数据丢失，则主机B会认为A未能收到自己发送的FIN消息，因此重传。这时，收到FIN消息的主机A将重启time-wait计时器。因此，如果网络状态不佳，time-wait状态将持续

(1)如果服务器最后发送的ACK因为某种原因丢失了，那么客户一定会重新发送FIN，这样因为有TIME_WAIT的存在，服务器会重新发送ACK给客户，如果没有TIME_WAIT，那么无论客户有没有收到ACK，服务器都已经关掉连接了，此时客户重新发送FIN，服务器将不会发送ACK，而是RST，从而使客户端报错。也就是说，TIME_WAIT有助于可靠地实现TCP全双工连接的终止。

(2)如果没有TIME_WAIT，我们可以在最后一个ACK还未到达客户的时候，就建立一个新的连接。那么此时，如果客户收到了这个ACK的话，就乱套了，必须保证这个ACK完全死掉之后，才能建立新的连接。也就是说，TIME_WAIT允许老的重复分节在网络中消逝。

　　回到我们的问题，由于我并不是正常地经过四次断开的方式中断连接，所以并不会存在最后一个ACK的问题。所以，这样是安全的。不过，最终的服务器版本，还是不要设置为端口可复用的
```php
<?php
$address = '0.0.0.0';
$port = $argv[1] ?? 8071;
$listen = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if (false === $listen) errhandle(__LINE__);
//ctrl+c重启时 能立马重启,要在bind,listen之前
if (true !== socket_set_option($listen, SOL_SOCKET, SO_REUSEADDR, 1)) errhandle(__LINE__);;

if (true !== socket_bind($listen, '0.0.0.0', $port)) errhandle(__LINE__);;
if (true !== socket_listen($listen, 5)) errhandle(__LINE__);;  //待连接队列长度
//socket_set_nonblock($listen);

echo "Server linsten on:{$address}:$port" . PHP_EOL;

while (true) {
    //连接socket，处理连接的接入
    $sock_client = socket_accept($listen);
    if (false === $sock_client) {
        errhandle(__LINE__,false);
        continue;
    }
    processClientConn($sock_client);
}

//处理已经连入的连接
function processClientConn($sock_client)
{
    if (socket_getpeername($sock_client, $clinet_addr, $client_port)) {
        echo "New client " . intval($sock_client) . " come from  {$clinet_addr}:$client_port" . PHP_EOL;
        sayWelcome($sock_client);
    }
    while (true) {
        //接收到不少于len
        $len = socket_recv($sock_client, $buf, 2048, 0);
        if ($len === false) {
            echo "no data" . PHP_EOL;
            continue;
        } elseif ($len === 0) {
            errhandle(__LINE__,false);
            socket_shutdown($sock_client);
            break;
        } else {
            echo "recv:{" . $buf . "}len=" . $len . PHP_EOL;
            if ($buf == 'quit') {
                socket_shutdown($sock_client);
                break;
            }
        }
    }
}

function errhandle($line_num,$exit=true)
{
    echo $line_num.":".socket_last_error() . ":" . socket_strerror(socket_last_error()) . PHP_EOL;
    if($exit){
        exit();
    }

}
function sayWelcome($client)
{
    $buf = date("H:i:s") . " welcome to server! you id:" . intval($client) . PHP_EOL;
    socket_write($client, $buf, strlen($buf));
}

```

#### <div id='SO_REUSEPORT'>SO_REUSEPORT</div>

目前常见的网络编程模型就是多进程或多线程，根据accpet的位置，分为如下场景
2种场景
* (1)单进程或线程创建socket，并进行listen和accept，接收到连接后创建进程和线程处理连接
* (2)单进程或线程创建socket，并进行listen，预先创建好多个工作进程或线程accept()在同一个服务器套接字

这两种模型解充分发挥了多核CPU的优势,虽然可以做到线程和CPU核绑定，但都会存在：

* 单一listener工作进程或线程在高速的连接接入处理时会成为瓶颈
* 多个线程之间竞争获取服务套接字
* 缓存行跳跃
* 很难做到CPU之间的负载均衡
* 随着核数的扩展，性能并没有随着提升


#### SO_REUSEPORT解决了什么问题
SO_REUSEPORT支持多个进程或者线程绑定到同一端口，提高服务器程序的性能，解决的问题：

* 允许多个套接字 bind()/listen() 同一个TCP/UDP端口
* 每一个线程拥有自己的服务器套接字
* 在服务器套接字上没有了锁的竞争
* 内核层面实现负载均衡
* 安全层面，监听同一个端口的套接字只能位于同一个用户下面

#### 其核心的实现主要有三点：

* 扩展 socket option，增加 SO_REUSEPORT 选项，用来设置 reuseport  
* 修改 bind 系统调用实现，以便支持可以绑定到相同的 IP 和端口  
* 修改处理新建连接的实现，查找 listener 的时候，能够支持在监听相同 IP 和端口的多个 sock 之间均衡选择。    
有了SO_RESUEPORT后，每个进程可以自己创建socket、bind、listen、accept相同的地址和端口，各自是独立平等的  
让多进程监听同一个端口，各个进程中accept socket fd不一样，有新连接建立时，内核只会唤醒一个进程来accept，并且保证唤醒的均衡性。

https://www.cnblogs.com/Anker/p/7076537.html

http://www.blogjava.net/yongboy/archive/2015/02/12/422893.html

没用reuseport的     
[socket_fork_no_reuseport.php](https://gitee.com/hk/process_thread_study/blob/master/php/advanced/socket_fork_no_reuseport.php)

用了的  
[socket_fork_reuseport.php](
https://gitee.com/hk/process_thread_study/blob/master/php/advanced/socket_fork_reuseport.php)

