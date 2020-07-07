<?php
 
// en este ejemplo se muestra como se construyen consulktas 
// para obtener varios registros como resultado
 
require('ac_db_inc.php');
 


$db = new DbOracle("test_db", "ArchySoft");
$sql = "SELECT first_name, phone_number FROM employees ORDER BY employee_id";
$res = $db->execFetchAll($sql, "Query Example");


 
echo "<table border='1'>\n";
echo "<tr><th>Name</th><th>Phone Number</th></tr>\n";
foreach ($res as $row) {
    $name = htmlspecialchars($row['FIRST_NAME'], ENT_NOQUOTES, 'UTF-8');
    $pn   = htmlspecialchars($row['PHONE_NUMBER'], ENT_NOQUOTES, 'UTF-8');
    echo "<tr><td>$name</td><td>$pn</td></tr>\n";
}
echo "</table>";
 
?>