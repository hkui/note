<?php
require_once 'Msg.php';

$msg=new Msg();

$msgType=$argv[1]??1;
if($msgType <=0){
    echo "msgType must >0";
    exit();
}
$num=$argv[2]??1;
for($i=1;$i<=$num;$i++){
    $r=$msg->send($msgType,$msgType."--".$i);
    var_dump($r);
}

echo posix_getpid();
echo PHP_EOL;
