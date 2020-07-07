<?php
include "../general/DBC.php";
include "../general/generales.inc";

$db = new DbCnnx();    

$SQLRemesas =" SELECT org.id AS id_organismos, arc.id AS id_archivos,
					per.anio AS anio_periodos, per.numero AS numero_periodos
				FROM organismos org, periodos per, archivos arc 
				ORDER BY org.id,arc.id, per.numero	";
$rows = $db->select($SQLRemesas);				
$Contador=CERO;
 while(isset($rows[$Contador]['id_organismos']))
        {
        	echo "id_organismos >". $rows[$Contador]['id_organismos'] . "< ";
        	echo "id_archivos >". $rows[$Contador]['id_archivos'] . "< ";
        	echo "anio_periodos >". $rows[$Contador]['anio_periodos'] . "< ";
        	echo "numero_periodos >". $rows[$Contador]['numero_periodos'] . "< <br>";
        	$Contador++;

        	$INS ="insert into remesas( id,  fecha_asignacion,  fecha_actualizacion,  id_organismos,
  				estatus,  id_archivos,  anio_periodos,  numero_periodos)
				values($Contador, curdate(),curdate(),'" .$rows[$Contador]['id_organismos'] . "','A'," .
				$rows[$Contador]['id_archivos'] .	" ," . $rows[$Contador]['anio_periodos'] . ", ".
				 $rows[$Contador]['numero_periodos'] .") ON DUPLICATE KEY UPDATE ".
                "fecha_asignacion =curdate(), fecha_actualizacion=curdate(),".
                "id_organismos=".$rows[$Contador]['id_organismos'] .
                ", id_archivos=".$rows[$Contador]['id_archivos'].
                ", anio_periodos=". $rows[$Contador]['anio_periodos'] .
                ",numero_periodos=".$rows[$Contador]['numero_periodos'];
			//echo " INS >$INS< <br>";
			$ins = $db->select($INS);	
        }
  echo "Numero Registrs >"      . $Contador ."< <br>";

?>