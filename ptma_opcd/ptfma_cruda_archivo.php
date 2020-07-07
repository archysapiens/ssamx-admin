<?php
session_start();
include "../general/DBC.php";
include "../general/generales.inc";
include "ptfma_cruda_archivo.inc";
include "ptfma_producto.inc";
include "pfma_validacion_archivos.inc";
include "pfma_validacion_archivos_trailer.inc";

//$_POST = $_SESSION ;

$TagEnvio="";
if(isset($_POST['TagEnvio']))
	$TagEnvio=$_POST['TagEnvio'];

$IdRemesa="";
if(isset($_POST['idremesa']))
	$IdRemesa=$_POST['idremesa'];

$IdArchivoPN="";
if(isset($_POST['idarchivopn']))
	$IdArchivoPN=$_POST['idarchivopn'];

$Operacion="";
if(isset($_POST['operacion']))
	$Operacion=$_POST['operacion'];

$ProductoNomina="";
if(isset($_POST['pn']))
	$ProductoNomina=$_POST['pn'];

/**
echo "TagEnvio >>$TagEnvio<< <br>";
echo "IdRemesa >$IdRemesa< <br>";
echo "IdArchivoPN >>$IdArchivoPN< <br>";
echo "Operacion >>$Operacion< <br>";
**/
$ArrTagEnvio= explode("-", $TagEnvio);
$IdOrg = $ArrTagEnvio[CERO];
$AnioProc = $ArrTagEnvio[UNO];
$QnaProc = $ArrTagEnvio[DOS];
if($Operacion=="eliminar"){
	$Resultado = eliminaArchivoPN($IdArchivoPN, $TagEnvio,$IdRemesa);
	if($Resultado== CERO){
		$TablaArchivoProdNomina = obtenArchivoPN($AnioProc, $QnaProc,$IdOrg);
        echo $TablaArchivoProdNomina;
	}
	else
		echo "<br><br> ERROR al eliminar Archivo <br><br>";

}
else if($Operacion=="analizar"){

	$ResultadoValidacionDat = fncValidaArchivo($IdOrg, "../staging/",$IdArchivoPN.".dat");
	$ResultadoRegistro = registraResultadoValidacion($TagEnvio,$IdArchivoPN.".dat",$ResultadoValidacionDat,$ProductoNomina);	

	// en esta funcion se usan solo dos parametros

	$ResultadoValidacionTra = fncValidaArchivoTrailer($IdOrg,"../staging/".$IdArchivoPN.".tra");

	

	$ResultadoRegistro = registraResultadoValidacion($TagEnvio,$IdArchivoPN.".tra",$ResultadoValidacionTra,$ProductoNomina);

	if($ResultadoValidacionDat > CERO){
		// "D" Archivo de Datos
		$Resultado = cargaRegistrosError($IdRemesa, $TagEnvio,$IdArchivoPN,"D");
	}
	if($ResultadoValidacionTra > CERO){
		// "T" Archivo Trail
		$Resultado = cargaRegistrosError($IdRemesa, $TagEnvio,$IdArchivoPN,"T");
	}




	$TablaArchivoProdNomina = obtenArchivoPN($AnioProc, $QnaProc,$IdOrg);
    echo $TablaArchivoProdNomina;

}
else
	echo "<br><br>No se identifica la operacion <br><br>";
	
?>