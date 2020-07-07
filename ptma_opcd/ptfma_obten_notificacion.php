<?php
session_start();
include "../general/DBC.php";
include "../general/generales.inc";

$IdUsuario ="";
if(isset($_SESSION['inputUsuario']))
	$IdUsuario =$_SESSION['inputUsuario'];

$IdOrganismo ="";
if(isset($_SESSION['idorg'] ))
	$IdOrganismo =$_SESSION['idorg'] ;

$db = new DbCnnx();    

$IdOrganismo  = $db->quote($IdOrganismo);
$IdUsuario    = $db->quote($IdUsuario);


$SQL = "SELECT  DATE_FORMAT(noti.fecha_evento_envio,'%Y%m%d%H%i%s') AS fecha_evento_envio, 
		noti.tipo_evento, noti.tipo_evento_detalle, 
		noti.anio_periodos, noti.numero_periodos, noti.id_remesas, CEILING(TIMESTAMPDIFF(SECOND,noti.fecha_evento_envio, NOW())/60) AS tiempo,
		reme.id_archivos, noti.tipo_evento_detalle as tipo_evento_detalle
		FROM notificaciones noti, remesas reme 
		WHERE noti.id_remesas = reme.id AND 
		noti.estatus='A' AND noti.id_usuarios=".$IdUsuario . 
		" AND noti.id_organismos =".$IdOrganismo .
		"order by noti.fecha_evento_envio desc";

echo ">>$SQL<<";
$Rows = $db->select($SQL);
$Contador= CERO;
if(is_array($Rows)){
		//echo "Si fue array <br>";
	 	while(isset($Rows[$Contador]['fecha_evento_envio']) and $Contador < TRES){
	        $FechaEvento = $Rows[$Contador]['fecha_evento_envio'];
	        $TipoEvento = $Rows[$Contador]['tipo_evento'];
	        $EventoDetalle = $Rows[$Contador]['tipo_evento_detalle'];
	        $Anio = $Rows[$Contador]['anio_periodos'];
	        $Qna = $Rows[$Contador]['numero_periodos'];
	        $Remesa = $Rows[$Contador]['id_remesas'];
	        $IdArchivo = $Rows[$Contador]['id_archivos'];
	        $Tiempo = $Rows[$Contador]['tiempo'];
	        $TipoEventoDet = $Rows[$Contador]['tipo_evento_detalle'];
	        $FechaProcRemesa="";

	        if($TipoEvento=="PV"){
	        	$ArrayDetalle = explode("/", $TipoEventoDet);
	        	if(is_array($ArrayDetalle)){
	        		$ArchDet = $ArrayDetalle[DOS];
	        		$FechaProcRemesa =substr($ArchDet,0,14);
	        	}// fin id is array
	        }// fin de if($TipoEvento=="PV")

	        if($Tiempo < 360)
	        		$Tiempo= "hace $Tiempo Min.";
	        elseif($Tiempo >= 360 and $Tiempo < 1440){
	        		$Horas = floor ($Tiempo/60);
	        		$Minutos= $Tiempo % 60;
	        		$Tiempo = "hace $Horas Hrs. $Minutos min.";
	        }// fin de if($Tiempo < 360)	

	        switch($TipoEvento){
	        	case 'PV': $Icono ="glyphicon glyphicon-alert";
	        			$Msg="Resultado Validación"; break;
	        	case 'T'  : $Icono ="glyphicon glyphicon-time"; 
	        				$Msg="Periodo envío PN";break;
	        }// fin switch

	        echo "
	         <li>
                <a  href=\"#\">
                	<div id=\"$FechaEvento-$Anio-$Qna-$Remesa-$IdArchivo-$FechaProcRemesa-$IdUsuario-$IdOrganismo\">
                       <i id=\"icono\" class=\"$Icono \"></i> 
                           $Msg
                        <span id=\"span\" class=\"pull-right text-muted small\">$Tiempo </span>
                    </div>
                 </a>
                </li>
             <li class=\"divider\"></li>
                 ";       


	        $Contador++;
	     }// fin del while   
}
else{
	//echo "No encontró Mensajes";
	echo "xxx";
}


?>