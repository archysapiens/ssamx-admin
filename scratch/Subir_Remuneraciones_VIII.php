<?php
set_time_limit(0);
/*
Carga informacion en la tabla remuneraciones_viii

"UR"|"PUESTO"|"NOMBRE"|"PER"|"NETO"|"TIPOTRAB"|
"GRATIFICACIONES"|"ESTIMULOS"|"PERIODICIDADESTIMULO"|"APOYOECONOMICO"|"QNAPROC"|"PRESTACIONESECONOMICAS"

*/

require('ac_db_inc.php');
$db = new DbOracle("test_db", "ArchiSoft");

$Areas="";
$Unidad="";
$Puesto="";
$EdoTrabajador=0;
$CargoPuesto="";
$CargoPuestoId=-1;

$Contador=0;
$ContadorOK=0;

$GestorArchivo = fopen("remuneaciones.txt", "r");
if (!$GestorArchivo) 
{
	echo "Error al abrir archivo Error |estructura.txt" ."|";
}
else{

    while (($Registro = fgets($GestorArchivo, 4096)) !== false) {
    	 $ArrRegistro = explode("|",$Registro);

    	 $UR = $ArrRegistro[0];
    	 $UR = preg_replace('/"/', '', $UR);

    	 $PUESTO = $ArrRegistro[1];
		 $PUESTO = preg_replace('/"/', '', $PUESTO);    	 

    	 $NOMBRE = $ArrRegistro[2];
    	 $NOMBRE = preg_replace('/"/', '', $NOMBRE);    	 

    	 $PER = $ArrRegistro[3];
    	 $NETO = $ArrRegistro[4];
    	 $TIPOTRAB = $ArrRegistro[5];
    	 $TIPOTRAB = preg_replace('/"/', '',$TIPOTRAB);    	 

    	 $GRATIFICACIONES= $ArrRegistro[6];
    	 $ESTIMULOS = $ArrRegistro[7];
    	 $PERIODICIDADESTIMULO= $ArrRegistro[8];    	 
    	 $APOYOECONOMICO= $ArrRegistro[9];    	 
    	 $QNAPROC= $ArrRegistro[10];    	 
    	 $PRESTACIONESECONOMICAS= $ArrRegistro[11];    	 

		 $Contador++;

		$sql = "SELECT unidades_id FROM CtUnidades where nombre_unidad=:UR";
		$res = $db->execFetchAll($sql, "Query Example", array(array(":UR", $UR, -1)));
		foreach ($res as $row) {
		    	$Unidad=$row['UNIDADES_ID'];
		}	

		$sql = "SELECT puestos_id FROM CtPuestos where codigo=:cod";
		$res = $db->execFetchAll($sql, "Query Example", array(array(":cod", $PUESTO, -1)));
		foreach ($res as $row) {
		    	$Puesto =$row['PUESTOS_ID'] ;
		}	

		if(strlen (trim($Puesto)) >0 and strlen (trim($Unidad)) >0){
			$sql = "SELECT CARGOPUESTO_ID FROM CtCargoPuesto where PUESTOS_ID=:Pto AND UNIDADES_ID=:Uni";
		    $res = $db->execFetchAll($sql, "Query", array(array(":Pto", $Puesto, -1), array(":Uni", $Unidad, -1)));
		    foreach ($res as $row) {
		        	$CargoPuestoId=$row['CARGOPUESTO_ID'];
		    }	
		}

		if ($CargoPuestoId > 0 ){
		/**	
		    	 echo "Ur |" . $UR . "|";
				 echo "PUESTO |" .$PUESTO. "|";
				 echo "NOMBRE |".$NOMBRE. "|";
		 		 echo "PER |".$PER. "|";	    	 
				 echo "NETO |".$NETO. "|";
				 echo "TIPOTRAB |".$TIPOTRAB. "|";
				 echo "GRATIFICACIONES |".$GRATIFICACIONES. "|";
				 echo "ESTIMULOS |".$ESTIMULOS. "|";
				 echo "PERIODICIDADESTIMULO |".$PERIODICIDADESTIMULO. "|";
				 echo "APOYOECONOMICO |".$APOYOECONOMICO. "|";	    	 
				 echo "QNAPROC |".$QNAPROC. "|";
				 echo "PRESTACIONESECONOMICAS |".$PRESTACIONESECONOMICAS. "|";	    	 

				 echo "Unidad |".$Unidad. "|";
				 echo "Puesto |" . $Puesto . "|";
				 echo "CargoPuestoId |".$CargoPuestoId. "|";	    
				 echo "<br>";
		**/		 

	    	 $SqlInsert="insert into REMUNERACIONES_VIII(REMUNERACIONES_ID,AREAS_ID , CARGOPUESTO_ID , PUESTOS_ID ) 
						VALUES(:ContId, :area,  :cargo,:pto)";
			$res = $db->execute($SqlInsert, "Query", array(array(":ContId", $Contador, -1),
												array(":area", $Unidad, -1),
												array(":cargo", $CargoPuestoId, -1),
												array(":pto", $Puesto, -1)	));
/**

			$res = $db->execute($SqlInsert, "Query", array(array(":ContId", $ContadorOk, -1),
												array(":area", $Areas, -1),
												array(":unidad", $Unidad, -1),
												array(":edo", $EdoTrabajador, -1),
												array(":cargo", $CargoPuestoId, -1),
												array(":pto", $Puesto, -1)	));

**/
				 $ContadorOK++;
		}		 
		$Contador++;
	}// fin del while
}	    	 
echo "<br> Contador >>$Contador<< <br>";
echo "<br> ContadorOk >>$ContadorOk << <br>";

?>		        