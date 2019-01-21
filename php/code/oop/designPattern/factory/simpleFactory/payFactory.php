<?php
/**
 * Created by PhpStorm.
 * User: 764432054@qq.com
 * Date: 2019/1/20
 * Time: 21:45
 */

namespace code\oop\designPattern\factory\simpleFactory;


class payFactory
{
    public static function createPayWeixin()
    {
        return new payWeixin();

    }
    public static function createPayAli(){
        return new payAli();
    }

    public static function createPayByType($type){
        switch ($type){
            case 1:
                $pay= new payWeixin();
                break;
            case 2:
                $pay= new payAli();
                break;
            default:
                throw new \InvalidArgumentException("暂不支持的支付方式");


        }
        return $pay;
    }

}