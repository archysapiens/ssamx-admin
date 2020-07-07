<?php

/************************************************
 * 
 * Funcion : obtenResultadosValidacion
 * Objetivo: Elaborar la presentacion de 
 *           resultados obtenidos despues del 
 *           proceso de validacion 
 * 
*************************************************/

function obtenResultadosValidacion($TipoNomina, $Estatus,$ArrArchivos, $ArrRpteValidacion, 
    $ArchivoErr, $NumRegAna)
{
date_default_timezone_set('America/Mexico_City');
$FechaProceso = date("d-m-Y");
$HoraProceso = date("H:i:s");
$Icono = "<i class=\"fa fa-warning fa-5x\" style=\"color:#F00404\"></i>";

$Estat = "<span class=\"label label-primary\" 
            style=\"background-color: #F00404;\">Error</span>

                        ";

$Archivos ="<dd> archivo1.zip </dd><dd> archivo1.zip </dd>";

$BtonSubir=" <div style=\" text-align:center;vertical-align:middle\">
            <button class=\"btn btn-warning btn-lg \" type=\"button\">
                <i class=\"fa fa-upload\">
                </i>&nbsp;&nbsp;
            <span class=\"bold\">Subir</span></button>
            </div>
                ";

$ReporteAnalisis =    "
                            <div class=\"row alert alert-info\">
                                <div class=\"col-xs-4\">
                                    <i class=\"fa fa-files-o fa-3x\" ></i>
                                </div>
                                <div class=\"col-xs-8 text-right\">
                                    Se recibieron 2 archivos de Nómina. 
                                </div>
                            </div>


                            <div class=\"row alert alert-success\">
                                <div class=\"col-xs-4\">
                                    <i class=\"fa fa-gears fa-3x\" ></i>
                                </div>
                                <div class=\"col-xs-8 text-right\">
                                    Se recibieron 2 archivos de Nómina. 
                                </div>
                            </div>

                            <div class=\"row alert alert-danger\">
                                <div class=\"col-xs-4\">
                                    <i class=\"fa fa-times-circle fa-3x\" ></i>
                                </div>
                                <div class=\"col-xs-8 text-right\">
                                    Se detectaron $NumRegAna <a href=\"$ArchivoErr\" download> Errores.</a> 
                                </div>
                            </div>
                      ";


if ($Estatus == EXITO)
{
    $Icono = "<i class=\"fa fa-check-circle-o fa-5x\" style=\"color:#1ab394\"></i>";

    $Estat = "<span class=\"label label-primary\" 
            style=\"background-color: #1ab394;\">Correcto</span>";


    $ReporteAnalisis = "
                            <div class=\"row alert alert-info\">
                                <div class=\"col-xs-4\">
                                    <i class=\"fa fa-files-o fa-3x\" ></i>
                                </div>
                                <div class=\"col-xs-8 text-right\">
                                    Se recibieron 2 archivos de Nómina. 
                                </div>
                            </div>


                            <div class=\"row alert alert-success\">
                                <div class=\"col-xs-4\">
                                    <i class=\"fa fa-gears fa-3x\" ></i>
                                </div>
                                <div class=\"col-xs-8 text-right\">
                                    Se recibieron 2 archivos de Nómina. 
                                </div>
                            </div>

                        ";

     $BtonSubir = "";                   

}    
/**
$Icono="";
$Archivos="";
$Estat ="";
$ReporteAnalisis="";
$BtonSubir="";                   
**/
return "
        <div class=\"row\" >
            <div class=\"col-lg-12\">
                <div class=\"ibox float-e-margins\">
                    <div class=\"ibox-title\">
                        <h5>Resultado de Verificación de Productos de Nómina</h5>
                        <div class=\"ibox-tools\">
                            
                        </div>
                </div>
                <div class=\"ibox-content\">

                    <div class=\"row\">

                    <div class=\"col-sm-5 b-r\" style=\"background-color:#f5f5f5\">

                        <div style=\"text-align:center;vertical-align:middle;\">

                        $Icono
                        
                        
                        </div>

                        <br>
                        
                            <dl class=\"dl-horizontal\">
                                    <dt>Entidad:</dt> <dd><h3>Estado de México</h3></dd>
                                    <dt>Fecha Validacion:</dt> <dd>  $FechaProceso</dd>
                                    <dt>Hora:</dt> <dd> $HoraProceso </dd>
                                    <dt>Estatus:</dt> <dd>
                                                    $Estat </dd>
                                    
                                    <dt>Archivos Analizados:</dt> $Archivos

                            </dl>
                        
                        
                            $BtonSubir

                    </div>
                <div class=\"col-sm-7\" id=\"zona-de-resultados-val\">
                    <div class=\"ibox-content\">
                        $ReporteAnalisis

                    </div>     
                </div>         
                     ";


}// fin de obtenResultadosValidacion($TipoNomina)


