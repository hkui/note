## 1.太空船操作符
 > 用于比较2个表达式，例如当$a小于，等于或大于$b时，分别返回-1,0,1
 ```php
echo 1 <=> 1;  //0
echo PHP_EOL;
echo 1 <=> 2;  //-1
echo PHP_EOL;
echo 2 <=> 1; //1
 ```

## 2.标量类型和返回值类型声明
* php7可对字符串(string),整型(int),浮点以及布尔类型的参数做声明。
* 参数类型声明不受制于默认模式和严格模式，默认模式下，当传入的参数不符合声明类型时，会首先尝试类型转换(这里的类型转换仅仅适用于**可转换**的类型，把'a'转换为Int也会报错)，而严格模式下则直接报错
```php
declare(strict_types=1); //strict_types=1表示严格模式
function sum(int ...$ints){
	return array_sum($ints);
}
var_dump(sum(1,'2','3.1',4.1));
```
###### 执行结果
```
Fatal error: Uncaught TypeError: Argument 2 passed to sum() must be of the type integer, string given
```
* 如果关闭严格模式，传入的参数会先转换为Int，结果为10
### 返回值类型受限制的
 下面代码声明返回值为int
```php
declare(strict_types=1); 
function sum(int ...$ints):int
{
	return array_sum($ints);
}
var_dump(sum(1,2,3)); //6
```
> php7.1对函数返回值类型做了扩充，可定义返回值类型为void,无论是否开启严格模式，==只要函数有"return;" 以外的其它return语句都会报错==

```php
declare(strict_types=1); 
function sum(int ...$ints):void
{
	// return NULL; //报错
	return ; //后面有 "return;"之外的语句也报错 
	// return array_sum($ints);
}
var_dump(sum(1,2,3));
```
> php7.1对参数类型和返回值类型还有进一步的支持，其类型可以使空类型，在参数或者返回值类型声明前加上"?"表示要么是null,要么是声明的类型
```php
declare(strict_types=1); 
function test(?int $a):?int
{
	return $a;
}
var_dump(test(null)); //NULL 
var_dump(test(1));  //int(1)
var_dump(test('a'));  // Fatal error
```

## 3.null合并操作符
```php
$page=isset($_GET['p'])?$_GET['p']:0;
//php7
$page =$_GET['p'] ??0;

//三元运算符
$page =$_GET['p'] ?? $_POST['p'] ??0;

```
## 4.常量数组
> php7之前无法通过define来定义一个常量数组的，php7支持了这个操作
```
define('STUDENT',['boy','girl']);
print_r(STUDENT);
```

## 5.namespace批量导入
```php
//php7之前
use Space\ClassA;
use Space\ClassB;
use Space\ClassC C;

//php7
use Space\{ClassA,ClassB,ClassC as C};
```

## 6.throwable接口
* 在php7之前，如果代码中有语法错误或者fatal error时，程序会直接报错退出，php7中实现了全局throwable接口，原来的Exception和部分Error实现了该接口

* 这种Error可以像Exception一样被第一个匹配的try/catch块捕获。如果没有匹配的catch块，则调用异常函数处理。如果尚未注册异常处理函数，则按照传统方式处理(Fatal error)

* Error类并非继承自Exception,所以不能用catch(Exception $e){}来捕获，可用catch(Error $e){} ,或者通过注册异常处理函数(set_exception_handler())来捕获Error

```php
try{
	abc();
}catch (Error $e){
	print_r($e);
}
echo 123;

```
##### php5里 Fatal error ,立即退出 之后的代码不会执行了
##### php7里
```
Error Object
(
    [message:protected] => Call to undefined function abc()
    [string:Error:private] => 
    [code:protected] => 0
    [file:protected] => /mnt/hgfs/www/web/md.php
    [line:protected] => 4
    [trace:Error:private] => Array
        (
        )

    [previous:Error:private] => 
)
123
```
### 或者通过注册异常处理函数来处理
```php
set_exception_handler(function($e){
	echo "err:".print_r($e,true);
	
});

abc();
echo 123;
```
php7下结果,php5依然Fatal error
```
err:Error Object
(
    [message:protected] => Call to undefined function abc()
    [string:Error:private] => 
    [code:protected] => 0
    [file:protected] => /mnt/hgfs/www/web/md.php
    [line:protected] => 7
    [trace:Error:private] => Array
        (
        )

    [previous:Error:private] => 
)
之后的也不会执行了

```

## 7.Closure::call()
#### 在php7之前，当动态的给一个对象添加方法时，可以通过Closure来复制一个闭包对象，并绑定到一个$this对象和类作用域
```php
class People{
	private $age=10;
}
$f=function(){
	return $this->age+1;
};

$p=$f->bindTo(new People,'People');
echo $p();
```
#### 在php7可通过call来暂时绑定一个闭包对象到$this对象并调用它
```php
class People{
	private $age=10;
}
$f=function(){
	return $this->age+1;
};

echo $f->call(new People);
```

## 8.intdiv
```php
echo intdiv(10,3);
```

## 9.list方括号写法
```php
$a=[1,2,3];
list($n1,$n2,$n3)=$a;

//php7
[$n1,$n2,$n3]=[4,5,6]; //[]并不是数组，而是list的简略形式
```

## 10.foreach遍历数组不再修改内部指针
```php
$arr=[1,2,3,4,5,6];
foreach ($arr as $key => $value) {
	if($value ==2) break;
}
echo current($arr);//php7下 1，php5下 3

```
## 11.匿名类可以使用 new class来定义,匿名类可以使用来代替完整的定义
```php
interface Cache{
	public function read ();
}
class Ca {
	private $cache;
	public function setcache(Cache $cache){
		$this->cache=$cache;
	}

}
$fcache =new Ca;
$fcache->setcache(new Class implements Cache {
	public function read(){

	}
});
```


> 其它，移除ASP和script PHP标签，移除$HTTP_RAW_POST_DATA、匿名类、常量类可见性等



