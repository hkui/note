<?php
/**
 * �򵥹���ģʽ
 */
namespace code\oop\designPattern\factory\simpleFactory;

require dirname(__FILE__).'/../../../../init.php';




//�ദ���õ�������������Ҫ��,�����payWexin���������޸Ĵ���Ĳ�������ĺܶ�ط�������ά��
$payWeixin=new payWeixin();
$payAli=new payAli();


//ͳһ��ȡ

$payWeixin=payFactory::createPayWeixin();
$payAli=payFactory::createPayAli();


//�����Ľ�

$payWeixin=payFactory::createPayByType(1);

$payAli=payFactory::createPayByType(2);

/**
 * ��������������µ�֧����ʽ Ҫô�����createĳĳĳ
 * Ҫô�ø�createPayByType��switch
 *
 ���Υ���˿��ŷ��ԭ��
���ŷ��ԭ�����˵���Ƕ���չ���Ŷ��޸ķ�գ�
��������������ǲ�Ӧ���ٸĶ� Factory ��ģ�
����������Ӧ��ʹ����չ�ķ�ʽ��
����Ǽ򵥹����ı׶��ˣ�
 */















