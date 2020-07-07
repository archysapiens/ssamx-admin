<?php
session_start();
include "../general/DBC.php";
include "../general/generales.inc";
include "ptma_opcd.inc";
include "ptfma_admin.inc";


$JS = fncBuildJSAdmin();
echo fncBuildHead();
echo fncBuildBodyAdmin();
echo fncBuildTail($JS);

?>


