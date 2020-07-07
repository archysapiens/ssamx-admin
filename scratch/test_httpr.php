<?php
$storeFolder  = 'validaciones' ;  
$UnZipPath    = '../staging/'  ;
$ds         ="/";


echo "Regressando ". $_POST['CustomField'] ."<br>";
//echo "Regressando ". $_POST['accountnum']."<br>";

if (is_array($_FILES)) 
{
	$targetPath = dirname( __FILE__ ) . $ds. $storeFolder . $ds; 
	$NumArch = count($_FILES['SelectArchivoProductoBase']['name']);
	print_r($_FILES);
	echo "Numero de archivos >>$NumArch<< <br>";
	 for($Ind=0;$Ind < $NumArch; $Ind++){
        //echo $_FILES['file']['name'][$Ind] . "<br>";
        $ArchivoBase = $_FILES['SelectArchivoProductoBase']['name'][$Ind];
        $tempFile = $_FILES['SelectArchivoProductoBase']['tmp_name'][$Ind];         
        $targetFile =  $targetPath. $_FILES['SelectArchivoProductoBase']['name'][$Ind];
        echo "targetFile >>$targetFile<< <br>";
     //   echo "Antes de mover archivo <br>";
     //   echo "tempFile >>$tempFile<<  targetFile>>$targetFile<< <br>";
        move_uploaded_file($tempFile,$targetFile);
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