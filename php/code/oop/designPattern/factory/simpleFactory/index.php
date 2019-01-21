<?php
/**
 * 简单工厂模式
 */
namespace code\oop\designPattern\factory\simpleFactory;

require dirname(__FILE__).'/../../../../init.php';




//多处调用的情况下如果将来要改,比如把payWexin改名或者修改传入的参数，会改很多地方，难以维护
$payWeixin=new payWeixin();
$payAli=new payAli();


//统一获取

$payWeixin=payFactory::createPayWeixin();
$payAli=payFactory::createPayAli();


//持续改进

$payWeixin=payFactory::createPayByType(1);

$payAli=payFactory::createPayByType(2);

/**
 * 上面代码如果添加新的支付方式 要么的添加create某某某
 * 要么得改createPayByType的switch
 *
这就违反了开放封闭原则；
开放封闭原则简单来说就是对扩展开放对修改封闭；
理想情况下我们是不应该再改动 Factory 类的；
增加新运算应该使用扩展的方式；
这就是简单工厂的弊端了；
 */















