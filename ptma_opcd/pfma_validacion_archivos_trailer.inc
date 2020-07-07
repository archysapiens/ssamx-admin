<?php
/*************************************************************
* 
*  Funcion : fncValidaArchivoTrailer
*  Objetivo: Validar el archivo de Trailer
*            
*  Fecha   : 1-May-2016
*  Autor   : ArchySapiens
*
*  Parametros
*   $IdEstado : Identificador del estado (01,02,...,30,DF,SP)
*   $Path     : Ruta de ubicacion 
*   $Archivo  : Archivo dedatos a validar
*   
*
***************************************************************/   

function fncValidaArchivoTrailer($IdEstado,$Archivo){
	$TotalRegErr       = CERO;
 	$ContadorRegistros = UNO;
 	
 	$ContadorErrorDIT = InicializaArray(16);

    echo "fncValidaArchivoTrailer IdEstado>$IdEstado<  Archivo>$Archivo< <br>";

 	$GestorArchivoErr = fopen($Archivo.".err", "w");
 	if (!$GestorArchivoErr) {
		echo "Error al abrir archivo Error >>" . $Archivo . ".err" . "<<";
	}
	else{
		$GestorArchivo = fopen($Archivo, "r");
		if ($GestorArchivo) 
		{
		    while (($Registro = fgets($GestorArchivo, 4096)) !== false) 
		    {
		    	$BanderaRegistr=0;
		   //     echo "Resgistro >>" . $Registro ."<<";
		        $ArrRegistro = explode("|",$Registro);
		        $NumFili= $ArrRegistro[0];
		        $NumEmpl= $ArrRegistro[1];
		        $NumChque= $ArrRegistro[2];
		        $TCONCEP = $ArrRegistro[3];
		        $CONCEP = $ArrRegistro[4];
		        $IMPORTE = $ArrRegistro[5];
		        $ANIO = $ArrRegistro[6];
		        $QNA = $ArrRegistro[7];
		        $PTAANT = $ArrRegistro[8];
		        $TOTPAGOS= $ArrRegistro[9];
		        $PAGOEFEC= $ArrRegistro[10];
		        $NOMPROD= $ArrRegistro[11];
		        $NUMCTROL= $ArrRegistro[12];
		        $NOMARCH= $ArrRegistro[13];
		        //$LLAVE= $ArrRegistro[14];

  				$ValidaError = fncValidaDIT_1($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NumFili);	
		        if($ValidaError!=0){
					$ContadorErrorDIT[UNO]++;
				}
//break;
		        $ValidaError = fncValidaDI_1($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NumEmpl);
		        if($ValidaError!=0){
					$ContadorErrorDIT[DOS]++;		        	
				}

				
				$ValidaError = fncValidaDIT_3($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NumChque);	
		        if($ValidaError!=0){
					$ContadorErrorDIT[TRES]++;		        	
				}


				$ValidaError = fncValidaDIT_4($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $TCONCEP);	
		        if($ValidaError!=0){
					$ContadorErrorDIT[CUATRO]++;
				}

				$ValidaError = fncValidaDIT_5($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $CONCEP);	
		        if($ValidaError!=0){
					$ContadorErrorDIT[CINCO]++;
				}

				$ValidaError = fncValidaDIT_6($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $IMPORTE);	
		        if($ValidaError!=0){
					$ContadorErrorDIT[SEIS]++;        	
				}

				$ValidaError = fncValidaDIT_7($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $ANIO);	
		        if($ValidaError!=0){
					$ContadorErrorDIT[SIETE]++;
				}

				$ValidaError = fncValidaDIT_8($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $QNA);	
		        if($ValidaError!=0){
					$ContadorErrorDIT[OCHO]++;
				}

				$ValidaError = fncValidaDIT_9($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $PTAANT);	
		        if($ValidaError!=0){
					$ContadorErrorDIT[NUEVE]++;
				}

				$ValidaError = fncValidaDIT_10($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $TOTPAGOS);	
		        if($ValidaError!=0){
					$ContadorErrorDIT[DIEZ]++;
				}

				$ValidaError = fncValidaDIT_11($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $PAGOEFEC);	
		        if($ValidaError!=0){
					$ContadorErrorDIT[DIEZ + UNO]++;
				}

				$ValidaError = fncValidaDIT_12($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NOMPROD);	
		        if($ValidaError!=0){
					$ContadorErrorDIT[DIEZ + DOS]++;
				}

				$ValidaError = fncValidaDIT_13($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NUMCTROL);	
		        if($ValidaError!=0){
					$ContadorErrorDIT[DIEZ + TRES]++;
				}
/**
				$ValidaError = fncValidaDIT_14($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $NOMARCH);	
		        if($ValidaError!=0){
					$ContadorErrorDIT[DIEZ + CUATRO]++;
				}

				$ValidaError = fncValidaDIT_15($IdEstado, $GestorArchivoErr, 
		        						$ContadorRegistros, $LLAVE);	
		        if($ValidaError!=0){
					$ContadorErrorDIT[DIEZ + CINCO]++;
				}
**/
				$ContadorRegistros++;
		    }// fin del while
		    //echo "Total registros >>$ContadorRegistros<< ";
		    foreach ($ContadorErrorDIT as &$valor) {
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
}// fin de la funcion fncValidaArchivoTrailer

/*************************************************************
* 
*  Funcion : fncValidaDIT_1
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

function fncValidaDIT_1($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = 0;

	$DIT_2           = "RFC";
	$DIT_2_ErrTam    = "Tamaño de registro debe ser 13 Caracteres";
	$DIT_2_ErrIdEdo  = "Identificador de estado Invalido";
	$DIT_2_ErrRFC = "RFC Incorrecto en Sección I AAAA";
	$DIT_2_ErrFecNac = "RFC Incorrecto en Sección II Fecha Nacimiento";
	$DIT_2_ErrHomoCve = "RFC Incorrecto en Sección III Homoclave";


	//echo "Datos Entrada: IdEstado >".$IdEstado. "< \nGestorErr >". $GestorErr ."< \nNumReg >".$NumReg. "< \nCampo >". $Campo ."<\n";

    /** Quita caracteres especiales **/
	$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);

	if (strlen($LocCampo) == 13)
	{

		if(!preg_match ("/[A-Z,a-z]{4}/" ,substr($LocCampo,0,4)))
		{
			$Error = $NumReg ."|".$DIT_2."|".$LocCampo."|" . $DIT_2_ErrRFC."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
		$CampoAux = substr($LocCampo,4,6);
		if(!preg_match ("/\d{6}/" ,$CampoAux))
		{
			$Error = $NumReg ."|".$DIT_2."|".$LocCampo."|" . $DIT_2_ErrFecNac ."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	

		if(strlen(substr($LocCampo,10,3)) != TRES)
		{
			$Error = $NumReg ."|".$DIT_2."|".$LocCampo."|" . $DIT_2_ErrHomoCve ."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	

	}
	else{
		$Error = $NumReg ."|".$DIT_2."|".$Campo."|" . $DIT_2_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_1


/*************************************************************
* 
*  Funcion : fncValidaDIT_3
*  Objetivo: Validar el campo Número de Cheque
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

function fncValidaDIT_3($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = 0;

	$DIT_3           = "Número de Cheque";
	$DIT_3_ErrTam    = "Tamaño de registro debe ser 9 Digitos";
	$DIT_3_ErrPatron  = "Número de Cheque no cumple con  directiva de Calidad 9 digitos";


	//echo "Datos Entrada: IdEstado >".$IdEstado. "< \nGestorErr >". $GestorErr ."< \nNumReg >".$NumReg. "< \nCampo >". $Campo ."<\n";

    /** Quita caracteres especiales **/
	$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);

	if (strlen($LocCampo) == 9)	{
		if(!preg_match ("/[0-9]{9}/" ,$LocCampo))
		{
			$Error = $NumReg ."|".$DIT_3."|".$LocCampo."|" . $DIT_3_ErrPatron."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	

	}
	else{
		$Error = $NumReg ."|".$DIT_3."|".$Campo."|" . $DIT_3_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = 1;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_3

/*************************************************************
* 
*  Funcion : fncValidaDIT_4
*  Objetivo: Validar el campo Tipo de Concepto
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

function fncValidaDIT_4($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = 0;

	$DIT_4           = "Tipo de Concepto";
	$DIT_4_ErrTam    = "Tamaño de registro debe ser 1 Digitos";
	$DIT_4_ErrPatron = "No cumple con la Directiva de Calidad definida por la DGRH [1-2]";
	


	//echo "Datos Entrada: IdEstado >".$IdEstado. "< \nGestorErr >". $GestorErr ."< \nNumReg >".$NumReg. "< \nCampo >". $Campo ."<\n";

    /** Quita caracteres especiales **/
	$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);

	if (strlen($LocCampo) == UNO)	{
		if(!preg_match ("/[1-2]{1}/" ,$LocCampo))
		{
			$Error = $NumReg ."|".$DIT_4."|".$LocCampo."|" . $DIT_4_ErrPatron."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = 1;
		}	
	}
	else{
		$Error = $NumReg ."|".$DIT_4."|".$Campo."|" . $DIT_4_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_4


/*************************************************************
* 
*  Funcion : fncValidaDIT_5
*  Objetivo: Validar el campo  Concepto
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

function fncValidaDIT_5($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = 0;

	$DIT_5           = "Concepto";
	$DIT_5_ErrTam    = "Tamaño de registro debe ser 2 Digitos";
	


	//echo "Datos Entrada: IdEstado >".$IdEstado. "< \nGestorErr >". $GestorErr ."< \nNumReg >".$NumReg. "< \nCampo >". $Campo ."<\n";

    /** Quita caracteres especiales **/
	$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);

	if (strlen($LocCampo) == DOS)	{
		$Bandera = CERO;
	}
	else{
		$Error = $NumReg ."|".$DIT_5."|".$Campo."|" . $DIT_5_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_5

/*************************************************************
* 
*  Funcion : fncValidaDIT_6
*  Objetivo: Validar el campo  Importe
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

function fncValidaDIT_6($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DIT_6           = "Importe";
	$DIT_6_ErrTam    = "Tamaño de registro debe ser mayor a CERO";
	


	//echo "Datos Entrada: IdEstado >".$IdEstado. "< \nGestorErr >". $GestorErr ."< \nNumReg >".$NumReg. "< \nCampo >". $Campo ."<\n";

    /** Quita caracteres especiales **/
	$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);

	if ($LocCampo > CERO)	{
		$Bandera = CERO;

	}
	else{
		$Error = $NumReg ."|".$DIT_6."|".$Campo."|" . $DIT_6_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_6

/*************************************************************
* 
*  Funcion : fncValidaDIT_7
*  Objetivo: Validar el campo  ANIO
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

function fncValidaDIT_7($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DIT_7           = "ANIO";
	$DIT_7_ErrTam    = "Tamaño de registro debe ser 4 Digitos";
	$DIT_7_ErrPattr    = "Debe ser digitos";
	


	//echo "Datos Entrada: IdEstado >".$IdEstado. "< \nGestorErr >". $GestorErr ."< \nNumReg >".$NumReg. "< \nCampo >". $Campo ."<\n";

    /** Quita caracteres especiales **/
	$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);

	if (strlen($LocCampo)  == CUATRO)	{
		if(!preg_match ("/[0-9]{4}/" ,$LocCampo))
		{
			$Error = $NumReg ."|".$DIT_7."|".$LocCampo."|" . $DIT_7_ErrPattr."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DIT_7."|".$Campo."|" . $DIT_7_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_7



/*************************************************************
* 
*  Funcion : fncValidaDIT_8
*  Objetivo: Validar el campo  Quincena
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

function fncValidaDIT_8($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DIT_8           = "Quincena";
	$DIT_8_ErrTam    = "Tamaño de registro debe ser 2 Digitos";
	$DIT_8_ErrPattr    = "Debe ser digitos";
	


	//echo "Datos Entrada: IdEstado >".$IdEstado. "< \nGestorErr >". $GestorErr ."< \nNumReg >".$NumReg. "< \nCampo >". $Campo ."<\n";

    /** Quita caracteres especiales **/
	$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);

	if (strlen($LocCampo)  == DOS)	{
		if(!preg_match ("/[0-9]{2}/" ,$LocCampo))
		{
			$Error = $NumReg ."|".$DIT_8."|".$LocCampo."|" . $DIT_8_ErrPattr."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DIT_8."|".$Campo."|" . $DIT_8_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_8

/*************************************************************
* 
*  Funcion : fncValidaDIT_9
*  Objetivo: Validar el campo  Partida Antecedente
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

function fncValidaDIT_9($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DIT_9           = "Partida Antecedente";
	$DIT_9_ErrTam    = "Tamaño de registro debe ser 2 Digitos";
	$DIT_9_ErrPattr    = "Debe ser digitos";
	


	//echo "Datos Entrada: IdEstado >".$IdEstado. "< \nGestorErr >". $GestorErr ."< \nNumReg >".$NumReg. "< \nCampo >". $Campo ."<\n";

    /** Quita caracteres especiales **/
	$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);

	if (strlen($LocCampo)  == DOS)	{
		if(!preg_match ("/[0-9|A-Z|a-z]{2}/" ,$LocCampo))
		{
			$Error = $NumReg ."|".$DIT_9."|".$LocCampo."|" . $DIT_9_ErrPattr."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DIT_9."|".$Campo."|" . $DIT_9_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_9

/*************************************************************
* 
*  Funcion : fncValidaDIT_10
*  Objetivo: Validar el campo  Total de Pagos
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

function fncValidaDIT_10($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DIT_10           = "Total de Pagos";
	$DIT_10_ErrTam    = "Tamaño de registro debe ser 4 Digitos";
	$DIT_10_ErrPattr    = "Debe ser digitos";
	


	//echo "Datos Entrada: IdEstado >".$IdEstado. "< \nGestorErr >". $GestorErr ."< \nNumReg >".$NumReg. "< \nCampo >". $Campo ."<\n";

    /** Quita caracteres especiales **/
	$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);

	if (strlen($LocCampo)  == CUATRO)	{
		if(!preg_match ("/[0-9]{4}/" ,$LocCampo))
		{
			$Error = $NumReg ."|".$DIT_10."|".$LocCampo."|" . $DIT_10_ErrPattr."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DIT_10."|".$Campo."|" . $DIT_10_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_10


/*************************************************************
* 
*  Funcion : fncValidaDIT_11
*  Objetivo: Validar el campo  Pagos Efectuados
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

function fncValidaDIT_11($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DIT_11           = "Pagos Efectuados";
	$DIT_11_ErrTam    = "Tamaño de registro debe ser 4 Digitos";
	$DIT_11_ErrPattr    = "Debe ser digitos";
	


	//echo "Datos Entrada: IdEstado >".$IdEstado. "< \nGestorErr >". $GestorErr ."< \nNumReg >".$NumReg. "< \nCampo >". $Campo ."<\n";

    /** Quita caracteres especiales **/
	$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);

	if (strlen($LocCampo)  == CUATRO)	{
		if(!preg_match ("/[0-9]{4}/" ,$LocCampo))
		{
			$Error = $NumReg ."|".$DIT_11."|".$LocCampo."|" . $DIT_11_ErrPattr."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}	
	}
	else{
		$Error = $NumReg ."|".$DIT_11."|".$Campo."|" . $DIT_11_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_11

/*************************************************************
* 
*  Funcion : fncValidaDIT_12
*  Objetivo: Validar el campo  Nombre del Producto
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

function fncValidaDIT_12($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DIT_12           = "Nombre del Producto";
	$DIT_12_ErrTam    = "Tamaño de registro debe ser 11 Digitos";
	$DIT_12_ErrPattr    = "Debe ser digitos";
	


	//echo "Datos Entrada: IdEstado >".$IdEstado. "< \nGestorErr >". $GestorErr ."< \nNumReg >".$NumReg. "< \nCampo >". $Campo ."<\n";

    /** Quita caracteres especiales **/
	$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);

	if (strlen($LocCampo)  == 11)	{
		$Bandera = CERO;	
	}
	else{
		$Error = $NumReg ."|".$DIT_12."|".$Campo."|" . $DIT_12_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_12

/*************************************************************
* 
*  Funcion : fncValidaDIT_13
*  Objetivo: Validar el campo  Número de Control
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

function fncValidaDIT_13($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DIT_13           = "Número de Control";
	$DIT_13_ErrTam    = "Tamaño de registro debe ser 20 Digitos";
	$DIT_13_ErrPattr    = "Debe ser digitos";
	


	//echo "Datos Entrada: IdEstado >".$IdEstado. "< \nGestorErr >". $GestorErr ."< \nNumReg >".$NumReg. "< \nCampo >". $Campo ."<\n";

    /** Quita caracteres especiales **/
	$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);

	if (strlen($LocCampo)  == 20)	{
		if(!preg_match ("/[0-9]{20}/" ,$LocCampo))
		{
			$Error = $NumReg ."|".$DIT_13."|".$LocCampo."|" . $DIT_13_ErrPattr."|\n";
			fwrite($GestorErr, $Error);
			$Bandera = UNO;
		}		
	}
	else{
		$Error = $NumReg ."|".$DIT_13."|".$Campo."|" . $DIT_13_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_13

/*************************************************************
* 
*  Funcion : fncValidaDIT_14
*  Objetivo: Validar el campo  Archivo cargado
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

function fncValidaDIT_14($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DIT_14           = "Archivo cargado";
	$DIT_14_ErrTam    = "Tamaño de registro debe ser 10 Caracteres";
	$DIT_14_ErrPattr    = "Debe ser digitos";

	//echo "Datos Entrada: IdEstado >".$IdEstado. "< \nGestorErr >". $GestorErr ."< \nNumReg >".$NumReg. "< \nCampo >". $Campo ."<\n";

    /** Quita caracteres especiales **/
	$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);

	if (strlen($LocCampo)  == DIEZ)	{
		$Bandera = CERO;		
	}
	else{
		$Error = $NumReg ."|".$DIT_14."|".$Campo."|" . $DIT_14_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_14

/*************************************************************
* 
*  Funcion : fncValidaDIT_15
*  Objetivo: Validar el campo  Llave
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

function fncValidaDIT_15($IdEstado, $GestorErr, $NumReg, $Campo)
{
	 
	$Bandera = CERO;

	$DIT_15           = "Llave";
	$DIT_15_ErrTam    = "Tamaño de registro debe ser 50 Caracteres";
	$DIT_15_ErrPattr    = "Debe ser digitos";

	//echo "Datos Entrada: IdEstado >".$IdEstado. "< \nGestorErr >". $GestorErr ."< \nNumReg >".$NumReg. "< \nCampo >". $Campo ."<\n";

    /** Quita caracteres especiales **/
	$LocCampo =preg_replace('/[^A-Za-z0-9\-]/', '', $Campo);

	if (strlen($LocCampo)  == 50)	{
		$Bandera = CERO;		
	}
	else{
		$Error = $NumReg ."|".$DIT_15."|".$Campo."|" . $DIT_15_ErrTam."|\n";
		fwrite($GestorErr, $Error);
		$Bandera = UNO;
	}
	return $Bandera;
}// fin de funcion fncValidaDI_15


?>