function fncBuildRow1(){

$ArrArchivo = "archivo1.zip";

$ArrResultados = "2 Archivos Analizados";

                      

$Resultados ="" ; obtenResultadosValidacion(416,0,$ArrArchivo,$ArrResultados,"archivo1.txt",0);


	return "
    <div class=\"row wrapper border-bottom white-bg page-heading\">
                <div class=\"col-lg-10\">
                    
                    <ol class=\"breadcrumb\">
                        <li>
                            <a href=\"#\">Quincena 6 </a>
                        </li>
                        <li>
                            <a href=\"#\">Estado de México</a>
                        </li>
                        <li class=\"active\">
                            <strong>Recepción de Productos </strong>
                        </li>
                    </ol>
                </div>
            </div>

        <div class=\"wrapper wrapper-content animated fadeInRight\" id=\"main_page\">
            <div class=\"row\">

            <div class=\"col-lg-12\" id=\"x00\">
                <div class=\"ibox float-e-margins\">
                    <div class=\"ibox-title animated bounceIn\">

                        <h5>
                            <i class=\"fa fa-hospital-o fa-2x\" style=\"color: #1ab394;\"></i>
                            Integración de Productos de Nómina X00
                        </h5>
                        <div class=\"ibox-tools\">
                            <a class=\"collapse-link\">
                                <i class=\"fa fa-chevron-up\"></i>
                            </a>
                            <a class=\"dropdown-toggle\" data-toggle=\"dropdown\" href=\"#\">
                                <i class=\"fa fa-wrench\"></i>
                            </a>
                            <ul class=\"dropdown-menu dropdown-user\">
                                <li><a href=\"#\">Config option 1</a>
                                </li>
                                <li><a href=\"#\">Config option 2</a>
                                </li>
                            </ul>
                            
                        </div>
                    </div>
                    <div class=\"ibox-content animated bounceIn\" id=\"nomina-x00\">

                        <div class=\"row\" style =\" text-align:center;vertical-align:middle\">
                            <div class=\"col-sm-5 b-r\">

                            <br><br><br>
                            <i class=\"fa fa-cloud-upload fa-5x\"></i>

                                <h3 class=\"m-t-none m-b\">Área Central,Órganos  Descentralizados, Organismos Públicos  Descentralizados,Honorarios</h3>
                                

                                <form role=\"form\">
                                    <div class=\"form-group\">
                                        <label>Bases de Datos Nomina</label> 
                                        <div id=\"resumen_carga\">
                                        </div>

                                    </div>
                                </form>
                            </div>

                            <div class=\"col-sm-7\" id=\"zona-de-carga\">
                            <form id=\"my-awesome-dropzone\" class=\"dropzone \" 
                                        action=\"pfma_validacion_archivos.php\">
                                    <p>Arrastre los archivos o solo haga click</p>
                                <div class=\"dropzone-previews\">
                                </div>

                            </form>   
                              <button id=\"enviar\" type\"button\"
                               class=\"btn btn-primary pull-right\">
                                  Validar</button>&nbsp;&nbsp;

                               <button id=\"clear-dropzone\" type\"button\" class=\"btn btn-primary pull-right\">
                                  Limpiar</button>   

                            
                            </div> <!-- fin de zona-de-carga -->

                        </div> <!-- fin de row -->

                    </div> <!-- fin de ibox-content x00 -->

                </div> <!-- fin de float-e-margins -->

            </div>


<!-- Nomina 416 -->

            <div class=\"col-lg-12\" id=\"x00\">
                <div class=\"ibox float-e-margins\">
                    <div class=\"ibox-title animated bounceIn\">

                        
                        <h5>
                            <i class=\"fa fa-user-md fa-2x\" style=\"color: #1ab394;\"></i>
                                 Integración de Productos de Nómina 416 
                        </h5>
                        
                        <div class=\"ibox-tools\">
                            <a class=\"collapse-link\">
                                <i class=\"fa fa-chevron-up\"></i>
                            </a>
                            <a class=\"dropdown-toggle\" data-toggle=\"dropdown\" href=\"#\">
                                <i class=\"fa fa-wrench\"></i>
                            </a>
                            <ul class=\"dropdown-menu dropdown-user\">
                                <li><a href=\"#\">Config option 1</a>
                                </li>
                                <li><a href=\"#\">Config option 2</a>
                                </li>
                            </ul>
                            
                        </div>
                    </div>
                    <div class=\"ibox-content  animated bounceIn\" id=\"nomina-416\">

                        <div class=\"row\">
                            <div class=\"col-sm-4 b-r\">
                                <h3 class=\"m-t-none m-b\">Área Central</h3>
                                <h3 class=\"m-t-none m-b\">Órganos  Descentralizados</h3>
                                <h3 class=\"m-t-none m-b\">Organismos Públicos  Descentralizados</h3>
                                <h3 class=\"m-t-none m-b\">Honorarios</h3>
                                

                                <form role=\"form\">
                                    <div class=\"form-group\">
                                        <label>Bases de Datos Nomina</label> 
                                        <div id=\"resumen_carga\">
                                        </div>

                                    </div>
                                </form>
                            </div>

                            <div class=\"col-sm-8\" id=\"zona-de-carga\">
                            <form id=\"my-awesome-dropzone\" class=\"dropzone \" 
                                        action=\"pfma_validacion_archivos.php\">
                                    <p>Arrastre los archivos o solo haga click</p>
                                <div class=\"dropzone-previews\">
                                </div>

                            </form>   
                              <button id=\"enviar\" type\"button\"
                               class=\"btn btn-primary pull-right\">
                                  Validar</button>&nbsp;&nbsp;

                               <button id=\"clear-dropzone\" type\"button\" class=\"btn btn-primary pull-right\">
                                  Limpiar</button>   

                            
                            </div> <!-- fin de zona-de-carga -->

                        </div> <!-- fin de row -->

                    </div> <!-- fin de ibox-content x00 -->

                </div> <!-- fin de float-e-margins -->

            </div>



<!-- fin nomina 416 -->
<!-- Nuevo tab -->

<div class=\"panel\">
    <div class=\"panel-body\">
        <h3 class=\"title-hero\">
            Alternate style
        </h3>
        <div class=\"example-box-wrapper\">

            <div id=\"form-wizard-3\" class=\"form-wizard\">
                <ul>
                    <li class=\"\">
                        <a href=\"#step-1\" data-toggle=\"tab\" aria-expanded=\"true\">
                            <label class=\"wizard-step\">1</label>
                      <span class=\"wizard-description\">
                         User details
                         <small>Gather the user details</small>
                      </span>
                        </a>
                    </li>
                    <li class=\"\">
                        <a href=\"#step-2\" data-toggle=\"tab\" aria-expanded=\"false\">
                            <label class=\"wizard-step\">2</label>
                      <span class=\"wizard-description\">
                         Contact information
                         <small>Confirm contact details</small>
                      </span>
                        </a>
                    </li>
                    <li class=\"\">
                        <a href=\"#step-3\" data-toggle=\"tab\">
                            <label class=\"wizard-step\">3</label>
                      <span class=\"wizard-description\">
                         Business support
                         <small>Establish business description</small>
                      </span>
                        </a>
                    </li>
                    <li class=\"active\">
                        <a href=\"#step-4\" data-toggle=\"tab\" aria-expanded=\"false\">
                            <label class=\"wizard-step\">4</label>
                      <span class=\"wizard-description\">
                         Final steps
                         <small>Finish and send the email</small>
                      </span>
                        </a>
                    </li>
                </ul>
                <div class=\"tab-content\">
                    <div class=\"tab-pane\" id=\"step-1\">
                        <div class=\"content-box\">
                            <h3 class=\"content-box-header bg-default\">
                                First
                            </h3>
                            <div class=\"content-box-wrapper\">
                                Lorem ipsum dolor sic amet dixit tu.
                            </div>
                        </div>
                    </div>
                    <div class=\"tab-pane\" id=\"step-2\">
                        <div class=\"content-box\">
                            <h3 class=\"content-box-header bg-black\">
                                Second
                            </h3>
                            <div class=\"content-box-wrapper\">
                                Lorem ipsum dolor sic amet dixit tu.
                            </div>
                        </div>
                    </div>
                    <div class=\"tab-pane\" id=\"step-3\">
                        <div class=\"content-box\">
                            <h3 class=\"content-box-header bg-green\">
                                Third
                            </h3>
                            <div class=\"content-box-wrapper\">
                                Lorem ipsum dolor sic amet dixit tu.
                            </div>
                        </div>
                    </div>
                    <div class=\"tab-pane active\" id=\"step-4\">
                        <div class=\"content-box\">
                            <h3 class=\"content-box-header bg-blue\">
                                Forth
                            </h3>
                            <div class=\"content-box-wrapper\">
                                Lorem ipsum dolor sic amet dixit tu.
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>


<!-- fin nuevo tab -->


<!-- Nomina 610 -->

            <div class=\"col-lg-12\" id=\"x00\">
                <div class=\"ibox float-e-margins\">
                    <div class=\"ibox-title animated bounceIn\">
                        <h5>
                            <i class=\"fa fa-medkit fa-2x\" style=\"color: #1ab394;\"></i>
                            Integración de Productos de Nómina 610
                        </h5>
                        <div class=\"ibox-tools\">
                            <a class=\"collapse-link\">
                                <i class=\"fa fa-chevron-up\"></i>
                            </a>
                            <a class=\"dropdown-toggle\" data-toggle=\"dropdown\" href=\"#\">
                                <i class=\"fa fa-wrench\"></i>
                            </a>
                            <ul class=\"dropdown-menu dropdown-user\">
                                <li><a href=\"#\">Config option 1</a>
                                </li>
                                <li><a href=\"#\">Config option 2</a>
                                </li>
                            </ul>
                            
                        </div>
                    </div>
                    <div class=\"ibox-content   animated bounceIn\" id=\"nomina-610\">

                        <div class=\"row\">
                            <div class=\"col-sm-4 b-r\">
                                <h3 class=\"m-t-none m-b\">Área Central</h3>
                                <h3 class=\"m-t-none m-b\">Órganos  Descentralizados</h3>
                                <h3 class=\"m-t-none m-b\">Organismos Públicos  Descentralizados</h3>
                                <h3 class=\"m-t-none m-b\">Honorarios</h3>
                                

                                <form role=\"form\">
                                    <div class=\"form-group\">
                                        <label>Bases de Datos Nomina</label> 
                                        <div id=\"resumen_carga\">
                                        </div>

                                    </div>
                                </form>
                            </div>

                            <div class=\"col-sm-8\" id=\"zona-de-carga\">
                            <form id=\"my-awesome-dropzone\" class=\"dropzone \" 
                                        action=\"pfma_validacion_archivos.php\">
                                    <p>Arrastre los archivos o solo haga click</p>
                                <div class=\"dropzone-previews\">
                                </div>

                            </form>   
                              <button id=\"enviar\" type\"button\"
                               class=\"btn btn-primary pull-right\">
                                  Validar</button>&nbsp;&nbsp;

                               <button id=\"clear-dropzone\" type\"button\" class=\"btn btn-primary pull-right\">
                                  Limpiar</button>   

                            
                            </div> <!-- fin de zona-de-carga -->

                        </div> <!-- fin de row -->

                    </div> <!-- fin de ibox-content x00 -->

                </div> <!-- fin de float-e-margins -->

            </div>



<!-- fin nomina 610 -->





   <!-- SECCION DE RESULTADOS -->
<!--
        <div id=\"resultados\"  class=\"wrapper wrapper-content animated fadeInRight\">
-->
                $Resultados
                <div class=\"col-lg-12\" id=\"x00\"  style=\" text-align:center;vertical-align:middle\">
                <div>
                    <button class=\"btn btn-primary btn-lg\" type=\"button\" id=\"EnviarRemesa\">
                    <i class=\"fa fa-upload\"></i>&nbsp;Enviar Archivos</button>
                </div> 
                </div> 


<!--          
        </div> 
-->        
    <!-- FIN SECCION DE RESULTADOS -->

                        </div>
                    </div>
                </div>
              </div>
            </div>                     
          </div>	";
}


