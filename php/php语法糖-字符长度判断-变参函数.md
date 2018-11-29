## 1.常见的php语法糖,并不是函数,语言结构
```php
echo();print();die();
isset();unset();
include();include_once();require(),require_once()
array(),list(),empty(),eval()
```
---
## 2.判断字符串长度
```php
$str="hello";
if( strlen($str) == 5){ echo 5; }
if( !isset($str[5])){}

```
## 3.定义变长参数函数
```php
function add(...$num){
    print_r(func_get_args());
    $sum=array_sum($num);
    return $sum;
}
echo add(1,2,3);
```
##### 输出结果
```
Array
(
    [0] => 1
    [1] => 2
    [2] => 3
)
6
```
