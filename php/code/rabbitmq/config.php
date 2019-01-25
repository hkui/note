<?php

require_once __DIR__ . '/../vendor/autoload.php';

define('HOST', '127.0.0.1');
define('PORT', 5672);
define('USER', 'admin');
define('PASS', 'admin');
define('VHOST', '/');

//If this is enabled you can see AMQP output on the CLI
define('AMQP_DEBUG', true);
