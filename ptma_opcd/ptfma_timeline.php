<?php

$IdEstado ="";

if(isset($_GET['id']))
	$IdEstado =$_GET['id'];	


echo "
        <div class=\"wrapper wrapper-content\">
            <div class=\"row animated fadeInRight\">
                <div class=\"col-sh-4 col-lg-12\">
                <div class=\"ibox float-e-margins\">

					<div class=\"text-center float-e-margins p-md\">
                    <h1>$IdEstado  </h1>
                    </div>

                        <div id=\"vertical-timeline\" class=\"vertical-container dark-timeline center-orientation\">



                            <div class=\"vertical-timeline-block\">
                                <div class=\"vertical-timeline-icon navy-bg\">
                                    <i class=\"fa fa-check-square\"></i>
                                </div>

                                <div class=\"vertical-timeline-content\">
                                    <h2>Envio de Producto de Nómina Finalizado</h2>
                                    <p>Una vez que se realizaron las validaciones de calidad de información establecidas por Dirección General de Recursos Humanos, se dar por terminada de forma satisfactoria.
                                    </p>
                                    <a href=\"#\" class=\"btn btn-sm btn-primary\"> More info</a>
                                    <span class=\"vertical-date\">
                                        12-Abr-2016 <br/>
                                        <small>13:24:35</small>
                                    </span>
                                </div>
                            </div>

                            <div class=\"vertical-timeline-block\">
                                <div class=\"vertical-timeline-icon yellow-bg\">
                                    <i class=\"fa fa-file-text\"></i>
                                </div>

                                <div class=\"vertical-timeline-content\">
                                    <h2>Observaciones</h2>
                                    <p>Revisando la información se detecto una inconsistencia  solo con el documento de presupuestales.</p>
                                    <a href=\"#\" class=\"btn btn-sm btn-success\"> Observaciones </a>
                                    <span class=\"vertical-date\">
                                        11-Abr-2016 <br/>
                                        <small>10:13:46</small>
                                    </span>
                                </div>
                            </div>

                            <div class=\"vertical-timeline-block\">
                                <div class=\"vertical-timeline-icon lazur-bg\">
                                    <i class=\"fa fa-paper-plane\"></i>
                                </div>

                                <div class=\"vertical-timeline-content\">
                                    <h2>Envio de Información</h2>
                                    <p>Se envia la información a base central para la integracion. </p>
                                    
                                    <span class=\"vertical-date\"> 08-Abr-2016  <br/><small>19:04:00</small></span>
                                </div>
                            </div>


                            <div class=\"vertical-timeline-block\">
                                <div class=\"vertical-timeline-icon lazur-bg\">
                                    <i class=\"fa fa-check-circle\"></i>
                                </div>

                                <div class=\"vertical-timeline-content\">
                                    <h2>Validación de Información Finalizada</h2>
                                    <p>La informacion de Productos de Nomina será enviada al proceso de validaciond e presupuestales</p>
                                    <span class=\"vertical-date\">08-Abr-2016 <br/><small>19:02:23</small></span>
                                </div>
                            </div>


                            <div class=\"vertical-timeline-block\">
                                <div class=\"vertical-timeline-icon red-bg\">
                                    <i class=\"fa fa-file-text-o\"></i>
                                </div>

                                <div class=\"vertical-timeline-content\">
                                    <h2>Análisis de Información</h2>
                                    <p>Se ejecutó el proceso de análisis y validación de Directivas de calidad de información y se detectó que los archivos no cumplieron con las directrices establecidas por la Dirección General de Recursos Humanos. </p>
                                    <a href=\"#\" class=\"btn btn-sm btn-info\">Revisar Errores</a>
                                    <span class=\"vertical-date\">08-Abr-2016 <br/>
                                    <small>15:23:03</small></span>
                                </div>
                            </div>




                            <div class=\"vertical-timeline-block\">
                                <div class=\"vertical-timeline-icon red-bg\">
                                    <i class=\"fa fa-file-text-o\"></i>
                                </div>

                                <div class=\"vertical-timeline-content\">
                                    <h2>Análisis de Información</h2>
                                    <p>Se ejecutó el proceso de análisis y validación de Directivas de calidad de información y se detectó que los archivos no cumplieron con las directrices establecidas por la Dirección General de Recursos Humanos. </p>
                                    <a href=\"#\" class=\"btn btn-sm btn-info\">Revisar Errores</a>
                                    <span class=\"vertical-date\">08-Abr-2016 <br/>
                                    <small>13:23:03</small></span>
                                </div>
                            </div>

                            <div class=\"vertical-timeline-block\">
                                <div class=\"vertical-timeline-icon navy-bg\">
                                    <i class=\"fa fa-clock-o \"></i>
                                </div>

                                <div class=\"vertical-timeline-content\">
                                    <h2>Inicia Periodo de Entrega</h2>
                                    <p>Inicia periodo de entrega de Productos de Nómina como lo marca la regulación Actual de la Dirección General de Recursos Humanos. </p>
                                    <span class=\"vertical-date\">07-Abr-2016 <br/>
                                    <small>09:00:00</small></span>
                                </div>
                            </div>
                        </div>

                    </div>
                </div>

            </div>
        </div>

";


?>