<?php
$storeFolder  = 'validaciones' ;  
$UnZipPath    = '../staging/'  ;
$ds         ="/";

echo "Estamos en test_httpV2.php "."<br>";

echo "Regressando ". $_POST['TagEnvio'] ."<br>";
//echo "Regressando ". $_POST['accountnum']."<br>";

if (is_array($_FILES)) 
{
	$targetPath = dirname( __FILE__ ) . $ds. $storeFolder . $ds; 
	//$NumArch = count($_FILES['SelectArchivoProductoBase']['name']);
	$NumArch = count($_FILES);
	print_r($_FILES);
	echo "Numero de archivos >>$NumArch<< <br>";
	 for($Ind=0;$Ind < $NumArch; $Ind++){
        //echo $_FILES['file']['name'][$Ind] . "<br>";
        $ArchivoBase = $_FILES['afile']['name'];
        $tempFile = $_FILES['afile']['tmp_name'];         
        $targetFile =  $targetPath. $_FILES['afile']['name'];
        echo "targetFile >>$targetFile<< <br>";
     //   echo "Antes de mover archivo <br>";
     //   echo "tempFile >>$tempFile<<  targetFile>>$targetFile<< <br>";
        move_uploaded_file($tempFile,$targetFile);
    }
   if (file_exists($targetFile)) {
        echo "El fichero $nombre_fichero existe";
    } else {
        echo "El fichero $nombre_fichero no existe";
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