<?php
require_once 'Msg.php';
$msg=new Msg();
$desiredmsgtype=$argv[1]??0;

while(true){

    $stat_arr=msg_stat_queue($msg->queue);
    if($stat_arr['msg_qnum'] <1){
        break;
    }
    $r=$msg->rcv($desiredmsgtype);

    print_r($r);

}

echo posix_getpid();
echo PHP_EOL;