function fncBuildTopNavBar()
{

return "
	<div id=\"page-wrapper\" class=\"gray-bg dashbard-1\">
        <div class=\"row border-bottom\">
        <nav class=\"navbar navbar-static-top\" role=\"navigation\" style=\"margin-bottom: 0\">
            <div class=\"navbar-header\">
                <a class=\"navbar-minimalize minimalize-styl-2 btn btn-primary\" href=\"#\">
                    <i class=\"fa fa-bars\"></i> 
                </a>
            </div>
            <ul class=\"nav navbar-top-links navbar-right\">
                <li>
                    <span class=\"m-r-sm text-muted welcome-message\">
                    Sistema de Recepción de Productos de Nómina</span>
                </li>
                <li class=\"dropdown\">
                    <a class=\"dropdown-toggle count-info\" data-toggle=\"dropdown\" href=\"#\">
                        <i class=\"fa fa-bell\"></i>  <span class=\"label label-primary\">8</span>
                    </a>
                    <ul class=\"dropdown-menu dropdown-alerts\">
                        <li>
                            <a href=\"#\">
                                <div>
                                    <i class=\"glyphicon glyphicon-time \"></i> 
                                    Inicia perido de recepción
                                    <span class=\"pull-right text-muted small\">Hace 4 min. </span>
                                </div>
                            </a>
                        </li>
                        <li class=\"divider\"></li>
                        <li>
                            <a href=\"#\">
                                <div>
                                    <i class=\"glyphicon glyphicon-alert\">
                                    </i> Inconsistencia en archivos
                                    <span class=\"pull-right text-muted small\">12 minutes ago</span>
                                </div>
                            </a>
                        </li>
                        <li class=\"divider\" style=\" background-color:#D8D8D8\" ></li>
                        <li>
                            <a href=\"#\">
                                <div>
                                    <i class=\"glyphicon glyphicon-ok-sign\">
                                    </i> Quincena 5
                                    <span class=\"pull-right text-muted small\">4 minutes ago</span>
                                </div>
                            </a>
                        </li>
                        <li class=\"divider\"></li>
                        <li>
                            <div class=\"text-center link-block\">
                                <a href=\"#\">
                                    <strong>Todos los Avisos</strong>
                                    <i class=\"fa fa-angle-right\"></i>
                                </a>
                            </div>
                        </li>
                    </ul>
                </li>


                <li>
                    <a href=\"../index.php\">
                        <i class=\"fa fa-sign-out\"></i> Log out
                    </a>
                </li>
                <li>
                    <a class=\"right-sidebar-toggle\">
                        <i class=\"fa fa-tasks\"></i>
                    </a>
                </li>
            </ul>

        </nav>
        </div>
		";



} // fin de fncBuildTopNavBar



