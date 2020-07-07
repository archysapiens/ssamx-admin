<?php
session_start();
include "../general/generales.inc";
include "ptma_opcd_tab.inc";


$JS = fncBuildJS();
echo fncBuildHead();
echo fncBuildBody();
echo fncBuildTail($JS);




?>