<?php

/*************************************************************
* 
*  Funcion : validaLayOut
*  Objetivo: Validar el LayOut Del Archivo
*            
*            
*  Fecha   : 24-Jun-2016
*  Autor   : Archy Sapiens
*
*  Parametros
*   $DataSrc  : Fuente de datos
*   $SepCampo : Separador de Campo
*   $NumCampos: Numero de Campos
*
*  Regreso
*
*   $bandera  : 0 Exito
*               1|num registro|eviencia
*
***************************************************************/   

function validaLayOut($DataSrc,$SepCampo,$NumCampos){
	$Bandera = CERO;
	$ValidacionRegistro = array();
	$GestorArchivo = fopen($DataSrc, "r");
	if ($GestorArchivo){
		    $Contador = UNO;
		    $ContError= CERO;
		    while (($Registro = fgets($GestorArchivo, 4096)) !== false){
		    	 $ArrRegistro = explode($SepCampo,$Registro);
		    	 $NumCamposRegistro = count($ArrRegistro);
		    	 if ($NumCamposRegistro != $NumCampos and $ContError < 100){
		    	 	array_push($ValidacionRegistro,$Contador . "|" . $Registro);
		    	 	$ContError++;
		    	 }
		    	 $Contador++;
		    }// fin del while	
	}// fin de if
	return $ValidacionRegistro;
}// fin de validaLayOut

/*************************************************************
* 
*  Funcion : registraNotificacion
*  Objetivo: Registra en la tabla de notificacion
*            
*            
*  Fecha   : 09-May-2016
*  Autor   : Archy Sapiens
*
*  Parametros
*   $IdEstado : Identificación del Organismo
*   $Anio     : Anio del perido(2016, 2017, 2018,etc)
*   $Prdiodo  : Quincena procesada(Q1, Q2, Q3, etc.)
*   $IdRemesa : rEMESA QUE VAMOS A PROCESAR
*   $TipoArch : Tipo del Archivo a procesar(1-X00, 2-416, 3-610, etc.)   
*   $LogValidacion : Es una rchivo en donde quedaron asentadas las 
*                    validaciones realizadas. 
*
***************************************************************/   

function registraNotificacion($IdEstado,$Anio,$Periodo,$IdRemesa,$TipoArchivo,$LogValidacion, $IdUsuario){
$db = new DbCnnx();
$IdEstado = $db->quote($IdEstado);
$Estatus = $db->quote('A');
$Usuario = $db->quote($IdUsuario);
$EvtoDetalle = $db->quote($LogValidacion);

echo "Entradas de notificacion";

$SQL= "INSERT INTO notificaciones
            (fecha_evento_envio,estatus,fecha_evento_lectura,
             id_usuarios,id_organismos,tipo_evento,
             tipo_evento_detalle,anio_periodos,numero_periodos,id_remesas)
		VALUES (now(),
		        $Estatus,
		        NULL,
		        $Usuario,
		        $IdEstado,
		        'PV',
		        $EvtoDetalle,
		        $Anio,
		        $Periodo,
		        $IdRemesa)";

echo "registraNotificacion SQL >>$SQL<< <br>";
$rows = $db->select($SQL);
$Resultad= $db->error();
if ($Resultad!="")
	echo "Error al insertar en Notificaciones <br>";
else
	echo "Exito al insertar en Notificaciones <br>";

}// fin de registraNotificacion



/*************************************************************
* 
*  Funcion : registraResultadosValidacion
*  Objetivo: Registra el resultado de la validacion en
*            la bitacora de validaciones
*            
*  Fecha   : 22-Abr-2016
*  Autor   : Archy Sapiens
*
*  Parametros
*   $IdEstado : Identificación del Organismo
*   $Anio     : Anio del perido(2016, 2017, 2018,etc)
*   $Prdiodo  : Quincena procesada(Q1, Q2, Q3, etc.)
*   $IdRemesa : rEMESA QUE VAMOS A PROCESAR
*   $TipoArch : Tipo del Archivo a procesar(1-X00, 2-416, 3-610, etc.)   
*   $LogValidacion : Es una rchivo en donde quedaron asentadas las 
*                    validaciones realizadas. 
*   $TipoRegistro: Este parametro nos indica que registro en bitacora 
*                  se realizara:
*                  CERO  : Resgistro de validacion Exitosa
*                  -UNO  : Registro, formato de archivo erroneo
*                  > CERO: Errores en campos
*  Valor de regreso
*
***************************************************************/   

function registraResultadosValidacion($IdEstado,$Anio,$Periodo,$IdRemesa,$TipoArchivo,$LogValidacion,
	$ResultadoValidacion, $ResValidacionTipoArch, $IdUsuario)
{ 
/**	
echo "registraResultadosValidacion ";
echo "IdEstado >$IdEstado<   <br>"; 
echo "Anio >$Anio<   <br>"; 
echo "Periodo >$Periodo<   <br>"; 
echo "TipoArchivo >$TipoArchivo<   <br>"; 
echo "LogValidacion >$LogValidacion<   <br>"; 
echo "TipoRegistro >$TipoRegistro<   <br>"; 
**/
$db = new DbCnnx();

$IdProceso = $IdEstado."_".$Anio."_".$Periodo."_".$IdRemesa."_".$TipoArchivo.".sql";
$IdProcesoExec = $IdEstado."_".$Anio."_".$Periodo."_".$IdRemesa."_".$TipoArchivo.".bat";
$PathStaging ="../staging/";
$VAL = UNO;
$EXEC= UNO;
if(($ResultadoValidacion > CERO) and (($ResValidacionTipoArch == DATA_NOMINA) OR ($ResValidacionTipoArch == DATA_NOMINA_TRAILER))){

	$GestorArchivoSQL = fopen($PathStaging.$IdProceso, "w");
	if ($GestorArchivoSQL){
		$ArrayPath = explode("/",$LogValidacion);
		$NombreArchivo = $ArrayPath[DOS];
		$FechaEvento = substr($NombreArchivo,0,14);
		$FechaEvento= $db->quote($FechaEvento);
		$LogValidacion= $db->quote($LogValidacion);

		$SQLRegistro = "INSERT INTO bitacora( fecha_evento, id_remesas,  archivo_procesado,
					  registro,  error,  campo,  descripcion, evidencia, id_directiva,
					  estatus,  fecha_actualiacion, archivos, total)
					value(STR_TO_DATE($FechaEvento,'%Y%m%d%H%i%s'),$IdRemesa, $LogValidacion,
					null,null,null,'Resultado de Proceso de Validacion de Directivas de Calidad',null,1,
					'E',null,$LogValidacion, $ResultadoValidacion)";
		$Rows = $db->select($SQLRegistro);
		echo "erro >> ". $db->error()."<< \n";	
		fwrite($GestorArchivoSQL,$SQLRegistro);
		fclose($GestorArchivoSQL);
		$VAL = CERO;
	}// fin de if ($GestorArchivoErr)
	else
		echo "\n No s epudo ejecutar el proeso de carga \n";
} // fin de f(($ResultadoValidacion > CERO) and ($ResValidacionTipoArch == DATA_NOMINA)

 $RegNotificacion =registraNotificacion($IdEstado,$Anio,$Periodo,$IdRemesa,$TipoArchivo,$LogValidacion, $IdUsuario); 

}// registraResultadosValidacion

?>