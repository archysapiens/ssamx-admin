<?php

/*************************************************************
* 
*  Funcion : obtenProcesosPlanificados
*  Objetivo: Obtiene los archivos que estan por planificarse
*            
*  Fecha   : 16-May-2016
*  Autor   : Archy Sapiens
*
*  Parametros
*   $IdPlanificacion : Identificación de la remesa
*  Valor de regreso : Vector con archivos
*
***************************************************************/   

function obtenProcesosPlanificados($IdPlanificacion){
	$db = new DbCnnx();   
	$SQL= "SELECT   fecha_evento,   id_remesas,   archivo_procesado
			FROM ssa.bitacora
			where id_remesas = $IdPlanificacion
			and estatus='P'";
	//echo "pfma_validacion_archivos.inc/obtenProcesosPlanificados/ SQL>>".$SQL."<< <br>";		
	$Rows = $db->select($SQL);
	if(!$Rows){
		echo "<br>pfma_validacion_archivos.inc/obtenProcesosPlanificados/No existe Remesa autorizada <br>";
	}	
	else{	
		return $Rows;
	}// fin de if
}// fin de obtenProcesosPlanificados

/*************************************************************
* 
*  Funcion : planificaProceso
*  Objetivo: Planifica el proceso de validacion y carga
*            
*            
*  Fecha   : 03-May-2016
*  Autor   : Archy Sapiens
*
*  Parametros
*   $IdEstado : Identificación del Organismo
*   $Anio     : Anio del perido(2016, 2017, 2018,etc)
*   $Prdiodo  : Quincena procesada(Q1, Q2, Q3, etc.)
*   $TipoArch : Tipo del Archivo a procesar(1-X00, 2-416, 3-610, etc.)   
*   $LogValidacion : Es una rchivo en donde quedaron asentadas las 
*                    validaciones realizadas. 
*   $EstatusPlan: Este parametro nos indica que registro en bitacora 
*                  se realizara:
*                  CERO  : Planifica el proceso
*                  -UNO  : Resgitra Error en formato Archivo
*  Valor de regreso
*
***************************************************************/   

function planificaProceso($IdEstado,$Anio,$Periodo,$TipoArchivo,$LogValidacion, $EstatusPlan,$IdTry)
{ 
/**
echo "registraValidacion ";
echo "IdEstado >$IdEstado<   <br>"; 
echo "Anio >$Anio<   <br>"; 
echo "Periodo >$Periodo<   <br>"; 
echo "TipoArchivo >$TipoArchivo<   <br>"; 
echo "LogValidacion >$LogValidacion<   <br>"; 
echo "EstatusPlan >$EstatusPlan<   <br>"; 
echo "IdTry >$IdTry<   <br>"; 
**/
$RemesaPlanificada=0;
$db = new DbCnnx();   
/*
date_default_timezone_set('America/Mexico_City');
$FechaProceso = date("Ymd");
$HoraProceso = date("His");
$FechaProceso =$FechaProceso.$HoraProceso;
*/
$FechaProceso=substr($IdTry,8,14);

$LogValidacionTmp =$LogValidacion;
$PathArray=explode("/",$LogValidacion);
$RenTmp =$PathArray[count($PathArray)-UNO];
//echo "RenTmp >>$RenTmp<< <br>";
$RenTmp2=$FechaProceso.$RenTmp;
//echo "RenTmp2 >>$RenTmp2<< <br>";
//echo "Antes LogValidacion >>$LogValidacion<< <br>";
$LogValidacion = str_replace($RenTmp, $RenTmp2, $LogValidacion);
//echo "Despues LogValidacion >>$LogValidacion<< <br>";


$FechaProceso = $db->quote($FechaProceso);
$IdEdo = $db->quote($IdEstado);
$LogToLoad = $db->quote($LogValidacion);
$StrMsg = "Planificacion";
$StrEstat="P";
if($EstatusPlan != CERO){
	$StrMsg = "Error ZIP";
	$StrEstat="E";
}
$StrPlan=$db->quote($StrMsg);
$StrEstat=$db->quote($StrEstat);




if(!rename($LogValidacionTmp, $LogValidacion))
	echo "pfma_validacion_archivos/rename";

$SQL = " SELECT	  id FROM remesas WHERE id_organismos=" . $IdEdo . " AND  
			estatus='A' AND id_archivos= " . $TipoArchivo . " AND 
			anio_periodos=". $Anio . " AND numero_periodos = ". $Periodo ;
//echo "planificaProceso/SQL Remesa>" .$SQL ."< <br>";
$rows = $db->select($SQL);
if(!$rows){
	echo "<br>pfma_validacion_archivos.inc/planificaProceso/No existe Remesa autorizada <br>";
	$RemesaPlanificada=0;
}	
else{	
		$IdValidacion =  CERO;
		$Contador=  CERO;
		while(isset($rows[$Contador]['id'])){
			$IdValidacion = $rows[$Contador]['id'] ;

			$Contador++;
		}// fin de while	
		$RemesaPlanificada=$IdValidacion;
	    $SQL ="INSERT INTO bitacora (fecha_evento, id_remesas, archivo_procesado, registro, error, campo, descripcion, evidencia, id_directiva,estatus) VALUES ( STR_TO_DATE(" . $FechaProceso . ",'%Y%m%d%H%i%s')," . $IdValidacion .",". $LogToLoad .",". CERO .",".
		$StrPlan .",". $StrPlan. ",".$StrPlan.",". $StrPlan.",1," .$StrEstat .")";
		//echo "Segundo SQL CERO >". $SQL ."< <br>";
		$rows = $db->select($SQL);
  }	// fin de existencia de remesa I  
  return $RemesaPlanificada;
}// fin de planificaProceso





/*************************************************************
* 
*  Funcion : registraValidacion
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

function registraValidacion($IdEstado,$Anio,$Periodo,$TipoArchivo,$LogValidacion,$TipoRegistro)
{ 
/**	
echo "registraValidacion ";
echo "IdEstado >$IdEstado<   <br>"; 
echo "Anio >$Anio<   <br>"; 
echo "Periodo >$Periodo<   <br>"; 
echo "TipoArchivo >$TipoArchivo<   <br>"; 
echo "LogValidacion >$LogValidacion<   <br>"; 
echo "TipoRegistro >$TipoRegistro<   <br>"; 
**/
$db = new DbCnnx();   
date_default_timezone_set('America/Mexico_City');
$FechaProceso = date("d-m-Y");
$HoraProceso = date("H:i:s");
$FechaProceso =$FechaProceso." ".$HoraProceso;
$FechaProceso = $db->quote($FechaProceso);
$IdEdo = $db->quote($IdEstado);
$LogToLoad = $db->quote($LogValidacion);
$SQL = " SELECT	  id FROM remesas WHERE id_organismos=" . $IdEdo . " AND  
			estatus='A' AND id_archivos= " . $TipoArchivo . " AND 
			anio_periodos=". $Anio . " AND numero_periodos = ". $Periodo ;
//echo "SQL Remesa>" .$SQL ."< <br>";
$rows = $db->select($SQL);
if(!$rows)
	echo "<br>pfma_validacion_archivos.inc/registraValidacion/No existe Remesa autorizada<br>";
else{	
		$IdValidacion =  CERO;
		$Contador=  CERO;
		while(isset($rows[$Contador]['id'])){
			$IdValidacion = $rows[$Contador]['id'] ;
			$Contador++;
		}// fin de while	
		//echo "<br> IdValidacion >" . $IdValidacion . "< <br>";
		//echo "<br> TipoRegistro >" . $TipoRegistro . "< <br>";
	
	if($TipoRegistro > CERO) {
		$GestorArchivoErr = fopen($LogValidacion, "r");
		if ($GestorArchivoErr){
		   while (($RegistroErr=fgets($GestorArchivoErr, 4096))!==false){
		    	$ArrRegistroErr = explode("|",$RegistroErr);
		    	$StrErr = $db->quote($ArrRegistroErr[3]);
		    	$StrCampo = $db->quote($ArrRegistroErr[1]);
		    	$StrDes = $db->quote($ArrRegistroErr[3]);
		    	$BanderaRegistr=CERO;
	        	$ArrRegistroErr = explode("|",$RegistroErr);
		        $SQL ="INSERT INTO BITACORA (fecha_evento, id_remesas, archivo_procesado, registro, error, campo, descripcion, evidencia, id_directiva,
				 estatus) VALUES ( STR_TO_DATE(" . $FechaProceso . ",'%d-%m-%Y %H:%i:%s')," . $IdValidacion .",". $LogToLoad .",". $ArrRegistroErr[0] .",".
					  $StrErr .",". $StrCampo. ",".$StrDes.",". $StrCampo.",1,'E')";
					 // echo "Segundo SQL >". $SQL ."< <br>";
				$rows = $db->select($SQL);
		    } //fin del while   
		}// fin Gestor Archvio	
 	}elseif($TipoRegistro ==CERO){	
		$StrOK=$db->quote("Sin Error");
	    $SQL ="INSERT INTO BITACORA (fecha_evento, id_remesas, archivo_procesado, registro, error, campo, descripcion, evidencia, id_directiva,estatus) VALUES ( STR_TO_DATE(" . $FechaProceso . ",'%d-%m-%Y %H:%i:%s')," . $IdValidacion .",". $LogToLoad .",". CERO .",".
		$StrOK .",". $StrOK. ",".$StrOK.",". $StrOK.",1,'K')";
		//echo "Segundo SQL CERO >". $SQL ."< <br>";
		$rows = $db->select($SQL);
	}elseif($TipoRegistro < CERO){
		$StrOK=$db->quote("Error de Formato de Archivos");
	    $SQL ="INSERT INTO BITACORA (fecha_evento, id_remesas, archivo_procesado, registro, error, campo, descripcion, evidencia, id_directiva,estatus) VALUES ( STR_TO_DATE(" . $FechaProceso . ",'%d-%m-%Y %H:%i:%s')," . $IdValidacion .",". $LogToLoad .",". CERO .",".
		$StrOK .",". $StrOK. ",".$StrOK.",".$StrOK.",1,'F')";
		//echo "Segundo SQL >". $SQL ."< <br>";
		$rows = $db->select($SQL);
	}
  }	// fin de existencia de remesa I  
}// fin de registraValidacion

/*************************************************************
* 
*  Funcion : validaCamposArchivo
*  Objetivo: Validar el numero de cmapos que tiene el archivo
*            
*  Fecha   : 12-Abr-2016
*  Autor   : Archy Sapiens
*
*  Parametros
*   $Archivo : Rutay nombre de archivo a validar
*
***************************************************************/   

function validaCamposArchivo($Archivo)
{
	$ValRegreso=FALLA;
	if (!copy($Archivo, $Archivo.".bak")) {
    	echo "Error al copiar $Archivo  <br>";
		$ValRegreso=FALLA;
	}
	else{
		$GestorArchivo = fopen($Archivo.".bak", "r");
		if ($GestorArchivo){
		    while (($Registro = fgets($GestorArchivo, 4096)) !== false) 
		    {
		    	//  83 echo " validaCamposArchivo >" .substr_count($Registro, '|') ."< <br>";
		    	if(  substr_count($Registro, '|') > 70)
		    		$ValRegreso=DATA_NOMINA;
		    	elseif(substr_count($Registro, '|') < 70)
		    		$ValRegreso=DATA_NOMINA_TRAILER;
		    	else
		    		$ValRegreso=FALLA;
	    		break;
		    }// fin del while	
		    fclose($GestorArchivo);
		 }    
		 else
		 	return FALLA;
	}// fin copy
	return $ValRegreso;
} // function validaCamposArchivo($Archivo)

/*************************************************************
* 
*  Funcion : validateDate
*  Objetivo: Validar formatos de Fecha
*            
*  Fecha   : 11-Abr-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $Fecha : Fecha a Validar
*   $Formato     : aaaammdd
*
***************************************************************/   

function validateDate($Fecha, $Formato = 'Ymd')
{
    $d = DateTime::createFromFormat($Formato, $Fecha);
    return $d && $d->format($Formato) == $Fecha;
}



/*************************************************************
* 
*  Funcion : fncValidaArchivo
*  Objetivo: Validar el archivo de datos
*            
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   $Path     : Ruta de ubicacion 
*   $Archivo  : Archivo dedatos a validar
*   
*
***************************************************************/   

function fncValidaArchivo($IdEstado, $Path,$Archivo)
{
	$TotalRegErr      = CERO;
 	$ContadorRegistros=UNO;
 	
 	$ContadorErrorDI = InicializaArray(80);

 	$GestorArchivoErr = fopen($Path.$Archivo.".err", "w");
 	if (!$GestorArchivoErr) 
	{
		echo "Error al abrir archivo Error >>".$Path.$Archivo.".err" ."<<";
	}
	else{
		$GestorArchivo = fopen($Path.$Archivo, "r");
		if ($GestorArchivo) 
		{
		    while (($Registro = fgets($GestorArchivo, 4096)) !== false) 
		    {
		    	$BanderaRegistr=0;
		   //     echo "Resgistro >>" . $Registro ."<<";
		        $ArrRegistro = explode("|",$Registro);
		        $NumEmpl= $ArrRegistro[0];
		        $NumFili= $ArrRegistro[1];
		        $CURP= $ArrRegistro[2];

		        $NombreEmpleado = $ArrRegistro[3];
		        $BancoNvo= $ArrRegistro[SEIS];
		        $NumCta = $ArrRegistro[SIETE];
		        $CLABE= $ArrRegistro[OCHO];
		        $CveSPC= $ArrRegistro[NUEVE];
		        $UR= $ArrRegistro[14];
		        $GF= $ArrRegistro[15];
		        $Fun= $ArrRegistro[16];
		        $SFun= $ArrRegistro[17];
		        $PG= $ArrRegistro[18];
		        $AI= $ArrRegistro[19];
		        $PP= $ArrRegistro[20];
		        $Ptda= $ArrRegistro[21];
		        $Pto= $ArrRegistro[22];
		        $NumPto= $ArrRegistro[23];
		        $Edo= $ArrRegistro[24];
		        $Mpio= $ArrRegistro[25];
		        $CenRes= $ArrRegistro[26];
		        $NSS= $ArrRegistro[27];
		        $Pagdria= $ArrRegistro[28];
		        $FteFin = $ArrRegistro[29];
		        $TabPto = $ArrRegistro[30];
		        $NIVEL = $ArrRegistro[31];
		        $Rango = $ArrRegistro[32];
		        $IndMando = $ArrRegistro[33];
		        $Horario = $ArrRegistro[34];
		        // el campo 36 queda libre
		        $TipTra = $ArrRegistro[36];
		        $NivSPC= $ArrRegistro[37];
		        $IndStat= $ArrRegistro[38];
		        $FecIng= $ArrRegistro[39];
		        $FecIngSS= $ArrRegistro[40];
		        $FecReIng= $ArrRegistro[41];
				$FecPag= $ArrRegistro[43];

				$PerPagIni= $ArrRegistro[44];
				$PerPagFin= $ArrRegistro[45];
				$PerAppIni= $ArrRegistro[46];
				$PerAppFin= $ArrRegistro[47];

				

				$QnaProReal= $ArrRegistro[48];
				$AnioProReal= $ArrRegistro[49];

				$TipoPago = $ArrRegistro[50];
				// no va (52) Instrumento de Pago Anterior  (Libre) 
				$IntrPagoNvo = $ArrRegistro[52];
				$Prpcns = $ArrRegistro[53];
				$Dedcns = $ArrRegistro[54];
				$Neto = $ArrRegistro[55];
				$NumTrail = $ArrRegistro[56];
				$NomProd = $ArrRegistro[58];
				$NumCtrl = $ArrRegistro[59];
				$NumCque = $ArrRegistro[60];
				// no hay regla 61
				$Jnda    = $ArrRegistro[62];
				// no hay 63 Número de Días de Prima Dominical (Libre)
				$CicloFONAC = $ArrRegistro[64];
				$NumAportFONAC= $ArrRegistro[65];
				$AcumuladoFONAC= $ArrRegistro[66];
				// no hay 67 Número de faltas en la quincena (Libre)
				$LicCLUES = $ArrRegistro[68];

				$PorcPen1 = $ArrRegistro[69];
				$PorcPen2 = $ArrRegistro[70];
				$PorcPen3 = $ArrRegistro[71];
				$PorcPen4 = $ArrRegistro[72];
				$PorcPen5 = $ArrRegistro[73];

				$ElecTipRtro = $ArrRegistro[74];				
				$TipUni = $ArrRegistro[75];				
				$DescCR = $ArrRegistro[76];				

		        $ValidaError = fncValidaDI_1($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NumEmpl);
		        if($ValidaError!=0){
					$ContadorErrorDI[UNO]++;		        	
				}
//break;
				$ValidaError = fncValidaDI_2($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NumFili, $NombreEmpleado);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DOS]++;
				}
				
				$ValidaError = fncValidaDI_3($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $CURP, $NombreEmpleado);	
		        if($ValidaError!=0){
					$ContadorErrorDI[TRES]++;		        	
				}


				$ValidaError = fncValidaDI_4($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NombreEmpleado);	
		        if($ValidaError!=0){
					$ContadorErrorDI[CUATRO]++;
				}

				$ValidaError = fncValidaDI_7($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $BancoNvo);	
		        if($ValidaError!=0){
					$ContadorErrorDI[SIETE]++;
				}

				$ValidaError = fncValidaDI_8($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NumCta);	
		        if($ValidaError!=0){
					$ContadorErrorDI[OCHO]++;        	
				}

				$ValidaError = fncValidaDI_9($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $CLABE);	
		        if($ValidaError!=0){
					$ContadorErrorDI[NUEVE]++;
				}

				$ValidaError = fncValidaDI_10($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $CveSPC);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ]++;
				}

				$ValidaError = fncValidaDI_15($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $UR);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + CINCO]++;
				}

				$ValidaError = fncValidaDI_16($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $GF);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + SEIS]++;
				}

				$ValidaError = fncValidaDI_17($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $Fun);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + SIETE]++;
				}

				$ValidaError = fncValidaDI_18($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $SFun);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + OCHO]++;
				}

				$ValidaError = fncValidaDI_19($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $PG);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + NUEVE]++;
				}

				$ValidaError = fncValidaDI_20($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $AI);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ]++;
				}

				$ValidaError = fncValidaDI_21($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $PP);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + UNO]++;
				}

				$ValidaError = fncValidaDI_22($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $Ptda);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DOS]++;
				}
				$ValidaError = fncValidaDI_23($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $Pto);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + TRES]++;
				}

				$ValidaError = fncValidaDI_24($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NumPto);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + CUATRO]++;
				}

				$ValidaError = fncValidaDI_25($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $Edo);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + CINCO]++;
				}

				$ValidaError = fncValidaDI_26($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $Mpio);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + SEIS]++;
				}

				$ValidaError = fncValidaDI_27($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $CenRes);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + SIETE]++;
				}

				$ValidaError = fncValidaDI_28($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NSS);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + OCHO]++;
				}

				$ValidaError = fncValidaDI_29($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $Pagdria);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + NUEVE]++;
				}

				$ValidaError = fncValidaDI_30($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $FteFin);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ]++;
				}

				$ValidaError = fncValidaDI_31($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $TabPto);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + UNO]++;
				}

				$ValidaError = fncValidaDI_32($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NIVEL);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + DOS]++;
				}
				$ValidaError = fncValidaDI_33($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $Rango);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + TRES]++;
				}

				$ValidaError = fncValidaDI_34($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $IndMando);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + CUATRO]++;
				}
				$ValidaError = fncValidaDI_35($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $Horario);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + CINCO]++;
				}

				// campo 36 queda libre

				$ValidaError = fncValidaDI_37($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $TipTra);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + SIETE]++;
				}

				$ValidaError = fncValidaDI_38($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NivSPC);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + OCHO]++;
				}

				$ValidaError = fncValidaDI_39($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $IndStat);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + NUEVE]++;
				}

				$ValidaError = fncValidaDI_40($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $FecIng);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + DIEZ]++;
				}


				$ValidaError = fncValidaDI_41($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $FecIngSS, $FecIng);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + DIEZ + UNO]++;
				}

				$ValidaError = fncValidaDI_42($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $FecReIng,$FecIngSS);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + DIEZ+ DOS]++;
				}

				$ValidaError = fncValidaDI_44($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $FecPag);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + DIEZ+ CUATRO]++;
				}

				$ValidaError = fncValidaDI_45($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $PerPagIni,$PerPagFin);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + DIEZ+ CINCO]++;
				}


				$ValidaError = fncValidaDI_46($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $PerPagFin, $PerPagIni);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + DIEZ+ SEIS]++;
				}

				$ValidaError = fncValidaDI_47($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $PerAppIni, $PerAppFin);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + DIEZ+ SIETE]++;
				}


				$ValidaError = fncValidaDI_48($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $PerAppFin, $PerAppIni);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + DIEZ+ OCHO]++;
				}

				$ValidaError = fncValidaDI_49($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $QnaProReal);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + DIEZ+ NUEVE]++;
				}


				$ValidaError = fncValidaDI_50($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $AnioProReal,$PerPagIni,$PerPagFin);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * CINCO]++;
				}


				$ValidaError = fncValidaDI_51($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $TipoPago);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * CINCO + UNO]++;
				}

				$ValidaError = fncValidaDI_53($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $IntrPagoNvo);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * CINCO + TRES]++;
				}

				$ValidaError = fncValidaDI_54($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $Prpcns);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * CINCO + CUATRO]++;
				}

				$ValidaError = fncValidaDI_55($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $Dedcns);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * CINCO + CINCO]++;
				}

				$ValidaError = fncValidaDI_56($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $Neto);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * CINCO + SEIS]++;
				}

				$ValidaError = fncValidaDI_57($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $NumTrail);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * CINCO + SIETE]++;
				}

				$ValidaError = fncValidaDI_59($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $NomProd);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * CINCO + NUEVE]++;
				}

				$ValidaError = fncValidaDI_60($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $NumCtrl);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SEIS]++;
				}

				$ValidaError = fncValidaDI_61($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $NumCque);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SEIS + UNO]++;
				}
				$ValidaError = fncValidaDI_63($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $Jnda);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SEIS + TRES]++;
				}

				$ValidaError = fncValidaDI_65($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $CicloFONAC);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SEIS + CINCO]++;
				}

				$ValidaError = fncValidaDI_66($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $NumAportFONAC);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SEIS + SEIS]++;
				}

				$ValidaError = fncValidaDI_67($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $AcumuladoFONAC);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SEIS + SIETE]++;
				}

				$ValidaError = fncValidaDI_69($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $LicCLUES );	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SEIS + NUEVE]++;
				}


				$ValidaError = fncValidaDI_70($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $PorcPen1  );	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SIETE ]++;
				}

				$ValidaError = fncValidaDI_71($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $PorcPen2  );	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SIETE + UNO]++;
				}

				$ValidaError = fncValidaDI_72($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $PorcPen3);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SIETE + DOS]++;
				}

				$ValidaError = fncValidaDI_73($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $PorcPen4);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SIETE + TRES]++;
				}

				$ValidaError = fncValidaDI_74($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $PorcPen5);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SIETE + CUATRO]++;
				}

				$ValidaError = fncValidaDI_75($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $ElecTipRtro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SIETE + CINCO]++;
				}

				$ValidaError = fncValidaDI_76($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $TipUni);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SIETE + SEIS]++;
				}

				$ValidaError = fncValidaDI_77($IdEstado, $GestorArchivoErr, 
		        					$ContadorRegistros, $DescCR);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ * SIETE + SIETE]++;
				}
		
		        $ContadorRegistros++;
		    }

		    foreach ($ContadorErrorDI as &$valor) {
 				   		$TotalRegErr = $TotalRegErr + $valor ;
			}
            /**
		    if (!feof($GestorArchivo)) {
		        echo "Error: fallo inesperado de fgets()\n";
		        $TotalRegErr=FALLA;
		    }
		    **/
		    fclose($GestorArchivo);
		} // fin Gestor archivo de datos
	} //Fin  if (!$GestorArchivoErr) 
	return $TotalRegErr;
}// fin de la funcion fncValidaArchivo


function InicializaArray($Limite){
		for($i = 1; $i <= $Limite; $i++) 
		{ 
		    ${'array'}[$i] = 0; 
		} 
	return $array;
} // fin de InicializaArray


/*************************************************************
* 
*  Funcion : fncValidaDI_1
*  Objetivo: Validar el campo Número de Empleado
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr :Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_1($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = 0;

	$DI_1           = "(1)Numero Empleado";
	$DI_1_ErrTam    = "Tamaño de registro debe ser 10";
	$DI_1_ErrIdEdo  = "Identificador de estado Invalido";
	$DI_1_ErrIdEmpl = "Número de Empleado Invalido";

	//echo "Datos Entrada: IdEstado >".$IdEstado. "< \nGestorErr >". $GestorErr ."< \nNumReg >".$NumReg. "< \nCampo >". $Campo ."<\n";

	$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);
	if (strlen($LocCampo) == DIEZ)
	{
		$ValidaIdEstado = substr($LocCampo,0,2);
		if($ValidaIdEstado != $IdEstado)
		{
			$Error = $NumReg ."|".$DI_1."|".$LocCampo."|" . $DI_1_ErrIdEdo." ($IdEstado)|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}
		if(!preg_match ("/\d{8}/" ,substr($LocCampo,2,8)))
		{
			$Error = $NumReg ."|".$DI_1."|".$LocCampo."|" . $DI_1_ErrIdEmpl."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
	/**
		$Error = $NumReg ."|".$DI_1."|".$Campo."|" . $DI_1_ErrTam."|" .strlen(preg_replace('/[^A-Za-z0-9\-]/', '', $Campo))."|\n";
    **/
		$Error = $NumReg ."|".$DI_1."|".$Campo."|" . $DI_1_ErrTam."|\n";
		
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_1



/*************************************************************
* 
*  Funcion : fncValidaDI_2
*  Objetivo: Validar el campo Número de Empleado
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_2($IdEstado, $GestorErr, $NumReg, $Campo,$CampoAux)
{
	 
	$Bandera = 0;

	$DI_2           = "(2)Filiación";
	$DI_2_ErrTam    = "Tamaño de registro debe ser 13 Caracteres";
	$DI_2_ErrIdEdo  = "Identificador de estado Invalido";
	$DI_2_ErrRFC = "RFC Incorrecto en Sección I AAAA";
	$DI_2_ErrFecNac = "RFC Incorrecto en Sección II Fecha Nacimiento";
	$DI_2_ErrHomoCve = "RFC Incorrecto en Sección III Homoclave";


	//echo "Datos Entrada: IdEstado >".$IdEstado. "< \nGestorErr >". $GestorErr ."< \nNumReg >".$NumReg. "< \nCampo >". $Campo ."<\n";
	$MtrxStrAux = explode("/", $CampoAux);
	$MtrxStrAuxApp = explode(",", $MtrxStrAux[CERO]);
	$AppPat		= (isset($MtrxStrAuxApp[CERO]))?$MtrxStrAuxApp[CERO]:"" ;
	$AppMat     = (isset($MtrxStrAuxApp[UNO]))?$MtrxStrAuxApp[UNO]:"";
	$NomEmpl    = (isset($MtrxStrAux[UNO]))?$MtrxStrAux[UNO]:"";
/**	
	echo "AppPat >$AppPat< <br>";
	echo "AppMat >$AppMat< <br>";
	echo "Nombre >$NomEmpl< <br>";
**/	
    /** Quita caracteres especiales **/
	$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);

	if (strlen($LocCampo) == 13)
	{

		if(!preg_match ("/[A-Z,a-z]{4}/" ,substr($LocCampo,0,4)))
		{
			$Error = $NumReg ."|".$DI_2."|".$LocCampo."|" . $DI_2_ErrRFC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
		$CampoAux = substr($LocCampo,4,6);
		if(!preg_match ("/\d{6}/" ,$CampoAux))
		{
			$Error = $NumReg ."|".$DI_2."|".$LocCampo."|" . $DI_2_ErrFecNac ."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	

		if(strlen(substr($LocCampo,10,3)) != TRES)
		{
			$Error = $NumReg ."|".$DI_2."|".$LocCampo."|" . $DI_2_ErrHomoCve ."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	

	}
	else
	{
		$Error = $NumReg ."|".$DI_2."|".$Campo."|" . $DI_2_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_2


/*************************************************************
* 
*  Funcion : fncValidaDI_3
*  Objetivo: Validar el campo CURP
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_3($IdEstado, $GestorErr, $NumReg, $Campo,$CampoAux)
{
	 
	$Bandera = 0;
	$CatEdo = array("AS" , "BC","BS", "CC", "CL", "CM","CS", "CH", "DF", 
				"DG", "GT", "GR", "HG", "JC", "MC","MN", "MS", "NT", "NL", "OC",
				"PL", "QT", "QR", "SP","SL", "SR", "TC", "TS", "TL","VZ", "YN", "ZS", "NE");

	$DI_3           = "(3)Clave Única de Registro de Población (CURP)";
	$DI_3_ErrTam    = "Tamaño de registro debe ser 18 Caracteres";
	$DI_3_ErrIdEdo  = "Identificador de estado Invalido";
	$DI_3_ErrRFC = "CURP Incorrecto en Sección I AAAA";
	$DI_3_ErrFecNac = "CURP Incorrecto en Sección II Fecha Nacimiento";
	$DI_3_ErrGenero = "CURP Incorrecto en Sección III Genero";
	$DI_3_ErrEntFecNac= "CURP Incorrecto en Sección IV Entidad Federativa Nacimeinto";


	//echo "Datos Entrada: IdEstado >".$IdEstado. "< \nGestorErr >". $GestorErr ."< \nNumReg >".$NumReg. "< \nCampo >". $Campo ."<\n";
	$MtrxStrAux = explode("/", $CampoAux);
	$MtrxStrAuxApp = explode(",", $MtrxStrAux[CERO]);
	$AppPat		= (isset($MtrxStrAuxApp[CERO]))?$MtrxStrAuxApp[CERO]:"" ;
	$AppMat     = (isset($MtrxStrAuxApp[UNO]))?$MtrxStrAuxApp[UNO]:"";
	$NomEmpl    = (isset($MtrxStrAux[UNO]))?$MtrxStrAux[UNO]:"";
/**	
	echo "AppPat >$AppPat< <br>";
	echo "AppMat >$AppMat< <br>";
	echo "Nombre >$NomEmpl< <br>";
**/	
    /** Quita caracteres especiales **/
	$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);

	if (strlen($LocCampo) == 18)
	{

		if(!preg_match ("/[A-Z,a-z]{4}/" ,substr($LocCampo,0,4)))
		{
			$Error = $NumReg ."|".$DI_3."|".$LocCampo."|" . $DI_3_ErrRFC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
		$CampoAux = substr($LocCampo,4,6);
		if(!preg_match ("/\d{6}/" ,$CampoAux))
		{
			$Error = $NumReg ."|".$DI_3."|".$LocCampo."|" . $DI_3_ErrFecNac ."|$CampoAux\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	

		if(!preg_match ("/[M|H|m|h]{1}/" ,substr($LocCampo,10,1)))
		{
			$Error = $NumReg ."|".$DI_3."|".$LocCampo."|" . $DI_3_ErrGenero ."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
		if(!in_array(substr($LocCampo,11,2), $CatEdo))
		{
			$Error = $NumReg ."|".$DI_3."|".$LocCampo."|" . $DI_3_ErrEntFecNac ."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_3."|".$LocCampo."|" . $DI_3_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_3


/*************************************************************
* 
*  Funcion : fncValidaDI_4
*  Objetivo: Validar el campo Nombre Empleado
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_4($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = 0;

	$DI_4           = "(4)Nombre del Empleado";
	$DI_4_ErrTam    = "Tamaño de registro debe ser 150 Caracteres";
	$DI_4_ErrIdEdo  = "Identificador de estado Invalido";
	$DI_4_ErrEstructura = "EL campo no cumple con estructura definida PATERNO,MATERNO/NOMBRE(S)";

    /** Quita caracteres especiales **/
	//$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);
	$LocCampo =$Campo;
	if (strlen($LocCampo) <= 150)
	{
		if(!preg_match ("/[?,A-Z,a-z,\s]{1,90},[?,A-Z,a-z,\s]{1,90}\/[?.A-Z,a-z,\s]{1,90}/" ,$LocCampo))
		{
			$Error = $NumReg ."|".$DI_4."|".$LocCampo."|" . $DI_4_ErrEstructura."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_4."|".$LocCampo."|" . $DI_4_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_4


/***
Las directivas 5 y 6 estan en definición.

***/



/*************************************************************
* 
*  Funcion : fncValidaDI_7
*  Objetivo: Validar el campo Banco Nuevo
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_7($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = 0;

	$DI_7           = "(7)Banco Nuevo";
	$DI_7_ErrTam    = "Tamaño de registro debe ser 5 dígitos";
	$DI_7_TESOFE  = "Identificador no pertenece al Catalogo de TESOFE/DGRH";

//	$TESOFE = explode("\n", file_get_contents('catalogo_tesofe.txt'));
	$TESOFE = array("2001","37006","37009","37019","37135","37166","37168","40002","40012",
"40014","40021","40022","40030","40032","40036","40037","40042","40044","40058","40059","40060",
"40062","40072","40102","40103","40106","40108","40110","40112","40113","40116","40124","40126",
"40127","40128","40129","40130","40131","40132","40133","40134","40136","40137","40138","40139",
"40140","40143","90600");

    /** Quita caracteres especiales **/
	//$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);
	$LocCampo =$Campo;
	if (strlen($LocCampo) == 5)
	{
		if(!in_array($LocCampo,$TESOFE))
		{
			$Error = $NumReg ."|".$DI_7."|".$LocCampo."|" . $DI_7_TESOFE."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_7."|".$LocCampo."|" . $DI_7_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_7

/*************************************************************
* 
*  Funcion : fncValidaDI_8
*  Objetivo: Validar el campo Numero de Cuenta
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_8($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = 0;

	$DI_8           = "(8)Numero de Cuenta";
	$DI_8_ErrTam    = "Tamaño de Numero de Cuenta debe ser 16 dígitos";
	$DI_8_NumCta    = "No cumple con Directiva debe ser 16 digitos";

    /** Quita caracteres especiales **/
	//$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);
	$LocCampo =$Campo;
	if (strlen($LocCampo) == 16)
	{
		if(!preg_match ("/\d{16}/" ,$LocCampo))
		{
			$Error = $NumReg ."|".$DI_8."|".$LocCampo."|" . $DI_8_NumCta."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_8."|".$LocCampo."|" . $DI_8_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_8



/*************************************************************
* 
*  Funcion : fncValidaDI_9
*  Objetivo: Validar el campo Clave del Banco (CLABE)
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_9($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = 0;

	$DI_9           = "(9)Clave del Banco (CLABE)";
	$DI_9_ErrTam    = "Tamaño de Clave del Banco (CLABE) debe ser 18 dígitos";
	$DI_9_NumCta    = "No cumple con Directiva debe ser 18 digitos";

	

    /** Quita caracteres especiales **/
	//$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);
	$LocCampo =$Campo;
	if (strlen($LocCampo) == 18)
	{
		if(!preg_match ("/\d{18}/" ,$LocCampo))
		{
			$Error = $NumReg ."|".$DI_8."|".$LocCampo."|" . $DI_8_NumCta."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_9."|".$LocCampo."|" . $DI_9_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_9



/*************************************************************
* 
*  Funcion : fncValidaDI_10
*  Objetivo: Validar el campo Clave del Servicio Profesional de Carrera (FUNCION)
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_10($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_10           = "(10)Clave del Servicio Profesional de Carrera (FUNCION)";
	$DI_10_ErrTam    = "Tamaño de Clave del Servicio Profesional de Carrera (FUNCION) debe ser 2 dígitos";
	$DI_10_CveInda   = "La cleve debe ser de 2 digitos";

	

    /** Quita caracteres especiales **/
	//$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);
	$LocCampo =$Campo;
	if (strlen($LocCampo) == DOS)
	{
		if(!preg_match ("/\d{2}/" ,$LocCampo))
		{
			$Error = $NumReg ."|".$DI_10."|".$LocCampo."|" . $DI_10_CveInda."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_10."|".$LocCampo."|" . $DI_10_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_10

/*************************************************************
* 
*  Funcion : fncValidaDI_15 
*  Objetivo: Validar el campo Unidad Responsable
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_15($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_15           = "(15)Unidad Responsable";
	$DI_15_ErrTam    = "Tamaño de UR debe ser Alfanumérico a 3 posiciones";
	$DI_15_UR   = "La UR no es parte del catalogo de DGRH";

	//$UR = explode("\n", file_get_contents('catalogo_ur.txt'));
	$UR = array("316","AYK","NCE","M7A","NBQ","NBR","NBS","615","NBU","100","111",
"112","113","114","160","170","171","172","300","310","312","313","314","315","416",
"500","510","511","512","513","514","600","610","611","613","614","E00","H06","I00",
"K00","L00","M00","N00","O00","PBP","PSF","Q00","R00","S00","S01","S02","S03","S04",
"S05","S06","S07","S08","S09","S10","S11","S12","S13","S14","S15","S16","S17","S18",
"S19","S20","S21","S22","S23","S24","S25","S26","S27","S28","S29","S30","S31","S32",
"SME","SPC","SPG","SPM","SSP","T00","U00","V00","VEC","VGE","W00","180","X00",
"REG","FO2","CON","FOR","HOM");

    /** Quita caracteres especiales **/
	//$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);

	$LocCampo =$Campo;
	if (strlen($LocCampo) == TRES)
	{
		if(!in_array($LocCampo,$UR))
		{
			$Error = $NumReg ."|".$DI_15."|".$LocCampo."|" . $DI_15_UR."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_15."|".$LocCampo."|" . $DI_15_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_15


/*************************************************************
* 
*  Funcion : fncValidaDI_16 
*  Objetivo: Validar el campo Grupo Funcional
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_16($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_16           = "(16)Grupo Funcional";
	$DI_16_ErrTam    = "Tamaño de Grupo Funcional debe ser dígito a 1 posicion";
	$DI_16_GF   = "El grupo Funcional no es parte del catalogo de DGRH";

	

    /** Quita caracteres especiales **/
	//$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);

	$LocCampo =$Campo;
	if (strlen($LocCampo) == UNO)
	{
		if(!preg_match ("/[1-4]{1}/" ,$LocCampo))
		{
			$Error = $NumReg ."|".$DI_16."|".$LocCampo."|" . $DI_16_GF."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_16."|".$LocCampo."|" . $DI_16_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_16

/*************************************************************
* 
*  Funcion : fncValidaDI_17 
*  Objetivo: Validar el campo Función
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_17($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_17           = "(17)Función";
	$DI_17_ErrTam    = "Tamaño de Función debe ser dígito a 1 posicion";
	$DI_17_F   = "La UR no es parte del catalogo de DGRH";

	

    /** Quita caracteres especiales **/
	//$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);

	$LocCampo =$Campo;
	if (strlen($LocCampo) == UNO)
	{
		if(!preg_match ("/[1-4]{1}/" ,$LocCampo))
		{
			$Error = $NumReg ."|".$DI_17."|".$LocCampo."|" . $DI_17_F."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_17."|".$LocCampo."|" . $DI_17_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_17

/*************************************************************
* 
*  Funcion : fncValidaDI_18 
*  Objetivo: Validar el campo SubFuncion
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_18($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_18           = "(18)SubFuncion";
	$DI_18_ErrTam    = "Tamaño de SubFunción debe ser dígito a 2 posicion";
	$DI_18_SF   	 = "La SubFuncion no es parte del catalogo de DGRH";

	

    /** Quita caracteres especiales **/
	//$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);
    $SF= array("01","02","03","04","10","15","05");
	$LocCampo =$Campo;
	if (strlen($LocCampo) == DOS)
	{
		if(!in_array($LocCampo,$SF))
		{
			$Error = $NumReg ."|".$DI_18."|".$LocCampo."|" . $DI_18_SF."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_18."|".$LocCampo."|" . $DI_18_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_18


/*************************************************************
* 
*  Funcion : fncValidaDI_19 
*  Objetivo: Validar el campo Programa General

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_19($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_19           = "(19)Programa General";
	$DI_19_ErrTam    = "Tamaño de Programa General debe ser dígito a 2 posicion";
	$DI_19_PG   	 = "La Programa General no es parte del catalogo de DGRH";

	

    /** Quita caracteres especiales **/
	//$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);
    $PG= array("04","09","15");

	$LocCampo =$Campo;
	if (strlen($LocCampo) == DOS)
	{
		if(!in_array($LocCampo,$PG))
		{
			$Error = $NumReg ."|".$DI_19."|".$LocCampo."|" . $DI_19_PG."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_19."|".$LocCampo."|" . $DI_19_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_19

/*************************************************************
* 
*  Funcion : fncValidaDI_20 
*  Objetivo: Validar el campo Actividad Institucional

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_20($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_20           = "(20)Actividad Institucional";
	$DI_20_ErrTam    = "Tamaño de Actividad Institucional debe ser dígito a 3 posicion";
	$DI_20_AI   	 = "La Actividad Institucional no es parte del catalogo de DGRH";
	
    $AI= array("002","004","015","019");

	$LocCampo =$Campo;
	if (strlen($LocCampo) == TRES)
	{
		if(!in_array($LocCampo,$AI))
		{
			$Error = $NumReg ."|".$DI_20."|".$LocCampo."|" . $DI_20_AI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_20."|".$LocCampo."|" . $DI_20_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_20

/*************************************************************
* 
*  Funcion : fncValidaDI_21 
*  Objetivo: Validar el campo Proyecto Proceso

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_21($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_21           = "(21)Proyecto Proceso";
	$DI_21_ErrTam    = "Tamaño de Actividad Institucional debe ser  a 4 Alfanumerico";
	$DI_21_PP   	 = "La Proyecto Proceso no es parte del catalogo de DGRH";
	
    $PP= array("1301", "E010","E025","I002");

	$LocCampo =$Campo;
	if (strlen($LocCampo) == CUATRO)
	{
		if(!in_array($LocCampo,$PP))
		{
			$Error = $NumReg ."|".$DI_21."|".$LocCampo."|" . $DI_21_PP."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_21."|".$LocCampo."|" . $DI_21_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_21

/*************************************************************
* 
*  Funcion : fncValidaDI_22 
*  Objetivo: Validar el campo Partida

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_22($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_22           = "(22)Partida";
	$DI_22_ErrTam    = "Tamaño de Actividad Institucional debe ser  a 5 Alfanumerico";
	$DI_22_Ptda   	 = "La Partida no es parte del catalogo de DGRH";
	
    $Ptda= array("44106","12301","11301");

	$LocCampo =$Campo;
	if (strlen($LocCampo) == CINCO)
	{
		if(!in_array($LocCampo,$Ptda))
		{
			$Error = $NumReg ."|".$DI_22."|".$LocCampo."|" . $DI_22_Ptda."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_22."|".$LocCampo."|" . $DI_22_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_22


/*************************************************************
* 
*  Funcion : fncValidaDI_23 
*  Objetivo: Validar el campo Puesto

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_23($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_23           = "(23)Puesto";
	$DI_23_ErrTam    = "Tamaño de Puesto debe ser  a 7 Alfanumerico";
	$DI_23_Pto   	 = "El Puesto no es parte del catalogo de DGRH";
	
    $Pto= array("CFKA003",
"CFKB003",
"CFOB003",
"OP98542",
"M02057",
"M02074",
"M02078",
"AM98582",
"AM98592",
"CF41027",
"CF41054",
"CFGB002",
"CFHB001",
"CFIC002",
"CFJB001",
"CFKB002",
"OP98552",
"M01007",
"M02055",
"M02065",
"M02106",
"M04005",
"CF41003",
"CF41022",
"CF41041",
"CF41049",
"CFJA003",
"CFMA003",
"CFMC002",
"CFNA002",
"CFPA002",
"CFPB003",
"CFPC002",
"M01003",
"M02007",
"M02013",
"M02024",
"M02035",
"M02040",
"M02049",
"M02062",
"M02066",
"M02083",
"M02085",
"M02094",
"M02105",
"M03002",
"M03009",
"M03024",
"CF41001",
"CF41007",
"CF41009",
"CF41012",
"CF41043",
"CF41087",
"CFGA002",
"CFGC001",
"CFGC002",
"CFHA003",
"CFIA002",
"CFIB002",
"CFJB002",
"CFJC001",
"CFJC003",
"CFKA002",
"CFKB001",
"CFKC001",
"CFLA002",
"CFLC001",
"CFMA002",
"CFMB003",
"CFMC001",
"CFMC003",
"CFPQ002",
"MP98512",
"PS98692",
"RS98592",
"M01008",
"M01012",
"M02001",
"M02016",
"M02019",
"M02021",
"M02029",
"M02060",
"M02076",
"M02093",
"M02097",
"M02108",
"M03003",
"M03005",
"M03006",
"M03018",
"M03021",
"M03023",
"M04001",
"CF40001",
"CF40002",
"CF40003",
"CF41010",
"CF41016",
"CF41024",
"CF41028",
"CF41032",
"CF41044",
"CF41048",
"CF41052",
"CF41057",
"CF41058",
"CF41060",
"CF41063",
"CF41075",
"CFGB001",
"CFGB003",
"CFGC003",
"CFHA001",
"CFHB002",
"CFHC001",
"CFHC002",
"CFHC003",
"CFIA003",
"CFIC001",
"CFJB003",
"CFKA001",
"CFLB001",
"CFLC002",
"CFMA001",
"CFNB002",
"CFNB003",
"CFOA002",
"CFOB001",
"CFOC003",
"CFPA003",
"CFPB002",
"EP98571",
"MP98532",
"OP98562",
"CFLB13",
"M01006",
"M02009",
"M02010",
"M02011",
"M02012",
"M02018",
"M02032",
"M02037",
"M02042",
"M02044",
"M02046",
"M02051",
"M02059",
"M02061",
"M02069",
"M02075",
"M02089",
"M02090",
"M02112",
"M03012",
"M04003",
"R12033",
"CF41004",
"CF41011",
"CF41013",
"CF41015",
"CF41018",
"CF41025",
"CF41039",
"CF41040",
"CF41042",
"CF41045",
"CF41056",
"CF41059",
"CF41064",
"CFGA003",
"CFHA002",
"CFIA001",
"CFIB003",
"CFJA001",
"CFJC002",
"CFKC002",
"CFKC003",
"CFLA003",
"CFLB003",
"CFLC003",
"CFMB002",
"CFMB023",
"CFNA001",
"CFNA003",
"CFNB001",
"CFNB037",
"CFNC002",
"CFNC003",
"CFOA001",
"CFOA003",
"CFOB002",
"CFPC003",
"CFPQ003",
"EP98582",
"CFNC001",
"CFOC001",
"CFPA001",
"CFPB001",
"CFPC001",
"CFPQ001",
"CF41047",
"CF41055",
"CF41062",
"CF41065",
"CF41074",
"CF41076",
"CF41077",
"CF41088",
"EP98572",
"MP98522",
"M01002",
"M01004",
"M01005",
"M01009",
"M01010",
"M01011",
"M01015",
"M02003",
"M02004",
"M02006",
"M02008",
"M02014",
"M02015",
"M02017",
"M02020",
"M02022",
"M02023",
"M02031",
"M02034",
"M02036",
"M02038",
"M02043",
"M02047",
"M02048",
"M02050",
"M02054",
"M02056",
"M02058",
"M02063",
"M02064",
"M02067",
"M02068",
"M02072",
"M02073",
"M02077",
"M02081",
"M02084",
"M02086",
"M02091",
"M02095",
"M02096",
"M02098",
"M02107",
"M02110",
"M02113",
"M03001",
"M03004",
"M03007",
"M03010",
"M03013",
"M03019",
"M03020",
"M03022",
"M03025",
"M04002",
"M04004",
"M04011",
"M04012",
"PS98592",
"RS98572",
"RS98582",
"M02100",
"M02101",
"M02109",
"MCT8002",
"MP98510",
"IP98510",
"CF01012",
"CF01059",
"CF21135",
"CF21905",
"CF34068",
"CF34245",
"CF40004",
"CF41002",
"CF41006",
"CF41008",
"CF41014",
"CF41026",
"CF41030",
"CF41038",
"CF41046",
"CF34246",
"CF34260",
"CF34261",
"CF34263",
"CF52000",
"CF41089",
"CF41090",
"M01016",
"M02114",
"M02115",
"M02116",
"M02117",
"M02118",
"M02119",
"M02120",
"CF52348",
"CF53083",
"CFMC03",
"CFMD09",
"CFMD12",
"CFMG06",
"CFMG08",
"CFMS06",
"CFMS08",
"CF01035",
"M02079",
"M02041",
"M02030",
"M02025",
"CF41050",
"CF41037",
"CF41036",
"CF41023",
"CF41017",
"CF52254",
"M02080",
"CF01037",
"CF01038",
"CF01041",
"CF01043",
"CF01046",
"CF01048",
"CF01050",
"CF01052",
"CF01055",
"CF01057",
"CF01060",
"CF01061",
"CF01062",
"CF01071",
"CF01120",
"CF01773",
"CF01776",
"CF01781",
"CF01784",
"CF01786",
"CF01787",
"CF01789",
"CF01907",
"CF01908",
"CF01909",
"CF01910",
"CF01911",
"CF01913",
"CF01914",
"CF01915",
"CF01916",
"CF01917",
"CF21323",
"CF21325",
"CF21326",
"CF51018",
"CF51082",
"CF52339",
"CF52343",
"CF52349",
"CF52383",
"CF52384",
"CF52387",
"CF52389",
"CF52394",
"CF52395",
"CF52397",
"CF52402",
"CF52404",
"CF52405",
"CF52407",
"CF52820",
"CF52937",
"M04006",
"CF01030",
"M01014",
"M02002",
"M02082",
"M02088",
"M03008",
"M03011",
"AM98572",
"CFLA001",
"CFLB002",
"CFMB001",
"CFOC002",
"EP98592",
"M02005",
"M02045",
"M02087",
"M02092",
"M02111",
"CF41031",
"CF41061",
"CF50000",
"CF51000",
"CFGA001",
"CFHB003",
"CFIB001",
"CFIC003",
"CFJA002");

	$LocCampo =$Campo;
	if (strlen($LocCampo) == SIETE)
	{
		if(!in_array($LocCampo,$Pto))
		{
			$Error = $NumReg ."|".$DI_23."|".$LocCampo."|" . $DI_23_Pto."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_23."|".$LocCampo."|" . $DI_23_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_23

/*************************************************************
* 
*  Funcion : fncValidaDI_24 
*  Objetivo: Validar el campo Numero de Puesto

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_24($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_24           = "(24)Número de Puesto";
	$DI_24_ErrTam    = "Tamaño de Número de Puesto debe ser  a 4 Alfanumerico";
	$DI_24_NumPto   	 = "El Número Puesto no es parte del catalogo de DGRH";
	
    $NumPto= array("0022","0101");

	$LocCampo =$Campo;
	if (strlen($LocCampo) == CUATRO)
	{
		if(!in_array($LocCampo,$NumPto))
		{
			$Error = $NumReg ."|".$DI_24."|".$LocCampo."|" . $DI_24_NumPto."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_24."|".$LocCampo."|" . $DI_24_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_24

/*************************************************************
* 
*  Funcion : fncValidaDI_25 
*  Objetivo: Validar el campo Estado

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_25($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_25           = "(25)Estado";
	$DI_25_ErrTam    = "Tamaño de Estado debe ser  a 2 Dígitos";
	$DI_25_Edo    	 = "El Estado no es parte del catalogo de DGRH";
	
    $Edo= array("DF","09","05","04","03","02","01","08","07","06","SP","32","31","30",
"29","28","27","26","25","24","23","22","21","20","19","18","17","16","15","14","13",
"12","11","10");

	$LocCampo =$Campo;
	if (strlen($LocCampo) == DOS)
	{
		if(!in_array($LocCampo,$Edo))
		{
			$Error = $NumReg ."|".$DI_25."|".$LocCampo."|" . $DI_25_Edo."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_25."|".$LocCampo."|" . $DI_25_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_25

/*************************************************************
* 
*  Funcion : fncValidaDI_26 
*  Objetivo: Validar el campo Municipio

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_26($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_26           = "(26)Municipio";
	$DI_26_ErrTam    = "Tamaño de campo Municipio debe ser  a 3 Dígitos";
	$DI_26_Mpio    	 = "El Municipio no es parte del catalogo de DGRH";
	
	// agregar catalogo de Municpios

if($IdEstado == "01"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011");
} //fin de if($IdEstado == "01")

if($IdEstado == "02"){
	$Mpio = array("001","002","003","004","005");
} //fin de if($IdEstado == "02")

if($IdEstado == "03"){
	$Mpio = array("001","002","003","008","009");
} //fin de if($IdEstado == "03")

if($IdEstado == "04"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011");
} //fin de if($IdEstado == "04")

if($IdEstado == "05"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","023","024","025","026","027","028","029","030","031","032","033","034","035","036","037","038");
} //fin de if($IdEstado == "05")

if($IdEstado == "06"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010");
} //fin de if($IdEstado == "06")

if($IdEstado == "07"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","023","024","025","026","027","028","029","030","031","032","033","034","035","036","037","038","039","040","041","042","043","044","045","046","047","048","049","050","051","052","053","054","055","056","057","058","059","060","061","062","063","064","065","066","067","068","069","070","071","072","073","074","075","076","077","078","079","080","081","082","083","084","085","086","087","088","089","090","091","092","093","094","096","097","098","099","100","101","102","103","104","105","106","107","108","109","110","111","112","113","114","115","116","117","118","119");
} //fin de if($IdEstado == "07")

if($IdEstado == "08"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","023","024","025","026","027","028","029","030","031","032","033","034","035","036","037","038","039","040","041","042","043","044","045","046","047","048","049","050","051","052","053","054","055","056","057","058","059","060","061","062","063","064","065","066","067");
} //fin de if($IdEstado == "08")

if($IdEstado == "09"){
	$Mpio = array("002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017");
} //fin de if($IdEstado == "09")

if($IdEstado == "10"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","023","024","025","026","027","028","029","030","031","032","033","034","035","036","037","038","039");
} //fin de if($IdEstado == "10")

if($IdEstado == "11"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","023","024","025","026","027","028","029","030","031","032","033","034","035","036","037","038","039","040","041","042","043","044","045","046");
} //fin de if($IdEstado == "11")

if($IdEstado == "12"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","023","024","025","026","027","028","029","030","031","032","033","034","035","036","037","038","039","040","041","042","043","044","045","046","047","048","049","050","051","052","053","054","055","056","057","058","059","060","061","062","063","064","065","066","067","068","069","070","071","072","073","074","075","076","077","078","079","080","081");
} //fin de if($IdEstado == "12")

if($IdEstado == "13"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","023","024","025","026","027","028","029","030","031","032","033","034","035","036","037","038","039","040","041","042","043","044","045","046","047","048","049","050","051","052","053","054","055","056","057","058","059","060","061","062","063","064","065","066","067","068","069","070","071","072","073","074","075","076","077","078","079","080","081","082","083","084");
} //fin de if($IdEstado == "13")

if($IdEstado == "14"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","023","024","025","026","027","028","029","030","031","032","033","034","035","036","037","038","039","040","041","042","043","044","045","046","047","048","049","050","051","052","053","054","055","056","057","058","059","060","061","062","063","064","065","066","067","068","069","070","071","072","073","074","075","076","077","078","079","080","081","082","083","084","085","086","087","088","089","090","091","092","093","094","095","096","097","098","099","100","101","102","103","104","105","106","107","108","109","110","111","112","113","114","115","116","117","118","119","120","121","122","123","124","125");
} //fin de if($IdEstado == "14")

if($IdEstado == "15"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","023","024","025","026","027","028","029","030","031","032","033","034","035","036","037","038","039","040","041","042","043","044","045","046","047","048","049","050","051","052","053","054","055","056","057","058","059","060","061","062","063","064","065","066","067","068","069","070","071","072","073","074","075","076","077","078","079","080","081","082","083","084","085","086","087","088","089","090","091","092","093","094","095","096","097","098","099","100","101","102","103","104","105","106","107","108","109","110","111","112","113","114","115","116","117","118","119","120","121","122","123","124","125");
} //fin de if($IdEstado == "15")

if($IdEstado == "16"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","023","024","025","026","027","028","029","030","031","032","033","034","035","036","037","038","039","040","041","042","043","044","045","046","047","048","049","050","051","052","053","054","055","056","057","058","059","060","061","062","063","064","065","066","067","068","069","070","071","072","073","074","075","076","077","078","079","080","081","082","083","084","085","086","087","088","089","090","091","092","093","094","095","096","097","098","099","100","101","102","103","104","105","106","107","108","108","109","110","111","112","113");
} //fin de if($IdEstado == "16")

if($IdEstado == "17"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","023","024","025","026","027","028","029","030","031","032","033");
} //fin de if($IdEstado == "17")

if($IdEstado == "18"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020");
} //fin de if($IdEstado == "18")

if($IdEstado == "19"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","023","024","025","026","027","028","029","030","031","032","033","034","035","036","037","038","039","040","041","042","043","044","045","046","047","048","049","050","051");
} //fin de if($IdEstado == "19")

if($IdEstado == "20"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","023","024","025","026","027","028","029","030","031","032","033","034","035","036","037","038","039","040","041","042","043","044","045","046","047","048","049","050","051","052","053","054","055","056","057","058","059","060","061","062","063","064","065","066","067","068","069","070","071","072","073","074","075","076","077","078","079","080","081","082","083","084","085","086","087","088","089","090","091","092","093","094","095","096","097","098","099","100","101","102","103","104","105","106","107","108","109","110","111","112","113","114","115","116","117","118","119","120","121","122","123","124","125","126","127","128","129","130","131","132","133","134","135","136","137","138","139","140","141","142","143","144","145","146","147","148","149","150","151","152","153","154","155","156","157","158","159","160","161","162","163","164","165","166","167","168","169","170","171","172","173","174","175","176","177","178","179","180","181","182","183","184","185","186","187","188","189","190","191","192","193","194","195","196","197","198","199","200","201","202","203","204","205","206","207","208","209","210","211","212","213","214","215","216","217","218","219","220","221","222","223","224","225","226","227","228","229","230","231","232","233","234","235","236","237","238","239","240","241","242","243","244","245","246","247","248","249","250","251","252","253","254","255","256","257","258","259","260","261","262","263","264","265","266","267","268","269","270","271","272","273","274","275","276","277","278","279","280","281","282","283","284","285","286","287","288","289","290","291","292","293","294","295","296","297","298","299","300","301","302","303","304","305","306","307","308","309","310","311","312","313","314","315","316","317","318","319","320","321","322","323","324","325","326","327","328","329","330","331","332","333","334","335","336","337","338","339","340","341","342","343","344","345","346","347","348","349","350","351","352","353","354","355","356","357","358","359","360","361","362","363","364","365","366","367","368","369","370","371","372","373","374","375","376","377","378","379","380","381","382","383","384","385","386","387","388","389","390","391","392","393","394","395","396","397","398","399","400","401","402","403","404","405","406","407","408","409","410","411","412","413","414","415","416","417","418","419","420","421","422","423","424","425","426","427","428","429","430","431","432","433","434","435","436","437","438","439","440","441","442","443","444","445","446","447","448","449","450","451","452","453","454","455","456","457","458","459","460","461","462","463","464","465","466","467","468","469","470","471","472","473","474","475","476","477","478","479","480","481","482","483","484","485","486","487","488","489","490","491","492","493","494","495","496","497","498","499","500","501","502","503","504","505","506","507","508","509","510","511","512","513","514","515","516","517","518","519","520","521","522","523","524","525","526","527","528","529","530","531","532","533","534","535","536","537","538","539","540","541","542","543","544","545","546","547","548","549","550","551","552","553","554","555","556","557","558","559","560","561","562","563","564","565","566","567","568","569","570");
} //fin de if($IdEstado == "20")

if($IdEstado == "21"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","023","024","025","026","027","028","029","030","031","032","033","034","035","036","037","038","039","040","041","042","043","044","045","046","047","048","049","050","051","052","053","054","055","056","057","058","059","060","061","062","063","064","065","066","067","068","069","070","071","072","073","074","075","076","077","078","079","080","081","082","083","084","085","086","087","088","089","090","091","092","093","094","095","096","097","098","099","100","101","102","103","104","105","106","107","108","109","110","111","112","113","114","115","116","117","118","119","120","121","122","123","124","125","126","127","128","129","130","131","132","133","134","135","136","137","138","139","140","141","142","143","144","145","146","147","148","149","150","151","152","153","154","155","156","157","158","159","160","161","162","163","164","165","166","167","168","169","170","171","172","173","174","175","176","177","178","179","180","181","182","183","184","185","186","187","188","189","190","191","192","193","194","195","196","197","198","199","200","201","202","203","204","205","206","207","208","209","210","211","212","213","214","215","216","217");
} //fin de if($IdEstado == "21")

if($IdEstado == "22"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018");
} //fin de if($IdEstado == "22")

if($IdEstado == "23"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010");
} //fin de if($IdEstado == "23")

if($IdEstado == "24"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","023","024","025","026","027","028","029","030","031","032","033","034","035","036","037","038","039","040","041","042","043","044","045","046","047","048","049","050","051","052","053","054","055","056","057","058");
} //fin de if($IdEstado == "24")

if($IdEstado == "25"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018");
} //fin de if($IdEstado == "25")

if($IdEstado == "26"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","023","024","025","026","027","028","029","030","031","032","033","034","035","036","037","038","039","040","041","042","043","044","045","046","047","048","049","050","051","052","053","054","055","056","057","058","059","060","061","062","063","064","065","066","067","068","069","070","071","072");
} //fin de if($IdEstado == "26")

if($IdEstado == "27"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017");
} //fin de if($IdEstado == "27")

if($IdEstado == "28"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","023","024","025","026","027","028","029","030","031","032","033","034","035","036","037","038","039","040","041","042","043");
} //fin de if($IdEstado == "28")

if($IdEstado == "29"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","023","024","025","026","027","028","029","030","031","032","033","034","035","036","037","038","039","040","041","042","043","044","045","046","047","048","049","050","051","052","053","054","055","056","057","058","059","060");
} //fin de if($IdEstado == "29")

if($IdEstado == "30"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","023","024","025","026","027","028","029","030","031","032","033","034","035","036","037","038","039","040","041","042","043","044","045","046","047","048","049","050","051","052","053","054","055","056","057","058","059","060","061","062","063","064","065","066","067","068","069","070","071","072","073","074","075","076","077","078","079","080","081","082","083","084","085","086","087","088","089","090","091","092","093","094","095","096","097","098","099","100","101","102","103","104","105","106","107","108","109","110","111","112","113","114","115","116","117","118","119","120","121","122","123","124","125","126","127","128","129","130","131","132","133","134","135","136","137","138","139","140","141","142","143","144","145","146","147","148","149","150","151","152","153","154","155","156","157","158","159","160","161","162","163","164","165","166","167","168","169","170","171","172","173","174","175","176","177","178","179","180","181","182","183","184","185","186","187","188","189","190","191","192","193","194","195","196","197","198","199","200","201","202","203","204","205","206","207","208","209","210","211","212");
} //fin de if($IdEstado == "30")

if($IdEstado == "31"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","023","024","025","026","027","028","029","030","031","032","033","034","035","036","037","038","039","040","041","042","043","044","045","046","047","048","049","050","051","052","053","054","055","056","057","058","059","060","061","062","063","064","065","066","067","068","069","070","071","072","073","074","075","076","077","078","079","080","081","082","083","084","085","086","087","088","089","090","091","092","093","094","095","096","097","098","099","100","101","102","103","104","105","106");
} //fin de if($IdEstado == "31")

if($IdEstado == "32"){
	$Mpio = array("001","002","003","004","005","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","023","024","025","026","027","028","029","030","031","032","033","034","035","036","037","038","039","040","041","042","043","044","045","046","047","048","049","050","051","052","053","054","055","056","057","058");
} //fin de if($IdEstado == "32")




	$LocCampo =$Campo;
	if (strlen($LocCampo) == TRES)
	{
		if(!in_array($LocCampo,$Mpio))
		{
			$Error = $NumReg ."|".$DI_26."|".$LocCampo."|" . $DI_26_Mpio."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_26."|".$LocCampo."|" . $DI_26_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_26

/*************************************************************
* 
*  Funcion : fncValidaDI_27 
*  Objetivo: Validar el campo Centro de Responsabilidad

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_27($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_27           = "(27)Centro de Responsabilidad";
	$DI_27_ErrTam    = "Tamaño de campo Centro de Responsabilidad debe ser  a 10 Caracters";
	$DI_27_Edo    	 = "El Centro de Responsabilidad no corresponde al Estado";
	$DI_27_CR    	 = "El Centro de Responsabilidad no corresponde al catalogo de DGRH";
	
	// agregar catalogo de Municpios
    $Edo= array($IdEstado);

	$LocCampo =$Campo;
	if (strlen($LocCampo) == DIEZ)
	{
		if(!in_array(substr($LocCampo,0,2),$Edo))
		{
			$Error = $NumReg ."|".$DI_27."|".$LocCampo."|" . $DI_27_Edo."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
		if(!preg_match("/\d{8}/",substr($LocCampo,2,8)))
		{
			$Error = $NumReg ."|".$DI_27."|".$LocCampo."|" . $DI_27_CR."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_27."|".$LocCampo."|" . $DI_27_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_27


/*************************************************************
* 
*  Funcion : fncValidaDI_28 
*  Objetivo: Validar el campo Cédula de Identidad (NSS)

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_28($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_28           = "(28)Cédula de Identidad (NSS)";
	$DI_28_ErrTam    = "Tamaño de campo Cédula de Identidad (NSS) debe ser  a 11 Caracters";
	$DI_28_NSS    	 = "La Cédula de Identidad (NSS) no corresponde (80)";
	$DI_28_ISSSTE   	 = "La Cédula de Identidad (NSS) no corresponde al asignado pór ISSSTE";
	
	// agregar catalogo de Municpios
	$LocCampo =$Campo;
	if (strlen($LocCampo) == (DIEZ + UNO))
	{
		if(!(substr($LocCampo,0,2) == "80"))
		{
			$Error = $NumReg ."|".$DI_28."|".$LocCampo."|" . $DI_28_NSS."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
		if(!preg_match("/\d{9}/",substr($LocCampo,2,9)))
		{
			$Error = $NumReg ."|".$DI_28."|".$LocCampo."|" . $DI_28_ISSSTE."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_28."|".$LocCampo."|" . $DI_28_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_28

/*************************************************************
* 
*  Funcion : fncValidaDI_29 
*  Objetivo: Validar el campo Pagaduria

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_29($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_29           = "(29)Pagaduria";
	$DI_29_ErrTam    = "Tamaño de campo Pagaduria debe ser  a 5 Caracters";
	$DI_29_Pgria   	 = "Pagaduria no corresponde las reglas de negocio establecidas por DGRH";
	
	
	// agregar catalogo de Municpios
	$LocCampo =$Campo;
	if (strlen($LocCampo) == CINCO)
	{
		if(!preg_match("/[A-Za-z0-9]{5}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_29."|".$LocCampo."|" . $DI_29_Pgria."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_29."|".$LocCampo."|" . $DI_29_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_29

/*************************************************************
* 
*  Funcion : fncValidaDI_30 
*  Objetivo: Validar el campo Número de AHISA - Fuente de Financiamiento

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_30($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_30           = "(30)Número de AHISA-Fuente de Financiamiento";
	$DI_30_ErrTam    = "Tamaño de campo Número de AHISA-Fuente de Financiamiento debe ser de 2 Digítos";
	$DI_30_noDI   	 = "Número de AHISA - Fuente de Financiamiento no corresponde las reglas de negocio establecidas por DGRH";
	

	$LocCampo =$Campo;
	if (strlen($LocCampo) == DOS)
	{
		if(!preg_match("/[0-9]{2}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_30."|".$LocCampo."|" . $DI_30_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_30."|".$LocCampo."|" . $DI_30_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_30

/*************************************************************
* 
*  Funcion : fncValidaDI_31 
*  Objetivo: Validar el campo Tabulador de Puesto

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_31($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_31           = "(31)Tabulador de Puesto";
	$DI_31_ErrTam    = "Tamaño de campo Tabulador de Puesto debe ser de 3 Digítos";
	$DI_31_noDI   	 = "Tabulador de Puesto no corresponde las Directivas Institucionales  establecidas por DGRH";
	

	$LocCampo =$Campo;
	if (strlen($LocCampo) == TRES)
	{
		if(!preg_match("/[0-9]{3}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_31."|".$LocCampo."|" . $DI_31_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_31."|".$LocCampo."|" . $DI_31_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_31

/*************************************************************
* 
*  Funcion : fncValidaDI_32 
*  Objetivo: Validar el campo Nivel de puesto - NIVEL

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_32($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_32           = "(32)Nivel de puesto - NIVEL";
	$DI_32_ErrTam    = "Nivel de puesto - NIVEL debe ser de 2 Digítos";
	$DI_32_noDI   	 = "Nivel de puesto - NIVEL no corresponde las Directivas Institucionales  establecidas por DGRH";
	

	$LocCampo =$Campo;
	if (strlen($LocCampo) == DOS)
	{
		if(!preg_match("/[0-9]{2}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_32."|".$LocCampo."|" . $DI_32_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_32."|".$LocCampo."|" . $DI_32_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_32

/*************************************************************
* 
*  Funcion : fncValidaDI_33 
*  Objetivo: Validar el campo Rango

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_33($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_33           = "(33)Rango";
	$DI_33_ErrTam    = "Rango debe ser de 1 Digítos";
	$DI_33_noDI   	 = "Rango no corresponde las Directivas Institucionales  establecidas por DGRH (1,2,3)";
	

	$LocCampo =$Campo;
	if (strlen($LocCampo) == UNO)
	{
		if(!preg_match("/[0-9]{1}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_33."|".$LocCampo."|" . $DI_33_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_33."|".$LocCampo."|" . $DI_33_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_33


/*************************************************************
* 
*  Funcion : fncValidaDI_34
*  Objetivo: Validar el campo Indicador de Mando

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_34($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_34           = "(34)Indicador de Mando";
	$DI_34_ErrTam    = "Indicador de Mando debe ser de 2 Digítos";
	$DI_34_noDI   	 = "Indicador de Mando no corresponde al catalogo establecidas por DGRH";
	
	$IndMando = array("01","08","10","30","50","60","70","75","80","90");

	$LocCampo =$Campo;
	if (strlen($LocCampo) == DOS)
	{
		if(!in_array($LocCampo, $IndMando))
		{
			$Error = $NumReg ."|".$DI_34."|".$LocCampo."|" . $DI_34_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_34."|".$LocCampo."|" . $DI_34_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_34

/*************************************************************
* 
*  Funcion : fncValidaDI_35
*  Objetivo: Validar el campo Horario Asignado

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_35($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_35           = "(35)Horario Asignado";
	$DI_35_ErrTam    = "Horario Asignado debe ser de 1 Digítos";
	$DI_35_noDI   	 = "Horario Asignado no corresponde al catalogo establecidas por DGRH(1-8)";
	
	

	$LocCampo =$Campo;
	if (strlen($LocCampo) == UNO)
	{
		if(!preg_match("/[1-8]{1}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_35."|".$LocCampo."|" . $DI_35_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_35."|".$LocCampo."|" . $DI_35_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_35


/*************************************************************
* 
*  Funcion : fncValidaDI_37
*  Objetivo: Validar el campo Tipo de Trabajador

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_37($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_37           = "(37)Tipo de Trabajador";
	$DI_37_ErrTam    = "Tipo de Trabajador debe ser de 2 Digítos";
	$DI_37_noDI   	 = "Tipo de Trabajador no corresponde al catalogo establecidas por DGRH(01,11,20)";
	
	

	$LocCampo =$Campo;
	if (strlen($LocCampo) == DOS)
	{
		if(!preg_match("/[0-9]{2}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_37."|".$LocCampo."|" . $DI_37_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_37."|".$LocCampo."|" . $DI_37_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_37


/*************************************************************
* 
*  Funcion : fncValidaDI_38
*  Objetivo: Validar el campo Nivel de puesto - Nivel de puesto SPC

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_38($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_38           = "(38)Nivel de puesto - Nivel de puesto SPC";
	$DI_38_ErrTam    = "Nivel de puesto - Nivel de puesto SPC debe ser de 10 Digítos";
	$DI_38_noDI   	 = "Nivel de puesto - Nivel de puesto SPC no corresponde al catalogo establecidas por DGRH";
	$LocCampo =$Campo;
	if (strlen($LocCampo) == DIEZ)
	{
		if(!preg_match("/[0-9]{10}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_38."|".$LocCampo."|" . $DI_38_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_38."|".$LocCampo."|" . $DI_38_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_38

/*************************************************************
* 
*  Funcion : fncValidaDI_39
*  Objetivo: Validar el campo Indicador del Empleado - Estatus del Empleado

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_39($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_39           = "(39)Indicador del Empleado - Estatus del Empleado";
	$DI_39_ErrTam    = "Indicador del Empleado - Estatus del Empleado debe ser de 1 Digíto";
	$DI_39_noDI   	 = "Indicador del Empleado - Estatus del Empleado no corresponde al catalogo establecido por DGRH(0,1,4)";

	$IndEmpl = array("0","2","1","4","3");	
	$LocCampo =$Campo;
	if (strlen($LocCampo) == UNO)
	{
		if(!in_array($LocCampo, $IndEmpl))
		{
			$Error = $NumReg ."|".$DI_39."|".$LocCampo."|" . $DI_39_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_39."|".$LocCampo."|" . $DI_39_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_39


/*************************************************************
* 
*  Funcion : fncValidaDI_40
*  Objetivo: Validar el campo Fecha de Ingreso al Gobierno Federal

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_40($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_40           = "(40)Fecha de Ingreso al Gobierno Federal";
	$DI_40_ErrTam    = "Fecha de Ingreso al Gobierno Federal debe ser de 8 Digíto(AAAAMMDD (AAAA=año, MM=mes, DD=día))";
	$DI_40_noDI   	 = "Fecha de Ingreso al Gobierno Federal no corresponde al formato establecido por DGRH(AAAAMMDD (AAAA=año, MM=mes, DD=día))";

		
	$LocCampo =$Campo;
	if (strlen($LocCampo) == OCHO)
	{
		if(!validateDate($LocCampo))
		{
			$Error = $NumReg ."|".$DI_40."|".$LocCampo."|" . $DI_40_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_40."|".$LocCampo."|" . $DI_40_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_40

/*************************************************************
* 
*  Funcion : fncValidaDI_41
*  Objetivo: Validar el campo Fecha de Ingreso a la Secretaría de Salud

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_41($IdEstado, $GestorErr, $NumReg, $Campo, $Campo2)
{
	 
	$Bandera = CERO;

	$DI_41           = "(41)Fecha de Ingreso a la Secretaría de Salud";
	$DI_41_ErrTam    = "Fecha de Ingreso a la Secretaría de Salud debe ser de 8 Digíto(AAAAMMDD (AAAA=año, MM=mes, DD=día))";
	$DI_41_noDI   	 = "Fecha de Ingreso a la Secretaría de Salud no corresponde al formato establecido por DGRH(AAAAMMDD (AAAA=año, MM=mes, DD=día))";
	$DI_41_FecIng 	 = "Fecha de Ingreso a la Secretaría de Salud no puede ser menor a Fecha de Ingreso al Gobierno Federal";
		
	$LocCampo =$Campo;
	if (strlen($LocCampo) == OCHO)
	{
		if(!validateDate($LocCampo))
		{
			$Error = $NumReg ."|".$DI_41."|".$LocCampo."|" . $DI_41_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}
		if(validateDate($LocCampo) and validateDate($Campo2))	
		{
			$Fecha1 = date_create($Campo2);
			$Fecha2 = date_create($LocCampo);
			$interval = date_diff($Fecha1, $Fecha2);
			if(intval($interval->format('%R%a') )< CERO)
			{
					$Error = $NumReg ."|".$DI_41."|".$LocCampo."|" . $DI_41_FecIng."|\n";
					fwrite($GestorErr, $Error);
					$Bandera = UNO;
			}	
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_41."|".$LocCampo."|" . $DI_41_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_41

/*************************************************************
* 
*  Funcion : fncValidaDI_42
*  Objetivo: Validar el campo Fecha de Reingreso

*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_42($IdEstado, $GestorErr, $NumReg, $Campo, $Campo2)
{
	 
	$Bandera = CERO;

	$DI_42           = "(42)Fecha de Reingreso";
	$DI_42_ErrTam    = "Fecha de Reingreso debe ser de 8 Digíto(AAAAMMDD (AAAA=año, MM=mes, DD=día))";
	$DI_42_noDI   	 = "Fecha de Reingreso no corresponde al formato establecido por DGRH(AAAAMMDD (AAAA=año, MM=mes, DD=día))";
	$DI_42_FecIng 	 = "Fecha de Reingreso no puede ser menor a Fecha de Ingreso al Gobierno Federal";
		
	$LocCampo =$Campo;
	if (strlen($LocCampo) == OCHO)
	{
		if(!validateDate($LocCampo))
		{
			$Error = $NumReg ."|".$DI_42."|".$LocCampo."|" . $DI_42_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}
		if(validateDate($LocCampo) and validateDate($Campo2))	
		{
			$Fecha1 = date_create($Campo2);
			$Fecha2 = date_create($LocCampo);
			$interval = date_diff($Fecha1, $Fecha2);
			if(intval($interval->format('%R%a')) < CERO)
			{
					$Error = $NumReg ."|".$DI_42."|".$LocCampo."|" . $DI_42_FecIng."|\n";
					fwrite($GestorErr, $Error);
					$Bandera = UNO;
			}	
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_42."|".$LocCampo."|" . $DI_42_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_42

// campo 43 sin Directiva Institucional

/*************************************************************
* 
*  Funcion : fncValidaDI_44
*  Objetivo: Validar el campo Fecha de Pago
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 14-Mar-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_44($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DI_44           = "(44)Fecha de Pago";
	$DI_44_ErrTam    = "Fecha de Pago debe ser de 9 Caracteres(DDMMMAAAA (AAAA=año, MM=mes(primeras 3 letras), DD=día))";
	$DI_44_noDI   	 = "Fecha de Pago no corresponde al formato establecido por DGRH(DDMMMAAAA DD=día, MM=mes(primeras 3 letras), AAAA=año)";
	$DI_44_FecIng 	 = "Fecha de Pago no puede ser menor a Fecha de Ingreso al Gobierno Federal";
	$MesValido=array("ENE","FEB","MAR","ABR","MAY","JUN","JUL","AGO","SEP", "OCT","NOV","DIC");

	$LocCampo =$Campo;
	if (strlen($LocCampo) == NUEVE)
	{
		$Dia =substr($LocCampo,0,2);
		$Mes =substr($LocCampo,2,3);
		$Anio=substr($LocCampo,5,4);
		$Resultado = array_search(strtoupper($Mes), $MesValido);		
		if  (strlen($Resultado) <= 0)
		{
			$Error = $NumReg ."|".$DI_44."|".$LocCampo."|" . $DI_44_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;

		}	
		$Fecha =$Anio.str_pad(((int) $Resultado) +1,2,"0",STR_PAD_LEFT).$Dia;

		if(!validateDate($Fecha))
		{
			$Error = $NumReg ."|".$DI_44."|".$LocCampo."|" . $DI_44_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}
	}
	else
	{
		$Error = $NumReg ."|".$DI_44."|".$LocCampo."|" . $DI_44_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_44


// 30-May-2016

/*************************************************************
* 
*  Funcion : fncValidaDI_45
*  Objetivo: Validar el campo Periodo de Pago Inicial
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 30-May-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_45($IdEstado, $GestorErr, $NumReg, $Campo, $Campo2)
{
	 
	$Bandera = CERO;

	$DI_45           = "(45)Periodo de Pago Inicial";
	$DI_45_ErrTam    = "Periodo de Pago Inicial ser de 8 Caracteres AAAAMMDD (AAAA=año, MM=mes, DD=día)";
	$DI_45_noDI   	 = "Periodo de Pago Inicial no corresponde al formato establecido por DGRH(AAAAMMDD (AAAA=año, MM=mes, DD=día)";
	$DI_45_PerFinal 	 = "Periodo de Pago Inicial no puede ser posterior a Periodo de Pago Final";		
	
	$LocCampo =$Campo;
	if (strlen($LocCampo) == OCHO)
	{
		if(!validateDate($LocCampo))
		{
			$Error = $NumReg ."|".$DI_45."|".$LocCampo."|" . $DI_45_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}

		if(validateDate($LocCampo) and validateDate($Campo2))	
		{
			$Fecha1 = date_create($LocCampo);
			$Fecha2 = date_create($Campo2);
			$interval = date_diff($Fecha1, $Fecha2);
			if(intval($interval->format('%R%a') )< CERO)
			{
					$Error = $NumReg ."|".$DI_45."|".$LocCampo."|" . 
					$DI_45_PerFinal ."(" .$LocCampo." )(". $Campo2.")|\n";
					fwrite($GestorErr, $Error);
					$Bandera = UNO;
			}	
		}	

	}
	else
	{
		$Error = $NumReg ."|".$DI_45."|".$LocCampo."|" . $DI_45_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_45


/*************************************************************
* 
*  Funcion : fncValidaDI_46
*  Objetivo: Validar el campo Periodo de Pago Final
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 30-May-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_46($IdEstado, $GestorErr, $NumReg, $Campo, $Campo2)
{
	 
	$Bandera = CERO;

	$DI_46           = "(46)Periodo de Pago Final";
	$DI_46_ErrTam    = "Periodo de Pago Final ser de 8 Caracteres AAAAMMDD (AAAA=año, MM=mes, DD=día)";
	$DI_46_noDI   	 = "Periodo de Pago Final no corresponde al formato establecido por DGRH(AAAAMMDD (AAAA=año, MM=mes, DD=día)";
	$DI_46_PerFinal  = "El perido final no puede ser menor al Periodo Inicial";	
	
	$LocCampo =$Campo;
	if (strlen($LocCampo) == OCHO)
	{
		if(!validateDate($LocCampo))
		{
			$Error = $NumReg ."|".$DI_46."|".$LocCampo."|" . $DI_46_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}

		if(validateDate($LocCampo) and validateDate($Campo2))	
		{
			$Fecha1 = date_create($LocCampo);
			$Fecha2 = date_create($Campo2);
			$interval = date_diff($Fecha1, $Fecha2);
			if(intval($interval->format('%R%a') )> CERO)
			{
					$Error = $NumReg ."|".$DI_46."|".$LocCampo."|" . 
					$DI_46_PerFinal."(". $LocCampo . ")(". $Campo2 .")|\n";
					fwrite($GestorErr, $Error);
					$Bandera = UNO;
			}	
		}	

	}
	else
	{
		$Error = $NumReg ."|".$DI_46."|".$LocCampo."|" . $DI_46_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_46


/*************************************************************
* 
*  Funcion : fncValidaDI_47
*  Objetivo: Validar el campo Periodo de Aplicación Inicial
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 30-May-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_47($IdEstado, $GestorErr, $NumReg, $Campo, $Campo2)
{
	 
	$Bandera = CERO;

	$DI_47           = "(47)Periodo de Aplicación Inicial";
	$DI_47_ErrTam    = "Periodo de Aplicación Inicial ser de 8 Caracteres AAAAMMDD (AAAA=año, MM=mes, DD=día)";
	$DI_47_noDI   	 = "Periodo de Aplicación Inicial no corresponde al formato establecido por DGRH(AAAAMMDD (AAAA=año, MM=mes, DD=día)";
	$DI_47_PerAppIni 	 = "Periodo de Aplicación Inicial no puede ser posterior a Periodo de Aplicacion Final";		
	$DI_47_AppIni="No Corresponde a datos de Aplicacion Inicial (01 o 16)";
	$DI_47_PerAppAnioMes="Mes y Año no corresponder con la Directiva de Calidad Establecida por la DGRH";
	$LocCampo =$Campo;
	if (strlen($LocCampo) == OCHO)
	{
		if(!validateDate($LocCampo))
		{
			$Error = $NumReg ."|".$DI_47."|".$LocCampo."|" . $DI_47_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}

		if(validateDate($LocCampo) and validateDate($Campo2))	
		{
			$Fecha1 = date_create($LocCampo);
			$Fecha2 = date_create($Campo2);
			$interval = date_diff($Fecha1, $Fecha2);
			if(intval($interval->format('%R%a') )< CERO)
			{
					$Error = $NumReg ."|".$DI_47."|".$LocCampo."|" . 
					"$DI_47_PerFinal($LocCampo)($Campo2)" ."|\n";
					fwrite($GestorErr, $Error);
					$Bandera = UNO;
			}	
		}	
		$Dia =substr($LocCampo,6,2);
		if($Dia != "01" and $Dia != "16" )
		{
			$Error = $NumReg ."|".$DI_47."|".$LocCampo."|" . $DI_47_AppIni."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}
		if(substr($LocCampo,0,6) != substr($Campo2,0,6))
		{
			$Error = $NumReg ."|".$DI_47."|".$LocCampo."|" . 
			$DI_47_PerAppAnioMes ."(" . $LocCampo .")(". $Campo2.")|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}
	}
	else
	{
		$Error = $NumReg ."|".$DI_47."|".$LocCampo."|" . $DI_47_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_47


/*************************************************************
* 
*  Funcion : fncValidaDI_48
*  Objetivo: Validar el campo Periodo de Aplicación Final
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 30-May-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_48($IdEstado, $GestorErr, $NumReg, $Campo, $Campo2){
	 
	$Bandera = CERO;

	$DI_48           = "(48)Periodo de Aplicación Final";
	$DI_48_ErrTam    = "Periodo de Aplicación Final ser de 8 Caracteres AAAAMMDD (AAAA=año, MM=mes, DD=día)";
	$DI_48_noDI   	 = "Periodo de Aplicación Final no corresponde al formato establecido por DGRH(AAAAMMDD (AAAA=año, MM=mes, DD=día)";
	$DI_48_PerAppIni 	 = "Periodo de Aplicación Final no puede ser Anterior a Periodo de Aplicacion Inicial";		
	$DI_48_AppIni="No Corresponde a datos de Aplicacion Final (15/28/29/30/31)";
	$DI_48_PerAppAnioMes="Mes y Año no corresponder con la Directiva de Calidad Establecida por la DGRH";

	$LocCampo =$Campo;
	if (strlen($LocCampo) == OCHO){
		if(!validateDate($LocCampo)){
			$Error = $NumReg ."|".$DI_47."|".$LocCampo."|" . $DI_47_noDI."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}

		if(validateDate($LocCampo) and validateDate($Campo2)){
			$Fecha1 = date_create($LocCampo);
			$Fecha2 = date_create($Campo2);
			$interval = date_diff($Fecha1, $Fecha2);
			if(intval($interval->format('%R%a') )> CERO){
					$Error = $NumReg ."|".$DI_48."|".$LocCampo."|" . 
					$DI_48_PerFinal ."( " . $LocCampo. ")(". $Campo2 .")|\n";
					fwrite($GestorErr, $Error);
					$Bandera = UNO;
			}	
		}	

		$Dia =substr($LocCampo,6,2);
		if($Dia != "05" and $Dia != "30" ){
			$Error = $NumReg ."|".$DI_48."|".$LocCampo."|" . $DI_48_AppIni."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}

		if(substr($LocCampo,0,6) != substr($Campo2,0,6)){
			$Error = $NumReg ."|".$DI_48."|".$LocCampo."|" . 
								"$DI_48_PerAppAnioMes ($LocCampo)($Campo2)"."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}
	}
	else{
		$Error = $NumReg ."|".$DI_48."|".$LocCampo."|" . $DI_48_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_48


/*************************************************************
* 
*  Funcion : fncValidaDI_49
*  Objetivo: Validar el campo Quincena de Proceso Real
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 30-May-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_49($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;

	$DI_49           = "(49)Quincena de Proceso Real";
	$DI_49_ErrTam    = "Quincena de Proceso Real ser de 2 digitos";
	$DI_49_Qna   	 = "La quincena no corresponde a la Directiva de Calidad deifinida por la DGRH(01-24)";

	$LocCampo =$Campo;
	if (strlen($LocCampo) == DOS){

		if((int)$LocCampo <1 and (int)$LocCampo > 24){
			$Error = $NumReg ."|".$DI_49."|".$LocCampo."|" . $DI_49_Qna."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}

	}
	else{
		$Error = $NumReg ."|".$DI_49."|".$LocCampo."|" . $DI_49_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_49


/*************************************************************
* 
*  Funcion : fncValidaDI_50
*  Objetivo: Validar el campo Año de Proceso Real
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 30-May-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_50($IdEstado, $GestorErr, $NumReg, $Campo, $PerIni,$PerFin){
	 
	$Bandera = CERO;
	$DI_50           = "(50)Año de Proceso Real";
	$DI_50_ErrTam    = "Año de Proceso Real ser de 4 digitos";
	$DI_50_Anio   	 = "No se aceptan años posteriores a año de periodo de pago inicial y perido de pago final ";

	$LocCampo =$Campo;
	if (strlen($LocCampo) == CUATRO){
		if((int)$LocCampo > substr($PerIni,CERO,CUATRO) OR 
					(int)$LocCampo > substr($PerFin,CERO,CUATRO)){
			$Error = $NumReg ."|".$DI_50."|".$LocCampo."|" . $DI_50_Anio."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}
	}
	else{
		$Error = $NumReg ."|".$DI_50."|".$LocCampo."|" . $DI_50_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_50

/*************************************************************
* 
*  Funcion : fncValidaDI_51
*  Objetivo: Validar el campo Tipo de Pago
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 1-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_51($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_51           = "(51)Tipo de Pago";
	$DI_51_ErrTam    = "Tipo de Pago ser de 1 digitos";
	$DI_51_Catalogo    = "El valor no coincide con la directiva de calidad de la DGRH";
	
	$LocCampo =$Campo;
	if (strlen($LocCampo) == UNO){
		if(!preg_match("/[0-8]{1}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_51."|".$LocCampo."|" . $DI_51_Catalogo."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_51."|".$LocCampo."|" . $DI_51_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_51


/*************************************************************
* 
*  Funcion : fncValidaDI_53
*  Objetivo: Validar el campo Instrumento de Pago Nuevo
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 1-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_53($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_53             = "(53)Instrumento de Pago Nuevo";
	$DI_53_ErrTam      = "Instrumento de Pago Nuevo ser de 2 digitos";
	$DI_53_Catalogo    = "El valor de Instrumento de Pago Nuevo no coincide con la directiva de calidad de la DGRH";
	
	$LocCampo =$Campo;
	if (strlen($LocCampo) == DOS){
		if($LocCampo != "02" and $LocCampo != "05" )
		{
			$Error = $NumReg ."|".$DI_53."|".$LocCampo."|" . $DI_53_Catalogo."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_53."|".$LocCampo."|" . $DI_53_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_53


/*************************************************************
* 
*  Funcion : fncValidaDI_54
*  Objetivo: Validar el campo Percepciones 
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 1-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_54($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_54             = "(54)Percepciones ";
	$DI_54_ErrTam      = "Percepciones debe  ser de 10 digitos y 2 decimales";
	$DI_54_Catalogo    = "Percepciones no coincide con la directiva de calidad de la DGRH(9999999999.99)";
	
	$LocCampo =$Campo;
	if (strlen($LocCampo) == 11){
		if(!preg_match("/[0-9]{8}.[0-9]{2}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_54."|".$LocCampo."|" . $DI_54_Catalogo."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_54."|".$LocCampo."|" . $DI_54_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_54




/*************************************************************
* 
*  Funcion : fncValidaDI_55
*  Objetivo: Validar el campo Deducciones
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 1-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_55($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_55             = "(55)Deducciones ";
	$DI_55_ErrTam      = "Deducciones debe  ser de 10 digitos y 2 decimales ";
	$DI_55_Catalogo    = "Deducciones no coincide con la directiva de calidad de la DGRH(9999999999.99)";
	
	$LocCampo =$Campo;
	if (strlen($LocCampo) == 11){
		if(!preg_match("/[0-9]{8}.[0-9]{2}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_55."|".$LocCampo."|" . $DI_55_Catalogo."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_55."|".$LocCampo."|" . $DI_55_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_55

/*************************************************************
* 
*  Funcion : fncValidaDI_56
*  Objetivo: Validar el campo Neto
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 1-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_56($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_56           = "(56)Neto";
	$DI_56_ErrTam    = "Neto debe  ser de 10 digitos y 2 decimales ";
	$DI_56_Catalogo  = "Neto no coincide con la directiva de calidad de la DGRH(9999999999.99)";
	
	$LocCampo =$Campo;
	if (strlen($LocCampo) == 11){
		if(!preg_match("/[0-9]{8}.[0-9]{2}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_56."|".$LocCampo."|" . $DI_56_Catalogo."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_56."|".$LocCampo."|" . $DI_56_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_56

/*************************************************************
* 
*  Funcion : fncValidaDI_57
*  Objetivo: Validar el campo Número de Trailers-Total  de Conceptos
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 1-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_57($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_57           = "(57)Número de Trailers-Total  de Conceptos ";
	$DI_57_ErrTam    = "Número de Trailers-Total  de Conceptos debe  ser de 2 ";
	$DI_57_Catalogo  = "No coincide con directiva de Calidad (Numérico a 2 posiciones)";
	
	$LocCampo =$Campo;
	if (strlen($LocCampo) == DOS){
		if(!preg_match("/[0-9]{2}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_57."|".$LocCampo."|" . $DI_57_Catalogo."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_57."|".$LocCampo."|" . $DI_57_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_57


/*************************************************************
* 
*  Funcion : fncValidaDI_59
*  Objetivo: Validar el campo Nombre del Producto
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 1-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_59($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_58           = "(59)Nombre del Producto";
	$DI_58_ErrTam    = "Nombre del Producto debe  ser de 11 caracteres/numeros";
	$DI_58_Catalogo  = "No coincide con directiva de Calidad (Alfanumérico a 11)";
	
	$LocCampo =$Campo;
	if (strlen($LocCampo) == 11){
		if(!preg_match("/[A-Z,a-z,0-9]{11}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_58."|".$LocCampo."|" . $DI_58_Catalogo."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_58."|".$LocCampo."|" . $DI_58_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_59



/*************************************************************
* 
*  Funcion : fncValidaDI_59
*  Objetivo: Validar el campo Número de Control 
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 1-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_60($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_59           = "(60) Número de Control ";
	$DI_59_Catalogo  = "No coincide con directiva de Calidad (Numerico)";
	
	$LocCampo =$Campo;
	
	if(!preg_match("/[0-9]{6}/",$LocCampo))
	{
		$Error = $NumReg ."|".$DI_59."|".$LocCampo."|" . $DI_59_Catalogo."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}	
	return $Bandera;
} // fin de funcion fncValidaDI_60


/*************************************************************
* 
*  Funcion : fncValidaDI_61
*  Objetivo: Validar el campo Número de Cheque
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 1-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_61($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_60           = "(61)Número de Cheque";
	$DI_60_ErrTam    = "Número de Cheque debe  ser de 10 Digitos";
	$DI_60_Menor     = "Número de Cheque debe ser mayor a cero y numerico";
	$DI_60_Catalogo  = "No coincide con directiva de Calidad (Alfanumérico a 11)";

	
	$LocCampo =$Campo;
	if (strlen($LocCampo) == DIEZ){
		if($LocCampo <= CERO)
		{
			$Error = $NumReg ."|".$DI_60."|".$LocCampo."|" . $DI_60_Menor."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	

		if(!preg_match("/[0-9]{10}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_60."|".$LocCampo."|" . $DI_60_Catalogo."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_60."|".$LocCampo."|" . $DI_60_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_61


// no hay regla para el campo 62 Digito Verificador (Libre)


/*************************************************************
* 
*  Funcion : fncValidaDI_63 
*  Objetivo: Validar el campo Indicador de TESOFE-JORNADA
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 2-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_63($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_62           = "(63)Indicador de TESOFE -JORNADA";
	$DI_62_ErrTam    = "Indicador de TESOFE-JORNADA debe  ser de 2 Digitos";
	$DI_62_Catalogo  = "Indicador de TESOFE-JORNADA No coincide con catalogo definido por la DGRH";
	
	$JorArray =array("01","02","03","04","05");	

	$LocCampo = $Campo;
	if (strlen($LocCampo) == DOS){

		if(!in_array($LocCampo,$JorArray)){
			$Error = $NumReg ."|".$DI_62."|".$LocCampo."|" . $DI_62_Catalogo."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	

	}
	else{
		$Error = $NumReg ."|".$DI_62."|".$LocCampo."|" . $DI_62_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_63

/*************************************************************
* 
*  Funcion : fncValidaDI_65 
*  Objetivo: Validar el campo Ciclo del FONAC
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 2-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_65($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_64           = "(65)Ciclo del FONAC";
	$DI_64_ErrTam    = "Ciclo del FONAC debe  ser de 4 Digitos";
	$DI_64_DC  = "Ciclo del FONAC No coincide con la Directiva de Calidad definida por la DGRH(Numérico a 4 posiciones)";
	
	$LocCampo = $Campo;
	if (strlen($LocCampo) == CUATRO){


		if(!preg_match("/[0-9]{4}/",$LocCampo)){
			$Error = $NumReg ."|".$DI_64."|".$LocCampo."|" . $DI_64_DC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_64."|".$LocCampo."|" . $DI_64_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_65

/*************************************************************
* 
*  Funcion : fncValidaDI_66
*  Objetivo: Validar el campo Número de Aportaciones al FONAC
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 2-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_66($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_65           = "(66)Número de Aportaciones al FONAC";
	$DI_65_ErrTam    = "Número de Aportaciones al FONAC debe  ser de 2 Digitos";
	$DI_65_DC  = "Número de Aportaciones al FONAC No coincide con la Directiva de Calidad definida por la DGRH(Numérico a 2 posiciones)";
	$DI_65_Catalogo  = "Número de Aportaciones al FONAC No coincide el catalogo definido por la DGRH(01-24)";
	
	
	$LocCampo = $Campo;
	if (strlen($LocCampo) == DOS){
		if(!preg_match("/[0-9]{2}/",$LocCampo)){
			$Error = $NumReg ."|".$DI_65."|".$LocCampo."|" . $DI_65_DC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
		if($LocCampo < 1 or $LocCampo > 24 ){
			$Error = $NumReg ."|".$DI_65."|".$LocCampo."|" . $DI_65_Catalogo."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_65."|".$LocCampo."|" . $DI_65_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_66

/*************************************************************
* 
*  Funcion : fncValidaDI_67
*  Objetivo: Validar el campo Acumulado de FONAC
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 2-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_67($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_66           = "(67)Acumulado de FONAC";
	$DI_66_ErrTam    = "Acumulado de FONAC debe  ser de 10 Digitos";
	$DI_66_DC  = "Acumulado de FONAC No coincide con la Directiva de Calidad definida por la DGRH(##########.##)";
	$DI_65_Catalogo  = "Acumulado de FONAC No coincide el catalogo definido por la DGRH(01-24)";
	
	
	$LocCampo = $Campo;
	if (strlen($LocCampo) == DIEZ){
		if(!preg_match("/[0-9]{7}.[0-9]{2}/",$LocCampo)){
			$Error = $NumReg ."|".$DI_66."|".$LocCampo."|" . $DI_66_DC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_66."|".$LocCampo."|" . $DI_66_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_67


/*************************************************************
* 
*  Funcion : fncValidaDI_68
*  Objetivo: Validar el campo Licencia sin Goce de Sueldo / CLUES
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 2-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_69($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_68           = "(69)Licencia sin Goce de Sueldo / CLUES";
	$DI_68_ErrTam    = "Licencia sin Goce de Sueldo / CLUES  ser de 11 caracteres";
	$DI_68_DC  = "Licencia sin Goce de Sueldo / CLUES No coincide con la Directiva de Calidad definida por la DGRH";
	$DI_68_Catalogo  = "Licencia sin Goce de Sueldo / CLUES No coincide el catalogo definido por la DGRH";


//Condicion de estado-clues
if($IdEstado == "01"){
	$Clues = array("ASSSA000013","ASSSA000025","ASSSA000030","ASSSA000042","ASSSA000054","ASSSA000066","ASSSA000071","ASSSA000083","ASSSA000095","ASSSA000100","ASSSA000112","ASSSA000124","ASSSA000136","ASSSA000141","ASSSA000153","ASSSA000165","ASSSA000170","ASSSA000182","ASSSA000194","ASSSA000206","ASSSA000211","ASSSA000223","ASSSA000235","ASSSA000240","ASSSA000252","ASSSA000264","ASSSA000276","ASSSA000281","ASSSA000293","ASSSA000305","ASSSA000310","ASSSA000322","ASSSA000334","ASSSA000346","ASSSA000351","ASSSA000363","ASSSA000375","ASSSA000380","ASSSA000392","ASSSA000404","ASSSA000416","ASSSA000421","ASSSA000433","ASSSA000445","ASSSA000450","ASSSA000462","ASSSA000474","ASSSA000491","ASSSA000503","ASSSA000515","ASSSA000520","ASSSA000532","ASSSA000544","ASSSA000556","ASSSA000561","ASSSA000573","ASSSA000585","ASSSA000590","ASSSA000602","ASSSA000614","ASSSA000626","ASSSA000631","ASSSA000643","ASSSA000655","ASSSA000660","ASSSA000672","ASSSA000684","ASSSA000696","ASSSA000701","ASSSA000713","ASSSA000725","ASSSA000730","ASSSA000742","ASSSA000754","ASSSA000766","ASSSA000771","ASSSA000783","ASSSA000795","ASSSA000800","ASSSA000812","ASSSA000824","ASSSA000836","ASSSA000841","ASSSA000853","ASSSA000865","ASSSA000870","ASSSA000894","ASSSA000906","ASSSA000911","ASSSA000923","ASSSA000931","ASSSA000943","ASSSA000955","ASSSA000960","ASSSA000984","ASSSA000996","ASSSA001001","ASSSA001013","ASSSA001025","ASSSA001030","ASSSA001046","ASSSA001051","ASSSA001063","ASSSA001075","ASSSA001080","ASSSA001092","ASSSA001104","ASSSA001116","ASSSA001121","ASSSA001133","ASSSA001145","ASSSA001150","ASSSA001162","ASSSA001174","ASSSA001186","ASSSA001191","ASSSA001203","ASSSA001215","ASSSA001220","ASSSA001232","ASSSA001244");
} //fin de if($IdEstado == "01")

//Condicion de estado-clues
if($IdEstado == "02"){
	$Clues = array("BCSSA000015","BCSSA000020","BCSSA000032","BCSSA000044","BCSSA000061","BCSSA000073","BCSSA000085","BCSSA000090","BCSSA000102","BCSSA000114","BCSSA000126","BCSSA000131","BCSSA000143","BCSSA000160","BCSSA000172","BCSSA000184","BCSSA000196","BCSSA000201","BCSSA000213","BCSSA000225","BCSSA000230","BCSSA000242","BCSSA000254","BCSSA000266","BCSSA000271","BCSSA000283","BCSSA000295","BCSSA000300","BCSSA000312","BCSSA000324","BCSSA000341","BCSSA000353","BCSSA000370","BCSSA000382","BCSSA000406","BCSSA000411","BCSSA000423","BCSSA000440","BCSSA000452","BCSSA000464","BCSSA000476","BCSSA000481","BCSSA000493","BCSSA000505","BCSSA000510","BCSSA000522","BCSSA000534","BCSSA000546","BCSSA000551","BCSSA000563","BCSSA000575","BCSSA000580","BCSSA000592","BCSSA000604","BCSSA000616","BCSSA000621","BCSSA000633","BCSSA000645","BCSSA000650","BCSSA000662","BCSSA000674","BCSSA000686","BCSSA000691","BCSSA000703","BCSSA000715","BCSSA000720","BCSSA000732","BCSSA000744","BCSSA000756","BCSSA000761","BCSSA000773","BCSSA000785","BCSSA000790","BCSSA000814","BCSSA000831","BCSSA000843","BCSSA000855","BCSSA000860","BCSSA000872","BCSSA000884","BCSSA000896","BCSSA000901","BCSSA000913","BCSSA000925","BCSSA000930","BCSSA000942","BCSSA000954","BCSSA000966","BCSSA000971","BCSSA000983","BCSSA000995","BCSSA001000","BCSSA001012","BCSSA001041","BCSSA001053","BCSSA001065","BCSSA001070","BCSSA001082","BCSSA001094","BCSSA001106","BCSSA001111","BCSSA001123","BCSSA001135","BCSSA001140","BCSSA001152","BCSSA001164","BCSSA001176","BCSSA001181","BCSSA001193","BCSSA001205","BCSSA001210","BCSSA001222","BCSSA001234","BCSSA001246","BCSSA001251","BCSSA001263","BCSSA001275","BCSSA001280","BCSSA001292","BCSSA001316","BCSSA001321","BCSSA001333","BCSSA001345","BCSSA001350","BCSSA001362","BCSSA001374","BCSSA001386","BCSSA001403","BCSSA001415","BCSSA001420","BCSSA001444","BCSSA001456","BCSSA001461","BCSSA001473","BCSSA001485","BCSSA001490","BCSSA001502","BCSSA001514","BCSSA001526","BCSSA001531","BCSSA001543","BCSSA001555","BCSSA001560","BCSSA001572","BCSSA001584","BCSSA001630","BCSSA001666","BCSSA017462","BCSSA017504","BCSSA017521","BCSSA017533","BCSSA017545","BCSSA017550","BCSSA017574","BCSSA017585","BCSSA017590","BCSSA017602","BCSSA017614","BCSSA017626","BCSSA017631","BCSSA017643","BCSSA017660","BCSSA017672","BCSSA017684","BCSSA017696","BCSSA017701","BCSSA017713","BCSSA017725","BCSSA017730","BCSSA017742","BCSSA017754","BCSSA017766","BCSSA017771","BCSSA017783","BCSSA017795","BCSSA017800","BCSSA017812","BCSSA017824","BCSSA017836","BCSSA017841","BCSSA017853","BCSSA017865","BCSSA017870","BCSSA017882","BCSSA017894","BCSSA017906","BCSSA017911","BCSSA017923","BCSSA017935","BCSSA017940","BCSSA017952","BCSSA017964","BCSSA017976","BCSSA017981","BCSSA017993","BCSSA018005","BCSSA018010","BCSSA018022","BCSSA018034","BCSSA018046","BCSSA018051","BCSSA018063","BCSSA018075","BCSSA018080","BCSSA018092","BCSSA018104","BCSSA018116","BCSSA018121","BCSSA018133","BCSSA018145","BCSSA018150","BCSSA018162","BCSSA018174","BCSSA018186","BCSSA018191","BCSSA018203","BCSSA018215","BCSSA018220","BCSSA018232","BCSSA018244","BCSSA018256","BCSSA018261","BCSSA018273","BCSSA018285","BCSSA018290","BCSSA018302","BCSSA018314");
} //fin de if($IdEstado == "02")

//Condicion de estado-clues
if($IdEstado == "03"){
	$Clues = array("BSSSA000011","BSSSA000035","BSSSA000040","BSSSA000052","BSSSA000064","BSSSA000076","BSSSA000081","BSSSA000093","BSSSA000105","BSSSA000110","BSSSA000134","BSSSA000146","BSSSA000151","BSSSA000192","BSSSA000204","BSSSA000216","BSSSA000221","BSSSA000233","BSSSA000245","BSSSA000274","BSSSA000286","BSSSA000315","BSSSA000320","BSSSA000344","BSSSA000356","BSSSA000361","BSSSA000373","BSSSA000385","BSSSA000390","BSSSA000402","BSSSA000414","BSSSA000431","BSSSA000443","BSSSA000455","BSSSA000460","BSSSA000472","BSSSA000501","BSSSA000530","BSSSA000542","BSSSA000554","BSSSA000566","BSSSA000571","BSSSA000583","BSSSA000595","BSSSA000612","BSSSA000624","BSSSA000636","BSSSA000641","BSSSA000653","BSSSA000665","BSSSA000682","BSSSA000694","BSSSA000706","BSSSA000711","BSSSA000723","BSSSA000735","BSSSA000740","BSSSA000764","BSSSA000776","BSSSA000781","BSSSA000793","BSSSA000806","BSSSA000811","BSSSA000835","BSSSA000840","BSSSA000852","BSSSA000864","BSSSA000876","BSSSA000881","BSSSA000893","BSSSA000905","BSSSA000910","BSSSA000922","BSSSA000933","BSSSA000945","BSSSA000950","BSSSA000962","BSSSA000974","BSSSA001003","BSSSA001020","BSSSA001032","BSSSA001044","BSSSA001056","BSSSA001061","BSSSA001073","BSSSA001085","BSSSA001090","BSSSA001102","BSSSA001114","BSSSA001126","BSSSA001131","BSSSA001143","BSSSA001155","BSSSA001160","BSSSA001172","BSSSA001184","BSSSA001196","BSSSA001201","BSSSA001213","BSSSA001225","BSSSA001230","BSSSA001242","BSSSA001254","BSSSA001266","BSSSA001271","BSSSA001283","BSSSA001295","BSSSA001300","BSSSA001312");
} //fin de if($IdEstado == "03")

//Condicion de estado-clues
if($IdEstado == "04"){
	$Clues = array("CCSSA000025","CCSSA000030","CCSSA000054","CCSSA000066","CCSSA000071","CCSSA000083","CCSSA000095","CCSSA000100","CCSSA000124","CCSSA000141","CCSSA000264","CCSSA000276","CCSSA000281","CCSSA000293","CCSSA000305","CCSSA000310","CCSSA000322","CCSSA000334","CCSSA000346","CCSSA000363","CCSSA000375","CCSSA000380","CCSSA000392","CCSSA000404","CCSSA000416","CCSSA000421","CCSSA000433","CCSSA000445","CCSSA000450","CCSSA000462","CCSSA000474","CCSSA000486","CCSSA000491","CCSSA000503","CCSSA000515","CCSSA000532","CCSSA000544","CCSSA000556","CCSSA000561","CCSSA000573","CCSSA000585","CCSSA000590","CCSSA000602","CCSSA000614","CCSSA000626","CCSSA000631","CCSSA000643","CCSSA000655","CCSSA000660","CCSSA000672","CCSSA000684","CCSSA000696","CCSSA000701","CCSSA000713","CCSSA000725","CCSSA000730","CCSSA000742","CCSSA000754","CCSSA000766","CCSSA000771","CCSSA000783","CCSSA000795","CCSSA000800","CCSSA000812","CCSSA000824","CCSSA000865","CCSSA000870","CCSSA000882","CCSSA000894","CCSSA000906","CCSSA000911","CCSSA000923","CCSSA000940","CCSSA000952","CCSSA000976","CCSSA000981","CCSSA000993","CCSSA001005","CCSSA001010","CCSSA001022","CCSSA001034","CCSSA001051","CCSSA001063","CCSSA001075","CCSSA001080","CCSSA001092","CCSSA001104","CCSSA001203","CCSSA001220","CCSSA001232","CCSSA001244","CCSSA001256","CCSSA001261","CCSSA001273","CCSSA001285","CCSSA001290","CCSSA001302","CCSSA001314","CCSSA001326","CCSSA001331","CCSSA001343","CCSSA001360","CCSSA001372","CCSSA001384","CCSSA001396","CCSSA001401","CCSSA001413","CCSSA001425","CCSSA001430","CCSSA001454","CCSSA001466","CCSSA001471","CCSSA001483","CCSSA001495","CCSSA001500","CCSSA001512","CCSSA001524","CCSSA001536","CCSSA001541","CCSSA001553","CCSSA017280","CCSSA017292","CCSSA017304","CCSSA017316","CCSSA017321","CCSSA017333","CCSSA017345","CCSSA017350","CCSSA017362","CCSSA017374","CCSSA017386","CCSSA017391","CCSSA017403","CCSSA017426","CCSSA017431","CCSSA017443","CCSSA017455","CCSSA017460","CCSSA017472","CCSSA017496","CCSSA017501","CCSSA017513","CCSSA017525","CCSSA017530","CCSSA017554","CCSSA017566","CCSSA017571","CCSSA017583","CCSSA017595","CCSSA017600","CCSSA017624","CCSSA017636","CCSSA017641","CCSSA017653","CCSSA017665","CCSSA017670","CCSSA017682","CCSSA017694","CCSSA017706");
} //fin de if($IdEstado == "04")

//Condicion de estado-clues
if($IdEstado == "05"){
	$Clues = array("CLSSA000016","CLSSA000021","CLSSA000033","CLSSA000045","CLSSA000050","CLSSA000062","CLSSA000074","CLSSA000086","CLSSA000091","CLSSA000103","CLSSA000115","CLSSA000120","CLSSA000132","CLSSA000144","CLSSA000156","CLSSA000161","CLSSA000173","CLSSA000185","CLSSA000190","CLSSA000202","CLSSA000214","CLSSA000226","CLSSA000231","CLSSA000243","CLSSA000255","CLSSA000260","CLSSA000272","CLSSA000284","CLSSA000296","CLSSA000301","CLSSA000313","CLSSA000325","CLSSA000330","CLSSA000342","CLSSA000354","CLSSA000366","CLSSA000371","CLSSA000383","CLSSA000395","CLSSA000400","CLSSA000412","CLSSA000424","CLSSA000436","CLSSA000441","CLSSA000453","CLSSA000465","CLSSA000470","CLSSA000482","CLSSA000494","CLSSA000506","CLSSA000511","CLSSA000523","CLSSA000535","CLSSA000540","CLSSA000552","CLSSA000564","CLSSA000576","CLSSA000581","CLSSA000593","CLSSA000605","CLSSA000610","CLSSA000622","CLSSA000634","CLSSA000646","CLSSA000651","CLSSA000663","CLSSA000675","CLSSA000680","CLSSA000692","CLSSA000704","CLSSA000716","CLSSA000721","CLSSA000733","CLSSA000745","CLSSA000750","CLSSA000762","CLSSA000774","CLSSA000786","CLSSA000803","CLSSA000815","CLSSA000820","CLSSA000844","CLSSA000856","CLSSA000861","CLSSA000873","CLSSA000885","CLSSA000890","CLSSA000902","CLSSA000914","CLSSA000926","CLSSA000931","CLSSA000960","CLSSA000972","CLSSA000984","CLSSA000996","CLSSA001001","CLSSA001013","CLSSA001025","CLSSA001030","CLSSA001042","CLSSA001054","CLSSA001066","CLSSA001071","CLSSA001100","CLSSA001112","CLSSA001124","CLSSA001136","CLSSA001141","CLSSA001153","CLSSA001170","CLSSA001182","CLSSA001206","CLSSA001211","CLSSA001223","CLSSA001235","CLSSA001240","CLSSA001252","CLSSA001264","CLSSA001276","CLSSA001281","CLSSA001293","CLSSA001305","CLSSA001310","CLSSA001322","CLSSA001334","CLSSA001346","CLSSA001351","CLSSA001363","CLSSA001375","CLSSA001380","CLSSA001392","CLSSA001404","CLSSA001416","CLSSA001421","CLSSA001433","CLSSA001445","CLSSA001450","CLSSA001462","CLSSA001474","CLSSA001486","CLSSA001491","CLSSA001503","CLSSA001515","CLSSA001520","CLSSA001532","CLSSA001544","CLSSA001556","CLSSA001561","CLSSA001573","CLSSA001585","CLSSA001590","CLSSA001602","CLSSA001614","CLSSA001626","CLSSA001631","CLSSA001643","CLSSA001655","CLSSA001660","CLSSA001672","CLSSA001684","CLSSA001696","CLSSA001701","CLSSA001713","CLSSA001725","CLSSA001730","CLSSA001742","CLSSA001754","CLSSA001766","CLSSA001771","CLSSA001795","CLSSA001800","CLSSA001812","CLSSA001824","CLSSA001836","CLSSA001841","CLSSA001853","CLSSA001865","CLSSA001882","CLSSA001894","CLSSA001906","CLSSA001923","CLSSA001935","CLSSA001940","CLSSA001952","CLSSA001964","CLSSA001970","CLSSA001982","CLSSA001994","CLSSA002006","CLSSA002011","CLSSA002023","CLSSA002035","CLSSA002040","CLSSA002064","CLSSA002076","CLSSA002093","CLSSA002105","CLSSA002122","CLSSA002134","CLSSA002146","CLSSA002175","CLSSA002180","CLSSA002192","CLSSA002203","CLSSA002215","CLSSA002220","CLSSA002232","CLSSA002244","CLSSA002256","CLSSA002261","CLSSA002273","CLSSA002285","CLSSA002290","CLSSA002302","CLSSA002314","CLSSA002331","CLSSA002343","CLSSA002355","CLSSA002360","CLSSA002401","CLSSA002413","CLSSA002425","CLSSA002430","CLSSA002442","CLSSA002454","CLSSA002466","CLSSA002471","CLSSA002483","CLSSA002495","CLSSA002500","CLSSA002512","CLSSA002524","CLSSA002536","CLSSA002553","CLSSA002570","CLSSA002582","CLSSA002594","CLSSA002606","CLSSA002611","CLSSA002640","CLSSA002710","CLSSA002722","CLSSA002734","CLSSA002746","CLSSA002751","CLSSA002763","CLSSA002780","CLSSA002804","CLSSA002816","CLSSA002821","CLSSA002833","CLSSA002845","CLSSA002850");
} //fin de if($IdEstado == "05")

//Condicion de estado-clues
if($IdEstado == "06"){
	$Clues = array("CMSSA000014","CMSSA000026","CMSSA000031","CMSSA000043","CMSSA000055","CMSSA000060","CMSSA000072","CMSSA000084","CMSSA000096","CMSSA000101","CMSSA000113","CMSSA000125","CMSSA000142","CMSSA000154","CMSSA000166","CMSSA000171","CMSSA000183","CMSSA000195","CMSSA000212","CMSSA000224","CMSSA000236","CMSSA000241","CMSSA000253","CMSSA000265","CMSSA000270","CMSSA000282","CMSSA000294","CMSSA000306","CMSSA000311","CMSSA000323","CMSSA000335","CMSSA000340","CMSSA000352","CMSSA000364","CMSSA000376","CMSSA000381","CMSSA000393","CMSSA000410","CMSSA000422","CMSSA000434","CMSSA000446","CMSSA000451","CMSSA000463","CMSSA000475","CMSSA000480","CMSSA000492","CMSSA000504","CMSSA000516","CMSSA000521","CMSSA000533","CMSSA000545","CMSSA000550","CMSSA000562","CMSSA000574","CMSSA000586","CMSSA000591","CMSSA000603","CMSSA000615","CMSSA000620","CMSSA000632","CMSSA000656","CMSSA000661","CMSSA000673","CMSSA000685","CMSSA000690","CMSSA000702","CMSSA000714","CMSSA000726","CMSSA000743","CMSSA000755","CMSSA000760","CMSSA000772","CMSSA000784","CMSSA000796","CMSSA000801","CMSSA000813","CMSSA000825","CMSSA000830","CMSSA000842","CMSSA000854","CMSSA000866","CMSSA000871","CMSSA000883","CMSSA000895","CMSSA000900","CMSSA000912","CMSSA000924","CMSSA000936","CMSSA000941","CMSSA000953","CMSSA000965","CMSSA000970","CMSSA000982","CMSSA000994","CMSSA001006","CMSSA001011","CMSSA001023","CMSSA001035","CMSSA001040","CMSSA001052","CMSSA001064","CMSSA001076","CMSSA001081","CMSSA001093","CMSSA001105","CMSSA001110","CMSSA001122","CMSSA001134","CMSSA001146","CMSSA001151","CMSSA001163","CMSSA001175","CMSSA001180","CMSSA001192","CMSSA001204","CMSSA001216","CMSSA001221","CMSSA001233","CMSSA001245","CMSSA001250","CMSSA001262","CMSSA001274","CMSSA001286","CMSSA001291","CMSSA001303","CMSSA001315","CMSSA001320","CMSSA001344","CMSSA001356","CMSSA010433","CMSSA010445","CMSSA010450","CMSSA010462","CMSSA010474","CMSSA010486","CMSSA010491","CMSSA010503","CMSSA010515","CMSSA010520","CMSSA010532","CMSSA010543","CMSSA010555","CMSSA010712","CMSSA010724","CMSSA010736","CMSSA010741","CMSSA010753","CMSSA010765","CMSSA010770","CMSSA010782","CMSSA010794","CMSSA010806","CMSSA010811","CMSSA010823","CMSSA010835","CMSSA010840","CMSSA010852","CMSSA010864","CMSSA010876","CMSSA010881","CMSSA010893","CMSSA010905","CMSSA010910","CMSSA010922","CMSSA010934","CMSSA010946","CMSSA010951","CMSSA010963","CMSSA010975","CMSSA010980","CMSSA010992","CMSSA011004","CMSSA011016","CMSSA011021");
} //fin de if($IdEstado == "06")

//Condicion de estado-clues
if($IdEstado == "07"){
	$Clues = array("CSSSA000016","CSSSA000021","CSSSA000033","CSSSA000045","CSSSA000050","CSSSA000062","CSSSA000074","CSSSA000086","CSSSA000091","CSSSA000103","CSSSA000120","CSSSA000132","CSSSA000144","CSSSA000156","CSSSA000161","CSSSA000173","CSSSA000185","CSSSA000190","CSSSA000202","CSSSA000214","CSSSA000226","CSSSA000243","CSSSA000255","CSSSA000260","CSSSA000272","CSSSA000284","CSSSA000301","CSSSA000313","CSSSA000325","CSSSA000342","CSSSA000354","CSSSA000366","CSSSA000371","CSSSA000383","CSSSA000395","CSSSA000400","CSSSA000412","CSSSA000424","CSSSA000436","CSSSA000441","CSSSA000453","CSSSA000465","CSSSA000470","CSSSA000482","CSSSA000494","CSSSA000506","CSSSA000511","CSSSA000523","CSSSA000535","CSSSA000540","CSSSA000552","CSSSA000564","CSSSA000576","CSSSA000581","CSSSA000593","CSSSA000605","CSSSA000610","CSSSA000622","CSSSA000634","CSSSA000646","CSSSA000651","CSSSA000663","CSSSA000675","CSSSA000680","CSSSA000692","CSSSA000704","CSSSA000716","CSSSA000733","CSSSA000745","CSSSA000750","CSSSA000762","CSSSA000774","CSSSA000786","CSSSA000791","CSSSA000803","CSSSA000815","CSSSA000820","CSSSA000832","CSSSA000844","CSSSA000856","CSSSA000861","CSSSA000885","CSSSA000890","CSSSA000902","CSSSA000914","CSSSA000926","CSSSA000931","CSSSA000943","CSSSA000955","CSSSA000972","CSSSA000996","CSSSA001001","CSSSA001013","CSSSA001025","CSSSA001030","CSSSA001042","CSSSA001054","CSSSA001066","CSSSA001071","CSSSA001083","CSSSA001095","CSSSA001100","CSSSA001112","CSSSA001124","CSSSA001136","CSSSA001141","CSSSA001165","CSSSA001170","CSSSA001182","CSSSA001194","CSSSA001206","CSSSA001211","CSSSA001223","CSSSA001235","CSSSA001240","CSSSA001252","CSSSA001264","CSSSA001276","CSSSA001281","CSSSA001293","CSSSA001305","CSSSA001322","CSSSA001334","CSSSA001346","CSSSA001351","CSSSA001363","CSSSA001375","CSSSA001380","CSSSA001392","CSSSA001404","CSSSA001421","CSSSA001433","CSSSA001445","CSSSA001450","CSSSA001462","CSSSA001474","CSSSA001491","CSSSA001503","CSSSA001515","CSSSA001520","CSSSA001532","CSSSA001556","CSSSA001561","CSSSA001573","CSSSA001585","CSSSA001602","CSSSA001614","CSSSA001626","CSSSA001631","CSSSA001643","CSSSA001655","CSSSA001660","CSSSA001672","CSSSA001684","CSSSA001696","CSSSA001701","CSSSA001725","CSSSA001730","CSSSA001742","CSSSA001754","CSSSA001766","CSSSA001771","CSSSA001783","CSSSA001795","CSSSA001800","CSSSA001812","CSSSA001824","CSSSA001836","CSSSA001841","CSSSA001894","CSSSA001906","CSSSA001911","CSSSA001923","CSSSA001940","CSSSA001952","CSSSA001976","CSSSA002005","CSSSA002010","CSSSA002080","CSSSA002104","CSSSA002121","CSSSA002145","CSSSA002162","CSSSA002203","CSSSA002215","CSSSA002220","CSSSA002232","CSSSA002244","CSSSA002256","CSSSA002261","CSSSA002273","CSSSA002290","CSSSA002314","CSSSA002326","CSSSA002331","CSSSA002343","CSSSA002355","CSSSA002360","CSSSA002372","CSSSA002384","CSSSA002396","CSSSA002401","CSSSA002413","CSSSA002425","CSSSA002430","CSSSA002442","CSSSA002454","CSSSA002466","CSSSA002483","CSSSA002495","CSSSA002500","CSSSA002512","CSSSA002524","CSSSA002541","CSSSA002553","CSSSA002565","CSSSA002570","CSSSA002582","CSSSA002594","CSSSA002611","CSSSA002623","CSSSA002635","CSSSA002640","CSSSA002652","CSSSA002664","CSSSA002676","CSSSA002681","CSSSA002693","CSSSA002705","CSSSA002710","CSSSA002722","CSSSA002734","CSSSA002746","CSSSA002763","CSSSA002775","CSSSA002780","CSSSA002792","CSSSA002816","CSSSA002821","CSSSA002833","CSSSA002845","CSSSA002850","CSSSA002862","CSSSA002874","CSSSA002886","CSSSA002891","CSSSA002903","CSSSA002920","CSSSA002932","CSSSA002944","CSSSA002956","CSSSA002961","CSSSA002973","CSSSA002985","CSSSA002990","CSSSA003002","CSSSA003026","CSSSA003031","CSSSA003043","CSSSA003055","CSSSA003060","CSSSA003084","CSSSA003096","CSSSA003101","CSSSA003113","CSSSA003125","CSSSA003130","CSSSA003142","CSSSA003166","CSSSA003171","CSSSA003183","CSSSA003195","CSSSA003200","CSSSA003212","CSSSA003224","CSSSA003236","CSSSA003241","CSSSA003253","CSSSA003265","CSSSA003270","CSSSA003294","CSSSA003306","CSSSA003311","CSSSA003323","CSSSA003340","CSSSA003352","CSSSA003364","CSSSA003376","CSSSA003381","CSSSA003393","CSSSA003405","CSSSA003410","CSSSA003422","CSSSA003434","CSSSA003451","CSSSA003475","CSSSA003480","CSSSA003492","CSSSA003504","CSSSA003516","CSSSA003521","CSSSA003533","CSSSA003545","CSSSA003550","CSSSA003562","CSSSA003574","CSSSA003586","CSSSA003591","CSSSA003603","CSSSA003615","CSSSA003620","CSSSA003644","CSSSA003656","CSSSA003661","CSSSA003673","CSSSA003685","CSSSA003690","CSSSA003702","CSSSA003714","CSSSA003726","CSSSA003731","CSSSA003743","CSSSA003755","CSSSA003760","CSSSA003772","CSSSA003784","CSSSA003796","CSSSA003801","CSSSA003813","CSSSA003825","CSSSA003830","CSSSA003842","CSSSA003854","CSSSA003866","CSSSA003883","CSSSA003895","CSSSA003900","CSSSA003912","CSSSA003936","CSSSA003941","CSSSA003953","CSSSA003965","CSSSA003970","CSSSA003982","CSSSA003994","CSSSA004006","CSSSA004011","CSSSA004023","CSSSA004035","CSSSA004040","CSSSA004052","CSSSA004064","CSSSA004076","CSSSA004081","CSSSA004093","CSSSA004105","CSSSA004110","CSSSA004122","CSSSA004134","CSSSA004146","CSSSA004151","CSSSA004163","CSSSA004175","CSSSA004180","CSSSA004192","CSSSA004204","CSSSA004216","CSSSA004221","CSSSA004233","CSSSA004245","CSSSA004250","CSSSA004262","CSSSA004274","CSSSA004286","CSSSA004291","CSSSA004303","CSSSA004320","CSSSA004332","CSSSA004344","CSSSA004356","CSSSA004361","CSSSA004373","CSSSA004385","CSSSA004390","CSSSA004402","CSSSA004426","CSSSA004431","CSSSA004443","CSSSA004455","CSSSA004460","CSSSA004472","CSSSA004484","CSSSA004496","CSSSA004501","CSSSA004513","CSSSA004525","CSSSA004530","CSSSA004542","CSSSA004566","CSSSA004571","CSSSA004583","CSSSA004595","CSSSA004600","CSSSA004612","CSSSA004624","CSSSA004636","CSSSA004641","CSSSA004653","CSSSA004665","CSSSA004670","CSSSA004682","CSSSA004694","CSSSA004711","CSSSA004723","CSSSA004735","CSSSA004740","CSSSA004764","CSSSA004776","CSSSA004781","CSSSA004793","CSSSA004805","CSSSA004810","CSSSA004822","CSSSA004834","CSSSA004846","CSSSA004851","CSSSA004863","CSSSA004875","CSSSA004880","CSSSA004904","CSSSA004916","CSSSA004945","CSSSA004950","CSSSA004962","CSSSA004986","CSSSA004991","CSSSA005003","CSSSA005015","CSSSA005020","CSSSA005032","CSSSA005044","CSSSA005056","CSSSA005061","CSSSA005073","CSSSA005085","CSSSA005090","CSSSA005102","CSSSA005114","CSSSA005126","CSSSA005131","CSSSA005143","CSSSA005155","CSSSA005160","CSSSA005172","CSSSA005184","CSSSA005196","CSSSA005201","CSSSA005213","CSSSA005225","CSSSA005230","CSSSA005242","CSSSA005254","CSSSA005266","CSSSA005271","CSSSA005283","CSSSA005295","CSSSA005300","CSSSA005312","CSSSA005324","CSSSA005336","CSSSA005341","CSSSA005353","CSSSA005370","CSSSA005382","CSSSA005394","CSSSA005406","CSSSA005411","CSSSA005423","CSSSA005435","CSSSA005440","CSSSA005452","CSSSA005464","CSSSA005481","CSSSA005493","CSSSA005505","CSSSA005510","CSSSA005522","CSSSA005534","CSSSA005546","CSSSA005551","CSSSA005563","CSSSA005575","CSSSA005580","CSSSA005592","CSSSA005604","CSSSA005616","CSSSA005621","CSSSA005633","CSSSA005645","CSSSA005650","CSSSA005662","CSSSA005674","CSSSA005686","CSSSA005691","CSSSA005715","CSSSA005720","CSSSA005732","CSSSA005744","CSSSA005756","CSSSA005761","CSSSA005773","CSSSA005785","CSSSA005790","CSSSA005802","CSSSA005814","CSSSA005826","CSSSA005831","CSSSA005843","CSSSA005855","CSSSA005860","CSSSA005872","CSSSA005884","CSSSA005896","CSSSA005901","CSSSA005913","CSSSA005925","CSSSA005930","CSSSA005942","CSSSA005954","CSSSA005966","CSSSA005971","CSSSA005983","CSSSA005995","CSSSA006000","CSSSA006012","CSSSA006024","CSSSA006036","CSSSA006041","CSSSA006053","CSSSA006065","CSSSA006070","CSSSA006082","CSSSA006094","CSSSA006106","CSSSA006111","CSSSA006135","CSSSA006140","CSSSA006152","CSSSA006164","CSSSA006176","CSSSA006181","CSSSA006205","CSSSA006210","CSSSA006222","CSSSA006234","CSSSA006263","CSSSA006275","CSSSA006280","CSSSA006292","CSSSA006304","CSSSA006316","CSSSA006321","CSSSA006333","CSSSA006345","CSSSA006350","CSSSA006362","CSSSA006374","CSSSA006386","CSSSA006391","CSSSA006403","CSSSA006415","CSSSA006420","CSSSA006432","CSSSA006444","CSSSA006456","CSSSA006461","CSSSA006473","CSSSA006485","CSSSA006490","CSSSA006502","CSSSA006514","CSSSA006526","CSSSA006531","CSSSA006543","CSSSA006555","CSSSA006560","CSSSA006572","CSSSA006584","CSSSA006596","CSSSA006601","CSSSA006613","CSSSA006625","CSSSA006630","CSSSA006642","CSSSA006654","CSSSA006666","CSSSA006683","CSSSA006695","CSSSA006700","CSSSA006712","CSSSA006724","CSSSA006736","CSSSA006741","CSSSA006753","CSSSA006765","CSSSA006770","CSSSA006782","CSSSA006794","CSSSA006806","CSSSA006811","CSSSA006823","CSSSA006835","CSSSA006840","CSSSA006852","CSSSA006864","CSSSA006876","CSSSA006881","CSSSA006893","CSSSA006905","CSSSA006910","CSSSA006922","CSSSA006934","CSSSA006946","CSSSA006951","CSSSA006963","CSSSA006975","CSSSA006980","CSSSA006992","CSSSA007004","CSSSA007016","CSSSA007021","CSSSA007033","CSSSA007045","CSSSA007050","CSSSA007062","CSSSA007074","CSSSA007086","CSSSA007091","CSSSA007103","CSSSA007115","CSSSA007120","CSSSA007132","CSSSA007144","CSSSA007156","CSSSA007161","CSSSA007173","CSSSA007185","CSSSA007190","CSSSA007202","CSSSA007214","CSSSA007226","CSSSA007231","CSSSA007243","CSSSA007255","CSSSA007260","CSSSA007284","CSSSA007296","CSSSA007301","CSSSA007313","CSSSA007325","CSSSA007330","CSSSA007342","CSSSA007354","CSSSA007366","CSSSA007371","CSSSA007383","CSSSA007395","CSSSA007400","CSSSA007412","CSSSA007424","CSSSA007436","CSSSA007453","CSSSA007465","CSSSA007470","CSSSA007494","CSSSA007506","CSSSA007511","CSSSA007523","CSSSA007535","CSSSA007540","CSSSA007552","CSSSA007564","CSSSA007576","CSSSA007581","CSSSA007593","CSSSA007605","CSSSA007610","CSSSA007622","CSSSA007634","CSSSA007646","CSSSA007651","CSSSA007663","CSSSA007675","CSSSA007680","CSSSA007692","CSSSA007704","CSSSA007716","CSSSA007721","CSSSA007733","CSSSA007745","CSSSA007750","CSSSA007762","CSSSA007786","CSSSA007791","CSSSA007803","CSSSA007815","CSSSA007820","CSSSA007832","CSSSA007844","CSSSA007861","CSSSA007885","CSSSA007890","CSSSA007902","CSSSA007914","CSSSA007926","CSSSA007931","CSSSA007943","CSSSA007955","CSSSA007960","CSSSA007972","CSSSA007984","CSSSA007996","CSSSA008001","CSSSA008013","CSSSA008025","CSSSA008030","CSSSA008042","CSSSA008066","CSSSA008071","CSSSA008083","CSSSA008095","CSSSA008100","CSSSA008112","CSSSA008124","CSSSA008136","CSSSA008141","CSSSA008153","CSSSA008165","CSSSA008170","CSSSA008182","CSSSA008194","CSSSA008206","CSSSA008211","CSSSA008223","CSSSA008235","CSSSA008240","CSSSA008252","CSSSA008264","CSSSA008276","CSSSA008281","CSSSA008293","CSSSA008305","CSSSA008310","CSSSA008322","CSSSA008334","CSSSA008346","CSSSA008351","CSSSA008363","CSSSA008375","CSSSA008380","CSSSA008392","CSSSA008416","CSSSA008421","CSSSA008433","CSSSA008445","CSSSA008450","CSSSA008474","CSSSA008491","CSSSA008503","CSSSA008515","CSSSA008520","CSSSA008590","CSSSA008614","CSSSA008631","CSSSA008643","CSSSA008655","CSSSA008672","CSSSA008684","CSSSA008696","CSSSA008701","CSSSA008713","CSSSA008725","CSSSA008754","CSSSA008771","CSSSA008812","CSSSA008824","CSSSA008836","CSSSA008841","CSSSA008853","CSSSA008865","CSSSA008870","CSSSA008882","CSSSA008894","CSSSA008906","CSSSA008911","CSSSA008923","CSSSA008935","CSSSA008952","CSSSA008964","CSSSA008976","CSSSA008981","CSSSA008993","CSSSA009005","CSSSA009010","CSSSA009022","CSSSA009034","CSSSA009046","CSSSA009051","CSSSA009063","CSSSA009075","CSSSA009080","CSSSA009092","CSSSA009104","CSSSA009116","CSSSA009121","CSSSA009133","CSSSA009145","CSSSA009150","CSSSA009162","CSSSA017166","CSSSA017171","CSSSA017183","CSSSA017196","CSSSA017213","CSSSA017225","CSSSA017230","CSSSA017242","CSSSA017266","CSSSA017271","CSSSA017283","CSSSA017295","CSSSA017300","CSSSA017312","CSSSA017324","CSSSA017336","CSSSA017341","CSSSA017353","CSSSA017365","CSSSA017370","CSSSA017382","CSSSA017394","CSSSA017406","CSSSA017411","CSSSA017435","CSSSA017446","CSSSA017451","CSSSA017463","CSSSA017480","CSSSA017492","CSSSA017504","CSSSA017516","CSSSA017521","CSSSA017533","CSSSA017545","CSSSA017550","CSSSA017562","CSSSA017574","CSSSA017586","CSSSA017591","CSSSA017603","CSSSA017615","CSSSA017620","CSSSA017632","CSSSA017656","CSSSA017661","CSSSA017673","CSSSA017685","CSSSA017690","CSSSA017702","CSSSA017714","CSSSA017726","CSSSA017731","CSSSA017743","CSSSA017755","CSSSA017760","CSSSA017772","CSSSA017784","CSSSA017801","CSSSA017813","CSSSA017825","CSSSA017830","CSSSA017842","CSSSA017854","CSSSA017866","CSSSA017883","CSSSA017895","CSSSA017900","CSSSA017912","CSSSA017924","CSSSA017936","CSSSA017941","CSSSA017953","CSSSA017965","CSSSA017970","CSSSA017982","CSSSA017994","CSSSA018006","CSSSA018011","CSSSA018023","CSSSA018035","CSSSA018040","CSSSA018064","CSSSA018076","CSSSA018081","CSSSA018093","CSSSA018105","CSSSA018110","CSSSA018122","CSSSA018134","CSSSA018146","CSSSA018151","CSSSA018163","CSSSA018175","CSSSA018180","CSSSA018192","CSSSA018204","CSSSA018216","CSSSA018221","CSSSA018233","CSSSA018245","CSSSA018250","CSSSA018262","CSSSA018274","CSSSA018291","CSSSA018303","CSSSA018315","CSSSA018320","CSSSA018332","CSSSA018344","CSSSA018356","CSSSA018361","CSSSA018373","CSSSA018385","CSSSA018390","CSSSA018402","CSSSA018414","CSSSA018426","CSSSA018443","CSSSA018455","CSSSA018460","CSSSA018472","CSSSA018484","CSSSA018496","CSSSA018501","CSSSA018513","CSSSA018525","CSSSA018530","CSSSA018542","CSSSA018554","CSSSA018566","CSSSA018571","CSSSA018583","CSSSA018595","CSSSA018600","CSSSA018612","CSSSA018624","CSSSA018636","CSSSA018641","CSSSA018653","CSSSA018665","CSSSA018670","CSSSA018682","CSSSA018694","CSSSA018706","CSSSA018711","CSSSA018723","CSSSA018735","CSSSA018740","CSSSA018752","CSSSA018764","CSSSA018776","CSSSA018781","CSSSA018793","CSSSA018805","CSSSA018810","CSSSA018822","CSSSA018834","CSSSA018846","CSSSA018851","CSSSA018863","CSSSA018875","CSSSA018880","CSSSA018892","CSSSA018904","CSSSA018916","CSSSA018921","CSSSA018933","CSSSA018945","CSSSA018950","CSSSA018962","CSSSA018974","CSSSA018986","CSSSA018991","CSSSA019003","CSSSA019015","CSSSA019020","CSSSA019032","CSSSA019044","CSSSA019056","CSSSA019061","CSSSA019073","CSSSA019090","CSSSA019102","CSSSA019114","CSSSA019126","CSSSA019131","CSSSA019143","CSSSA019155","CSSSA019160","CSSSA019172","CSSSA019184","CSSSA019196","CSSSA019201","CSSSA019213","CSSSA019225","CSSSA019230","CSSSA019242","CSSSA019254","CSSSA019266","CSSSA019271","CSSSA019283","CSSSA019295","CSSSA019300","CSSSA019312","CSSSA019324","CSSSA019336","CSSSA019341","CSSSA019353","CSSSA019365","CSSSA019370","CSSSA019382","CSSSA019394","CSSSA019406","CSSSA019411","CSSSA019423","CSSSA019435","CSSSA019440","CSSSA019452","CSSSA019464","CSSSA019476","CSSSA019481","CSSSA019493","CSSSA019505","CSSSA019510","CSSSA019522","CSSSA019534","CSSSA019546","CSSSA019551","CSSSA019563","CSSSA019575","CSSSA019580","CSSSA019592","CSSSA019604","CSSSA019616","CSSSA019621","CSSSA019633","CSSSA019645","CSSSA019650","CSSSA019662","CSSSA019674","CSSSA019686","CSSSA019691","CSSSA019703","CSSSA019715","CSSSA019720","CSSSA019732","CSSSA019744","CSSSA019756","CSSSA019761","CSSSA019773","CSSSA019785","CSSSA019790","CSSSA019802","CSSSA019814","CSSSA019826","CSSSA019831","CSSSA019843","CSSSA019855","CSSSA019860","CSSSA019872","CSSSA019884","CSSSA019896","CSSSA019901","CSSSA019913","CSSSA019925","CSSSA019930","CSSSA019942","CSSSA019954","CSSSA019966","CSSSA019971","CSSSA019983","CSSSA019995","CSSSA020000","CSSSA020012","CSSSA020024","CSSSA020036","CSSSA020041","CSSSA020053","CSSSA020065","CSSSA020070","CSSSA020082","CSSSA020094","CSSSA020106","CSSSA020111","CSSSA020123","CSSSA020135","CSSSA020140","CSSSA020152","CSSSA020164","CSSSA020176");
} //fin de if($IdEstado == "07")

//Condicion de estado-clues
if($IdEstado == "08"){
	$Clues = array("CHSSA000022","CHSSA000034","CHSSA000075","CHSSA000080","CHSSA000104","CHSSA000133","CHSSA000150","CHSSA000162","CHSSA000191","CHSSA000203","CHSSA000215","CHSSA000220","CHSSA000232","CHSSA000261","CHSSA000273","CHSSA000290","CHSSA000302","CHSSA000314","CHSSA000326","CHSSA000343","CHSSA000355","CHSSA000360","CHSSA000372","CHSSA000384","CHSSA000396","CHSSA000401","CHSSA000413","CHSSA000425","CHSSA000430","CHSSA000454","CHSSA000466","CHSSA000471","CHSSA000483","CHSSA000495","CHSSA000500","CHSSA000512","CHSSA000524","CHSSA000541","CHSSA000553","CHSSA000565","CHSSA000570","CHSSA000582","CHSSA000594","CHSSA000606","CHSSA000611","CHSSA000623","CHSSA000640","CHSSA000652","CHSSA000664","CHSSA000676","CHSSA000681","CHSSA000705","CHSSA000722","CHSSA000734","CHSSA000746","CHSSA000751","CHSSA000891","CHSSA000903","CHSSA000915","CHSSA000920","CHSSA000932","CHSSA000944","CHSSA000956","CHSSA000961","CHSSA000973","CHSSA000985","CHSSA000990","CHSSA001002","CHSSA001026","CHSSA001031","CHSSA001055","CHSSA001060","CHSSA001072","CHSSA001084","CHSSA001096","CHSSA001101","CHSSA001113","CHSSA001125","CHSSA001130","CHSSA001142","CHSSA001166","CHSSA001171","CHSSA001183","CHSSA001195","CHSSA001241","CHSSA001253","CHSSA001265","CHSSA001270","CHSSA001282","CHSSA001306","CHSSA001323","CHSSA001340","CHSSA001364","CHSSA001381","CHSSA001393","CHSSA001405","CHSSA001422","CHSSA001434","CHSSA001446","CHSSA001451","CHSSA001463","CHSSA001475","CHSSA001492","CHSSA001504","CHSSA001516","CHSSA001521","CHSSA001533","CHSSA001545","CHSSA001550","CHSSA001562","CHSSA001574","CHSSA001586","CHSSA001591","CHSSA001603","CHSSA001620","CHSSA001644","CHSSA001656","CHSSA001661","CHSSA001673","CHSSA001685","CHSSA001690","CHSSA001726","CHSSA001743","CHSSA001755","CHSSA001760","CHSSA001772","CHSSA001784","CHSSA001796","CHSSA001801","CHSSA001813","CHSSA001842","CHSSA001866","CHSSA001871","CHSSA001883","CHSSA001895","CHSSA001900","CHSSA001912","CHSSA001941","CHSSA001953","CHSSA001970","CHSSA001982","CHSSA002006","CHSSA002011","CHSSA002023","CHSSA002040","CHSSA002081","CHSSA002093","CHSSA002105","CHSSA002110","CHSSA002122","CHSSA002134","CHSSA002146","CHSSA002151","CHSSA002163","CHSSA002175","CHSSA002192","CHSSA002233","CHSSA002245","CHSSA002250","CHSSA002262","CHSSA002274","CHSSA002286","CHSSA002291","CHSSA002303","CHSSA002315","CHSSA002332","CHSSA002344","CHSSA002356","CHSSA002361","CHSSA002385","CHSSA002390","CHSSA002402","CHSSA002414","CHSSA002426","CHSSA002431","CHSSA002443","CHSSA002455","CHSSA002460","CHSSA002484","CHSSA002496","CHSSA002501","CHSSA002525","CHSSA002530","CHSSA002554","CHSSA002566","CHSSA002571","CHSSA002583","CHSSA002595","CHSSA002600","CHSSA002636","CHSSA002653","CHSSA002670","CHSSA002682","CHSSA002706","CHSSA002711","CHSSA002723","CHSSA002735","CHSSA002740","CHSSA002752","CHSSA002764","CHSSA002834","CHSSA002846","CHSSA002851","CHSSA002880","CHSSA002904","CHSSA002916","CHSSA002921","CHSSA017412","CHSSA017424","CHSSA017436","CHSSA017441","CHSSA017465","CHSSA017470","CHSSA017482","CHSSA017494","CHSSA017506","CHSSA017511","CHSSA017523","CHSSA017535","CHSSA017540","CHSSA017552","CHSSA017564","CHSSA017576","CHSSA017581","CHSSA017593","CHSSA017605","CHSSA017610","CHSSA017622","CHSSA017634","CHSSA017646","CHSSA017651","CHSSA017663","CHSSA017675","CHSSA017686","CHSSA017691","CHSSA017703","CHSSA017715","CHSSA017720","CHSSA017732","CHSSA017744","CHSSA017761","CHSSA017773","CHSSA017785","CHSSA017790","CHSSA017802","CHSSA017814","CHSSA017826","CHSSA017831","CHSSA017855","CHSSA017860","CHSSA017872","CHSSA017884","CHSSA017896","CHSSA017901","CHSSA017913","CHSSA017925","CHSSA017930","CHSSA017942","CHSSA017954","CHSSA017966","CHSSA017971","CHSSA017983","CHSSA017995","CHSSA018000","CHSSA018012","CHSSA018024","CHSSA018036","CHSSA018041","CHSSA018053","CHSSA018065","CHSSA018070","CHSSA018082","CHSSA018094","CHSSA018106","CHSSA018111","CHSSA018123","CHSSA018135","CHSSA018140","CHSSA018152","CHSSA018164","CHSSA018176","CHSSA018181","CHSSA018193","CHSSA018205","CHSSA018210","CHSSA018222","CHSSA018234","CHSSA018246","CHSSA018251","CHSSA018263","CHSSA018275","CHSSA018280","CHSSA018292","CHSSA018304","CHSSA018316","CHSSA018321","CHSSA018345","CHSSA018350","CHSSA018362","CHSSA018374","CHSSA018386","CHSSA018403","CHSSA018415","CHSSA018420","CHSSA018432","CHSSA018444","CHSSA018456","CHSSA018461","CHSSA018473","CHSSA018485","CHSSA018490","CHSSA018502","CHSSA018514","CHSSA018526","CHSSA018531","CHSSA018543","CHSSA018555","CHSSA018560","CHSSA018572","CHSSA018584","CHSSA018596","CHSSA018601","CHSSA018613","CHSSA018625","CHSSA018630","CHSSA018642","CHSSA018654","CHSSA018666","CHSSA018671","CHSSA018683");
} //fin de if($IdEstado == "08")

//Condicion de estado-clues
if($IdEstado == "09"){
	$Clues = array("DFSSA000053","DFSSA000065","DFSSA000111","DFSSA000123","DFSSA000135","DFSSA000152","DFSSA000176","DFSSA000181","DFSSA000205","DFSSA000210","DFSSA000222","DFSSA000234","DFSSA000246","DFSSA000251","DFSSA000263","DFSSA000275","DFSSA000350","DFSSA000415","DFSSA000420","DFSSA000432","DFSSA000444","DFSSA000456","DFSSA000461","DFSSA000473","DFSSA000485","DFSSA000490","DFSSA000502","DFSSA000514","DFSSA000526","DFSSA000596","DFSSA000613","DFSSA000630","DFSSA000642","DFSSA000654","DFSSA000666","DFSSA000671","DFSSA000683","DFSSA000695","DFSSA000700","DFSSA000712","DFSSA000835","DFSSA000840","DFSSA000852","DFSSA000864","DFSSA000881","DFSSA000980","DFSSA000992","DFSSA001004","DFSSA001016","DFSSA001021","DFSSA001033","DFSSA001045","DFSSA001050","DFSSA001062","DFSSA001074","DFSSA001086","DFSSA001091","DFSSA001103","DFSSA001115","DFSSA001120","DFSSA001132","DFSSA001144","DFSSA001156","DFSSA001161","DFSSA001173","DFSSA001185","DFSSA001190","DFSSA001202","DFSSA001214","DFSSA001226","DFSSA001231","DFSSA001243","DFSSA001255","DFSSA001260","DFSSA001272","DFSSA001284","DFSSA001296","DFSSA001371","DFSSA001383","DFSSA001395","DFSSA001400","DFSSA001412","DFSSA001424","DFSSA001511","DFSSA001540","DFSSA001634","DFSSA001651","DFSSA001663","DFSSA001675","DFSSA001680","DFSSA001692","DFSSA001704","DFSSA001716","DFSSA001733","DFSSA001745","DFSSA001750","DFSSA001762","DFSSA001774","DFSSA001786","DFSSA001791","DFSSA001803","DFSSA001815","DFSSA001820","DFSSA001832","DFSSA001844","DFSSA001856","DFSSA001926","DFSSA001955","DFSSA001960","DFSSA001972","DFSSA001984","DFSSA001996","DFSSA002001","DFSSA002025","DFSSA002030","DFSSA002066","DFSSA002100","DFSSA002112","DFSSA002124","DFSSA002136","DFSSA002141","DFSSA002153","DFSSA002165","DFSSA002170","DFSSA002182","DFSSA002194","DFSSA002206","DFSSA002281","DFSSA002305","DFSSA002310","DFSSA002322","DFSSA002334","DFSSA002346","DFSSA002351","DFSSA002363","DFSSA002375","DFSSA002380","DFSSA002392","DFSSA002404","DFSSA002416","DFSSA002421","DFSSA002433","DFSSA002491","DFSSA002520","DFSSA002532","DFSSA002544","DFSSA002556","DFSSA002561","DFSSA002573","DFSSA002590","DFSSA002602","DFSSA002614","DFSSA002626","DFSSA002631","DFSSA002643","DFSSA002655","DFSSA002660","DFSSA002672","DFSSA002701","DFSSA002713","DFSSA002725","DFSSA002730","DFSSA002742","DFSSA002766","DFSSA002771","DFSSA002783","DFSSA002795","DFSSA002800","DFSSA002812","DFSSA002824","DFSSA002836","DFSSA002841","DFSSA002853","DFSSA002865","DFSSA002870","DFSSA002882","DFSSA002894","DFSSA002906","DFSSA002911","DFSSA002923","DFSSA002993","DFSSA003046","DFSSA003051","DFSSA003063","DFSSA003075","DFSSA003080","DFSSA003092","DFSSA003104","DFSSA003121","DFSSA003133","DFSSA003145","DFSSA003150","DFSSA003162","DFSSA003220","DFSSA003232","DFSSA003244","DFSSA003256","DFSSA003273","DFSSA003285","DFSSA003290","DFSSA003302","DFSSA003314","DFSSA003326","DFSSA003331","DFSSA003372","DFSSA003384","DFSSA003454","DFSSA003466","DFSSA003471","DFSSA003483","DFSSA003495","DFSSA003500","DFSSA003536","DFSSA003541","DFSSA003553","DFSSA003611","DFSSA003623","DFSSA003635","DFSSA003640","DFSSA003652","DFSSA003664","DFSSA003705","DFSSA003710","DFSSA003722","DFSSA003804","DFSSA003816","DFSSA003821","DFSSA003833","DFSSA003845","DFSSA003850","DFSSA003862","DFSSA003874","DFSSA003886","DFSSA003891","DFSSA003903","DFSSA003915","DFSSA003920","DFSSA003932","DFSSA003944","DFSSA003956","DFSSA003961","DFSSA003973","DFSSA003990","DFSSA004002","DFSSA004014","DFSSA004026","DFSSA004031","DFSSA004043","DFSSA004055","DFSSA004060","DFSSA004072","DFSSA004084","DFSSA004096","DFSSA004101","DFSSA004113","DFSSA004125","DFSSA004130","DFSSA004142","DFSSA004154","DFSSA004166","DFSSA004195","DFSSA004265","DFSSA004270","DFSSA017525","DFSSA017530","DFSSA017542","DFSSA017554","DFSSA017566","DFSSA017571","DFSSA017583","DFSSA017595","DFSSA017600","DFSSA017612","DFSSA017624","DFSSA017636","DFSSA017641","DFSSA017653","DFSSA017665","DFSSA017670","DFSSA017682","DFSSA017694","DFSSA017706","DFSSA017711","DFSSA017723","DFSSA017735","DFSSA017740","DFSSA017752","DFSSA017764","DFSSA017776","DFSSA017781","DFSSA017793","DFSSA017805","DFSSA017810","DFSSA017822","DFSSA017834","DFSSA017846","DFSSA017851","DFSSA017863","DFSSA017875","DFSSA017886","DFSSA017891","DFSSA017915","DFSSA017920","DFSSA017932","DFSSA017944","DFSSA017956","DFSSA017961","DFSSA017973","DFSSA017985","DFSSA017990","DFSSA018002","DFSSA018014","DFSSA018026","DFSSA018031","DFSSA018043","DFSSA018055","DFSSA018060","DFSSA018072","DFSSA018084","DFSSA018096","DFSSA018101","DFSSA018113","DFSSA018125","DFSSA018130","DFSSA018142","DFSSA018154","DFSSA018166","DFSSA018171","DFSSA018323","DFSSA018335","DFSSA018340","DFSSA018352","DFSSA018364","DFSSA018376","DFSSA018381","DFSSA018393","DFSSA018405","DFSSA018410","DFSSA018422","DFSSA018434","DFSSA018446","DFSSA018451","DFSSA018463","DFSSA018475","DFSSA018480","DFSSA018492","DFSSA018504","DFSSA018516","DFSSA018521","DFSSA018533","DFSSA018545","DFSSA018550","DFSSA018562","DFSSA018574","DFSSA018586","DFSSA018591","DFSSA018603","DFSSA018615","DFSSA018620","DFSSA018632","DFSSA018644","DFSSA018656","DFSSA018661","DFSSA018673","DFSSA018685","DFSSA018690","DFSSA018702","DFSSA018714","DFSSA018726","DFSSA018731","DFSSA018743","DFSSA018755","DFSSA018760","DFSSA018772","DFSSA018784","DFSSA018796","DFSSA018801","DFSSA018813","DFSSA018825","DFSSA018830","DFSSA018842","DFSSA018854","DFSSA018866","DFSSA018871","DFSSA018883","DFSSA018895","DFSSA018900","DFSSA018912","DFSSA018924","DFSSA018936","DFSSA018941","DFSSA018953","DFSSA018965","DFSSA018970","DFSSA018982","DFSSA018994","DFSSA019006","DFSSA019011","DFSSA019023","DFSSA019035","DFSSA019040","DFSSA019052","DFSSA019064","DFSSA019076","DFSSA019081","DFSSA019093","DFSSA019105","DFSSA019110");
} //fin de if($IdEstado == "09")

//Condicion de estado-clues
if($IdEstado == "10"){
	$Clues = array("DGSSA000010","DGSSA000022","DGSSA000034","DGSSA000046","DGSSA000051","DGSSA000063","DGSSA000075","DGSSA000080","DGSSA000092","DGSSA000104","DGSSA000116","DGSSA000121","DGSSA000133","DGSSA000145","DGSSA000150","DGSSA000162","DGSSA000174","DGSSA000186","DGSSA000191","DGSSA000203","DGSSA000215","DGSSA000220","DGSSA000232","DGSSA000244","DGSSA000256","DGSSA000261","DGSSA000273","DGSSA000285","DGSSA000302","DGSSA000314","DGSSA000326","DGSSA000331","DGSSA000343","DGSSA000355","DGSSA000360","DGSSA000372","DGSSA000384","DGSSA000396","DGSSA000401","DGSSA000413","DGSSA000425","DGSSA000442","DGSSA000454","DGSSA000471","DGSSA000483","DGSSA000495","DGSSA000500","DGSSA000512","DGSSA000524","DGSSA000536","DGSSA000541","DGSSA000553","DGSSA000565","DGSSA000570","DGSSA000582","DGSSA000594","DGSSA000606","DGSSA000623","DGSSA000635","DGSSA000640","DGSSA000652","DGSSA000664","DGSSA000676","DGSSA000693","DGSSA000705","DGSSA000710","DGSSA000722","DGSSA000734","DGSSA000746","DGSSA000751","DGSSA000763","DGSSA000775","DGSSA000780","DGSSA000792","DGSSA000804","DGSSA000816","DGSSA000821","DGSSA000833","DGSSA000845","DGSSA000850","DGSSA000862","DGSSA000874","DGSSA000886","DGSSA000891","DGSSA000903","DGSSA000915","DGSSA000920","DGSSA000932","DGSSA000944","DGSSA000956","DGSSA000961","DGSSA000973","DGSSA000985","DGSSA000990","DGSSA001014","DGSSA001026","DGSSA001031","DGSSA001043","DGSSA001055","DGSSA001060","DGSSA001072","DGSSA001084","DGSSA001096","DGSSA001101","DGSSA001113","DGSSA001125","DGSSA001130","DGSSA001154","DGSSA001166","DGSSA001171","DGSSA001183","DGSSA001200","DGSSA001212","DGSSA001224","DGSSA001241","DGSSA001253","DGSSA001265","DGSSA001270","DGSSA001282","DGSSA001294","DGSSA001306","DGSSA001311","DGSSA001323","DGSSA001340","DGSSA001352","DGSSA001364","DGSSA001376","DGSSA001381","DGSSA001393","DGSSA001405","DGSSA001410","DGSSA001422","DGSSA001434","DGSSA001446","DGSSA001451","DGSSA001463","DGSSA001475","DGSSA001480","DGSSA001492","DGSSA001504","DGSSA001516","DGSSA001533","DGSSA001545","DGSSA001562","DGSSA001574","DGSSA001586","DGSSA001591","DGSSA001603","DGSSA001615","DGSSA001620","DGSSA001632","DGSSA001644","DGSSA001656","DGSSA001661","DGSSA001673","DGSSA001685","DGSSA001690","DGSSA001702","DGSSA001714","DGSSA001726","DGSSA001731","DGSSA001743","DGSSA001755","DGSSA001760","DGSSA001772","DGSSA001784","DGSSA001796","DGSSA001801","DGSSA001813","DGSSA001825","DGSSA001830","DGSSA001842","DGSSA001854","DGSSA001866","DGSSA001871","DGSSA001883","DGSSA001895","DGSSA001900","DGSSA001912","DGSSA001924","DGSSA001965","DGSSA001970","DGSSA001982","DGSSA001994","DGSSA002006","DGSSA002011","DGSSA002052","DGSSA002076","DGSSA002081","DGSSA002093","DGSSA002105","DGSSA002110","DGSSA002122","DGSSA002134","DGSSA002146","DGSSA002151","DGSSA002163","DGSSA002175","DGSSA002180","DGSSA002192","DGSSA002204","DGSSA002221","DGSSA002233","DGSSA002245","DGSSA002250","DGSSA002262","DGSSA002274","DGSSA002303","DGSSA002315","DGSSA002320","DGSSA002332","DGSSA017115","DGSSA017132","DGSSA017144","DGSSA017156","DGSSA017161","DGSSA017173","DGSSA017185","DGSSA017190","DGSSA017202","DGSSA017214","DGSSA017226","DGSSA017231","DGSSA017242","DGSSA017254","DGSSA017266","DGSSA017271","DGSSA017283","DGSSA017295","DGSSA017300","DGSSA017312","DGSSA017324","DGSSA017336","DGSSA017341","DGSSA017365","DGSSA017370","DGSSA017382","DGSSA017394","DGSSA017406","DGSSA017411","DGSSA017423","DGSSA017435","DGSSA017440","DGSSA017452","DGSSA017464","DGSSA017476","DGSSA017481","DGSSA017493","DGSSA017505","DGSSA017510","DGSSA017522","DGSSA017534","DGSSA017546","DGSSA017551","DGSSA017563","DGSSA017575","DGSSA017580","DGSSA017592","DGSSA017604","DGSSA017616","DGSSA017621","DGSSA017633","DGSSA017645","DGSSA017650","DGSSA017662","DGSSA017674","DGSSA017686","DGSSA017691","DGSSA017703","DGSSA017715","DGSSA017720","DGSSA017732","DGSSA017744","DGSSA017756","DGSSA017761","DGSSA017773","DGSSA017785","DGSSA017790","DGSSA017802","DGSSA017814","DGSSA017826","DGSSA017831","DGSSA017843","DGSSA017855","DGSSA017860","DGSSA017872");
} //fin de if($IdEstado == "10")

//Condicion de estado-clues
if($IdEstado == "11"){
	$Clues = array("GTSSA000013","GTSSA000025","GTSSA000030","GTSSA000042","GTSSA000054","GTSSA000066","GTSSA000071","GTSSA000083","GTSSA000095","GTSSA000100","GTSSA000112","GTSSA000124","GTSSA000136","GTSSA000141","GTSSA000153","GTSSA000165","GTSSA000170","GTSSA000182","GTSSA000194","GTSSA000206","GTSSA000211","GTSSA000223","GTSSA000235","GTSSA000240","GTSSA000252","GTSSA000264","GTSSA000276","GTSSA000281","GTSSA000293","GTSSA000305","GTSSA000310","GTSSA000322","GTSSA000334","GTSSA000346","GTSSA000351","GTSSA000363","GTSSA000375","GTSSA000380","GTSSA000392","GTSSA000404","GTSSA000416","GTSSA000421","GTSSA000433","GTSSA000445","GTSSA000450","GTSSA000462","GTSSA000474","GTSSA000486","GTSSA000491","GTSSA000503","GTSSA000515","GTSSA000520","GTSSA000532","GTSSA000544","GTSSA000556","GTSSA000561","GTSSA000573","GTSSA000585","GTSSA000590","GTSSA000602","GTSSA000614","GTSSA000626","GTSSA000631","GTSSA000643","GTSSA000655","GTSSA000660","GTSSA000672","GTSSA000684","GTSSA000696","GTSSA000701","GTSSA000713","GTSSA000725","GTSSA000730","GTSSA000742","GTSSA000754","GTSSA000766","GTSSA000771","GTSSA000795","GTSSA000800","GTSSA000812","GTSSA000824","GTSSA000836","GTSSA000841","GTSSA000853","GTSSA000865","GTSSA000870","GTSSA000882","GTSSA000894","GTSSA000906","GTSSA000911","GTSSA000923","GTSSA000935","GTSSA000940","GTSSA000952","GTSSA000964","GTSSA000976","GTSSA000981","GTSSA000993","GTSSA001005","GTSSA001010","GTSSA001022","GTSSA001034","GTSSA001046","GTSSA001051","GTSSA001063","GTSSA001075","GTSSA001080","GTSSA001092","GTSSA001104","GTSSA001116","GTSSA001121","GTSSA001133","GTSSA001145","GTSSA001150","GTSSA001162","GTSSA001174","GTSSA001186","GTSSA001191","GTSSA001203","GTSSA001215","GTSSA001220","GTSSA001232","GTSSA001244","GTSSA001256","GTSSA001261","GTSSA001273","GTSSA001285","GTSSA001290","GTSSA001302","GTSSA001314","GTSSA001326","GTSSA001331","GTSSA001343","GTSSA001355","GTSSA001360","GTSSA001372","GTSSA001384","GTSSA001396","GTSSA001401","GTSSA001413","GTSSA001425","GTSSA001430","GTSSA001442","GTSSA001454","GTSSA001466","GTSSA001471","GTSSA001483","GTSSA001495","GTSSA001500","GTSSA001512","GTSSA001524","GTSSA001536","GTSSA001541","GTSSA001553","GTSSA001565","GTSSA001570","GTSSA001582","GTSSA001594","GTSSA001606","GTSSA001611","GTSSA001623","GTSSA001635","GTSSA001640","GTSSA001652","GTSSA001664","GTSSA001676","GTSSA001681","GTSSA001693","GTSSA001705","GTSSA001710","GTSSA001722","GTSSA001734","GTSSA001746","GTSSA001751","GTSSA001763","GTSSA001775","GTSSA001780","GTSSA001792","GTSSA001816","GTSSA001821","GTSSA001833","GTSSA001845","GTSSA001850","GTSSA001862","GTSSA001874","GTSSA001886","GTSSA001891","GTSSA001903","GTSSA001915","GTSSA001920","GTSSA001932","GTSSA001944","GTSSA001956","GTSSA001961","GTSSA001973","GTSSA001985","GTSSA001990","GTSSA002002","GTSSA002014","GTSSA002026","GTSSA002031","GTSSA002043","GTSSA002055","GTSSA002060","GTSSA002072","GTSSA002084","GTSSA002096","GTSSA002101","GTSSA002113","GTSSA002125","GTSSA002130","GTSSA002142","GTSSA002154","GTSSA002166","GTSSA002171","GTSSA002183","GTSSA002195","GTSSA002200","GTSSA002212","GTSSA002224","GTSSA002236","GTSSA002241","GTSSA002253","GTSSA002265","GTSSA002270","GTSSA002282","GTSSA002294","GTSSA002306","GTSSA002311","GTSSA002323","GTSSA002335","GTSSA002340","GTSSA002352","GTSSA002364","GTSSA002376","GTSSA002381","GTSSA002393","GTSSA002405","GTSSA002410","GTSSA002422","GTSSA002434","GTSSA002446","GTSSA002451","GTSSA002463","GTSSA002475","GTSSA002480","GTSSA002492","GTSSA002504","GTSSA002516","GTSSA002521","GTSSA002533","GTSSA002545","GTSSA002550","GTSSA002562","GTSSA002574","GTSSA002586","GTSSA002591","GTSSA002603","GTSSA002615","GTSSA002620","GTSSA002632","GTSSA002644","GTSSA002656","GTSSA002661","GTSSA002673","GTSSA002685","GTSSA002690","GTSSA002702","GTSSA002714","GTSSA002726","GTSSA002731","GTSSA002743","GTSSA002755","GTSSA002760","GTSSA002772","GTSSA002784","GTSSA002796","GTSSA002801","GTSSA002813","GTSSA002825","GTSSA002830","GTSSA002842","GTSSA002854","GTSSA002866","GTSSA002871","GTSSA002883","GTSSA002895","GTSSA002900","GTSSA002912","GTSSA002924","GTSSA002936","GTSSA002941","GTSSA002953","GTSSA002970","GTSSA002982","GTSSA002994","GTSSA003011","GTSSA003023","GTSSA003035","GTSSA003040","GTSSA003052","GTSSA003064","GTSSA003076","GTSSA003081","GTSSA003093","GTSSA003105","GTSSA003110","GTSSA003122","GTSSA003134","GTSSA003146","GTSSA003151","GTSSA003163","GTSSA003175","GTSSA003180","GTSSA003192","GTSSA003204","GTSSA003216","GTSSA003221","GTSSA003233","GTSSA003245","GTSSA003250","GTSSA003262","GTSSA003274","GTSSA003286","GTSSA003291","GTSSA003303","GTSSA003315","GTSSA003320","GTSSA003332","GTSSA003344","GTSSA003361","GTSSA003373","GTSSA003385","GTSSA003390","GTSSA003402","GTSSA003414","GTSSA003426","GTSSA003431","GTSSA003443","GTSSA003455","GTSSA003460","GTSSA003472","GTSSA003484","GTSSA003496","GTSSA003501","GTSSA003513","GTSSA003525","GTSSA003530","GTSSA003542","GTSSA003554","GTSSA003566","GTSSA003571","GTSSA003583","GTSSA003595","GTSSA003600","GTSSA003612","GTSSA003624","GTSSA003636","GTSSA003641","GTSSA003653","GTSSA003665","GTSSA003670","GTSSA003682","GTSSA003694","GTSSA003706","GTSSA003711","GTSSA003723","GTSSA003735","GTSSA003740","GTSSA003752","GTSSA003764","GTSSA003776","GTSSA003781","GTSSA003793","GTSSA003805","GTSSA003810","GTSSA003822","GTSSA003834","GTSSA003846","GTSSA003851","GTSSA003863","GTSSA003875","GTSSA003880","GTSSA003892","GTSSA003904","GTSSA003916","GTSSA003921","GTSSA003933","GTSSA003945","GTSSA003950","GTSSA003962","GTSSA003974","GTSSA003986","GTSSA003991","GTSSA004003","GTSSA004015","GTSSA004020","GTSSA004032","GTSSA004044","GTSSA004056","GTSSA004061","GTSSA004073","GTSSA004085","GTSSA004090","GTSSA004102","GTSSA004114","GTSSA004126","GTSSA004131","GTSSA004143","GTSSA004155","GTSSA004160","GTSSA004172","GTSSA004184","GTSSA004196","GTSSA004201","GTSSA004213","GTSSA004225","GTSSA004230","GTSSA004242","GTSSA004254","GTSSA004266","GTSSA004271","GTSSA004283","GTSSA004295","GTSSA004300","GTSSA004312","GTSSA004324","GTSSA004336","GTSSA004341","GTSSA004353","GTSSA004365","GTSSA004370","GTSSA004382","GTSSA004394","GTSSA004406","GTSSA004411","GTSSA004423","GTSSA004435","GTSSA004440","GTSSA004452","GTSSA004464","GTSSA004476","GTSSA004481","GTSSA004493","GTSSA004505","GTSSA004510","GTSSA004522","GTSSA004534","GTSSA004546","GTSSA004551","GTSSA004563","GTSSA004575","GTSSA004580","GTSSA004592","GTSSA004604","GTSSA004616","GTSSA004621","GTSSA004633","GTSSA004645","GTSSA004650","GTSSA004662","GTSSA004674","GTSSA004686","GTSSA004691","GTSSA004703","GTSSA004715","GTSSA004720","GTSSA004732","GTSSA004744","GTSSA004756","GTSSA004761","GTSSA004773","GTSSA004785","GTSSA004790","GTSSA004802","GTSSA004814","GTSSA004826","GTSSA004831","GTSSA004843","GTSSA004855","GTSSA004860","GTSSA004872","GTSSA004884","GTSSA004896","GTSSA004901","GTSSA004913","GTSSA004925","GTSSA004930","GTSSA004942","GTSSA004954","GTSSA004966","GTSSA004971","GTSSA004983","GTSSA004995","GTSSA005000","GTSSA005012","GTSSA005024","GTSSA005036","GTSSA005041","GTSSA005053","GTSSA005065","GTSSA005070","GTSSA005082","GTSSA005094","GTSSA005106","GTSSA005111","GTSSA005123","GTSSA005135","GTSSA005140","GTSSA005152","GTSSA005164","GTSSA005176","GTSSA005181","GTSSA005193","GTSSA005205","GTSSA005210","GTSSA005222","GTSSA005234","GTSSA005246","GTSSA005251","GTSSA005263","GTSSA005275","GTSSA005280","GTSSA005292","GTSSA005304","GTSSA005316","GTSSA005386","GTSSA005391","GTSSA005403","GTSSA005415","GTSSA016481","GTSSA016493","GTSSA016505","GTSSA016510","GTSSA016534","GTSSA016546","GTSSA016551","GTSSA016563","GTSSA016575","GTSSA016580","GTSSA016592","GTSSA016604","GTSSA016616","GTSSA016621","GTSSA016633","GTSSA016645","GTSSA016650","GTSSA016662","GTSSA016674","GTSSA016685","GTSSA016690","GTSSA016702","GTSSA016714","GTSSA016726","GTSSA016731","GTSSA016743","GTSSA016755","GTSSA016760","GTSSA016772","GTSSA016784","GTSSA016796","GTSSA016801","GTSSA016813","GTSSA016825","GTSSA016830","GTSSA016842","GTSSA016854","GTSSA016866","GTSSA016871","GTSSA016883","GTSSA016895","GTSSA016900","GTSSA016912","GTSSA016924","GTSSA016936","GTSSA016941","GTSSA016953","GTSSA016965","GTSSA016970","GTSSA016982","GTSSA016994","GTSSA017006","GTSSA017011","GTSSA017023","GTSSA017035","GTSSA017040","GTSSA017052","GTSSA017064","GTSSA017076","GTSSA017081","GTSSA017093","GTSSA017105","GTSSA017110","GTSSA017122","GTSSA017134","GTSSA017146","GTSSA017151","GTSSA017163","GTSSA017175","GTSSA017180","GTSSA017192","GTSSA017204","GTSSA017216","GTSSA017221","GTSSA017233","GTSSA017245","GTSSA017250","GTSSA017262","GTSSA017274","GTSSA017286","GTSSA017291","GTSSA017303","GTSSA017315","GTSSA017320","GTSSA017332","GTSSA017344","GTSSA017356","GTSSA017361","GTSSA017373","GTSSA017385","GTSSA017390","GTSSA017402","GTSSA017414","GTSSA017426","GTSSA017431","GTSSA017443","GTSSA017455","GTSSA017460","GTSSA017472","GTSSA017484","GTSSA017496","GTSSA017501","GTSSA017513","GTSSA017525");
} //fin de if($IdEstado == "11")

//Condicion de estado-clues
if($IdEstado == "12"){
	$Clues = array("GRSSA000010","GRSSA000022","GRSSA000034","GRSSA000046","GRSSA000051","GRSSA000063","GRSSA000075","GRSSA000080","GRSSA000092","GRSSA000104","GRSSA000116","GRSSA000121","GRSSA000133","GRSSA000145","GRSSA000150","GRSSA000162","GRSSA000174","GRSSA000186","GRSSA000191","GRSSA000203","GRSSA000215","GRSSA000220","GRSSA000232","GRSSA000244","GRSSA000256","GRSSA000261","GRSSA000273","GRSSA000285","GRSSA000290","GRSSA000302","GRSSA000314","GRSSA000326","GRSSA000331","GRSSA000343","GRSSA000355","GRSSA000360","GRSSA000372","GRSSA000384","GRSSA000396","GRSSA000401","GRSSA000413","GRSSA000425","GRSSA000430","GRSSA000442","GRSSA000454","GRSSA000466","GRSSA000471","GRSSA000483","GRSSA000495","GRSSA000500","GRSSA000512","GRSSA000524","GRSSA000536","GRSSA000541","GRSSA000553","GRSSA000565","GRSSA000570","GRSSA000582","GRSSA000594","GRSSA000606","GRSSA000611","GRSSA000623","GRSSA000635","GRSSA000640","GRSSA000652","GRSSA000664","GRSSA000676","GRSSA000710","GRSSA000722","GRSSA000734","GRSSA000746","GRSSA000751","GRSSA000763","GRSSA000775","GRSSA000780","GRSSA000792","GRSSA000804","GRSSA000816","GRSSA000821","GRSSA000833","GRSSA000845","GRSSA000850","GRSSA000862","GRSSA000874","GRSSA000886","GRSSA000891","GRSSA000903","GRSSA000915","GRSSA000920","GRSSA000932","GRSSA000944","GRSSA000956","GRSSA000961","GRSSA000973","GRSSA000985","GRSSA000990","GRSSA001002","GRSSA001014","GRSSA001026","GRSSA001031","GRSSA001043","GRSSA001055","GRSSA001060","GRSSA001072","GRSSA001096","GRSSA001101","GRSSA001113","GRSSA001125","GRSSA001130","GRSSA001142","GRSSA001154","GRSSA001166","GRSSA001171","GRSSA001183","GRSSA001195","GRSSA001200","GRSSA001212","GRSSA001224","GRSSA001236","GRSSA001241","GRSSA001253","GRSSA001265","GRSSA001270","GRSSA001282","GRSSA001294","GRSSA001306","GRSSA001311","GRSSA001323","GRSSA001335","GRSSA001340","GRSSA001352","GRSSA001364","GRSSA001376","GRSSA001381","GRSSA001393","GRSSA001405","GRSSA001410","GRSSA001422","GRSSA001434","GRSSA001446","GRSSA001451","GRSSA001463","GRSSA001475","GRSSA001480","GRSSA001492","GRSSA001504","GRSSA001516","GRSSA001521","GRSSA001533","GRSSA001545","GRSSA001550","GRSSA001562","GRSSA001586","GRSSA001591","GRSSA001603","GRSSA001615","GRSSA001620","GRSSA001632","GRSSA001644","GRSSA001656","GRSSA001661","GRSSA001673","GRSSA001685","GRSSA001690","GRSSA001702","GRSSA001714","GRSSA001726","GRSSA001731","GRSSA001743","GRSSA001755","GRSSA001760","GRSSA001772","GRSSA001784","GRSSA001796","GRSSA001801","GRSSA001813","GRSSA001825","GRSSA001830","GRSSA001842","GRSSA001854","GRSSA001866","GRSSA001871","GRSSA001883","GRSSA001895","GRSSA001900","GRSSA001912","GRSSA001924","GRSSA001936","GRSSA001941","GRSSA001953","GRSSA001965","GRSSA001970","GRSSA001982","GRSSA001994","GRSSA002006","GRSSA002011","GRSSA002023","GRSSA002035","GRSSA002040","GRSSA002052","GRSSA002064","GRSSA002076","GRSSA002081","GRSSA002093","GRSSA002105","GRSSA002110","GRSSA002122","GRSSA002134","GRSSA002146","GRSSA002151","GRSSA002163","GRSSA002175","GRSSA002180","GRSSA002192","GRSSA002204","GRSSA002216","GRSSA002221","GRSSA002233","GRSSA002245","GRSSA002250","GRSSA002262","GRSSA002274","GRSSA002286","GRSSA002291","GRSSA002303","GRSSA002315","GRSSA002320","GRSSA002332","GRSSA002344","GRSSA002356","GRSSA002361","GRSSA002373","GRSSA002385","GRSSA002390","GRSSA002402","GRSSA002414","GRSSA002426","GRSSA002431","GRSSA002443","GRSSA002455","GRSSA002460","GRSSA002472","GRSSA002484","GRSSA002496","GRSSA002501","GRSSA002513","GRSSA002525","GRSSA002530","GRSSA002542","GRSSA002554","GRSSA002566","GRSSA002571","GRSSA002583","GRSSA002595","GRSSA002600","GRSSA002612","GRSSA002624","GRSSA002636","GRSSA002641","GRSSA002653","GRSSA002665","GRSSA002670","GRSSA002682","GRSSA002694","GRSSA002706","GRSSA002711","GRSSA002723","GRSSA002735","GRSSA002740","GRSSA002752","GRSSA002764","GRSSA002776","GRSSA002781","GRSSA002793","GRSSA002805","GRSSA002810","GRSSA002822","GRSSA002834","GRSSA002846","GRSSA002851","GRSSA002863","GRSSA002875","GRSSA002880","GRSSA002892","GRSSA002904","GRSSA002921","GRSSA002933","GRSSA002945","GRSSA002950","GRSSA002962","GRSSA002974","GRSSA002986","GRSSA002991","GRSSA003003","GRSSA003015","GRSSA003020","GRSSA003032","GRSSA003044","GRSSA003056","GRSSA003061","GRSSA003073","GRSSA003085","GRSSA003090","GRSSA003102","GRSSA003114","GRSSA003126","GRSSA003131","GRSSA003143","GRSSA003155","GRSSA003160","GRSSA003172","GRSSA003184","GRSSA003196","GRSSA003201","GRSSA003213","GRSSA003225","GRSSA003230","GRSSA003242","GRSSA003254","GRSSA003266","GRSSA003271","GRSSA003283","GRSSA003295","GRSSA003300","GRSSA003312","GRSSA003324","GRSSA003336","GRSSA003341","GRSSA003353","GRSSA003365","GRSSA003370","GRSSA003382","GRSSA003394","GRSSA003406","GRSSA003411","GRSSA003423","GRSSA003435","GRSSA003440","GRSSA003452","GRSSA003464","GRSSA003476","GRSSA003481","GRSSA003493","GRSSA003505","GRSSA003510","GRSSA003522","GRSSA003534","GRSSA003546","GRSSA003551","GRSSA003563","GRSSA003575","GRSSA003580","GRSSA003592","GRSSA003604","GRSSA003616","GRSSA003621","GRSSA003633","GRSSA003645","GRSSA003650","GRSSA003662","GRSSA003674","GRSSA003686","GRSSA003691","GRSSA003703","GRSSA003715","GRSSA003720","GRSSA003732","GRSSA003744","GRSSA003756","GRSSA003761","GRSSA003773","GRSSA003785","GRSSA003790","GRSSA003802","GRSSA003814","GRSSA003826","GRSSA003831","GRSSA003843","GRSSA003855","GRSSA003860","GRSSA003872","GRSSA003884","GRSSA003896","GRSSA003901","GRSSA003913","GRSSA003925","GRSSA003930","GRSSA003942","GRSSA003954","GRSSA003966","GRSSA003971","GRSSA003983","GRSSA003995","GRSSA004000","GRSSA004012","GRSSA004024","GRSSA004036","GRSSA004041","GRSSA004053","GRSSA004065","GRSSA004070","GRSSA004082","GRSSA004094","GRSSA004106","GRSSA004111","GRSSA004123","GRSSA004135","GRSSA004140","GRSSA004152","GRSSA004164","GRSSA004176","GRSSA004181","GRSSA004193","GRSSA004205","GRSSA004210","GRSSA004222","GRSSA004234","GRSSA004246","GRSSA004251","GRSSA004263","GRSSA004275","GRSSA004280","GRSSA004292","GRSSA004304","GRSSA004316","GRSSA004321","GRSSA004333","GRSSA004345","GRSSA004350","GRSSA004362","GRSSA004374","GRSSA004386","GRSSA004391","GRSSA004403","GRSSA004415","GRSSA004420","GRSSA004432","GRSSA004444","GRSSA004456","GRSSA004461","GRSSA004473","GRSSA004485","GRSSA004490","GRSSA004502","GRSSA004514","GRSSA004526","GRSSA004531","GRSSA004543","GRSSA004555","GRSSA004560","GRSSA004572","GRSSA004584","GRSSA004596","GRSSA004601","GRSSA004613","GRSSA004625","GRSSA004630","GRSSA004642","GRSSA004654","GRSSA004666","GRSSA004671","GRSSA004695","GRSSA004700","GRSSA004712","GRSSA004724","GRSSA004736","GRSSA004741","GRSSA004753","GRSSA004765","GRSSA004770","GRSSA004782","GRSSA004794","GRSSA004806","GRSSA004811","GRSSA004823","GRSSA004835","GRSSA004840","GRSSA004852","GRSSA004864","GRSSA004876","GRSSA004881","GRSSA004893","GRSSA004905","GRSSA004910","GRSSA004922","GRSSA004934","GRSSA004946","GRSSA004951","GRSSA004963","GRSSA004975","GRSSA004980","GRSSA004992","GRSSA005004","GRSSA005016","GRSSA005021","GRSSA005033","GRSSA005045","GRSSA005050","GRSSA005062","GRSSA005074","GRSSA005086","GRSSA005091","GRSSA005103","GRSSA005115","GRSSA005120","GRSSA005132","GRSSA005144","GRSSA005156","GRSSA005161","GRSSA005173","GRSSA005185","GRSSA005190","GRSSA005202","GRSSA005214","GRSSA005226","GRSSA005231","GRSSA005243","GRSSA005255","GRSSA005260","GRSSA005272","GRSSA005284","GRSSA005296","GRSSA005301","GRSSA005313","GRSSA005325","GRSSA005330","GRSSA005342","GRSSA005354","GRSSA005366","GRSSA005371","GRSSA005383","GRSSA005395","GRSSA005400","GRSSA005412","GRSSA005424","GRSSA005436","GRSSA005441","GRSSA005470","GRSSA005482","GRSSA005494","GRSSA005506","GRSSA005511","GRSSA005523","GRSSA005535","GRSSA005540","GRSSA005552","GRSSA005564","GRSSA005576","GRSSA005581","GRSSA005593","GRSSA005605","GRSSA005610","GRSSA005622","GRSSA005634","GRSSA005646","GRSSA005651","GRSSA005663","GRSSA005675","GRSSA005680","GRSSA005692","GRSSA005704","GRSSA005716","GRSSA005721","GRSSA005733","GRSSA005745","GRSSA005750","GRSSA005762","GRSSA005774","GRSSA005786","GRSSA005791","GRSSA005803","GRSSA005815","GRSSA005820","GRSSA005832","GRSSA005844","GRSSA005856","GRSSA005861","GRSSA005873","GRSSA005885","GRSSA005890","GRSSA005902","GRSSA005914","GRSSA005926","GRSSA005931","GRSSA005943","GRSSA005955","GRSSA005960","GRSSA005972","GRSSA005984","GRSSA005996","GRSSA006001","GRSSA006013","GRSSA006025","GRSSA006030","GRSSA006042","GRSSA006066","GRSSA006071","GRSSA006083","GRSSA006095","GRSSA006100","GRSSA006112","GRSSA006124","GRSSA006136","GRSSA006141","GRSSA006153","GRSSA006165","GRSSA006170","GRSSA006182","GRSSA006194","GRSSA006206","GRSSA006211","GRSSA006223","GRSSA006235","GRSSA006240","GRSSA006252","GRSSA006264","GRSSA006276","GRSSA006281","GRSSA006293","GRSSA006305","GRSSA006310","GRSSA006322","GRSSA006334","GRSSA006346","GRSSA006351","GRSSA006363","GRSSA006375","GRSSA006380","GRSSA006392","GRSSA006404","GRSSA006416","GRSSA006421","GRSSA006433","GRSSA006445","GRSSA006450","GRSSA006462","GRSSA006474","GRSSA006486","GRSSA006491","GRSSA006503","GRSSA006515","GRSSA006520","GRSSA006532","GRSSA006544","GRSSA006556","GRSSA006561","GRSSA006573","GRSSA006585","GRSSA006590","GRSSA006602","GRSSA006614","GRSSA006626","GRSSA006631","GRSSA006643","GRSSA006655","GRSSA006660","GRSSA006672","GRSSA006684","GRSSA006696","GRSSA006701","GRSSA006713","GRSSA006725","GRSSA006730","GRSSA006754","GRSSA006766","GRSSA006771","GRSSA006783","GRSSA006795","GRSSA006800","GRSSA006812","GRSSA006824","GRSSA006836","GRSSA006841","GRSSA006853","GRSSA006865","GRSSA006870","GRSSA006882","GRSSA006894","GRSSA006906","GRSSA006911","GRSSA006923","GRSSA006935","GRSSA006940","GRSSA006952","GRSSA006964","GRSSA006976","GRSSA006981","GRSSA006993","GRSSA007005","GRSSA007010","GRSSA007022","GRSSA007034","GRSSA007046","GRSSA007051","GRSSA007063","GRSSA007075","GRSSA007080","GRSSA007092","GRSSA007104","GRSSA007116","GRSSA007121","GRSSA007133","GRSSA007145","GRSSA007150","GRSSA007162","GRSSA007174","GRSSA007186","GRSSA007191","GRSSA007203","GRSSA007215","GRSSA007220","GRSSA007232","GRSSA007244","GRSSA007256","GRSSA007261","GRSSA007273","GRSSA007285","GRSSA007290","GRSSA007302","GRSSA007314","GRSSA007326","GRSSA007331","GRSSA007343","GRSSA007355","GRSSA007360","GRSSA007372","GRSSA007384","GRSSA007396","GRSSA007401","GRSSA007413","GRSSA007425","GRSSA007430","GRSSA007442","GRSSA007454","GRSSA007466","GRSSA007471","GRSSA007483","GRSSA007495","GRSSA007500","GRSSA007512","GRSSA007524","GRSSA007536","GRSSA007541","GRSSA007553","GRSSA007565","GRSSA007570","GRSSA007582","GRSSA007594","GRSSA007606","GRSSA007611","GRSSA007623","GRSSA007635","GRSSA007640","GRSSA007652","GRSSA007664","GRSSA007676","GRSSA007681","GRSSA007693","GRSSA007705","GRSSA007710","GRSSA007722","GRSSA007734","GRSSA007746","GRSSA007751","GRSSA007763","GRSSA007775","GRSSA007780","GRSSA007792","GRSSA007804","GRSSA007816","GRSSA007821","GRSSA007833","GRSSA007845","GRSSA007850","GRSSA007862","GRSSA007874","GRSSA007886","GRSSA007891","GRSSA007903","GRSSA007915","GRSSA007920","GRSSA007932","GRSSA007944","GRSSA007956","GRSSA007961","GRSSA007973","GRSSA007985","GRSSA007990","GRSSA008002","GRSSA008014","GRSSA008026","GRSSA008031","GRSSA008043","GRSSA008055","GRSSA008060","GRSSA008072","GRSSA008084","GRSSA008096","GRSSA008101","GRSSA008113","GRSSA008125","GRSSA008130","GRSSA008142","GRSSA008154","GRSSA008166","GRSSA008171","GRSSA008183","GRSSA008195","GRSSA008200","GRSSA008212","GRSSA008224","GRSSA008236","GRSSA008241","GRSSA008253","GRSSA008265","GRSSA008270","GRSSA008282","GRSSA008294","GRSSA008306","GRSSA008311","GRSSA008323","GRSSA008335","GRSSA008340","GRSSA008352","GRSSA008364","GRSSA008376","GRSSA008381","GRSSA008393","GRSSA008405","GRSSA008410","GRSSA008422","GRSSA008434","GRSSA008446","GRSSA008451","GRSSA008463","GRSSA008475","GRSSA008480","GRSSA008492","GRSSA008504","GRSSA008516","GRSSA008521","GRSSA008533","GRSSA008545","GRSSA008550","GRSSA008562","GRSSA008574","GRSSA008586","GRSSA008591","GRSSA008603","GRSSA008615","GRSSA008620","GRSSA008644","GRSSA008656","GRSSA008661","GRSSA008673","GRSSA008685","GRSSA008690","GRSSA008702","GRSSA008714","GRSSA008726","GRSSA008731","GRSSA008743","GRSSA008755","GRSSA008760","GRSSA008772","GRSSA008784","GRSSA008796","GRSSA008801","GRSSA008813","GRSSA008825","GRSSA008830","GRSSA008842","GRSSA008854","GRSSA008866","GRSSA008871","GRSSA008883","GRSSA008895","GRSSA008900","GRSSA008912","GRSSA008924","GRSSA008936","GRSSA008941","GRSSA008953","GRSSA008965","GRSSA008970","GRSSA008982","GRSSA008994","GRSSA009006","GRSSA009011","GRSSA009023","GRSSA009035","GRSSA009040","GRSSA009052","GRSSA009064","GRSSA009076","GRSSA009081","GRSSA009105","GRSSA009110","GRSSA009122","GRSSA009134","GRSSA009146","GRSSA009151","GRSSA009163","GRSSA009175","GRSSA009216","GRSSA009221","GRSSA009233","GRSSA009245","GRSSA009274","GRSSA009286","GRSSA009291","GRSSA009315","GRSSA009332","GRSSA009344","GRSSA009361","GRSSA009373","GRSSA009390","GRSSA009426","GRSSA009431","GRSSA009455","GRSSA009472","GRSSA009484","GRSSA009501","GRSSA009513","GRSSA009525","GRSSA009530","GRSSA009542","GRSSA009554","GRSSA009566","GRSSA009595","GRSSA009600","GRSSA009612","GRSSA009624","GRSSA009636","GRSSA009735","GRSSA009740","GRSSA009752","GRSSA009764","GRSSA009776","GRSSA009781","GRSSA009793","GRSSA009805","GRSSA009810","GRSSA009822","GRSSA009834","GRSSA009846","GRSSA009851","GRSSA009863","GRSSA009875","GRSSA009916","GRSSA009921","GRSSA011531","GRSSA011560","GRSSA011573","GRSSA011585","GRSSA011590","GRSSA011602","GRSSA011614","GRSSA011626","GRSSA011631","GRSSA011643","GRSSA011655","GRSSA011660","GRSSA011672","GRSSA011684","GRSSA011696","GRSSA011701","GRSSA011713","GRSSA011725","GRSSA011730","GRSSA011742","GRSSA011754","GRSSA011766","GRSSA011770","GRSSA011782","GRSSA011794","GRSSA011806","GRSSA011823","GRSSA011835","GRSSA011840","GRSSA011852","GRSSA011864","GRSSA011876","GRSSA011881","GRSSA011893","GRSSA011905","GRSSA011910","GRSSA011922","GRSSA011934","GRSSA011946","GRSSA011951","GRSSA011963","GRSSA011975","GRSSA011980","GRSSA011992","GRSSA012016","GRSSA012021","GRSSA012033","GRSSA012045","GRSSA012050","GRSSA012062","GRSSA012074","GRSSA012086","GRSSA012091","GRSSA012103","GRSSA012115","GRSSA012120","GRSSA012132","GRSSA012144","GRSSA012156","GRSSA012161","GRSSA012173","GRSSA012185","GRSSA012190","GRSSA012202","GRSSA012214","GRSSA012226","GRSSA012231","GRSSA012243","GRSSA012255","GRSSA012260","GRSSA012272","GRSSA012284","GRSSA012296","GRSSA012301","GRSSA012313","GRSSA012325","GRSSA012330","GRSSA012342","GRSSA012354","GRSSA012366","GRSSA012371","GRSSA012383","GRSSA012395","GRSSA012400","GRSSA012412","GRSSA012424","GRSSA012436","GRSSA012441","GRSSA012453","GRSSA012465","GRSSA012470","GRSSA012482","GRSSA012494","GRSSA012506","GRSSA012511","GRSSA012523","GRSSA012535","GRSSA012540","GRSSA012552","GRSSA012564","GRSSA012576","GRSSA012581");
} //fin de if($IdEstado == "12")

//Condicion de estado-clues
if($IdEstado == "13"){
	$Clues = array("HGSSA000016","HGSSA000021","HGSSA000033","HGSSA000045","HGSSA000050","HGSSA000062","HGSSA000074","HGSSA000086","HGSSA000091","HGSSA000103","HGSSA000115","HGSSA000120","HGSSA000132","HGSSA000144","HGSSA000156","HGSSA000161","HGSSA000173","HGSSA000185","HGSSA000190","HGSSA000202","HGSSA000214","HGSSA000226","HGSSA000231","HGSSA000243","HGSSA000255","HGSSA000260","HGSSA000272","HGSSA000284","HGSSA000296","HGSSA000301","HGSSA000313","HGSSA000330","HGSSA000342","HGSSA000354","HGSSA000366","HGSSA000371","HGSSA000383","HGSSA000395","HGSSA000400","HGSSA000412","HGSSA000424","HGSSA000436","HGSSA000441","HGSSA000453","HGSSA000465","HGSSA000470","HGSSA000482","HGSSA000494","HGSSA000506","HGSSA000511","HGSSA000523","HGSSA000535","HGSSA000540","HGSSA000552","HGSSA000564","HGSSA000576","HGSSA000581","HGSSA000593","HGSSA000605","HGSSA000610","HGSSA000622","HGSSA000634","HGSSA000646","HGSSA000651","HGSSA000663","HGSSA000675","HGSSA000680","HGSSA000692","HGSSA000704","HGSSA000716","HGSSA000721","HGSSA000733","HGSSA000745","HGSSA000750","HGSSA000762","HGSSA000774","HGSSA000786","HGSSA000791","HGSSA000803","HGSSA000815","HGSSA000820","HGSSA000832","HGSSA000844","HGSSA000856","HGSSA000861","HGSSA000873","HGSSA000885","HGSSA000890","HGSSA000902","HGSSA000914","HGSSA000926","HGSSA000931","HGSSA000943","HGSSA000955","HGSSA000960","HGSSA000972","HGSSA000984","HGSSA000996","HGSSA001001","HGSSA001013","HGSSA001025","HGSSA001030","HGSSA001042","HGSSA001054","HGSSA001066","HGSSA001071","HGSSA001083","HGSSA001095","HGSSA001100","HGSSA001112","HGSSA001124","HGSSA001136","HGSSA001141","HGSSA001153","HGSSA001165","HGSSA001170","HGSSA001182","HGSSA001194","HGSSA001206","HGSSA001211","HGSSA001223","HGSSA001235","HGSSA001240","HGSSA001252","HGSSA001264","HGSSA001276","HGSSA001281","HGSSA001293","HGSSA001305","HGSSA001310","HGSSA001322","HGSSA001334","HGSSA001346","HGSSA001351","HGSSA001363","HGSSA001375","HGSSA001380","HGSSA001392","HGSSA001404","HGSSA001416","HGSSA001421","HGSSA001433","HGSSA001445","HGSSA001450","HGSSA001462","HGSSA001474","HGSSA001486","HGSSA001491","HGSSA001503","HGSSA001515","HGSSA001520","HGSSA001532","HGSSA001544","HGSSA001556","HGSSA001561","HGSSA001573","HGSSA001585","HGSSA001590","HGSSA001602","HGSSA001614","HGSSA001626","HGSSA001631","HGSSA001643","HGSSA001655","HGSSA001660","HGSSA001672","HGSSA001684","HGSSA001696","HGSSA001701","HGSSA001713","HGSSA001725","HGSSA001730","HGSSA001742","HGSSA001754","HGSSA001766","HGSSA001771","HGSSA001783","HGSSA001795","HGSSA001800","HGSSA001812","HGSSA001824","HGSSA001836","HGSSA001841","HGSSA001853","HGSSA001865","HGSSA001870","HGSSA001882","HGSSA001894","HGSSA001906","HGSSA001923","HGSSA001935","HGSSA001940","HGSSA001952","HGSSA001964","HGSSA001976","HGSSA001981","HGSSA001993","HGSSA002005","HGSSA002010","HGSSA002022","HGSSA002034","HGSSA002046","HGSSA002051","HGSSA002063","HGSSA002075","HGSSA002080","HGSSA002092","HGSSA002104","HGSSA002116","HGSSA002121","HGSSA002133","HGSSA002145","HGSSA002150","HGSSA002162","HGSSA002174","HGSSA002186","HGSSA002191","HGSSA002203","HGSSA002215","HGSSA002220","HGSSA002232","HGSSA002244","HGSSA002256","HGSSA002261","HGSSA002273","HGSSA002285","HGSSA002290","HGSSA002302","HGSSA002314","HGSSA002326","HGSSA002331","HGSSA002343","HGSSA002355","HGSSA002360","HGSSA002372","HGSSA002384","HGSSA002396","HGSSA002401","HGSSA002413","HGSSA002425","HGSSA002430","HGSSA002442","HGSSA002454","HGSSA002466","HGSSA002471","HGSSA002483","HGSSA002495","HGSSA002500","HGSSA002512","HGSSA002524","HGSSA002536","HGSSA002541","HGSSA002553","HGSSA002565","HGSSA002570","HGSSA002582","HGSSA002594","HGSSA002611","HGSSA002623","HGSSA002635","HGSSA002640","HGSSA002652","HGSSA002664","HGSSA002676","HGSSA002681","HGSSA002693","HGSSA002705","HGSSA002710","HGSSA002722","HGSSA002734","HGSSA002746","HGSSA002751","HGSSA002763","HGSSA002775","HGSSA002780","HGSSA002792","HGSSA002804","HGSSA002816","HGSSA002821","HGSSA002833","HGSSA002845","HGSSA002850","HGSSA002862","HGSSA002874","HGSSA002886","HGSSA002891","HGSSA002903","HGSSA002920","HGSSA002932","HGSSA002944","HGSSA002956","HGSSA002961","HGSSA002973","HGSSA002985","HGSSA002990","HGSSA003002","HGSSA003014","HGSSA003026","HGSSA003031","HGSSA003043","HGSSA003055","HGSSA003060","HGSSA003072","HGSSA003084","HGSSA003096","HGSSA003101","HGSSA003113","HGSSA003125","HGSSA003130","HGSSA003142","HGSSA003154","HGSSA003166","HGSSA003171","HGSSA003183","HGSSA003195","HGSSA003200","HGSSA003212","HGSSA003224","HGSSA003236","HGSSA003241","HGSSA003253","HGSSA003265","HGSSA003270","HGSSA003282","HGSSA003294","HGSSA003306","HGSSA003311","HGSSA003323","HGSSA003335","HGSSA003340","HGSSA003352","HGSSA003364","HGSSA003376","HGSSA003381","HGSSA003393","HGSSA003405","HGSSA003410","HGSSA003422","HGSSA003434","HGSSA003446","HGSSA003451","HGSSA003463","HGSSA003475","HGSSA003480","HGSSA003492","HGSSA003504","HGSSA003516","HGSSA003521","HGSSA003533","HGSSA003545","HGSSA003550","HGSSA003562","HGSSA003574","HGSSA003586","HGSSA003591","HGSSA003603","HGSSA003615","HGSSA003620","HGSSA003632","HGSSA003644","HGSSA003656","HGSSA003661","HGSSA003673","HGSSA003685","HGSSA003690","HGSSA003702","HGSSA003714","HGSSA003726","HGSSA003731","HGSSA003743","HGSSA003755","HGSSA003760","HGSSA003772","HGSSA003784","HGSSA003796","HGSSA003801","HGSSA003813","HGSSA003825","HGSSA003830","HGSSA003842","HGSSA003854","HGSSA003866","HGSSA003871","HGSSA003883","HGSSA003895","HGSSA003900","HGSSA003912","HGSSA003924","HGSSA003936","HGSSA003941","HGSSA003965","HGSSA003970","HGSSA003982","HGSSA003994","HGSSA004006","HGSSA004011","HGSSA004023","HGSSA004035","HGSSA004040","HGSSA004052","HGSSA004064","HGSSA004076","HGSSA004081","HGSSA004093","HGSSA004105","HGSSA004110","HGSSA004122","HGSSA004134","HGSSA004146","HGSSA004163","HGSSA004175","HGSSA004180","HGSSA004192","HGSSA004204","HGSSA004216","HGSSA004221","HGSSA004233","HGSSA004245","HGSSA004250","HGSSA004262","HGSSA004274","HGSSA004286","HGSSA004291","HGSSA004303","HGSSA004315","HGSSA004320","HGSSA004344","HGSSA004356","HGSSA004361","HGSSA004373","HGSSA004385","HGSSA004390","HGSSA004402","HGSSA004414","HGSSA004426","HGSSA004431","HGSSA004443","HGSSA004455","HGSSA004472","HGSSA004484","HGSSA004496","HGSSA004501","HGSSA004513","HGSSA004525","HGSSA004530","HGSSA004554","HGSSA004566","HGSSA004571","HGSSA004583","HGSSA004595","HGSSA004600","HGSSA004612","HGSSA004624","HGSSA004636","HGSSA004641","HGSSA004653","HGSSA004665","HGSSA004670","HGSSA004682","HGSSA004694","HGSSA004706","HGSSA004711","HGSSA004723","HGSSA004735","HGSSA004740","HGSSA004752","HGSSA004781","HGSSA004793","HGSSA004805","HGSSA004810","HGSSA004822","HGSSA004834","HGSSA004846","HGSSA004851","HGSSA004863","HGSSA004875","HGSSA015294","HGSSA015306","HGSSA015311","HGSSA015323","HGSSA015335","HGSSA015340","HGSSA015352","HGSSA015364","HGSSA015376","HGSSA015381","HGSSA015393","HGSSA015405","HGSSA015410","HGSSA015422","HGSSA015434","HGSSA015446","HGSSA015451","HGSSA015463","HGSSA015475","HGSSA015480","HGSSA015492","HGSSA015503","HGSSA015515","HGSSA015520","HGSSA015532","HGSSA015544","HGSSA015556","HGSSA015561","HGSSA015573","HGSSA015585","HGSSA015590","HGSSA015602","HGSSA015614","HGSSA015626","HGSSA015631","HGSSA015655","HGSSA015660","HGSSA015672","HGSSA015684","HGSSA015696","HGSSA015701","HGSSA015713","HGSSA015725","HGSSA015730","HGSSA015742","HGSSA015754","HGSSA015766","HGSSA015771","HGSSA015783","HGSSA015795","HGSSA015800","HGSSA015812","HGSSA015824","HGSSA015853","HGSSA015894","HGSSA015906","HGSSA015923","HGSSA015935","HGSSA015940","HGSSA015952","HGSSA015964","HGSSA015976","HGSSA015981","HGSSA015993","HGSSA016005","HGSSA016022","HGSSA016034","HGSSA016046","HGSSA016051","HGSSA016063","HGSSA016075","HGSSA016092","HGSSA016104","HGSSA016116","HGSSA016133","HGSSA016145","HGSSA016150","HGSSA016162","HGSSA016186","HGSSA016191","HGSSA016203","HGSSA016232","HGSSA016244","HGSSA016256","HGSSA016261","HGSSA016273","HGSSA016314","HGSSA016326","HGSSA016331","HGSSA016360","HGSSA016372","HGSSA016396","HGSSA016401","HGSSA016413","HGSSA016425","HGSSA016442","HGSSA016454","HGSSA016466","HGSSA016471","HGSSA016483","HGSSA016495","HGSSA016500","HGSSA016512","HGSSA016524","HGSSA016536","HGSSA016541","HGSSA016553","HGSSA016565","HGSSA016570","HGSSA016582","HGSSA016594","HGSSA016606","HGSSA016611","HGSSA016676","HGSSA016681","HGSSA016705","HGSSA016710","HGSSA016722","HGSSA016746","HGSSA016751","HGSSA016763","HGSSA016775","HGSSA016780","HGSSA016821","HGSSA016850","HGSSA016862","HGSSA016886","HGSSA016891","HGSSA016903","HGSSA016915","HGSSA016920","HGSSA016932","HGSSA016961","HGSSA016973","HGSSA016985","HGSSA016990","HGSSA017031","HGSSA017043","HGSSA017055","HGSSA017060","HGSSA017084","HGSSA017096","HGSSA017101","HGSSA017113","HGSSA017125","HGSSA017142","HGSSA017154","HGSSA017166","HGSSA017195","HGSSA017200","HGSSA017212","HGSSA017241","HGSSA017282","HGSSA017306","HGSSA017323","HGSSA017335","HGSSA017340","HGSSA017352","HGSSA017364","HGSSA017376","HGSSA017381","HGSSA017393","HGSSA017405","HGSSA017410","HGSSA017422","HGSSA017434","HGSSA017446","HGSSA017451","HGSSA017475","HGSSA017480","HGSSA017492","HGSSA017516","HGSSA017521","HGSSA017545","HGSSA017550","HGSSA017562","HGSSA017574","HGSSA017591","HGSSA017603","HGSSA017615","HGSSA017644","HGSSA017656","HGSSA017661","HGSSA017673","HGSSA017685","HGSSA017690","HGSSA017702","HGSSA017714","HGSSA017726","HGSSA017731","HGSSA017743","HGSSA017755","HGSSA017760","HGSSA017772","HGSSA017784","HGSSA017796","HGSSA017801","HGSSA017813","HGSSA017825","HGSSA017830","HGSSA017842","HGSSA017854","HGSSA017866","HGSSA017871","HGSSA017883","HGSSA017895","HGSSA017900","HGSSA017912","HGSSA017924","HGSSA017936","HGSSA017941","HGSSA017953","HGSSA017965","HGSSA017970","HGSSA017982","HGSSA017994");
} //fin de if($IdEstado == "13")

//Condicion de estado-clues
if($IdEstado == "14"){
	$Clues = array("JCSSA000013","JCSSA000025","JCSSA000030","JCSSA000042","JCSSA000066","JCSSA000071","JCSSA000083","JCSSA000095","JCSSA000100","JCSSA000112","JCSSA000124","JCSSA000136","JCSSA000141","JCSSA000153","JCSSA000165","JCSSA000170","JCSSA000182","JCSSA000206","JCSSA000211","JCSSA000223","JCSSA000235","JCSSA000240","JCSSA000252","JCSSA000264","JCSSA000276","JCSSA000281","JCSSA000293","JCSSA000305","JCSSA000310","JCSSA000322","JCSSA000334","JCSSA000346","JCSSA000351","JCSSA000363","JCSSA000375","JCSSA000380","JCSSA000392","JCSSA000404","JCSSA000416","JCSSA000421","JCSSA000433","JCSSA000445","JCSSA000450","JCSSA000462","JCSSA000474","JCSSA000486","JCSSA000491","JCSSA000503","JCSSA000515","JCSSA000520","JCSSA000532","JCSSA000544","JCSSA000556","JCSSA000561","JCSSA000573","JCSSA000585","JCSSA000590","JCSSA000602","JCSSA000614","JCSSA000626","JCSSA000631","JCSSA000643","JCSSA000655","JCSSA000660","JCSSA000672","JCSSA000684","JCSSA000696","JCSSA000701","JCSSA000713","JCSSA000725","JCSSA000730","JCSSA000742","JCSSA000754","JCSSA000766","JCSSA000771","JCSSA000783","JCSSA000795","JCSSA000800","JCSSA000812","JCSSA000836","JCSSA000841","JCSSA000853","JCSSA000865","JCSSA000870","JCSSA000882","JCSSA000906","JCSSA000911","JCSSA000935","JCSSA000940","JCSSA000952","JCSSA000964","JCSSA000976","JCSSA000981","JCSSA000993","JCSSA001005","JCSSA001010","JCSSA001022","JCSSA001034","JCSSA001046","JCSSA001051","JCSSA001063","JCSSA001075","JCSSA001116","JCSSA001121","JCSSA001133","JCSSA001145","JCSSA001150","JCSSA001162","JCSSA001174","JCSSA001186","JCSSA001191","JCSSA001203","JCSSA001215","JCSSA001220","JCSSA001232","JCSSA001244","JCSSA001256","JCSSA001261","JCSSA001273","JCSSA001285","JCSSA001290","JCSSA001302","JCSSA001314","JCSSA001326","JCSSA001331","JCSSA001384","JCSSA001396","JCSSA001401","JCSSA001413","JCSSA001425","JCSSA001430","JCSSA001442","JCSSA001454","JCSSA001466","JCSSA001471","JCSSA001483","JCSSA001495","JCSSA001500","JCSSA001512","JCSSA001524","JCSSA001536","JCSSA001541","JCSSA001553","JCSSA001565","JCSSA001570","JCSSA001582","JCSSA001594","JCSSA001606","JCSSA001611","JCSSA001623","JCSSA001635","JCSSA001640","JCSSA001652","JCSSA001664","JCSSA001676","JCSSA001681","JCSSA001693","JCSSA001705","JCSSA001710","JCSSA001722","JCSSA001734","JCSSA001746","JCSSA001751","JCSSA001763","JCSSA001775","JCSSA001780","JCSSA001792","JCSSA001804","JCSSA001816","JCSSA001821","JCSSA001833","JCSSA001845","JCSSA001850","JCSSA001862","JCSSA001874","JCSSA001886","JCSSA001891","JCSSA001903","JCSSA001915","JCSSA001920","JCSSA001932","JCSSA001944","JCSSA001956","JCSSA001961","JCSSA001973","JCSSA001985","JCSSA001990","JCSSA002002","JCSSA002014","JCSSA002026","JCSSA002031","JCSSA002043","JCSSA002055","JCSSA002060","JCSSA002072","JCSSA002084","JCSSA002101","JCSSA002113","JCSSA002125","JCSSA002130","JCSSA002142","JCSSA002154","JCSSA002166","JCSSA002171","JCSSA002183","JCSSA002195","JCSSA002200","JCSSA002212","JCSSA002224","JCSSA002236","JCSSA002241","JCSSA002253","JCSSA002265","JCSSA002270","JCSSA002282","JCSSA002294","JCSSA002306","JCSSA002311","JCSSA002323","JCSSA002335","JCSSA002340","JCSSA002352","JCSSA002364","JCSSA002376","JCSSA002381","JCSSA002393","JCSSA002405","JCSSA002410","JCSSA002422","JCSSA002434","JCSSA002446","JCSSA002451","JCSSA002463","JCSSA002475","JCSSA002480","JCSSA002492","JCSSA002504","JCSSA002516","JCSSA002521","JCSSA002533","JCSSA002545","JCSSA002550","JCSSA002562","JCSSA002574","JCSSA002586","JCSSA002603","JCSSA002615","JCSSA002620","JCSSA002632","JCSSA002644","JCSSA002656","JCSSA002661","JCSSA002673","JCSSA002685","JCSSA002690","JCSSA002702","JCSSA002726","JCSSA002731","JCSSA002743","JCSSA002755","JCSSA002772","JCSSA002784","JCSSA002796","JCSSA002801","JCSSA002813","JCSSA002825","JCSSA002830","JCSSA002842","JCSSA002854","JCSSA002866","JCSSA002871","JCSSA002883","JCSSA002895","JCSSA002900","JCSSA002912","JCSSA002924","JCSSA002936","JCSSA002941","JCSSA002953","JCSSA002965","JCSSA002970","JCSSA002982","JCSSA002994","JCSSA003006","JCSSA003011","JCSSA003023","JCSSA003035","JCSSA003040","JCSSA003052","JCSSA003064","JCSSA003076","JCSSA003081","JCSSA003093","JCSSA003105","JCSSA003110","JCSSA003122","JCSSA003134","JCSSA003146","JCSSA003151","JCSSA003163","JCSSA003175","JCSSA003180","JCSSA003192","JCSSA003204","JCSSA003216","JCSSA003221","JCSSA003233","JCSSA003245","JCSSA003250","JCSSA003262","JCSSA003274","JCSSA003286","JCSSA003291","JCSSA003303","JCSSA003315","JCSSA003320","JCSSA003332","JCSSA003344","JCSSA003356","JCSSA003361","JCSSA003373","JCSSA003385","JCSSA003390","JCSSA003402","JCSSA003414","JCSSA003426","JCSSA003431","JCSSA003443","JCSSA003455","JCSSA003460","JCSSA003472","JCSSA003484","JCSSA003496","JCSSA003501","JCSSA003513","JCSSA003525","JCSSA003530","JCSSA003542","JCSSA003554","JCSSA003566","JCSSA003571","JCSSA003583","JCSSA003595","JCSSA003600","JCSSA003612","JCSSA003624","JCSSA003636","JCSSA003641","JCSSA003653","JCSSA003665","JCSSA003670","JCSSA003694","JCSSA003706","JCSSA003711","JCSSA003723","JCSSA003735","JCSSA003740","JCSSA003752","JCSSA003764","JCSSA003776","JCSSA003781","JCSSA003793","JCSSA003805","JCSSA003810","JCSSA003822","JCSSA003846","JCSSA003863","JCSSA003875","JCSSA003880","JCSSA003892","JCSSA003904","JCSSA003916","JCSSA003921","JCSSA003933","JCSSA003945","JCSSA003950","JCSSA003962","JCSSA003974","JCSSA003986","JCSSA003991","JCSSA004003","JCSSA004015","JCSSA004020","JCSSA004032","JCSSA004044","JCSSA004056","JCSSA004061","JCSSA004073","JCSSA004085","JCSSA004090","JCSSA004102","JCSSA004114","JCSSA004126","JCSSA004131","JCSSA004143","JCSSA004155","JCSSA004160","JCSSA004172","JCSSA004184","JCSSA004196","JCSSA004201","JCSSA004213","JCSSA004225","JCSSA004230","JCSSA004242","JCSSA004266","JCSSA004271","JCSSA004283","JCSSA004295","JCSSA004300","JCSSA004312","JCSSA004324","JCSSA004336","JCSSA004341","JCSSA004353","JCSSA004365","JCSSA004370","JCSSA004382","JCSSA004394","JCSSA004406","JCSSA004411","JCSSA004423","JCSSA004435","JCSSA004440","JCSSA004452","JCSSA004464","JCSSA004476","JCSSA004481","JCSSA004493","JCSSA004505","JCSSA004510","JCSSA004522","JCSSA004534","JCSSA004546","JCSSA004551","JCSSA004563","JCSSA004575","JCSSA004580","JCSSA004592","JCSSA004604","JCSSA004616","JCSSA004621","JCSSA004633","JCSSA004645","JCSSA004650","JCSSA004662","JCSSA004674","JCSSA004686","JCSSA004691","JCSSA004703","JCSSA004715","JCSSA004720","JCSSA004732","JCSSA004744","JCSSA004756","JCSSA004761","JCSSA004773","JCSSA004785","JCSSA004790","JCSSA004802","JCSSA004814","JCSSA004826","JCSSA004831","JCSSA004843","JCSSA004855","JCSSA004860","JCSSA004872","JCSSA004884","JCSSA004896","JCSSA004913","JCSSA004925","JCSSA004930","JCSSA004942","JCSSA004954","JCSSA004983","JCSSA004995","JCSSA005000","JCSSA005012","JCSSA005024","JCSSA005036","JCSSA005041","JCSSA005053","JCSSA005065","JCSSA005070","JCSSA005082","JCSSA005094","JCSSA005106","JCSSA005111","JCSSA005123","JCSSA005135","JCSSA005140","JCSSA005164","JCSSA005176","JCSSA005181","JCSSA005193","JCSSA005205","JCSSA005210","JCSSA005222","JCSSA005234","JCSSA005246","JCSSA005251","JCSSA005263","JCSSA005275","JCSSA005280","JCSSA005292","JCSSA005304","JCSSA005316","JCSSA005321","JCSSA005333","JCSSA005345","JCSSA005350","JCSSA005362","JCSSA005374","JCSSA005386","JCSSA005391","JCSSA005403","JCSSA005415","JCSSA005420","JCSSA005432","JCSSA005444","JCSSA005456","JCSSA005461","JCSSA005473","JCSSA005485","JCSSA005490","JCSSA005502","JCSSA005514","JCSSA005526","JCSSA005531","JCSSA005543","JCSSA005555","JCSSA005560","JCSSA005572","JCSSA005584","JCSSA005596","JCSSA005601","JCSSA005613","JCSSA005625","JCSSA005630","JCSSA005642","JCSSA005654","JCSSA005666","JCSSA005671","JCSSA005683","JCSSA005695","JCSSA005700","JCSSA005712","JCSSA005724","JCSSA005736","JCSSA005741","JCSSA005753","JCSSA005765","JCSSA005770","JCSSA005782","JCSSA005806","JCSSA005811","JCSSA005823","JCSSA005835","JCSSA005840","JCSSA005852","JCSSA005864","JCSSA005876","JCSSA005881","JCSSA005893","JCSSA005905","JCSSA005910","JCSSA005922","JCSSA005934","JCSSA005946","JCSSA005951","JCSSA005963","JCSSA005975","JCSSA005980","JCSSA005992","JCSSA006004","JCSSA006016","JCSSA006021","JCSSA006033","JCSSA006045","JCSSA006050","JCSSA006062","JCSSA006074","JCSSA006086","JCSSA006091","JCSSA006103","JCSSA006115","JCSSA006120","JCSSA006132","JCSSA006144","JCSSA006156","JCSSA006161","JCSSA006173","JCSSA006185","JCSSA006190","JCSSA006202","JCSSA006214","JCSSA006226","JCSSA006231","JCSSA006243","JCSSA006255","JCSSA006260","JCSSA006272","JCSSA006284","JCSSA006296","JCSSA006301","JCSSA006313","JCSSA006325","JCSSA006330","JCSSA006342","JCSSA006354","JCSSA006366","JCSSA006371","JCSSA006383","JCSSA006395","JCSSA006400","JCSSA006412","JCSSA006424","JCSSA006436","JCSSA006441","JCSSA006453","JCSSA006465","JCSSA006470","JCSSA006482","JCSSA006494","JCSSA006506","JCSSA006511","JCSSA006523","JCSSA006535","JCSSA006540","JCSSA006552","JCSSA006564","JCSSA006576","JCSSA006581","JCSSA006593","JCSSA006605","JCSSA006610","JCSSA006622","JCSSA006634","JCSSA006646","JCSSA006651","JCSSA006663","JCSSA006675","JCSSA006680","JCSSA006692","JCSSA006704","JCSSA006716","JCSSA006721","JCSSA006733","JCSSA006745","JCSSA006750","JCSSA006762","JCSSA006774","JCSSA006786","JCSSA006791","JCSSA006803","JCSSA006815","JCSSA006820","JCSSA006832","JCSSA006844","JCSSA006856","JCSSA006861","JCSSA006873","JCSSA006885","JCSSA006890","JCSSA006902","JCSSA006914","JCSSA006926","JCSSA006931","JCSSA006943","JCSSA006955","JCSSA006960","JCSSA006972","JCSSA006984","JCSSA006996","JCSSA007001","JCSSA007013","JCSSA007030","JCSSA007042","JCSSA007054","JCSSA007066","JCSSA007083","JCSSA007095","JCSSA007100","JCSSA007112","JCSSA007124","JCSSA007136","JCSSA007141","JCSSA007153","JCSSA007165","JCSSA007170","JCSSA007182","JCSSA007194","JCSSA007206","JCSSA007211","JCSSA007223","JCSSA007235","JCSSA007240","JCSSA007252","JCSSA007264","JCSSA007276","JCSSA007281","JCSSA007293","JCSSA007305","JCSSA007310","JCSSA007322","JCSSA007334","JCSSA007346","JCSSA007351","JCSSA007363","JCSSA007375","JCSSA007380","JCSSA007392","JCSSA007404","JCSSA007416","JCSSA007421","JCSSA007433","JCSSA007445","JCSSA007450","JCSSA007462","JCSSA007474","JCSSA007486","JCSSA007491","JCSSA007503","JCSSA007515","JCSSA007520","JCSSA007532","JCSSA007544","JCSSA007556","JCSSA007561","JCSSA007573","JCSSA007585","JCSSA007590","JCSSA007602","JCSSA007614","JCSSA007626","JCSSA007631","JCSSA007655","JCSSA007660","JCSSA007672","JCSSA007684","JCSSA007696","JCSSA007701","JCSSA007713","JCSSA007725","JCSSA007730","JCSSA007742","JCSSA007754","JCSSA007766","JCSSA007771","JCSSA007783","JCSSA007795","JCSSA007800","JCSSA007824","JCSSA007836","JCSSA007841","JCSSA007853","JCSSA007865","JCSSA012596","JCSSA012601","JCSSA012613","JCSSA012626","JCSSA012631","JCSSA012643","JCSSA012655","JCSSA012660","JCSSA012672","JCSSA012684","JCSSA012696","JCSSA012701","JCSSA012713","JCSSA012725","JCSSA012730","JCSSA012742","JCSSA012754","JCSSA012766","JCSSA012771","JCSSA012783","JCSSA012795","JCSSA012800","JCSSA012812","JCSSA012824","JCSSA012836","JCSSA012841","JCSSA012853","JCSSA012865","JCSSA012870","JCSSA012882","JCSSA012894","JCSSA012906","JCSSA012911","JCSSA012923","JCSSA012935","JCSSA012940","JCSSA012952","JCSSA012964","JCSSA012976","JCSSA012981","JCSSA012992","JCSSA013004","JCSSA013016","JCSSA013021","JCSSA013033","JCSSA013045","JCSSA013050","JCSSA013062","JCSSA013074","JCSSA013086","JCSSA013091","JCSSA013103","JCSSA013115","JCSSA013120","JCSSA013132","JCSSA013144","JCSSA013156","JCSSA013161","JCSSA013173","JCSSA013185","JCSSA013190","JCSSA013202","JCSSA013214","JCSSA013226","JCSSA013231","JCSSA013243","JCSSA013255","JCSSA013260","JCSSA013272","JCSSA013284","JCSSA013296","JCSSA013301","JCSSA013313","JCSSA013325","JCSSA013330","JCSSA013342","JCSSA013354","JCSSA013366","JCSSA013371","JCSSA013383","JCSSA013395","JCSSA013400","JCSSA013412","JCSSA013424","JCSSA013436","JCSSA013441","JCSSA013453","JCSSA013465","JCSSA013470","JCSSA013482","JCSSA013494","JCSSA013506","JCSSA013511","JCSSA013523","JCSSA013535","JCSSA013540","JCSSA013552","JCSSA013564","JCSSA013576","JCSSA013581","JCSSA013593","JCSSA013605","JCSSA013610","JCSSA013622","JCSSA013634","JCSSA013646","JCSSA013651","JCSSA013663","JCSSA013675","JCSSA013680","JCSSA013692","JCSSA013704","JCSSA013716","JCSSA013721","JCSSA013733","JCSSA013745","JCSSA013750","JCSSA013762","JCSSA013774","JCSSA013786","JCSSA013791","JCSSA013803","JCSSA013815","JCSSA013820","JCSSA013832","JCSSA013856");
} //fin de if($IdEstado == "14")

//Condicion de estado-clues
if($IdEstado == "15"){
	$Clues = array("MCSSA000014","MCSSA000026","MCSSA000031","MCSSA000043","MCSSA000055","MCSSA000060","MCSSA000072","MCSSA000084","MCSSA000096","MCSSA000101","MCSSA000113","MCSSA000125","MCSSA000130","MCSSA000142","MCSSA000154","MCSSA000166","MCSSA000171","MCSSA000183","MCSSA000195","MCSSA000200","MCSSA000212","MCSSA000224","MCSSA000236","MCSSA000241","MCSSA000253","MCSSA000265","MCSSA000270","MCSSA000282","MCSSA000294","MCSSA000306","MCSSA000311","MCSSA000323","MCSSA000335","MCSSA000340","MCSSA000352","MCSSA000376","MCSSA000381","MCSSA000393","MCSSA000405","MCSSA000410","MCSSA000422","MCSSA000434","MCSSA000446","MCSSA000463","MCSSA000475","MCSSA000480","MCSSA000492","MCSSA000516","MCSSA000521","MCSSA000533","MCSSA000545","MCSSA000550","MCSSA000562","MCSSA000574","MCSSA000586","MCSSA000591","MCSSA000603","MCSSA000615","MCSSA000632","MCSSA000644","MCSSA000656","MCSSA000661","MCSSA000673","MCSSA000685","MCSSA000702","MCSSA000726","MCSSA000731","MCSSA000755","MCSSA000760","MCSSA000772","MCSSA000784","MCSSA000796","MCSSA000801","MCSSA000813","MCSSA000825","MCSSA000830","MCSSA000842","MCSSA000854","MCSSA000866","MCSSA000871","MCSSA000883","MCSSA000895","MCSSA000900","MCSSA000912","MCSSA000924","MCSSA000936","MCSSA000941","MCSSA000953","MCSSA000965","MCSSA000970","MCSSA000982","MCSSA000994","MCSSA001011","MCSSA001023","MCSSA001035","MCSSA001040","MCSSA001064","MCSSA001081","MCSSA001093","MCSSA001110","MCSSA001146","MCSSA001151","MCSSA001163","MCSSA001175","MCSSA001180","MCSSA001192","MCSSA001204","MCSSA001216","MCSSA001221","MCSSA001233","MCSSA001245","MCSSA001250","MCSSA001262","MCSSA001274","MCSSA001286","MCSSA001291","MCSSA001303","MCSSA001315","MCSSA001320","MCSSA001332","MCSSA001344","MCSSA001356","MCSSA001361","MCSSA001373","MCSSA001385","MCSSA001390","MCSSA001402","MCSSA001414","MCSSA001426","MCSSA001431","MCSSA001443","MCSSA001455","MCSSA001460","MCSSA001472","MCSSA001484","MCSSA001496","MCSSA001513","MCSSA001525","MCSSA001530","MCSSA001542","MCSSA001554","MCSSA001566","MCSSA001571","MCSSA001583","MCSSA001595","MCSSA001600","MCSSA001612","MCSSA001624","MCSSA001636","MCSSA001665","MCSSA001670","MCSSA001682","MCSSA001694","MCSSA001706","MCSSA001711","MCSSA001723","MCSSA001735","MCSSA001740","MCSSA001752","MCSSA001764","MCSSA001776","MCSSA001781","MCSSA001793","MCSSA001805","MCSSA001810","MCSSA001822","MCSSA001834","MCSSA001846","MCSSA001851","MCSSA001863","MCSSA001875","MCSSA001880","MCSSA001892","MCSSA001904","MCSSA001916","MCSSA001921","MCSSA001933","MCSSA001945","MCSSA001950","MCSSA001962","MCSSA001974","MCSSA001986","MCSSA001991","MCSSA002003","MCSSA002015","MCSSA002020","MCSSA002032","MCSSA002044","MCSSA002056","MCSSA002061","MCSSA002073","MCSSA002085","MCSSA002090","MCSSA002102","MCSSA002114","MCSSA002126","MCSSA002131","MCSSA002143","MCSSA002155","MCSSA002160","MCSSA002172","MCSSA002184","MCSSA002196","MCSSA002213","MCSSA002225","MCSSA002230","MCSSA002242","MCSSA002254","MCSSA002266","MCSSA002271","MCSSA002283","MCSSA002295","MCSSA002300","MCSSA002312","MCSSA002324","MCSSA002336","MCSSA002341","MCSSA002353","MCSSA002365","MCSSA002370","MCSSA002382","MCSSA002394","MCSSA002406","MCSSA002411","MCSSA002423","MCSSA002440","MCSSA002452","MCSSA002464","MCSSA002476","MCSSA002481","MCSSA002493","MCSSA002505","MCSSA002510","MCSSA002522","MCSSA002534","MCSSA002546","MCSSA002551","MCSSA002575","MCSSA002580","MCSSA002592","MCSSA002604","MCSSA002616","MCSSA002621","MCSSA002633","MCSSA002645","MCSSA002650","MCSSA002662","MCSSA002674","MCSSA002686","MCSSA002691","MCSSA002703","MCSSA002715","MCSSA002720","MCSSA002732","MCSSA002744","MCSSA002756","MCSSA002761","MCSSA002773","MCSSA002802","MCSSA002814","MCSSA002826","MCSSA002831","MCSSA002843","MCSSA002855","MCSSA002860","MCSSA002872","MCSSA002896","MCSSA002925","MCSSA002930","MCSSA002954","MCSSA002966","MCSSA002971","MCSSA002983","MCSSA003000","MCSSA003024","MCSSA003036","MCSSA003041","MCSSA003053","MCSSA003065","MCSSA003082","MCSSA003094","MCSSA003106","MCSSA003111","MCSSA003123","MCSSA003135","MCSSA003152","MCSSA003176","MCSSA003181","MCSSA003193","MCSSA003205","MCSSA003210","MCSSA003222","MCSSA003234","MCSSA003246","MCSSA003251","MCSSA003263","MCSSA003275","MCSSA003280","MCSSA003292","MCSSA003304","MCSSA003316","MCSSA003321","MCSSA003333","MCSSA003345","MCSSA003350","MCSSA003386","MCSSA003391","MCSSA003403","MCSSA003415","MCSSA003420","MCSSA003444","MCSSA003456","MCSSA003461","MCSSA003485","MCSSA003490","MCSSA003531","MCSSA003543","MCSSA003555","MCSSA003560","MCSSA003584","MCSSA003596","MCSSA003601","MCSSA003613","MCSSA003625","MCSSA003630","MCSSA003654","MCSSA003666","MCSSA003671","MCSSA003683","MCSSA003695","MCSSA003700","MCSSA003724","MCSSA003736","MCSSA003741","MCSSA003753","MCSSA003765","MCSSA003770","MCSSA003782","MCSSA003794","MCSSA003806","MCSSA003823","MCSSA003840","MCSSA003852","MCSSA003864","MCSSA003876","MCSSA003881","MCSSA003893","MCSSA003905","MCSSA003922","MCSSA003934","MCSSA003946","MCSSA003951","MCSSA003963","MCSSA003975","MCSSA003992","MCSSA004016","MCSSA004021","MCSSA004033","MCSSA004045","MCSSA004050","MCSSA004062","MCSSA004074","MCSSA004086","MCSSA004091","MCSSA004103","MCSSA004115","MCSSA004120","MCSSA004132","MCSSA004144","MCSSA004156","MCSSA004161","MCSSA004173","MCSSA004185","MCSSA004190","MCSSA004202","MCSSA004214","MCSSA004226","MCSSA004231","MCSSA004243","MCSSA004255","MCSSA004260","MCSSA004272","MCSSA004284","MCSSA004296","MCSSA004301","MCSSA004313","MCSSA004325","MCSSA004330","MCSSA004342","MCSSA004354","MCSSA004366","MCSSA004371","MCSSA004383","MCSSA004395","MCSSA004400","MCSSA004412","MCSSA004441","MCSSA004465","MCSSA004470","MCSSA004482","MCSSA004494","MCSSA004506","MCSSA004511","MCSSA004523","MCSSA004535","MCSSA004552","MCSSA004564","MCSSA004576","MCSSA004581","MCSSA004593","MCSSA004605","MCSSA004610","MCSSA004622","MCSSA004634","MCSSA004646","MCSSA004651","MCSSA004663","MCSSA004675","MCSSA004680","MCSSA004692","MCSSA004704","MCSSA004716","MCSSA004721","MCSSA004733","MCSSA004745","MCSSA004750","MCSSA004762","MCSSA004774","MCSSA004786","MCSSA004791","MCSSA004803","MCSSA004815","MCSSA004820","MCSSA004832","MCSSA004856","MCSSA004861","MCSSA004873","MCSSA004885","MCSSA004890","MCSSA004902","MCSSA004914","MCSSA004926","MCSSA004931","MCSSA004943","MCSSA004955","MCSSA004960","MCSSA004972","MCSSA004984","MCSSA004996","MCSSA005001","MCSSA005013","MCSSA005025","MCSSA005030","MCSSA005042","MCSSA005054","MCSSA005066","MCSSA005071","MCSSA005083","MCSSA005095","MCSSA005100","MCSSA005112","MCSSA005124","MCSSA005165","MCSSA005170","MCSSA005206","MCSSA005223","MCSSA005235","MCSSA005276","MCSSA005281","MCSSA005293","MCSSA005305","MCSSA005322","MCSSA005346","MCSSA005351","MCSSA005363","MCSSA005375","MCSSA005380","MCSSA005392","MCSSA005416","MCSSA005421","MCSSA005433","MCSSA005445","MCSSA005450","MCSSA005486","MCSSA005491","MCSSA005503","MCSSA005515","MCSSA005520","MCSSA005532","MCSSA005544","MCSSA005556","MCSSA005561","MCSSA005573","MCSSA005585","MCSSA005602","MCSSA005614","MCSSA005626","MCSSA005631","MCSSA005643","MCSSA005655","MCSSA005672","MCSSA005701","MCSSA005725","MCSSA005730","MCSSA005754","MCSSA005766","MCSSA005771","MCSSA005783","MCSSA005812","MCSSA005824","MCSSA005836","MCSSA005853","MCSSA005865","MCSSA005870","MCSSA005882","MCSSA005894","MCSSA005906","MCSSA005911","MCSSA005923","MCSSA005935","MCSSA005940","MCSSA005952","MCSSA005964","MCSSA005976","MCSSA005981","MCSSA005993","MCSSA006005","MCSSA006010","MCSSA006022","MCSSA006034","MCSSA006046","MCSSA006051","MCSSA006075","MCSSA006080","MCSSA006092","MCSSA006104","MCSSA006116","MCSSA006121","MCSSA006133","MCSSA006145","MCSSA006150","MCSSA006162","MCSSA006174","MCSSA006186","MCSSA006191","MCSSA006203","MCSSA006215","MCSSA006220","MCSSA006232","MCSSA006244","MCSSA006256","MCSSA006261","MCSSA006273","MCSSA006285","MCSSA006290","MCSSA006302","MCSSA006314","MCSSA006326","MCSSA006331","MCSSA006343","MCSSA006355","MCSSA006360","MCSSA006372","MCSSA006384","MCSSA006396","MCSSA006401","MCSSA006413","MCSSA006425","MCSSA006430","MCSSA006454","MCSSA006471","MCSSA006483","MCSSA006495","MCSSA006500","MCSSA006512","MCSSA006524","MCSSA006536","MCSSA006541","MCSSA006565","MCSSA006570","MCSSA006582","MCSSA006594","MCSSA006606","MCSSA006611","MCSSA006623","MCSSA006635","MCSSA006640","MCSSA006652","MCSSA006664","MCSSA006676","MCSSA006681","MCSSA006693","MCSSA006705","MCSSA006710","MCSSA006722","MCSSA006734","MCSSA006746","MCSSA006751","MCSSA006763","MCSSA006775","MCSSA006780","MCSSA006792","MCSSA006804","MCSSA006816","MCSSA006821","MCSSA006833","MCSSA006845","MCSSA006850","MCSSA006862","MCSSA006874","MCSSA006886","MCSSA006891","MCSSA006903","MCSSA006915","MCSSA006920","MCSSA006944","MCSSA006956","MCSSA006961","MCSSA006973","MCSSA006985","MCSSA006990","MCSSA007002","MCSSA007026","MCSSA007031","MCSSA007043","MCSSA007055","MCSSA007060","MCSSA007084","MCSSA007096","MCSSA007101","MCSSA007113","MCSSA007125","MCSSA007130","MCSSA007142","MCSSA007154","MCSSA007166","MCSSA007171","MCSSA007183","MCSSA007195","MCSSA007200","MCSSA007212","MCSSA007224","MCSSA007236","MCSSA007241","MCSSA007253","MCSSA007265","MCSSA007282","MCSSA007294","MCSSA007306","MCSSA007311","MCSSA007323","MCSSA007335","MCSSA007352","MCSSA007364","MCSSA007376","MCSSA007381","MCSSA007393","MCSSA007405","MCSSA007410","MCSSA007422","MCSSA007434","MCSSA007446","MCSSA007463","MCSSA007475","MCSSA007480","MCSSA007492","MCSSA007504","MCSSA007533","MCSSA007545","MCSSA007550","MCSSA007562","MCSSA007574","MCSSA007586","MCSSA007591","MCSSA007603","MCSSA007615","MCSSA007620","MCSSA007661","MCSSA007673","MCSSA007685","MCSSA007690","MCSSA007702","MCSSA007714","MCSSA007726","MCSSA007731","MCSSA007755","MCSSA007760","MCSSA007772","MCSSA007784","MCSSA007796","MCSSA007801","MCSSA007813","MCSSA007825","MCSSA007830","MCSSA007842","MCSSA007854","MCSSA007866","MCSSA007871","MCSSA007900","MCSSA007912","MCSSA007924","MCSSA007936","MCSSA007941","MCSSA007953","MCSSA007965","MCSSA007970","MCSSA007982","MCSSA007994","MCSSA008006","MCSSA008011","MCSSA008023","MCSSA008035","MCSSA008040","MCSSA008052","MCSSA008064","MCSSA008076","MCSSA008081","MCSSA008093","MCSSA008105","MCSSA008110","MCSSA008122","MCSSA008146","MCSSA008163","MCSSA008175","MCSSA008180","MCSSA008192","MCSSA008204","MCSSA008216","MCSSA008221","MCSSA008233","MCSSA008245","MCSSA008250","MCSSA008274","MCSSA008286","MCSSA008291","MCSSA008303","MCSSA008315","MCSSA008320","MCSSA008332","MCSSA008344","MCSSA008356","MCSSA008361","MCSSA008385","MCSSA008390","MCSSA008414","MCSSA008426","MCSSA008431","MCSSA008443","MCSSA008455","MCSSA008460","MCSSA008472","MCSSA008496","MCSSA008501","MCSSA008513","MCSSA008525","MCSSA008530","MCSSA008542","MCSSA008554","MCSSA008566","MCSSA008583","MCSSA008595","MCSSA008600","MCSSA008624","MCSSA008653","MCSSA008670","MCSSA008694","MCSSA008706","MCSSA008723","MCSSA008735","MCSSA008740","MCSSA008752","MCSSA008764","MCSSA008776","MCSSA008781","MCSSA008793","MCSSA008805","MCSSA008810","MCSSA008822","MCSSA008834","MCSSA008846","MCSSA008851","MCSSA008863","MCSSA008875","MCSSA008880","MCSSA008892","MCSSA008904","MCSSA008916","MCSSA008921","MCSSA008945","MCSSA008950","MCSSA008962","MCSSA008974","MCSSA008986","MCSSA008991","MCSSA009003","MCSSA009015","MCSSA009020","MCSSA009032","MCSSA009044","MCSSA009056","MCSSA009073","MCSSA009085","MCSSA009090","MCSSA009114","MCSSA009126","MCSSA009131","MCSSA009143","MCSSA009155","MCSSA009160","MCSSA009172","MCSSA009184","MCSSA009196","MCSSA009213","MCSSA009230","MCSSA009242","MCSSA009254","MCSSA009266","MCSSA009271","MCSSA009283","MCSSA009295","MCSSA009300","MCSSA009312","MCSSA009324","MCSSA009336","MCSSA009341","MCSSA009353","MCSSA009365","MCSSA009370","MCSSA009382","MCSSA009394","MCSSA009406","MCSSA009411","MCSSA009423","MCSSA009435","MCSSA009440","MCSSA009452","MCSSA009464","MCSSA009476","MCSSA009481","MCSSA009493","MCSSA009505","MCSSA009510","MCSSA009522","MCSSA009534","MCSSA009551","MCSSA009563","MCSSA009575","MCSSA009592","MCSSA009604","MCSSA009616","MCSSA009621","MCSSA009645","MCSSA009650","MCSSA009662","MCSSA009674","MCSSA009686","MCSSA009691","MCSSA009703","MCSSA009720","MCSSA009732","MCSSA009756","MCSSA009761","MCSSA009773","MCSSA009814","MCSSA009826","MCSSA009831","MCSSA009843","MCSSA009855","MCSSA009860","MCSSA009872","MCSSA009884","MCSSA009901","MCSSA009925","MCSSA009930","MCSSA009942","MCSSA009954","MCSSA009966","MCSSA009983","MCSSA009995","MCSSA010000","MCSSA010012","MCSSA010024","MCSSA010036","MCSSA010041","MCSSA010053","MCSSA010065","MCSSA010082","MCSSA010111","MCSSA010123","MCSSA010140","MCSSA010152","MCSSA010164","MCSSA010176","MCSSA010181","MCSSA010210","MCSSA010222","MCSSA010234","MCSSA010246","MCSSA010251","MCSSA010263","MCSSA010275","MCSSA010280","MCSSA010292","MCSSA010304","MCSSA010316","MCSSA010321","MCSSA010333","MCSSA010345","MCSSA015233","MCSSA015245","MCSSA015250","MCSSA015262","MCSSA015286","MCSSA015292","MCSSA015304","MCSSA015316","MCSSA015321","MCSSA015333","MCSSA015345","MCSSA015350","MCSSA015362","MCSSA015374","MCSSA015386","MCSSA015391","MCSSA015403","MCSSA015415","MCSSA015420","MCSSA015432","MCSSA015444","MCSSA015456","MCSSA015461","MCSSA015473","MCSSA015485","MCSSA015490","MCSSA015514","MCSSA015526","MCSSA015531","MCSSA015543","MCSSA015555","MCSSA015560","MCSSA015572","MCSSA015584","MCSSA015596","MCSSA015601","MCSSA015613","MCSSA015625","MCSSA015630","MCSSA015642","MCSSA015654","MCSSA015666","MCSSA015671","MCSSA015683","MCSSA015695","MCSSA015700","MCSSA015712","MCSSA015724","MCSSA015736","MCSSA015741","MCSSA015753","MCSSA015765","MCSSA015770","MCSSA015782","MCSSA015794","MCSSA015806","MCSSA015811","MCSSA015823","MCSSA015835","MCSSA015840","MCSSA015852","MCSSA015864","MCSSA015876","MCSSA015904","MCSSA015916","MCSSA015921","MCSSA015933","MCSSA015945","MCSSA015950","MCSSA015962","MCSSA015974","MCSSA015986","MCSSA015991","MCSSA016003","MCSSA016015","MCSSA016020","MCSSA016032","MCSSA016044","MCSSA016061","MCSSA016085","MCSSA016102","MCSSA016126","MCSSA016131","MCSSA016143","MCSSA016155","MCSSA016160","MCSSA016184","MCSSA016213","MCSSA016242","MCSSA016254","MCSSA016283","MCSSA016295","MCSSA016300","MCSSA016312","MCSSA016382","MCSSA016406","MCSSA016411","MCSSA016440","MCSSA016452","MCSSA016464","MCSSA016476","MCSSA016510","MCSSA016534","MCSSA016563","MCSSA016575","MCSSA016592","MCSSA016604","MCSSA016616","MCSSA016621","MCSSA016633","MCSSA016645","MCSSA016650","MCSSA016662","MCSSA016674","MCSSA016691","MCSSA016703","MCSSA016744","MCSSA016756","MCSSA016761","MCSSA016773","MCSSA016790","MCSSA016802","MCSSA016814","MCSSA016826","MCSSA016831","MCSSA016843","MCSSA016855","MCSSA016860","MCSSA016872","MCSSA016884","MCSSA016896","MCSSA016901","MCSSA016913","MCSSA016925","MCSSA016930","MCSSA016942","MCSSA016954","MCSSA016966","MCSSA016971","MCSSA016983","MCSSA016995","MCSSA017000","MCSSA017012","MCSSA017024","MCSSA017036","MCSSA017041","MCSSA017053","MCSSA017065","MCSSA017070","MCSSA017082","MCSSA017094","MCSSA017106","MCSSA017152","MCSSA017181","MCSSA017193","MCSSA017205","MCSSA017222","MCSSA017234","MCSSA017246","MCSSA017263","MCSSA017275","MCSSA017280","MCSSA017292","MCSSA017304","MCSSA017316","MCSSA017321","MCSSA017333","MCSSA017345","MCSSA017350","MCSSA017362","MCSSA017374","MCSSA017386","MCSSA017391","MCSSA017403","MCSSA017415","MCSSA017420","MCSSA017432","MCSSA017444","MCSSA017456","MCSSA017461","MCSSA017473","MCSSA017485","MCSSA017490","MCSSA017502","MCSSA017526","MCSSA017531","MCSSA017543","MCSSA017555","MCSSA017560","MCSSA017572","MCSSA017584","MCSSA017596","MCSSA017601","MCSSA017613","MCSSA017625","MCSSA017630","MCSSA017642","MCSSA017654","MCSSA017666","MCSSA017671","MCSSA017683","MCSSA017695","MCSSA017700","MCSSA017712","MCSSA017724","MCSSA017736","MCSSA017741","MCSSA017753","MCSSA017765","MCSSA017770","MCSSA017782","MCSSA017794","MCSSA017806","MCSSA017811","MCSSA017823","MCSSA017835","MCSSA017840","MCSSA017852","MCSSA017864","MCSSA017876","MCSSA017881","MCSSA017893","MCSSA017905","MCSSA017910","MCSSA017922","MCSSA017934","MCSSA017951","MCSSA017963","MCSSA017975","MCSSA017980","MCSSA017992","MCSSA018004","MCSSA018016","MCSSA018021","MCSSA018033","MCSSA018045","MCSSA018050","MCSSA018062","MCSSA018074","MCSSA018086","MCSSA018091","MCSSA018103","MCSSA018115","MCSSA018120","MCSSA018132","MCSSA018144","MCSSA018156","MCSSA018161","MCSSA018173","MCSSA018185","MCSSA018190","MCSSA018202","MCSSA018214","MCSSA018226","MCSSA018231","MCSSA018243","MCSSA018255","MCSSA018260","MCSSA018272","MCSSA018284","MCSSA018296","MCSSA018301","MCSSA018313","MCSSA018325","MCSSA018330","MCSSA018342","MCSSA018354","MCSSA018366","MCSSA018371","MCSSA018383","MCSSA018395","MCSSA018400","MCSSA018412","MCSSA018424","MCSSA018436","MCSSA018441","MCSSA018453","MCSSA018470","MCSSA018482","MCSSA018494","MCSSA018506","MCSSA018511","MCSSA018523","MCSSA018535","MCSSA018540","MCSSA018552","MCSSA018564","MCSSA018576","MCSSA018581","MCSSA018593","MCSSA018605","MCSSA018610","MCSSA018622","MCSSA018634","MCSSA018646","MCSSA018651","MCSSA018663","MCSSA018675","MCSSA018680","MCSSA018692","MCSSA018704","MCSSA018716","MCSSA018721","MCSSA018733","MCSSA018745","MCSSA018750","MCSSA018762","MCSSA018774","MCSSA018786","MCSSA018791","MCSSA018803","MCSSA018815","MCSSA018820","MCSSA018832","MCSSA018844","MCSSA018856","MCSSA018861","MCSSA018873","MCSSA018885","MCSSA018890","MCSSA018902","MCSSA018914","MCSSA018926","MCSSA018931","MCSSA018943");
} //fin de if($IdEstado == "15")

//Condicion de estado-clues
if($IdEstado == "16"){
	$Clues = array("MNSSA000013","MNSSA000030","MNSSA000054","MNSSA000066","MNSSA000083","MNSSA000095","MNSSA000100","MNSSA000112","MNSSA000124","MNSSA000136","MNSSA000153","MNSSA000165","MNSSA000170","MNSSA000194","MNSSA000206","MNSSA000211","MNSSA000223","MNSSA000235","MNSSA000240","MNSSA000252","MNSSA000264","MNSSA000276","MNSSA000281","MNSSA000293","MNSSA000305","MNSSA000310","MNSSA000322","MNSSA000334","MNSSA000346","MNSSA000351","MNSSA000363","MNSSA000375","MNSSA000404","MNSSA000416","MNSSA000421","MNSSA000433","MNSSA000445","MNSSA000450","MNSSA000462","MNSSA000474","MNSSA000486","MNSSA000491","MNSSA000503","MNSSA000515","MNSSA000532","MNSSA000544","MNSSA000561","MNSSA000573","MNSSA000590","MNSSA000602","MNSSA000614","MNSSA000626","MNSSA000631","MNSSA000643","MNSSA000655","MNSSA000660","MNSSA000672","MNSSA000684","MNSSA000696","MNSSA000701","MNSSA000713","MNSSA000725","MNSSA000730","MNSSA000742","MNSSA000754","MNSSA000766","MNSSA000771","MNSSA000783","MNSSA000800","MNSSA000812","MNSSA000824","MNSSA000836","MNSSA000841","MNSSA000853","MNSSA000865","MNSSA000870","MNSSA000882","MNSSA000894","MNSSA000906","MNSSA000911","MNSSA000923","MNSSA000935","MNSSA000940","MNSSA000952","MNSSA000964","MNSSA000981","MNSSA000993","MNSSA001005","MNSSA001034","MNSSA001046","MNSSA001051","MNSSA001063","MNSSA001080","MNSSA001092","MNSSA001145","MNSSA001150","MNSSA001162","MNSSA001174","MNSSA001186","MNSSA001191","MNSSA001203","MNSSA001220","MNSSA001232","MNSSA001244","MNSSA001256","MNSSA001261","MNSSA001302","MNSSA001314","MNSSA001326","MNSSA001331","MNSSA001343","MNSSA001355","MNSSA001360","MNSSA001372","MNSSA001384","MNSSA001396","MNSSA001401","MNSSA001413","MNSSA001425","MNSSA001430","MNSSA001442","MNSSA001466","MNSSA001471","MNSSA001495","MNSSA001512","MNSSA001524","MNSSA001536","MNSSA001541","MNSSA001553","MNSSA001565","MNSSA001570","MNSSA001582","MNSSA001594","MNSSA001606","MNSSA001652","MNSSA001664","MNSSA001676","MNSSA001681","MNSSA001693","MNSSA001710","MNSSA001722","MNSSA001751","MNSSA001763","MNSSA001775","MNSSA001780","MNSSA001792","MNSSA001804","MNSSA001816","MNSSA001821","MNSSA001833","MNSSA001845","MNSSA001850","MNSSA001862","MNSSA001874","MNSSA001886","MNSSA001891","MNSSA001903","MNSSA001956","MNSSA001961","MNSSA001973","MNSSA001985","MNSSA001990","MNSSA002002","MNSSA002014","MNSSA002026","MNSSA002031","MNSSA002043","MNSSA002055","MNSSA002060","MNSSA002072","MNSSA002096","MNSSA002101","MNSSA002125","MNSSA002130","MNSSA002142","MNSSA002171","MNSSA002183","MNSSA002195","MNSSA002200","MNSSA002212","MNSSA002224","MNSSA002236","MNSSA002241","MNSSA002265","MNSSA002270","MNSSA002294","MNSSA002306","MNSSA002311","MNSSA002323","MNSSA002340","MNSSA002352","MNSSA002376","MNSSA002381","MNSSA002405","MNSSA002410","MNSSA002422","MNSSA002434","MNSSA002446","MNSSA002451","MNSSA002475","MNSSA002480","MNSSA002492","MNSSA002504","MNSSA002521","MNSSA002533","MNSSA002545","MNSSA002550","MNSSA002562","MNSSA002586","MNSSA002615","MNSSA002620","MNSSA002632","MNSSA002656","MNSSA002661","MNSSA002673","MNSSA002690","MNSSA002702","MNSSA002726","MNSSA002731","MNSSA002743","MNSSA002755","MNSSA002760","MNSSA002772","MNSSA002784","MNSSA002796","MNSSA002801","MNSSA002813","MNSSA002825","MNSSA002842","MNSSA002854","MNSSA002866","MNSSA002871","MNSSA002883","MNSSA002900","MNSSA002924","MNSSA002936","MNSSA002953","MNSSA002965","MNSSA002982","MNSSA002994","MNSSA003006","MNSSA003011","MNSSA003023","MNSSA003052","MNSSA003081","MNSSA003093","MNSSA003105","MNSSA003110","MNSSA003122","MNSSA003146","MNSSA003151","MNSSA003175","MNSSA003180","MNSSA003204","MNSSA003216","MNSSA003221","MNSSA003233","MNSSA003245","MNSSA003250","MNSSA003262","MNSSA003274","MNSSA003291","MNSSA003303","MNSSA003315","MNSSA003320","MNSSA003344","MNSSA003356","MNSSA003361","MNSSA003385","MNSSA003390","MNSSA003402","MNSSA003414","MNSSA003431","MNSSA003443","MNSSA003455","MNSSA003460","MNSSA003472","MNSSA003484","MNSSA003496","MNSSA003501","MNSSA003513","MNSSA003525","MNSSA003530","MNSSA003542","MNSSA003554","MNSSA003566","MNSSA003571","MNSSA003583","MNSSA003595","MNSSA003600","MNSSA003612","MNSSA003624","MNSSA003636","MNSSA003653","MNSSA003665","MNSSA003670","MNSSA003682","MNSSA003694","MNSSA003706","MNSSA003711","MNSSA003723","MNSSA003735","MNSSA003764","MNSSA003776","MNSSA003781","MNSSA003793","MNSSA003805","MNSSA003810","MNSSA003822","MNSSA003834","MNSSA003851","MNSSA003875","MNSSA003880","MNSSA003904","MNSSA003916","MNSSA003921","MNSSA003933","MNSSA003945","MNSSA003962","MNSSA003974","MNSSA003986","MNSSA003991","MNSSA004003","MNSSA004020","MNSSA004032","MNSSA004044","MNSSA004085","MNSSA004090","MNSSA004114","MNSSA004126","MNSSA004131","MNSSA004143","MNSSA004155","MNSSA004160","MNSSA004172","MNSSA004184","MNSSA004196","MNSSA004201","MNSSA004213","MNSSA004225","MNSSA004230","MNSSA004242","MNSSA004254","MNSSA004266","MNSSA004271","MNSSA004283","MNSSA004295","MNSSA004300","MNSSA004312","MNSSA004324","MNSSA004336","MNSSA004341","MNSSA004353","MNSSA004365","MNSSA004370","MNSSA004382","MNSSA004394","MNSSA004406","MNSSA004411","MNSSA004423","MNSSA004435","MNSSA004440","MNSSA004452","MNSSA004464","MNSSA004476","MNSSA004481","MNSSA004493","MNSSA004505","MNSSA004510","MNSSA004522","MNSSA004534","MNSSA004546","MNSSA004551","MNSSA004563","MNSSA004580","MNSSA004592","MNSSA004604","MNSSA004616","MNSSA004621","MNSSA004633","MNSSA004645","MNSSA004650","MNSSA004662","MNSSA004674","MNSSA004686","MNSSA004691","MNSSA004703","MNSSA004715","MNSSA004720","MNSSA004732","MNSSA004744","MNSSA004756","MNSSA004761","MNSSA004773","MNSSA004785","MNSSA004790","MNSSA004802","MNSSA004814","MNSSA004826","MNSSA004831","MNSSA004843","MNSSA004855","MNSSA004860","MNSSA004896","MNSSA004901","MNSSA004913","MNSSA004925","MNSSA004930","MNSSA004942","MNSSA004954","MNSSA004966","MNSSA004971","MNSSA004995","MNSSA005000","MNSSA005012","MNSSA005024","MNSSA005036","MNSSA005041","MNSSA005053","MNSSA005065","MNSSA005070","MNSSA005082","MNSSA005094","MNSSA005106","MNSSA005111","MNSSA005123","MNSSA005135","MNSSA005140","MNSSA005152","MNSSA005164","MNSSA005176","MNSSA005193","MNSSA005205","MNSSA005210","MNSSA005222","MNSSA005234","MNSSA005246","MNSSA016043","MNSSA016055","MNSSA016060","MNSSA016072","MNSSA016084","MNSSA016096","MNSSA016102","MNSSA016114","MNSSA016126","MNSSA016131","MNSSA016143","MNSSA016155","MNSSA016160","MNSSA016171","MNSSA016183","MNSSA016195","MNSSA016200","MNSSA016212","MNSSA016224","MNSSA016236","MNSSA016241","MNSSA016253","MNSSA016265","MNSSA016270","MNSSA016282","MNSSA016294","MNSSA016306","MNSSA016311","MNSSA016323","MNSSA016335","MNSSA016340","MNSSA016352","MNSSA016364","MNSSA016393","MNSSA016405","MNSSA016410","MNSSA016422","MNSSA016451","MNSSA016463","MNSSA016475","MNSSA016480","MNSSA016492","MNSSA016504","MNSSA016516","MNSSA016521","MNSSA016533","MNSSA016545","MNSSA016550","MNSSA016562","MNSSA016574","MNSSA016586","MNSSA016591","MNSSA016603","MNSSA016615","MNSSA016620","MNSSA016632","MNSSA016644","MNSSA016656","MNSSA016661","MNSSA016673","MNSSA016685","MNSSA016690","MNSSA016714","MNSSA016726","MNSSA016731","MNSSA016743","MNSSA016755","MNSSA016760","MNSSA016772","MNSSA016784","MNSSA016796","MNSSA016801","MNSSA016813","MNSSA016825","MNSSA016830","MNSSA016842","MNSSA016854","MNSSA016866","MNSSA016871","MNSSA016883","MNSSA016895","MNSSA016900","MNSSA016912","MNSSA016936","MNSSA016941","MNSSA016953","MNSSA016965","MNSSA016970","MNSSA016982","MNSSA016994","MNSSA017006","MNSSA017011","MNSSA017023","MNSSA017035","MNSSA017040","MNSSA017052","MNSSA017064","MNSSA017076","MNSSA017081","MNSSA017093","MNSSA017105","MNSSA017110","MNSSA017122","MNSSA017134","MNSSA017146","MNSSA017151","MNSSA017163","MNSSA017175","MNSSA017180","MNSSA017192","MNSSA017204","MNSSA017216","MNSSA017221","MNSSA017233","MNSSA017245","MNSSA017250","MNSSA017262","MNSSA017274","MNSSA017286","MNSSA017291","MNSSA017303","MNSSA017315","MNSSA017320","MNSSA017332","MNSSA017344","MNSSA017356","MNSSA017361","MNSSA017373","MNSSA017385");
} //fin de if($IdEstado == "16")

//Condicion de estado-clues
if($IdEstado == "17"){
	$Clues = array("MSSSA000022","MSSSA000034","MSSSA000046","MSSSA000051","MSSSA000075","MSSSA000080","MSSSA000092","MSSSA000104","MSSSA000116","MSSSA000121","MSSSA000133","MSSSA000145","MSSSA000150","MSSSA000162","MSSSA000174","MSSSA000186","MSSSA000191","MSSSA000203","MSSSA000215","MSSSA000220","MSSSA000232","MSSSA000256","MSSSA000261","MSSSA000273","MSSSA000290","MSSSA000302","MSSSA000314","MSSSA000326","MSSSA000331","MSSSA000343","MSSSA000355","MSSSA000360","MSSSA000372","MSSSA000384","MSSSA000396","MSSSA000401","MSSSA000413","MSSSA000425","MSSSA000430","MSSSA000442","MSSSA000454","MSSSA000466","MSSSA000471","MSSSA000495","MSSSA000500","MSSSA000512","MSSSA000524","MSSSA000536","MSSSA000541","MSSSA000553","MSSSA000565","MSSSA000570","MSSSA000582","MSSSA000606","MSSSA000611","MSSSA000623","MSSSA000640","MSSSA000652","MSSSA000664","MSSSA000676","MSSSA000681","MSSSA000693","MSSSA000710","MSSSA000734","MSSSA000746","MSSSA000751","MSSSA000763","MSSSA000775","MSSSA000780","MSSSA000792","MSSSA000804","MSSSA000816","MSSSA000821","MSSSA000833","MSSSA000845","MSSSA000850","MSSSA000862","MSSSA000874","MSSSA000886","MSSSA000891","MSSSA000903","MSSSA000915","MSSSA000932","MSSSA000944","MSSSA000956","MSSSA000961","MSSSA000973","MSSSA000985","MSSSA000990","MSSSA001002","MSSSA001031","MSSSA001043","MSSSA001060","MSSSA001072","MSSSA001084","MSSSA001096","MSSSA001101","MSSSA001113","MSSSA001125","MSSSA001142","MSSSA001154","MSSSA001166","MSSSA001171","MSSSA001183","MSSSA001200","MSSSA001212","MSSSA001236","MSSSA001241","MSSSA001253","MSSSA001265","MSSSA001270","MSSSA001282","MSSSA001294","MSSSA001306","MSSSA001311","MSSSA001323","MSSSA001340","MSSSA001376","MSSSA001381","MSSSA001393","MSSSA001405","MSSSA001410","MSSSA001422","MSSSA001434","MSSSA001446","MSSSA001451","MSSSA001463","MSSSA001475","MSSSA001480","MSSSA001492","MSSSA001504","MSSSA001516","MSSSA001521","MSSSA001533","MSSSA001545","MSSSA001550","MSSSA001562","MSSSA001574","MSSSA001586","MSSSA001591","MSSSA001603","MSSSA001615","MSSSA001620","MSSSA001632","MSSSA001661","MSSSA001673","MSSSA001685","MSSSA001690","MSSSA001702","MSSSA001714","MSSSA001726","MSSSA001731","MSSSA001743","MSSSA001755","MSSSA001760","MSSSA001772","MSSSA001784","MSSSA001796","MSSSA001801","MSSSA001813","MSSSA001825","MSSSA001830","MSSSA001842","MSSSA001866","MSSSA001871","MSSSA001883","MSSSA001895","MSSSA001900","MSSSA001912","MSSSA001924","MSSSA001941","MSSSA001953","MSSSA001965","MSSSA001994","MSSSA002006","MSSSA002023","MSSSA002035","MSSSA002040","MSSSA002052","MSSSA002064","MSSSA002076","MSSSA002081","MSSSA002093","MSSSA002105","MSSSA002110","MSSSA002122","MSSSA002134","MSSSA002146","MSSSA002151","MSSSA002164","MSSSA002176","MSSSA002193","MSSSA002205","MSSSA002210","MSSSA002222","MSSSA002234","MSSSA002246","MSSSA002251","MSSSA002275","MSSSA002280","MSSSA002292","MSSSA002303","MSSSA002315","MSSSA002320","MSSSA002332","MSSSA002344","MSSSA002356","MSSSA002361","MSSSA002373","MSSSA002385","MSSSA002390","MSSSA002402","MSSSA002414","MSSSA002426","MSSSA002431","MSSSA002443","MSSSA002455","MSSSA002460","MSSSA002472","MSSSA002484","MSSSA002496","MSSSA002513","MSSSA002525","MSSSA002530","MSSSA002542","MSSSA002554","MSSSA002566","MSSSA002571","MSSSA002583","MSSSA002595","MSSSA002612","MSSSA002624","MSSSA002636","MSSSA002641","MSSSA002653","MSSSA002665","MSSSA002670","MSSSA002682","MSSSA002694","MSSSA002706","MSSSA002711","MSSSA002723","MSSSA002735","MSSSA002740","MSSSA002752","MSSSA002764","MSSSA002776","MSSSA002781","MSSSA002793","MSSSA002805","MSSSA002810","MSSSA002822","MSSSA002834","MSSSA002846","MSSSA002851","MSSSA002863","MSSSA002875","MSSSA002880","MSSSA002892","MSSSA002904","MSSSA002916");
} //fin de if($IdEstado == "17")

//Condicion de estado-clues
if($IdEstado == "18"){
	$Clues = array("NTSSA000013","NTSSA000025","NTSSA000030","NTSSA000042","NTSSA000054","NTSSA000066","NTSSA000071","NTSSA000083","NTSSA000095","NTSSA000100","NTSSA000112","NTSSA000124","NTSSA000136","NTSSA000141","NTSSA000153","NTSSA000165","NTSSA000170","NTSSA000182","NTSSA000194","NTSSA000206","NTSSA000211","NTSSA000223","NTSSA000235","NTSSA000240","NTSSA000252","NTSSA000264","NTSSA000276","NTSSA000281","NTSSA000293","NTSSA000305","NTSSA000310","NTSSA000322","NTSSA000346","NTSSA000351","NTSSA000363","NTSSA000375","NTSSA000416","NTSSA000474","NTSSA000486","NTSSA000491","NTSSA000503","NTSSA000520","NTSSA000532","NTSSA000544","NTSSA000556","NTSSA000561","NTSSA000573","NTSSA000585","NTSSA000590","NTSSA000602","NTSSA000614","NTSSA000626","NTSSA000631","NTSSA000643","NTSSA000655","NTSSA000660","NTSSA000672","NTSSA000684","NTSSA000696","NTSSA000701","NTSSA000713","NTSSA000725","NTSSA000730","NTSSA000742","NTSSA000754","NTSSA000771","NTSSA000783","NTSSA000795","NTSSA000800","NTSSA000812","NTSSA000824","NTSSA000836","NTSSA000841","NTSSA000853","NTSSA000865","NTSSA000870","NTSSA000882","NTSSA000894","NTSSA000906","NTSSA000911","NTSSA000923","NTSSA000935","NTSSA000952","NTSSA000964","NTSSA000976","NTSSA000981","NTSSA001005","NTSSA001010","NTSSA001022","NTSSA001034","NTSSA001046","NTSSA001051","NTSSA001063","NTSSA001075","NTSSA001080","NTSSA001092","NTSSA001104","NTSSA001116","NTSSA001121","NTSSA001133","NTSSA001145","NTSSA001150","NTSSA001162","NTSSA001174","NTSSA001186","NTSSA001203","NTSSA001215","NTSSA001220","NTSSA001232","NTSSA001244","NTSSA001261","NTSSA001273","NTSSA001285","NTSSA001290","NTSSA001302","NTSSA001314","NTSSA001326","NTSSA001331","NTSSA001343","NTSSA001355","NTSSA001360","NTSSA001372","NTSSA001384","NTSSA001396","NTSSA001401","NTSSA001413","NTSSA001425","NTSSA001430","NTSSA001442","NTSSA001454","NTSSA001471","NTSSA001483","NTSSA001495","NTSSA001500","NTSSA001512","NTSSA001524","NTSSA001536","NTSSA001541","NTSSA001553","NTSSA001565","NTSSA001570","NTSSA001582","NTSSA001594","NTSSA001611","NTSSA001623","NTSSA001635","NTSSA001640","NTSSA001652","NTSSA001664","NTSSA001676","NTSSA001681","NTSSA001693","NTSSA001705","NTSSA001710","NTSSA001722","NTSSA001734","NTSSA001746","NTSSA001751","NTSSA001763","NTSSA001775","NTSSA001780","NTSSA001792","NTSSA001804","NTSSA001816","NTSSA001821","NTSSA001833","NTSSA001845","NTSSA001850","NTSSA001862","NTSSA001874","NTSSA001886","NTSSA001891","NTSSA001903","NTSSA001932","NTSSA001956","NTSSA001985","NTSSA001990","NTSSA002002","NTSSA002014","NTSSA002026","NTSSA002031","NTSSA002043","NTSSA002055","NTSSA002060","NTSSA002072","NTSSA002084","NTSSA002096","NTSSA002101","NTSSA002113","NTSSA002125","NTSSA002130","NTSSA002142","NTSSA002154","NTSSA002166","NTSSA002171","NTSSA002183","NTSSA002195","NTSSA002200","NTSSA002212","NTSSA002224","NTSSA002236","NTSSA002241","NTSSA002253","NTSSA002265","NTSSA002270","NTSSA002294","NTSSA002306","NTSSA015064","NTSSA015076","NTSSA015081","NTSSA015093","NTSSA015105","NTSSA015110","NTSSA015122","NTSSA015134","NTSSA015146","NTSSA015151","NTSSA015163","NTSSA015175","NTSSA015192","NTSSA015204","NTSSA015216","NTSSA015220","NTSSA015232","NTSSA015244","NTSSA015256","NTSSA015261","NTSSA015273","NTSSA015285","NTSSA015302","NTSSA015314","NTSSA015326","NTSSA015331","NTSSA015343","NTSSA015355","NTSSA015360","NTSSA015372","NTSSA015384","NTSSA015396","NTSSA015401","NTSSA015413","NTSSA015425","NTSSA015430","NTSSA015442","NTSSA015454","NTSSA015466","NTSSA015471","NTSSA015483","NTSSA015495","NTSSA015500","NTSSA015512","NTSSA015524","NTSSA015536","NTSSA015582","NTSSA015664","NTSSA015676","NTSSA015681","NTSSA015693","NTSSA015705","NTSSA015710","NTSSA015722","NTSSA015734","NTSSA015746","NTSSA015751","NTSSA015763","NTSSA015775","NTSSA015780","NTSSA015792","NTSSA015804","NTSSA015816","NTSSA015821","NTSSA015833","NTSSA015845","NTSSA015850","NTSSA015862","NTSSA015874","NTSSA015886","NTSSA015891","NTSSA015903","NTSSA015915","NTSSA015920","NTSSA015932","NTSSA016031","NTSSA016043","NTSSA016055","NTSSA016060","NTSSA016072","NTSSA016084","NTSSA016096","NTSSA016101","NTSSA016113","NTSSA016125","NTSSA016130","NTSSA016142");
} //fin de if($IdEstado == "18")

//Condicion de estado-clues
if($IdEstado == "19"){
	$Clues = array("NLSSA000015","NLSSA000020","NLSSA000032","NLSSA000044","NLSSA000056","NLSSA000061","NLSSA000073","NLSSA000085","NLSSA000090","NLSSA000102","NLSSA000126","NLSSA000131","NLSSA000143","NLSSA000155","NLSSA000160","NLSSA000172","NLSSA000196","NLSSA000201","NLSSA000213","NLSSA000225","NLSSA000230","NLSSA000242","NLSSA000254","NLSSA000266","NLSSA000271","NLSSA000283","NLSSA000295","NLSSA000300","NLSSA000312","NLSSA000324","NLSSA000336","NLSSA000341","NLSSA000365","NLSSA000370","NLSSA000382","NLSSA000394","NLSSA000406","NLSSA000411","NLSSA000423","NLSSA000435","NLSSA000440","NLSSA000452","NLSSA000464","NLSSA000476","NLSSA000481","NLSSA000493","NLSSA000505","NLSSA000510","NLSSA000522","NLSSA000534","NLSSA000546","NLSSA000551","NLSSA000575","NLSSA000580","NLSSA000592","NLSSA000604","NLSSA000616","NLSSA000621","NLSSA000633","NLSSA000645","NLSSA000650","NLSSA000674","NLSSA000686","NLSSA000691","NLSSA000703","NLSSA000720","NLSSA000732","NLSSA000744","NLSSA000761","NLSSA000773","NLSSA000785","NLSSA000790","NLSSA000802","NLSSA000814","NLSSA000831","NLSSA000843","NLSSA000855","NLSSA000860","NLSSA000884","NLSSA000896","NLSSA000901","NLSSA000913","NLSSA000925","NLSSA000930","NLSSA000942","NLSSA000954","NLSSA000966","NLSSA000971","NLSSA000983","NLSSA000995","NLSSA001000","NLSSA001012","NLSSA001024","NLSSA001036","NLSSA001041","NLSSA001053","NLSSA001065","NLSSA001070","NLSSA001082","NLSSA001094","NLSSA001106","NLSSA001111","NLSSA001123","NLSSA001135","NLSSA001140","NLSSA001152","NLSSA001164","NLSSA001176","NLSSA001181","NLSSA001193","NLSSA001205","NLSSA001210","NLSSA001222","NLSSA001234","NLSSA001246","NLSSA001251","NLSSA001263","NLSSA001275","NLSSA001280","NLSSA001292","NLSSA001304","NLSSA001316","NLSSA001321","NLSSA001333","NLSSA001345","NLSSA001350","NLSSA001362","NLSSA001374","NLSSA001386","NLSSA001391","NLSSA001403","NLSSA001415","NLSSA001420","NLSSA001432","NLSSA001444","NLSSA001456","NLSSA001461","NLSSA001473","NLSSA001485","NLSSA001490","NLSSA001502","NLSSA001514","NLSSA001526","NLSSA001531","NLSSA001543","NLSSA001555","NLSSA001560","NLSSA001584","NLSSA001596","NLSSA001601","NLSSA001625","NLSSA001630","NLSSA001642","NLSSA001654","NLSSA001666","NLSSA001671","NLSSA001683","NLSSA001695","NLSSA001700","NLSSA001712","NLSSA001724","NLSSA001736","NLSSA001741","NLSSA001753","NLSSA001765","NLSSA001770","NLSSA001782","NLSSA001794","NLSSA001806","NLSSA001811","NLSSA001823","NLSSA001835","NLSSA001840","NLSSA001852","NLSSA001864","NLSSA001876","NLSSA001881","NLSSA001893","NLSSA001905","NLSSA001910","NLSSA001922","NLSSA001934","NLSSA001951","NLSSA001963","NLSSA001975","NLSSA001980","NLSSA001992","NLSSA002004","NLSSA002016","NLSSA002021","NLSSA002033","NLSSA002045","NLSSA002050","NLSSA002062","NLSSA002074","NLSSA002086","NLSSA002091","NLSSA002103","NLSSA002115","NLSSA002120","NLSSA002132","NLSSA002144","NLSSA002156","NLSSA002161","NLSSA002173","NLSSA002185","NLSSA002190","NLSSA002202","NLSSA002226","NLSSA002231","NLSSA002243","NLSSA002255","NLSSA002260","NLSSA002272","NLSSA002284","NLSSA002296","NLSSA002301","NLSSA002313","NLSSA002325","NLSSA002330","NLSSA002342","NLSSA002354","NLSSA002366","NLSSA002371","NLSSA002383","NLSSA002395","NLSSA002400","NLSSA002412","NLSSA002424","NLSSA002436","NLSSA002441","NLSSA002453","NLSSA002465","NLSSA002470","NLSSA002482","NLSSA002494","NLSSA002506","NLSSA002511","NLSSA002523","NLSSA002535","NLSSA002540","NLSSA002552","NLSSA002564","NLSSA002576","NLSSA002581","NLSSA002593","NLSSA002605","NLSSA002610","NLSSA002622","NLSSA002634","NLSSA002646","NLSSA002651","NLSSA002663","NLSSA002675","NLSSA002680","NLSSA002692","NLSSA002704","NLSSA002716","NLSSA002721","NLSSA002733","NLSSA002745","NLSSA002750","NLSSA002762","NLSSA002774","NLSSA002786","NLSSA002791","NLSSA002803","NLSSA002815","NLSSA002820","NLSSA002832","NLSSA002856","NLSSA002861","NLSSA002873","NLSSA002890","NLSSA002902","NLSSA002914","NLSSA002926","NLSSA002931","NLSSA002943","NLSSA002955","NLSSA002972","NLSSA002984","NLSSA002996","NLSSA003001","NLSSA003025","NLSSA003030","NLSSA003042","NLSSA003054","NLSSA003066","NLSSA003071","NLSSA003083","NLSSA003100","NLSSA003112","NLSSA003124","NLSSA003136","NLSSA003141","NLSSA003153","NLSSA003165","NLSSA003170","NLSSA003182","NLSSA003194","NLSSA003206","NLSSA003211","NLSSA003223","NLSSA003235","NLSSA003240","NLSSA003252","NLSSA003264","NLSSA003276","NLSSA003281","NLSSA003293","NLSSA003305","NLSSA003310","NLSSA003322","NLSSA003334","NLSSA003346","NLSSA003351","NLSSA003363","NLSSA003375","NLSSA003380","NLSSA003392","NLSSA003404","NLSSA003416","NLSSA003421","NLSSA003433","NLSSA003445","NLSSA003450","NLSSA003462","NLSSA003474","NLSSA003486","NLSSA003491","NLSSA003503","NLSSA003515","NLSSA003520","NLSSA003532","NLSSA003544","NLSSA003556","NLSSA003561","NLSSA003573","NLSSA003585","NLSSA003590","NLSSA003602","NLSSA003614","NLSSA003626","NLSSA003631","NLSSA003643","NLSSA003655","NLSSA003660","NLSSA003672","NLSSA003684","NLSSA003696","NLSSA003701","NLSSA003713","NLSSA003725","NLSSA003730","NLSSA003754","NLSSA003766","NLSSA003771","NLSSA003783","NLSSA003795","NLSSA003800","NLSSA003812","NLSSA003824","NLSSA003836","NLSSA003841","NLSSA003853","NLSSA003865","NLSSA003870","NLSSA003882","NLSSA003894","NLSSA003906","NLSSA003911","NLSSA003923","NLSSA003935","NLSSA003940","NLSSA003952","NLSSA003964","NLSSA003976","NLSSA003981","NLSSA003993","NLSSA004005","NLSSA004010","NLSSA004034","NLSSA004046","NLSSA004051","NLSSA004063","NLSSA004075","NLSSA004080","NLSSA004092","NLSSA004104","NLSSA004116","NLSSA004121","NLSSA004145","NLSSA004150","NLSSA004162","NLSSA004186","NLSSA004191","NLSSA004203","NLSSA004215","NLSSA004220","NLSSA004232","NLSSA004244","NLSSA004256","NLSSA004261","NLSSA004273","NLSSA004285","NLSSA004290","NLSSA004302","NLSSA004314","NLSSA004326","NLSSA004331","NLSSA004343","NLSSA004355","NLSSA004360","NLSSA004372","NLSSA004384","NLSSA004396","NLSSA004401","NLSSA004413","NLSSA004425","NLSSA004430","NLSSA004442","NLSSA004454","NLSSA004466","NLSSA004471","NLSSA004495","NLSSA004512","NLSSA004524","NLSSA004536","NLSSA004541","NLSSA004553","NLSSA004565","NLSSA004570","NLSSA004582","NLSSA004606","NLSSA004664","NLSSA004676","NLSSA004681","NLSSA004693","NLSSA004751","NLSSA013991","NLSSA014003","NLSSA014015","NLSSA014020","NLSSA014032","NLSSA014045","NLSSA014050","NLSSA014062","NLSSA014074","NLSSA014086","NLSSA014091","NLSSA014103","NLSSA014115","NLSSA014120","NLSSA014144","NLSSA014156","NLSSA014161","NLSSA014173","NLSSA014185","NLSSA014190","NLSSA014202","NLSSA014214","NLSSA014226","NLSSA014231","NLSSA014243","NLSSA014255","NLSSA014260","NLSSA014271","NLSSA014283","NLSSA014295","NLSSA014300","NLSSA014324","NLSSA014336","NLSSA014341","NLSSA014353","NLSSA014365","NLSSA014370","NLSSA014382","NLSSA014394","NLSSA014406","NLSSA014411","NLSSA014423","NLSSA014435","NLSSA014440","NLSSA014452","NLSSA014464","NLSSA014476","NLSSA014493","NLSSA014505","NLSSA014510","NLSSA014522","NLSSA014534","NLSSA014546","NLSSA014551","NLSSA014563","NLSSA014575","NLSSA014580","NLSSA014592","NLSSA014604","NLSSA014616","NLSSA014621","NLSSA014633","NLSSA014645","NLSSA014650","NLSSA014662","NLSSA014674","NLSSA014686","NLSSA014691","NLSSA014703","NLSSA014715","NLSSA014720","NLSSA014732","NLSSA014744","NLSSA014756","NLSSA014761","NLSSA014773","NLSSA014785","NLSSA014790","NLSSA014802","NLSSA014814","NLSSA014826","NLSSA014831","NLSSA014843","NLSSA014855","NLSSA014860","NLSSA014872","NLSSA014884","NLSSA014896","NLSSA014901","NLSSA014913","NLSSA014925","NLSSA014930","NLSSA014942","NLSSA014954","NLSSA014966","NLSSA014971","NLSSA014983","NLSSA014995","NLSSA015000","NLSSA015012","NLSSA015024","NLSSA015036","NLSSA015041");
} //fin de if($IdEstado == "19")

//Condicion de estado-clues
if($IdEstado == "20"){
	$Clues = array("OCSSA000010","OCSSA000022","OCSSA000034","OCSSA000046","OCSSA000051","OCSSA000063","OCSSA000075","OCSSA000080","OCSSA000092","OCSSA000104","OCSSA000116","OCSSA000121","OCSSA000133","OCSSA000145","OCSSA000150","OCSSA000162","OCSSA000174","OCSSA000186","OCSSA000191","OCSSA000203","OCSSA000215","OCSSA000220","OCSSA000232","OCSSA000244","OCSSA000256","OCSSA000261","OCSSA000273","OCSSA000285","OCSSA000290","OCSSA000302","OCSSA000314","OCSSA000326","OCSSA000331","OCSSA000343","OCSSA000355","OCSSA000360","OCSSA000372","OCSSA000384","OCSSA000396","OCSSA000413","OCSSA000425","OCSSA000430","OCSSA000454","OCSSA000466","OCSSA000471","OCSSA000483","OCSSA000495","OCSSA000500","OCSSA000512","OCSSA000524","OCSSA000536","OCSSA000541","OCSSA000553","OCSSA000565","OCSSA000570","OCSSA000582","OCSSA000594","OCSSA000606","OCSSA000611","OCSSA000623","OCSSA000635","OCSSA000640","OCSSA000652","OCSSA000664","OCSSA000676","OCSSA000681","OCSSA000693","OCSSA000705","OCSSA000710","OCSSA000722","OCSSA000734","OCSSA000746","OCSSA000751","OCSSA000763","OCSSA000775","OCSSA000780","OCSSA000792","OCSSA000804","OCSSA000816","OCSSA000821","OCSSA000833","OCSSA000850","OCSSA000862","OCSSA000874","OCSSA000886","OCSSA000891","OCSSA000903","OCSSA000920","OCSSA000932","OCSSA000944","OCSSA000956","OCSSA000961","OCSSA000973","OCSSA000985","OCSSA000990","OCSSA001002","OCSSA001014","OCSSA001026","OCSSA001031","OCSSA001043","OCSSA001055","OCSSA001060","OCSSA001072","OCSSA001084","OCSSA001096","OCSSA001101","OCSSA001113","OCSSA001130","OCSSA001142","OCSSA001154","OCSSA001166","OCSSA001171","OCSSA001195","OCSSA001200","OCSSA001212","OCSSA001224","OCSSA001236","OCSSA001241","OCSSA001253","OCSSA001265","OCSSA001270","OCSSA001282","OCSSA001294","OCSSA001306","OCSSA001311","OCSSA001323","OCSSA001335","OCSSA001340","OCSSA001352","OCSSA001364","OCSSA001376","OCSSA001381","OCSSA001393","OCSSA001405","OCSSA001410","OCSSA001422","OCSSA001434","OCSSA001446","OCSSA001451","OCSSA001463","OCSSA001475","OCSSA001480","OCSSA001492","OCSSA001504","OCSSA001516","OCSSA001521","OCSSA001533","OCSSA001545","OCSSA001550","OCSSA001562","OCSSA001574","OCSSA001591","OCSSA001603","OCSSA001615","OCSSA001620","OCSSA001632","OCSSA001644","OCSSA001661","OCSSA001673","OCSSA001685","OCSSA001690","OCSSA001702","OCSSA001714","OCSSA001726","OCSSA001731","OCSSA001743","OCSSA001755","OCSSA001760","OCSSA001772","OCSSA001784","OCSSA001796","OCSSA001801","OCSSA001813","OCSSA001825","OCSSA001830","OCSSA001842","OCSSA001854","OCSSA001866","OCSSA001871","OCSSA001883","OCSSA001895","OCSSA001900","OCSSA001912","OCSSA001924","OCSSA001936","OCSSA001941","OCSSA001953","OCSSA001965","OCSSA001970","OCSSA001982","OCSSA001994","OCSSA002006","OCSSA002011","OCSSA002023","OCSSA002035","OCSSA002040","OCSSA002052","OCSSA002064","OCSSA002076","OCSSA002081","OCSSA002093","OCSSA002105","OCSSA002110","OCSSA002122","OCSSA002134","OCSSA002146","OCSSA002151","OCSSA002163","OCSSA002175","OCSSA002180","OCSSA002192","OCSSA002204","OCSSA002216","OCSSA002221","OCSSA002233","OCSSA002245","OCSSA002250","OCSSA002262","OCSSA002274","OCSSA002286","OCSSA002291","OCSSA002303","OCSSA002315","OCSSA002320","OCSSA002332","OCSSA002344","OCSSA002356","OCSSA002361","OCSSA002373","OCSSA002385","OCSSA002390","OCSSA002402","OCSSA002414","OCSSA002426","OCSSA002431","OCSSA002443","OCSSA002455","OCSSA002460","OCSSA002472","OCSSA002484","OCSSA002496","OCSSA002501","OCSSA002513","OCSSA002525","OCSSA002530","OCSSA002542","OCSSA002554","OCSSA002566","OCSSA002571","OCSSA002583","OCSSA002595","OCSSA002600","OCSSA002612","OCSSA002624","OCSSA002636","OCSSA002641","OCSSA002653","OCSSA002665","OCSSA002670","OCSSA002682","OCSSA002694","OCSSA002706","OCSSA002711","OCSSA002723","OCSSA002740","OCSSA002752","OCSSA002764","OCSSA002776","OCSSA002781","OCSSA002793","OCSSA002805","OCSSA002810","OCSSA002822","OCSSA002834","OCSSA002846","OCSSA002851","OCSSA002863","OCSSA002875","OCSSA002880","OCSSA002892","OCSSA002904","OCSSA002916","OCSSA002921","OCSSA002933","OCSSA002945","OCSSA002950","OCSSA002962","OCSSA002974","OCSSA002986","OCSSA002991","OCSSA003003","OCSSA003015","OCSSA003020","OCSSA003032","OCSSA003044","OCSSA003056","OCSSA003061","OCSSA003073","OCSSA003085","OCSSA003090","OCSSA003102","OCSSA003114","OCSSA003126","OCSSA003131","OCSSA003143","OCSSA003155","OCSSA003160","OCSSA003172","OCSSA003184","OCSSA003196","OCSSA003201","OCSSA003213","OCSSA003230","OCSSA003242","OCSSA003254","OCSSA003266","OCSSA003271","OCSSA003283","OCSSA003295","OCSSA003300","OCSSA003312","OCSSA003324","OCSSA003336","OCSSA003341","OCSSA003353","OCSSA003365","OCSSA003370","OCSSA003382","OCSSA003394","OCSSA003406","OCSSA003411","OCSSA003423","OCSSA003435","OCSSA003440","OCSSA003452","OCSSA003464","OCSSA003476","OCSSA003481","OCSSA003493","OCSSA003505","OCSSA003510","OCSSA003522","OCSSA003534","OCSSA003546","OCSSA003551","OCSSA003563","OCSSA003575","OCSSA003580","OCSSA003592","OCSSA003604","OCSSA003616","OCSSA003621","OCSSA003633","OCSSA003645","OCSSA003662","OCSSA003674","OCSSA003686","OCSSA003691","OCSSA003703","OCSSA003715","OCSSA003732","OCSSA003744","OCSSA003756","OCSSA003761","OCSSA003773","OCSSA003785","OCSSA003790","OCSSA003802","OCSSA003814","OCSSA003826","OCSSA003831","OCSSA003843","OCSSA003855","OCSSA003860","OCSSA003872","OCSSA003884","OCSSA003896","OCSSA003913","OCSSA003925","OCSSA003930","OCSSA003942","OCSSA003954","OCSSA003966","OCSSA003971","OCSSA003983","OCSSA003995","OCSSA004000","OCSSA004012","OCSSA004024","OCSSA004036","OCSSA004041","OCSSA004053","OCSSA004065","OCSSA004070","OCSSA004082","OCSSA004094","OCSSA004106","OCSSA004111","OCSSA004123","OCSSA004135","OCSSA004140","OCSSA004152","OCSSA004176","OCSSA004181","OCSSA004193","OCSSA004205","OCSSA004210","OCSSA004222","OCSSA004234","OCSSA004246","OCSSA004251","OCSSA004263","OCSSA004275","OCSSA004280","OCSSA004292","OCSSA004304","OCSSA004316","OCSSA004321","OCSSA004333","OCSSA004345","OCSSA004350","OCSSA004362","OCSSA004374","OCSSA004386","OCSSA004391","OCSSA004403","OCSSA004415","OCSSA004420","OCSSA004432","OCSSA004444","OCSSA004456","OCSSA004461","OCSSA004473","OCSSA004485","OCSSA004490","OCSSA004502","OCSSA004514","OCSSA004526","OCSSA004531","OCSSA004543","OCSSA004555","OCSSA004560","OCSSA004572","OCSSA004584","OCSSA004596","OCSSA004601","OCSSA004613","OCSSA004630","OCSSA004642","OCSSA004666","OCSSA004683","OCSSA004695","OCSSA004700","OCSSA004712","OCSSA004724","OCSSA004736","OCSSA004741","OCSSA004753","OCSSA004765","OCSSA004770","OCSSA004782","OCSSA004794","OCSSA004806","OCSSA004811","OCSSA004823","OCSSA004835","OCSSA004840","OCSSA004852","OCSSA004864","OCSSA004876","OCSSA004881","OCSSA004893","OCSSA004905","OCSSA004910","OCSSA004922","OCSSA004934","OCSSA004946","OCSSA004951","OCSSA004963","OCSSA004975","OCSSA004980","OCSSA004992","OCSSA005004","OCSSA005016","OCSSA005033","OCSSA005045","OCSSA005050","OCSSA005062","OCSSA005074","OCSSA005086","OCSSA005091","OCSSA005103","OCSSA005115","OCSSA005132","OCSSA005144","OCSSA005156","OCSSA005161","OCSSA005173","OCSSA005185","OCSSA005190","OCSSA005202","OCSSA005214","OCSSA005226","OCSSA005231","OCSSA005243","OCSSA005255","OCSSA005260","OCSSA005272","OCSSA005284","OCSSA005296","OCSSA005301","OCSSA005313","OCSSA005325","OCSSA005330","OCSSA005342","OCSSA005354","OCSSA005366","OCSSA005383","OCSSA005395","OCSSA005400","OCSSA005412","OCSSA005424","OCSSA005436","OCSSA005441","OCSSA005453","OCSSA005465","OCSSA005470","OCSSA005482","OCSSA005494","OCSSA005506","OCSSA005511","OCSSA005540","OCSSA005552","OCSSA005564","OCSSA005576","OCSSA005581","OCSSA005593","OCSSA005605","OCSSA005610","OCSSA005622","OCSSA005634","OCSSA005646","OCSSA005651","OCSSA005663","OCSSA005675","OCSSA005680","OCSSA005692","OCSSA005704","OCSSA005716","OCSSA005721","OCSSA005733","OCSSA005745","OCSSA005750","OCSSA005762","OCSSA005774","OCSSA005786","OCSSA005791","OCSSA005803","OCSSA005815","OCSSA005820","OCSSA005832","OCSSA005844","OCSSA005861","OCSSA005873","OCSSA005885","OCSSA005890","OCSSA005902","OCSSA005914","OCSSA005926","OCSSA005931","OCSSA005943","OCSSA005955","OCSSA005960","OCSSA005972","OCSSA005984","OCSSA005996","OCSSA006001","OCSSA006025","OCSSA006030","OCSSA006042","OCSSA006054","OCSSA006066","OCSSA006071","OCSSA006083","OCSSA006095","OCSSA006100","OCSSA006112","OCSSA006124","OCSSA006136","OCSSA006141","OCSSA006153","OCSSA006165","OCSSA006170","OCSSA006182","OCSSA006206","OCSSA006223","OCSSA006235","OCSSA006240","OCSSA006252","OCSSA006264","OCSSA006276","OCSSA006281","OCSSA006293","OCSSA006305","OCSSA006322","OCSSA006334","OCSSA006346","OCSSA006351","OCSSA006363","OCSSA006380","OCSSA006392","OCSSA006404","OCSSA006416","OCSSA006421","OCSSA006433","OCSSA006445","OCSSA006450","OCSSA006462","OCSSA006474","OCSSA006486","OCSSA006491","OCSSA006503","OCSSA006515","OCSSA006520","OCSSA006532","OCSSA006544","OCSSA006556","OCSSA006561","OCSSA006573","OCSSA006585","OCSSA006590","OCSSA006602","OCSSA006614","OCSSA006626","OCSSA006631","OCSSA006643","OCSSA006655","OCSSA006660","OCSSA006672","OCSSA006684","OCSSA006696","OCSSA006701","OCSSA006725","OCSSA006730","OCSSA006742","OCSSA006754","OCSSA006766","OCSSA006771","OCSSA006783","OCSSA006795","OCSSA006800","OCSSA006812","OCSSA006824","OCSSA006836","OCSSA006841","OCSSA006853","OCSSA006865","OCSSA006870","OCSSA006882","OCSSA006894","OCSSA006906","OCSSA006911","OCSSA006923","OCSSA006935","OCSSA006940","OCSSA006952","OCSSA006964","OCSSA006976","OCSSA006981","OCSSA006993","OCSSA007005","OCSSA007010","OCSSA007022","OCSSA007034","OCSSA007046","OCSSA007051","OCSSA007063","OCSSA007075","OCSSA007080","OCSSA007092","OCSSA007104","OCSSA007116","OCSSA007121","OCSSA007133","OCSSA007145","OCSSA007150","OCSSA007162","OCSSA007174","OCSSA007186","OCSSA007191","OCSSA007203","OCSSA007215","OCSSA007232","OCSSA007244","OCSSA007256","OCSSA007314","OCSSA007360","OCSSA007372","OCSSA007384","OCSSA007396","OCSSA007401","OCSSA007413","OCSSA007425","OCSSA007430","OCSSA007442","OCSSA007454","OCSSA007466","OCSSA007471","OCSSA007483","OCSSA007495","OCSSA007500","OCSSA007512","OCSSA007524","OCSSA007536","OCSSA007541","OCSSA007553","OCSSA007565","OCSSA007570","OCSSA007582","OCSSA007594","OCSSA014740","OCSSA014752","OCSSA014764","OCSSA014776","OCSSA014781","OCSSA014810","OCSSA014822","OCSSA014851","OCSSA014863","OCSSA014880","OCSSA014892","OCSSA014916","OCSSA014933","OCSSA014950","OCSSA014974","OCSSA014991","OCSSA015015","OCSSA015032","OCSSA015044","OCSSA015056","OCSSA015061","OCSSA015073","OCSSA015085","OCSSA015102","OCSSA015114","OCSSA015126","OCSSA015131","OCSSA015143","OCSSA015155","OCSSA015160","OCSSA015172","OCSSA015184","OCSSA015225","OCSSA015230","OCSSA015266","OCSSA015283","OCSSA015295","OCSSA015300","OCSSA015312","OCSSA015336","OCSSA015341","OCSSA015353","OCSSA015365","OCSSA015370","OCSSA015382","OCSSA015394","OCSSA015406","OCSSA015423","OCSSA015452","OCSSA015464","OCSSA015481","OCSSA015522","OCSSA015546","OCSSA015580","OCSSA015592","OCSSA015604","OCSSA015621","OCSSA015662","OCSSA015703","OCSSA015715","OCSSA015720","OCSSA015773","OCSSA015785","OCSSA015790","OCSSA015826","OCSSA015843","OCSSA015855","OCSSA015884","OCSSA015896","OCSSA015925","OCSSA015930","OCSSA015954","OCSSA015966","OCSSA015971","OCSSA015983","OCSSA015995","OCSSA016000","OCSSA016012","OCSSA016036","OCSSA016041","OCSSA016065","OCSSA016094","OCSSA016106","OCSSA016111","OCSSA016123","OCSSA016135","OCSSA016152","OCSSA016181","OCSSA016193","OCSSA016210","OCSSA016222","OCSSA016234","OCSSA016246","OCSSA016263","OCSSA016280","OCSSA016304","OCSSA016316","OCSSA016333","OCSSA016345","OCSSA016350","OCSSA016374","OCSSA016391","OCSSA016403","OCSSA016432","OCSSA016456","OCSSA016461","OCSSA016473","OCSSA016490","OCSSA016502","OCSSA016514","OCSSA016526","OCSSA016543","OCSSA016560","OCSSA016613","OCSSA016642","OCSSA016666","OCSSA016695","OCSSA016711","OCSSA016723","OCSSA016735","OCSSA016740","OCSSA016752","OCSSA016764","OCSSA016776","OCSSA016781","OCSSA016793","OCSSA016805","OCSSA016810","OCSSA016822","OCSSA016834","OCSSA016846","OCSSA016851","OCSSA016863","OCSSA016875","OCSSA016880","OCSSA016892","OCSSA016904","OCSSA016916","OCSSA016921","OCSSA016933","OCSSA016945","OCSSA016950","OCSSA016962","OCSSA016974","OCSSA016986","OCSSA016991","OCSSA017003","OCSSA017015","OCSSA017020","OCSSA017032","OCSSA017044","OCSSA017056","OCSSA017061","OCSSA017073","OCSSA017085","OCSSA017090","OCSSA017102","OCSSA017114","OCSSA017126","OCSSA017131","OCSSA017143","OCSSA017160","OCSSA017172","OCSSA017184","OCSSA017196","OCSSA017201","OCSSA017213","OCSSA017225","OCSSA017230","OCSSA017242","OCSSA017254","OCSSA017266","OCSSA017271","OCSSA017283","OCSSA017295","OCSSA017300","OCSSA017312","OCSSA017324","OCSSA017336","OCSSA017341","OCSSA017353","OCSSA017365","OCSSA017370","OCSSA017382","OCSSA017394","OCSSA017406","OCSSA017411","OCSSA017423","OCSSA017435","OCSSA017440","OCSSA017452","OCSSA017464","OCSSA017476","OCSSA017481","OCSSA017493","OCSSA017505","OCSSA017510","OCSSA017522","OCSSA017534","OCSSA017546","OCSSA017551","OCSSA017563","OCSSA017575","OCSSA017580","OCSSA017604","OCSSA017616","OCSSA017621","OCSSA017633","OCSSA017645","OCSSA017650","OCSSA017662","OCSSA017674","OCSSA017686","OCSSA017691","OCSSA017703","OCSSA017715","OCSSA017720","OCSSA017732","OCSSA017744","OCSSA017756","OCSSA017761","OCSSA017773","OCSSA017785","OCSSA017790","OCSSA017802","OCSSA017814","OCSSA017826","OCSSA017831","OCSSA017843","OCSSA017855","OCSSA017860","OCSSA017872","OCSSA017884","OCSSA017896","OCSSA017901","OCSSA017913","OCSSA017925","OCSSA017930","OCSSA017942","OCSSA017954","OCSSA017966","OCSSA017971","OCSSA017983","OCSSA017995","OCSSA018000","OCSSA018012","OCSSA018024","OCSSA018036","OCSSA018041","OCSSA018053","OCSSA018065","OCSSA018070","OCSSA018082","OCSSA018094","OCSSA018106","OCSSA018111","OCSSA018123","OCSSA018135","OCSSA018140","OCSSA018152","OCSSA018164","OCSSA018176","OCSSA018181","OCSSA018193","OCSSA018205","OCSSA018210","OCSSA018222","OCSSA018234","OCSSA018246","OCSSA018251","OCSSA018263","OCSSA018275","OCSSA018280","OCSSA018292","OCSSA018304","OCSSA018316","OCSSA018321","OCSSA018333","OCSSA018345","OCSSA018362","OCSSA018374","OCSSA018386","OCSSA018391","OCSSA018403","OCSSA018420","OCSSA018432","OCSSA018444","OCSSA018456","OCSSA018461","OCSSA018473","OCSSA018485","OCSSA018490","OCSSA018502","OCSSA018514","OCSSA018526","OCSSA018531","OCSSA018543","OCSSA018555","OCSSA018560","OCSSA018572","OCSSA018584","OCSSA018596","OCSSA018601","OCSSA018613","OCSSA018625","OCSSA018630","OCSSA018642","OCSSA018654","OCSSA018666","OCSSA018671","OCSSA018683","OCSSA018695","OCSSA018700","OCSSA018712","OCSSA018724","OCSSA018736","OCSSA018741","OCSSA018753","OCSSA018770","OCSSA018782","OCSSA018794","OCSSA018806","OCSSA018811","OCSSA018823","OCSSA018835","OCSSA018840","OCSSA018852","OCSSA018864","OCSSA018876","OCSSA018881","OCSSA018893","OCSSA018905","OCSSA018910","OCSSA018922","OCSSA018934","OCSSA018946","OCSSA018951","OCSSA018963","OCSSA018975","OCSSA018980","OCSSA019004","OCSSA019016","OCSSA019021","OCSSA019033","OCSSA019045","OCSSA019050","OCSSA019062","OCSSA019074","OCSSA019086","OCSSA019091","OCSSA019103","OCSSA019115","OCSSA019132","OCSSA019144","OCSSA019156","OCSSA019161","OCSSA019173","OCSSA019185","OCSSA019190","OCSSA019202","OCSSA019214","OCSSA019226","OCSSA019231","OCSSA019243","OCSSA019255","OCSSA019260","OCSSA019272","OCSSA019284","OCSSA019296","OCSSA019301","OCSSA019313","OCSSA019325","OCSSA019330","OCSSA019342","OCSSA019354","OCSSA019366","OCSSA019371","OCSSA019383","OCSSA019395","OCSSA019400","OCSSA019412","OCSSA019424","OCSSA019436","OCSSA019441","OCSSA019453","OCSSA019465","OCSSA019470","OCSSA019494","OCSSA019506","OCSSA019511","OCSSA019523","OCSSA019535","OCSSA019540","OCSSA019552","OCSSA019564","OCSSA019581","OCSSA019593","OCSSA019605","OCSSA019610","OCSSA019622","OCSSA019634","OCSSA019646","OCSSA019651","OCSSA019663","OCSSA019675","OCSSA019680","OCSSA019692","OCSSA019704","OCSSA019716","OCSSA019721","OCSSA019733","OCSSA019745","OCSSA019750","OCSSA019762","OCSSA019774","OCSSA019786","OCSSA019791","OCSSA019803","OCSSA019815","OCSSA019820","OCSSA019832","OCSSA019844","OCSSA019856","OCSSA019861","OCSSA019873","OCSSA019885","OCSSA019890","OCSSA019902","OCSSA019914","OCSSA019926","OCSSA019955","OCSSA019960","OCSSA019972","OCSSA019996","OCSSA020001","OCSSA020013","OCSSA020025","OCSSA020030","OCSSA020042","OCSSA020054","OCSSA020066","OCSSA020071","OCSSA020083","OCSSA020100","OCSSA020112","OCSSA020124","OCSSA020136","OCSSA020141","OCSSA020153","OCSSA020165","OCSSA020170","OCSSA020182","OCSSA020194","OCSSA020206","OCSSA020211","OCSSA020223","OCSSA020235","OCSSA020240","OCSSA020252","OCSSA020264","OCSSA020276","OCSSA020281","OCSSA020293","OCSSA020305","OCSSA020310","OCSSA020322","OCSSA020334","OCSSA020346","OCSSA020351","OCSSA020363","OCSSA020375","OCSSA020380","OCSSA020392","OCSSA020404","OCSSA020416","OCSSA020421","OCSSA020433","OCSSA020445","OCSSA020450","OCSSA020474","OCSSA020486","OCSSA020491","OCSSA020515","OCSSA020520","OCSSA020532","OCSSA020544","OCSSA020556","OCSSA020561","OCSSA020573","OCSSA020585","OCSSA020590","OCSSA020602","OCSSA020614","OCSSA020626","OCSSA020631","OCSSA020643","OCSSA020655","OCSSA020660","OCSSA020672","OCSSA020684","OCSSA020696","OCSSA020701","OCSSA020713","OCSSA020725","OCSSA020730","OCSSA020766","OCSSA020771","OCSSA020783","OCSSA020795","OCSSA020800","OCSSA020812","OCSSA020824","OCSSA020836","OCSSA020841","OCSSA020865","OCSSA020870","OCSSA020911","OCSSA020923","OCSSA020935","OCSSA020940","OCSSA020952","OCSSA020964","OCSSA020976","OCSSA020981","OCSSA020993","OCSSA021005","OCSSA021010","OCSSA021022","OCSSA021034","OCSSA021046","OCSSA021051","OCSSA021063","OCSSA021075","OCSSA021080","OCSSA021092","OCSSA021104","OCSSA021116","OCSSA021121","OCSSA021133","OCSSA021145","OCSSA021150","OCSSA021162","OCSSA021174","OCSSA021186","OCSSA021191","OCSSA021203","OCSSA021215","OCSSA021220","OCSSA021232","OCSSA021244");
} //fin de if($IdEstado == "20")

//Condicion de estado-clues
if($IdEstado == "21"){
	$Clues = array("PLSSA000011","PLSSA000035","PLSSA000052","PLSSA000064","PLSSA000076","PLSSA000081","PLSSA000122","PLSSA000134","PLSSA000146","PLSSA000163","PLSSA000175","PLSSA000192","PLSSA000204","PLSSA000216","PLSSA000221","PLSSA000233","PLSSA000245","PLSSA000250","PLSSA000262","PLSSA000274","PLSSA000291","PLSSA000303","PLSSA000315","PLSSA000320","PLSSA000332","PLSSA000344","PLSSA000356","PLSSA000361","PLSSA000373","PLSSA000385","PLSSA000390","PLSSA000414","PLSSA000426","PLSSA000431","PLSSA000443","PLSSA000455","PLSSA000460","PLSSA000472","PLSSA000484","PLSSA000496","PLSSA000501","PLSSA000513","PLSSA000525","PLSSA000530","PLSSA000542","PLSSA000554","PLSSA000566","PLSSA000571","PLSSA000583","PLSSA000595","PLSSA000600","PLSSA000612","PLSSA000624","PLSSA000636","PLSSA000641","PLSSA000653","PLSSA000665","PLSSA000670","PLSSA000682","PLSSA000694","PLSSA000706","PLSSA000711","PLSSA000723","PLSSA000735","PLSSA000752","PLSSA000764","PLSSA000776","PLSSA000781","PLSSA000793","PLSSA000805","PLSSA000810","PLSSA000822","PLSSA000834","PLSSA000846","PLSSA000851","PLSSA000863","PLSSA000880","PLSSA000892","PLSSA000904","PLSSA000916","PLSSA000921","PLSSA000933","PLSSA000945","PLSSA000950","PLSSA000962","PLSSA000974","PLSSA000986","PLSSA000991","PLSSA001003","PLSSA001015","PLSSA001020","PLSSA001032","PLSSA001044","PLSSA001056","PLSSA001061","PLSSA001073","PLSSA001085","PLSSA001114","PLSSA001126","PLSSA001131","PLSSA001143","PLSSA001155","PLSSA001160","PLSSA001172","PLSSA001184","PLSSA001196","PLSSA001201","PLSSA001213","PLSSA001225","PLSSA001230","PLSSA001242","PLSSA001254","PLSSA001266","PLSSA001271","PLSSA001283","PLSSA001295","PLSSA001300","PLSSA001312","PLSSA001324","PLSSA001336","PLSSA001341","PLSSA001353","PLSSA001365","PLSSA001370","PLSSA001382","PLSSA001394","PLSSA001406","PLSSA001411","PLSSA001423","PLSSA001435","PLSSA001493","PLSSA001505","PLSSA001510","PLSSA001522","PLSSA001534","PLSSA001546","PLSSA001551","PLSSA001563","PLSSA001575","PLSSA001580","PLSSA001592","PLSSA001604","PLSSA001616","PLSSA001621","PLSSA001645","PLSSA001662","PLSSA001674","PLSSA001686","PLSSA001691","PLSSA001703","PLSSA001715","PLSSA001720","PLSSA001732","PLSSA001744","PLSSA001756","PLSSA001761","PLSSA001773","PLSSA001802","PLSSA001814","PLSSA001826","PLSSA001831","PLSSA001843","PLSSA001855","PLSSA001860","PLSSA001872","PLSSA001913","PLSSA001925","PLSSA001930","PLSSA001942","PLSSA001954","PLSSA001966","PLSSA001971","PLSSA001983","PLSSA001995","PLSSA002000","PLSSA002012","PLSSA002024","PLSSA002036","PLSSA002041","PLSSA002053","PLSSA002065","PLSSA002070","PLSSA002094","PLSSA002106","PLSSA002123","PLSSA002135","PLSSA002140","PLSSA002152","PLSSA002164","PLSSA002176","PLSSA002181","PLSSA002193","PLSSA002205","PLSSA002210","PLSSA002222","PLSSA002234","PLSSA002246","PLSSA002251","PLSSA002263","PLSSA002275","PLSSA002280","PLSSA002292","PLSSA002304","PLSSA002316","PLSSA002321","PLSSA002333","PLSSA002345","PLSSA002350","PLSSA002362","PLSSA002374","PLSSA002386","PLSSA002403","PLSSA002415","PLSSA002420","PLSSA002432","PLSSA002444","PLSSA002461","PLSSA002473","PLSSA002485","PLSSA002490","PLSSA002502","PLSSA002514","PLSSA002526","PLSSA002531","PLSSA002543","PLSSA002683","PLSSA002695","PLSSA002700","PLSSA002712","PLSSA002724","PLSSA002736","PLSSA002741","PLSSA002753","PLSSA002765","PLSSA002770","PLSSA002782","PLSSA002794","PLSSA002806","PLSSA002811","PLSSA002823","PLSSA002835","PLSSA002840","PLSSA002852","PLSSA002864","PLSSA002876","PLSSA002881","PLSSA002893","PLSSA002905","PLSSA002910","PLSSA002934","PLSSA002946","PLSSA002951","PLSSA002963","PLSSA002975","PLSSA002980","PLSSA002992","PLSSA003004","PLSSA003021","PLSSA003033","PLSSA003045","PLSSA003050","PLSSA003062","PLSSA003074","PLSSA003086","PLSSA003091","PLSSA003103","PLSSA003115","PLSSA003120","PLSSA003132","PLSSA003156","PLSSA003161","PLSSA003173","PLSSA003185","PLSSA003190","PLSSA003214","PLSSA003226","PLSSA003231","PLSSA003243","PLSSA003255","PLSSA003260","PLSSA003284","PLSSA003296","PLSSA003301","PLSSA003325","PLSSA003330","PLSSA003342","PLSSA003354","PLSSA003366","PLSSA003371","PLSSA003383","PLSSA003400","PLSSA003412","PLSSA003424","PLSSA003441","PLSSA003453","PLSSA003465","PLSSA003470","PLSSA003482","PLSSA003494","PLSSA003506","PLSSA003523","PLSSA003535","PLSSA003540","PLSSA003552","PLSSA003581","PLSSA003593","PLSSA003605","PLSSA003610","PLSSA003622","PLSSA003634","PLSSA003646","PLSSA003651","PLSSA003663","PLSSA003716","PLSSA003721","PLSSA003733","PLSSA003745","PLSSA003750","PLSSA003762","PLSSA003774","PLSSA003786","PLSSA003791","PLSSA003803","PLSSA003815","PLSSA003832","PLSSA003856","PLSSA003861","PLSSA003873","PLSSA003885","PLSSA003890","PLSSA003902","PLSSA003914","PLSSA003926","PLSSA003931","PLSSA003943","PLSSA003955","PLSSA003972","PLSSA003984","PLSSA003996","PLSSA004001","PLSSA004013","PLSSA004025","PLSSA004042","PLSSA004054","PLSSA004066","PLSSA004071","PLSSA004083","PLSSA004095","PLSSA004100","PLSSA004112","PLSSA004136","PLSSA004141","PLSSA004153","PLSSA004165","PLSSA004170","PLSSA004182","PLSSA004194","PLSSA004206","PLSSA004211","PLSSA004223","PLSSA004235","PLSSA004240","PLSSA004252","PLSSA004264","PLSSA004276","PLSSA004281","PLSSA004293","PLSSA004305","PLSSA004310","PLSSA004322","PLSSA004334","PLSSA004346","PLSSA004351","PLSSA004363","PLSSA004375","PLSSA004380","PLSSA004404","PLSSA004416","PLSSA004421","PLSSA004433","PLSSA004445","PLSSA004450","PLSSA004462","PLSSA004474","PLSSA004486","PLSSA004491","PLSSA004503","PLSSA004515","PLSSA004520","PLSSA004532","PLSSA004544","PLSSA004556","PLSSA004561","PLSSA004573","PLSSA004585","PLSSA004590","PLSSA004602","PLSSA004614","PLSSA004626","PLSSA004631","PLSSA004643","PLSSA004655","PLSSA004660","PLSSA004672","PLSSA004684","PLSSA004696","PLSSA004701","PLSSA004713","PLSSA004725","PLSSA004730","PLSSA004742","PLSSA004754","PLSSA004766","PLSSA004771","PLSSA004783","PLSSA004795","PLSSA004800","PLSSA004812","PLSSA004865","PLSSA004870","PLSSA004882","PLSSA004894","PLSSA004906","PLSSA004911","PLSSA004923","PLSSA004935","PLSSA004940","PLSSA004964","PLSSA004976","PLSSA004981","PLSSA004993","PLSSA005005","PLSSA005010","PLSSA005022","PLSSA005034","PLSSA005046","PLSSA005051","PLSSA005063","PLSSA005075","PLSSA005080","PLSSA005092","PLSSA005104","PLSSA005116","PLSSA005121","PLSSA005133","PLSSA005145","PLSSA005150","PLSSA005162","PLSSA005174","PLSSA005186","PLSSA005191","PLSSA005203","PLSSA005215","PLSSA005220","PLSSA005232","PLSSA005244","PLSSA005256","PLSSA005261","PLSSA005273","PLSSA005285","PLSSA005290","PLSSA005302","PLSSA005314","PLSSA005326","PLSSA005331","PLSSA005355","PLSSA005360","PLSSA005384","PLSSA005396","PLSSA005401","PLSSA005413","PLSSA005425","PLSSA005430","PLSSA005442","PLSSA005454","PLSSA005466","PLSSA005471","PLSSA005483","PLSSA005495","PLSSA005500","PLSSA005512","PLSSA005524","PLSSA005536","PLSSA005541","PLSSA005553","PLSSA005565","PLSSA005570","PLSSA005582","PLSSA005594","PLSSA005606","PLSSA005611","PLSSA005623","PLSSA005635","PLSSA005640","PLSSA005652","PLSSA005664","PLSSA005676","PLSSA005681","PLSSA005693","PLSSA005705","PLSSA005710","PLSSA005722","PLSSA005734","PLSSA005746","PLSSA005816","PLSSA005821","PLSSA005833","PLSSA005845","PLSSA005850","PLSSA005862","PLSSA014641","PLSSA014653","PLSSA014665","PLSSA014670","PLSSA014683","PLSSA014695","PLSSA014700","PLSSA014712","PLSSA014724","PLSSA014736","PLSSA014741","PLSSA014753","PLSSA014765","PLSSA014770","PLSSA014782","PLSSA014794","PLSSA014806","PLSSA014811","PLSSA014823","PLSSA014835","PLSSA014840","PLSSA014852","PLSSA014864","PLSSA014876","PLSSA014881","PLSSA014893","PLSSA014905","PLSSA014910","PLSSA014922","PLSSA015016","PLSSA015021","PLSSA015032","PLSSA015044","PLSSA015056","PLSSA015061","PLSSA015085","PLSSA015090","PLSSA015102","PLSSA015114","PLSSA015126","PLSSA015131","PLSSA015143","PLSSA015155","PLSSA015160","PLSSA015172","PLSSA015184","PLSSA015196","PLSSA015201","PLSSA015213","PLSSA015225","PLSSA015230","PLSSA015242","PLSSA015254","PLSSA015266","PLSSA015271","PLSSA015283","PLSSA015295","PLSSA015300","PLSSA015312","PLSSA015324","PLSSA015336","PLSSA015341","PLSSA015353","PLSSA015365","PLSSA015370","PLSSA015382","PLSSA015394","PLSSA015406","PLSSA015411","PLSSA015423","PLSSA015435","PLSSA015440","PLSSA015452","PLSSA015464","PLSSA015476","PLSSA015481","PLSSA015493","PLSSA015505","PLSSA015510","PLSSA015522","PLSSA015534","PLSSA015546","PLSSA015551","PLSSA015563","PLSSA015575","PLSSA015580","PLSSA015592","PLSSA015604","PLSSA015616","PLSSA015621","PLSSA015633","PLSSA015645","PLSSA015650","PLSSA015662","PLSSA015674","PLSSA015686","PLSSA015691","PLSSA015703","PLSSA015715","PLSSA015720","PLSSA015732","PLSSA015744","PLSSA015756","PLSSA015761","PLSSA015773","PLSSA015785","PLSSA015790","PLSSA015802","PLSSA015814","PLSSA015826","PLSSA015831","PLSSA015843","PLSSA015855","PLSSA015860","PLSSA015872","PLSSA015884","PLSSA015896","PLSSA015901","PLSSA015913","PLSSA015925","PLSSA015930","PLSSA015942","PLSSA015954","PLSSA015966","PLSSA015971","PLSSA015983","PLSSA015995","PLSSA016000","PLSSA016012","PLSSA016024","PLSSA016036","PLSSA016041","PLSSA016053","PLSSA016065","PLSSA016070","PLSSA016082","PLSSA016094","PLSSA016106","PLSSA016111","PLSSA016123","PLSSA016135","PLSSA016140","PLSSA016152","PLSSA016164","PLSSA016176","PLSSA016181","PLSSA016193","PLSSA016205","PLSSA016210","PLSSA016222","PLSSA016234","PLSSA016246","PLSSA016251","PLSSA016263","PLSSA016275","PLSSA016280","PLSSA016292","PLSSA016304","PLSSA016316","PLSSA016321","PLSSA016333","PLSSA016345","PLSSA016350","PLSSA016362","PLSSA016374","PLSSA016386","PLSSA016391","PLSSA016403","PLSSA016415","PLSSA016420","PLSSA016432","PLSSA016444","PLSSA016456","PLSSA016461","PLSSA016473","PLSSA016485","PLSSA016490","PLSSA016502","PLSSA016514","PLSSA016526","PLSSA016531","PLSSA016543","PLSSA016555","PLSSA016560","PLSSA016572","PLSSA016584","PLSSA016596","PLSSA016601","PLSSA016613","PLSSA016625","PLSSA016630","PLSSA016642","PLSSA016654","PLSSA016666","PLSSA016671","PLSSA016683","PLSSA016695","PLSSA016700","PLSSA016712","PLSSA016724","PLSSA016736","PLSSA016741","PLSSA016753","PLSSA016765","PLSSA016770","PLSSA016782","PLSSA016794","PLSSA016806","PLSSA016811","PLSSA016823","PLSSA016835","PLSSA016840","PLSSA016852","PLSSA016864","PLSSA016876","PLSSA016881","PLSSA016893","PLSSA016905","PLSSA016910","PLSSA016922","PLSSA016934","PLSSA016946","PLSSA016951","PLSSA016963","PLSSA016975","PLSSA016980","PLSSA016992","PLSSA017004","PLSSA017016");
} //fin de if($IdEstado == "21")

//Condicion de estado-clues
if($IdEstado == "22"){
	$Clues = array("QTSSA000014","QTSSA000031","QTSSA000043","QTSSA000055","QTSSA000060","QTSSA000072","QTSSA000084","QTSSA000096","QTSSA000101","QTSSA000113","QTSSA000125","QTSSA000130","QTSSA000142","QTSSA000166","QTSSA000171","QTSSA000183","QTSSA000200","QTSSA000212","QTSSA000236","QTSSA000253","QTSSA000282","QTSSA000294","QTSSA000311","QTSSA000323","QTSSA000352","QTSSA000364","QTSSA000376","QTSSA000405","QTSSA000434","QTSSA000446","QTSSA000463","QTSSA000475","QTSSA000480","QTSSA000492","QTSSA000516","QTSSA000521","QTSSA000533","QTSSA000545","QTSSA000550","QTSSA000562","QTSSA000574","QTSSA000586","QTSSA000591","QTSSA000603","QTSSA000615","QTSSA000620","QTSSA000632","QTSSA000644","QTSSA000656","QTSSA000673","QTSSA000685","QTSSA000714","QTSSA000726","QTSSA000731","QTSSA000755","QTSSA000760","QTSSA000772","QTSSA000784","QTSSA000796","QTSSA000830","QTSSA000842","QTSSA000854","QTSSA000866","QTSSA000871","QTSSA000883","QTSSA000895","QTSSA000912","QTSSA000924","QTSSA000936","QTSSA000941","QTSSA000953","QTSSA000970","QTSSA000982","QTSSA000994","QTSSA001006","QTSSA001011","QTSSA001023","QTSSA001035","QTSSA001040","QTSSA001052","QTSSA001064","QTSSA001076","QTSSA001093","QTSSA001105","QTSSA001110","QTSSA001122","QTSSA001134","QTSSA001146","QTSSA001151","QTSSA001163","QTSSA001175","QTSSA001192","QTSSA001204","QTSSA001216","QTSSA001221","QTSSA001233","QTSSA001245","QTSSA001250","QTSSA001274","QTSSA001286","QTSSA001291","QTSSA001303","QTSSA001315","QTSSA001332","QTSSA001344","QTSSA001356","QTSSA001373","QTSSA001390","QTSSA001402","QTSSA001414","QTSSA001426","QTSSA001431","QTSSA001443","QTSSA001460","QTSSA001472","QTSSA001484","QTSSA001496","QTSSA001501","QTSSA001513","QTSSA001525","QTSSA001530","QTSSA001542","QTSSA001554","QTSSA001566","QTSSA001583","QTSSA001595","QTSSA001600","QTSSA001612","QTSSA001624","QTSSA001636","QTSSA001641","QTSSA001653","QTSSA001665","QTSSA001682","QTSSA001694","QTSSA001706","QTSSA001711","QTSSA001723","QTSSA001735","QTSSA001740","QTSSA001752","QTSSA001764","QTSSA001793","QTSSA001805","QTSSA001810","QTSSA001822","QTSSA001834","QTSSA001846","QTSSA001863","QTSSA001875","QTSSA001880","QTSSA001904","QTSSA001916","QTSSA001921","QTSSA001933","QTSSA001945","QTSSA001962","QTSSA001974","QTSSA002003","QTSSA002015","QTSSA002020","QTSSA002044","QTSSA002061","QTSSA002073","QTSSA002085","QTSSA002090","QTSSA002102","QTSSA002114","QTSSA002160","QTSSA002172","QTSSA002184","QTSSA002196","QTSSA002213","QTSSA002225","QTSSA002230","QTSSA002242","QTSSA002266","QTSSA002271","QTSSA002283","QTSSA002300","QTSSA002312","QTSSA002324","QTSSA002336","QTSSA002341","QTSSA002353","QTSSA002370","QTSSA002382","QTSSA002394","QTSSA002406","QTSSA002411","QTSSA002435","QTSSA002452","QTSSA002464","QTSSA002476","QTSSA002481","QTSSA002493","QTSSA002505","QTSSA002522","QTSSA002534","QTSSA002546","QTSSA002551","QTSSA012101","QTSSA012113","QTSSA012125","QTSSA012130","QTSSA012142","QTSSA012154","QTSSA012166","QTSSA012171","QTSSA012183","QTSSA012195","QTSSA012200","QTSSA012212","QTSSA012224","QTSSA012236","QTSSA012240","QTSSA012252","QTSSA012264","QTSSA012276","QTSSA012281","QTSSA012293","QTSSA012305","QTSSA012310","QTSSA012322","QTSSA012334","QTSSA012346","QTSSA012351","QTSSA012363","QTSSA012380","QTSSA012392","QTSSA012404","QTSSA012416","QTSSA012421","QTSSA012433","QTSSA012445","QTSSA012450","QTSSA012462","QTSSA012474","QTSSA012486","QTSSA012491","QTSSA012503","QTSSA012515","QTSSA012520","QTSSA012532","QTSSA012544","QTSSA012556","QTSSA012561","QTSSA012573","QTSSA012585","QTSSA012590","QTSSA012602","QTSSA012614","QTSSA012626","QTSSA012631","QTSSA012643","QTSSA012655","QTSSA012660","QTSSA012672","QTSSA012684","QTSSA012696","QTSSA012725","QTSSA012730","QTSSA012742","QTSSA012754","QTSSA012766","QTSSA012771","QTSSA012783","QTSSA012795","QTSSA012800","QTSSA012812","QTSSA012824","QTSSA012836","QTSSA012841","QTSSA012853","QTSSA012865","QTSSA012870","QTSSA012882","QTSSA012894","QTSSA012906","QTSSA012911","QTSSA012923","QTSSA012935","QTSSA012940","QTSSA012952","QTSSA012964");
} //fin de if($IdEstado == "22")

//Condicion de estado-clues
if($IdEstado == "23"){
	$Clues = array("QRSSA000011","QRSSA000023","QRSSA000035","QRSSA000040","QRSSA000052","QRSSA000064","QRSSA000076","QRSSA000081","QRSSA000093","QRSSA000105","QRSSA000110","QRSSA000122","QRSSA000134","QRSSA000146","QRSSA000151","QRSSA000163","QRSSA000175","QRSSA000180","QRSSA000192","QRSSA000204","QRSSA000233","QRSSA000245","QRSSA000250","QRSSA000262","QRSSA000274","QRSSA000286","QRSSA000291","QRSSA000303","QRSSA000315","QRSSA000320","QRSSA000332","QRSSA000344","QRSSA000356","QRSSA000361","QRSSA000373","QRSSA000390","QRSSA000402","QRSSA000414","QRSSA000426","QRSSA000431","QRSSA000443","QRSSA000455","QRSSA000460","QRSSA000472","QRSSA000484","QRSSA000496","QRSSA000501","QRSSA000525","QRSSA000530","QRSSA000542","QRSSA000554","QRSSA000566","QRSSA000571","QRSSA000583","QRSSA000595","QRSSA000600","QRSSA000612","QRSSA000624","QRSSA000636","QRSSA000641","QRSSA000653","QRSSA000665","QRSSA000670","QRSSA000682","QRSSA000694","QRSSA000706","QRSSA000711","QRSSA000723","QRSSA000735","QRSSA000740","QRSSA000752","QRSSA000764","QRSSA000776","QRSSA000781","QRSSA000793","QRSSA000805","QRSSA000810","QRSSA000822","QRSSA000834","QRSSA000846","QRSSA000851","QRSSA000863","QRSSA000875","QRSSA000880","QRSSA000904","QRSSA000916","QRSSA000933","QRSSA000945","QRSSA000950","QRSSA000962","QRSSA000974","QRSSA000986","QRSSA000991","QRSSA001003","QRSSA001020","QRSSA001044","QRSSA001056","QRSSA001061","QRSSA001073","QRSSA001085","QRSSA001102","QRSSA001114","QRSSA001126","QRSSA001131","QRSSA001143","QRSSA001155","QRSSA001160","QRSSA001172","QRSSA001184","QRSSA001196","QRSSA001201","QRSSA001213","QRSSA001225","QRSSA001230","QRSSA001300","QRSSA001411","QRSSA001423","QRSSA001435","QRSSA001440","QRSSA001452","QRSSA001464","QRSSA001476","QRSSA001481","QRSSA001493","QRSSA001505","QRSSA001510","QRSSA001522","QRSSA001534","QRSSA001546","QRSSA001551","QRSSA001563","QRSSA001575","QRSSA001580","QRSSA001592","QRSSA001650","QRSSA001662","QRSSA001674","QRSSA001715","QRSSA001720","QRSSA001732","QRSSA017470","QRSSA017482","QRSSA017494","QRSSA017506","QRSSA017523","QRSSA017535","QRSSA017552","QRSSA017564","QRSSA017576","QRSSA017581","QRSSA017593","QRSSA017605","QRSSA017610","QRSSA017622","QRSSA017634","QRSSA017646","QRSSA017651","QRSSA017663","QRSSA017675","QRSSA017680","QRSSA017692","QRSSA017704","QRSSA017716","QRSSA017721","QRSSA017733","QRSSA017745","QRSSA017750","QRSSA017762","QRSSA017774","QRSSA017786","QRSSA017791","QRSSA017803","QRSSA017815","QRSSA017820","QRSSA017832","QRSSA017844","QRSSA017861","QRSSA017873","QRSSA017885","QRSSA017890","QRSSA017902","QRSSA017914","QRSSA017926","QRSSA017931","QRSSA017943","QRSSA017955","QRSSA017960","QRSSA017972","QRSSA017984","QRSSA017996","QRSSA018001","QRSSA018013","QRSSA018025","QRSSA018030","QRSSA018042","QRSSA018054");
} //fin de if($IdEstado == "23")

//Condicion de estado-clues
if($IdEstado == "24"){
	$Clues = array("SPSSA000011","SPSSA000023","SPSSA000035","SPSSA000040","SPSSA000052","SPSSA000064","SPSSA000076","SPSSA000081","SPSSA000093","SPSSA000105","SPSSA000110","SPSSA000122","SPSSA000134","SPSSA000146","SPSSA000151","SPSSA000163","SPSSA000175","SPSSA000180","SPSSA000192","SPSSA000204","SPSSA000216","SPSSA000221","SPSSA000233","SPSSA000245","SPSSA000250","SPSSA000262","SPSSA000274","SPSSA000286","SPSSA000291","SPSSA000303","SPSSA000315","SPSSA000320","SPSSA000332","SPSSA000344","SPSSA000356","SPSSA000361","SPSSA000373","SPSSA000385","SPSSA000390","SPSSA000402","SPSSA000414","SPSSA000426","SPSSA000431","SPSSA000455","SPSSA000460","SPSSA000472","SPSSA000484","SPSSA000496","SPSSA000501","SPSSA000513","SPSSA000525","SPSSA000530","SPSSA000542","SPSSA000554","SPSSA000566","SPSSA000571","SPSSA000583","SPSSA000595","SPSSA000600","SPSSA000612","SPSSA000624","SPSSA000636","SPSSA000641","SPSSA000653","SPSSA000665","SPSSA000670","SPSSA000682","SPSSA000694","SPSSA000706","SPSSA000711","SPSSA000723","SPSSA000735","SPSSA000740","SPSSA000752","SPSSA000764","SPSSA000776","SPSSA000781","SPSSA000793","SPSSA000805","SPSSA000810","SPSSA000822","SPSSA000834","SPSSA000846","SPSSA000851","SPSSA000863","SPSSA000875","SPSSA000880","SPSSA000892","SPSSA000904","SPSSA000921","SPSSA000933","SPSSA000945","SPSSA000950","SPSSA000962","SPSSA000974","SPSSA000986","SPSSA000991","SPSSA001003","SPSSA001015","SPSSA001020","SPSSA001032","SPSSA001044","SPSSA001056","SPSSA001061","SPSSA001073","SPSSA001085","SPSSA001102","SPSSA001114","SPSSA001126","SPSSA001143","SPSSA001160","SPSSA001172","SPSSA001184","SPSSA001196","SPSSA001201","SPSSA001213","SPSSA001225","SPSSA001230","SPSSA001242","SPSSA001254","SPSSA001266","SPSSA001271","SPSSA001283","SPSSA001295","SPSSA001300","SPSSA001312","SPSSA001324","SPSSA001336","SPSSA001341","SPSSA001353","SPSSA001365","SPSSA001370","SPSSA001382","SPSSA001394","SPSSA001406","SPSSA001411","SPSSA001423","SPSSA001435","SPSSA001440","SPSSA001452","SPSSA001464","SPSSA001476","SPSSA001481","SPSSA001493","SPSSA001505","SPSSA001510","SPSSA001522","SPSSA001534","SPSSA001551","SPSSA001563","SPSSA001575","SPSSA001592","SPSSA001604","SPSSA001616","SPSSA001621","SPSSA001633","SPSSA001645","SPSSA001650","SPSSA001662","SPSSA001674","SPSSA001686","SPSSA001691","SPSSA001703","SPSSA001720","SPSSA001732","SPSSA001756","SPSSA001761","SPSSA001773","SPSSA001785","SPSSA001802","SPSSA001814","SPSSA001826","SPSSA001831","SPSSA001843","SPSSA001855","SPSSA001860","SPSSA001872","SPSSA001884","SPSSA001896","SPSSA001901","SPSSA001913","SPSSA001925","SPSSA001930","SPSSA001942","SPSSA001954","SPSSA001971","SPSSA001983","SPSSA001995","SPSSA002000","SPSSA002012","SPSSA002024","SPSSA002036","SPSSA002041","SPSSA002053","SPSSA002065","SPSSA002070","SPSSA002082","SPSSA002094","SPSSA002106","SPSSA002111","SPSSA002123","SPSSA002135","SPSSA002140","SPSSA002152","SPSSA002164","SPSSA002176","SPSSA002181","SPSSA002193","SPSSA002205","SPSSA002210","SPSSA002222","SPSSA002234","SPSSA002246","SPSSA002251","SPSSA002263","SPSSA002275","SPSSA002280","SPSSA002292","SPSSA002304","SPSSA002316","SPSSA002321","SPSSA002333","SPSSA002345","SPSSA002350","SPSSA002362","SPSSA002374","SPSSA002386","SPSSA002391","SPSSA002403","SPSSA002415","SPSSA002420","SPSSA002432","SPSSA002444","SPSSA002456","SPSSA002461","SPSSA002473","SPSSA002485","SPSSA002490","SPSSA002502","SPSSA002514","SPSSA002526","SPSSA002531","SPSSA002543","SPSSA002555","SPSSA002560","SPSSA002572","SPSSA002584","SPSSA002596","SPSSA002601","SPSSA002613","SPSSA002625","SPSSA002630","SPSSA002642","SPSSA002654","SPSSA002666","SPSSA002671","SPSSA002683","SPSSA002695","SPSSA002700","SPSSA002712","SPSSA002724","SPSSA002736","SPSSA002741","SPSSA002753","SPSSA002765","SPSSA002770","SPSSA002782","SPSSA002794","SPSSA002806","SPSSA002811","SPSSA002823","SPSSA002835","SPSSA002840","SPSSA002852","SPSSA002864","SPSSA002876","SPSSA002881","SPSSA002893","SPSSA002905","SPSSA002910","SPSSA002922","SPSSA002951","SPSSA002963","SPSSA002975","SPSSA016823","SPSSA016835","SPSSA016841","SPSSA016853","SPSSA016865","SPSSA016870","SPSSA016882","SPSSA016894","SPSSA016906","SPSSA016911","SPSSA016923","SPSSA016935","SPSSA016940","SPSSA016952","SPSSA016964","SPSSA016976","SPSSA016981","SPSSA016993","SPSSA017005","SPSSA017010","SPSSA017022","SPSSA017034","SPSSA017046","SPSSA017051","SPSSA017062","SPSSA017074","SPSSA017086","SPSSA017091","SPSSA017103","SPSSA017115","SPSSA017120","SPSSA017132","SPSSA017144","SPSSA017156","SPSSA017161","SPSSA017173","SPSSA017185","SPSSA017190","SPSSA017202","SPSSA017214","SPSSA017226","SPSSA017231","SPSSA017243","SPSSA017255","SPSSA017260","SPSSA017272","SPSSA017284","SPSSA017296","SPSSA017301","SPSSA017313","SPSSA017325","SPSSA017330","SPSSA017342","SPSSA017354","SPSSA017366","SPSSA017371","SPSSA017383","SPSSA017395","SPSSA017400","SPSSA017412","SPSSA017424","SPSSA017436","SPSSA017441","SPSSA017453","SPSSA017465","SPSSA017470","SPSSA017482","SPSSA017494","SPSSA017506","SPSSA017511","SPSSA017523","SPSSA017535","SPSSA017540");
} //fin de if($IdEstado == "24")

//Condicion de estado-clues
if($IdEstado == "25"){
	$Clues = array("SLSSA000024","SLSSA000036","SLSSA000041","SLSSA000053","SLSSA000065","SLSSA000070","SLSSA000082","SLSSA000094","SLSSA000106","SLSSA000111","SLSSA000123","SLSSA000135","SLSSA000140","SLSSA000152","SLSSA000164","SLSSA000176","SLSSA000181","SLSSA000193","SLSSA000205","SLSSA000210","SLSSA000222","SLSSA000234","SLSSA000246","SLSSA000251","SLSSA000263","SLSSA000275","SLSSA000280","SLSSA000292","SLSSA000304","SLSSA000316","SLSSA000321","SLSSA000333","SLSSA000345","SLSSA000350","SLSSA000362","SLSSA000374","SLSSA000386","SLSSA000391","SLSSA000403","SLSSA000415","SLSSA000420","SLSSA000432","SLSSA000444","SLSSA000456","SLSSA000473","SLSSA000485","SLSSA000490","SLSSA000502","SLSSA000514","SLSSA000526","SLSSA000531","SLSSA000543","SLSSA000555","SLSSA000560","SLSSA000572","SLSSA000584","SLSSA000596","SLSSA000601","SLSSA000613","SLSSA000625","SLSSA000630","SLSSA000642","SLSSA000666","SLSSA000671","SLSSA000683","SLSSA000695","SLSSA000700","SLSSA000712","SLSSA000724","SLSSA000736","SLSSA000741","SLSSA000753","SLSSA000765","SLSSA000770","SLSSA000782","SLSSA000794","SLSSA000806","SLSSA000811","SLSSA000823","SLSSA000835","SLSSA000840","SLSSA000852","SLSSA000864","SLSSA000876","SLSSA000881","SLSSA000893","SLSSA000905","SLSSA000910","SLSSA000922","SLSSA000934","SLSSA000946","SLSSA000951","SLSSA000963","SLSSA000980","SLSSA000992","SLSSA001004","SLSSA001016","SLSSA001021","SLSSA001033","SLSSA001045","SLSSA001050","SLSSA001062","SLSSA001074","SLSSA001086","SLSSA001091","SLSSA001103","SLSSA001115","SLSSA001120","SLSSA001132","SLSSA001144","SLSSA001156","SLSSA001161","SLSSA001173","SLSSA001185","SLSSA001190","SLSSA001202","SLSSA001214","SLSSA001226","SLSSA001255","SLSSA001260","SLSSA001272","SLSSA001284","SLSSA001296","SLSSA001301","SLSSA001313","SLSSA001325","SLSSA001330","SLSSA001342","SLSSA001354","SLSSA001366","SLSSA001371","SLSSA001383","SLSSA001395","SLSSA001400","SLSSA001412","SLSSA001424","SLSSA001436","SLSSA001441","SLSSA001453","SLSSA001465","SLSSA001470","SLSSA001482","SLSSA001494","SLSSA001506","SLSSA001511","SLSSA001523","SLSSA001540","SLSSA001552","SLSSA001564","SLSSA001576","SLSSA001581","SLSSA001593","SLSSA001605","SLSSA001610","SLSSA001622","SLSSA001634","SLSSA001646","SLSSA001651","SLSSA001663","SLSSA001675","SLSSA001680","SLSSA001692","SLSSA001704","SLSSA001716","SLSSA001721","SLSSA001733","SLSSA001745","SLSSA001750","SLSSA001762","SLSSA001774","SLSSA001786","SLSSA001791","SLSSA001803","SLSSA001815","SLSSA001820","SLSSA001832","SLSSA001844","SLSSA001856","SLSSA001861","SLSSA001873","SLSSA001885","SLSSA001902","SLSSA001914","SLSSA001926","SLSSA001931","SLSSA001943","SLSSA001955","SLSSA001960","SLSSA001972","SLSSA001984","SLSSA001996","SLSSA002001","SLSSA002013","SLSSA002025","SLSSA002030","SLSSA002042","SLSSA002054","SLSSA002066","SLSSA002071","SLSSA002083","SLSSA002095","SLSSA002100","SLSSA002112","SLSSA002124","SLSSA002136","SLSSA002141","SLSSA002153","SLSSA002165","SLSSA002170","SLSSA002182","SLSSA002194","SLSSA002206","SLSSA002211","SLSSA002223","SLSSA002235","SLSSA002240","SLSSA002252","SLSSA002264","SLSSA002276","SLSSA002281","SLSSA002293","SLSSA002305","SLSSA002310","SLSSA002351","SLSSA002363","SLSSA002380","SLSSA002392","SLSSA002404","SLSSA002416","SLSSA002445","SLSSA002450","SLSSA002462","SLSSA002474","SLSSA002486","SLSSA002491","SLSSA002503","SLSSA002515","SLSSA002532","SLSSA002544","SLSSA017273","SLSSA017285","SLSSA017314","SLSSA017320","SLSSA017332","SLSSA017344","SLSSA017356","SLSSA017361","SLSSA017373","SLSSA017385","SLSSA017390","SLSSA017402","SLSSA017414","SLSSA017426","SLSSA017431","SLSSA017443","SLSSA017455","SLSSA017460","SLSSA017472","SLSSA017484","SLSSA017496","SLSSA017501","SLSSA017513","SLSSA017524","SLSSA017536","SLSSA017541","SLSSA017553","SLSSA017565","SLSSA017570","SLSSA017582","SLSSA017594","SLSSA017606","SLSSA017611","SLSSA017623","SLSSA017635","SLSSA017640","SLSSA017652","SLSSA017664","SLSSA017676","SLSSA017681","SLSSA017693","SLSSA017705","SLSSA017710","SLSSA017722","SLSSA017734","SLSSA017746","SLSSA017751","SLSSA017763","SLSSA017775","SLSSA017780","SLSSA017792","SLSSA017804","SLSSA017816","SLSSA017821","SLSSA017833","SLSSA017845","SLSSA017850","SLSSA017862","SLSSA017874","SLSSA017886","SLSSA017891","SLSSA017903","SLSSA017944","SLSSA017956","SLSSA017961","SLSSA017973","SLSSA017985","SLSSA017990","SLSSA018002","SLSSA018014","SLSSA018026","SLSSA018031","SLSSA018043","SLSSA018055","SLSSA018060","SLSSA018072","SLSSA018084","SLSSA018096","SLSSA018101","SLSSA018113","SLSSA018125","SLSSA018130","SLSSA018142","SLSSA018154","SLSSA018166","SLSSA018183","SLSSA018195","SLSSA018200","SLSSA018212","SLSSA018224","SLSSA018236","SLSSA018241","SLSSA018253","SLSSA018265","SLSSA018270","SLSSA018282","SLSSA018294","SLSSA018306","SLSSA018311","SLSSA018323","SLSSA018335","SLSSA018340","SLSSA018352","SLSSA018364","SLSSA018376","SLSSA018381","SLSSA018393","SLSSA018405","SLSSA018410","SLSSA018422","SLSSA018446");
} //fin de if($IdEstado == "25")

//Condicion de estado-clues
if($IdEstado == "26"){
	$Clues = array("SRSSA000014","SRSSA000026","SRSSA000043","SRSSA000055","SRSSA000060","SRSSA000072","SRSSA000084","SRSSA000096","SRSSA000101","SRSSA000113","SRSSA000125","SRSSA000130","SRSSA000142","SRSSA000154","SRSSA000166","SRSSA000171","SRSSA000183","SRSSA000195","SRSSA000200","SRSSA000212","SRSSA000224","SRSSA000236","SRSSA000241","SRSSA000253","SRSSA000265","SRSSA000270","SRSSA000282","SRSSA000294","SRSSA000306","SRSSA000311","SRSSA000323","SRSSA000335","SRSSA000340","SRSSA000352","SRSSA000364","SRSSA000376","SRSSA000381","SRSSA000393","SRSSA000405","SRSSA000410","SRSSA000416","SRSSA000434","SRSSA000446","SRSSA000451","SRSSA000463","SRSSA000475","SRSSA000480","SRSSA000492","SRSSA000504","SRSSA000521","SRSSA000545","SRSSA000550","SRSSA000562","SRSSA000574","SRSSA000586","SRSSA000591","SRSSA000603","SRSSA000615","SRSSA000620","SRSSA000632","SRSSA000644","SRSSA000656","SRSSA000661","SRSSA000673","SRSSA000685","SRSSA000690","SRSSA000702","SRSSA000714","SRSSA000726","SRSSA000731","SRSSA000743","SRSSA000755","SRSSA000760","SRSSA000772","SRSSA000784","SRSSA000796","SRSSA000801","SRSSA000813","SRSSA000825","SRSSA000830","SRSSA000842","SRSSA000854","SRSSA000866","SRSSA000871","SRSSA000883","SRSSA000895","SRSSA000900","SRSSA000912","SRSSA000924","SRSSA000936","SRSSA000941","SRSSA000953","SRSSA000965","SRSSA000970","SRSSA000982","SRSSA000994","SRSSA001006","SRSSA001011","SRSSA001023","SRSSA001035","SRSSA001040","SRSSA001052","SRSSA001064","SRSSA001081","SRSSA001093","SRSSA001105","SRSSA001110","SRSSA001122","SRSSA001134","SRSSA001146","SRSSA001151","SRSSA001163","SRSSA001180","SRSSA001192","SRSSA001204","SRSSA001216","SRSSA001221","SRSSA001233","SRSSA001245","SRSSA001250","SRSSA001262","SRSSA001274","SRSSA001286","SRSSA001291","SRSSA001303","SRSSA001315","SRSSA001320","SRSSA001332","SRSSA001344","SRSSA001356","SRSSA001361","SRSSA001385","SRSSA001390","SRSSA001402","SRSSA001414","SRSSA001426","SRSSA001431","SRSSA001443","SRSSA001455","SRSSA001460","SRSSA001472","SRSSA001484","SRSSA001496","SRSSA001501","SRSSA001513","SRSSA001525","SRSSA001530","SRSSA001542","SRSSA001554","SRSSA001566","SRSSA001571","SRSSA001583","SRSSA001595","SRSSA001600","SRSSA001612","SRSSA001624","SRSSA001636","SRSSA001641","SRSSA001653","SRSSA001665","SRSSA001670","SRSSA001682","SRSSA001694","SRSSA001706","SRSSA001711","SRSSA001723","SRSSA001735","SRSSA001740","SRSSA001752","SRSSA001764","SRSSA001776","SRSSA001781","SRSSA001793","SRSSA001805","SRSSA001810","SRSSA001822","SRSSA001834","SRSSA001846","SRSSA001851","SRSSA001863","SRSSA001875","SRSSA001880","SRSSA001892","SRSSA001904","SRSSA001916","SRSSA001921","SRSSA001933","SRSSA001945","SRSSA001950","SRSSA001962","SRSSA001974","SRSSA001986","SRSSA001991","SRSSA002003","SRSSA002015","SRSSA002020","SRSSA002032","SRSSA002044","SRSSA002056","SRSSA002061","SRSSA002073","SRSSA002085","SRSSA002090","SRSSA002102","SRSSA002114","SRSSA002126","SRSSA002131","SRSSA002143","SRSSA002155","SRSSA002160","SRSSA002172","SRSSA002184","SRSSA002198","SRSSA002201","SRSSA002213","SRSSA002225","SRSSA002230","SRSSA002242","SRSSA002254","SRSSA002266","SRSSA002271","SRSSA002283","SRSSA002295","SRSSA002300","SRSSA002312","SRSSA002324","SRSSA002336","SRSSA002341","SRSSA002353","SRSSA002365","SRSSA002370","SRSSA002382","SRSSA002394","SRSSA002406","SRSSA002411","SRSSA002423","SRSSA002435","SRSSA002440","SRSSA002452","SRSSA002464","SRSSA002476","SRSSA002481","SRSSA002493","SRSSA002505","SRSSA002510","SRSSA002551","SRSSA002575","SRSSA002580","SRSSA002592","SRSSA002604","SRSSA002616","SRSSA002621","SRSSA002633","SRSSA002645","SRSSA002650","SRSSA002662","SRSSA002674","SRSSA002686","SRSSA002691","SRSSA002703","SRSSA002715","SRSSA002720","SRSSA002732","SRSSA002744","SRSSA002756","SRSSA002773","SRSSA002790","SRSSA002802","SRSSA002814","SRSSA002826","SRSSA002843","SRSSA002884","SRSSA002913","SRSSA002925","SRSSA002930","SRSSA002954","SRSSA002966","SRSSA002971","SRSSA002983","SRSSA003000","SRSSA003012","SRSSA003024","SRSSA003036","SRSSA003065","SRSSA003082","SRSSA003140","SRSSA003152","SRSSA003176","SRSSA003251","SRSSA003263","SRSSA003292","SRSSA003304","SRSSA003316","SRSSA003362","SRSSA003374","SRSSA003391","SRSSA003420","SRSSA003432","SRSSA003444","SRSSA003456","SRSSA003461","SRSSA003473","SRSSA003502","SRSSA003514","SRSSA003526","SRSSA003531","SRSSA003543","SRSSA003555","SRSSA003560","SRSSA003572","SRSSA003625","SRSSA003630","SRSSA003654","SRSSA003671","SRSSA003695","SRSSA003700","SRSSA003712","SRSSA003736","SRSSA003741","SRSSA003765","SRSSA003770","SRSSA003782","SRSSA003794","SRSSA003806","SRSSA003811","SRSSA003823","SRSSA003840","SRSSA003852","SRSSA003881","SRSSA003893","SRSSA003905","SRSSA003934","SRSSA004004","SRSSA004021","SRSSA004033","SRSSA004045","SRSSA004062","SRSSA004103","SRSSA004115","SRSSA004120","SRSSA004144","SRSSA004173","SRSSA004190","SRSSA004202","SRSSA004214","SRSSA004226","SRSSA004231","SRSSA004243","SRSSA004255","SRSSA004260","SRSSA004272","SRSSA004284","SRSSA004296","SRSSA004301","SRSSA004313","SRSSA004325","SRSSA004330","SRSSA004342","SRSSA004366","SRSSA004371","SRSSA004383","SRSSA004395","SRSSA004400","SRSSA004412","SRSSA004424","SRSSA004436","SRSSA004453","SRSSA004465","SRSSA004482","SRSSA004494","SRSSA004506","SRSSA004511","SRSSA004523","SRSSA004535","SRSSA004540","SRSSA004552","SRSSA004564","SRSSA004576","SRSSA004581","SRSSA004593","SRSSA004605","SRSSA004610","SRSSA004622","SRSSA004634","SRSSA004646","SRSSA004651","SRSSA004663","SRSSA004675","SRSSA004692","SRSSA004704","SRSSA004716","SRSSA004733","SRSSA004745","SRSSA004750","SRSSA004762","SRSSA004786","SRSSA004844","SRSSA004856","SRSSA004861","SRSSA004873","SRSSA004885","SRSSA004890","SRSSA004902","SRSSA004914","SRSSA004926","SRSSA004943","SRSSA004960","SRSSA004996","SRSSA005001","SRSSA005013","SRSSA005025","SRSSA005030","SRSSA005042","SRSSA005054","SRSSA005083","SRSSA005095","SRSSA005100","SRSSA005112","SRSSA005124","SRSSA005136","SRSSA005153","SRSSA005165","SRSSA005170","SRSSA005182","SRSSA005211","SRSSA005223","SRSSA005235","SRSSA005240","SRSSA005252","SRSSA005276","SRSSA005281","SRSSA005293","SRSSA005305","SRSSA005310","SRSSA005346","SRSSA005351","SRSSA005375","SRSSA005380","SRSSA005392","SRSSA005404","SRSSA005416","SRSSA005421","SRSSA005433","SRSSA005445","SRSSA005474","SRSSA005486","SRSSA005491","SRSSA005503","SRSSA005532","SRSSA005556","SRSSA005561","SRSSA005573","SRSSA005590","SRSSA005602","SRSSA005626","SRSSA005631","SRSSA005643","SRSSA005684","SRSSA005696","SRSSA005701","SRSSA005725","SRSSA005730","SRSSA005836","SRSSA005841","SRSSA005865","SRSSA005870","SRSSA005894","SRSSA005906","SRSSA005911","SRSSA005923","SRSSA005935","SRSSA005952","SRSSA005964","SRSSA005976","SRSSA005981","SRSSA006075","SRSSA006121","SRSSA006145","SRSSA006174","SRSSA006186","SRSSA006191","SRSSA006203","SRSSA017444","SRSSA017450","SRSSA017462","SRSSA017474","SRSSA017486","SRSSA017491","SRSSA017503","SRSSA017515","SRSSA017520","SRSSA017532","SRSSA017544","SRSSA017556","SRSSA017561","SRSSA017573","SRSSA017585","SRSSA017590","SRSSA017602","SRSSA017614","SRSSA017626","SRSSA017631","SRSSA017643","SRSSA017655","SRSSA017666","SRSSA017671","SRSSA017683","SRSSA017695","SRSSA017700","SRSSA017712","SRSSA017736","SRSSA017741","SRSSA017753","SRSSA017765","SRSSA017770","SRSSA017806","SRSSA017811","SRSSA017835","SRSSA017840","SRSSA017852","SRSSA017864","SRSSA017876","SRSSA017893","SRSSA017905","SRSSA018004","SRSSA018016","SRSSA018021","SRSSA018045","SRSSA018050","SRSSA018062","SRSSA018074","SRSSA018086","SRSSA018103","SRSSA018115","SRSSA018120","SRSSA018132","SRSSA018156","SRSSA018161","SRSSA018173","SRSSA018185","SRSSA018190","SRSSA018202","SRSSA018214","SRSSA018226","SRSSA018231","SRSSA018243","SRSSA018255","SRSSA018260","SRSSA018272","SRSSA018284","SRSSA018296","SRSSA018301","SRSSA018313","SRSSA018325","SRSSA018330","SRSSA018342","SRSSA018366","SRSSA018371","SRSSA018395","SRSSA018400","SRSSA018412","SRSSA018424","SRSSA018436","SRSSA018441","SRSSA018453","SRSSA018465","SRSSA018470","SRSSA018482");
} //fin de if($IdEstado == "26")

//Condicion de estado-clues
if($IdEstado == "27"){
	$Clues = array("TCSSA000014","TCSSA000031","TCSSA000043","TCSSA000055","TCSSA000060","TCSSA000096","TCSSA000101","TCSSA000113","TCSSA000125","TCSSA000130","TCSSA000142","TCSSA000154","TCSSA000166","TCSSA000171","TCSSA000183","TCSSA000195","TCSSA000200","TCSSA000212","TCSSA000224","TCSSA000236","TCSSA000241","TCSSA000253","TCSSA000265","TCSSA000270","TCSSA000282","TCSSA000294","TCSSA000306","TCSSA000335","TCSSA000340","TCSSA000352","TCSSA000364","TCSSA000376","TCSSA000381","TCSSA000405","TCSSA000410","TCSSA000422","TCSSA000434","TCSSA000446","TCSSA000451","TCSSA000463","TCSSA000475","TCSSA000480","TCSSA000504","TCSSA000516","TCSSA000521","TCSSA000533","TCSSA000545","TCSSA000550","TCSSA000562","TCSSA000574","TCSSA000586","TCSSA000591","TCSSA000603","TCSSA000615","TCSSA000632","TCSSA000644","TCSSA000656","TCSSA000661","TCSSA000673","TCSSA000685","TCSSA000726","TCSSA000743","TCSSA000755","TCSSA000760","TCSSA000772","TCSSA000784","TCSSA000796","TCSSA000801","TCSSA000813","TCSSA000825","TCSSA000830","TCSSA000842","TCSSA000854","TCSSA000866","TCSSA000871","TCSSA000883","TCSSA000895","TCSSA000900","TCSSA000912","TCSSA000924","TCSSA000936","TCSSA000941","TCSSA000953","TCSSA000965","TCSSA000970","TCSSA000982","TCSSA000994","TCSSA001006","TCSSA001023","TCSSA001035","TCSSA001040","TCSSA001052","TCSSA001064","TCSSA001076","TCSSA001081","TCSSA001163","TCSSA001175","TCSSA001180","TCSSA001192","TCSSA001204","TCSSA001216","TCSSA001221","TCSSA001233","TCSSA001245","TCSSA001250","TCSSA001262","TCSSA001274","TCSSA001286","TCSSA001291","TCSSA001303","TCSSA001315","TCSSA001320","TCSSA001332","TCSSA001344","TCSSA001356","TCSSA001361","TCSSA001373","TCSSA001385","TCSSA001390","TCSSA001402","TCSSA001414","TCSSA001426","TCSSA001431","TCSSA001443","TCSSA001455","TCSSA001460","TCSSA001472","TCSSA001484","TCSSA001496","TCSSA001501","TCSSA001513","TCSSA001525","TCSSA001542","TCSSA001554","TCSSA001566","TCSSA001571","TCSSA001583","TCSSA001595","TCSSA001600","TCSSA001612","TCSSA001624","TCSSA001636","TCSSA001653","TCSSA001706","TCSSA001711","TCSSA001723","TCSSA001735","TCSSA001740","TCSSA001752","TCSSA001764","TCSSA001776","TCSSA001781","TCSSA001793","TCSSA001805","TCSSA001810","TCSSA001822","TCSSA001834","TCSSA001846","TCSSA001851","TCSSA001863","TCSSA001875","TCSSA001880","TCSSA001892","TCSSA001904","TCSSA001916","TCSSA001921","TCSSA001933","TCSSA001945","TCSSA001950","TCSSA001974","TCSSA001986","TCSSA001991","TCSSA002003","TCSSA002061","TCSSA002073","TCSSA002085","TCSSA002090","TCSSA002102","TCSSA002114","TCSSA002126","TCSSA002131","TCSSA002143","TCSSA002155","TCSSA002160","TCSSA002172","TCSSA002184","TCSSA002196","TCSSA002201","TCSSA002213","TCSSA002225","TCSSA002230","TCSSA002242","TCSSA002254","TCSSA002266","TCSSA002271","TCSSA002283","TCSSA002295","TCSSA002300","TCSSA002312","TCSSA002324","TCSSA002336","TCSSA002341","TCSSA002353","TCSSA002370","TCSSA002382","TCSSA002394","TCSSA002406","TCSSA002411","TCSSA002423","TCSSA002440","TCSSA002464","TCSSA002481","TCSSA002493","TCSSA002505","TCSSA002510","TCSSA002522","TCSSA002534","TCSSA002546","TCSSA002551","TCSSA002563","TCSSA002575","TCSSA002580","TCSSA002592","TCSSA002604","TCSSA002616","TCSSA002621","TCSSA002633","TCSSA002645","TCSSA002650","TCSSA002662","TCSSA002674","TCSSA002686","TCSSA002691","TCSSA002703","TCSSA002715","TCSSA002720","TCSSA002732","TCSSA002756","TCSSA002761","TCSSA002773","TCSSA002785","TCSSA002802","TCSSA002814","TCSSA002831","TCSSA002843","TCSSA002855","TCSSA002860","TCSSA002872","TCSSA002884","TCSSA002896","TCSSA002901","TCSSA002913","TCSSA002925","TCSSA002930","TCSSA002942","TCSSA002954","TCSSA002966","TCSSA002971","TCSSA003024","TCSSA003036","TCSSA003041","TCSSA003053","TCSSA003065","TCSSA003070","TCSSA003082","TCSSA003094","TCSSA003106","TCSSA003111","TCSSA003123","TCSSA003135","TCSSA003164","TCSSA003176","TCSSA003181","TCSSA003193","TCSSA003205","TCSSA003210","TCSSA003222","TCSSA003234","TCSSA003246","TCSSA003251","TCSSA003263","TCSSA003275","TCSSA003280","TCSSA003292","TCSSA003304","TCSSA003316","TCSSA003333","TCSSA003350","TCSSA003386","TCSSA003391","TCSSA003403","TCSSA003415","TCSSA003420","TCSSA003432","TCSSA003444","TCSSA003456","TCSSA003461","TCSSA003473","TCSSA003485","TCSSA003490","TCSSA003502","TCSSA003514","TCSSA003526","TCSSA003584","TCSSA003596","TCSSA003601","TCSSA003613","TCSSA003625","TCSSA003630","TCSSA003642","TCSSA003654","TCSSA003666","TCSSA003671","TCSSA003683","TCSSA003695","TCSSA003700","TCSSA003712","TCSSA003724","TCSSA003736","TCSSA003741","TCSSA003753","TCSSA003765","TCSSA003770","TCSSA003806","TCSSA003811","TCSSA003823","TCSSA003835","TCSSA003840","TCSSA003852","TCSSA003864","TCSSA003876","TCSSA003881","TCSSA003893","TCSSA003905","TCSSA003910","TCSSA003922","TCSSA003934","TCSSA003946","TCSSA003951","TCSSA003963","TCSSA003980","TCSSA003992","TCSSA004004","TCSSA004016","TCSSA004021","TCSSA004033","TCSSA004045","TCSSA004050","TCSSA004062","TCSSA004074","TCSSA004086","TCSSA004091","TCSSA004103","TCSSA004115","TCSSA004120","TCSSA004132","TCSSA004144","TCSSA004156","TCSSA004161","TCSSA004173","TCSSA004185","TCSSA004202","TCSSA004214","TCSSA004226","TCSSA004231","TCSSA004243","TCSSA004255","TCSSA004260","TCSSA004272","TCSSA004284","TCSSA004296","TCSSA004301","TCSSA004313","TCSSA004325","TCSSA004330","TCSSA004366","TCSSA004371","TCSSA004383","TCSSA004395","TCSSA004400","TCSSA004412","TCSSA004424","TCSSA004436","TCSSA004441","TCSSA004453","TCSSA004465","TCSSA004470","TCSSA004494","TCSSA004506","TCSSA004511","TCSSA004523","TCSSA004535","TCSSA004540","TCSSA004552","TCSSA004564","TCSSA004576","TCSSA004581","TCSSA004593","TCSSA004605","TCSSA004610","TCSSA004622","TCSSA004634","TCSSA004646","TCSSA004651","TCSSA004663","TCSSA004675","TCSSA004680","TCSSA004692","TCSSA004704","TCSSA004716","TCSSA004721","TCSSA004733","TCSSA004745","TCSSA004750","TCSSA004762","TCSSA004774","TCSSA004786","TCSSA004791","TCSSA004803","TCSSA004815","TCSSA004820","TCSSA004832","TCSSA004844","TCSSA004861","TCSSA004873","TCSSA004885","TCSSA004890","TCSSA004902","TCSSA004914","TCSSA004926","TCSSA004943","TCSSA004955","TCSSA004960","TCSSA004972","TCSSA004984","TCSSA005001","TCSSA005013","TCSSA005025","TCSSA005030","TCSSA005042","TCSSA005054","TCSSA005066","TCSSA005071","TCSSA005083","TCSSA005095","TCSSA005100","TCSSA005112","TCSSA005124","TCSSA005136","TCSSA005153","TCSSA005165","TCSSA005170","TCSSA005182","TCSSA005194","TCSSA005211","TCSSA005235","TCSSA005240","TCSSA005252","TCSSA005264","TCSSA005276","TCSSA005281","TCSSA005293","TCSSA005305","TCSSA005310","TCSSA005322","TCSSA005334","TCSSA005346","TCSSA005351","TCSSA005363","TCSSA005392","TCSSA005404","TCSSA005416","TCSSA005421","TCSSA005433","TCSSA005445","TCSSA005450","TCSSA005462","TCSSA005474","TCSSA005486","TCSSA005491","TCSSA005503","TCSSA005515","TCSSA005520","TCSSA005532","TCSSA005544","TCSSA005556","TCSSA005561","TCSSA005573","TCSSA005585","TCSSA005590","TCSSA005602","TCSSA005614","TCSSA005626","TCSSA005631","TCSSA005643","TCSSA005655","TCSSA005660","TCSSA005672","TCSSA005684","TCSSA005701","TCSSA005713","TCSSA005725","TCSSA005742","TCSSA005754","TCSSA005766","TCSSA005771","TCSSA005783","TCSSA005795","TCSSA005976","TCSSA005981","TCSSA005993","TCSSA006005","TCSSA006010","TCSSA006022","TCSSA006051","TCSSA006063","TCSSA006075","TCSSA006080","TCSSA006092","TCSSA006104","TCSSA006116","TCSSA006121","TCSSA006145","TCSSA006150","TCSSA006162","TCSSA006174","TCSSA006186","TCSSA006191","TCSSA006215","TCSSA006220","TCSSA006232","TCSSA006244","TCSSA016371","TCSSA016383","TCSSA016395","TCSSA016400","TCSSA016412","TCSSA016424","TCSSA016436","TCSSA016441","TCSSA016453","TCSSA016465","TCSSA016470","TCSSA016482","TCSSA016494","TCSSA016506","TCSSA016511","TCSSA016523","TCSSA016535","TCSSA016540","TCSSA016552","TCSSA016564","TCSSA016576","TCSSA016581","TCSSA016605","TCSSA016610","TCSSA016622","TCSSA016634","TCSSA016646","TCSSA016651","TCSSA016663","TCSSA016675","TCSSA016680","TCSSA016692","TCSSA016704","TCSSA016716","TCSSA016721","TCSSA016733","TCSSA016744","TCSSA016756","TCSSA016761","TCSSA016773","TCSSA016785","TCSSA016831","TCSSA016843","TCSSA016855","TCSSA016860","TCSSA016872","TCSSA016884","TCSSA016896","TCSSA016901","TCSSA016913","TCSSA016925","TCSSA016930","TCSSA016942","TCSSA016954","TCSSA016966","TCSSA016983","TCSSA016995","TCSSA017000","TCSSA017012","TCSSA017024","TCSSA017036","TCSSA017041","TCSSA017053","TCSSA017065","TCSSA017070","TCSSA017082","TCSSA017094","TCSSA017106","TCSSA017111","TCSSA017123","TCSSA017135","TCSSA017140","TCSSA017152","TCSSA017164","TCSSA017176","TCSSA017181","TCSSA017193","TCSSA017205","TCSSA017210","TCSSA017222","TCSSA017234","TCSSA017246","TCSSA017251","TCSSA017263","TCSSA017275","TCSSA017280","TCSSA017292","TCSSA017304","TCSSA017316","TCSSA017321","TCSSA017333","TCSSA017345","TCSSA017350","TCSSA017362","TCSSA017374","TCSSA017386","TCSSA017391","TCSSA017403","TCSSA017415","TCSSA017420","TCSSA017432","TCSSA017444","TCSSA017456","TCSSA017461","TCSSA017473","TCSSA017485","TCSSA017490","TCSSA017502","TCSSA017514","TCSSA017526","TCSSA017531","TCSSA017543","TCSSA017555","TCSSA017560","TCSSA017572","TCSSA017584","TCSSA017596","TCSSA017601","TCSSA017613","TCSSA017625","TCSSA017630","TCSSA017642","TCSSA017654","TCSSA017666","TCSSA017671","TCSSA017683","TCSSA017695","TCSSA017700","TCSSA017712","TCSSA017724","TCSSA017736","TCSSA017741","TCSSA017753","TCSSA017765","TCSSA017770","TCSSA017782");
} //fin de if($IdEstado == "27")

//Condicion de estado-clues
if($IdEstado == "28"){
	$Clues = array("TSSSA000010","TSSSA000022","TSSSA000034","TSSSA000046","TSSSA000051","TSSSA000063","TSSSA000075","TSSSA000092","TSSSA000104","TSSSA000116","TSSSA000121","TSSSA000145","TSSSA000150","TSSSA000162","TSSSA000174","TSSSA000186","TSSSA000191","TSSSA000203","TSSSA000215","TSSSA000220","TSSSA000232","TSSSA000244","TSSSA000256","TSSSA000261","TSSSA000273","TSSSA000285","TSSSA000290","TSSSA000302","TSSSA000326","TSSSA000331","TSSSA000372","TSSSA000384","TSSSA000396","TSSSA000401","TSSSA000413","TSSSA000425","TSSSA000442","TSSSA000454","TSSSA000466","TSSSA000483","TSSSA000495","TSSSA000500","TSSSA000512","TSSSA000524","TSSSA000536","TSSSA000553","TSSSA000565","TSSSA000582","TSSSA000594","TSSSA000611","TSSSA000623","TSSSA000635","TSSSA000676","TSSSA000681","TSSSA000693","TSSSA000705","TSSSA000710","TSSSA000722","TSSSA000734","TSSSA000746","TSSSA000763","TSSSA000775","TSSSA000780","TSSSA000792","TSSSA000804","TSSSA000816","TSSSA000821","TSSSA000833","TSSSA000845","TSSSA000874","TSSSA000886","TSSSA000891","TSSSA000903","TSSSA000915","TSSSA000920","TSSSA000932","TSSSA000944","TSSSA000961","TSSSA000973","TSSSA000985","TSSSA000990","TSSSA001002","TSSSA001014","TSSSA001026","TSSSA001031","TSSSA001096","TSSSA001101","TSSSA001113","TSSSA001125","TSSSA001130","TSSSA001142","TSSSA001154","TSSSA001166","TSSSA001171","TSSSA001183","TSSSA001195","TSSSA001212","TSSSA001253","TSSSA001265","TSSSA001270","TSSSA001294","TSSSA001306","TSSSA001311","TSSSA001323","TSSSA001335","TSSSA001340","TSSSA001352","TSSSA001364","TSSSA001376","TSSSA001381","TSSSA001393","TSSSA001405","TSSSA001410","TSSSA001422","TSSSA001434","TSSSA001446","TSSSA001451","TSSSA001463","TSSSA001475","TSSSA001492","TSSSA001504","TSSSA001516","TSSSA001521","TSSSA001533","TSSSA001545","TSSSA001550","TSSSA001562","TSSSA001586","TSSSA001615","TSSSA001620","TSSSA001632","TSSSA001644","TSSSA001656","TSSSA001661","TSSSA001673","TSSSA001685","TSSSA001702","TSSSA001714","TSSSA001726","TSSSA001731","TSSSA001755","TSSSA001760","TSSSA001772","TSSSA001825","TSSSA001854","TSSSA001866","TSSSA001871","TSSSA001883","TSSSA001895","TSSSA001900","TSSSA001912","TSSSA001924","TSSSA001936","TSSSA001941","TSSSA001953","TSSSA001965","TSSSA001982","TSSSA001994","TSSSA002011","TSSSA002035","TSSSA002040","TSSSA002052","TSSSA002093","TSSSA002110","TSSSA002122","TSSSA002134","TSSSA002146","TSSSA002151","TSSSA002163","TSSSA002175","TSSSA002192","TSSSA002221","TSSSA002233","TSSSA002245","TSSSA002250","TSSSA002262","TSSSA002274","TSSSA002286","TSSSA002291","TSSSA002303","TSSSA002315","TSSSA002320","TSSSA002332","TSSSA002344","TSSSA002356","TSSSA002361","TSSSA002373","TSSSA002402","TSSSA002414","TSSSA002426","TSSSA002431","TSSSA002443","TSSSA002460","TSSSA002484","TSSSA002496","TSSSA002501","TSSSA002530","TSSSA002542","TSSSA002554","TSSSA002566","TSSSA002571","TSSSA002583","TSSSA002595","TSSSA002600","TSSSA002612","TSSSA002624","TSSSA002636","TSSSA002641","TSSSA002653","TSSSA002665","TSSSA002711","TSSSA002723","TSSSA002735","TSSSA002740","TSSSA002764","TSSSA002776","TSSSA002781","TSSSA002793","TSSSA002805","TSSSA002810","TSSSA002846","TSSSA002851","TSSSA002863","TSSSA002875","TSSSA002880","TSSSA002892","TSSSA002904","TSSSA002916","TSSSA002921","TSSSA002933","TSSSA002945","TSSSA002950","TSSSA002962","TSSSA002974","TSSSA002991","TSSSA003003","TSSSA003032","TSSSA003056","TSSSA003061","TSSSA003073","TSSSA003085","TSSSA003090","TSSSA003114","TSSSA003131","TSSSA003143","TSSSA003155","TSSSA003160","TSSSA003172","TSSSA003184","TSSSA017535","TSSSA017540","TSSSA017552","TSSSA017564","TSSSA017576","TSSSA017581","TSSSA017593","TSSSA017605","TSSSA017610","TSSSA017622","TSSSA017634","TSSSA017646","TSSSA017651","TSSSA017663","TSSSA017675","TSSSA017680","TSSSA017692","TSSSA017704","TSSSA017716","TSSSA017721","TSSSA017733","TSSSA017745","TSSSA017750","TSSSA017762","TSSSA017774","TSSSA017786","TSSSA017791","TSSSA017803","TSSSA017814","TSSSA017826","TSSSA017831","TSSSA017843","TSSSA017860","TSSSA017872","TSSSA017884","TSSSA017896","TSSSA017901","TSSSA017913","TSSSA017925","TSSSA017930","TSSSA017942","TSSSA017954","TSSSA017971","TSSSA017983","TSSSA017995","TSSSA018000","TSSSA018012","TSSSA018024","TSSSA018036","TSSSA018041","TSSSA018053","TSSSA018065","TSSSA018070","TSSSA018082","TSSSA018094","TSSSA018106","TSSSA018111","TSSSA018123","TSSSA018135","TSSSA018140","TSSSA018152","TSSSA018164","TSSSA018176","TSSSA018181","TSSSA018193","TSSSA018205","TSSSA018210","TSSSA018222","TSSSA018234","TSSSA018246","TSSSA018251","TSSSA018263","TSSSA018275","TSSSA018280","TSSSA018292","TSSSA018304","TSSSA018316","TSSSA018321","TSSSA018333","TSSSA018345","TSSSA018350","TSSSA018362","TSSSA018374","TSSSA018386","TSSSA018403","TSSSA018415","TSSSA018420","TSSSA018432","TSSSA018444","TSSSA018456","TSSSA018461","TSSSA018473","TSSSA018485","TSSSA018490","TSSSA018502","TSSSA018514","TSSSA018526","TSSSA018531","TSSSA018543","TSSSA018555","TSSSA018560","TSSSA018572","TSSSA018584","TSSSA018596","TSSSA018601","TSSSA018613","TSSSA018625","TSSSA018630","TSSSA018642","TSSSA018654","TSSSA018666","TSSSA018671","TSSSA018683","TSSSA018695","TSSSA018700","TSSSA018712","TSSSA018724","TSSSA018741","TSSSA018753","TSSSA018765","TSSSA018770","TSSSA018782","TSSSA018794","TSSSA018806","TSSSA018811","TSSSA018823","TSSSA018835","TSSSA018840","TSSSA018852","TSSSA018864","TSSSA018876","TSSSA018881","TSSSA018893","TSSSA018905","TSSSA018910","TSSSA018922","TSSSA018934","TSSSA018946","TSSSA018951","TSSSA018963","TSSSA018975","TSSSA018980","TSSSA018992","TSSSA019004","TSSSA019016","TSSSA019021","TSSSA019033","TSSSA019045","TSSSA019050","TSSSA019062","TSSSA019074","TSSSA019086","TSSSA019091","TSSSA019103","TSSSA019115","TSSSA019120","TSSSA019132","TSSSA019144","TSSSA019156","TSSSA019161","TSSSA019173","TSSSA019185","TSSSA019190","TSSSA019202","TSSSA019214","TSSSA019226","TSSSA019231","TSSSA019243","TSSSA019255","TSSSA019260","TSSSA019272","TSSSA019284","TSSSA019296","TSSSA019301","TSSSA019313","TSSSA019325","TSSSA019330","TSSSA019342","TSSSA019354","TSSSA019366","TSSSA019371","TSSSA019383","TSSSA019395","TSSSA019400","TSSSA019412","TSSSA019424","TSSSA019436","TSSSA019441");
} //fin de if($IdEstado == "28")

//Condicion de estado-clues
if($IdEstado == "29"){
	$Clues = array("TLSSA000010","TLSSA000022","TLSSA000034","TLSSA000051","TLSSA000063","TLSSA000075","TLSSA000080","TLSSA000092","TLSSA000104","TLSSA000116","TLSSA000121","TLSSA000133","TLSSA000145","TLSSA000150","TLSSA000162","TLSSA000174","TLSSA000186","TLSSA000191","TLSSA000203","TLSSA000215","TLSSA000220","TLSSA000232","TLSSA000244","TLSSA000256","TLSSA000261","TLSSA000273","TLSSA000285","TLSSA000290","TLSSA000302","TLSSA000314","TLSSA000326","TLSSA000343","TLSSA000355","TLSSA000360","TLSSA000372","TLSSA000384","TLSSA000396","TLSSA000401","TLSSA000413","TLSSA000425","TLSSA000430","TLSSA000442","TLSSA000454","TLSSA000466","TLSSA000471","TLSSA000495","TLSSA000500","TLSSA000512","TLSSA000524","TLSSA000536","TLSSA000541","TLSSA000553","TLSSA000565","TLSSA000570","TLSSA000582","TLSSA000594","TLSSA000606","TLSSA000611","TLSSA000623","TLSSA000635","TLSSA000640","TLSSA000652","TLSSA000664","TLSSA000676","TLSSA000681","TLSSA000693","TLSSA000705","TLSSA000710","TLSSA000722","TLSSA000734","TLSSA000746","TLSSA000751","TLSSA000763","TLSSA000775","TLSSA000780","TLSSA000792","TLSSA000804","TLSSA000816","TLSSA000821","TLSSA000833","TLSSA000845","TLSSA000850","TLSSA000862","TLSSA000874","TLSSA000886","TLSSA000891","TLSSA000903","TLSSA000915","TLSSA000920","TLSSA000932","TLSSA000944","TLSSA000956","TLSSA000961","TLSSA000973","TLSSA000985","TLSSA000990","TLSSA001002","TLSSA001014","TLSSA001026","TLSSA001031","TLSSA001043","TLSSA001055","TLSSA001060","TLSSA001072","TLSSA001084","TLSSA001096","TLSSA001101","TLSSA001113","TLSSA001125","TLSSA001130","TLSSA001142","TLSSA001166","TLSSA001183","TLSSA001195","TLSSA001200","TLSSA001212","TLSSA001224","TLSSA001236","TLSSA001241","TLSSA001253","TLSSA001265","TLSSA001270","TLSSA001282","TLSSA001294","TLSSA001306","TLSSA001311","TLSSA001323","TLSSA001335","TLSSA001340","TLSSA001352","TLSSA001364","TLSSA001376","TLSSA001381","TLSSA001393","TLSSA001405","TLSSA001410","TLSSA001422","TLSSA001434","TLSSA001446","TLSSA001451","TLSSA001463","TLSSA001475","TLSSA001480","TLSSA001492","TLSSA001504","TLSSA001516","TLSSA001521","TLSSA001533","TLSSA001545","TLSSA001550","TLSSA001562","TLSSA001574","TLSSA001586","TLSSA001591","TLSSA001603","TLSSA001615","TLSSA001620","TLSSA001632","TLSSA001644","TLSSA001656","TLSSA001661","TLSSA001673","TLSSA001685","TLSSA001690","TLSSA001702","TLSSA001714","TLSSA001726","TLSSA001731","TLSSA001743","TLSSA001755","TLSSA001772","TLSSA017540","TLSSA017552","TLSSA017564","TLSSA017576","TLSSA017581","TLSSA017593","TLSSA017605","TLSSA017610","TLSSA017634","TLSSA017645","TLSSA017650","TLSSA017662","TLSSA017686","TLSSA017703","TLSSA017715","TLSSA017720","TLSSA017732","TLSSA017773","TLSSA017790","TLSSA017802","TLSSA017814","TLSSA017826","TLSSA017831","TLSSA017843","TLSSA017860","TLSSA017872","TLSSA017884","TLSSA017896","TLSSA017901","TLSSA017913","TLSSA017925","TLSSA017930","TLSSA017942","TLSSA017954","TLSSA017966","TLSSA017971","TLSSA017983","TLSSA017995","TLSSA018000","TLSSA018012","TLSSA018024");
} //fin de if($IdEstado == "29")

//Condicion de estado-clues
if($IdEstado == "30"){
	$Clues = array("VZSSA000013","VZSSA000025","VZSSA000030","VZSSA000042","VZSSA000066","VZSSA000071","VZSSA000083","VZSSA000095","VZSSA000100","VZSSA000112","VZSSA000124","VZSSA000136","VZSSA000141","VZSSA000153","VZSSA000165","VZSSA000170","VZSSA000194","VZSSA000206","VZSSA000211","VZSSA000223","VZSSA000235","VZSSA000240","VZSSA000252","VZSSA000264","VZSSA000281","VZSSA000293","VZSSA000310","VZSSA000322","VZSSA000346","VZSSA000351","VZSSA000363","VZSSA000375","VZSSA000380","VZSSA000392","VZSSA000404","VZSSA000416","VZSSA000421","VZSSA000433","VZSSA000445","VZSSA000450","VZSSA000474","VZSSA000486","VZSSA000491","VZSSA000515","VZSSA000532","VZSSA000544","VZSSA000556","VZSSA000561","VZSSA000573","VZSSA000585","VZSSA000590","VZSSA000602","VZSSA000614","VZSSA000626","VZSSA000631","VZSSA000643","VZSSA000655","VZSSA000660","VZSSA000672","VZSSA000684","VZSSA000696","VZSSA000701","VZSSA000713","VZSSA000730","VZSSA000742","VZSSA000754","VZSSA000766","VZSSA000771","VZSSA000783","VZSSA000795","VZSSA000800","VZSSA000812","VZSSA000824","VZSSA000836","VZSSA000841","VZSSA000853","VZSSA000870","VZSSA000882","VZSSA000894","VZSSA000906","VZSSA000911","VZSSA000923","VZSSA000935","VZSSA000940","VZSSA000952","VZSSA000976","VZSSA000981","VZSSA000993","VZSSA001005","VZSSA001022","VZSSA001046","VZSSA001063","VZSSA001080","VZSSA001092","VZSSA001104","VZSSA001116","VZSSA001121","VZSSA001133","VZSSA001145","VZSSA001150","VZSSA001162","VZSSA001174","VZSSA001186","VZSSA001191","VZSSA001203","VZSSA001215","VZSSA001220","VZSSA001232","VZSSA001244","VZSSA001256","VZSSA001261","VZSSA001273","VZSSA001290","VZSSA001302","VZSSA001314","VZSSA001326","VZSSA001343","VZSSA001355","VZSSA001372","VZSSA001384","VZSSA001396","VZSSA001401","VZSSA001425","VZSSA001430","VZSSA001442","VZSSA001454","VZSSA001466","VZSSA001471","VZSSA001483","VZSSA001495","VZSSA001500","VZSSA001512","VZSSA001524","VZSSA001536","VZSSA001541","VZSSA001553","VZSSA001565","VZSSA001570","VZSSA001582","VZSSA001594","VZSSA001606","VZSSA001611","VZSSA001623","VZSSA001635","VZSSA001640","VZSSA001652","VZSSA001664","VZSSA001676","VZSSA001681","VZSSA001693","VZSSA001705","VZSSA001710","VZSSA001722","VZSSA001734","VZSSA001746","VZSSA001751","VZSSA001763","VZSSA001775","VZSSA001780","VZSSA001792","VZSSA001804","VZSSA001816","VZSSA001821","VZSSA001833","VZSSA001845","VZSSA001850","VZSSA001862","VZSSA001874","VZSSA001886","VZSSA001891","VZSSA001903","VZSSA001915","VZSSA001920","VZSSA001932","VZSSA001944","VZSSA001956","VZSSA001961","VZSSA001973","VZSSA001990","VZSSA002002","VZSSA002014","VZSSA002026","VZSSA002031","VZSSA002043","VZSSA002055","VZSSA002060","VZSSA002072","VZSSA002084","VZSSA002096","VZSSA002101","VZSSA002113","VZSSA002125","VZSSA002130","VZSSA002142","VZSSA002154","VZSSA002171","VZSSA002183","VZSSA002195","VZSSA002212","VZSSA002224","VZSSA002236","VZSSA002241","VZSSA002253","VZSSA002265","VZSSA002270","VZSSA002282","VZSSA002294","VZSSA002306","VZSSA002311","VZSSA002323","VZSSA002335","VZSSA002340","VZSSA002352","VZSSA002364","VZSSA002376","VZSSA002381","VZSSA002393","VZSSA002405","VZSSA002410","VZSSA002422","VZSSA002434","VZSSA002446","VZSSA002451","VZSSA002463","VZSSA002475","VZSSA002480","VZSSA002492","VZSSA002504","VZSSA002521","VZSSA002545","VZSSA002550","VZSSA002562","VZSSA002574","VZSSA002586","VZSSA002591","VZSSA002603","VZSSA002620","VZSSA002644","VZSSA002656","VZSSA002673","VZSSA002685","VZSSA002690","VZSSA002702","VZSSA002714","VZSSA002726","VZSSA002731","VZSSA002743","VZSSA002755","VZSSA002760","VZSSA002772","VZSSA002784","VZSSA002796","VZSSA002813","VZSSA002825","VZSSA002830","VZSSA002842","VZSSA002854","VZSSA002866","VZSSA002871","VZSSA002883","VZSSA002900","VZSSA002912","VZSSA002924","VZSSA002936","VZSSA002941","VZSSA002953","VZSSA002965","VZSSA002970","VZSSA002982","VZSSA003006","VZSSA003011","VZSSA003023","VZSSA003035","VZSSA003040","VZSSA003052","VZSSA003064","VZSSA003076","VZSSA003081","VZSSA003093","VZSSA003105","VZSSA003110","VZSSA003122","VZSSA003146","VZSSA003151","VZSSA003163","VZSSA003175","VZSSA003180","VZSSA003192","VZSSA003204","VZSSA003216","VZSSA003221","VZSSA003233","VZSSA003245","VZSSA003250","VZSSA003262","VZSSA003274","VZSSA003286","VZSSA003291","VZSSA003315","VZSSA003320","VZSSA003344","VZSSA003356","VZSSA003361","VZSSA003373","VZSSA003385","VZSSA003390","VZSSA003402","VZSSA003414","VZSSA003426","VZSSA003431","VZSSA003443","VZSSA003460","VZSSA003472","VZSSA003484","VZSSA003496","VZSSA003501","VZSSA003513","VZSSA003525","VZSSA003530","VZSSA003542","VZSSA003554","VZSSA003566","VZSSA003571","VZSSA003583","VZSSA003595","VZSSA003600","VZSSA003612","VZSSA003624","VZSSA003636","VZSSA003641","VZSSA003653","VZSSA003665","VZSSA003670","VZSSA003682","VZSSA003706","VZSSA003723","VZSSA003735","VZSSA003740","VZSSA003752","VZSSA003764","VZSSA003776","VZSSA003781","VZSSA003793","VZSSA003805","VZSSA003810","VZSSA003822","VZSSA003834","VZSSA003846","VZSSA003851","VZSSA003863","VZSSA003875","VZSSA003892","VZSSA003904","VZSSA003916","VZSSA003921","VZSSA003933","VZSSA003945","VZSSA003950","VZSSA003962","VZSSA003974","VZSSA003986","VZSSA003991","VZSSA004003","VZSSA004015","VZSSA004020","VZSSA004032","VZSSA004044","VZSSA004056","VZSSA004061","VZSSA004073","VZSSA004085","VZSSA004102","VZSSA004114","VZSSA004126","VZSSA004131","VZSSA004143","VZSSA004155","VZSSA004160","VZSSA004172","VZSSA004184","VZSSA004196","VZSSA004201","VZSSA004213","VZSSA004225","VZSSA004230","VZSSA004242","VZSSA004254","VZSSA004271","VZSSA004283","VZSSA004295","VZSSA004300","VZSSA004312","VZSSA004324","VZSSA004336","VZSSA004341","VZSSA004353","VZSSA004365","VZSSA004370","VZSSA004382","VZSSA004394","VZSSA004406","VZSSA004411","VZSSA004423","VZSSA004435","VZSSA004440","VZSSA004452","VZSSA004464","VZSSA004476","VZSSA004481","VZSSA004493","VZSSA004505","VZSSA004510","VZSSA004522","VZSSA004534","VZSSA004546","VZSSA004551","VZSSA004563","VZSSA004580","VZSSA004604","VZSSA004616","VZSSA004621","VZSSA004650","VZSSA004662","VZSSA004674","VZSSA004686","VZSSA004691","VZSSA004703","VZSSA004715","VZSSA004720","VZSSA004732","VZSSA004744","VZSSA004756","VZSSA004761","VZSSA004773","VZSSA004785","VZSSA004790","VZSSA004802","VZSSA004814","VZSSA004826","VZSSA004831","VZSSA004843","VZSSA004855","VZSSA004860","VZSSA004872","VZSSA004884","VZSSA004896","VZSSA004901","VZSSA004913","VZSSA004925","VZSSA004930","VZSSA004942","VZSSA004954","VZSSA004966","VZSSA004971","VZSSA004995","VZSSA005000","VZSSA005012","VZSSA005024","VZSSA005036","VZSSA005053","VZSSA005065","VZSSA005070","VZSSA005082","VZSSA005094","VZSSA005106","VZSSA005111","VZSSA005123","VZSSA005135","VZSSA005140","VZSSA005152","VZSSA005164","VZSSA005176","VZSSA005181","VZSSA005193","VZSSA005205","VZSSA005210","VZSSA005234","VZSSA005246","VZSSA005251","VZSSA005263","VZSSA005275","VZSSA005280","VZSSA005292","VZSSA005304","VZSSA005316","VZSSA005321","VZSSA005333","VZSSA005345","VZSSA005350","VZSSA005362","VZSSA005374","VZSSA005386","VZSSA005391","VZSSA005403","VZSSA005415","VZSSA005420","VZSSA005432","VZSSA005444","VZSSA005456","VZSSA005461","VZSSA005485","VZSSA005490","VZSSA005502","VZSSA005514","VZSSA005526","VZSSA005531","VZSSA005543","VZSSA005555","VZSSA005560","VZSSA005572","VZSSA005584","VZSSA005596","VZSSA005601","VZSSA005613","VZSSA005625","VZSSA005630","VZSSA005642","VZSSA005654","VZSSA005671","VZSSA005683","VZSSA005695","VZSSA005700","VZSSA005712","VZSSA005724","VZSSA005736","VZSSA005741","VZSSA005753","VZSSA005765","VZSSA005770","VZSSA005782","VZSSA005794","VZSSA005811","VZSSA005823","VZSSA005835","VZSSA005852","VZSSA005864","VZSSA005876","VZSSA005881","VZSSA005893","VZSSA005905","VZSSA005922","VZSSA005934","VZSSA005946","VZSSA005951","VZSSA005963","VZSSA005975","VZSSA005980","VZSSA005992","VZSSA006004","VZSSA006016","VZSSA006021","VZSSA006033","VZSSA006045","VZSSA006050","VZSSA006062","VZSSA006086","VZSSA006091","VZSSA006103","VZSSA006115","VZSSA006120","VZSSA006132","VZSSA006156","VZSSA006161","VZSSA006173","VZSSA006190","VZSSA006202","VZSSA006214","VZSSA006226","VZSSA006231","VZSSA006243","VZSSA006272","VZSSA006284","VZSSA006301","VZSSA006313","VZSSA006325","VZSSA006330","VZSSA006342","VZSSA006354","VZSSA006366","VZSSA006371","VZSSA006383","VZSSA006395","VZSSA006400","VZSSA006412","VZSSA006436","VZSSA006441","VZSSA006453","VZSSA006465","VZSSA006470","VZSSA006482","VZSSA006494","VZSSA006506","VZSSA006511","VZSSA006523","VZSSA006535","VZSSA006540","VZSSA006552","VZSSA006564","VZSSA006576","VZSSA006581","VZSSA006593","VZSSA006605","VZSSA006610","VZSSA006622","VZSSA006634","VZSSA006646","VZSSA006651","VZSSA006663","VZSSA006675","VZSSA006692","VZSSA006704","VZSSA006716","VZSSA006721","VZSSA006733","VZSSA006745","VZSSA006750","VZSSA006762","VZSSA006774","VZSSA006786","VZSSA006791","VZSSA006803","VZSSA006815","VZSSA006820","VZSSA006832","VZSSA006844","VZSSA006856","VZSSA006861","VZSSA006873","VZSSA006885","VZSSA006902","VZSSA006914","VZSSA006926","VZSSA006931","VZSSA006943","VZSSA006955","VZSSA006960","VZSSA006972","VZSSA006984","VZSSA006996","VZSSA007001","VZSSA007013","VZSSA007025","VZSSA007030","VZSSA007042","VZSSA007054","VZSSA007066","VZSSA007071","VZSSA007083","VZSSA007095","VZSSA007100","VZSSA007112","VZSSA007124","VZSSA007136","VZSSA007141","VZSSA007153","VZSSA007165","VZSSA007170","VZSSA007182","VZSSA007194","VZSSA007211","VZSSA007223","VZSSA007235","VZSSA007240","VZSSA007252","VZSSA007264","VZSSA007276","VZSSA007281","VZSSA007293","VZSSA007305","VZSSA007310","VZSSA007322","VZSSA007334","VZSSA007346","VZSSA007351","VZSSA007375","VZSSA007392","VZSSA007404","VZSSA007416","VZSSA007421","VZSSA007433","VZSSA007445","VZSSA007450","VZSSA007462","VZSSA007474","VZSSA007486","VZSSA007491","VZSSA007503","VZSSA007515","VZSSA007520","VZSSA007532","VZSSA007544","VZSSA007556","VZSSA007561","VZSSA007573","VZSSA007585","VZSSA007590","VZSSA007602","VZSSA007614","VZSSA007626","VZSSA007631","VZSSA007643","VZSSA007655","VZSSA007660","VZSSA007672","VZSSA007684","VZSSA007696","VZSSA007701","VZSSA007713","VZSSA007725","VZSSA007730","VZSSA007742","VZSSA007754","VZSSA007766","VZSSA007771","VZSSA007783","VZSSA007795","VZSSA007800","VZSSA007812","VZSSA007824","VZSSA007836","VZSSA007841","VZSSA007853","VZSSA007865","VZSSA007870","VZSSA007882","VZSSA007891","VZSSA007903","VZSSA007915","VZSSA014862","VZSSA014874","VZSSA014886","VZSSA014891","VZSSA014904","VZSSA014916","VZSSA014921","VZSSA014933","VZSSA014945","VZSSA014950","VZSSA014962","VZSSA014974","VZSSA014986","VZSSA015003","VZSSA015015","VZSSA015020","VZSSA015032","VZSSA015044","VZSSA015056","VZSSA015061","VZSSA015073","VZSSA015085","VZSSA015090","VZSSA015102","VZSSA015114","VZSSA015126","VZSSA015131","VZSSA015160","VZSSA015172","VZSSA015184","VZSSA015196","VZSSA015201","VZSSA015213","VZSSA015242","VZSSA015254","VZSSA015283","VZSSA015295","VZSSA015300","VZSSA015312","VZSSA015324","VZSSA015336","VZSSA015341","VZSSA015353","VZSSA015365","VZSSA015370","VZSSA015382","VZSSA015394","VZSSA015406","VZSSA015411","VZSSA015423","VZSSA015435","VZSSA015440","VZSSA015452","VZSSA015463","VZSSA015475","VZSSA015480","VZSSA015492","VZSSA015504","VZSSA015516","VZSSA015521","VZSSA015533","VZSSA015545","VZSSA015550","VZSSA015562","VZSSA015574","VZSSA015586","VZSSA015591","VZSSA015603","VZSSA015615","VZSSA015620","VZSSA015632","VZSSA015644","VZSSA015656","VZSSA015661","VZSSA015673","VZSSA015685","VZSSA015690","VZSSA015702","VZSSA015714","VZSSA015726","VZSSA015731","VZSSA015743","VZSSA015755","VZSSA015760","VZSSA015772","VZSSA015784","VZSSA015796","VZSSA015801","VZSSA015813","VZSSA015825","VZSSA015830","VZSSA015842","VZSSA015854","VZSSA015866","VZSSA015871","VZSSA015895","VZSSA015900","VZSSA015912","VZSSA015936","VZSSA015941","VZSSA015953","VZSSA015965","VZSSA015970","VZSSA015982","VZSSA015994","VZSSA016006","VZSSA016011","VZSSA016023","VZSSA016035","VZSSA016040","VZSSA016052","VZSSA016076","VZSSA016081","VZSSA016093","VZSSA016101","VZSSA016113","VZSSA016125","VZSSA016130","VZSSA016142","VZSSA016154","VZSSA016166","VZSSA016171","VZSSA016183","VZSSA016195","VZSSA016200","VZSSA016212","VZSSA016224","VZSSA016236","VZSSA016241","VZSSA016253","VZSSA016265","VZSSA016270","VZSSA016294","VZSSA016306","VZSSA016311","VZSSA016323","VZSSA016335","VZSSA016340","VZSSA016352","VZSSA016364","VZSSA016376","VZSSA016381","VZSSA016393","VZSSA016405","VZSSA016410","VZSSA016422","VZSSA016434","VZSSA016446","VZSSA016451","VZSSA016463","VZSSA016475","VZSSA016480","VZSSA016492","VZSSA016504","VZSSA016516","VZSSA016521","VZSSA016533","VZSSA016545","VZSSA016550","VZSSA016562","VZSSA016574","VZSSA016586","VZSSA016591","VZSSA016603","VZSSA016615","VZSSA016620","VZSSA016632","VZSSA016644","VZSSA016656","VZSSA016661","VZSSA016673","VZSSA016685","VZSSA016690","VZSSA016702","VZSSA016714","VZSSA016726","VZSSA016731","VZSSA016743","VZSSA016755","VZSSA016760","VZSSA016772","VZSSA016784","VZSSA016796","VZSSA016801","VZSSA016813","VZSSA016825","VZSSA016830","VZSSA016842","VZSSA016854","VZSSA016866","VZSSA016871","VZSSA016883","VZSSA016895","VZSSA016900","VZSSA016912","VZSSA016924","VZSSA016936","VZSSA016941","VZSSA016953","VZSSA016965","VZSSA016970","VZSSA016982","VZSSA016994","VZSSA017006","VZSSA017011","VZSSA017023","VZSSA017035","VZSSA017040","VZSSA017052","VZSSA017064","VZSSA017076","VZSSA017081","VZSSA017093","VZSSA017105","VZSSA017110");
} //fin de if($IdEstado == "30")

//Condicion de estado-clues
if($IdEstado == "31"){
	$Clues = array("YNSSA000022","YNSSA000034","YNSSA000046","YNSSA000051","YNSSA000063","YNSSA000075","YNSSA000092","YNSSA000104","YNSSA000116","YNSSA000121","YNSSA000133","YNSSA000145","YNSSA000150","YNSSA000162","YNSSA000174","YNSSA000186","YNSSA000203","YNSSA000215","YNSSA000220","YNSSA000232","YNSSA000244","YNSSA000256","YNSSA000273","YNSSA000285","YNSSA000290","YNSSA000314","YNSSA000326","YNSSA000331","YNSSA000343","YNSSA000355","YNSSA000360","YNSSA000372","YNSSA000384","YNSSA000396","YNSSA000401","YNSSA000413","YNSSA000425","YNSSA000442","YNSSA000454","YNSSA000466","YNSSA000471","YNSSA000483","YNSSA000524","YNSSA000541","YNSSA000553","YNSSA000565","YNSSA000570","YNSSA000582","YNSSA000606","YNSSA000611","YNSSA000623","YNSSA000635","YNSSA000640","YNSSA000664","YNSSA000676","YNSSA000681","YNSSA000693","YNSSA000705","YNSSA000710","YNSSA000734","YNSSA000746","YNSSA000751","YNSSA000763","YNSSA000780","YNSSA000792","YNSSA000804","YNSSA000821","YNSSA000833","YNSSA000845","YNSSA000850","YNSSA000862","YNSSA000886","YNSSA000891","YNSSA000903","YNSSA000915","YNSSA000920","YNSSA000932","YNSSA000944","YNSSA000956","YNSSA000961","YNSSA000973","YNSSA000985","YNSSA000990","YNSSA001002","YNSSA001014","YNSSA001026","YNSSA001031","YNSSA001043","YNSSA001055","YNSSA001060","YNSSA001072","YNSSA001084","YNSSA001096","YNSSA001101","YNSSA001113","YNSSA001125","YNSSA001130","YNSSA001142","YNSSA001154","YNSSA001166","YNSSA001171","YNSSA001183","YNSSA001195","YNSSA001200","YNSSA001212","YNSSA001224","YNSSA001236","YNSSA001241","YNSSA001253","YNSSA001265","YNSSA001270","YNSSA001282","YNSSA001294","YNSSA001306","YNSSA001311","YNSSA001323","YNSSA001335","YNSSA001340","YNSSA001352","YNSSA001376","YNSSA001393","YNSSA001405","YNSSA001422","YNSSA001446","YNSSA001451","YNSSA001463","YNSSA001475","YNSSA001480","YNSSA001492","YNSSA001504","YNSSA001516","YNSSA001521","YNSSA001533","YNSSA001545","YNSSA001550","YNSSA001562","YNSSA001574","YNSSA001586","YNSSA001591","YNSSA001603","YNSSA001615","YNSSA001620","YNSSA001632","YNSSA001644","YNSSA001656","YNSSA001661","YNSSA001702","YNSSA001714","YNSSA001726","YNSSA001731","YNSSA001743","YNSSA013423","YNSSA013435","YNSSA013440","YNSSA013452","YNSSA013464","YNSSA013476","YNSSA013481","YNSSA013510","YNSSA013522","YNSSA013534","YNSSA013546","YNSSA013551","YNSSA013563","YNSSA013575","YNSSA013580","YNSSA013604","YNSSA013616","YNSSA013621","YNSSA013633","YNSSA013645","YNSSA013650","YNSSA013662","YNSSA013674","YNSSA013684","YNSSA013696","YNSSA013701","YNSSA013713","YNSSA013725","YNSSA013730","YNSSA013742","YNSSA013766","YNSSA013771","YNSSA013783","YNSSA013795","YNSSA013800","YNSSA013812","YNSSA013824","YNSSA013836","YNSSA013841","YNSSA013853","YNSSA013865","YNSSA013870","YNSSA013882","YNSSA013894","YNSSA013906","YNSSA013911","YNSSA013923","YNSSA013935","YNSSA013981","YNSSA013993","YNSSA014005","YNSSA014010","YNSSA014022","YNSSA014034","YNSSA014046","YNSSA014051","YNSSA014063","YNSSA014075","YNSSA014080","YNSSA014092","YNSSA014104","YNSSA014116","YNSSA014121","YNSSA014133","YNSSA014145","YNSSA014150","YNSSA014162");
} //fin de if($IdEstado == "31")
	
	
	$LocCampo = $Campo;
	if (strlen($LocCampo) == 11){
		if(!in_array($LocCampo,$Clues)){  
			$Error = $NumReg ."|".$DI_68."|".$LocCampo."|" . $DI_68_Catalogo."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_68."|".$LocCampo."|" . $DI_68_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_69


/*************************************************************
* 
*  Funcion : fncValidaDI_70
*  Objetivo: Validar el campo Porcentaje de Pensión 01 
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 2-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_70($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_70           = "(70)Porcentaje de Pensión 01 ";
	$DI_70_ErrTam    = "Porcentaje de Pensión 01   ser de 3 enteros y 2 decimales(###.##)";
	$DI_70_DC  = "Porcentaje de Pensión 01  No coincide con la Directiva de Calidad definida por la DGRH(###.##)";
	
	
	$LocCampo = $Campo;
	if (strlen($LocCampo) <= SEIS){
		if(!preg_match("/[0-9]{3}.[0-9]{2}/",$LocCampo)){
			$Error = $NumReg ."|".$DI_70."|".$LocCampo."|" . $DI_70_DC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_70."|".$LocCampo."|" . $DI_70_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_70

/*************************************************************
* 
*  Funcion : fncValidaDI_71
*  Objetivo: Validar el campo Porcentaje de Pensión 01 
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 2-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_71($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_71           = "(71)Porcentaje de Pensión 02 ";
	$DI_71_ErrTam    = "Porcentaje de Pensión 02   ser de 3 enteros y 2 decimales(###.##)";
	$DI_71_DC  = "Porcentaje de Pensión 02  No coincide con la Directiva de Calidad definida por la DGRH(###.##)";
	
	$LocCampo = $Campo;
	if (strlen($LocCampo) <= SEIS){
		if(!preg_match("/[0-9]{3}.[0-9]{2}/",$LocCampo)){
			$Error = $NumReg ."|".$DI_71."|".$LocCampo."|" . $DI_71_DC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_71."|".$LocCampo."|" . $DI_71_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_71

/*************************************************************
* 
*  Funcion : fncValidaDI_72
*  Objetivo: Validar el campo Porcentaje de Pensión 03
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 2-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_72($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_72           = "(72)Porcentaje de Pensión 03";
	$DI_72_ErrTam    = "Porcentaje de Pensión 03 ser de 3 enteros y 2 decimales(###.##)";
	$DI_72_DC  = "Porcentaje de Pensión 03 No coincide con la Directiva de Calidad definida por la DGRH(###.##)";
	
	$LocCampo = $Campo;
	if (strlen($LocCampo) <= SEIS){
		if(!preg_match("/[0-9]{3}.[0-9]{2}/",$LocCampo)){
			$Error = $NumReg ."|".$DI_72."|".$LocCampo."|" . $DI_72_DC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_72."|".$LocCampo."|" . $DI_72_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_72


/*************************************************************
* 
*  Funcion : fncValidaDI_73
*  Objetivo: Validar el campo Porcentaje de Pensión 04
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 2-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_73($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_73           = "(73)Porcentaje de Pensión 04";
	$DI_73_ErrTam    = "Porcentaje de Pensión 04 ser de 3 enteros y 2 decimales(###.##)";
	$DI_73_DC  = "Porcentaje de Pensión 04 No coincide con la Directiva de Calidad definida por la DGRH(###.##)";
	
	$LocCampo = $Campo;
	if (strlen($LocCampo) <= SEIS){
		if(!preg_match("/[0-9]{3}.[0-9]{2}/",$LocCampo)){
			$Error = $NumReg ."|".$DI_73."|".$LocCampo."|" . $DI_73_DC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_73."|".$LocCampo."|" . $DI_73_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_73


/*************************************************************
* 
*  Funcion : fncValidaDI_74
*  Objetivo: Validar el campo Porcentaje de Pensión 05
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 2-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_74($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_74           = "(74)Porcentaje de Pensión 05";
	$DI_74_ErrTam    = "Porcentaje de Pensión 04 ser de 3 enteros y 2 decimales(###.##)";
	$DI_74_DC  = "Porcentaje de Pensión 04 No coincide con la Directiva de Calidad definida por la DGRH(###.##)";
	
	$LocCampo = $Campo;
	if (strlen($LocCampo) <= SEIS){
		if(!preg_match("/[0-9]{3}.[0-9]{2}/",$LocCampo)){
			$Error = $NumReg ."|".$DI_74."|".$LocCampo."|" . $DI_74_DC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_74."|".$LocCampo."|" . $DI_74_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_74


/*************************************************************
* 
*  Funcion : fncValidaDI_75
*  Objetivo: Validar el campo Elección de tipo de retiro del ISSSTE
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 2-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_75($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_75           = "(75)Elección de tipo de retiro del ISSSTE";
	$DI_75_ErrTam    = "Elección de tipo de retiro del ISSSTE 1 enteros [0,1,2]";
	$DI_75_DC  = "Elección de tipo de retiro con la Directiva de Calidad definida por la DGRH[0 (sin descripción), 1 (decimo transitorio), 2 (cuenta individual)]";
	
	$LocCampo = $Campo;
	if (strlen($LocCampo) == UNO){
		if(!preg_match("/[0-2]{1}/",$LocCampo)){
			$Error = $NumReg ."|".$DI_75."|".$LocCampo."|" . $DI_75_DC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_75."|".$LocCampo."|" . $DI_75_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_75


/*************************************************************
* 
*  Funcion : fncValidaDI_76
*  Objetivo: Validar el campo Tipo de Unidad
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 2-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_76($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_76           = "(76)Tipo de Unidad";
	$DI_76_ErrTam    = "Tipo de Unidad 1 enteros [1,2]";
	$DI_76_DC  = "Tipo de Unidad con la Directiva de Calidad definida por la DGRH[1-2]";
	
	$LocCampo = $Campo;
	if (strlen($LocCampo) == UNO){
		if(!preg_match("/[1-2]{1}/",$LocCampo)){
			$Error = $NumReg ."|".$DI_76."|".$LocCampo."|" . $DI_76_DC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_76."|".$LocCampo."|" . $DI_76_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_76


/*************************************************************
* 
*  Funcion : fncValidaDI_77
*  Objetivo: Validar el campo Descripción de Centro de Responsabilidad
*            de acuerdo a las reglas de negocio establecidas
*  Fecha   : 2-Jun-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   GestorErr : Es controlador del archivo que controla los errores
*   NumReg    : Numero de registro que se analiza
*   Campo     : Contenido del Campo a analizar
*
***************************************************************/   

function fncValidaDI_77($IdEstado, $GestorErr, $NumReg, $Campo){
	 
	$Bandera = CERO;
	$DI_77           = "(77)Descripción de Centro de Responsabilidad";
	$DI_77_ErrTam    = "Descripción de Centro de Responsabilidad no cumple con el tamaño de 150 caracteres";
	$DI_77_DC  = "Descripción de Centro de Responsabilidad de Calidad definida por la DGRH";
	
	$LocCampo = $Campo;
	if (strlen($LocCampo) <= 150){
		if(!preg_match("/[0-9,A-Z,a-z,' ']/",$LocCampo)){
			$Error = $NumReg ."|".$DI_77."|".$LocCampo."|" . $DI_77_DC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DI_77."|".$LocCampo."|" . $DI_77_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDI_77


?>
