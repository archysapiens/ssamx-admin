<?php

require('ac_db_inc.php');
$db = new DbOracle("test_db", "ArchiSoft");

$Areas="";
$Unidad="";
$Puesto="";
$EdoTrabajador=0;
$CargoPuesto="";
$CargoPuestoId=-1;

$GestorArchivo = fopen("rusp2315.txt", "r");
if (!$GestorArchivo) 
{
	echo "Error al abrir archivo Error >>estructura.txt" ."<<";
}
else{
	$Contador=0;
    while (($Registro = fgets($GestorArchivo, 4096)) !== false) 
    {
    	 $ArrRegistro = explode("|",$Registro);

    	 $UR = $ArrRegistro[1];
    	 $CR = $ArrRegistro[53];
    	 $STS_PZA = $ArrRegistro[19];
    	 $COD_RHNET = $ArrRegistro[18];
    	 $CODIGO = $ArrRegistro[5];
    	 $RFC= $ArrRegistro[20];
    	 $CLVE_PRES = $ArrRegistro[55];
    	 if (TRIM($RFC)=="NULL"){
    	 //if (true){	

	    	 echo "RFC >>" .$RFC. "<< ";
	    	 echo "CODIGO >>".$CODIGO. "<< ";
	    	 echo "Ur >>" . $UR . "<< ";
	    	 echo "CR >>".$CR. "<< ";	    	 

	    	 echo "STS_PZA >>".$STS_PZA. "<< ";
	    	 echo "COD_RHNET >>".$COD_RHNET. "<< ";
	    	 echo "CLVE_PRES >>".$CLVE_PRES. "<< ";

	    	 $Contador++;

		 	$sql = "SELECT unidades_id FROM CtUnidades where nombre_unidad=:UR";
	        $res = $db->execFetchAll($sql, "Query Example", array(array(":UR", $UR, -1)));
	        foreach ($res as $row) {
	        //	echo "id uNIDAD >". $row['UNIDADES_ID'] ."<< <BR>";
	        	$Unidad=$row['UNIDADES_ID'];
	        }	

	        $sql = "SELECT puestos_id FROM CtPuestos where codigo=:cod";
	        $res = $db->execFetchAll($sql, "Query Example", array(array(":cod", $CODIGO, -1)));
	        foreach ($res as $row) {
	        //	echo "id Puestos >". $row['PUESTOS_ID'] ."<< <BR>";
	        	$Puesto =$row['PUESTOS_ID'] ;
	        }	

		 	$sql = "SELECT areas_id FROM CtAreas where nombre=:CR";
	        $res = $db->execFetchAll($sql, "Query Example", array(array(":CR", $CR, -1)));
	        foreach ($res as $row) {
	        //	echo "id uNIDAD >". $row['UNIDADES_ID'] ."<< <BR>";
	        	$Areas=$row['AREAS_ID'];
	        }	

    		$sql = "SELECT DEN_PTO FROM convertidorcp where clvepres15=:CVEPRES";
	        $res = $db->execFetchAll($sql, "Query", array(array(":CVEPRES", $CLVE_PRES, -1)));
	        foreach ($res as $row) {
	        //	echo "id uNIDAD >". $row['UNIDADES_ID'] ."<< <BR>";
	        	$CargoPuesto=$row['DEN_PTO'];
	        }	
	        if(strlen (trim($CargoPuesto)) <=0 ){
	    		$sql = "SELECT DEN_PTO FROM convertidorcp where CLVE_PRES=:CVEPRES";
		        $res = $db->execFetchAll($sql, "Query", array(array(":CVEPRES", $CLVE_PRES, -1)));
		        foreach ($res as $row) {
		        //	echo "id uNIDAD >". $row['UNIDADES_ID'] ."<< <BR>";
		        	$CargoPuesto=$row['DEN_PTO'];
		        }	
	        }
	        if(strlen (trim($CargoPuesto)) >0){
	        	//$CargoPuesto = "%". $CargoPuesto ."%";
	    		$sql = "SELECT CARGOPUESTO_ID FROM CtCargoPuesto where trim(DESCRIPCION)=:CarPto";
		        $res = $db->execFetchAll($sql, "Query", array(array(":CarPto", $CargoPuesto, -1)));
		        foreach ($res as $row) {
		        //	echo "id uNIDAD >". $row['UNIDADES_ID'] ."<< <BR>";
		        	$CargoPuestoId=$row['CARGOPUESTO_ID'];
		        }	

	        }


	    	 echo "Unidad >>".$Unidad. "<< ";
	    	 echo "Puesto >>" . $Puesto . "<< ";
	    	 echo "Areas >>".$Areas. "<< ";	    
	
	    	 if ($STS_PZA ==1){
	    	 		if(trim($COD_RHNET)=="NULL")
	    	 			//Ocupado Administrativo
	    	 			$EdoTrabajador=1;
	    	 		else //Ocupado servicio profesional
	    	 			$EdoTrabajador=2;
	    	 }
	    	 elseif($STS_PZA ==2){ 
	    	 		if(trim($COD_RHNET) !="NULL")
	    	 			//Vacante Administrativo
	    	 			$EdoTrabajador=3;
	    	 		else //Vacante servicio profesional
	    	 			$EdoTrabajador=4;
	    	 }//fin if 

			 echo " Edo >>".$EdoTrabajador ."<< ";
			 echo " CargoPuesto >>".$CargoPuesto ."<< ";
			 echo " CargoPuestoId >>".$CargoPuestoId ."<< ";

	    	 echo "<br>";

	    	 $SqlInsert="insert into PlazasVacantes_Xa(PLAZAVACANTE_ID, AREAS_ID ,
						UNIDADES_ID ,ESTADOTRABAJDOR_ID  ,CARGOPUESTO_ID  ,PUESTOS_ID ) 
						VALUES(:ContId, :area,:unidad, :edo, :cargo,:pto)";
			$res = $db->execute($SqlInsert, "Query", array(array(":ContId", $Contador, -1),
												array(":area", $Areas, -1),
												array(":unidad", $Unidad, -1),
												array(":edo", $EdoTrabajador, -1),
												array(":cargo", $CargoPuestoId, -1),
												array(":pto", $Puesto, -1)	));





		    }// fin del If RFC

	}// fin del while
}	    	 
echo "<br> Contador >>$Contador<< <br>";

?>		        