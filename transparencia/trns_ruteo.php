<?php
//include "./general/DBC.php";
include "./general/generales.inc";
require("./general/ac_db_inc.php");
 
echo "Inicia programa <br>";

$ArrUsuarioInterfaz = explode("@",$_POST['inputUsuario']);

$UsuarioInterfaz = $ArrUsuarioInterfaz[0];

$Usuario = $_POST['inputUsuario'];

$Passwd = $_POST['inputPassword'];



echo "Consulta <br>";

$sql = "SELECT count(*) as existe FROM usuarios usu  where usu.id='" . 
		$Usuario .	"'  AND usu.password='" . 
		$Passwd."'";


echo "sql >$sql< <br>";


$db = new DbOracle("test_db", "ArchySoft");

echo "Antes del execFetchAll";

$res = $db->execFetchAll($sql, "Query Example");

echo "Antes del If";

if(!$res)
	header("location: index.php?msg=Credenciales no Autorizadas");
else
{
	session_start();
    $_SESSION = $_POST;
    //session_write_close();
	$Contador =  CERO;
	$Menu = "";

	foreach ($res as $row) {

	    $Existe = htmlspecialchars($row['EXISTE'], ENT_NOQUOTES, 'UTF-8');
	    $Contador++;
	}

	echo "Contador >>".$Contador ."<< <br>";
	echo "<br> EXISTE >>". $Existe ."<< <br>";

	echo "UsuarioInterfaz >>". strtoupper($UsuarioInterfaz) ."<< <br>";

	if ("VACANTES" == strtoupper($UsuarioInterfaz)){
		header("location: trns/trns_vacantes.php");
	}// IF 



}// if(!$rows)



?>