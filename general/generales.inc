<?php
define("UNO", 1);
define("DOS", 2);
define("TRES", 3);
define("CUATRO", 4);
define("CINCO", 5);
define("SEIS", 6);
define("SIETE", 7);
define("OCHO", 8);
define("NUEVE", 9);
define("CERO", 0);
define("EXITO", 0);
define("FALLA", 1);
define("DIEZ", 10);
define("DATA_NOMINA", "DATA_NOMINA");
define("DATA_NOMINA_TRAILER", "DATA_NOMINA_TRAILER");


function formateaFechas($fecha = "2016-7-20") 
	{
    $meses = array("Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre");
    $fecha = explode("-", $fecha);

    if ($fecha) {        
          $fecha[0] = $fecha[0][2] . " de " .$meses[date('n')-1]. " del " . $fecha[0][0];
    }
    return $fecha[0];
} // fin de formateaFechas




?>