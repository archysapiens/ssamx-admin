<?php

/*********************************************************************
 * 
 * Funcion : cierraRemesa
 * Objetivo: Cierre de remesa y envio a Carag Tabla Staging
 * Parametros
 * $IdRemesa   : Identificador de remesa
 *               
 * Retorno
 * $Resultado  : CERO OK otro Nk
  **********************************************************************/

function cierraRemesa($IdRemesa,$AnioEnvio, $QnaEnvio){
$Resultado=-UNO;
//$TagEnvio = "$QnaEnvio|$AnioEnvio";
$TagEnvio = "$AnioEnvio-$QnaEnvio";
//echo "cierraRemesa/para IdRemesa>$IdRemesa< AnioEnvio>$AnioEnvio< QnaEnvio>$QnaEnvio< <br>";
//echo "cierraRemesa/para TagEnvio>$TagEnvio<<br>";
$db = new DbCnnx();     
if($IdRemesa > CERO){
    $SQL= " update remesas 
            set estatus='T', fecha_actualizacion=now(),
            tag_envio='$TagEnvio' 
            WHERE id = $IdRemesa ";    

    $Rows = $db->select($SQL);    
    echo ">>>".$db->error()."<< <br>";
    $Resultado=CERO;
}
else
    echo "ptfma_envia_remesa_info.inc/cierraRemesa/error($IdRemesa , $AnioEnvio , $QnaEnvio)";
return $Resultado;
} // fin de cierraRemesa

/*********************************************************************
 * 
 * Funcion : construyeTablaProductosNomina
 * Objetivo: Construye tabla de los productos de nomina a enviar 
 
 * Parametros
 * $TagEnvio :  Identificador Tag de Envio de remesa
 * $IdRemesa   : Identificador de remesa
 *               
 * Retorno
 * $Resultado  : Tabla construida
  **********************************************************************/

function construyeTablaProductosNomina($TagEnvio,$IdRemesa){
$HeaderTabla ="   <table class=\"table table-striped table-hover\">
                                                <tbody>";

$TailTabla = " </tbody>
                                </table>";
$BodyTabla="";                                

$db = new DbCnnx(); 
$SQLProdNom ="SELECT  logg.id_remesas, logg.tipo_archivo,logg.archivo,logg.registros,
logg.observaciones, logg.etiqueta_envio, logg.archivo_error,
logg.registros_error, logg.estatus, logg.id_tipo_nom, 
(SELECT ct.DESCRIPCION FROM cat_tipnom ct WHERE ct.TIPO=logg.id_tipo_nom  COLLATE utf8_spanish_ci )AS tipo_nomina, (SELECT ct.TIPO FROM cat_tipnom ct WHERE ct.TIPO=logg.id_tipo_nom  COLLATE utf8_spanish_ci )AS tipo
              FROM remesas rem, logger logg
              WHERE rem.id=logg.id_remesas AND 
              rem.id=$IdRemesa AND 
              logg.etiqueta_envio='$TagEnvio' 
              ORDER BY logg.fecha_agregacion";

//echo "construyeTablaProductosNomina/ >>$SQLProdNom<<";

$Rows = $db->select($SQLProdNom);

if(is_array($Rows)){
  $Contador= CERO;
  $TagEnvioActual   = "";
  $TagEnvioAnterior = "";
  $ListaArchivoProdNomina="";

  while(isset($Rows[$Contador]['etiqueta_envio'])) {

      $TagEnvioActual   = $Rows[$Contador]['etiqueta_envio'];
      $IdRemesa         =$Rows[$Contador]['id_remesas'];
      $TipoArchivo      =$Rows[$Contador]['tipo_archivo'];
      $ArchivoProcesado = $Rows[$Contador]['archivo'];
      $NumRegistros     = $Rows[$Contador]['registros'];
      $Observaciones    = $Rows[$Contador]['observaciones'];
      $TipoNomina       = utf8_encode($Rows[$Contador]['tipo_nomina'] );
      $Tipo       = $Rows[$Contador]['tipo'];  

      
      $TipoNominaAux =" ".SUBSTR($TipoNomina,0,7);  

      $ArrNombreArchivoProcesado =explode("/", $ArchivoProcesado);
      $NombreArchivoProcesado =$ArrNombreArchivoProcesado[DOS];


      if($TipoArchivo=='D'){
	      $BodyTabla.="    <tr>
                    <td>
                    <i class=\"fa fa-file-o\" aria-hidden=\"true\" style=\"color:#313131;\"></i>
                    <strong>$NombreArchivoProcesado </strong></td>

                    <td class=\"btn-outline\" style=\"width: 116px;\" data-toggle=\"tooltip\" data-placement=\"top\" title=\"$TipoNomina\" data-original-title=\"Tooltip on top\">$Tipo $TipoNominaAux</td>

                    <td> $NumRegistros</td>
                    <td> $NumRegistros</td>";
    		$BodyTabla.="   <td> Percepciones</td>
                    <td class=\"client-status\">Deducciones</td>
               </tr>";

      }
      else{
	      $BodyTabla.="    <tr>
				    <td>
				    <i class=\"fa fa-file-text-o\" style=\"color:#313131;\"></i>
				    $NombreArchivoProcesado </td>
                    <td class=\"btn-outline\" style=\"width: 116px;\" data-toggle=\"tooltip\" data-placement=\"down\" title=\"$TipoNomina\" data-original-title=\"Tooltip on top\">$Tipo $TipoNominaAux</td>

				    <td> $NumRegistros</td>
				    <td> $NumRegistros</td>";

      		$BodyTabla.="   <td> $ ###,###.##</td>
                    <td class=\"client-status\">$ ###,###.##</td>
               </tr>";
      }                          
      $Contador++;         
   }//fin while
   return $HeaderTabla . $BodyTabla . $TailTabla;
}// fin del if  


}// fin de construyeTablaProductosNomina

