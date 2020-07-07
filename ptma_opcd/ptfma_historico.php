<?php
session_start();
include "../general/generales.inc";
include "../general/DBC.php";
include "ptma_opcd.inc";
include "ptfma_historico.inc";

$quincenaurl="";
if(isset($_GET['quincenaurl']))
    $quincenaurl=$_GET['quincenaurl'];

$anioquincenaurl="";
if(isset($_GET['anioquincenaurl']))
    $anioquincenaurl=$_GET['anioquincenaurl'];

$HisQnas = obtenerHistoricoQnas($quincenaurl, $anioquincenaurl);
echo $HisQnas;
?>