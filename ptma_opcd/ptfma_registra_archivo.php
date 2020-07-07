<?php

session_start();
include "../general/DBC.php";
include "../general/generales.inc";
include "ptfma_registra_archivo.inc";

include "ptfma_producto.inc";


$storeFolder  = '../staging/' ;  
$UnZipPath    = '../staging/'  ;
$ds         ="/";

//echo "Estamos en ptfma_registra_archivo.php "."<br>";


$TagEnvio ="";
if(isset($_POST['TagEnvio']))
    $TagEnvio = $_POST['TagEnvio'];

$IdOrg="";
if(isset($_SESSION['idorg']))
    $IdOrg = $_SESSION['idorg'];

//echo "Regressando ". $TagEnvio ."<br>";
$ArrTagEnvio = explode("-",$TagEnvio);

$AnioProc = $ArrTagEnvio[UNO];
$QnaProc  = $ArrTagEnvio[DOS];

//echo "Regressando ". $_POST['accountnum']."<br>";
$TablaArchivoProdNomina="";
    //print_r($_FILES);
if (is_array($_FILES)) 
{
    $targetPath = dirname( __FILE__ ) . $ds. $storeFolder ; 
    //$NumArch = count($_FILES['SelectArchivoProductoBase']['name']);
    $NumArch = count($_FILES);
   // print_r($_FILES);
    //echo "Numero de archivos >>$NumArch<< <br>";
     for($Ind=0;$Ind < $NumArch; $Ind++){
        //echo $_FILES['file']['name'][$Ind] . "<br>";
        $ArchivoBase = strtolower($_FILES['producto_nomina']['name']);
        $ArrArchivoBase =explode(".", $ArchivoBase);
        $ExtensionArchivo = $ArrArchivoBase[UNO];
        $tempFile = $_FILES['producto_nomina']['tmp_name'];         
        $targetFile =  strtolower($targetPath. $_FILES['producto_nomina']['name']);

//        echo "targetFile >>$targetFile<< <br>";
     //   echo "Antes de mover archivo <br>";
     //   echo "tempFile >>$tempFile<<  targetFile>>$targetFile<< <br>";
        move_uploaded_file($tempFile,$targetFile);
    }
   if (file_exists($targetFile)) {
        //echo "El fichero $targetFile existe";
        $Resultado = registraArchivoPN($TagEnvio,$storeFolder.$ArchivoBase,$ExtensionArchivo);
        $TablaArchivoProdNomina = obtenArchivoPN($AnioProc, $QnaProc,$IdOrg);
        echo $TablaArchivoProdNomina;
    } else {
        echo "El fichero $targetFile no existe";
    }
}
else{
            
    $result  = array();
    $files = scandir($storeFolder);                 
    if ( false!==$files ) {
        foreach ( $files as $file ) {
            if ( '.'!=$file && '..'!=$file) {       
                $obj['name'] = $file;
                $obj['size'] = filesize($storeFolder.$ds.$file);
                $result[] = $obj;
            }
        }// foreach
    } // if ( false!==$files )
    header('Content-type: text/json');              
    header('Content-type: application/json');
    echo json_encode($result);
 }        


?>