<?php

/*********************************************************************
 * 
 * Funcion : cargaRegistrosError
 * Objetivo: Genera el archivo para carga archivos de 
 *           
 * Parametros
 * $IdRemesa:  Identificador de remesa
 * $TagEnvio   : Identificador que etiqueta la remesa
 * $IdArchivoPN: Identificador de archivo de producto de nomina              
 * Retorno
 * $Resultado  : CERO si se elimino correctamente
 *               otro numero si existe aun el registro
 **********************************************************************/

function cargaRegistrosError($IdRemesa, $TagEnvio,$IdArchivoPN,$TipoArchivo){
$PathExec="../staging/";	
$TagEnvioAux =$TagEnvio."-".$IdArchivoPN;
$GestorArchivoSql = fopen($PathExec.$TagEnvioAux."_".$TipoArchivo.".sql", "w");

$SUFF="tra";
if($TipoArchivo == "D")
	$SUFF="dat";

if (!$GestorArchivoSql) {
	echo "Error al abrir archivo Error >>".$PathExec.$TagEnvio."_".$TipoArchivo.".sql" ."<<";
}
else{
	fwrite($GestorArchivoSql, "set @idremesa=$IdRemesa;\n" );
	fwrite($GestorArchivoSql, "set @etiqueta='$TagEnvio';\n" );
	fwrite($GestorArchivoSql, "set @archivo_err='$IdArchivoPN.$SUFF';\n" );
	fwrite($GestorArchivoSql, "set @fecha=now();\n" );
	fwrite($GestorArchivoSql, "load data local infile '../staging/$IdArchivoPN.$SUFF.err'\n" );
	fwrite($GestorArchivoSql, "INTO TABLE errores\n" );
	fwrite($GestorArchivoSql, "FIELDS TERMINATED BY '|' ENCLOSED BY '\"'\n" );
	fwrite($GestorArchivoSql, "LINES TERMINATED BY '\\n'\n" );
	fwrite($GestorArchivoSql, "(numero_registro,  campo, evidencia, descripcion)\n" );
	fwrite($GestorArchivoSql, "set id_remesas=@idremesa, etiqueta_envio=@etiqueta,\n" );
	fwrite($GestorArchivoSql, "archivo_error=@archivo_err,fecha_registro=@fecha;\n" );
	fclose($GestorArchivoSql);

	//$Comando = "mysql --host=localhost --user=root ssa <".$PathExec.$TagEnvioAux.".sql";
	//system($Comando, $retval);
	//echo "retval >>$retval<<";
	//echo "Comando >>$Comando<<";
}

}// fin de cargaRegistrosError

/*********************************************************************
 * 
 * Funcion : registraResultadoValidacion
 * Objetivo: Registra el resultado d ela validacion del archvio
 *           considera archivo de datos y trailer
 * Parametros
 * $IdArchivo:  Identificador del Archivo a eliminar
 * $TagEnvio   : Identificador que etiqueta la remesa
 *               
 * Retorno
 * $Resultado  : CERO si se elimino correctamente
 *               otro numero si existe aun el registro
 **********************************************************************/

function registraResultadoValidacion($TagEnvio,$IdArchivoPN,$ResultadoValidacionDat,$ProductoNomina){
$db = new DbCnnx();  
$Resultado = CERO;
$PathStaging="../staging/";
$ArchivoActualizadoErr = $PathStaging.$IdArchivoPN.".err";
$ArchivoActualizado = $PathStaging.$IdArchivoPN;
$SQL= "update logger 
		set archivo_error='$ArchivoActualizadoErr',
		registros_error=$ResultadoValidacionDat,
		fecha_validacion=NOW(), estatus='A',
		id_tipo_nom='$ProductoNomina'
    WHERE archivo = '$ArchivoActualizado' AND 
    etiqueta_envio='$TagEnvio'";	
//echo "registraResultadoValidacion SQL >$SQL< <br>";
$Rows = $db->select($SQL);    


}// fin de registraResultadoValidacion 


/*********************************************************************
 * 
 * Funcion : eliminaArchivoPN
 * Objetivo: Elimna Archivo de producto de nomina
 *           
 * Parametros
 * $IdArchivo:  Identificador del Archivo a eliminar
 * $TagEnvio   : Identificador que etiqueta la remesa
 *               
 * Retorno
 * $Resultado  : CERO si se elimino correctamente
 *               otro numero si existe aun el registro
 **********************************************************************/
function eliminaArchivoPN($IdArchivo, $TagEnvio,$IdRemesa){
$db = new DbCnnx();  
$Resultado = CERO;
$SQL= "delete from logger
    WHERE archivo like '%$IdArchivo%' AND 
    etiqueta_envio='$TagEnvio'";

$Rows = $db->select($SQL);

$SQL= "delete from errores
    WHERE archivo_error like '%$IdArchivo%' AND 
    etiqueta_envio='$TagEnvio' and id_remesas=$IdRemesa";

$Rows = $db->select($SQL);


$SQL= "select count(*) existe
        WHERE archivo like '%$IdArchivo%' AND 
        etiqueta_envio='$TagEnvio'";

$Rows = $db->select($SQL);
if(is_array($Rows)){
  $Contador= CERO;
  if(isset($Rows[$Contador]['existe']))
  	$Resultado = $Rows[$Contador]['existe'];
}else
	$Resultado = CERO;
return $Resultado;
}// fin de 	eliminaarchivoPN

?>