/*********************************************************************
 * 
 * Funcion : construyeInfoEnvioRemesas
 * Objetivo: Construye 
 *           considera archivo de datos y trailer
 * Parametros
 * $IdArchivo:  Identificador del Archivo a eliminar
 * $TagEnvio   : Identificador que etiqueta la remesa
 *               
 * Retorno
 * $Resultado  : CERO si se elimino correctamente
 *               otro numero si existe aun el registro
 **********************************************************************/

function construyeInfoEnvioRemesas($TagEnvio,$FechaLimite,$IdRemesa){
$HeadRemesa = "<div class=\"row\">
                <div class=\"col-sm-8\">
                    <div class=\"ibox\">
                        <div class=\"ibox-content\">
                            <span class=\"text-muted small pull-right\">Fecha Limite: <i class=\"fa fa-clock-o\"></i> $FechaLimite</span>
                             <div class=\"clients-list forum-item active\">


                            <ul class=\"nav nav-tabs\">
                                <span class=\"pull-right small text-muted\">1406 Elementos</span>
                                <li class=\"active\">
                                
                                <a data-toggle=\"tab\" href=\"#tab-1\" aria-expanded=\"true\">
                                <i class=\"fa fa-user-md fa-2x\"></i> Producto de Nómina

                                </a>
                                
                                </li>
                                <li class=\"\"><a data-toggle=\"tab\" href=\"#tab-2\" aria-expanded=\"false\"><i class=\"fa fa-hospital-o fa-2x\"></i> Unidades Responsables</a></li>
                            </ul>
					";

$TailRemesa =   "         </div>
                       </div>
                    </div>
                </div>
            </div>	" ;

$TablaRemesa = construyeTablaProductosNomina($TagEnvio,$IdRemesa);

return  "			$HeadRemesa
                            <div class=\"tab-content\">
                                <div id=\"tab-1\" class=\"tab-pane active\">
                                    <div class=\"slimScrollDiv\" style=\"position: relative; overflow: hidden; width: auto; height: 100%;\"><div class=\"full-height-scroll\" style=\"overflow: hidden; width: auto; height: 100%;\">
                                        <div class=\"table-responsive\">

<!-- Fin d ela tabla de productos de nomina -->
										$TablaRemesa
<!-- Fin d ela tabla de productos de nomina -->


                                        </div>
                                    </div>
                                    <div class=\"slimScrollBar\" style=\"width: 7px; position: absolute; top: 0px; opacity: 0.4; display: block; border-radius: 7px; z-index: 99; right: 1px; height: 368.852px; background: rgb(0, 0, 0);\">
                                    </div>
                                    <div class=\"slimScrollRail\" style=\"width: 7px; height: 100%; position: absolute; top: 0px; display: none; border-radius: 7px; opacity: 0.2; z-index: 90; right: 1px; background: rgb(51, 51, 51);\">
                                    </div>
                                    </div>
                                </div>

                                <div id=\"tab-2\" class=\"tab-pane\">
                                    <div class=\"slimScrollDiv\" style=\"position: relative; overflow: hidden; width: auto; height: 100%;\"><div class=\"full-height-scroll\" style=\"overflow: hidden; width: auto; height: 100%;\">
                                        <div class=\"table-responsive\">
                                            <table class=\"table table-striped table-hover\">
                                                <tbody>
                                                <tr>
                                                    <td><a data-toggle=\"tab\" href=\"#company-1\" class=\"client-link\" aria-expanded=\"false\">Tellus Institute</a></td>
                                                    <td>Rexton</td>
                                                    <td><i class=\"fa fa-flag\"></i> Angola</td>
                                                    <td class=\"client-status\"><span class=\"label label-primary\">Active</span></td>
                                                </tr>
                                                <tr>
                                                    <td><a data-toggle=\"tab\" href=\"#company-2\" class=\"client-link\" aria-expanded=\"false\">Velit Industries</a></td>
                                                    <td>Maglie</td>
                                                    <td><i class=\"fa fa-flag\"></i> Luxembourg</td>
                                                    <td class=\"client-status\"><span class=\"label label-primary\">Active</span></td>
                                                </tr>
                                                <tr>
                                                    <td><a data-toggle=\"tab\" href=\"#company-3\" class=\"client-link\" aria-expanded=\"false\">Art Limited</a></td>
                                                    <td>Sooke</td>
                                                    <td><i class=\"fa fa-flag\"></i> Philippines</td>
                                                    <td class=\"client-status\"></td>
                                                </tr>
                                                <tr>
                                                    <td><a data-toggle=\"tab\" href=\"#company-1\" class=\"client-link\" aria-expanded=\"false\">Tempor Arcu Corp.</a></td>
                                                    <td>Eisden</td>
                                                    <td><i class=\"fa fa-flag\"></i> Korea, North</td>
                                                    <td class=\"client-status\"><span class=\"label label-warning\">Waiting</span></td>
                                                </tr>
                                                <tr>
                                                    <td><a data-toggle=\"tab\" href=\"#company-2\" class=\"client-link\" aria-expanded=\"false\">Penatibus Consulting</a></td>
                                                    <td>Tribogna</td>
                                                    <td><i class=\"fa fa-flag\"></i> Montserrat</td>
                                                    <td class=\"client-status\"></td>
                                                </tr>
                                                <tr>
                                                    <td><a data-toggle=\"tab\" href=\"#company-3\" class=\"client-link\" aria-expanded=\"false\"> Ultrices Incorporated</a></td>
                                                    <td>Basingstoke</td>
                                                    <td><i class=\"fa fa-flag\"></i> Tunisia</td>
                                                    <td class=\"client-status\"><span class=\"label label-primary\">Active</span></td>
                                                </tr>
                                                <tr>
                                                    <td><a data-toggle=\"tab\" href=\"#company-2\" class=\"client-link\" aria-expanded=\"false\">Et Arcu Inc.</a></td>
                                                    <td>Sioux City</td>
                                                    <td><i class=\"fa fa-flag\"></i> Burundi</td>
                                                    <td class=\"client-status\"><span class=\"label label-primary\">Active</span></td>
                                                </tr>
                                                <tr>
                                                    <td><a data-toggle=\"tab\" href=\"#company-1\" class=\"client-link\" aria-expanded=\"false\">Tellus Institute</a></td>
                                                    <td>Rexton</td>
                                                    <td><i class=\"fa fa-flag\"></i> Angola</td>
                                                    <td class=\"client-status\"><span class=\"label label-primary\">Active</span></td>
                                                </tr>
                                                <tr>
                                                    <td><a data-toggle=\"tab\" href=\"#company-2\" class=\"client-link\" aria-expanded=\"false\">Velit Industries</a></td>
                                                    <td>Maglie</td>
                                                    <td><i class=\"fa fa-flag\"></i> Luxembourg</td>
                                                    <td class=\"client-status\"></td>
                                                </tr>
                                                <tr>
                                                    <td><a data-toggle=\"tab\" href=\"#company-3\" class=\"client-link\" aria-expanded=\"false\">Art Limited</a></td>
                                                    <td>Sooke</td>
                                                    <td><i class=\"fa fa-flag\"></i> Philippines</td>
                                                    <td class=\"client-status\"></td>
                                                </tr>
                                                <tr>
                                                    <td><a data-toggle=\"tab\" href=\"#company-1\" class=\"client-link\" aria-expanded=\"false\">Tempor Arcu Corp.</a></td>
                                                    <td>Eisden</td>
                                                    <td><i class=\"fa fa-flag\"></i> Korea, North</td>
                                                    <td class=\"client-status\"><span class=\"label label-warning\">Waiting</span></td>
                                                </tr>
                                                <tr>
                                                    <td><a data-toggle=\"tab\" href=\"#company-2\" class=\"client-link\" aria-expanded=\"false\">Penatibus Consulting</a></td>
                                                    <td>Tribogna</td>
                                                    <td><i class=\"fa fa-flag\"></i> Montserrat</td>
                                                    <td class=\"client-status\"></td>
                                                </tr>
                                                <tr>
                                                    <td><a data-toggle=\"tab\" href=\"#company-3\" class=\"client-link\" aria-expanded=\"false\"> Ultrices Incorporated</a></td>
                                                    <td>Basingstoke</td>
                                                    <td><i class=\"fa fa-flag\"></i> Tunisia</td>
                                                    <td class=\"client-status\"><span class=\"label label-primary\">Active</span></td>
                                                </tr>
                                                <tr>
                                                    <td><a data-toggle=\"tab\" href=\"#company-2\" class=\"client-link\" aria-expanded=\"false\">Et Arcu Inc.</a></td>
                                                    <td>Sioux City</td>
                                                    <td><i class=\"fa fa-flag\"></i> Burundi</td>
                                                    <td class=\"client-status\"><span class=\"label label-primary\">Active</span></td>
                                                </tr>
                                                <tr>
                                                    <td><a data-toggle=\"tab\" href=\"#company-1\" class=\"client-link\" aria-expanded=\"false\">Tellus Institute</a></td>
                                                    <td>Rexton</td>
                                                    <td><i class=\"fa fa-flag\"></i> Angola</td>
                                                    <td class=\"client-status\"><span class=\"label label-primary\">Active</span></td>
                                                </tr>
                                                <tr>
                                                    <td><a data-toggle=\"tab\" href=\"#company-2\" class=\"client-link\" aria-expanded=\"false\">Velit Industries</a></td>
                                                    <td>Maglie</td>
                                                    <td><i class=\"fa fa-flag\"></i> Luxembourg</td>
                                                    <td class=\"client-status\"></td>
                                                </tr>
                                                <tr>
                                                    <td><a data-toggle=\"tab\" href=\"#company-3\" class=\"client-link\" aria-expanded=\"false\">Art Limited</a></td>
                                                    <td>Sooke</td>
                                                    <td><i class=\"fa fa-flag\"></i> Philippines</td>
                                                    <td class=\"client-status\"></td>
                                                </tr>
                                                <tr>
                                                    <td><a data-toggle=\"tab\" href=\"#company-1\" class=\"client-link\" aria-expanded=\"false\">Tempor Arcu Corp.</a></td>
                                                    <td>Eisden</td>
                                                    <td><i class=\"fa fa-flag\"></i> Korea, North</td>
                                                    <td class=\"client-status\"><span class=\"label label-warning\">Waiting</span></td>
                                                </tr>
                                                <tr>
                                                    <td><a data-toggle=\"tab\" href=\"#company-2\" class=\"client-link\" aria-expanded=\"false\">Penatibus Consulting</a></td>
                                                    <td>Tribogna</td>
                                                    <td><i class=\"fa fa-flag\"></i> Montserrat</td>
                                                    <td class=\"client-status\"></td>
                                                </tr>
                                                <tr>
                                                    <td><a data-toggle=\"tab\" href=\"#company-3\" class=\"client-link\" aria-expanded=\"false\"> Ultrices Incorporated</a></td>
                                                    <td>Basingstoke</td>
                                                    <td><i class=\"fa fa-flag\"></i> Tunisia</td>
                                                    <td class=\"client-status\"><span class=\"label label-primary\">Active</span></td>
                                                </tr>
                                                <tr>
                                                    <td><a data-toggle=\"tab\" href=\"#company-2\" class=\"client-link\" aria-expanded=\"false\">Et Arcu Inc.</a></td>
                                                    <td>Sioux City</td>
                                                    <td><i class=\"fa fa-flag\"></i> Burundi</td>
                                                    <td class=\"client-status\"><span class=\"label label-primary\">Active</span></td>
                                                </tr>
                                                </tbody>
                                            </table>
                                        </div>
                                    </div><div class=\"slimScrollBar\" style=\"width: 7px; position: absolute; top: 0px; opacity: 0.4; display: block; border-radius: 7px; z-index: 99; right: 1px; background: rgb(0, 0, 0);\"></div><div class=\"slimScrollRail\" style=\"width: 7px; height: 100%; position: absolute; top: 0px; display: none; border-radius: 7px; opacity: 0.2; z-index: 90; right: 1px; background: rgb(51, 51, 51);\"></div></div>
                                </div>
                            </div>

                            </div>
                        </div>
                    </div>
                </div>
                <div class=\"col-sm-4\">
                    <div class=\"ibox \">

                        <div class=\"ibox-content\">
                            <div class=\"tab-content\">
                                <div id=\"contact-1\" class=\"tab-pane active\">
                                    <div class=\"row m-b-lg\">
                                        <div class=\"col-lg-4 text-center\">
                                            <h2>Remesa</h2>

                                            <div class=\"m-b-sm\">
                                                <img alt=\"image\" class=\"img-circle\" src=\"../img/a2.jpg\" style=\"width: 62px\">
                                            </div>
                                        </div>
                                        <div class=\"col-lg-8\">
                                            <strong>
                                                About me
                                            </strong>

                                            <p>
                                                Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod
                                                tempor incididunt ut labore et dolore magna aliqua.
                                            </p>
                                            <button type=\"button\" class=\"btn btn-primary btn-sm btn-block\"><i class=\"fa fa-envelope\"></i> Send Message
                                            </button>
                                        </div>
                                    </div>
                                    <div class=\"client-detail\">
                                    <div class=\"slimScrollDiv\" style=\"position: relative; overflow: hidden; width: auto; height: 100%;\"><div class=\"full-height-scroll\" style=\"overflow: hidden; width: auto; height: 100%;\">

                                        <strong>Last activity</strong>

                                        <ul class=\"list-group clear-list\">
                                            <li class=\"list-group-item fist-item\">
                                                <span class=\"pull-right\"> 09:00 pm </span>
                                                Please contact me
                                            </li>
                                            <li class=\"list-group-item\">
                                                <span class=\"pull-right\"> 10:16 am </span>
                                                Sign a contract
                                            </li>
                                            <li class=\"list-group-item\">
                                                <span class=\"pull-right\"> 08:22 pm </span>
                                                Open new shop
                                            </li>
                                            <li class=\"list-group-item\">
                                                <span class=\"pull-right\"> 11:06 pm </span>
                                                Call back to Sylvia
                                            </li>
                                            <li class=\"list-group-item\">
                                                <span class=\"pull-right\"> 12:00 am </span>
                                                Write a letter to Sandra
                                            </li>
                                        </ul>
                                        <strong>Notes</strong>
                                        <p>
                                            Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod
                                            tempor incididunt ut labore et dolore magna aliqua.
                                        </p>
                                        <hr>
                                        <strong>Timeline activity</strong>
                                        <div id=\"vertical-timeline\" class=\"vertical-container dark-timeline\">
                                            <div class=\"vertical-timeline-block\">
                                                <div class=\"vertical-timeline-icon gray-bg\">
                                                    <i class=\"fa fa-coffee\"></i>
                                                </div>
                                                <div class=\"vertical-timeline-content\">
                                                    <p>Conference on the sales results for the previous year.
                                                    </p>
                                                    <span class=\"vertical-date small text-muted\"> 2:10 pm - 12.06.2014 </span>
                                                </div>
                                            </div>
                                            <div class=\"vertical-timeline-block\">
                                                <div class=\"vertical-timeline-icon gray-bg\">
                                                    <i class=\"fa fa-briefcase\"></i>
                                                </div>
                                                <div class=\"vertical-timeline-content\">
                                                    <p>Many desktop publishing packages and web page editors now use Lorem.
                                                    </p>
                                                    <span class=\"vertical-date small text-muted\"> 4:20 pm - 10.05.2014 </span>
                                                </div>
                                            </div>
                                            <div class=\"vertical-timeline-block\">
                                                <div class=\"vertical-timeline-icon gray-bg\">
                                                    <i class=\"fa fa-bolt\"></i>
                                                </div>
                                                <div class=\"vertical-timeline-content\">
                                                    <p>There are many variations of passages of Lorem Ipsum available.
                                                    </p>
                                                    <span class=\"vertical-date small text-muted\"> 06:10 pm - 11.03.2014 </span>
                                                </div>
                                            </div>
                                            <div class=\"vertical-timeline-block\">
                                                <div class=\"vertical-timeline-icon navy-bg\">
                                                    <i class=\"fa fa-warning\"></i>
                                                </div>
                                                <div class=\"vertical-timeline-content\">
                                                    <p>The generated Lorem Ipsum is therefore.
                                                    </p>
                                                    <span class=\"vertical-date small text-muted\"> 02:50 pm - 03.10.2014 </span>
                                                </div>
                                            </div>
                                            <div class=\"vertical-timeline-block\">
                                                <div class=\"vertical-timeline-icon gray-bg\">
                                                    <i class=\"fa fa-coffee\"></i>
                                                </div>
                                                <div class=\"vertical-timeline-content\">
                                                    <p>Conference on the sales results for the previous year.
                                                    </p>
                                                    <span class=\"vertical-date small text-muted\"> 2:10 pm - 12.06.2014 </span>
                                                </div>
                                            </div>
                                            <div class=\"vertical-timeline-block\">
                                                <div class=\"vertical-timeline-icon gray-bg\">
                                                    <i class=\"fa fa-briefcase\"></i>
                                                </div>
                                                <div class=\"vertical-timeline-content\">
                                                    <p>Many desktop publishing packages and web page editors now use Lorem.
                                                    </p>
                                                    <span class=\"vertical-date small text-muted\"> 4:20 pm - 10.05.2014 </span>
                                                </div>
                                            </div>
                                        </div>
                                    </div><div class=\"slimScrollBar\" style=\"width: 7px; position: absolute; top: 0px; opacity: 0.4; display: none; border-radius: 7px; z-index: 99; right: 1px; height: 341.083px; background: rgb(0, 0, 0);\"></div><div class=\"slimScrollRail\" style=\"width: 7px; height: 100%; position: absolute; top: 0px; display: none; border-radius: 7px; opacity: 0.2; z-index: 90; right: 1px; background: rgb(51, 51, 51);\"></div></div>
                                    </div>
                                </div>
                                <div id=\"contact-2\" class=\"tab-pane\">
                                    <div class=\"row m-b-lg\">
                                        <div class=\"col-lg-4 text-center\">
                                            <h2>Edan Randall</h2>

                                            <div class=\"m-b-sm\">
                                                <img alt=\"image\" class=\"img-circle\" src=\"../img/a3.jpg\" style=\"width: 62px\">
                                            </div>
                                        </div>
                                        <div class=\"col-lg-8\">
                                            <strong>
                                                About me
                                            </strong>

                                            <p>
                                                Many desktop publishing packages and web page editors now use Lorem Ipsum as their default tempor incididunt model text.
                                            </p>
                                            <button type=\"button\" class=\"btn btn-primary btn-sm btn-block\"><i class=\"fa fa-envelope\"></i> Send Message
                                            </button>
                                        </div>
                                    </div>
                                    <div class=\"client-detail\">
                                        <div class=\"slimScrollDiv\" style=\"position: relative; overflow: hidden; width: auto; height: 100%;\"><div class=\"full-height-scroll\" style=\"overflow: hidden; width: auto; height: 100%;\">

                                            <strong>Last activity</strong>

                                            <ul class=\"list-group clear-list\">
                                                <li class=\"list-group-item fist-item\">
                                                    <span class=\"pull-right\"> 09:00 pm </span>
                                                    Lorem Ipsum available
                                                </li>
                                                <li class=\"list-group-item\">
                                                    <span class=\"pull-right\"> 10:16 am </span>
                                                    Latin words, combined
                                                </li>
                                                <li class=\"list-group-item\">
                                                    <span class=\"pull-right\"> 08:22 pm </span>
                                                    Open new shop
                                                </li>
                                                <li class=\"list-group-item\">
                                                    <span class=\"pull-right\"> 11:06 pm </span>
                                                    The generated Lorem Ipsum
                                                </li>
                                                <li class=\"list-group-item\">
                                                    <span class=\"pull-right\"> 12:00 am </span>
                                                    Content here, content here
                                                </li>
                                            </ul>
                                            <strong>Notes</strong>
                                            <p>
                                                There are many variations of passages of Lorem Ipsum available, but the majority have suffered alteration in some form, by injected humour, or randomised words.
                                            </p>
                                            <hr>
                                            <strong>Timeline activity</strong>
                                            <div id=\"vertical-timeline\" class=\"vertical-container dark-timeline\">
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-briefcase\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>Many desktop publishing packages and web page editors now use Lorem.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 4:20 pm - 10.05.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-bolt\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>There are many variations of passages of Lorem Ipsum available.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 06:10 pm - 11.03.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon navy-bg\">
                                                        <i class=\"fa fa-warning\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>The generated Lorem Ipsum is therefore.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 02:50 pm - 03.10.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-coffee\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>Conference on the sales results for the previous year.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 2:10 pm - 12.06.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-briefcase\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>Many desktop publishing packages and web page editors now use Lorem.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 4:20 pm - 10.05.2014 </span>
                                                    </div>
                                                </div>
                                            </div>
                                        </div><div class=\"slimScrollBar\" style=\"width: 7px; position: absolute; top: 0px; opacity: 0.4; display: block; border-radius: 7px; z-index: 99; right: 1px; background: rgb(0, 0, 0);\"></div><div class=\"slimScrollRail\" style=\"width: 7px; height: 100%; position: absolute; top: 0px; display: none; border-radius: 7px; opacity: 0.2; z-index: 90; right: 1px; background: rgb(51, 51, 51);\"></div></div>
                                    </div>
                                </div>
                                <div id=\"contact-3\" class=\"tab-pane\">
                                    <div class=\"row m-b-lg\">
                                        <div class=\"col-lg-4 text-center\">
                                            <h2>Jasper Carson</h2>

                                            <div class=\"m-b-sm\">
                                                <img alt=\"image\" class=\"img-circle\" src=\"../img/a4.jpg\" style=\"width: 62px\">
                                            </div>
                                        </div>
                                        <div class=\"col-lg-8\">
                                            <strong>
                                                About me
                                            </strong>

                                            <p>
                                                Latin professor at Hampden-Sydney College in Virginia, looked  embarrassing hidden in the middle.
                                            </p>
                                            <button type=\"button\" class=\"btn btn-primary btn-sm btn-block\"><i class=\"fa fa-envelope\"></i> Send Message
                                            </button>
                                        </div>
                                    </div>
                                    <div class=\"client-detail\">
                                        <div class=\"slimScrollDiv\" style=\"position: relative; overflow: hidden; width: auto; height: 100%;\"><div class=\"full-height-scroll\" style=\"overflow: hidden; width: auto; height: 100%;\">

                                            <strong>Last activity</strong>

                                            <ul class=\"list-group clear-list\">
                                                <li class=\"list-group-item fist-item\">
                                                    <span class=\"pull-right\"> 09:00 pm </span>
                                                    Aldus PageMaker including
                                                </li>
                                                <li class=\"list-group-item\">
                                                    <span class=\"pull-right\"> 10:16 am </span>
                                                    Finibus Bonorum et Malorum
                                                </li>
                                                <li class=\"list-group-item\">
                                                    <span class=\"pull-right\"> 08:22 pm </span>
                                                    Write a letter to Sandra
                                                </li>
                                                <li class=\"list-group-item\">
                                                    <span class=\"pull-right\"> 11:06 pm </span>
                                                    Standard chunk of Lorem
                                                </li>
                                                <li class=\"list-group-item\">
                                                    <span class=\"pull-right\"> 12:00 am </span>
                                                    Open new shop
                                                </li>
                                            </ul>
                                            <strong>Notes</strong>
                                            <p>
                                                Lorem Ipsum passage, and going through the cites of the word in classical literature, discovered the undoubtable source.
                                            </p>
                                            <hr>
                                            <strong>Timeline activity</strong>
                                            <div id=\"vertical-timeline\" class=\"vertical-container dark-timeline\">
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-coffee\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>Conference on the sales results for the previous year.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 2:10 pm - 12.06.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-briefcase\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>Many desktop publishing packages and web page editors now use Lorem.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 4:20 pm - 10.05.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-bolt\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>There are many variations of passages of Lorem Ipsum available.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 06:10 pm - 11.03.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon navy-bg\">
                                                        <i class=\"fa fa-warning\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>The generated Lorem Ipsum is therefore.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 02:50 pm - 03.10.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-coffee\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>Conference on the sales results for the previous year.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 2:10 pm - 12.06.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-briefcase\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>Many desktop publishing packages and web page editors now use Lorem.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 4:20 pm - 10.05.2014 </span>
                                                    </div>
                                                </div>
                                            </div>
                                        </div><div class=\"slimScrollBar\" style=\"width: 7px; position: absolute; top: 0px; opacity: 0.4; display: block; border-radius: 7px; z-index: 99; right: 1px; background: rgb(0, 0, 0);\"></div><div class=\"slimScrollRail\" style=\"width: 7px; height: 100%; position: absolute; top: 0px; display: none; border-radius: 7px; opacity: 0.2; z-index: 90; right: 1px; background: rgb(51, 51, 51);\"></div></div>
                                    </div>
                                </div>
                                <div id=\"contact-4\" class=\"tab-pane\">
                                    <div class=\"row m-b-lg\">
                                        <div class=\"col-lg-4 text-center\">
                                            <h2>Reuben Pacheco</h2>

                                            <div class=\"m-b-sm\">
                                                <img alt=\"image\" class=\"img-circle\" src=\"../img/a5.jpg\" style=\"width: 62px\">
                                            </div>
                                        </div>
                                        <div class=\"col-lg-8\">
                                            <strong>
                                                About me
                                            </strong>

                                            <p>
                                                Finibus Bonorum et Malorum\" (The Extremes of Good and Evil) by Cicero,written in 45 BC. This book is a treatise on.
                                            </p>
                                            <button type=\"button\" class=\"btn btn-primary btn-sm btn-block\"><i class=\"fa fa-envelope\"></i> Send Message
                                            </button>
                                        </div>
                                    </div>
                                    <div class=\"client-detail\">
                                        <div class=\"slimScrollDiv\" style=\"position: relative; overflow: hidden; width: auto; height: 100%;\"><div class=\"full-height-scroll\" style=\"overflow: hidden; width: auto; height: 100%;\">

                                            <strong>Last activity</strong>

                                            <ul class=\"list-group clear-list\">
                                                <li class=\"list-group-item fist-item\">
                                                    <span class=\"pull-right\"> 09:00 pm </span>
                                                    The point of using
                                                </li>
                                                <li class=\"list-group-item\">
                                                    <span class=\"pull-right\"> 10:16 am </span>
                                                    Lorem Ipsum is that it has
                                                </li>
                                                <li class=\"list-group-item\">
                                                    <span class=\"pull-right\"> 08:22 pm </span>
                                                    Text, and a search for 'lorem ipsum'
                                                </li>
                                                <li class=\"list-group-item\">
                                                    <span class=\"pull-right\"> 11:06 pm </span>
                                                    Passages of Lorem Ipsum
                                                </li>
                                                <li class=\"list-group-item\">
                                                    <span class=\"pull-right\"> 12:00 am </span>
                                                    If you are going
                                                </li>
                                            </ul>
                                            <strong>Notes</strong>
                                            <p>
                                                Lorem Ipsum which looks reasonable. The generated Lorem Ipsum is therefore always free from repetition, injected humour, or non-characteristic words etc.
                                            </p>
                                            <hr>
                                            <strong>Timeline activity</strong>
                                            <div id=\"vertical-timeline\" class=\"vertical-container dark-timeline\">
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-coffee\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>Conference on the sales results for the previous year.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 2:10 pm - 12.06.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-briefcase\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>Many desktop publishing packages and web page editors now use Lorem.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 4:20 pm - 10.05.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-bolt\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>There are many variations of passages of Lorem Ipsum available.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 06:10 pm - 11.03.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon navy-bg\">
                                                        <i class=\"fa fa-warning\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>The generated Lorem Ipsum is therefore.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 02:50 pm - 03.10.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-coffee\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>Conference on the sales results for the previous year.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 2:10 pm - 12.06.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-briefcase\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>Many desktop publishing packages and web page editors now use Lorem.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 4:20 pm - 10.05.2014 </span>
                                                    </div>
                                                </div>
                                            </div>
                                        </div><div class=\"slimScrollBar\" style=\"width: 7px; position: absolute; top: 0px; opacity: 0.4; display: block; border-radius: 7px; z-index: 99; right: 1px; background: rgb(0, 0, 0);\"></div><div class=\"slimScrollRail\" style=\"width: 7px; height: 100%; position: absolute; top: 0px; display: none; border-radius: 7px; opacity: 0.2; z-index: 90; right: 1px; background: rgb(51, 51, 51);\"></div></div>
                                    </div>
                                </div>
                                <div id=\"company-1\" class=\"tab-pane\">
                                    <div class=\"m-b-lg\">
                                            <h2>Tellus Institute</h2>

                                            <p>
                                                Finibus Bonorum et Malorum\" (The Extremes of Good and Evil) by Cicero,written in 45 BC. This book is a treatise on.
                                            </p>
                                            <div>
                                                <small>Active project completion with: 48%</small>
                                                <div class=\"progress progress-mini\">
                                                    <div style=\"width: 48%;\" class=\"progress-bar\"></div>
                                                </div>
                                            </div>
                                    </div>
                                    <div class=\"client-detail\">
                                        <div class=\"slimScrollDiv\" style=\"position: relative; overflow: hidden; width: auto; height: 100%;\"><div class=\"full-height-scroll\" style=\"overflow: hidden; width: auto; height: 100%;\">

                                            <strong>Last activity</strong>

                                            <ul class=\"list-group clear-list\">
                                                <li class=\"list-group-item fist-item\">
                                                    <span class=\"pull-right\"> <span class=\"label label-primary\">NEW</span> </span>
                                                    The point of using
                                                </li>
                                                <li class=\"list-group-item\">
                                                    <span class=\"pull-right\"> <span class=\"label label-warning\">WAITING</span></span>
                                                    Lorem Ipsum is that it has
                                                </li>
                                                <li class=\"list-group-item\">
                                                    <span class=\"pull-right\"> <span class=\"label label-danger\">BLOCKED</span> </span>
                                                    If you are going
                                                </li>
                                            </ul>
                                            <strong>Notes</strong>
                                            <p>
                                                Lorem Ipsum which looks reasonable. The generated Lorem Ipsum is therefore always free from repetition, injected humour, or non-characteristic words etc.
                                            </p>
                                            <hr>
                                            <strong>Timeline activity</strong>
                                            <div id=\"vertical-timeline\" class=\"vertical-container dark-timeline\">
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-coffee\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>Conference on the sales results for the previous year.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 2:10 pm - 12.06.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-briefcase\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>Many desktop publishing packages and web page editors now use Lorem.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 4:20 pm - 10.05.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-bolt\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>There are many variations of passages of Lorem Ipsum available.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 06:10 pm - 11.03.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon navy-bg\">
                                                        <i class=\"fa fa-warning\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>The generated Lorem Ipsum is therefore.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 02:50 pm - 03.10.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-coffee\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>Conference on the sales results for the previous year.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 2:10 pm - 12.06.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-briefcase\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>Many desktop publishing packages and web page editors now use Lorem.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 4:20 pm - 10.05.2014 </span>
                                                    </div>
                                                </div>
                                            </div>
                                        </div><div class=\"slimScrollBar\" style=\"width: 7px; position: absolute; top: 0px; opacity: 0.4; display: block; border-radius: 7px; z-index: 99; right: 1px; background: rgb(0, 0, 0);\"></div><div class=\"slimScrollRail\" style=\"width: 7px; height: 100%; position: absolute; top: 0px; display: none; border-radius: 7px; opacity: 0.2; z-index: 90; right: 1px; background: rgb(51, 51, 51);\"></div></div>
                                    </div>
                                </div>
                                <div id=\"company-2\" class=\"tab-pane\">
                                    <div class=\"m-b-lg\">
                                        <h2>Penatibus Consulting</h2>

                                        <p>
                                            There are many variations of passages of Lorem Ipsum available, but the majority have suffered alteration in some.
                                        </p>
                                        <div>
                                            <small>Active project completion with: 22%</small>
                                            <div class=\"progress progress-mini\">
                                                <div style=\"width: 22%;\" class=\"progress-bar\"></div>
                                            </div>
                                        </div>
                                    </div>
                                    <div class=\"client-detail\">
                                        <div class=\"slimScrollDiv\" style=\"position: relative; overflow: hidden; width: auto; height: 100%;\"><div class=\"full-height-scroll\" style=\"overflow: hidden; width: auto; height: 100%;\">

                                            <strong>Last activity</strong>

                                            <ul class=\"list-group clear-list\">
                                                <li class=\"list-group-item fist-item\">
                                                    <span class=\"pull-right\"> <span class=\"label label-warning\">WAITING</span> </span>
                                                    Aldus PageMaker
                                                </li>
                                                <li class=\"list-group-item\">
                                                    <span class=\"pull-right\"><span class=\"label label-primary\">NEW</span> </span>
                                                    Lorem Ipsum, you need to be sure
                                                </li>
                                                <li class=\"list-group-item\">
                                                    <span class=\"pull-right\"> <span class=\"label label-danger\">BLOCKED</span> </span>
                                                    The generated Lorem Ipsum
                                                </li>
                                            </ul>
                                            <strong>Notes</strong>
                                            <p>
                                                Lorem Ipsum which looks reasonable. The generated Lorem Ipsum is therefore always free from repetition, injected humour, or non-characteristic words etc.
                                            </p>
                                            <hr>
                                            <strong>Timeline activity</strong>
                                            <div id=\"vertical-timeline\" class=\"vertical-container dark-timeline\">
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-coffee\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>Conference on the sales results for the previous year.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 2:10 pm - 12.06.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-briefcase\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>Many desktop publishing packages and web page editors now use Lorem.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 4:20 pm - 10.05.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-bolt\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>There are many variations of passages of Lorem Ipsum available.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 06:10 pm - 11.03.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon navy-bg\">
                                                        <i class=\"fa fa-warning\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>The generated Lorem Ipsum is therefore.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 02:50 pm - 03.10.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-coffee\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>Conference on the sales results for the previous year.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 2:10 pm - 12.06.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-briefcase\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>Many desktop publishing packages and web page editors now use Lorem.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 4:20 pm - 10.05.2014 </span>
                                                    </div>
                                                </div>
                                            </div>
                                        </div><div class=\"slimScrollBar\" style=\"width: 7px; position: absolute; top: 0px; opacity: 0.4; display: block; border-radius: 7px; z-index: 99; right: 1px; background: rgb(0, 0, 0);\"></div><div class=\"slimScrollRail\" style=\"width: 7px; height: 100%; position: absolute; top: 0px; display: none; border-radius: 7px; opacity: 0.2; z-index: 90; right: 1px; background: rgb(51, 51, 51);\"></div></div>
                                    </div>
                                </div>
                                <div id=\"company-3\" class=\"tab-pane\">
                                    <div class=\"m-b-lg\">
                                        <h2>Ultrices Incorporated</h2>

                                        <p>
                                            Many desktop publishing packages and web page editors now use Lorem Ipsum as their default model text.
                                        </p>
                                        <div>
                                            <small>Active project completion with: 72%</small>
                                            <div class=\"progress progress-mini\">
                                                <div style=\"width: 72%;\" class=\"progress-bar\"></div>
                                            </div>
                                        </div>
                                    </div>
                                    <div class=\"client-detail\">
                                        <div class=\"slimScrollDiv\" style=\"position: relative; overflow: hidden; width: auto; height: 100%;\"><div class=\"full-height-scroll\" style=\"overflow: hidden; width: auto; height: 100%;\">

                                            <strong>Last activity</strong>

                                            <ul class=\"list-group clear-list\">
                                                <li class=\"list-group-item fist-item\">
                                                    <span class=\"pull-right\"> <span class=\"label label-danger\">BLOCKED</span> </span>
                                                    Hidden in the middle of text
                                                </li>
                                                <li class=\"list-group-item\">
                                                    <span class=\"pull-right\"><span class=\"label label-primary\">NEW</span> </span>
                                                    Non-characteristic words etc.
                                                </li>
                                                <li class=\"list-group-item\">
                                                    <span class=\"pull-right\">  <span class=\"label label-warning\">WAITING</span> </span>
                                                    Bonorum et Malorum
                                                </li>
                                            </ul>
                                            <strong>Notes</strong>
                                            <p>
                                                There are many variations of passages of Lorem Ipsum available, but the majority have suffered alteration in some form, by injected humour.
                                            </p>
                                            <hr>
                                            <strong>Timeline activity</strong>
                                            <div id=\"vertical-timeline\" class=\"vertical-container dark-timeline\">
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-briefcase\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>Many desktop publishing packages and web page editors now use Lorem.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 4:20 pm - 10.05.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-bolt\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>There are many variations of passages of Lorem Ipsum available.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 06:10 pm - 11.03.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon navy-bg\">
                                                        <i class=\"fa fa-warning\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>The generated Lorem Ipsum is therefore.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 02:50 pm - 03.10.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-coffee\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>Conference on the sales results for the previous year.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 2:10 pm - 12.06.2014 </span>
                                                    </div>
                                                </div>
                                                <div class=\"vertical-timeline-block\">
                                                    <div class=\"vertical-timeline-icon gray-bg\">
                                                        <i class=\"fa fa-briefcase\"></i>
                                                    </div>
                                                    <div class=\"vertical-timeline-content\">
                                                        <p>Many desktop publishing packages and web page editors now use Lorem.
                                                        </p>
                                                        <span class=\"vertical-date small text-muted\"> 4:20 pm - 10.05.2014 </span>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                       <div class=\"slimScrollBar\" style=\"width: 7px; position: absolute; top: 0px; opacity: 0.4; display: block; border-radius: 7px; z-index: 99; right: 1px; background: rgb(0, 0, 0);\">
                                       </div>
                                       <div class=\"slimScrollRail\" style=\"width: 7px; height: 100%; position: absolute; top: 0px; display: none; border-radius: 7px; opacity: 0.2; z-ndex: 90; right: 1px; background: rgb(51, 51, 51);\">
                                       </div>
                                       </div>
                                    </div>
                                </div>
          $TailRemesa  ";	
}// fin de function


?>