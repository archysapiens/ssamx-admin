<?php
function validateDate($date, $format = 'Ymd')
{
    $d = DateTime::createFromFormat($format, $date);
    return $d && $d->format($format) == $date;
}


$Fecha="20160411";
echo validateDate($Fecha);

?>