function fncBuildJS()
{

return "
   <!-- Mainly scripts -->
    <script src=\"../js/jquery-2.1.1.js\"></script>
    <script src=\"../js/bootstrap.min.js\"></script>
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
   

    <!-- jQuery UI -->
    <script src=\"../js/plugins/jquery-ui/jquery-ui.min.js\"></script>

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

     <!-- DROPZONE -->
    <script src=\"../js/plugins/dropzone/dropzone.js\"></script>
<!--
    <script src=\"//ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js\"></script>

  -->  
 




    <script>
        $(document).ready(function() {


            setTimeout(function() {
                toastr.options = {
                    closeButton: true,
                    progressBar: true,
                    showMethod: 'slideDown',
                    timeOut: 4000
                };
                toastr.success('Dirección General de Recursos Humanos', 'Secretaria de Salud');

            }, 1200);


            var data1 = [
                [0,4],[1,8],[2,5],[3,10],[4,4],[5,16],[6,5],[7,11],[8,6],[9,11],[10,30],[11,10],[12,13],[13,4],[14,3],[15,3],[16,6]
            ];
            var data2 = [
                [0,1],[1,0],[2,2],[3,0],[4,1],[5,3],[6,1],[7,5],[8,2],[9,3],[10,2],[11,1],[12,0],[13,2],[14,8],[15,0],[16,0]
            ];
            $(\"#flot-dashboard-chart\").length && $.plot($(\"#flot-dashboard-chart\"), [
                data1, data2
            ],
                    {
                        series: {
                            lines: {
                                show: false,
                                fill: true
                            },
                            splines: {
                                show: true,
                                tension: 0.4,
                                lineWidth: 1,
                                fill: 0.4
                            },
                            points: {
                                radius: 0,
                                show: true
                            },
                            shadowSize: 2
                        },
                        grid: {
                            hoverable: true,
                            clickable: true,
                            tickColor: \"#d5d5d5\",
                            borderWidth: 1,
                            color: '#d5d5d5'
                        },
                        colors: [\"#1ab394\", \"#1C84C6\"],
                        xaxis:{
                        },
                        yaxis: {
                            ticks: 4
                        },
                        tooltip: false
                    }
            );

            var doughnutData = [
                {
                    value: 300,
                    color: \"#a3e1d4\",
                    highlight: \"#1ab394\",
                    label: \"App\"
                },
                {
                    value: 50,
                    color: \"#dedede\",
                    highlight: \"#1ab394\",
                    label: \"Software\"
                },
                {
                    value: 100,
                    color: \"#A4CEE8\",
                    highlight: \"#1ab394\",
                    label: \"Laptop\"
                }
            ];

            var doughnutOptions = {
                segmentShowStroke: true,
                segmentStrokeColor: \"#fff\",
                segmentStrokeWidth: 2,
                percentageInnerCutout: 45, // This is 0 for Pie charts
                animationSteps: 100,
                animationEasing: \"easeOutBounce\",
                animateRotate: true,
                animateScale: false
            };

            var ctx = document.getElementById(\"doughnutChart\").getContext(\"2d\");
            var DoughnutChart = new Chart(ctx).Doughnut(doughnutData, doughnutOptions);

            var polarData = [
                {
                    value: 300,
                    color: \"#a3e1d4\",
                    highlight: \"#1ab394\",
                    label: \"App\"
                },
                {
                    value: 140,
                    color: \"#dedede\",
                    highlight: \"#1ab394\",
                    label: \"Software\"
                },
                {
                    value: 200,
                    color: \"#A4CEE8\",
                    highlight: \"#1ab394\",
                    label: \"Laptop\"
                }
            ];

            var polarOptions = {
                scaleShowLabelBackdrop: true,
                scaleBackdropColor: \"rgba(255,255,255,0.75)\",
                scaleBeginAtZero: true,
                scaleBackdropPaddingY: 1,
                scaleBackdropPaddingX: 1,
                scaleShowLine: true,
                segmentShowStroke: true,
                segmentStrokeColor: \"#fff\",
                segmentStrokeWidth: 2,
                animationSteps: 100,
                animationEasing: \"easeOutBounce\",
                animateRotate: true,
                animateScale: false
            };
            var ctx = document.getElementById(\"polarChart\").getContext(\"2d\");
            var Polarchart = new Chart(ctx).PolarArea(polarData, polarOptions);

        });
    </script>

<script>




     Dropzone.options.myAwesomeDropzone = {
                autoProcessQueue: false,
                init: function() {
                var myAwesomeDropzone = this; // closure
                var submitButton = document.querySelector(\"#enviar\");
                var ListaFile=\"\";
                 

                 submitButton.addEventListener(\"click\", function(e) {
                         console.log ('Enviando Archivos');  
                         //e.preventDefault();
                        //e.stopPropagation();
                         myAwesomeDropzone.processQueue(); // Tell Dropzone to process all queued files.
                         //$(\"#my-awesome-dropzone\").submit();

                         //zona-de-carga

                         console.log ('finaliza proceso de validacion');     
                         $('#enviar').prop('disabled', true);
                         $('#resultados').removeClass('hide');
                         $('#myModal4').modal('show');


                 });

                this.on(\"success\", function(file, responseText) {
                    //var MtrxRes = split(responseText);
                        //alert(responseText);

                        $('#nomina-x00').html(responseText);
                        $('#myModal4').modal('hide');

                        //file.previewTemplate.appendChild(document.createTextNode(responseText));
                });

                 this.on(\"complete\", function(file) {
                         ListaFile= ListaFile + '<p>' +
                         '<span class=\"glyphicon glyphicon-open-file\" STYLE=\" font-size: 35px;\"> </span>  ' 
                         +file.name +'</p>';
                         console.log ('Proceso exitoso' + file.name);  
                         console.log (ListaFile);  
                         $('#resumen_carga').html(ListaFile);

                    });
                 this.on(\"processing\", function(files, response) {
                        console.log ('Procesando');

                    });

                 this.on(\"queuecomplete\", function(files, response) {
                        //alert(typeof response );
                        //alert(typeof files );
                        console.log ('termina queuecomplete ');

                    });

                     var _this = this;

                     document.querySelector(\"button#clear-dropzone\").addEventListener(\"click\", function() {
                            console.log ('Eliminando');  
                            _this.removeAllFiles();
                            $('#resumen_carga').html('');
                            $('#resultados').hide();
                            $('#enviar').prop('disabled', false);
                     });
                }
            }
