<?php
include "../general/DBC.php";
include "../general/generales.inc";
include "ptfma_registro.inc";
$db = new DbCnnx(); 
   
echo fncBuildHead();
echo fncBuildBody();
echo fncBuildJS();

if (isset($_POST['submitConfirmarAlta'])) {
            switch($_POST['submitConfirmarAlta']) {
                case "confirmar":
				
							$target_path = "../images/FileUpload/";
							$target_path = $target_path . basename( $_FILES['txt_foto']['name']);
							if(move_uploaded_file($_FILES['txt_foto']['tmp_name'], $target_path))
							{
								$id= $_POST['txt_email'];
								$nombre = $_POST['txt_nombre'];
								$app_paterno = $_POST['txt_app_p'];
								$app_materno = $_POST['txt_app_m'];
								$sexo= $_POST['sexo'];
								$edad= $_POST['txt_edad'];
								@$fecha_nac= $_POST['txt_fech_nac'];
								$usuario=$_POST['txt_usuario'];
								$tel_oficina = $_POST['txt_tel_ofi'];
								$extension = $_POST['txt_ext'];
								$tel_mobil = $_POST['txt_tel_per'];
								$organismos = $_POST['txt_organismos'];
								$unid_respon = $_POST['txt_uni_respon'];
								$pregunta=$_POST['txt_pregunta_seguridad'];
								$respuesta=$_POST['txt_respuesta'];
								$password = $_POST['txt_psw'];
								
								$SQL = "INSERT INTO usuarios VALUES ('$id','$nombre','$app_paterno','$app_materno','$sexo','$edad','$fecha_nac','$target_path','$usuario','$tel_oficina','$extension','$tel_mobil','$organismos','$unid_respon','1','$pregunta','$respuesta','$password')";
								$row = $db->query($SQL);
								$SQL2 = "INSERT INTO privilegios VALUES (NOW(),'$organismos','$id','I',NOW(),1)";
								$row = $db->query($SQL2);
								
								include("ptfma_AltaUsuario.php");
							}
							else{
								echo "Ha ocurrido un error, trate de nuevo!";
							}
                   
                    BREAK;
            }
        }
		
		
		
					

?>