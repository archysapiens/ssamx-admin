<?php

include "../general/DBC.php";
include "../general/generales.inc";

$db = new DbCnnx(); 
	
 if (isset($_REQUEST['var'])) { 

 $var_decode=base64_decode($_REQUEST['var']);
 
 $SQL ="Update privilegios set estatus='A' where id_usuarios='$var_decode'";
	$row = $db->query($SQL);
	
header('location: /ssa/index.php');

}  


?>