</script>





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

		    <title>Secretaria de Saluds</title>

		    <link href=\"../css/bootstrap.min.css\" rel=\"stylesheet\">
		    <link href=\"../font-awesome/css/font-awesome.css\" rel=\"stylesheet\">

		    <!-- Toastr style -->
		    <link href=\"../css/plugins/toastr/toastr.min.css\" rel=\"stylesheet\">

		    <!-- Gritter -->
		    <link href=\"../js/plugins/gritter/jquery.gritter.css\" rel=\"stylesheet\">


            <link href=\"../css/animate.css\" rel=\"stylesheet\">
            <link href=\"../css/style.css\" rel=\"stylesheet\">            

            <link href=\"../css/plugins/dropzone/basic.css\" rel=\"stylesheet\">
            <link href=\"../css/plugins/dropzone/dropzone.css\" rel=\"stylesheet\">
<link href=\"../css/tab2.css\" rel=\"stylesheet\">

<style>
.form-wizard>ul>li a .wizard-step {
    font-size: 16px;
    line-height: 42px;
    position: relative;
    z-index: 5;
    display: block;
    width: 40px;
    height: 40px;
    margin: 0 auto 5px;
    cursor: pointer;
    text-align: center;
    color: #fafafa;
    border-radius: 100px;
    background: #ccc;
}

