<?php
include "../general/generales.inc";
include "pfma_validacion_archivos.inc";

include "../general/DBC.php";
$IdEstado=15;
$UnZipPath="../staging/";
$ArchivoValidar="HO0416DA.txt.err";

$ResultadoRegistro = registraValidacion($IdEstado,2016,8,1,$UnZipPath.$ArchivoValidar);
                   //registraValidacion($IdEstado,2016,8,1,$UnZipPath.$ArchivoValidar);

?>