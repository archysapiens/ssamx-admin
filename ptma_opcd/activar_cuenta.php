<?php

include "../general/CnxGral.inc";
$Conn = fncConxBaseDatos(HOST, USU, PWD, BD );
	
 if (isset($_REQUEST['var'])) { 

 $var_decode=base64_decode($_REQUEST['var']);
 $query_update_user=mysqli_query($Conn, "Update privilegios set estatus='A' where id_usuarios='$var_decode'");
	
header('location: /ssa/index.php');

}  


?>