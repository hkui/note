<?php
namespace code\oop\designPattern\factory\simpleFactory;

include dirname(__FILE__).'/../../../../init.php';

//多处调用的情况下如果将来要改pay，会改很多地方，难以维护
$oldpay=new pay();


//只需要改pay工场里的createPay即可
$pay=payFactory::createPay();












