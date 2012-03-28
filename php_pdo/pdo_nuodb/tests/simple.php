<?php /* $Id: connect.phpt 161049 2012-03-26 01:37:06Z tgates $ */

$db = new PDO("nuodb:dbname=test_base","CLOUD","user") or die;
unset($db);
echo "done\n";

?>