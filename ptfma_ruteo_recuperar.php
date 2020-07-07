<?php
include "./general/DBC.php";
include "./general/generales.inc";
 include("class.phpmailer.php");

  $mail = new phpmailer();
  $mail->PluginDir = "";
  $mail->Mailer = "smtp";
  $mail->Host = "smtp.gmail.com";
  $mail->SMTPAuth = true;


$usuarios=$_POST['inputUsuariorecuperado'];

$db = new DbCnnx();    
$Usuariorecuperado = $db->quote($_POST['inputUsuariorecuperado']);
//$Passwd = $db->quote($_POST['inputPassword']);

$SQL ="SELECT * FROM usuarios WHERE id=". $Usuariorecuperado."";
$rows = $db->select($SQL);
$Messagerecuperar = "No hay un usuario con esa dirección de correo ";
$Messagerecuperar2 = "Se enviaron las credenciales de acceso";
include('conexion.php');
$sql="SELECT password  FROM usuarios where  id= $Usuariorecuperado ";  
$consulta=mysql_query($sql) or die (mysql_error());
$pass=mysql_result($consulta, 0, 'password');


if(!$rows)
	header("location: ptfma_recuperar_pwd.php?Message={$Messagerecuperar}");
else
{
	
	  //Nombre de usuario y password del correo origen
  $mail->Username = "all221410164@gmail.com"; 
  $mail->Password = "omardejesus";
  //Dirección de correo y el nombre que de la persona que envía el correo
  $mail->From = "all221410164@gmail.com";
  $mail->FromName = "Omar De Jesus Filomeno";
  
  $mail->Timeout=50;

  //Dirección de destino del correo
  
$mail->addAddress($usuarios);


  //Asignamos asunto y cuerpo del mensaje
  //El cuerpo del mensaje lo ponemos en formato html
  $mail->Subject = "Recuperacion de password";
;
  $mail->Body = "Esta es su contraseña olvidada ".$pass;
  $mail->AltBody = "Contraseña olvidada se recupero exitosamente";
  
  $exito = $mail->Send();  
  $intentos=1; 
  while ((!$exito) && ($intentos < 5)) {
	sleep(5);
     	$exito = $mail->Send();
     	$intentos=$intentos+1;		
   }		
   if(!$exito){
		header("location: ptfma_recuperar_pwd.php?Message=Problemas enviando correo electrónico!");
		
   }
   else{
   	header("location: index.php?Message=Se enviaron las credenciales de acceso!");
	echo "<br/>".$mail->ErrorInfo;
   } 

header("location: index.php?Message={$Messagerecuperar2}");
					
}// if(!$rows)


?>


