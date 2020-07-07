<?php
session_start();
include "../general/DBC.php";
include "../general/generales.inc";
//include "ptfma_existe_archivo.inc";

$TagEnvio ="";
if(isset($_POST['TagEnvio']))
    $TagEnvio = $_POST['TagEnvio'];
$ArchivoExiste ="";
if(isset($_POST['archivo_existe']))
    $ArchivoExiste = $_POST['archivo_existe'];

$storeFolder  = '../staging/' ;  
$ArchivoExiste='../staging/'.$ArchivoExiste;

$db = new DbCnnx();    
$SQLRegistro="SELECT  id_remesas
				FROM logger
				WHERE etiqueta_envio = '$TagEnvio' AND 
				archivo = '$ArchivoExiste'";
//echo "SQLRegistro >>$SQLRegistro<<";
$Rows = $db->select($SQLRegistro);

if(is_array($Rows)){
  $Contador = CERO;
  if(isset($Rows[$Contador]['id_remesas'])) {				
  	echo -UNO;
  }	
  else
  	echo CERO;
 }
 else 
 	echo CERO;
?>