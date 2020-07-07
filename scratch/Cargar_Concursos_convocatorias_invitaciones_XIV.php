<?php
require('ac_db_inc.php');

$db = new DbOracle("test_db", "ArchiSoft");
require('ac_db_pnom.php');
$dbPN = new DbOraclePN("test_db", "ArchiSoft");

$Areas="";
$Unidad="";
$Puesto="";
$EdoTrabajador=0;
$CargoPuesto="";
$CargoPuestoId=-1;

$GestorArchivo = fopen("rusp1116.txt", "r");
if (!$GestorArchivo) {
	echo "Error al abrir archivo Error |estructura.txt" ."|";
}
else{
	echo "Antes del while <br>";
	$Contador=0;
    while (($Registro = fgets($GestorArchivo, 4096)) !== false) {
    	
    	 $CargoPuestoId=0;
    	 $Unidad=0;
    	 $Puesto=0;
    	 $Areas=0;
    	 $Total=0;



    	 $ArrRegistro = explode("|",$Registro);

    	 $UR = $ArrRegistro[1];
    	 $CR = $ArrRegistro[53];
    	 $STS_PZA = $ArrRegistro[19];
    	 $COD_RHNET = $ArrRegistro[18];
    	 $CODIGO = $ArrRegistro[5];
    	 $RFC= $ArrRegistro[20];
    	 $CLVE_PRES = $ArrRegistro[55];
    	 $PTDA =$ArrRegistro[47];
    	 $CargoPuesto=$ArrRegistro[4];
    	 $NivelPuesto=$ArrRegistro[6];
    	 //echo "RFC >>$RFC<< CR >>$CR<< PTDA >>$PTDA<< <br>";
    	 if (TRIM($RFC)=="NULL" and trim($CR)!="NULL" and trim($PTDA)=="11301"){
    	 //if (true){	
    	 	$Contador++;
    	 	 $Sueldo=0;
    	 	 $Deducciones=0;
    	 	 $Neto=0;
    	 	 echo "$Contador|PTDA|$PTDA|";
	    	 echo "RFC |" .$RFC. "| ";
	    	 echo "CODIGO |".$CODIGO. "| ";
	    	 echo "Ur |" . $UR . "| ";
	    	 echo "CR |".$CR. "| ";	    	 

	    	 echo "STS_PZA |".$STS_PZA. "| ";
	    	 echo "COD_RHNET |".$COD_RHNET. "| ";
	    	 echo "CLVE_PRES |".$CLVE_PRES. "| ";
    	

		 	$sql = "SELECT unidades_id FROM CtUnidades where nombre_unidad=:UR";
	        $res = $db->execFetchAll($sql, "Query Example", array(array(":UR", $UR, -1)));
	        foreach ($res as $row) {
	        //	echo "id uNIDAD >". $row['UNIDADES_ID'] ."| <BR>";
	        	$Unidad=$row['UNIDADES_ID'];
	        }	

	        $sql = "SELECT puestos_id FROM CtPuestos where codigo=:cod";
	        $res = $db->execFetchAll($sql, "Query Example", array(array(":cod", $CODIGO, -1)));
	        foreach ($res as $row) {
	        //	echo "id Puestos >". $row['PUESTOS_ID'] ."| <BR>";
	        	$Puesto =$row['PUESTOS_ID'] ;
	        }	

		 	$sql = "SELECT areas_id FROM CtAreas where nombre=:CR";
	        $res = $db->execFetchAll($sql, "Query Example", array(array(":CR", $CR, -1)));
	        foreach ($res as $row) {
	        //	echo "id uNIDAD >". $row['UNIDADES_ID'] ."| <BR>";
	        	$Areas=$row['AREAS_ID'];
	        }	


	        if(strlen (trim($CargoPuesto)) >0){
	        	//$CargoPuesto = "%". $CargoPuesto ."%";
	    		$sql = "SELECT CARGOPUESTO_ID FROM CtCargoPuesto where trim(DESCRIPCION)=:CarPto";
		        $res = $db->execFetchAll($sql, "Query", array(array(":CarPto", $CargoPuesto, -1)));
		        foreach ($res as $row) {
		        //	echo "id uNIDAD >". $row['UNIDADES_ID'] ."| <BR>";
		        	$CargoPuestoId=$row['CARGOPUESTO_ID'];
		        }	
	        }

	    	 echo "Unidad |".$Unidad. "| ";
	    	 echo "Puesto |" . $Puesto . "| ";
	    	 echo "Areas |".$Areas. "| ";	    
	
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

			 echo " Edo |".$EdoTrabajador ."| ";
			 echo " CargoPuesto |".$CargoPuesto ."| ";
			 echo " CargoPuestoId |".$CargoPuestoId ."| ";

	    	 echo "<br>";

	    	 if($CargoPuestoId <= 0){
	    	 	echo "Vamos a insertar en CtCargoPuesto <br>";
	    	 	$SqlCargoPuesto ="Select count(*) as TOTAL from CtCargoPuesto";
	    	 	$res = $db->execFetchAll($SqlCargoPuesto, "Query");
		        foreach ($res as $row) {
		        //	echo "id uNIDAD >". $row['UNIDADES_ID'] ."| <BR>";
		        	$Total=$row['TOTAL'];
		        }

		        echo "Contamos la tabla CtCargoPuesto y da  $Total <br>";
		        echo "CtCargoPuesto >>$Total<< >>$CargoPuesto<< >>$Puesto<< >>$Unidad<< <br>";
		        $Total= $Total +1;
		        $CargoPuestoId=$Total;
	   	    	$SqlInsert="insert into CtCargoPuesto(CARGOPUESTO_ID,DESCRIPCION,
										PUESTOS_ID, UNIDADES_ID) 
						VALUES(:Total, :descrip,:puesto,:unidad)";
				$res = $db->execute($SqlInsert, "Query", array(array(":Total", $Total, -1),
												array(":descrip", $CargoPuesto, -1),
												array(":puesto", $Puesto, -1),
												array(":unidad", $Unidad, -1)));

		     } // fin del if


		     // Seccion que se conecta a PRO_NOMINA

		      $sqlIN = "select sum(bt.importe) as sueldo
						from bdac2016 bd, btac2016 bt, partida_remu pr
						where bd.rfc=:rfcv and BD.partida ='11301' AND
			            bD.INDMANDO not in ('90','80') and bD.tipnom IN ('11','6L')  
			            and bD.QNAPROC='12' and bD.tipotrab!='20' AND 
			            bd.llave=bt.llave and          
			            bt.tconcep=1 and  
						bt.CONCEP=pr.CONCEPTO and bt.ptaant = pr.PARTIDA_ANTECEDENTE and 
						bt.CONCEP in('06', '07','42','55') and 
		      			bt.PTAANT in ('00','CG','AG')";
	        	$res = $dbPN->execFetchAll($sqlIN, "Query Example",array(array(":rfcv",$RFC,-1)));
	       
		        foreach ($res as $rowIN) {
		        //	echo "id Puestos >". $row['PUESTOS_ID'] ."| <BR>";
		        	$Sueldo =$rowIN['SUELDO'] * 2;
		        }	

		      $sqlIN = "select sum(bt.importe) as deducciones
						from bdac2016 bd, btac2016 bt, partida_remu pr
						where bd.rfc=:rfcv and BD.partida ='11301' AND
			            bD.INDMANDO not in ('90','80') and bD.tipnom IN ('11','6L')  
			            and bD.QNAPROC='12' and bD.tipotrab!='20' AND 
			            bd.llave=bt.llave and          
			            bt.tconcep=1 and  
						bt.CONCEP=pr.CONCEPTO and bt.ptaant = pr.PARTIDA_ANTECEDENTE and 
						bt.CONCEP in('01','02','04') and 
		      			bt.PTAANT in ('52','SI','SR','SP','SS')";
	        	$res = $dbPN->execFetchAll($sqlIN, "Query Example",array(array(":rfcv",$RFC,-1)));
	       
		        foreach ($res as $rowIN) {
		        //	echo "id Puestos >". $row['PUESTOS_ID'] ."| <BR>";
		        	$Deducciones =$rowIN['DEDUCCIONES'] * 2;
		        }	



		     $Neto =   $Sueldo - $Deducciones;
		     echo "Antes de ejecutar el insert a PlazasVacantes_Xa<br>";

	    	 $SqlInsert="insert into Convocatoria_XIV(
									CONVOCATORIA_ID,
									AREAS_ID,
									CARGOPUESTO_ID,
									PUESTOS_ID,
									SALARIOBRUTOMENSUAL,
									SALARIONETOMENSUAL)
						VALUES(:ContId, :area, :cargo,:pto,:bruto,:neto)";
			$res = $db->execute($SqlInsert, "Query", array(array(":ContId", $Contador, -1),
												array(":area", $Areas, -1),
												array(":cargo", $CargoPuestoId, -1),
												array(":pto", $Puesto, -1),
												array(":bruto", $Sueldo, -1),
												array(":neto", $Neto, -1),

													));
		    }// fin del If RFC
	} // fin del while
}	    	 
echo "<br> Contador |$Contador| <br>";

?>		        