<?php

header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");
session_start();

include_once '../general/CnxGral.inc';
//include 'lista_tecnico.inc';

$HndConx= fncConxBaseDatos("localhost", "root", "Secnomina#2016", "ssa" );

$TagEnvio="";
if(isset($_GET['tagenvio']))
	$TagEnvio=$_GET['tagenvio'];

$IdRemesa="";
if(isset($_GET['idremesa']))
	$IdRemesa=$_GET['idremesa'];

$IdArchivoPN="";
if(isset($_GET['idarchivopn']))
	$IdArchivoPN=$_GET['idarchivopn'];

$HeadJQ= $_GET['callback'];

$sord = $_GET['sord']; 
$sidx = $_GET['sidx'];

// if we not pass at first time index use the first column for the index or what you want
if(!$sidx){
$sidx =1; 
$ordenar ="	order by numero_registro ". $sord;	
} 
else{
	$ordenar ="	order by $sidx ". $sord;		
}


$page = $_GET['page']; 
 
// get how many rows we want to have into the grid - rowNum parameter in the grid 
$limit = $_GET['rows']; 
 
// get index row - i.e. user click to sort. At first time sortname parameter -
// after that the index from colModel 
$PathExec="../staging/";
$FileLog=$TagEnvio."_".$IdArchivoPN."_"."lo4php.log";

$GestorArchivoSql = fopen($PathExec.$FileLog, "w");
if (!$GestorArchivoSql) {
	echo "Error al abrir archivo Error >>".$PathExec.$FileLog."<<";
}
else{
		$SQL=" SELECT  count(*) AS count
			FROM errores
				where id_remesas=$IdRemesa and 
				etiqueta_envio='$TagEnvio' and 
				archivo_error like '%$IdArchivoPN%'		";		

		fwrite($GestorArchivoSql, "Contar SQL >$SQL<\n" );

		$result = mysqli_query($HndConx, $SQL);
		$row=mysqli_fetch_array($result,MYSQLI_ASSOC);
		$count = $row['count'];

		// calculate the total pages for the query 
		if( $count > 0 && $limit > 0) { 
		              $total_pages = ceil($count/$limit); 
		} else { 
		              $total_pages = 0; 
		} 
		 
		// if for some reasons the requested page is greater than the total 
		// set the requested page to total page 
		if ($page > $total_pages) $page=$total_pages;
		 
		// calculate the starting position of the rows 
		$start = $limit*$page - $limit;
		 
		// if for some reasons start position is negative set it to 0 
		// typical case is that the user type 0 for the requested page 
		if($start <0) $start = 0; 

		


		$SQL=" SELECT  numero_registro,  campo,  evidencia,  descripcion
				FROM errores
				where id_remesas=$IdRemesa and 
				etiqueta_envio='$TagEnvio' and 
				archivo_error like '%$IdArchivoPN%'" .$ordenar ;
					

			$result = mysqli_query($HndConx, $SQL);

			fwrite($GestorArchivoSql, "Detalle SQL >$SQL<\n" );
			
			$BodyJS="";
			$Contador=0;
			while ($row=mysqli_fetch_array($result,MYSQLI_ASSOC))
			{

				$Id=$row['numero_registro'];
				$Rfc=str_replace('"','',$row['campo']);
				$Curp =str_replace('"','',$row['evidencia']);
				$Nombre=utf8_encode (str_replace('"','',$row['descripcion']));

				if($Contador ==0)
					$BodyJS.= "{\"numero_registro\": \"$Id\", \"campo\": \"$Rfc\", \"evidencia\": \"$Curp\", \"descripcion\": \"$Nombre\" } ";
				else
					$BodyJS.= ",{\"numero_registro\": \"$Id\", \"campo\": \"$Rfc\", \"evidencia\": \"$Curp\", \"descripcion\": \"$Nombre\" } ";
				$Contador++;
			}
		fclose($GestorArchivoSql);
			
		echo utf8_encode(" 
					$HeadJQ(
					{
					   \"page\":\"$page\",
					   \"total\":\"$total_pages\",
					   \"records\":\"$count\", 
					   \"rows\":
					[
					 $BodyJS
					]
					 })");
			
}

?>