<?php
session_start();
include "../general/DBC.php";
include "../general/generales.inc";

$IdUsuario ="";
if(isset($_SESSION['inputUsuario']))
	$IdUsuario =$_SESSION['inputUsuario'];

$IdOrganismo ="";
if(isset($_SESSION['idorg'] ))
	$IdOrganismo =$_SESSION['idorg'] ;

$db = new DbCnnx();    

$IdOrganismo  = $db->quote($IdOrganismo);
$IdUsuario    = $db->quote($IdUsuario);


$SQL = "select  count(*) as notificaciones
		from notificaciones 
		where estatus='A' and id_usuarios= ".$IdUsuario . 
		" and id_organismos =".$IdOrganismo ;
$Rows = $db->select($SQL);
$Contador= CERO;
if(isset($Rows[$Contador]['notificaciones'])){
	        $NumNotificaciones = $Rows[$Contador]['notificaciones'];
	        if ($NumNotificaciones== CERO)
				$NumNotificaciones= "";        	
}
else
		$NumNotificaciones= "";
echo $NumNotificaciones;

?>