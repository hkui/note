
# php代码

```php
    <?php
	public static function OpenCityAllOut(){
	    static $out_all_city;
	    if($out_all_city) return $out_all_city;
	    $out_all_city=array_filter(self::$open_city_all,function($v){
	        if($v['show']){
	            return $v;
	        }
	    });
	    return $out_all_city;
	}
```
# 表格
name|age|分数
--|:--:|--:
小明|28|90
小k|22|98
晓东|25|100

## 流程图
```
graph LR;  
　　A-->B;    
　　A-->C;  
　　B-->D;  
　　C-->D; 
```

## 时序图
```
sequenceDiagram
　　　participant Alice
　　　participant Bob
　　　Alice->John:Hello John, how are you?
　　　loop Healthcheck
　　　　　John->John:Fight against hypochondria
　　　end
　　　Note right of John:Rational thoughts <br/>prevail...
　　　John-->Alice:Great!
　　　John->Bob: How about you?
　　　Bob-->John: Jolly good!
```

# 甘特图
```
gantt
　　　dateFormat　YYYY-MM-DD
　　　title Adding GANTT diagram functionality to mermaid
　　　section A section
　　　Completed task　　:done, des1, 2014-01-06,2014-01-08
　　　Active task 　　　　:active, des2, 2014-01-09, 3d
　　　future task 　　　　:　　　  des3, after des2, 5d
　　　future task2　　　　:　　　  des4, after des3, 5d
　　　section Critical tasks
　　　Completed task in the critical line　:crit, done, 2014-01-06,24h
　　　Implement parser and json　　　　　　:crit, done, after des1, 2d
　　　Create tests for parser　　　　　　　:crit, active, 3d
　　　Future task in critical line　　　　　:crit, 5d
　　　Create tests for renderer　　　　　　:2d
　　　Add to ,mermaid　　　　　　　　　　　:1d
```
