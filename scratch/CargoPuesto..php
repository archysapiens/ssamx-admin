<?php



$GestorArchivo = fopen("estructura.txt", "r");
 	if (!$GestorArchivoErr) 
	{
		echo "Error al abrir archivo Error >>estructura.txt" ."<<";
	}
	else{
		    while (($Registro = fgets($GestorArchivo, 4096)) !== false) 
		    {
		    	$BanderaRegistr=0;
		   //     echo "Resgistro >>" . $Registro ."<<";
		        $ArrRegistro = explode("|",$Registro);
		     }
	}	        

?>		        