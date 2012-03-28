<?php /* $Id: testdb.inc 161049 2012-03-26 01:37:06Z tgates $ */

$user = 'CLOUD';
$password = 'user';
ini_set('nuodb.default_user',$user);
ini_set('nuodb.default_password',$password);

/* we need just the generated name, not the file itself */
unlink($test_base = tempnam('/tmp',"php_nuodb_test"));

function init_db()
{
	global $test_base, $user, $password;

	$test_db = nuodb_query(NUODB_CREATE,sprintf("CREATE DATABASE '%s' USER '%s' PASSWORD '%s'",
		$test_base, $user, $password));
	$tr = nuodb_trans($test_db);
	nuodb_query($tr,"create table test1 (i integer, c varchar(100))");
	nuodb_commit_ret($tr);
	nuodb_query($tr,"insert into test1(i, c) values(1, 'test table not created with isql')");
	nuodb_commit($tr);
	nuodb_close($test_db);
}

function cleanup_db()
{
	global $test_base;
    
	$r = nuodb_connect($test_base);
	nuodb_drop_db($r);
}

register_shutdown_function('cleanup_db');
init_db();
