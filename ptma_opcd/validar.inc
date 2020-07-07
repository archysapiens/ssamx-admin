<?php


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

function fncValidaArchivoV2($IdEstado, $Path,$Archivo)
{
	$TotalRegErr      = CERO;
 	$ContadorRegistros=UNO;
 	
 	$ContadorErrorDI = InicializaArray(70);

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
		        $Lon = strlen($Registro);

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

				$RegistroTmp = substr($Registro, CERO ,($Lon-DOS) );
				$Registro=$RegistroTmp;
/**
		        $ValidaError = fncValidaDIV2_1($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NumEmpl,$Registro);
		        if($ValidaError!=0){
					$ContadorErrorDI[UNO]++;		        	
				}
**/

/**
se uso para prueba de validacion

				$ValidaError = fncValidaDIV2_25($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $Edo,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + CINCO]++;
				}
				$ValidaError = fncValidaDIV2_26($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $Mpio,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + SEIS]++;
				}
				$ValidaError = fncValidaDIV2_27($IdEstado, $GestorArchivoErr, 
					$ContadorRegistros, $CenRes,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + SIETE]++;
				}


**/





				$ValidaError = fncValidaDIV2_2($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NumFili, $NombreEmpleado,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DOS]++;
				}
				//break;
				$ValidaError = fncValidaDIV2_3($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $CURP, $NombreEmpleado,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[TRES]++;		        	
				}


				$ValidaError = fncValidaDIV2_4($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NombreEmpleado,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[CUATRO]++;
				}

				$ValidaError = fncValidaDIV2_7($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $BancoNvo,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[SIETE]++;
				}

				$ValidaError = fncValidaDIV2_8($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NumCta,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[OCHO]++;        	
				}

				$ValidaError = fncValidaDIV2_9($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $CLABE,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[NUEVE]++;
				}

				$ValidaError = fncValidaDIV2_10($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $CveSPC,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ]++;
				}

				$ValidaError = fncValidaDIV2_15($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $UR,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + CINCO]++;
				}

				$ValidaError = fncValidaDIV2_16($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $GF,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + SEIS]++;
				}

				$ValidaError = fncValidaDIV2_17($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $Fun,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + SIETE]++;
				}

				$ValidaError = fncValidaDIV2_18($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $SFun,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + OCHO]++;
				}

				$ValidaError = fncValidaDIV2_19($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $PG,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + NUEVE]++;
				}

				$ValidaError = fncValidaDIV2_20($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $AI,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ]++;
				}

				$ValidaError = fncValidaDIV2_21($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $PP,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + UNO]++;
				}

				$ValidaError = fncValidaDIV2_22($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $Ptda,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DOS]++;
				}
				$ValidaError = fncValidaDIV2_23($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $Pto,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + TRES]++;
				}

				$ValidaError = fncValidaDIV2_24($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NumPto,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + CUATRO]++;
				}

				$ValidaError = fncValidaDIV2_25($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $Edo,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + CINCO]++;
				}

				$ValidaError = fncValidaDIV2_26($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $Mpio,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + SEIS]++;
				}

				$ValidaError = fncValidaDIV2_27($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $CenRes,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + SIETE]++;
				}

				$ValidaError = fncValidaDIV2_28($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NSS,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + OCHO]++;
				}

				$ValidaError = fncValidaDIV2_29($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $Pagdria,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + NUEVE]++;
				}

				$ValidaError = fncValidaDIV2_30($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $FteFin,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ]++;
				}

				$ValidaError = fncValidaDIV2_31($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $TabPto,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + UNO]++;
				}

				$ValidaError = fncValidaDIV2_32($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NIVEL,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + DOS]++;
				}
				$ValidaError = fncValidaDIV2_33($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $Rango,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + TRES]++;
				}

				$ValidaError = fncValidaDIV2_34($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $IndMando,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + CUATRO]++;
				}
				$ValidaError = fncValidaDIV2_35($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $Horario,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + CINCO]++;
				}

				// campo 36 queda libre

				$ValidaError = fncValidaDIV2_37($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $TipTra,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + SIETE]++;
				}

				$ValidaError = fncValidaDIV2_38($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NivSPC,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + OCHO]++;
				}

				$ValidaError = fncValidaDIV2_39($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $IndStat,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + NUEVE]++;
				}

				$ValidaError = fncValidaDIV2_40($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $FecIng,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + DIEZ]++;
				}


				$ValidaError = fncValidaDIV2_41($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $FecIngSS, $FecIng,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + DIEZ + UNO]++;
				}

				$ValidaError = fncValidaDIV2_42($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $FecReIng,$FecIngSS,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + DIEZ+ DOS]++;
				}

				$ValidaError = fncValidaDIV2_44($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $FecPag,$Registro);	
		        if($ValidaError!=0){
					$ContadorErrorDI[DIEZ + DIEZ + DIEZ + DIEZ+ CUATRO]++;
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




/*************************************************************
* 
*  Funcion : fncValidaDIV2_1
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

function fncValidaDIV2_1($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = 0;

	$DI_1           = "Numero Empleado";
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
			$Error = $NumReg ."|".$DI_1."|".$LocCampo."|" . $DI_1_ErrIdEdo." ($IdEstado)|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}
		if(!preg_match ("/\d{8}/" ,substr($LocCampo,2,8)))
		{
			$Error = $NumReg ."|".$DI_1."|".$LocCampo."|" . $DI_1_ErrIdEmpl."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
	/**
		$Error = $NumReg ."|".$DI_1."|".$Campo."|" . $DI_1_ErrTam."|" .strlen(preg_replace('/[^A-Za-z0-9\-]/', '', $Campo,$Registro))."|$Registro|\n";
    **/
		$Error = $NumReg ."|".$DI_1."|".$Campo."|" . $DI_1_ErrTam."|$Registro|\n";
		
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDIV2_1



/*************************************************************
* 
*  Funcion : fncValidaDIV2_2
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

function fncValidaDIV2_2($IdEstado, $GestorErr, $NumReg, $Campo,$CampoAux,$Registro)
{
	 
	$Bandera = 0;

	$DI_2           = "Filiación";
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
			$Error = $NumReg ."|".$DI_2."|".$LocCampo."|" . $DI_2_ErrRFC."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
		$CampoAux = substr($LocCampo,4,6);
		if(!preg_match ("/\d{6}/" ,$CampoAux))
		{
			$Error = $NumReg ."|".$DI_2."|".$LocCampo."|" . $DI_2_ErrFecNac ."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	

		if(strlen(substr($LocCampo,10,3)) != TRES)
		{
			$Error = $NumReg ."|".$DI_2."|".$LocCampo."|" . $DI_2_ErrHomoCve ."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	

	}
	else
	{
		$Error = $NumReg ."|".$DI_2."|".$Campo."|" . $DI_2_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDIV2_2


/*************************************************************
* 
*  Funcion : fncValidaDIV2_3
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

function fncValidaDIV2_3($IdEstado, $GestorErr, $NumReg, $Campo,$CampoAux,$Registro)
{
	 
	$Bandera = 0;
	$CatEdo = array("AS" , "BC","BS", "CC", "CL", "CM","CS", "CH", "DF", 
				"DG", "GT", "GR", "HG", "JC", "MC","MN", "MS", "NT", "NL", "OC",
				"PL", "QT", "QR", "SP","SL", "SR", "TC", "TS", "TL","VZ", "YN", "ZS", "NE");

	$DI_3           = "Clave Única de Registro de Población (CURP)";
	$DI_3_ErrTam    = "Tamaño de registro debe ser 18 Caracteres";
	$DI_3_ErrIdEdo  = "Identificador de estado Invalido";
	$DI_3_ErrRFC 	= "CURP Incorrecto en Sección I AAAA";
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
			$Error = $NumReg ."|".$DI_3."|".$LocCampo."|" . $DI_3_ErrRFC."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
		$CampoAux = substr($LocCampo,4,6);
		if(!preg_match ("/\d{6}/" ,$CampoAux))
		{
			$Error = $NumReg ."|".$DI_3."|".$LocCampo."|" . $DI_3_ErrFecNac ."|$Registro\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	

		if(!preg_match ("/[M|H|m|h]{1}/" ,substr($LocCampo,10,1)))
		{
			$Error = $NumReg ."|".$DI_3."|".$LocCampo."|" . $DI_3_ErrGenero ."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
		if(!in_array(substr($LocCampo,11,2), $CatEdo))
		{
			$Error = $NumReg ."|".$DI_3."|".$LocCampo."|" . $DI_3_ErrEntFecNac ."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_3."|".$LocCampo."|" . $DI_3_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDIV2_3


/*************************************************************
* 
*  Funcion : fncValidaDIV2_4
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

function fncValidaDIV2_4($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = 0;

	$DI_4           = "Nombre del Empleado";
	$DI_4_ErrTam    = "Tamaño de registro debe ser 150 Caracteres";
	$DI_4_ErrIdEdo  = "Identificador de estado Invalido";
	$DI_4_ErrEstructura = "EL campo no cumple con estructura definida PATERNO,MATERNO/NOMBRE(S)";

    /** Quita caracteres especiales **/
	//$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo,$Registro);
	$LocCampo =$Campo;
	if (strlen($LocCampo) <= 150)
	{
		if(!preg_match ("/[?,A-Z,a-z,\s]{1,90},[?,A-Z,a-z,\s]{1,90}\/[?.A-Z,a-z,\s]{1,90}/" ,$LocCampo))
		{
			$Error = $NumReg ."|".$DI_4."|".$LocCampo."|" . $DI_4_ErrEstructura."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_4."|".$LocCampo."|" . $DI_4_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDIV2_4


/***
Las directivas 5 y 6 estan en definición.

***/



/*************************************************************
* 
*  Funcion : fncValidaDIV2_7
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

function fncValidaDIV2_7($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = 0;

	$DI_7           = "Banco Nuevo";
	$DI_7_ErrTam    = "Tamaño de registro debe ser 5 dígitos";
	$DI_7_TESOFE  = "Identificador no pertenece al Catalogo de TESOFE";

//	$TESOFE = explode("\n", file_get_contents('catalogo_tesofe.txt'));
	$TESOFE = array("2001","37006","37009","37019","37135","37166","37168","40002","40012",
"40014","40021","40022","40030","40032","40036","40037","40042","40044","40058","40059","40060",
"40062","40072","40102","40103","40106","40108","40110","40112","40113","40116","40124","40126",
"40127","40128","40129","40130","40131","40132","40133","40134","40136","40137","40138","40139",
"40140","40143","90600");

    /** Quita caracteres especiales **/
	//$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo,$Registro);
	$LocCampo =$Campo;
	if (strlen($LocCampo) == 5)
	{
		if(!in_array($LocCampo,$TESOFE))
		{
			$Error = $NumReg ."|".$DI_7."|".$LocCampo."|" . $DI_7_TESOFE."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_7."|".$LocCampo."|" . $DI_7_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDIV2_7

/*************************************************************
* 
*  Funcion : fncValidaDIV2_8
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

function fncValidaDIV2_8($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = 0;

	$DI_8           = "Numero de Cuenta";
	$DI_8_ErrTam    = "Tamaño de Numero de Cuenta debe ser 16 dígitos";
	$DI_8_NumCta    = "No cumple con Directiva debe ser 16 digitos";

    /** Quita caracteres especiales **/
	//$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo,$Registro);
	$LocCampo =$Campo;
	if (strlen($LocCampo) == 16)
	{
		if(!preg_match ("/\d{16}/" ,$LocCampo))
		{
			$Error = $NumReg ."|".$DI_8."|".$LocCampo."|" . $DI_8_NumCta."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_8."|".$LocCampo."|" . $DI_8_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDIV2_8



/*************************************************************
* 
*  Funcion : fncValidaDIV2_9
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

function fncValidaDIV2_9($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = 0;

	$DI_9           = "Clave del Banco (CLABE)";
	$DI_9_ErrTam    = "Tamaño de Clave del Banco (CLABE) debe ser 18 dígitos";
	$DI_9_NumCta    = "No cumple con Directiva debe ser 18 digitos";

	

    /** Quita caracteres especiales **/
	//$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo,$Registro);
	$LocCampo =$Campo;
	if (strlen($LocCampo) == 18)
	{
		if(!preg_match ("/\d{18}/" ,$LocCampo))
		{
			$Error = $NumReg ."|".$DI_8."|".$LocCampo."|" . $DI_8_NumCta."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_9."|".$LocCampo."|" . $DI_9_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDIV2_9



/*************************************************************
* 
*  Funcion : fncValidaDIV2_10
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

function fncValidaDIV2_10($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_10           = "Clave del Servicio Profesional de Carrera (FUNCION)";
	$DI_10_ErrTam    = "Tamaño de Clave del Servicio Profesional de Carrera (FUNCION) debe ser 2 dígitos";
	$DI_10_CveInda   = "La cleve debe ser de 2 digitos";

	

    /** Quita caracteres especiales **/
	//$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo,$Registro);
	$LocCampo =$Campo;
	if (strlen($LocCampo) == DOS)
	{
		if(!preg_match ("/\d{2}/" ,$LocCampo))
		{
			$Error = $NumReg ."|".$DI_10."|".$LocCampo."|" . $DI_10_CveInda."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_10."|".$LocCampo."|" . $DI_10_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDIV2_10

/*************************************************************
* 
*  Funcion : fncValidaDIV2_15 
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

function fncValidaDIV2_15($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_15           = "Unidad Responsable";
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
	//$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo,$Registro);

	$LocCampo =$Campo;
	if (strlen($LocCampo) == TRES)
	{
		if(!in_array($LocCampo,$UR))
		{
			$Error = $NumReg ."|".$DI_15."|".$LocCampo."|" . $DI_15_UR."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_15."|".$LocCampo."|" . $DI_15_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDIV2_15


/*************************************************************
* 
*  Funcion : fncValidaDIV2_16 
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

function fncValidaDIV2_16($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_16           = "Grupo Funcional";
	$DI_16_ErrTam    = "Tamaño de Grupo Funcional debe ser dígito a 1 posicion";
	$DI_16_GF   = "El grupo Funcional no es parte del catalogo de DGRH";

	

    /** Quita caracteres especiales **/
	//$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo,$Registro);

	$LocCampo =$Campo;
	if (strlen($LocCampo) == UNO)
	{
		if(!preg_match ("/[1-4]{1}/" ,$LocCampo))
		{
			$Error = $NumReg ."|".$DI_16."|".$LocCampo."|" . $DI_16_GF."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_16."|".$LocCampo."|" . $DI_16_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDIV2_16

/*************************************************************
* 
*  Funcion : fncValidaDIV2_17 
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

function fncValidaDIV2_17($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_17           = "Función";
	$DI_17_ErrTam    = "Tamaño de Función debe ser dígito a 1 posicion";
	$DI_17_F   = "La UR no es parte del catalogo de DGRH";

	

    /** Quita caracteres especiales **/
	//$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo,$Registro);

	$LocCampo =$Campo;
	if (strlen($LocCampo) == UNO)
	{
		if(!preg_match ("/[1-4]{1}/" ,$LocCampo))
		{
			$Error = $NumReg ."|".$DI_17."|".$LocCampo."|" . $DI_17_F."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_17."|".$LocCampo."|" . $DI_17_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDIV2_17

/*************************************************************
* 
*  Funcion : fncValidaDIV2_18 
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

function fncValidaDIV2_18($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_18           = "SubFuncion";
	$DI_18_ErrTam    = "Tamaño de SubFunción debe ser dígito a 2 posicion";
	$DI_18_SF   	 = "La SubFuncion no es parte del catalogo de DGRH";

	

    /** Quita caracteres especiales **/
	//$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo,$Registro);
    $SF= array("01","02","03","04","10","15","05");
	$LocCampo =$Campo;
	if (strlen($LocCampo) == DOS)
	{
		if(!in_array($LocCampo,$SF))
		{
			$Error = $NumReg ."|".$DI_18."|".$LocCampo."|" . $DI_18_SF."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_18."|".$LocCampo."|" . $DI_18_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
} // fin de funcion fncValidaDIV2_18


/*************************************************************
* 
*  Funcion : fncValidaDIV2_19 
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

function fncValidaDIV2_19($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_19           = "Programa General";
	$DI_19_ErrTam    = "Tamaño de Programa General debe ser dígito a 2 posicion";
	$DI_19_PG   	 = "La Programa General no es parte del catalogo de DGRH";

	

    /** Quita caracteres especiales **/
	//$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo,$Registro);
    $PG= array("04","09","15");

	$LocCampo =$Campo;
	if (strlen($LocCampo) == DOS)
	{
		if(!in_array($LocCampo,$PG))
		{
			$Error = $NumReg ."|".$DI_19."|".$LocCampo."|" . $DI_19_PG."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_19."|".$LocCampo."|" . $DI_19_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
} // fin de funcion fncValidaDIV2_19

/*************************************************************
* 
*  Funcion : fncValidaDIV2_20 
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

function fncValidaDIV2_20($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_20           = "Actividad Institucional";
	$DI_20_ErrTam    = "Tamaño de Actividad Institucional debe ser dígito a 3 posicion";
	$DI_20_AI   	 = "La Actividad Institucional no es parte del catalogo de DGRH";
	
    $AI= array("002","004","015","019");

	$LocCampo =$Campo;
	if (strlen($LocCampo) == TRES)
	{
		if(!in_array($LocCampo,$AI))
		{
			$Error = $NumReg ."|".$DI_20."|".$LocCampo."|" . $DI_20_AI."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_20."|".$LocCampo."|" . $DI_20_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
} // fin de funcion fncValidaDIV2_20

/*************************************************************
* 
*  Funcion : fncValidaDIV2_21 
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

function fncValidaDIV2_21($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_21           = "Proyecto Proceso";
	$DI_21_ErrTam    = "Tamaño de Actividad Institucional debe ser  a 4 Alfanumerico";
	$DI_21_PP   	 = "La Proyecto Proceso no es parte del catalogo de DGRH";
	
    $PP= array("1301", "E010","E025","I002");

	$LocCampo =$Campo;
	if (strlen($LocCampo) == CUATRO)
	{
		if(!in_array($LocCampo,$PP))
		{
			$Error = $NumReg ."|".$DI_21."|".$LocCampo."|" . $DI_21_PP."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_21."|".$LocCampo."|" . $DI_21_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
} // fin de funcion fncValidaDIV2_21

/*************************************************************
* 
*  Funcion : fncValidaDIV2_22 
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

function fncValidaDIV2_22($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_22           = "Partida";
	$DI_22_ErrTam    = "Tamaño de Actividad Institucional debe ser  a 5 Alfanumerico";
	$DI_22_Ptda   	 = "La Partida no es parte del catalogo de DGRH";
	
    $Ptda= array("44106","12301","11301","12101","12201");

	$LocCampo =$Campo;
	if (strlen($LocCampo) == CINCO)
	{
		if(!in_array($LocCampo,$Ptda))
		{
			$Error = $NumReg ."|".$DI_22."|".$LocCampo."|" . $DI_22_Ptda."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_22."|".$LocCampo."|" . $DI_22_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDIV2_22


/*************************************************************
* 
*  Funcion : fncValidaDIV2_23 
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

function fncValidaDIV2_23($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_23           = "Puesto";
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
	$LocCampo =trim($Campo);

	if(!in_array($LocCampo,$Pto))
	{
		$Error = $NumReg ."|".$DI_23."|".$LocCampo."|" . $DI_23_Pto."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}	

/**

	if (strlen($LocCampo) == SIETE)
	{
		if(!in_array($LocCampo,$Pto))
		{
			$Error = $NumReg ."|".$DI_23."|".$LocCampo."|" . $DI_23_Pto."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_23."|".$LocCampo."|" . $DI_23_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
**/	
	return $Bandera;
} // fin de funcion fncValidaDIV2_23

/*************************************************************
* 
*  Funcion : fncValidaDIV2_24 
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

function fncValidaDIV2_24($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_24           = "Número de Puesto";
	$DI_24_ErrTam    = "Tamaño de Número de Puesto debe ser  a 4 Alfanumerico";
	$DI_24_NumPto   	 = "El Número Puesto no es parte del catalogo de DGRH";
	
    $NumPto= array("0022","0101");

	$LocCampo =$Campo;
	if (strlen($LocCampo) == CUATRO)
	{
		if(!in_array($LocCampo,$NumPto)) {
			$Error = $NumReg ."|".$DI_24."|".$LocCampo."|" . $DI_24_NumPto."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_24."|".$LocCampo."|" . $DI_24_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDIV2_24

/*************************************************************
* 
*  Funcion : fncValidaDIV2_25 
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

function fncValidaDIV2_25($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_25           = "Estado";
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
			$Error = $NumReg ."|".$DI_25."|".$LocCampo."|" . $DI_25_Edo."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_25."|".$LocCampo."|" . $DI_25_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDIV2_25

/*************************************************************
* 
*  Funcion : fncValidaDIV2_26 
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

function fncValidaDIV2_26($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_26           = "Municipio";
	$DI_26_ErrTam    = "Tamaño de campo Municipio debe ser  a 3 Dígitos";
	$DI_26_Mpio    	 = "El Municipio no es parte del catalogo de DGRH";
	
	// agregar catalogo de Municpios
/**	
    $Mpio= array("001","002","003","004","005","006","007","008","009","010","011",
"012","013","014","015","016","017","018","019","020","021","022","023","024","025",
"026","027","028","029","030","031","032","033","034","035","036","037","038","039",
"040","041","042","043","044","045","046","047","048","049","050","051","052","053",
"054","055","056","057","058","059","060","061","062","063","064","065","066","067",
"068","069","070","071","072","073","074","075","076","077","078","079","080","081",
"082","083","084","085","086","087","088","089","090","091","092","093","094","096",
"097","098","099","100","101","102","103","104","105","106","107","108","109","110",
"111","112","113","114","115","116","117","118","119","328","329","330","331","332",
"333","334","335","336","337","338","339","340","341","342","343","344","345","346",
"347","348","349","350","351","352","353","354","355","356","357","358","359","360",
"361","362","363","364","365","366","367","368","369","370","371");
**/

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
			$Error = $NumReg ."|".$DI_26."|".$LocCampo."|" . $DI_26_Mpio."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_26."|".$LocCampo."|" . $DI_26_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDIV2_26

/*************************************************************
* 
*  Funcion : fncValidaDIV2_27 
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

function fncValidaDIV2_27($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_27           = "Centro de Responsabilidad";
	$DI_27_ErrTam    = "Tamaño de campo Centro de Responsabilidad debe ser  a 10 Caracters";
	$DI_27_Edo    	 = "El Centro de Responsabilidad no corresponde al Estado";
	$DI_27_CR    	 = "El Centro de Responsabilidad no corresponde al catalogo de DGRH";
	
	// agregar catalogo de Municpios
    $Edo= array($IdEstado);

    $Responsabilidad =array("0716000001","0716000002","0716000003","0910000000","0910000001",
"0910000002","0910000003","0910000512","0910010000","0910020000","0910030000","0911100513",
"0911101000","0911102000","0911103000","0911104000","0911105000","0911106000","0911107000",
"0911200000","0911200001","0911200513","0911201000","0911202000","0911300000","0911300001",
"0911300002","0911300513","0911400000","0911400001","0911400513","0913201030","0916000000",
"0916000001","0916000002","0916000003","0916000004","0916000005","0916000006","0916000007",
"0916000008","0916000009","0916000010","0916000011","0916000012","0916000013","0916000014",
"0916000015","0916000016","0916000017","0916000018","0916000019","0916000020","0916000021",
"0916000022","0916000023","0916000024","0916000025","0916000026","0916000027","0916000028",
"0916000029","0916000030","0916000031","0916000032","0916000033","0916000513","0916001513",
"0916002513","0916003513","0916130512","0917000000","0917000001","0917000513","0917010000",
"0917100000","0917100001","0917200000","0917200001","0917201000","0917202000","0917203000",
"0918000000","0918000001","0918000513","0930000000","0930010000","0931000000","0931000001",
"0931000513",
"0931200000",
"0931200513",
"0931201000",
"0931300000",
"0931300001",
"0931400000",
"0931400001",
"0931400513",
"0931500000",
"0931500001",
"0931500513",
"0931600000",
"0931600001",
"0931600002",
"0931600003",
"0950000000",
"0950000001",
"0950000002",
"0950000010",
"0950000513",
"0951000000",
"0951000513",
"0951010000",
"0951020000",
"0951030000",
"0951040000",
"0951050000",
"0951060000",
"0951070000",
"0951080000",
"0951081000",
"0951082000",
"0951100000",
"0951100001",
"0951100513",
"0951200000",
"0951200513",
"0951201000",
"0951201100",
"0951201200",
"0951202000",
"0951203000",
"0951204000",
"0951205000",
"0951206000",
"0951207000",
"0951208000",
"0951209000",
"0951300000",
"0951302000",
"0951303000",
"0951304000",
"0951305000",
"0951306000",
"0951307000",
"0951308000",
"0951308513",
"0951309000",
"0951309001",
"0951309002",
"0951400000",
"0951400001",
"0951401000",
"0951401513",
"0951402000",
"0951403000",
"0951404000",
"0951405000",
"0951406000",
"0951407000",
"0951408000",
"0951409000",
"0960000000",
"0960000001",
"0960000513",
"0961000000",
"0961000001",
"0961000002",
"0961000003",
"0961000004",
"0961000005",
"0961000006",
"0961000513",
"0961001000",
"0961001100",
"0961001200",
"0961001300",
"0961001400",
"0961001500",
"0961001600",
"0961001700",
"0961001800",
"0961001900",
"0961002000",
"0961002100",
"0961002200",
"0961002300",
"0961002400",
"0961002500",
"0961002600",
"0961002700",
"0961002800",
"0961002900",
"0961003000",
"0961003100",
"0961003200",
"0961003300",
"0961003301",
"0961004000",
"0961005000",
"0961006000",
"0961008000",
"0961009000",
"0961030000",
"0961030001",
"0961030002",
"0961030003",
"0961030004",
"0961030005",
"0961030006",
"0961030007",
"0961030008",
"0961030009",
"0961030010",
"0961030011",
"0961030012",
"0961030013",
"0961030014",
"0961030070",
"0961100000",
"0961100001",
"0961100002",
"0961100003",
"0961100004",
"0961100005",
"0961100006",
"0961100007",
"0961100008",
"0961100009",
"0961100010",
"0961100011",
"0961100012",
"0961100013",
"0961100014",
"0961100015",
"0961100016",
"0961100017",
"0961100018",
"0961100019",
"0961100020",
"0961100021",
"0961100022",
"0961100023",
"0961100024",
"0961100025",
"0961100026",
"0961100027",
"0961100028",
"0961100029",
"0961100030",
"0961100031",
"0961100032",
"0961100082",
"0961100083",
"0961100084",
"096110008A",
"096110017A",
"096110030A",
"096110030B",
"096110030C",
"0961100513",
"0961100A01",
"0961100B02",
"0961100B03",
"0961300000",
"0961300001",
"0961300513",
"0961400000",
"0961400001",
"0961400513",
"0961401000",
"0961402000",
"0961501610",
"0998030000",
"09AYK00000",
"09E0000000",
"09E0000001",
"09E0000002",
"09E0000513",
"09I0000000",
"09I0000001",
"09I0000513",
"09I0010000",
"09I0020000",
"09I0030000",
"09K0000000",
"09K0000001",
"09L0000000",
"09L0000001",
"09L0000513",
"09L0010000",
"09L0020000",
"09L0030000",
"09L0040000",
"09L0050000",
"09L0060000",
"09L0070000",
"09M0000000",
"09M0000001",
"09M0000002",
"09M0000512",
"09N0000000",
"09N0000001",
"09N0000513",
"09N0001513",
"09N0002513",
"09N0010000",
"09N0010001",
"09N0010610",
"09N0020000",
"09N0020001",
"09N0020610",
"09N0030000",
"09N0030001",
"09N0030610",
"09N0040000",
"09N0040001",
"09N0050000",
"09N0050001",
"09N0060000",
"09N0060001",
"09NCE00000",
"09O0000000",
"09O0000001",
"09O0000002",
"09O0000003",
"09O0000004",
"09O0000006",
"09O0000007",
"09O0000008",
"09O0000009",
"09O0000100",
"09O0000200",
"09O0000300",
"09O0000400",
"09O0000500",
"09O0000513",
"09O0000600",
"09O0000900",
"09O0010000",
"09O0010513",
"09O0012000",
"09O0013000",
"09O0014000",
"09Q0000000",
"09Q0000001",
"09Q0000002",
"09Q0000513",
"09R0000000",
"09R0000001",
"09R0000513",
"09S0000000",
"09S0000001",
"09S0000002",
"09S0000003",
"09S0000004",
"09S0000005",
"09S0000006",
"09S0000007",
"09S0000008",
"09S0000009",
"09S0000011",
"09S0000513",
"09S0010000",
"09T0000000",
"09T0010000",
"09T0010513",
"09U0000000",
"09U0000001",
"09U0000002",
"09U0000003",
"09U0000004",
"09U0000005",
"09U0000006",
"09U0000007",
"09U0000008",
"09U0000010",
"09U0000011",
"09U0000012",
"09U0000013",
"09U0000014",
"09U0000015",
"09U0000016",
"09U0000017",
"09U0000018",
"09U0000019",
"09U0000020",
"09U0000021",
"09U0000022",
"09U0000023",
"09U0000024",
"09U0000025",
"09U0000026",
"09U0000027",
"09U0000028",
"09U0000029",
"09U0000030",
"09U0000031",
"09U0000032",
"09U0000033",
"09U0000034",
"09U0000035",
"09U0000036",
"09U0000037",
"09U0000038",
"09U0000113",
"09U0000213",
"09U0000313",
"09U0000413",
"09U0000513",
"09U0000613",
"09U0000713",
"09U0000813",
"09U0000913",
"09U0001013",
"09U0001113",
"09U0001213",
"09U0001313",
"09U0001413",
"09U0001513",
"09U0002030",
"09U0003030",
"09U0004030",
"09U0005030",
"09U0006030",
"09U0007001",
"09U0007002",
"09U0007003",
"09U0007004",
"09U0007005",
"09U0007006",
"09U0007007",
"09U0007010",
"09U0007030",
"09U0008030",
"09U0010000",
"09U0010001",
"09U0010002",
"09U0010003",
"09U0010004",
"09U0010030",
"09U0011000",
"09U0011030",
"09U0012000",
"09U0012001",
"09U0012002",
"09U0012003",
"09U0012004",
"09U0012005",
"09U0012006",
"09U0012007",
"09U0013000",
"09U0014000",
"09U0015000",
"09U0015001",
"09U0015002",
"09U0015003",
"09U0015004",
"09U0015005",
"09U0015006",
"09U0015007",
"09U0015008",
"09U0015009",
"09U0015010",
"09U0016001",
"09U0016002",
"09U0016003",
"09U0016004",
"09U0016005",
"09U0016006",
"09U0016007",
"09U0016008",
"09U0020001",
"09U0020002",
"09U0020003",
"09U0020004",
"09U0020005",
"09U0020006",
"09U0023001",
"09U0023002",
"09U0023003",
"09U0023004",
"09U0024001",
"09U0024002",
"09U0024004",
"09U0024005",
"09U0024006",
"09U0026001",
"09U0026002",
"09U0026003",
"09U0026004",
"09U0026005",
"09U0026006",
"09U0026007",
"09U0026008",
"09U0026009",
"09U0026010",
"09U0028001",
"09U0028002",
"09U0028003",
"09U0028004",
"09U0028005",
"09U0028006",
"09U0028007",
"09U0100022",
"09U0200022",
"09U0300022",
"09U0400022",
"09U0500022",
"09U0600022",
"09V0000000",
"09V0000001",
"09V0000513",
"09W0000000",
"09W0000001",
"09W0000513",
"09X0000000",
"09X0000001",
"09X0000002",
"09X0000513",
"1116000001",
"1116000002",
"2016000001",
"2016000002",
"2816000000",
"2816000001",
"3116000001",
"3116000002"
);

	$LocCampo =$Campo;
	if (strlen($LocCampo) == DIEZ)
	{
		if(!in_array($LocCampo,$Responsabilidad))
		{
			$Error = $NumReg ."|".$DI_27."|".$LocCampo."|" . $DI_27_Edo."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
		if(!preg_match("/\d{8}/",substr($LocCampo,2,8)))
		{
			$Error = $NumReg ."|".$DI_27."|".$LocCampo."|" . $DI_27_CR."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_27."|".$LocCampo."|" . $DI_27_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDIV2_27


/*************************************************************
* 
*  Funcion : fncValidaDIV2_28 
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

function fncValidaDIV2_28($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_28           = "Cédula de Identidad (NSS)";
	$DI_28_ErrTam    = "Tamaño de campo Cédula de Identidad (NSS) debe ser  a 11 Caracters";
	$DI_28_NSS    	 = "La Cédula de Identidad (NSS) no corresponde (80)";
	$DI_28_ISSSTE   	 = "La Cédula de Identidad (NSS) no corresponde al asignado pór ISSSTE";
	
	// agregar catalogo de Municpios
	$LocCampo =$Campo;
	if (strlen($LocCampo) == (DIEZ + UNO))
	{
		if(!(substr($LocCampo,0,2) == "80"))
		{
			$Error = $NumReg ."|".$DI_28."|".$LocCampo."|" . $DI_28_NSS."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
		if(!preg_match("/\d{9}/",substr($LocCampo,2,9)))
		{
			$Error = $NumReg ."|".$DI_28."|".$LocCampo."|" . $DI_28_ISSSTE."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_28."|".$LocCampo."|" . $DI_28_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDIV2_28

/*************************************************************
* 
*  Funcion : fncValidaDIV2_29 
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

function fncValidaDIV2_29($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_29           = "Pagaduria";
	$DI_29_ErrTam    = "Tamaño de campo Pagaduria debe ser  a 5 Caracters";
	$DI_29_Pgria   	 = "Pagaduria no corresponde las reglas de negocio establecidas por DGRH";
	
	
	// agregar catalogo de Municpios
	$LocCampo =$Campo;
	if (strlen($LocCampo) == CINCO)
	{
		if(!preg_match("/[A-Za-z0-9]{5}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_29."|".$LocCampo."|" . $DI_29_Pgria."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_29."|".$LocCampo."|" . $DI_29_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDIV2_29

/*************************************************************
* 
*  Funcion : fncValidaDIV2_30 
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

function fncValidaDIV2_30($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_30           = "Número de AHISA-Fuente de Financiamiento";
	$DI_30_ErrTam    = "Tamaño de campo Número de AHISA-Fuente de Financiamiento debe ser de 2 Digítos";
	$DI_30_noDI   	 = "Número de AHISA - Fuente de Financiamiento no corresponde las reglas de negocio establecidas por DGRH";
	

	$LocCampo =$Campo;
	if (strlen($LocCampo) == DOS)
	{
		if(!preg_match("/[0-9]{2}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_30."|".$LocCampo."|" . $DI_30_noDI."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_30."|".$LocCampo."|" . $DI_30_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDIV2_30

/*************************************************************
* 
*  Funcion : fncValidaDIV2_31 
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

function fncValidaDIV2_31($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_31           = "Tabulador de Puesto";
	$DI_31_ErrTam    = "Tamaño de campo Tabulador de Puesto debe ser de 3 Digítos";
	$DI_31_noDI   	 = "Tabulador de Puesto no corresponde las Directivas Institucionales  establecidas por DGRH";
	

	$LocCampo =$Campo;
	if (strlen($LocCampo) == TRES)
	{
		if(!preg_match("/[0-9]{3}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_31."|".$LocCampo."|" . $DI_31_noDI."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_31."|".$LocCampo."|" . $DI_31_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDIV2_31

/*************************************************************
* 
*  Funcion : fncValidaDIV2_32 
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

function fncValidaDIV2_32($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_32           = "Nivel de puesto - NIVEL";
	$DI_32_ErrTam    = "Nivel de puesto - NIVEL debe ser de 2 Digítos";
	$DI_32_noDI   	 = "Nivel de puesto - NIVEL no corresponde las Directivas Institucionales  establecidas por DGRH";
	

	$LocCampo =$Campo;
	if (strlen($LocCampo) == DOS)
	{
		if(!preg_match("/[0-9]{2}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_32."|".$LocCampo."|" . $DI_32_noDI."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_32."|".$LocCampo."|" . $DI_32_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDIV2_32

/*************************************************************
* 
*  Funcion : fncValidaDIV2_33 
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

function fncValidaDIV2_33($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_33           = "Rango";
	$DI_33_ErrTam    = "Rango debe ser de 1 Digítos";
	$DI_33_noDI   	 = "Rango no corresponde las Directivas Institucionales  establecidas por DGRH (1,2,3)";
	

	$LocCampo =$Campo;
	if (strlen($LocCampo) == UNO)
	{
		if(!preg_match("/[0-9]{1}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_33."|".$LocCampo."|" . $DI_33_noDI."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_33."|".$LocCampo."|" . $DI_33_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDIV2_33


/*************************************************************
* 
*  Funcion : fncValidaDIV2_34
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

function fncValidaDIV2_34($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_34           = "Indicador de Mando";
	$DI_34_ErrTam    = "Indicador de Mando debe ser de 2 Digítos";
	$DI_34_noDI   	 = "Indicador de Mando no corresponde al catalogo establecidas por DGRH";
	
	$IndMando = array("01","08","10","30","50","60","70","75","80","90");

	$LocCampo =$Campo;
	if (strlen($LocCampo) == DOS)
	{
		if(!in_array($LocCampo, $IndMando))
		{
			$Error = $NumReg ."|".$DI_34."|".$LocCampo."|" . $DI_34_noDI."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_34."|".$LocCampo."|" . $DI_34_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDIV2_34

/*************************************************************
* 
*  Funcion : fncValidaDIV2_35
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

function fncValidaDIV2_35($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_35           = "Horario Asignado";
	$DI_35_ErrTam    = "Horario Asignado debe ser de 1 Digítos";
	$DI_35_noDI   	 = "Horario Asignado no corresponde al catalogo establecidas por DGRH(1-8)";
	
	

	$LocCampo =$Campo;
	if (strlen($LocCampo) == UNO)
	{
		if(!preg_match("/[1-8]{1}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_35."|".$LocCampo."|" . $DI_35_noDI."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_35."|".$LocCampo."|" . $DI_35_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDIV2_35


/*************************************************************
* 
*  Funcion : fncValidaDIV2_37
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

function fncValidaDIV2_37($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_37           = "Tipo de Trabajador";
	$DI_37_ErrTam    = "Tipo de Trabajador debe ser de 2 Digítos";
	$DI_37_noDI   	 = "Tipo de Trabajador no corresponde al catalogo establecidas por DGRH(01,11,20)";
	
	

	$LocCampo =$Campo;
	if (strlen($LocCampo) == DOS)
	{
		if(!preg_match("/[0-9]{2}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_37."|".$LocCampo."|" . $DI_37_noDI."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_37."|".$LocCampo."|" . $DI_37_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDIV2_37


/*************************************************************
* 
*  Funcion : fncValidaDIV2_38
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

function fncValidaDIV2_38($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_38           = "Nivel de puesto - Nivel de puesto SPC";
	$DI_38_ErrTam    = "Nivel de puesto - Nivel de puesto SPC debe ser de 10 Digítos";
	$DI_38_noDI   	 = "Nivel de puesto - Nivel de puesto SPC no corresponde al catalogo establecidas por DGRH";
	$LocCampo =$Campo;
	if (strlen($LocCampo) == DIEZ)
	{
		if(!preg_match("/[0-9]{10}/",$LocCampo))
		{
			$Error = $NumReg ."|".$DI_38."|".$LocCampo."|" . $DI_38_noDI."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_38."|".$LocCampo."|" . $DI_38_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDIV2_38

/*************************************************************
* 
*  Funcion : fncValidaDIV2_39
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

function fncValidaDIV2_39($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_39           = "Indicador del Empleado - Estatus del Empleado";
	$DI_39_ErrTam    = "Indicador del Empleado - Estatus del Empleado debe ser de 1 Digíto";
	$DI_39_noDI   	 = "Indicador del Empleado - Estatus del Empleado no corresponde al catalogo establecido por DGRH(0,1,4)";

	$IndEmpl = array("0","2","1","4","3");	
	$LocCampo =$Campo;
	if (strlen($LocCampo) == UNO)
	{
		if(!in_array($LocCampo, $IndEmpl))
		{
			$Error = $NumReg ."|".$DI_39."|".$LocCampo."|" . $DI_39_noDI."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_39."|".$LocCampo."|" . $DI_39_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDIV2_39


/*************************************************************
* 
*  Funcion : fncValidaDIV2_40
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

function fncValidaDIV2_40($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_40           = "Fecha de Ingreso al Gobierno Federal";
	$DI_40_ErrTam    = "Fecha de Ingreso al Gobierno Federal debe ser de 8 Digíto(AAAAMMDD (AAAA=año, MM=mes, DD=día))";
	$DI_40_noDI   	 = "Fecha de Ingreso al Gobierno Federal no corresponde al formato establecido por DGRH(AAAAMMDD (AAAA=año, MM=mes, DD=día))";

		
	$LocCampo =$Campo;
	if (strlen($LocCampo) == OCHO)
	{
		if(!validateDate($LocCampo))
		{
			$Error = $NumReg ."|".$DI_40."|".$LocCampo."|" . $DI_40_noDI."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_40."|".$LocCampo."|" . $DI_40_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDIV2_40

/*************************************************************
* 
*  Funcion : fncValidaDIV2_41
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

function fncValidaDIV2_41($IdEstado, $GestorErr, $NumReg, $Campo, $Campo2,$Registro)
{
	 
	$Bandera = CERO;

	$DI_41           = "Fecha de Ingreso a la Secretaría de Salud";
	$DI_41_ErrTam    = "Fecha de Ingreso a la Secretaría de Salud debe ser de 8 Digíto(AAAAMMDD (AAAA=año, MM=mes, DD=día))";
	$DI_41_noDI   	 = "Fecha de Ingreso a la Secretaría de Salud no corresponde al formato establecido por DGRH(AAAAMMDD (AAAA=año, MM=mes, DD=día))";
	$DI_41_FecIng 	 = "Fecha de Ingreso a la Secretaría de Salud no puede ser menor a Fecha de Ingreso al Gobierno Federal";
		
	$LocCampo =$Campo;
	if (strlen($LocCampo) == OCHO)
	{
		if(!validateDate($LocCampo))
		{
			$Error = $NumReg ."|".$DI_41."|".$LocCampo."|" . $DI_41_noDI."|$Registro|\n";
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
					$Error = $NumReg ."|".$DI_41."|".$LocCampo."|" . $DI_41_FecIng."|$Registro|\n";
					fwrite($GestorErr, $Error);
					$Bandera = UNO;
			}	
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_41."|".$LocCampo."|" . $DI_41_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDIV2_41

/*************************************************************
* 
*  Funcion : fncValidaDIV2_42
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

function fncValidaDIV2_42($IdEstado, $GestorErr, $NumReg, $Campo, $Campo2,$Registro)
{
	 
	$Bandera = CERO;

	$DI_42           = "Fecha de Reingreso";
	$DI_42_ErrTam    = "Fecha de Reingreso debe ser de 8 Digíto(AAAAMMDD (AAAA=año, MM=mes, DD=día))";
	$DI_42_noDI   	 = "Fecha de Reingreso no corresponde al formato establecido por DGRH(AAAAMMDD (AAAA=año, MM=mes, DD=día))";
	$DI_42_FecIng 	 = "Fecha de Reingreso no puede ser menor a Fecha de Ingreso al Gobierno Federal";
		
	$LocCampo =$Campo;
	if (strlen($LocCampo) == OCHO)
	{
		if(!validateDate($LocCampo))
		{
			$Error = $NumReg ."|".$DI_42."|".$LocCampo."|" . $DI_42_noDI."|$Registro|\n";
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
					$Error = $NumReg ."|".$DI_42."|".$LocCampo."|" . $DI_42_FecIng."|$Registro|\n";
					fwrite($GestorErr, $Error);
					$Bandera = UNO;
			}	
		}	
	}
	else
	{
		$Error = $NumReg ."|".$DI_42."|".$LocCampo."|" . $DI_42_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDIV2_42

// campo 43 sin Directiva Institucional

/*************************************************************
* 
*  Funcion : fncValidaDIV2_44
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

function fncValidaDIV2_44($IdEstado, $GestorErr, $NumReg, $Campo,$Registro)
{
	 
	$Bandera = CERO;

	$DI_44           = "Fecha de Pago";
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
			$Error = $NumReg ."|".$DI_44."|".$LocCampo."|" . $DI_44_noDI."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;

		}	
		$Fecha =$Anio.str_pad(((int) $Resultado) +1,2,"0",STR_PAD_LEFT).$Dia;

		if(!validateDate($Fecha))
		{
			$Error = $NumReg ."|".$DI_44."|".$LocCampo."|" . $DI_44_noDI."|$Registro|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}
	}
	else
	{
		$Error = $NumReg ."|".$DI_44."|".$LocCampo."|" . $DI_44_ErrTam."|$Registro|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
} // fin de funcion fncValidaDIV2_44




?>