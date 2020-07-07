<?php




function registraArchivoPN($TagEnvio, $Archivo, $ExtensionArchivo){

$db = new DbCnnx();    
// Desemtramar Etiqueta de Envio
$TipoArchivo=strtoupper($ExtensionArchivo);
$ArrTag = explode ("-",$TagEnvio);
$IdOrg = $ArrTag[CERO];
$Anio  = $ArrTag[UNO];
$Qna   = $ArrTag[DOS];
$Tagdate = $ArrTag[TRES];
$TipoArch = $ArrTag[CUATRO];

//echo "TipoArch >>$TipoArch<< <br>";
//echo "TipoArchivo >>$TipoArchivo<< <br>";

$SQLRegistro="SELECT  id,  fecha_asignacion,  fecha_actualizacion,
			    id_organismos,  estatus,  id_archivos,
			    anio_periodos,  numero_periodos,  id_usuarios
				FROM ssa.remesas
				WHERE anio_periodos=$Anio AND 
				numero_periodos=$Qna AND 
				id_organismos='$IdOrg' AND id_archivos=$TipoArch";

$Rows = $db->select($SQLRegistro);
$NumeroRegistros=0;
if(is_array($Rows)){
  $Contador = CERO;
  if(isset($Rows[$Contador]['id'])) {				
  		$IdRemesa = $Rows[$Contador]['id'];
 		
  		$NumeroRegistros = calculaNumeroRegistros($Archivo);
  		

		//echo "registraArchivoPN/$Archivo";	
		
  		$SQLLogger = "INSERT INTO logger(id_remesas, fecha_registro,   fecha_validacion,
             fecha_carga,             tipo_archivo,             archivo,
             registros,             observaciones,             etiqueta_envio,
             archivo_error,             registros_error,             estatus,
             id_tipo_nom,fecha_agregacion)
		VALUES ($IdRemesa, STR_TO_DATE('" . $Tagdate . "','%Y%m%d%H%i%s'),   null,
		        null,        SUBSTRING('$TipoArchivo',1,1), '$Archivo',
		        $NumeroRegistros,'Registro Inicial','$TagEnvio',
		        null,        null,        'I',
		        null,now())	";
		$Rows = $db->select($SQLLogger);

		//echo "registraArchivoPN Error >>".$db->error() ."<< <br>";
  }// fin if(isset
}  	

} // fin function registraArchivoPN

/*********************************************************************
 * 
 * Funcion : calculaNumeroRegistros
 * Objetivo: Calcula el numero de registros de un archivo
 *           
 * Parametros
 * Archivo:  Identificador del Archivo a contabilizar
 * Retorno
 * TotalRegistros  : Total de registros en el archivo
 **********************************************************************/

function calculaNumeroRegistros($Archivo){

$TotalRegistros = CERO;

$fp = fopen( $Archivo, "r");
	while(($bufer = fgets($fp, 4096)) !== false) {
			
			$TotalRegistros++;
	}

fclose( $fp);

return $TotalRegistros;
}


?>