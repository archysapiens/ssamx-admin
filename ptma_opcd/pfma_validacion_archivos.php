<?php
session_start();
include "../general/generales.inc";
include "pfma_validacion_archivos.inc";
include "pfma_validacion_archivos_trailer.inc";
include "ptma_opcd.inc";
include "../general/DBC.php";

date_default_timezone_set('America/Mexico_City');
$FechaProceso = date("Y-m-d");
$HoraProceso = date("H:i:s");
$FechaProceso =$FechaProceso." ".$HoraProceso;


$ds         =  DIRECTORY_SEPARATOR; 
$IdEstado   = $_SESSION['idorg'] ;
$Anio=CERO;
if(isset($_GET['anio']))
    $Anio=$_GET['anio'];

$Quincena=CERO;
if(isset($_GET['quincena']))
    $Quincena=$_GET['quincena'];
$TipoArchivo=CERO;
if(isset($_GET['tipo_archivo']))
    $TipoArchivo=$_GET['tipo_archivo'];

$IdPanel="";
if(isset($_GET['idpanel']))
    $IdPanel=$_GET['idpanel'];

$IdTry=CERO;
if(isset($_POST['TRYSEND']))
    $IdTry = $_POST['TRYSEND'];

//echo "<br>IdTry >>$IdTry<< <br>";


$storeFolder  = 'validaciones' ;  
$UnZipPath    = '../staging/'  ;

$ArchivoValidar="";
$ResultadoValidacion=0; 
$ArrayArchivos=array();
$GestorArchivoErr = fopen("valida.log", "w");
$IdPlanificacion = -UNO;
fwrite($GestorArchivoErr, "Antes del If (!empty(_FILES)) \n");
if (is_array($_FILES)) 
{
 //   print_r($_FILES);

    fwrite($GestorArchivoErr, "despues  del If (!empty(_FILES)) \n");
    $targetPath = dirname( __FILE__ ) . $ds. $storeFolder . $ds; 
  //  print_r($_FILES);
    //$NumArch = count($_FILES['file']['name']);

    $NumArch = count($_FILES);

    $Error= "NumArch >>$NumArch<< \n";
    fwrite($GestorArchivoErr, $Error);

    for($Ind=0;$Ind < $NumArch; $Ind++){
        //echo $_FILES['file']['name'][$Ind] . "<br>";
        $ArchivoBase = $_FILES['file']['name'];
        $ArrArchivoBase =explode(".",$ArchivoBase);

        $tempFile = $_FILES['file']['tmp_name'];         
        $targetFile =  $targetPath. $_FILES['file']['name'];
     //   echo "Antes de mover archivo <br>";
     //   echo "tempFile >>$tempFile<<  targetFile>>$targetFile<< <br>";
        move_uploaded_file($tempFile,$targetFile);
/**
        if(move_uploaded_file($tempFile,$targetFile))
            echo "Se copio sin problemas <br>";
        else
            echo "Problemas al copiar <br>";    
**/
        if(extension_loaded('zip')){
            $zip = new ZipArchive;
            if ($zip->open($targetFile) === TRUE){
                $ArchivoValidar = $zip->getNameIndex(CERO);
                $zip->extractTo($UnZipPath);
                $zip->close();
                array_push($ArrayArchivos,$ArchivoValidar);
                $IdPlanificacion = planificaProceso($IdEstado,$Anio,$Quincena,$TipoArchivo,$UnZipPath.$ArchivoValidar,CERO,$IdTry);
            }else{ 
                echo "fallo al descomprimir >>". $targetFile ."<<";
                $IdPlanificacion = planificaProceso($IdEstado,$Anio,$Quincena,$TipoArchivo,$UnZipPath.$ArchivoValidar,FALLA,$IdTry);
            } // fin de if ($zip->open($targetFile)
        }    
        else{

                system("rm -f /var/www/html/staging/".$ArrArchivoBase[CERO].".*");
                $Comando = "unzip  ". $targetFile ." -d/var/www/html/staging";
               // $Comando = "unzip  -d/var/www/html/staging -f ". $targetFile;

                //echo "Comando >>$Comando<< <br>";
                $Resultado=system($Comando,$BaderaExec);
             //   echo "Resultado >>$Resultado<< BaderaExec >>$BaderaExec<< <br>";
                if ($BaderaExec== CERO){
                    $ArrTmpResultado =explode(":",$Resultado);
                    $ArraTmpResArchivo=explode("/",$ArrTmpResultado[UNO]);
                    $ArchivoValidar = end($ArraTmpResArchivo);
                    if (file_exists("/var/www/html/staging/".$ArchivoValidar)){
                        array_push($ArrayArchivos,$ArchivoValidar);
                        $IdPlanificacion = planificaProceso($IdEstado,$Anio,$Quincena,$TipoArchivo,$UnZipPath.$ArchivoValidar,CERO,$IdTry);
                    }
                    else
                        echo "pfma_validacion_archivos.php/No existe el archivo","/var/www/html/staging/".$ArchivoValidar;
                }
                else{
                    echo "fallo al descomprimir >>". $targetFile ."<<";
                    $IdPlanificacion = planificaProceso($IdEstado,$Anio,$Quincena,$TipoArchivo,$UnZipPath.$ArchivoValidar,FALLA,$IdTry);
                }
        }// fin del if extension_loaded('zip')
    }// fin de for    
    $NumArchivosPlanificados = obtenProcesosPlanificados($IdPlanificacion);

    //echo obtenResultadosValidacion($TipoArchivo, CERO,$NumArchivosPlanificados,"Cadana de Validacion",$UnZipPath.$ArchivoValidar.".err", $ResultadoValidacion);
    //construyeTipoPanel($Estatus, $Icono,$TipoArchivo,$Descripcion,$FechaStage,$FechaLim,$IdPanel,$HeaderArray);

    $HeaderArray=array($Anio,$Quincena );
    echo construyeTipoPanel("P","",$TipoArchivo,"Descripcion",$FechaProceso,"2016-05-23",$IdPanel,$HeaderArray);

fclose($GestorArchivoErr);
}else {                                                           
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
