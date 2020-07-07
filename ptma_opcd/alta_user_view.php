<?php
session_start();
include "../general/DBC.php";
include "../general/generales.inc";
include "alta_user_view.inc";
include "../general/CnxGral.inc";
$Conn = fncConxBaseDatos(HOST, USU, PWD, BD );
   
    
   
$Bienvenida="";
if(isset($_SESSION['modalidad']))
	$Bienvenida=$_SESSION['modalidad'];

$quincenaurl="";
if(isset($_GET['quincenaurl']))
	$quincenaurl=$_GET['quincenaurl'];

$anioquincenaurl="";
if(isset($_GET['anioquincenaurl']))
	$anioquincenaurl=$_GET['anioquincenaurl'];

/**

echo "Inciando <br>";
echo "quincenaurl >$quincenaurl< <br>";
echo "anioquincenaurl >>$anioquincenaurl<<br>";

**/

$Configuracion 	= configuraSesion($quincenaurl,$anioquincenaurl);
$Dropzones  	= construyeDropzones($Configuracion);

/*echo ">>$Configuracion<< <br>";*/
$_SESSION['configuracion'] = $Configuracion;
$JS = fncBuildJS($Bienvenida,$Dropzones);

echo fncBuildHead();
echo fncBuildBody($Configuracion);
echo fncBuildTail($JS);

$_SESSION['modalidad']="operacion";


if (isset($_POST['submitConfirmarAlta'])) {
            switch($_POST['submitConfirmarAlta']) {
                case "confirmar":
							$id= $_POST['txt_email'];
							$nombre = $_POST['txt_nombre'];
							$app_paterno = $_POST['txt_app_p'];
							$app_materno = $_POST['txt_app_m'];
							$sexo= $_POST['sexo'];
							$edad= $_POST['txt_edad'];
							@$fecha_nac= $_POST['txt_fech_nac'];
							$foto='ola.png';
							$usuario=$_POST['txt_usuario'];
							$tel_oficina = $_POST['txt_tel_ofi'];
							$extension = $_POST['txt_ext'];
							$tel_mobil = $_POST['txt_tel_per'];
							$organismos = $_POST['txt_organismos'];
							$unid_respon = $_POST['txt_uni_respon'];
							$pregunta=$_POST['txt_pregunta_seguridad'];
							$respuesta=$_POST['txt_respuesta'];
							$password = $_POST['txt_psw'];
							$query_insert_user=mysqli_query($Conn, "INSERT INTO usuarios VALUES ('$id','$nombre','$app_paterno','$app_materno','$sexo','$edad','$fecha_nac','$foto','$usuario','$tel_oficina','$extension','$tel_mobil','$organismos','$unid_respon','1','$pregunta','$respuesta','$password')");
							$query_insert_user=mysqli_query($Conn, "INSERT INTO privilegios VALUES (NOW(),'$organismos','$id','I',NOW(),1)");
							
							include("AltaUsuario.php");
                   
                    BREAK;
            }
        }
		
		
		
					

?>