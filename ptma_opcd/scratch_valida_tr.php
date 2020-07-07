<?php

include "../general/DBCBATCH.php";
include "../general/generales.inc";
include "pfma_validacion_archivos.inc";
include "pfma_validacion_archivos_trailer.inc";
include "ptma_opcd.inc";

$res = fncValidaArchivoTrailer("15", "../staging/20160519170611BT161508.txt");

echo "res  >>$res<< <br>";


?>