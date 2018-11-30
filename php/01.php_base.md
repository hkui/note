## 1.PHP编码规范
>https://github.com/PizzaLiu/PHP-FIG

## 2.运算符优先级
#### 2.1 、运算符有关的一道面试题
```php
$a=3;
$b=4;
if($a=3 ||$b=6){
    var_dump($a);
    $a++;
    var_dump($a);
    $a++;
    var_dump($a);
    ++$b;
}
echo $a,",",$b;
```
###### 结果
```
bool(true)
bool(true)
bool(true)
1,5
```
> 赋值运算符优先级小于逻辑运算符,$a=(3||$b=6), 3||$b=6,得到a=true,$b=6未执行到 true++永远是true,输出就是1

#### 复习下运算符优先级
结合方向|运算符|附加信息
--|--|--
无 |clone new |clone 和 new 
左 |[| array() 
右 |++ -- ~ (int) (float) (string) (array) (object) (bool) @| 类型和递增／递减
无 |instanceof |类型  
右 |! |逻辑运算符  
左 |* / % |算术运算符  
左 | + - . |算术运算符和字符串运算符 
左 |<< >> |位运算符  
无 | == != === !== <> |比较运算符  
左 |& |位运算符和引用 
左 |^ |位运算符  
左 | \| |位运算符  
左 | && |逻辑运算符  
左 |\|\| |逻辑运算符  
左 |? : |三元运算符  
右 |= += -= *= /= .= %= &= \|= ^= <<= >>= => | 赋值运算符  
左 |and |逻辑运算符  
左 |xor |逻辑运算符  
左 |or |逻辑运算符  
左 |, |多处用到 

#### 2.2 、count和一些基本变量
```php
<?php
$sum=count('123')+count(null)+count(false);
var_dump(count('123'));
var_dump(count(null));
var_dump(count(false));
var_dump(count(true));
echo $sum;
```
##### 结果
```
int(1)
int(0)
int(1)
int(1)
2
```

## 3.常见的php语法糖,并不是函数,而语言结构
```php
echo();print();die();
isset();unset();
include();include_once();require(),require_once()
array(),list(),empty(),eval()
```
---
## 4.判断字符串长度
```php
$str="hello";
if( strlen($str) == 5){ echo 5; }
if( !isset($str[5])){}

```
## 5.定义变长参数函数
```php
function add(...$num){
    print_r(func_get_args());
    $sum=array_sum($num);
    return $sum;
}
echo add(1,2,3);
```
###### 输出结果
```
Array
(
    [0] => 1
    [1] => 2
    [2] => 3
)
6
```
