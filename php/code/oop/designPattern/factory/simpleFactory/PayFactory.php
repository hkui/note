<?php
/**
 * Created by PhpStorm.
 * User: 764432054@qq.com
 * Date: 2019/1/20
 * Time: 21:45
 */

namespace code\oop\designPattern\factory\simpleFactory;


class PayFactory
{
    public static function createPayWeixin()
    {
        return new PayWeixin();

    }
    public static function createPayAli(){
        return new PayAli();
    }

    public static function createPayByType($type){
        switch ($type){
            case 1:
                $pay= new PayWeixin();
                break;
            case 2:
                $pay= new PayAli();
                break;
            default:
                throw new \InvalidArgumentException("暂不支持的支付方式");


        }
        return $pay;
    }

}