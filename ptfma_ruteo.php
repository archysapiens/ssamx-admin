<?php
include "./general/DBC.php";
include "./general/generales.inc";

$db = new DbCnnx();    

$Usuario="xxx";
if(isset($_POST['inputUsuario']))
	$Usuario=$_POST['inputUsuario'];

$Passwd="xxx";
if(isset($_POST['inputPassword']))
	$Passwd=$_POST['inputPassword'];


//echo "Usuario >$Usuario< Passwd >$Passwd< <br>";
//$Usuario = $db->quote($Usuario);
//$Passwd = $db->quote($Passwd);

$SQL = "SELECT usu.nombre as nombre_usuario,usu.app_paterno, usu.app_materno, 
		pri.id_roles, rol.descripcion, org.id, org.nombre as organismo
		FROM usuarios usu, privilegios pri, organismos org, roles rol
		WHERE usu.id=pri.id_usuarios AND pri.id_organismos= org.id AND 
		pri.id_roles= rol.id AND 
		usu.id='" . $Usuario ."' AND usu.password='" . $Passwd."'  AND pri.estatus='A'";
//echo "SQL >$SQL< <br>";
$rows = $db->select($SQL);
echo "error >>" .$db->error()."< <br>" ;

if(!$rows)
	header("location: index.php?msg=Credenciales no Autorizadas");
else
{
	echo "Si encontro registrs <bR>";
	session_start();
    $_SESSION = $_POST;
    //session_write_close();
	$Contador=  CERO;
	$Menu="";
	while(isset($rows[$Contador]['nombre_usuario']))
	{
		$_SESSION['idorg'] = $rows[$Contador]['id'];
		$_SESSION['organismo'] = $rows[$Contador]['organismo'];
		echo "id >>" .$rows[$Contador]['id'] ." << <br>" ;

		$NombreUsuario = $rows[$Contador]['nombre_usuario'] . " " . $rows[$Contador]['app_paterno'] . " ". $rows[$Contador]['app_materno'];
		$Organismo = $rows[$Contador]['organismo'];
		if($Contador == CERO)
			$MenuOperacion =$rows[$Contador]['id_roles'];
		else
			$MenuOperacion =$MenuOperacion . "|" . $rows[$Contador]['id_roles'];		
		$Contador++;
	}// fin del while 
	$_SESSION['nombre_usuario'] = $NombreUsuario;
	// menu_operacion solo identifica los menus que va desplegar en la barra lateral
	$_SESSION['menu_operacion'] = $MenuOperacion;
	$_SESSION['modalidad'] = "inicial";
	
	echo "MenuOperacion >>$MenuOperacion<< <br>";

	if($MenuOperacion == TRES)
		header("location: ptma_opcd/ptfma_admin.php");				
	elseif($MenuOperacion == DIEZ)
		header("location: ptma_opcd/ptfma_producto.php");					
	elseif($MenuOperacion == "1|2")	
		header("location: ptma_opcd/ptma_opcd.php");
	else	
		header("location: index.php?msg=Credenciales no Definidas");
/**
	if($pos = strpos($MenuOperacion, (string)TRES) === false)
		if($pos = strpos($MenuOperacion, (string) UNO) === false)
			header("location: index.php?msg=Credenciales no Definidas");
		else
			header("location: ptma_opcd/ptma_opcd.php");
	elseif($MenuOperacion==DIEZ)
		header("location: ptma_opcd/ptfma_producto.php");					
	else	
		header("location: ptma_opcd/ptfma_admin.php");				
**/		
}// if(!$rows)

?>