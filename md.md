
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
#### 表格
name|age|分数
--|:--:|--:
小明|28|90
小k|22|98
晓东|25|100

##### 流程图github不支持 时序图github也不支持 test


### Todo list
- [x] 已完成
    - [x] 已完成1
    - [x] 已完成2
- [ ] 待办1
- [ ] 待办2

