<?php 
function formateaFechas($fecha_original='2016-7-20', $formato='%d de %B del %Y') { 
    
    return (!empty($fecha_original) ? strftime($formato, strtotime($fecha_original)) : "" ); 
} 
echo formateaFechas("2016-7-20")."<br>";
echo formateaFechas("2016-1-20")."<br>";
echo formateaFechas("2016-2-20")."<br>";
echo formateaFechas("2016-3-20")."<br>";
echo formateaFechas("2016-4-20")."<br>";
echo formateaFechas("2016-5-20")."<br>";
echo formateaFechas("2016-6-20")."<br>";

?> 