.form-wizard>ul>li a, .form-wizard>ul>li a:hover {
    position: relative;
    display: block;
    opacity: 1;
    color: #666;
    -moz-opacity: 1;
    filter: alpha(opacity:100);
}

:active, :focus, :visited, a, a:active, a:focus, a:visited {
    outline: 0;
    outline-color: initial;
    outline-style: initial;
    outline-width: 0px;
}

.form-wizard>ul {
    position: relative;
    display: table;
    width: 100%;
    margin: 0 0 20px;
    list-style: none;
}
.chosen-results, .form-wizard>ul, .nav-list ul, .nav-list-horizontal ul, .parsley-errors-list, .reset-ul, .tabs-navigation>ul, ul.messages-box, ul.notifications-box, ul.progress-box {
    margin: 0;
    padding: 0;
    list-style: none;
}
ol, ul {
    margin-top: 0;
    margin-bottom: 10px;
}
*, :after, :before {
    -webkit-box-sizing: border-box;
    -moz-box-sizing: border-box;
    box-sizing: border-box;
}
*, :after, :before {
    -webkit-box-sizing: border-box;
    -moz-box-sizing: border-box;
    box-sizing: border-box;
}
user agent stylesheet
ul, menu, dir {
    display: block;
    list-style-type: disc;
    -webkit-margin-before: 1em;
    -webkit-margin-after: 1em;
    -webkit-margin-start: 0px;
    -webkit-margin-end: 0px;
    -webkit-padding-start: 40px;
}
Inherited from body
body {
    font-family: \"Open Sans\",\"Helvetica Neue\",Helvetica,Arial,sans-serif;
    font-size: 13px;
    color: #3e4855;
    background-color: #fff;
    line-height: 1.42857143;
}
body {
    font-family: \"Helvetica Neue\",Helvetica,Arial,sans-serif;
    font-size: 14px;
    line-height: 1.42857143;
    color: #333;
    background-color: #fff;
}


