<?php
 
// test_db.php
// EN este ejemplo se muestra como se construyen consultas 
// usando parametros
 
require('ac_db_inc.php');

$Id=100; 
$Phone='728-28-22-744';


$db = new DbOracle("test_db", "ArchiSoft");
$sql = "UPDATE EMPLOYEES SET phone_number=:Phone  where EMPLOYEE_ID=:Id";
$res = $db->execute($sql, "Query Example", array(array(":Id", $Id, -1),
												array(":Phone", $Phone, -1)	));


 
 
?>