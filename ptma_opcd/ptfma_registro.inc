<?php

/*********************************************************************
 * 
 * Funcion : fncBuildRow1
 * Objetivo: Construir tabs
 *
 **********************************************************************/

function fncBuildRow1(){

	return "
			<div class=\"wrapper wrapper-content animated bounceIn\" id=\"main_page\">
				<div class=\"row\">
					<div class=\"col-lg-6 col-md-offset-3\">
						<div class=\"ibox float-e-margins\">
							<div class=\"ibox-title\">
								<h3>Agregar Nuevo Usuario <span class=\"glyphicon glyphicon-user\"></span></h3>
							</div>
							<div class=\"ibox-content\">
								<div class=\"board\">
									<div class=\"board-inner\">
										<div class=\"liner\"></div>
										<ul class=\"nav nav-tabs\" id=\"myTab\" role=\"tablist\">
											<li role=\"presentation\" class=\"active\">
												<a href=\"#personal\" data-toggle=\"tab\" aria-controls=\"personal\" role=\"tab\" title=\"Personales\">
													<span class=\"round-tabs one\">
													<i class=\"glyphicon glyphicon-user\"></i>
													</span> 
												</a>
											</li>
											<li role=\"presentation\" class=\"disabled\">
												<a href=\"#contacto\" data-toggle=\"tab\" aria-controls=\"contacto\" role=\"tab\" title=\"Contacto\">
													<span class=\"round-tabs two\">
													<i class=\"glyphicon glyphicon-phone-alt\"></i>
													</span> 
												</a>
											</li>
											<li role=\"presentation\" class=\"disabled\">
												<a href=\"#organismo\" data-toggle=\"tab\" aria-controls=\"organismo\" role=\"tab\" title=\"Organismo\">
													<span class=\"round-tabs three\">
													<i class=\"glyphicon glyphicon-th-list\"></i>
													</span> 
												</a>
											</li>
											 <li role=\"presentation\" class=\"disabled\">
												<a href=\"#credencial\" data-toggle=\"tab\" aria-controls=\"credencial\" role=\"tab\" title=\"Credenciales\">
													<span class=\"round-tabs four\">
													<i class=\"glyphicon glyphicon-pencil\"></i>
													</span> 
												</a>
											 </li>
											
										</ul>
									</div>
									<form role=\"form\" id=\"FormUser\" action=\"\" method=\"post\" enctype=\"multipart/form-data\">
										<div class=\"tab-content\">
											<div class=\"tab-pane fade in active\" role=\"tabpanel\" id=\"personal\">
												<h3 class=\"head text-center\"></h3><br>
												<p class=\"text-danger pull-left\">(*) Campos obligatorios.</p><br><br>
												<div class=\"col-sm-5 col-sm-offset-1 b-r\">
													<div class=\"form-group\"><label>* Nombre</label> <input type=\"text\" placeholder=\"Pedro\" name=\"txt_nombre\" id=\"txt_nombre\" class=\"form-control text-capitalize\" required autofocus></div>
													<div class=\"form-group\"><label>* Apellido Paterno</label> <input type=\"text\" placeholder=\"Perez\" name=\"txt_app_p\" id=\"txt_app_p\" class=\"form-control text-capitalize\" required></div>
													<div class=\"form-group\"><label>* Apellido Materno</label> <input type=\"text\" placeholder=\"Perez\" name=\"txt_app_m\" id=\"txt_app_m\" class=\"form-control text-capitalize\" required></div>
													<div class=\"form-group\"><label>* Sexo</label><div class=\"i-checks\"><label><input type=\"radio\" name=\"sexo\" value=\"Masculino\" class=\"form-control\" checked> <i></i> Masculino </label>&nbsp; &nbsp; <label><input type=\"radio\" name=\"sexo\" value=\"Femenino\" class=\"form-control\"> <i></i> Femenino</label></div></div>
													<div class=\"form-group\"><label>Edad</label> 
													<div class=\"input-group spinner\">
														<input type=\"text\" value=\"18\" min=\"1\" max=\"100\" name=\"txt_edad\" class=\"form-control\">
														<div class=\"input-group-btn-vertical\">
														  <button class=\"btn btn-default\" type=\"button\"><i class=\"fa fa-caret-up\"></i></button>
														  <button class=\"btn btn-default\" type=\"button\"><i class=\"fa fa-caret-down\"></i></button>
														</div>
													</div></div>
													<div class=\"form-group\" id=\"data_1\">
														<label >Fecha de Nacimiento</label>
														<div class=\"input-group date\">
															<span class=\"input-group-addon\"><i class=\"fa fa-calendar\"></i></span><input type=\"text\" class=\"form-control\" name=\"txt_fech_nac\" placeholder=\"08/16/2000\" value=\"08/16/2000\" >
														</div>
													</div>
												</div>
												<div class=\"col-sm-5\">
													<br>
													<div class=\"form-group\"><label>* Foto de Perfil</label> 
														<div class=\"input-group image-preview\">
															<input type=\"text\" class=\"form-control image-preview-filename\" disabled=\"disabled\" PLACEHOLDER=\"Elige Imágen\">
															<span class=\"input-group-btn\">
																<button type=\"button\" class=\"btn btn-default image-preview-clear\" style=\"display:none;\">
																	<span class=\"glyphicon glyphicon-remove\"></span> Limpiar
																</button>
																<div class=\"btn btn-default image-preview-input\">
																	<span class=\"glyphicon glyphicon-folder-open\"></span>
																	<span class=\"image-preview-input-title\">Buscar</span>
																	<input type=\"file\" accept=\"image/png, image/jpeg, image/gif\" name=\"txt_foto\" id=\"txt_foto\" class=\"form-control img\" required/>
																</div>
															</span>
														</div>
													</div>
													<div class=\"form-group\"><label>* Usuario:</label> <input type=\"text\" placeholder=\"Usuario\" name=\"txt_usuario\" id=\"txt_usuario\" class=\"form-control\" required></div>
													<div class=\"form-group\"><label>* Contraseña:</label> <input type=\"password\" placeholder=\"********\" name=\"txt_psw\" id=\"txt_psw\" class=\"form-control\" required></div>
													<div style=\"margin-top:80px;\" class=\"text-center\">
														<ul class=\"list-inline pull-right\">
															<li><button class=\"btn btn-primary next-step\" id=\"primero\" type=\"submit\"><i class=\"glyphicon glyphicon-saved\"></i>&nbsp;&nbsp;<span class=\"bold\">Guardar y continuar</span></button></li>
														</ul>
													</div>
												</div>
											</div>
											<div class=\"tab-pane fade\"  role=\"tabpanel\" id=\"contacto\">
												<h3 class=\"head text-center\"></h3><br>
												<p class=\"text-danger pull-left\">(*) Campos obligatorios.</p><br><br>
												<div class=\"col-sm-7 col-sm-offset-2\">
													<div class=\"form-group\"><label>* Correo </label> <input type=\"email\" placeholder=\"ejemplo@ejemplo.com\" name=\"txt_email\" id=\"txt_email\" class=\"form-control\" required></div>
													<div class=\"form-group\"><label> Telefono de oficina</label><input type=\"text\" name=\"txt_tel_ofi\" class=\"form-control\" data-mask=\"(999) 999-9999\" placeholder=\"(###) ###-####\"></div>
													<div class=\"form-group\"><label> Extension</label><input type=\"text\" name=\"txt_ext\" class=\"form-control\" data-mask=\"9999\" placeholder=\"###\" ></div>
													<div class=\"form-group\"><label> Telefono Personal</label><input type=\"text\" name=\"txt_tel_per\" class=\"form-control\" data-mask=\"(999) 999-9999\" placeholder=\"(###) ###-####\"></div>	 
													<div style=\"margin-top:40px;\" class=\"text-center\">
														<ul class=\"list-inline text-center\">
															<li><button class=\"btn btn-default prev-step\"  type=\"button\"><i class=\"glyphicon glyphicon-chevron-left\"></i>&nbsp;&nbsp;<span class=\"bold\">Anterior</span></button></li>
															<li><button class=\"btn btn-primary next-step-contacto\"  type=\"submit\"><i class=\"glyphicon glyphicon-saved\"></i>&nbsp;&nbsp;<span class=\"bold\">Guardar y continuar</span></button></li>
														</ul>
													</div>
												</div>
											</div>
											<div class=\"tab-pane fade\" role=\"tabpanel\" id=\"organismo\">
												<h3 class=\"head text-center\"></h3><br>
												<p class=\"text-danger pull-left\">(*) Campos obligatorios.</p><br><br>
												<div class=\"col-sm-7 col-sm-offset-2\">
													<div class=\"form-group\"><label>* Organismos:  </label>
														<select name=\"txt_organismos\" id=\"txt_organismos\" class=\"select2_demo_3 form-control\" style=\"width:330px;\" required>
															<option></option>
															<option value=\"01\">Aguascalientes</option> 
															<option value=\"02\">Baja California</option> 
															<option value=\"03\">Baja California Sur</option>
															<option value=\"04\">Campeche</option> 
															<option value=\"05\">Coahuila</option> 
															<option value=\"06\">Colima</option> 
														</select>
													</div>
													<div class=\"form-group\"><label>* Unidad Responsable: </label>
														<select name=\"txt_uni_respon\" id=\"txt_uni_respon\" class=\"select2_demo_3 form-control\" style=\"width:330px;\" required>
															<option></option>
															<option value=\"Noe\">Noe</option> 
															<option value=\"Juan\">Juan</option> 
															<option value=\"Raul\">Raul</option>
															<option value=\"Maria\">Maria</option> 
															<option value=\"Jaime\">Jaime</option> 
															<option value=\"Israel\">Israel</option>
															<option value=\"Sergio\">Sergio</option> 
															<option value=\"Elia\">Elia</option> 
															<option value=\"Victor\">Victor</option> 
															<option value=\"Beatriz\">Beatriz</option> 
															<option value=\"Efrain\">Efrain</option> 
															<option value=\"Edgar\">Edgar</option> 
														</select>
													</div>
													<div style=\"margin-top:40px;\" class=\"text-center\">
														<ul class=\"list-inline text-center\">
															<li><button class=\"btn btn-default prev-step\"  type=\"button\"><i class=\"glyphicon glyphicon-chevron-left\"></i>&nbsp;&nbsp;<span class=\"bold\">Anterior</span></button></li>
															<li><button class=\"btn btn-primary next-step-organismo\"  type=\"submit\"><i class=\"glyphicon glyphicon-saved\"></i>&nbsp;&nbsp;<span class=\"bold\">Guardar y continuar</span></button></li>
														</ul>
													</div>
												</div>
											</div>
											<div class=\"tab-pane fade\" role=\"tabpanel\" id=\"credencial\">
												<h3 class=\"head text-center\"></h3><br>
												<p class=\"text-danger pull-left\">(*) Campos obligatorios.</p><br><br>
												<div class=\"col-sm-7 col-sm-offset-2\">
													<div class=\"form-group\"><label >* Credenciales</label>
														<div class=\"col-sm-10\">
															<div class=\"i-checks\"><label> <input type=\"checkbox\" value=\"10\" name=\"txt_creden[]\" checked> <i></i> + Producto de Nomina </label></div>
															<div class=\"i-checks\"><label> <input type=\"checkbox\"  value=\"2\" name=\"txt_creden[]\"> <i></i> + Articulo 74 </label></div>
															<div class=\"i-checks\"><label> <input type=\"checkbox\" value=\"8\" name=\"txt_creden[]\"> <i></i> + Articulo 74 Frac II </label></div>
															<div class=\"i-checks\"><label> <input type=\"checkbox\" value=\"9\" name=\"txt_creden[]\"> <i></i> + Articulo 74 Frac III </label></div>														
														</div>
													</div><br><br><br><br><br>
													<div class=\"form-group\"><label>* Pregunta de Seguridad </label>
														<select name=\"txt_pregunta_seguridad\" class=\"select2_demo_3 form-control\" style=\"width:330px;\" required>
															<option></option>
															<option value=\"1\">Selecciona una pregunta</option>
															<option value=\"¿Nombre de su canción preferida?\">¿Nombre de su canción preferida?</option>
															<option value=\"¿Nombre de su pelicula preferida?\">¿Nombre de su pelicula preferida?</option>
															<option value=\"¿Nombre de la ciudad que deceas conocer?\">¿Nombre de la ciudad que deceas conocer?</option>
															<option value=\"¿Nombre de su libro preferido?\">¿Nombre de su libro preferido?</option>
															<option value=\"¿Nombre de su restaurante favorito?\">¿Nombre de su restaurante favorito?</option>
															<option value=\"¿Nombre de su autor preferido?\">¿Nombre de su autor preferido?</option>
															<option value=\"¿Nombre de un amigo entrañable?\">¿Nombre de un amigo entrañable?</option>
															<option value=\"¿Nombre de su juego de la infancia preferido?\">¿Nombre de su juego de la infancia preferido?</option>
															<option value=\"¿Una fecha a recordar?\">¿Una fecha a recordar?</option>
															<option value=\"¿Nombre de su lugar favorito?\">¿Nombre de su lugar favorito?</option>
															<option value=\"¿Nombre de su color favorito?\">¿Nombre de su color favorito?</option>
														</select>
													</div>
													<div class=\"form-group\"><label>* Respuesta </label> <input type=\"text\" placeholder=\"Escribe tu respuesta\" name=\"txt_respuesta\" class=\"form-control\" required></div>										
													<div style=\"margin-top:40px;\" class=\"text-center\">
														<ul class=\"list-inline text-center\">
															<li><button class=\"btn btn-default prev-step\"  type=\"button\"><i class=\"glyphicon glyphicon-chevron-left\"></i>&nbsp;&nbsp;<span class=\"bold\">Anterior</span></button></li>
															<li><button class=\"btn btn-primary\" name=\"submitConfirmarAlta\" id=\"submitConfirmarAlta\" value=\"confirmar\" type=\"submit\"><i class=\"glyphicon glyphicon-floppy-saved\"></i>&nbsp;&nbsp;<span class=\"bold\">Guardar</span></button></li>
														</ul>
													</div>
												</div>
											</div>
											<div class=\"clearfix\"></div>
										</div>
									</form>
								</div>
							</div>
						</div>
					</div>
				</div>
			</div>
    	";
}