</style>

		</head>";
} // fin de fncBuildHead


function fncBuildBody()
{

	$PrimParte = fncBuildTopNavBar();
	$Row1= fncBuildRow1();
	return "

<body>

<table align=\"center\" height=\"60\" style=\"width: 100%\">
  <tr>
     <td width=\"40%\" align=\"left\"><img src=\"../images/logoSALUD_hoz.png\" width=\"289\" height=\"95\" /></td>
     <!--<td width=\"420\" align=\"left\">
     <img src=\"../images/70Salud.jpg\" width=\"375\" height=\"91\" /></td>-->
     <!--<td width=\"683\" align=\"right\">
     <div id=\"dominio\">Recepción Art. 74</div>

     
     </td>  -->  
     <td width=\"60%\" align=\"right\">
             <div class=\"col-lg-11\">
                    <h2> Dirección General de Recursos Humanos
                    
                    </h2>
        </div>

     
     </td>    
  </tr>
</table> 


    <div id=\"wrapper\">
        <nav class=\"navbar-default navbar-static-side\" role=\"navigation\">
            <div class=\"sidebar-collapse\">
                <ul class=\"nav metismenu \" id=\"side-menu\">
                    <li class=\"nav-header\">
                        <div class=\"dropdown profile-element\"> <span>
                            <img alt=\"image\" class=\"img-circle\" 
                            src=\"../img/profile_small.jpg\" />
                             </span>
                            <a data-toggle=\"dropdown\" class=\"dropdown-toggle\" href=\"#\">
                            <span class=\"clear\"> <span class=\"block m-t-xs\"> 
                            <strong class=\"font-bold text-muted\">Noe Alvarez Salvador</strong>
                             </span> <span class=\"text-muted text-xs block\">
                             Responsable de Nómina <b class=\"caret\"></b></span> </span> </a>
                            <ul class=\"dropdown-menu animated fadeInRight m-t-xs\">
                                <li><a href=\"#\">Profile</a></li>
                                <li class=\"divider\"></li>
                                <li><a href=\"../index.php\">Logout</a></li>
                            </ul>
                        </div>
                        <div class=\"logo-element\">
                            IN+
                        </div>
                    </li>
                    <li class=\"active\">
                        <a href=\"#\">
                          <i class=\"fa fa-th-large\"></i> 
                          <span class=\"nav-label\">Productos de Nómina</span> 
                          <span class=\"fa arrow\"></span></a>
                        <ul class=\"nav nav-second-level\">
                            <li class=\"active\">
                             <a href=\"#\" id=\"Qhis\">
                              Anteriores 
                             </a>
                             
                              
                              </li>
                            <li class=\"divider\"></li>  
                            <li><a href=\"ptma_opcd.php\" id=\"Q6\">Quincena 6</a></li>
                            <li class=\"divider\" style=\" background-color:#D8D8D8\" ></li>

                            <li><a href=\"#\" id=\"Q7\">Quincena 7</a></li>
                            <li class=\"divider\" style=\" background-color:#D8D8D8\" ></li>
                            <li><a href=\"#\"id=\"Q100\">Próximas 
                            	<span class=\"label label-primary pull-right\">NEW
                            	</span></a>
                            </li>
                        </ul>
                    </li>
                    <li>
                        <a href=\"#\"><i class=\"glyphicon glyphicon-list-alt\"></i> 
                        <span class=\"nav-label\">Articulo 74</span><span class=\"fa arrow\"></span></a>
                        <ul class=\"nav nav-second-level collapse\">
                            <li><a href=\"#\" id=\"Q74000\">Historico</a></li>
                            <li><a href=\"#\" id=\"Q74006\">Quincena 6</a></li>
                            <li><a href=\"#\" id=\"Q74007\">Quincena 7</a></li>
                            <li><a href=\"#\" id=\"Q74100\">Siguientes </a></li>
                        </ul>
                    </li>
                </ul>

            </div>
        </nav>

        $PrimParte

        $Row1
							";


} // fin de fncBuildBody

