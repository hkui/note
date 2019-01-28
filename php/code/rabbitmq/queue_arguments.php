<?php

include(__DIR__ . '/config.php');

use PhpAmqpLib\Connection\AMQPStreamConnection;
use PhpAmqpLib\Wire\AMQPTable;
use PhpAmqpLib\Message\AMQPMessage;



$delay_queue_name='delay';
$delay_exchange_name="delay_exchange";

$connection = new AMQPStreamConnection(HOST, PORT, USER, PASS, VHOST);
$channel = $connection->channel();



$delay_time=mt_rand(15000,30000);
$delay_time=10000;
$delay_name=$delay_queue_name."-".$delay_time;




$channel->queue_declare($delay_name, false, true, false, false, false, new AMQPTable(array(
   "x-dead-letter-exchange" => 'router',
   "x-message-ttl" => $delay_time,
   "x-expires" => $delay_time+1000
)));



$channel->exchange_declare($delay_exchange_name, 'direct', false, true, false);

$channel->queue_bind($delay_name, $delay_exchange_name);

$messageBody = date("Y-m-d H:i:s")."--".$delay_time;

$message = new AMQPMessage($messageBody, array('content_type' => 'text/plain', 'delivery_mode' => AMQPMessage::DELIVERY_MODE_PERSISTENT));
$channel->basic_publish($message, $delay_exchange_name);

$channel->close();
$connection->close();
