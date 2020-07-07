<?php
include "../general/DBCBATCH.php";
include "../general/generales.inc";
include "pfma_validacion_archivos.inc";
include "pfma_validacion_archivos_trailer.inc";
include "ptma_opcd.inc";
include "ptfma_demon.inc";

echo "Inicia proceso\n";
$ResultadoValidacion =CERO;
while(UNO){
	echo "En el while\n";
	sleep(10);
	echo "Despues sleep\n";
	date_default_timezone_set('America/Mexico_City');
	$FechaProceso = date("d-m-Y");
	$HoraProceso = date("H:i:s");
	$FechaHoraProceso = $FechaProceso." ".$HoraProceso;

	$QueryDemon = "SELECT bita.id_remesas as id, DATE_FORMAT(bita.fecha_evento,'%d-%m-%Y %H:%i:%s') as fecha_evento, 
					bita.archivo_procesado as archivo_procesado,bita.error as error, 
					bita.estatus as estatus, rem.id_organismos as organismo,  
					rem.anio_periodos as anio,rem.numero_periodos as periodo,
					rem.id_archivos as id_archivo, rem.id_usuarios as id_usuario,
					DATE_FORMAT(bita.fecha_evento,'%Y%m%d%H%i%s') as fecha_log
					FROM bitacora bita, remesas rem
					WHERE bita.id_remesas = rem.id AND bita.estatus ='P'";
	//echo "QRY >>$QueryDemon << \n ";				

	$db = new DbCnnx();  
	$Rows = $db->select($QueryDemon);
	echo "erro >> ". $db->error()."<< \n";
	$Contador=CERO;
	if(is_array($Rows)){
		echo "SI fue array \n";
	 	while(isset($Rows[$Contador]['id'])){
	        $IdRemesa = $Rows[$Contador]['id'];
	        $FechaPlanificacion = $Rows[$Contador]['fecha_evento'];
	        $ArchProcesar = $Rows[$Contador]['archivo_procesado'];
	        $IdEdo = $Rows[$Contador]['organismo'];
	        $AnioQna = $Rows[$Contador]['anio'];
	        $Qna = $Rows[$Contador]['periodo'];
	        $IdArchivo = $Rows[$Contador]['id_archivo'];
	        $IdUsuario = $Rows[$Contador]['id_usuario'];
	        $FechaLog=$Rows[$Contador]['fecha_log'];
	        echo "IdRemesa >>$IdRemesa<< \n";
	        echo "FechaPlanificacion >>$FechaPlanificacion<< \n";
	        echo "ArchProcesar >>$ArchProcesar<< \n";
	        echo "IdEdo >>$IdEdo<< \n";
	        echo "AnioQna >>$AnioQna<< \n";
	        echo "Qna >>$Qna<< \n";
	        echo "IdArchivo >>$IdArchivo<< \n";
	        echo "FechaHoraProceso >>$FechaHoraProceso<< \n";
	        echo "Usuario >>$IdUsuario<< \n";

            $ResValidacionTipoArch = validaCamposArchivo($ArchProcesar);
            echo "ResValidacionTipoArch >>$ResValidacionTipoArch<< <br>";

            if($ResValidacionTipoArch == DATA_NOMINA){   
                echo  "Seccion para validar archivo DATA_NOMINA <br>";
                $ResultadoValidacion =fncValidaArchivo($IdEdo, "",$ArchProcesar);
                if ($ResultadoValidacion==EXITO){ 
                	$LOG="../staging/".$IdEdo."-"."bd-".$IdRemesa."-".$Qna."$FechaLog.log";
  					$CTL="../staging/load.ctl";
					$Comando = "sqlldr userid=system/oracle@xe data='$ArchProcesar' control=$CTL log=$LOG";
					echo "\n Antes de ejecutar el comando sqlldr>>$Comando<< \n\n";
					system($Comando, $retval);
					$Estatus ="'K'";
                	echo EXITO."|Validacion Exitosa";
                    //echo obtenResultadosValidacion($IdArchivo, $ResultadoValidacion,$ArchProcesar, "Cadana de Validacion",$ArchProcesar.".err", $ResultadoValidacion);
                }   
                else{ 
                	echo FALLA."|Errores en Archivo";
                	$Estatus ="'E'";
                    //echo obtenResultadosValidacion($IdArchivo, FALLA,$ArchProcesar, "Cadana de Validacion",$ArchProcesar.".err", $ResultadoValidacion);
                }// fin del if de fncValidaArchivo    

            } // if(validaCamposArchivo($ArchivoValidar) == DATA)
            elseif($ResValidacionTipoArch == DATA_NOMINA_TRAILER){// echo "Error por definir";
                echo  "Seccion para validar archivo DATA_NOMINA_TRAILER <br>";
                if(($ResultadoValidacion =fncValidaArchivoTrailer($IdEdo, $ArchProcesar))==EXITO){ 
                	echo EXITO."|Validacion Exitosa";
                	$Estatus ="'K'";

                	$LOG="../staging/".$IdEdo."-"."bt-".$IdRemesa."-".$Qna."$FechaLog.log";
  					$CTL="../staging/loadbt.ctl";
					$Comando = "sqlldr userid=system/oracle@xe data='$ArchProcesar' control=$CTL log=$LOG";
					echo "\n Antes de ejecutar el comando sqlldr>>$Comando<< \n\n";

					system($Comando, $retval);

                	//echo obtenResultadosValidacion($IdArchivo, $ResultadoValidacion,$_FILES['file']['name'], "Cadana de Validacion",$ArchProcesar.".err", $ResultadoValidacion);
                }   
                else{ echo FALLA."|Errores en Archivo";
                		$Estatus ="'E'";
                    //echo obtenResultadosValidacion($IdArchivo, FALLA,$_FILES['file']['name'], "Cadana de Validacion",$ArchProcesar.".err", $ResultadoValidacion);
                }// fin del if de fncValidaArchivo    
           }else{ 
                $ResultadoRegistro = registraValidacion($IdEdo,$AnioQna,$Qna,$IdArchivo,$ArchProcesar.".err",-UNO);
           }// fin de validaCamposArchivo    

           $ResultadoRegistro = registraResultadosValidacion($IdEdo,$AnioQna,$Qna,$IdRemesa,$IdArchivo,$ArchProcesar.".err",$ResultadoValidacion, $ResValidacionTipoArch, $IdUsuario);
           $QueryDemon = "update bitacora set estatus =".$Estatus.
           				", evidencia='$FechaPlanificacion', total= " .$ResultadoValidacion.
					" WHERE id_remesas =". $IdRemesa .
					" and fecha_evento =STR_TO_DATE('".$FechaPlanificacion."','%d-%m-%Y %H:%i:%s')".
					" and evidencia='Planificacion'and estatus ='P' and ".
					" archivo_procesado='$ArchProcesar'";
			echo "UPDATE QRY >>$QueryDemon << \n ";				
			$Rows = $db->select($QueryDemon);
			echo "erro >> ". $db->error()."<< \n";		
	        $Contador++;
	    }// fin de while
	}
	else{
		echo "sin proceso a validar \n";
	} // fin de if(!is_array($Rows))
}// fin del while
?>