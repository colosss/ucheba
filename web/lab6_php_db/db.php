<?php
mysqli_report(MYSQLI_REPORT_ERROR | MYSQLI_REPORT_STRICT);

$host = 'localhost';
$user = 'root';
$password = '';
$database = 'lab6_computer_shop';

$link = mysqli_connect($host, $user, $password, $database);
mysqli_set_charset($link, 'utf8mb4');
?>
