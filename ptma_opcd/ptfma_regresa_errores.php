<?php
$TagEnvio="";
if(isset($_POST['TagEnvio']))
	$TagEnvio=$_POST['TagEnvio'];

$IdRemesa="";
if(isset($_POST['idremesa']))
	$IdRemesa=$_POST['idremesa'];

$IdArchivoPN="";
if(isset($_POST['idarchivopn']))
	$IdArchivoPN=$_POST['idarchivopn'];



echo  "
                    
                                <div class=\"modal-dialog\" style=\"width: 750px;    margin-top: 60px;\">
                                    <div class=\"modal-content animated flipInY\">

                                        <div class=\"modal-header\">
                                            <button type=\"button\" class=\"close\" data-dismiss=\"modal\"><span aria-hidden=\"true\">&times;</span><span class=\"sr-only\">Close</span></button>
                                            <h4 class=\"modal-title\">Tag Envio $TagEnvio Remesa $IdRemesa</h4>
                                            <small class=\"font-bold\">$IdArchivoPN Resumen de Productos de Nómina.</small>
                                        </div>
                                        <div class=\"modal-body\">



<!-- inicio de cuerpo -->

            <table id=\"tabla_errores\" tabindex=\"0\" cellspacing=\"0\" cellpadding=\"0\" border=\"0\" role=\"grid\" aria-multiselectable=\"false\" aria-labelledby=\"gbox_table_list_1\" class=\"ui-jqgrid-btable\" style=\"width: 935px;\">
            <tbody>

            </tbody>
            </table>


<!-- fin de cuerpo -->

                                        </div>
                                        <div class=\"modal-footer\">
                                            <button type=\"button\" class=\"btn btn-white\" data-dismiss=\"modal\">Cerrar</button>
                                            <button type=\"button\" class=\"btn btn-primary\">Imprimir</button>
                                        </div>
                                    </div>
                                </div>


	";

?>