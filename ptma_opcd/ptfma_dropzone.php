<?php

echo "
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

                        <div class=\"row\" style=\" text-align:center;vertical-align:middle\">
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
                            <form id=\"my-awesome-dropzone\" class=\"dropzone dz-clickable\" action=\"pfma_validacion_archivos.php\">
                                    <p>Arrastre los archivos o solo haga click</p>
                                <div class=\"dropzone-previews\">
                                </div>

                            <div class=\"dz-default dz-message\"><span>Drop files here to upload</span></div></form>   
                              <button id=\"enviar\" type\"button\"=\"\" class=\"btn btn-primary pull-right\">
                                  Validar</button>&nbsp;&nbsp;

                               <button id=\"clear-dropzone\" type\"button\"=\"\" class=\"btn btn-primary pull-right\">
                                  Limpiar</button>   

                            
                            </div> <!-- fin de zona-de-carga -->

                        </div> <!-- fin de row -->

                    </div> <!-- fin de ibox-content x00 -->

                </div> <!-- fin de float-e-margins -->

	";

?>