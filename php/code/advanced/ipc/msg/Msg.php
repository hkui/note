<?php
/**
 * Created by PhpStorm.
 * User: 764432054@qq.com
 * Date: 2019/9/29
 * Time: 23:03
 */

class Msg
{
    public $msgKey;
    public $queue;
    public function __construct()
    {
        $this->msgKey= ftok(__FILE__, 'b');
        $this->queue= msg_get_queue($this->msgKey, 0666);
        return $this->queue;
    }
    public function send($msg_type,$data){
        return msg_send($this->queue, $msg_type, $data);
    }
    public function rcv($desiredmsgtype){
        msg_receive($this->queue, $desiredmsgtype,$msgtype,1000,$message);
        return [$msgtype=>$message];
    }
}



