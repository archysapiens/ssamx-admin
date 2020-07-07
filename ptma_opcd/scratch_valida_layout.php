<?php
include "../general/generales.inc";
include "ptfma_demon.inc";

$Resultado = validaLayOut("../staging/20160624184025BD161508_ok.txt","|",87);
$NumCampos= count($Resultado);
echo "<br> NumCampos >>$NumCampos<< <br>";

?>