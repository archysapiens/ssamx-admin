<?php
session_start();
include "../general/DBC.php";
include "../general/generales.inc";
include "ptfma_despliega_resultado.inc";
include "ptma_opcd.inc";


$Credencial = $_POST['credencial'];
$db = new DbCnnx();  
//$FechaEvento-$Anio-$Qna-$Remesa-$IdArchivo-$FechaProcRemesa-$IdUsuario-$IdOrganismo

//echo "Recibi credencial >> $Credencial << <br>";
$ArrayCredencial = explode ("-",$Credencial);

$FechaProcValidacionTmp =$ArrayCredencial[CERO];

$FechaProcValidacion=substr($FechaProcValidacionTmp,0,4)."-".
						substr($FechaProcValidacionTmp,4,2)."-".
						substr($FechaProcValidacionTmp,6,2)." ".
						substr($FechaProcValidacionTmp,8,2).":".
						substr($FechaProcValidacionTmp,10,2).":".
						substr($FechaProcValidacionTmp,12,2);

$Anio = $ArrayCredencial[UNO];
$Quincena =$ArrayCredencial[DOS];


$FechaProceso = $ArrayCredencial[CINCO];
$IdRemesa =$ArrayCredencial[TRES];
$IdArchivo =$ArrayCredencial[CUATRO];

$SQL = "select fecha_evento, archivo_procesado, estatus, SUM(total) as total
		from bitacora 
		where id_remesas = $IdRemesa
		and fecha_evento = STR_TO_DATE('" . $FechaProceso . "','%Y%m%d%H%i%s')
		AND total IS NOT NULL
		GROUP BY fecha_evento, archivo_procesado, estatus";

//echo "SQL >>$SQL<<";
$Rows = $db->select($SQL);
$FechaEvento="";
if(is_array($Rows)){
	$HeaderArray=array($Anio,$Quincena );
	$Contador= CERO;
	$EstatusFinal = "K";
	
	$actual   = "";
	$anterior = "";
	//echo "Antes de while";
	while(isset($Rows[$Contador]['fecha_evento'])) {
            $FechaEvento = $Rows[$Contador]['fecha_evento'];
            $ArchivoProcesado = $Rows[$Contador]['archivo_procesado'];
            $Estatus = $Rows[$Contador]['estatus'];
            $Total = $Rows[$Contador]['total'];
            $actual = $FechaEvento;
           // echo "Contador >>$Contador<< anterior>>$anterior<<  actual>>$actual<<";
            if(preg_match ("/\.err/",$ArchivoProcesado))
            	array_push($HeaderArray,$ArchivoProcesado ."|".$Total);

			if(($actual != $anterior) and ($Contador > UNO)) {
	        	break;
            }
            if ($Estatus != "K")
	            	$EstatusFinal = "E";
            $anterior = $actual;
            $Contador++;
     }// fin de while
     //echo "despues de while";
//construyeTipoPanel($Estatus, $Icono,$TipoArchivo,$Descripcion,$FechaStage,$FechaLim,$IdPanel,$HeaderArray);
    //echo "<br> desplega_resultado/EstatusFinal>>$EstatusFinal<< / IdArchivo >>$IdArchivo<< <br>";
    //print_r($HeaderArray);
    //echo "<br>";
    echo construyeTipoPanel($EstatusFinal,"",$IdArchivo,"ptfma_despliega_resultado",$FechaEvento,$FechaProcValidacion,$IdArchivo,$HeaderArray);
}// fin de if(!is_array($Rows))
?>