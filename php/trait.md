#### 1.执行顺序
* 优先使用当前类，再使用use的trait里的
```php
trait T1{
    public $name='T1';
	public function m1(){
		return __CLASS__.'-'.__METHOD__;
	}
    protected function m2(){
        return __CLASS__.'-'.__METHOD__;
    }
}
trait T2{
    public function m1(){
        return __CLASS__.'-'.__METHOD__;
    }
    public function m3(){
        return __CLASS__.'-'.__METHOD__;
    }
}
class T{
    use T1,T2;
    public function m1(){
        return __CLASS__.'-'.__METHOD__;
    }

}

$t=new T;
echo $t->m1();//T-T::m1
```
#### 2.多个trait冲突
##### 1.上面代码 如果当前类里没有m1(T1,T2里均有的方法),则会产生冲突,这时可设置优先使用哪个trait或者起别名T可改为以下
```php
class T{
    use T1,T2{
        T2::m1 insteadof T1;
    }
}

$t=new T;
echo $t->m1();//T-T2::m1
```
##### 2.或者起别名
```php
class T{
    use T1,T2{
        T1::m1 insteadof T2;
        T2::m1 as t2_m1;
    }
}

$t=new T;
echo $t->m1(),PHP_EOL,$t->t2_m1(); // T-T1::m1  T-T2::m1
```
#### 3.改变trait的访问权限
```php
trait T1{
	public function m1(){
		return __CLASS__.'-'.__METHOD__;
	}
    protected function m2(){
        return __CLASS__.'-'.__METHOD__;
    }
}
trait T2{
    public function m3(){
        return __CLASS__.'-'.__METHOD__;
    }
}
class T{
    use T1{
        m1 as protected;
        m2 as public;
    }
    use T2;
}

$t=new T;
//echo $t->m1(),PHP_EOL; // Call to protected method T::m1() from context ''
echo $t->m2(),PHP_EOL; //T-T1::m2
```
[trait](http://php.net/manual/zh/language.oop5.traits.php)

- [ ] trait与Yii2里behavior

