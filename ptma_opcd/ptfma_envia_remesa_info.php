<?php

/*********************************************************************
 * 
 * Programa : ptfma_envia_remesa_info.php
 * Objetivo : Envia informacion de la remesa a enviar
 
 **********************************************************************/

session_start();
include "../general/DBC.php";
include "../general/generales.inc";
include "ptfma_envia_remesa_info.inc";
$TagEnvio="";
if(isset($_POST['TagEnvio']))
	$TagEnvio=$_POST['TagEnvio'];

$AnioEnvio="";
if(isset($_POST['anio_envio']))
	$AnioEnvio=$_POST['anio_envio'];

$QnaEnvio="";
if(isset($_POST['quincena_envio']))
	$QnaEnvio=$_POST['quincena_envio'];

$FechaLimite="";
if(isset( $_SESSION['fecha_limite']))
	$FechaLimite= $_SESSION['fecha_limite'];

$IdRemesa="";
if(isset( $_SESSION['id_remesas']))
	$IdRemesa= $_SESSION['id_remesas'];

// $FechaLimite= formateaFechas($FechaLimite);

if(cierraRemesa($IdRemesa,$AnioEnvio, $QnaEnvio)!=CERO){
	echo "Error en el envio de la informacion";
}
else{
	
	echo construyeInfoEnvioRemesas($TagEnvio, $FechaLimite,$IdRemesa);
}// fin del if


?>