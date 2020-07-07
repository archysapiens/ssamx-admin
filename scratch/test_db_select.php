<?php
 
// test_db.php
// EN este ejemplo se muestra como se construyen consultas 
// usando parametros
 
require('ac_db_inc.php');

$Id=100; 

$db = new DbOracle("test_db", "ArchiSoft");
$sql = "SELECT first_name, phone_number FROM employees where EMPLOYEE_ID=:Id ORDER BY employee_id";
$res = $db->execFetchAll($sql, "Query Example", array(array(":Id", $Id, -1)));

 
echo "<table border='1'>\n";
echo "<tr><th>Name</th><th>Phone Number</th></tr>\n";
foreach ($res as $row) {
    $name = htmlspecialchars($row['FIRST_NAME'], ENT_NOQUOTES, 'UTF-8');
    $pn   = htmlspecialchars($row['PHONE_NUMBER'], ENT_NOQUOTES, 'UTF-8');
    echo "<tr><td>$name</td><td>$pn</td></tr>\n";
}
echo "</table>";
 
?>