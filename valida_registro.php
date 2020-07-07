<?php
include "./conexion.php";
include "./general/generales.inc";
  $nombre = $_REQUEST['nombre'];
  $app = $_REQUEST['app'];
  $apm = $_REQUEST['apm'];
  $direccion = $_REQUEST['direccion'];
  $telefono = $_REQUEST['telefono'];
  $email = $_REQUEST['email'];
  $password = $_REQUEST['password'];
  
  if(isset($_POST["g-recaptcha-response"]) && $_POST["g-recaptcha-response"])
  {
	  var_dump($_POST);
	  $secret = "6LcMNCATAAAAALH6CRY-KYEnjUnGe1RDpG3ueI5P";
	  $ip = $_SERVER ["REMOTE_ADOR"];
	  
	  $captcha = $_POST["g-recaptcha-response"];
	  
	  $result = file_get_contents("https://www.google.com/recaptcha/api/siteverify?secret=$secret&response=$captcha&remoteip=$ip");
	  echo "<br>";
	  var_dump($result);
	  
	  $array = Json_decode($result, TRUE);
	  echo "<br>";
	  if ($array["success"])
	  {
		  echo "Codigo Valido";
	  }
	  else{
		  echo "Eres spam";
	  }
  }

  include("email/class.phpmailer.php");
  $mail = new phpmailer();
  $mail->PluginDir = "";
  $mail->Mailer = "smtp";
  $mail->Host = "smtp.gmail.com";
  $mail->SMTPAuth = true;
/*  $sql="select id from usuarios where id='$email'";
	$msj= mysql_query($sql) or die (mysql_error());
	$mjs2= mysql_result($msj,0,'id');
	if ($mjs2 != $email){ */
  $consulta= "insert into usuarios(id,nombre,app_paterno,app_materno,tel_oficina,extension,tel_mobil,password) values('$email','$nombre', '$app', '$apm','$telefono','$telefono','$telefono','$password')";
 
  mysql_query ($consulta) or die (mysql_error());
  
  
  //Nombre de usuario y password del correo origen
  $mail->Username = "al221310409@gmail.com"; 
  $mail->Password = "moniflo12";
  //Dirección de correo y el nombre que de la persona que envía el correo
  $mail->From = "al221410771@gmail.com";
  $mail->FromName = "Zaira Cortez Najera";
  
  $mail->Timeout = 30;

  //Dirección de destino del correo
  $mail->AddAddress($email);

  //Asignamos asunto y cuerpo del mensaje
  //El cuerpo del mensaje lo ponemos en formato html
  $mail->Subject = "Registro Exitoso";
  $mail->Body = "<b>Hola $nombre, el regitro al sistema se dio de manera exitosa<br>
    Datos registrados:<br>
    Direccion: $direccion <br>
    Telefono: $telefono
    <br>
	Contraseña: $password<br>
    
    </b>";
  $mail->AltBody = "Registro de Usuario";
    
  $exito = $mail->Send();  
  $intentos=1; 
  while ((!$exito) && ($intentos < 5)) {
	sleep(5);
      echo "Enviado a: $email";
     	$exito = $mail->Send();
     	$intentos=$intentos+1;		
   }		
   if(!$exito){
	echo "Problemas al enviar el correo electrónico!";
 
	echo "<br/>".$mail->ErrorInfo;	
   }
   else{
	echo "Mensaje enviado correctamente!";
 


   }
	/*}
else{
	echo "El correo no existe en la base de datos";
}*/	
?>