<?php

require('ac_db_inc.php');
$db = new DbOracle("test_db", "ArchiSoft");



	$GestorArchivo = fopen("estructura.txt", "r");
 	if (!$GestorArchivo) 
	{
		echo "Error al abrir archivo Error >>estructura.txt" ."<<";
	}
	else{
			$Contador=0;
		    while (($Registro = fgets($GestorArchivo, 4096)) !== false) 
		    {
		    	
		        //echo "Resgistro >>" . $Registro ."<< <br>";
		        $ArrRegistro = explode("|",$Registro);
		        $UR=$ArrRegistro[0];
		        //echo "UR >".$UR ."<br>";
		        $Cod= $ArrRegistro[1];
		        //echo "PUESTO >".$Cod."<br>";
		        $Desc = $ArrRegistro[2];
		        //echo "Descripcion >".$ArrRegistro[2]."<br>";
		        
		        $sql = "SELECT unidades_id FROM CtUnidades where nombre_unidad=:UR";
		        $res = $db->execFetchAll($sql, "Query Example", array(array(":UR", $UR, -1)));
		        foreach ($res as $row) {
		        //	echo "id uNIDAD >". $row['UNIDADES_ID'] ."<< <BR>";
		        	$Unidad=$row['UNIDADES_ID'];
		        }	

		        $sql = "SELECT puestos_id FROM CtPuestos where codigo=:cod";
		        $res = $db->execFetchAll($sql, "Query Example", array(array(":cod", $Cod, -1)));
		        foreach ($res as $row) {
		        //	echo "id Puestos >". $row['PUESTOS_ID'] ."<< <BR>";
		        	$Puesto =$row['PUESTOS_ID'] ;
		        }	
		        $Contador++;
		        $SQLInsr="INSERT INTO CtCargoPuesto(CARGOPUESTO_ID,DESCRIPCION,PUESTOS_ID,UNIDADES_ID)
		        VALUES(" . $Contador. ",'" .$Desc. "',". $Puesto .",". $Unidad .  ");";
		        //echo "SQL >>".$SQLInsr ."<< <br>";
		        echo $SQLInsr ."<br>";


		     }
	}	        

?>		        
