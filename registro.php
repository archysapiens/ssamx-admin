<?php

echo  "

<!DOCTYPE html>
<html>

<head>

    <meta charset=\"utf-8\">
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">

    <title>Nuevo Registro </title>

    <link href=\"css/bootstrap.min.css\" rel=\"stylesheet\">
    <link href=\"font-awesome/css/font-awesome.css\" rel=\"stylesheet\">

    <link href=\"css/animate.css\" rel=\"stylesheet\">
    <link href=\"css/style.css\" rel=\"stylesheet\">
	<script src='https://www.google.com/recaptcha/api.js'></script>
</head>

<body class=\"gray-bg\">

                <table align=\"center\" height=\"60\">
  <tr>
     <td width=\"420\" align=\"left\"><img src=\"images/logoSALUD_hoz.png\" width=\"289\" height=\"95\" /></td>
     <!--<td width=\"420\" align=\"left\">
     <img src=\"images/70Salud.jpg\" width=\"375\" height=\"91\" /></td>-->
     <!--<td width=\"683\" align=\"right\">
     <div id=\"dominio\">Recepción Art. 74</div>


     </td>  -->
     <td width=\"683\" align=\"right\">
             <div class=\"col-lg-10\">
                    <h2>Sistema de Recepción de Productos de Nómina</h2>
        </div>


     </td>
  </tr>
</table>



     <div class=\"passwordBox animated fadeInDown\">
        <div class=\"row\">

            <div class=\"col-md-12\">
                <div class=\"ibox-content\">

                    <h2 class=\"font-bold\">Agregar nuevo usuario</h2>
		</div>

                   

		<form action='valida_registro.php' method='POST>
		<div class='form-group'>
			<label>Nombre completo: </label>
			<input type='text' class='form-control' name='nombre'>
		</div>
		<div class='form-group'>
			<label>Apellido paterno: </label>
			<input type='text' class='form-control' name='app'>
		</div>
		<div class='form-group'>
			<label>Apellido materno: </label>
			<input type='text' class='form-control' name='apm'>
		</div>
		<div class='form-group'>
			<label>Direccion: </label>
			<input type='text' class='form-control' name='direccion'>
		</div>
		<div class='form-group'>
			<label>Telefono: </label>
			<input type='text' class='form-control' name='telefono'>
		</div>
		<div class='form-group'>
			<label>Email: </label>
			<input type='text' class='form-control' name='email'>
		</div>
		<div class='form-group'>
			<label>Password: </label>
			<input type='password' class='form-control' name='password'>
		</div>
		
		<div class='g-recaptcha' data-sitekey='6LcMNCATAAAAAKXuo_VpzgablnRTWvTHu3PhYAk_'></div>
		<br>
		
			<input type='submit' class='btn btn-primary'><br>
					
		</form>
		<br>
		

	</div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        <hr/>
        <div class=\"row\">
            <div class=\"col-md-6\">
                &nbsp;
            </div>
            <div class=\"col-md-6 text-right\">
               <small>&nbsp;</small>
            </div>
        </div>
    </div>



      <div id=\"footerEPN\" style=\"clear:both; margin-top: 12px;\">
            <div style=\"clear: both; width: 100%; border-top: 1px solid #dedede; margin-bottom: 1px;\"></div>
            <div style=\"border-top: 1px solid #dedede; border-bottom: 1px solid #dedede; font-family: 'Times New Roman', serif; font-size: 14px; color: #666666; text-align: center; padding: 14px 0px;\">SECRETAR&Iacute;A DE SALUD - ALGUNOS DERECHOS RESERVADOS &copy; 2012 - <a href=\"http://portal.salud.gob.mx/contenidos/inicio/politicas.html\" style=\"text-decoration: none; color: #808080;\">POL&Iacute;TICAS DE PRIVACIDAD</a></div>
            <div style=\"clear: both; width: 100%; border-top: 1px solid #dedede; margin-top: 1px;\"></div>

            <div style=\"clear:both; width: 100%;\">

              <div style=\"float: left; border-top: 1px solid #dedede; border-bottom: 1px solid #dedede; width: 336px; height:1px; margin-top: 38px;\"></div>
                <div align=\"right\"><img src=\"images/logoSALUD_hoz.png\" width=\"220\" height=\"72\" style=\"float:left; margin: 0px 24px;\" align=\"middle\" />
                </div>
                <div style=\"float: left; border-top: 1px solid #dedede; border-bottom: 1px solid #dedede; width: 336px; height:1px; margin-top: 38px;\"></div>
                <div style=\"clear: both; width: 100%;\"></div>
            </div>

            <div style=\"margin: 32px auto 42px auto; text-align: center; font-family: 'Times New Roman', serif; font-weight: lighter; font-size: 13px;\">
                <p style=\"color: #808080; line-height: 5px;\">Lieja No. 7, Col. Ju&aacuterez, Deleg. Cuauht&eacutemoc</p>
                <p style=\"color: #808080; line-height: 5px;\">Distrito Federal CP. 06600 </p>
            </div>
            <div style=\"clear: both; width: 100%;\"></div>
        </div>
</div>



</body>

</html>
";

?>
