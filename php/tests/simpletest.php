<?php

$br = (php_sapi_name() == "cli")? "":"<br>";

$library_name = 'php_nuodb';
if (PHP_OS === 'Linux') {
   $library_name = 'lib'.$library_name;
}
echo $library_name."$br\n";

if(!extension_loaded($library_name)) {
	dl($library_name.'.' . PHP_SHLIB_SUFFIX);
}
$module = $library_name;
$functions = get_extension_funcs($module);
echo "\nFunctions available in the NuoDB extension:$br\n\n";
foreach($functions as $func) {
    echo $func."$br\n";
}
echo "$br\n";

$nuodb_conn = nuodb_connect("test@localhost", "cloud", "user", "hockey");
//echo nuodb_connect("test@ec2-107-20-199-139.compute-1.amazonaws.com");
$result = nuodb_query("drop table players2");
if (!$result)
  echo "Drop Error: ".nuodb_error()."\n";
$result = nuodb_query("commit");
if (!$result)
  echo "Commit Error: ".nuodb_error()."\n";
$result = nuodb_query("rollback");
if (!$result)
  echo "Rollback Error: ".nuodb_error()."\n";
$result = nuodb_query("create table players2 (lastname char(50), firstname char(50), age decimal(10))");
if (!$result)
  echo "Create Error: ".nuodb_error()."\n";
$result = nuodb_query("insert into players2(lastname, firstname, age) values('thomas1', NULL, 1)");
if (!$result)
  echo "Insert1 Error: ".nuodb_error()."\n";
$result = nuodb_query("insert into players2(lastname, firstname, age) values('thomas2', 'tim2', 2)");
if (!$result)
  echo "Insert2 Error: ".nuodb_error()."\n";
$result = nuodb_query("insert into players2(lastname, firstname, age) values('', NULL, 3)");
if (!$result)
  echo "Insert3 Error: ".nuodb_error()."\n";
$result = nuodb_query("select * from players2");
if (!$result)
  echo "Select1 Error: ".nuodb_error()."\n";
echo "\nDumping1 result array:\n\n";
for ($i=0; $row = nuodb_fetch_array($result); $i++) {
    var_dump($row);
}
$result = nuodb_query("delete from players2 where lastname = 'thomas2'");
if (!$result)
  echo "Delete Error: ".nuodb_error()."\n";
$result = nuodb_query("select * from players2");
if (!$result)
  echo "Select2 Error: ".nuodb_error()."\n";
echo "\nDumping2 result array:\n\n";
for ($i=0; $row = nuodb_fetch_array($result); $i++) {
    var_dump($row);
}
echo "\nFreeing result\n";
nuodb_free_result($result);
echo "Disconnecting\n\n";
nuodb_disconnect($nuodb_conn);
?>