function fncBuildTail($JS)
{

return "
    <div class=\"spiner-example modal inmodal\" id=\"myModal4\" tabindex=\"-1\" 
    role=\"dialog\" aria-hidden=\"true\" style=\"display:none; position: absolute;\">
<br>
      <br>
      <br>

      <div class=\"sk-spinner sk-spinner-fading-circle\">

                         <div class=\"sk-circle1 sk-circle \" 
                                style=\"width: 300%;height: 300%;\"></div>

                            <div class=\"sk-circle2 sk-circle \" 
                                style=\"width: 300%;height: 300%;\"></div>
                            <div class=\"sk-circle3 sk-circle \" 
                            style=\"width: 300%;height: 300%;\"></div>
                            <div class=\"sk-circle4 sk-circle\" 
                            style=\"width: 300%;height: 300%;\"></div>
                            <div class=\"sk-circle5 sk-circle\" 
                            style=\"width: 300%;height: 300%;\"></div>
                            <div class=\"sk-circle6 sk-circle\" 
                            style=\"width: 300%;height: 300%;\"></div>
                            <div class=\"sk-circle7 sk-circle\" 
                            style=\"width: 300%;height: 300%;\"></div>
                            <div class=\"sk-circle8 sk-circle\" 
                            style=\"width: 300%;height: 300%;\"></div>
                            <div class=\"sk-circle9 sk-circle\" 
                            style=\"width: 300%;height: 300%;\"></div>
                            <div class=\"sk-circle10 sk-circle\" 
                            style=\"width: 300%;height: 300%;\"></div>
                            <div class=\"sk-circle11 sk-circle\" 
                            style=\"width: 300%;height: 300%;\"></div>
                            <div class=\"sk-circle12 sk-circle\" 
                            style=\"width: 300%;height: 300%;\"></div>
        </div>
    </div>
                







			$JS


<script>

		$('a').click(function(){
			var IdQna = event.target.id;
			var reg = new RegExp(/^Q[0-9]{1,3}/);


	  		//alert('Alguien Pulso >' + IdQna +'< estatus' + reg.test(IdQna) );


				if( reg.test(IdQna))
				{
					//alert('Elejiste ' + IdQna);

					//$('#page-wrapper').load( \"dashboard.php\" );


				}
                else {
                    if(IdQna == 'Qhis')
                     {   
                    
                    $('#main_page').load( \"historico.php\" );

                    }

                }



			}
		);

        $('#EnviarRemesa').click(function(){
            //var IdB = event.target.id;
            alert ('Enviar Remesa');
            }
        );



</script>
			</body>
			</html>
	";
} // fin de fncBuildTail


?>