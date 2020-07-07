<?php

$LocCampo="HOSPITAL GENERAL DE LA CIUDAD DE MEXICO 12";
echo ">>" . preg_match("/[0-9,A-Z,a-z,' ']/",$LocCampo) . "<<";


?>