/*********************************************************************
 * 
 * Funcion : fncBuildJS
 * Objetivo: Footer
 *
 **********************************************************************/

function fncBuildJS()
{

return "
   <!-- Mainly scripts -->
    <script src=\"../js/jquery-2.1.1.js\"></script>
    <script src=\"../js/bootstrap.min.js\"></script>
    <script src=\"../js/bootstrapValidator.min.js\"></script>
    <script src=\"../js/plugins/metisMenu/jquery.metisMenu.js\"></script>
    <script src=\"../js/plugins/slimscroll/jquery.slimscroll.min.js\"></script>

    <!-- Flot -->
    <script src=\"../js/plugins/flot/jquery.flot.js\"></script>
    <script src=\"../js/plugins/flot/jquery.flot.tooltip.min.js\"></script>
    <script src=\"../js/plugins/flot/jquery.flot.spline.js\"></script>
    <script src=\"../js/plugins/flot/jquery.flot.resize.js\"></script>
    <script src=\"../js/plugins/flot/jquery.flot.pie.js\"></script>

    <!-- Peity  -->
    <script src=\"../js/plugins/peity/jquery.peity.min.js\"></script>
    <script src=\"../js/demo/peity-demo.js\"></script>

    <!-- Custom and plugin javascript  -->
    <script src=\"../js/inspinia.js\"></script>
    <script src=\"../js/plugins/pace/pace.min.js\"></script>

    <!-- GITTER -->
    <script src=\"../js/plugins/gritter/jquery.gritter.min.js\"></script>

    <!-- Sparkline -->
    <script src=\"../js/plugins/sparkline/jquery.sparkline.min.js\"></script>
    

    <!-- Sparkline demo data  -->
    <script src=\"../js/demo/sparkline-demo.js\"></script>

    <!-- ChartJS-->
    <script src=\"../js/plugins/chartJs/Chart.min.js\"></script>

    <!-- Toastr -->
    <script src=\"../js/plugins/toastr/toastr.min.js\"></script>
	
	<!--Datepicker -->
	<script src=\"../js/plugins/datapicker/bootstrap-datepicker.js\"></script>
    
	 <!-- iCheck -->
    <script src=\"../js/plugins/iCheck/icheck.min.js\"></script>
 
	
	<!-- Select2 -->
    <script src=\"../js/plugins/select2/select2.full.min.js\"></script>
	
	
    <script src=\"../js/tabs.js\"></script>

	<!-- DROPZONE -->
    <script src=\"../js/plugins/dropzone/dropzone.js\"></script>
	
	  <!-- Input Mask-->
    <script src=\"../js/plugins/jasny/jasny-bootstrap.min.js\"></script>
	 
	<script>
			$(document).ready(function () {
				$('#FormUser').bootstrapValidator({
					button: {
						selector: '#primero',
						disabled: 'disabled'
					},
					feedbackIcons: {
						valid: 'glyphicon glyphicon-ok',
						invalid: 'glyphicon glyphicon-remove',
						validating: 'glyphicon glyphicon-refresh'
					},
					fields: {
						txt_nombre: {
							validators: {
								notEmpty: {
									message: ' '
								},
								regexp: {
									regexp: /^[a-zA-Z\s]+$/,
									message: ' '
								}
							}
						},
						txt_app_p: {
							validators: {
								notEmpty: {
									message: ' '
								},
								regexp: {
									regexp: /^[a-zA-Z\s]+$/,
									message: ' '
								}
							}
						},
						txt_app_m: {
							validators: {
								notEmpty: {
									message: ' '
								},
								regexp: {
									regexp: /^[a-zA-Z\s]+$/,
									message: ' '
								}
							}
						},
						txt_usuario: {
							validators: {
								notEmpty: {
									message: ' '
								},
								regexp: {
									regexp: /^[a-zA-Z0-9\s]+$/,
									message: ' '
								}
							}
						},
						txt_psw: {
							validators: {
								notEmpty: {
									message: ' '
								}
							}
						},
						txt_foto: {
							validators: {
								notEmpty: {
									message: ' '
								}
							}
						},
						txt_email: {
							validators: {
								notEmpty: {
									message: ' '
								},
								emailAddress: {
									message: ' '
								}
							}
						},
						txt_organismos: {
							validators: {
								notEmpty: {
									message: ' '
								}
							}
						},
						txt_uni_respon: {
							validators: {
								notEmpty: {
									message: ' '
								}
							}
						},
						txt_pregunta_seguridad: {
							validators: {
								notEmpty: {
									message: ' '
								}
							}
						},
						txt_respuesta: {
							validators: {
								notEmpty: {
									message: ' '
								},
								regexp: {
									regexp: /^[a-zA-Z0-9\s]+$/,
									message: ' '
								}
							}
						}
					}
				});
                $('.i-checks').iCheck({
                    checkboxClass: 'icheckbox_square-green',
                    radioClass: 'iradio_square-green',
                });
            });
			$(\".select2_demo_3\").select2({
                placeholder: \"Seleccionar opción\",
                allowClear: true
            });
			$(function(){

				$('.spinner .btn:first-of-type').on('click', function() {
				  var btn = $(this);
				  var input = btn.closest('.spinner').find('input');
				  if (input.attr('max') == undefined || parseInt(input.val()) < parseInt(input.attr('max'))) {    
					input.val(parseInt(input.val(), 10) + 1);
				  } else {
					btn.next(\"disabled\", true);
				  }
				});
				$('.spinner .btn:last-of-type').on('click', function() {
				  var btn = $(this);
				  var input = btn.closest('.spinner').find('input');
				  if (input.attr('min') == undefined || parseInt(input.val()) > parseInt(input.attr('min'))) {    
					input.val(parseInt(input.val(), 10) - 1);
				  } else {
					btn.prev(\"disabled\", true);
				  }
				});

			})
        </script>
	<script>
		$(document).ready(function(){
			$('#data_1 .input-group.date').datepicker({
                todayBtn: \"linked\",
                keyboardNavigation: false,
                forceParse: false,
                calendarWeeks: true,
                autoclose: true
            });
		});
		$(document).on('click', '#close-preview', function(){ 
		$('.image-preview').popover('hide');
		// Hover befor close the preview
		$('.image-preview').hover(
			function () {
			   $('.image-preview').popover('show');
			}, 
			 function () {
			   $('.image-preview').popover('hide');
			}
		);    
	});

	$(function() {
		// Create the close button
		var closebtn = $('<button/>', {
			type:\"button\",
			text: 'x',
			id: 'close-preview',
			style: 'font-size: initial;',
		});
		closebtn.attr(\"class\",\"close pull-right\");
		// Set the popover default content
		$('.image-preview').popover({
			trigger:'manual',
			html:true,
			title: \"<strong>Vista</strong>\"+$(closebtn)[0].outerHTML,
			content: \"No hay imágen\",
			placement:'bottom'
		});
		// Clear event
		$('.image-preview-clear').click(function(){
			$('.image-preview').attr(\"data-content\",\"\").popover('hide');
			$('.image-preview-filename').val(\"\");
			$('.image-preview-clear').hide();
			$('.image-preview-input input:file').val(\"\");
			$(\".image-preview-input-title\").text(\"Buscar\"); 
		}); 
		// Create the preview image
		$(\".image-preview-input input:file\").change(function (){     
			var img = $('<img/>', {
				id: 'dynamic',
				width:200,
				height:150
			});      
			var file = this.files[0];
			var reader = new FileReader();
			// Set preview image into the popover data-content
			reader.onload = function (e) {
				$(\".image-preview-input-title\").text(\"Cambiar\");
				$(\".image-preview-clear\").show();
				$(\".image-preview-filename\").val(file.name);            
				img.attr('src', e.target.result);
				$(\".image-preview\").attr(\"data-content\",$(img)[0].outerHTML).popover(\"show\");
			}        
			reader.readAsDataURL(file);
		});  
	});
	 </script>
	 </html>

	";

} // fin de fncBuildJS


function fncBuildHead()
{
return " 	
<!DOCTYPE html>
<html>
	<head>
		<meta charset=\"utf-8\">
		<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">

		<title>Secretaria de Salud</title>

		<link href=\"../css/bootstrap.min.css\" rel=\"stylesheet\">
		<link href=\"../font-awesome/css/font-awesome.css\" rel=\"stylesheet\">

		<!-- Toastr style -->
		<link href=\"../css/plugins/toastr/toastr.min.css\" rel=\"stylesheet\">

		<!-- Gritter -->
		<link href=\"../js/plugins/gritter/jquery.gritter.css\" rel=\"stylesheet\">

		<!-- Data picker -->
		<link href=\"../css/plugins/datapicker/datepicker3.css\" rel=\"stylesheet\">
		<link href=\"../css/plugins/iCheck/custom.css\" rel=\"stylesheet\">
		
		<link href=\"../css/plugins/select2/select2.min.css\" rel=\"stylesheet\">
		
		<link href=\"../css/input-foto.css\" rel=\"stylesheet\">
		<link href=\"../css/animate.css\" rel=\"stylesheet\">
		<link href=\"../css/style.css\" rel=\"stylesheet\">            

		<link href=\"../css/plugins/dropzone/basic.css\" rel=\"stylesheet\">
		<link href=\"../css/plugins/dropzone/dropzone.css\" rel=\"stylesheet\">
		<style type=\"text/css\">
			#FormUser .form-control-feedback
			 {
				right: -30px;
			}
		</style>
	</head>";
} // fin de fncBuildHead


function fncBuildBody()
{ 
	$Row1= fncBuildRow1();

	return "
			<body class=\"gray-bg\">
                <table align=\"center\" height=\"60\">
				  <tr>
					 <td width=\"420\" align=\"left\"><img src=\"../images/logoSALUD_hoz.png\" width=\"289\" height=\"95\" /></td>
					 <!--<td width=\"420\" align=\"left\">
					 <img src=\"../images/70Salud.jpg\" width=\"375\" height=\"91\" /></td>-->
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
					$Row1
				<div id=\"footerEPN\" style=\"clear:both; margin-top: 12px;\">
					<div style=\"clear: both; width: 100%; border-top: 1px solid #dedede; margin-bottom: 1px;\"></div>
					<div style=\"border-top: 1px solid #dedede; border-bottom: 1px solid #dedede; font-family: 'Times New Roman', serif; font-size: 14px; color: #666666; text-align: center; padding: 14px 0px;\">SECRETAR&Iacute;A DE SALUD - ALGUNOS DERECHOS RESERVADOS &copy; 2012 - <a href=\"http://portal.salud.gob.mx/contenidos/inicio/politicas.html\" style=\"text-decoration: none; color: #808080;\">POL&Iacute;TICAS DE PRIVACIDAD</a></div>
					<div style=\"clear: both; width: 100%; border-top: 1px solid #dedede; margin-top: 1px;\"></div>
					<div style=\"clear:both; width: 100%;\">
					  <div style=\"float: left; border-top: 1px solid #dedede; border-bottom: 1px solid #dedede; width: 336px; height:1px; margin-top: 38px;\"></div>
						<div align=\"right\"><img src=\"../images/logoSALUD_hoz.png\" width=\"220\" height=\"72\" style=\"float:left; margin: 0px 24px;\" align=\"middle\" />
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
			</body>";

} // fin de fncBuildBody



?>