<?php
namespace code\oop\designPattern\factory\simpleFactory;

include dirname(__FILE__).'/../../../../init.php';

//�ദ���õ�������������Ҫ��pay����ĺܶ�ط�������ά��
$oldpay=new pay();


//ֻ��Ҫ��pay�������createPay����
$pay=payFactory::createPay();












