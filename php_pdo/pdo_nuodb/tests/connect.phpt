--TEST--
PDO_Nuodb: connect/disconnect
--SKIPIF--
<?php include("skipif.inc"); ?>
--FILE--
<?php /* $Id: connect.phpt 161049 2012-03-26 01:37:06Z tgates $ */

	require("testdb.inc");
    
	$db = new PDO("nuodb:dbname=$test_base",$user,$password) or die;
	unset($db);
	echo "done\n";
	
?>
--EXPECT--
done
