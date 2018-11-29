>不用eval(),eval()能够执行所有php代码，非常危险
```php
eval('echo `pwd`;');
```
##### 但是往往通过口头约定是不行的,总有那么几个家伙不听，不长记性，所以必须有一种强制措施，从根源上避免

##### 从上节我们知道eval()是语言结构，并不是函数，所以使用disable_functions时不行的,要么你重新编译，一般我们会采用可以用php的扩展**Suhosin**来解决
```suhosin.executor.disable_eval = on ```

# suhosin介绍
> Suhosin是一个PHP程序的保护系统。它的设计初衷是为了保护服务器和用户抵御
PHP程序和PHP核心中，已知或者未知的缺陷。Suhosin有两个独立的部分，使用
时可以分开使用或者联合使用。第一部分是一个用于PHP核心的补丁，它能抵御缓
冲区溢出或者格式化串的弱点；第二部分是一个强大的PHP扩展，包含其他所有的
保护措施。

## 特性列表
#### 1）引擎保护（仅补丁）
* 保护内部的内存管理抵御缓冲区溢出
* 防止Zend哈希表被破坏
* 防止Zend链接列表被破坏
* 保护PHP核心及其扩展抵御格式化串弱点
* 某些libc realpath() 产生的错误
#### 2）各种特性
* 模拟器保护模式
* 增加两个函数sha256()和sha256_file()到PHP核心中
* 所有平台，加入CRYPT_BLOWFISH到函数crypt()中
* 打开对phpinfo()页的透明保护
* SQL数据库用户保护（测试阶段）
#### 3）运行时保护
* 加密cookies
* 允许禁止eval()函数
* 通过配置一个最大执行深度，来防止无穷递归
* 支持每个vhost配置黑白名单
* 防止mail()函数的新行攻击
* 防止preg_replace()的攻击
#### 4）Session 保护
* 加密session数据
* 防止session被劫持
* 防止超长的session id
* 防止恶意的session id

##### 下载安装
> http://www.hardened-php.net/suhosin/download.html

## 按照一般扩展的安装方法编译安装完后
> 在php.ini加入 ```extension=suhosin.so```

# 使用方法

### suhosin有三个选项控制eval
* suhosin.executor.eval.whitelist 白名单
* suhosin.executor.eval.blacklist 黑名单
* suhosin.executor.disable_eval 禁用eval
###### 很多程序需要eval，所以我们不能禁用，使用黑名单禁止一些危险的函数

#### 编辑ini
```
[Suhosin]
suhosin.executor.eval.blacklist=phpinfo,fputs,fopen,fwrite
```




