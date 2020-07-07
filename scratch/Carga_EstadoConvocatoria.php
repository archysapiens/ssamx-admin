<?php

require('ac_db_inc.php');
$db = new DbOracle("test_db", "ArchiSoft");
header('content-type: text/html; charset=utf-8');
$ArrayEdoConv = array("En Proceso","En Evaluación", "Finalizado");

$Total = count($ArrayEdoConv);

for ($Ind=0; $Ind < $Total; $Ind++){
	$Item =$ArrayEdoConv[$Ind];
	echo "ArrayEdoConv >>".$Item ."<< <br>";
	$SqlInsert="insert into PlazasVacantes_Xa(PLAZAVACANTE_ID, AREAS_ID ,
						UNIDADES_ID ,ESTADOTRABAJDOR_ID  ,CARGOPUESTO_ID  ,PUESTOS_ID,NIV_TAB ) 
						VALUES(:ContId, :area,:unidad, :edo, :cargo,:pto,:niv)";
			$res = $db->execute($SqlInsert, "Query", array(array(":ContId", $Contador, -1),
												array(":area", $Areas, -1),
												array(":unidad", $Unidad, -1),
												array(":edo", $EdoTrabajador, -1),
												array(":cargo", $CargoPuestoId, -1),
												array(":pto", $Puesto, -1),
												array(":niv", $NivelPuesto, -1)	));


}





?>