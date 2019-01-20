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
    public static function createPay()
    {
        return new pay();

    }

}