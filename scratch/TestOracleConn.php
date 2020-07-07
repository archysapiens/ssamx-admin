<?php

//
// proceso de carga de l tabla Remuneraciones_VIII
// FASE I Descarga de Informacion.
//
error_reporting(E_ALL);
ini_set('display_errors', 1);
require('../general/generales.inc');
require('ac_db_pn.php');
$db = new DbOracle("pro_nomina", "ArchiSoft");
$sqlUR = "select ur	from cat_ur";

$resUR = $db->execFetchAll($sqlUR, "Query Example");

foreach ($resUR as $rowUR) {
	$CatUR=$rowUR['UR'];
	echo "CatUR >$CatUR<  <br>";

}// fin foreach



?>		        
