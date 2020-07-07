<html>
<head>
<META HTTP-EQUIV= "Refresh"CONTENT=\"1;URL=javascript:history.back() ">
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
</head>
<body>
<?php
include "../general/Mail/class.phpmailer.php";
include "../general/Mail/class.smtp.php";

$mail = new PHPMailer(true);
$NombreCompleto=@$_POST['txt_nombre']." ".@$_POST['txt_app_p']." ".@$_POST['txt_app_m'];
if(@$_POST['txt_email']!="")
{$address=@$_POST['txt_email'];}
$var_encode=base64_encode($_POST['txt_email']);
$link="ssa/ptma_opcd/activar_cuenta.php?var=$var_encode";
	$body = '
<html>
	<head>
	  <meta name="viewport" content="width=device-width" />
	  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
	  <title>SECRETARÍA DE SALUD  - Activación de Cuenta</title>    
	</head>
	<body style="background-color: #f6f6f6; -webkit-font-smoothing: antialiased;
	-webkit-text-size-adjust: none; width: 100% !important; height: 100%;
	line-height: 1.6;">
	<table style="background-color: #f6f6f6; width: 100%;">
	  <tr>
		<td></td>
		<td style="width: 100% !important; vertical-align: top;" width="600">
		  <div style="max-width: 600px; margin: 0 auto; display: block;
		  padding: 20px; padding: 10px !important;">
		  <table style="background: #fff; border: 1px solid #e9e9e9;
		  border-radius: 3px;" width="100%" cellpadding="0" cellspacing="0">
		  <tr>
			<td style="padding: 20px; vertical-align: top;">
			  <table  cellpadding="0" cellspacing="0">
				<tr>
				  <td style="font-size: 30px; color: #fff; font-weight: 500;
				  padding: 20px; text-align: right; border-radius: 3px 3px 0 0;
				  background-color:rgb(66, 160, 67); vertical-align: top;">
				  <img src="http://ensanut.insp.mx/images/logo_ssa.png" align="left" height="55" />
				  <span>SECRETARÍA DE SALUD</span>
				</td>
			  </tr>
			  <tr>
				<td style="padding: 0 0 20px; vertical-align: top;" >
				  <h2 style="
				  color: #676A6C; margin: 40px 0 0; line-height: 1.2;
				  font-weight: 600;font-size: 12px;text-transform: capitalize;">
				  Estimado (a): '.$NombreCompleto.'</h2>
				</td>
			  </tr>
			  <tr>
				<td style="padding: 0 0 20px; vertical-align: top;">
				  Hemos recibido la solicitud de activar cuenta para el 
				  sistema de SECRETAR&Iacute;A DE SALUD.
				</td>
			  </tr>                                
			  <tr>
				<td style="padding: 0 0 20px; vertical-align: top;">
				 Gracias por registrarte con nosotros. Para activar tu perfil presiona el siguiente 
				  botón &emsp;
				  <a href="'.$_SERVER['SERVER_NAME']."/".$link.'" 
				   style="text-decoration: none; color: #FFF; background:rgb(66, 160, 67);
				   border: solid rgb(66, 160, 67); border-width: 5px 10px; line-height: 2;
				   font-weight: bold; text-align: center; cursor: pointer;
				   display: inline-block; border-radius: 5px; text-transform: capitalize;">
				   Activar Cuenta
				 </a>
				 <br />
				 ó copia y pega la siguiente liga en el navegador:<br>
				 '."http://".$_SERVER['SERVER_NAME']."/".$link.'
				 
			   </td>
			 </tr>           
			<tr>
			  <td style="padding: 0 0 20px; vertical-align: top;">
				Si no solicitaste una nueva cuenta, puedes hacer caso 
				omiso de este mensaje de correo electrónico. Otra 
				persona puede haber escrito tu dirección de correo 
				electrónico por error. 
			  </td>
			</tr>                            
		  </table>                              
		</td>
	  </tr>
	</table>
	</div>
	</td>
	<td></td>
	</tr>
	</table>
	</body>
</html>
';
    $mail->IsSMTP();
    $mail->SMTPAuth = true;
    $mail->SMTPSecure = "ssl";
    $mail->Host = "smtp.gmail.com";
    $mail->Port = 465; 
	
$mail->Username = 'ecosheyss@gmail.com';
$mail->Password = 'Seguridad';

try {
 
$mail->SetFrom('ecosheyss@gmail.com', 'Sistema Secretaria de Salud');
@$nombre = $_POST['NombreCorreo'];
$mail->AddAddress($address, $nombre);

$mail->Subject    = "Activar Cuenta";

$mail->AltBody    = "";

$mail->MsgHTML($body);
  $mail->Send();
  echo '<script> alert("Revisar Correo para activar cuenta"); setTimeout("history.back(1)", 100); </script>';
} catch (phpmailerException $e) {
  echo $e->errorMessage();
} catch (Exception $e) {
  echo $e->getMessage();
}
?>
</body>
</html>
