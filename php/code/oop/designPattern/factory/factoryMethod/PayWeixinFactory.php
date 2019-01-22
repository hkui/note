<?php
/**
 * Created by PhpStorm.
 * User: huangkui@lepu.cn
 * Date: 2019/1/22
 * Time: 14:00
 */

namespace code\oop\designPattern\factory\factoryMethod;


class PayWeixinFactory extends  PayFactory
{
    public function createPay()
    {
        return new PayWeixin();
    }
}