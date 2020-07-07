<?php
/*********************************************************************
 * 
 * Funcion : construyeDropzones
 * Objetivo: Construir los los Dropzones y las funciones 
 *           de operacion JS
 * Parametros
 * $Configuracion:  Viene una cadena
 *              Arreglo de datos de ancabezado que tiene 
 *               lo siguiente:
 *                CERO  Año del periodo
 *                UNO   Quincena a entregar
 *                DOS   Fecha Limite de entrega de Info
 *                TRES  Numero Max de Quincenas
 *                CUATRO Fecha Lim. de Ultima quincena
 *               
 *               SECCION II Tipos de Archivos Autorizados
 *                  1  Archivos X00  
 *                  2  Archivos 416  
 *                  3  Archivos 610    
 **********************************************************************/
function construyeDropzones($ConfiguracionPanels){
date_default_timezone_set('America/Mexico_City');
$FechaProceso = date("d-m-Y");
$HoraProceso = date("H:i:s");
$FechaProcesoTS = date("Ymd");
$HoraProcesoTS = date("His");

$DropZones="";
$DropZonesActions="";
$DatosConfig = explode("|", $ConfiguracionPanels);
$DatosQuincena = explode("@",$DatosConfig[CERO]);


$NumCampos = count($DatosConfig);
  for($Contador = UNO; $Contador < $NumCampos - UNO; $Contador++){
            $TiposArchivos = $DatosConfig[$Contador];
            $DatosTipoArchivo = explode("@", $TiposArchivos);
            $TipoArchivo = $DatosTipoArchivo[CERO];
            $Descripcion = $DatosTipoArchivo[UNO];
            $Estatus     = $DatosTipoArchivo[DOS];
            $FechaStage  = $DatosTipoArchivo[TRES];
            $NombreForma = "my-awesome-dropzone_". 
                                strtolower(str_replace(" ", "_", $Descripcion));
            $DescripcionBoton= strtolower(str_replace(" ", "_", $Descripcion));


            // Identificador Unico de Intentos de Envio de remesa
            $IdTS = $_SESSION['idorg'].$DatosQuincena[CERO].$DatosQuincena[UNO].
                      $FechaProcesoTS.$HoraProcesoTS.$TipoArchivo;


                    
            if($Estatus != "K" and $Estatus != "P"){
            $DropZones .= "
                        /**
                            Objeto myDropzone$TipoArchivo
                            Se encarga de subir los archivo de nomina tipo $Descripcion
                            Fecha : $FechaProceso $HoraProceso
                            Autor : Secretaria de Salud
                        **/

                        var myDropzone$TipoArchivo = new Dropzone(\"form#$NombreForma\",
                        { 
                            uploadMultiple: false,
                            headers: { \"TIPOA\": \"$TipoArchivo\" },
                            params: {\"TRYSEND\": \"$IdTS\"},
                            thumbnailWidth: 40,
                            thumbnailHeight: 40,
                            parallelUploads: 20,
                            maxFilesize: 256,
                            autoProcessQueue: false,
                            init: function(){
                                this.on(\"error\", function(file, responseText) {
                                        alert('error >'+responseText );
                                        //alert(responseText);
                                });
                                this.on(\"addedfile\", function(file) {
                                       // alert(file.name );
                                        //$(\"#enviar1\").prop( \"disabled\", false );
                                            //alert(responseText);
                                });
                                this.on(\"success\", function(file, responseText) {
                                       
                                        $('#myModal4').modal('hide');
                                   //alert(\"success >\" + responseText +\"<\");
                                            //alert(responseText);
                                   $('#$DescripcionBoton').html(responseText); 
                                });
                                this.on(\"complete\", function(file, responseText) {
                                        //alert(file.name + 'tam >' + file.size +'<') ;
                                        //    alert(responseText);
                                 });
                                    
                                 this.on(\"successmultiple\", function(file, responseText) {
                                        //alert(file.name + 'tam >' + file.size +'<') ;
                                        //    alert(responseText);
                                 });
   

                            }
                           });  // fin de myDropzone$TipoArchivo     ";


                 $DropZonesActions .=  "
                                /**
                                    Control de DropZone $Descripcion

                                **/

                                $('#clear-dropzone_$DescripcionBoton').click(function(){
                                  alert(myDropzone$TipoArchivo.options.maxFilesize);  
                                  myDropzone$TipoArchivo.removeAllFiles(true);
                                });
                                                                               
                                $('#enviar_$DescripcionBoton').click(function(){
                                   $('#myModal4').modal('show');
                                   myDropzone$TipoArchivo.processQueue();
                                });
                                ";
         }// if($Estatus=="K")                      

  }// fin for
  return $DropZones.$DropZonesActions;
} // fin de construyeDropzones


/*********************************************************************
 * 
 * Funcion : construyeTipoPanel
 * Objetivo: Construir los tipos de paneles
 *           
 * Parametros
 * $TipoPanel:  Determina si va a ser Panel de Carga "E" o ""
 * $Icono    :  Icno a Utilizar
 * $TipoArchivo: 1,2,3 
 *                  1  Archivos X00  
 *                  2  Archivos 416  
 *                  3  Archivos 610    
 * $Descripcion: Descriptivo del tipo de archivo(arriba)
 * $FechaLim   : Fecha limite en que el envio de archivos Cierra
 * $IdPanel    : Identificador asigando a cada panel
 * $HeaderArray: Encabezado con los siguientes datos
 *                CERO  Año del periodo
 *                UNO   Quincena a entregar
 *                DOS   Fecha Limite de entrega de Info
 *                TRES  Numero Max de Quincenas
 *                CUATRO Fecha Lim. de Ultima quincena
 *
 **********************************************************************/

function construyeTipoPanel($TipoPanel,$Icono,$TipoArchivo,$Descripcion,$FechaStage,$FechaLim,$IdPanel,$HeaderArray ){

$StrValidacion ="?tipo_archivo=".urlencode($TipoArchivo) ."&anio=".
                  urlencode($HeaderArray[CERO])."&quincena=".urlencode($HeaderArray[UNO]).
                    "&idpanel=".urlencode($IdPanel);

$Anio = $HeaderArray[CERO];                    
$Archivos="";
$TituloPanel ="<div class=\"col-lg-12\" id=\"productos-nomina-$IdPanel\">
                    <div class=\"ibox float-e-margins\">
                      <div class=\"ibox-title animated bounceIn\">
                        <h5>
                            <i class=\"fa $Icono fa-2x\" style=\"color: #1ab394;\"></i>
                            Integración de Productos de Nómina $Descripcion
                        </h5>
                        <div class=\"ibox-tools\">
                            Fecha Limite de entrega: $FechaLim
                            <a class=\"collapse-link\">
                                <i class=\"fa fa-chevron-up\"></i>
                            </a>
                        </div>
                </div>";
$Body="";
if(($TipoPanel=="" or $TipoPanel=="E" or $TipoPanel=="F") and ($Descripcion !="ptfma_despliega_resultado")){

              $Body="  <div class=\"ibox-content animated bounceIn\" id=\"$IdPanel\">

                        <div class=\"row\" style =\" text-align:center;vertical-align:middle\">
                            <div class=\"col-sm-5 b-r\">

                            <br><br><br>
                            <i class=\"fa fa-cloud-upload fa-5x\"></i>

                                <h3 class=\"m-t-none m-b\">Área Central,Órganos  Descentralizados, Organismos Públicos  Descentralizados,Honorarios</h3>
                                

                                <form role=\"form\">
                                    <div class=\"form-group\">
                                        <label>Bases de Datos Nomina</label> 
                                        <div id=\"resumen_carga_$IdPanel\">
                                        </div>

                                    </div>
                                </form>
                            </div>

                            <div class=\"col-sm-7\" id=\"zona-de-carga\">
                            <form enctype=\"multipart/form-data\" id=\"my-awesome-dropzone_$IdPanel\" class=\"dropzone\" 
                                        action=\"pfma_validacion_archivos.php$StrValidacion\">
                                    <p>Arrastre los archivos o solo haga click</p>
                                <div class=\"dropzone-previews\">
                                </div>

                            </form>   
                              <button id=\"enviar_$IdPanel\" type\"button\"
                               class=\"btn btn-primary pull-right\">
                                  Validar</button>&nbsp;&nbsp;

                               <button id=\"clear-dropzone_$IdPanel\" type\"button\" class=\"btn btn-primary pull-right\">
                                  Limpiar</button>   

                            </div> <!-- fin de zona-de-carga -->
                        </div> <!-- fin de row -->
                    </div> <!-- fin de ibox-content x00 -->
                </div> <!-- fin de float-e-margins -->
            </div>";      
  }elseif ($TipoPanel=="K") {

              $TituloPanel ="<div class=\"col-lg-12\" id=\"productos-nomina-$IdPanel\">
                    <div class=\"ibox float-e-margins\">
                      <div class=\"ibox-title animated bounceIn\">
                        <h5>
                            <i class=\"fa $Icono fa-2x\" style=\"color: #1ab394;\"></i>
                            Proceso de Aplicación de Directivas de Calidad
                        </h5>
                        <div class=\"ibox-tools\">
                            Fecha procesamiento: $FechaLim
                            <a class=\"collapse-link\">
                                <i class=\"fa fa-chevron-up\"></i>
                            </a>
                        </div>
                </div>";


                  $Quincena = $HeaderArray[UNO];
                  $NomUsuario = $_SESSION['nombre_usuario'];
                  $IdOrg = $_SESSION['idorg'];
                  $Organizacion=$_SESSION['organismo'];
                 // $Procesos= obtenProcesosPlanificadosV2($IdOrg,$Quincena,$Anio,$TipoArchivo);

                  $NumArchivos = count($HeaderArray);

                    //echo "NumArchivos >" . $NumArchivos . "< <br>";
                  //print_r($HeaderArray);
                  
                    for($Ind=$NumArchivos-2;$Ind < $NumArchivos; $Ind++){

                        $PathParse = explode("|", $HeaderArray[$Ind]);
                        $TotalErrores=$PathParse[UNO];
                        $PathArchError= $PathParse[CERO];
                        $NombreArchivoAux = explode("/", $PathParse[CERO]);
                        $NombreArchivo = "";
                        if(isset($NombreArchivoAux[DOS]))
                          $NombreArchivo = $NombreArchivoAux[DOS];

                        $NombreArchivo = substr($NombreArchivo, 14,30);
                        $Archivos .= " 
                          <dt>$NombreArchivo :</dt> <dd> 
                        <a id=\"view-resultado-$TipoArchivo\"  download
                                  class=\"btn btn-outline btn-default view-pdf\" href=\"$PathArchError\">
                                   <i class=\"fa fa-file-archive-o fa-2x\"></i>
                                              $TotalErrores Errores 
                                       </a> 
                                              </dd>"
                                       ;
                    }
                     // fin del for    

                    $HeaderDiv= "<div class=\"ibox-content \" id=\"$IdPanel\">";
                    $TailDiv= "</div>";
                    /**
                    if($Icono==""){
                        $HeaderDiv= "";
                        $TailDiv= "";
                        $TituloPanel="";
                        $Descripcion= ucfirst($IdPanel) ;
                    }
**/

                  $TotalProcesados = $NumArchivos-DOS;
                  $Body=" $HeaderDiv
                            <div class=\"row\">
                                <div class=\"col-lg-10\">
                                    <div class=\"m-b-md\">
                                        <a href=\"#\" class=\"btn btn-danger btn-xs pull-right\">
                                        <i class=\"fa fa-exclamation-triangle fa-5x\"></i></a>
                                        <h2>Resultado de Validación de Datos</h2>
                                    </div>
                                    <dl class=\"dl-horizontal\">
                                        <dt>Estatus:</dt> <dd>
                                        <span class=\"label label-warning2\">
                                        Prevención </span></dd>
                                    </dl>
                                </div>
                            </div>

                            <div class=\"row\">
                                <div class=\"col-lg-6\">
                                    <dl class=\"dl-horizontal\">
                                        <dt>Organismo:</dt> <dd>$Organizacion</dd>
                                        <dt>Tipo Archivo:</dt> <dd>$TipoArchivo</dd>
                                        <dt>Quincena:</dt> <dd>   $Quincena </dd>
                                        <dt>Enviada por:</dt> <dd><a href=\"#\" class=\"text-navy\"> $NomUsuario</a> </dd>
                                        <dt>Fecha Envio:</dt> <dd>  $FechaStage </dd>
                                    </dl>
                                </div>
                                <div class=\"col-lg-6\" id=\"cluster_info\">
                                    <dl class=\"dl-horizontal\">

                                        <dt>A.Procesados:</dt> <dd>  $TotalProcesados </dd>
                                        

                                              $Archivos

                                        
                                    </dl>
                                </div>
                            </div>

                            <div class=\"row\">
                                <div class=\"col-lg-12\">
                                    <dl class=\"dl-horizontal\">
                                        <dt>Resultado:</dt>
                                        <dd>
                                        <div class=\"progress progress-striped active m-b-sm\">
                                    <div id=\"barravalidacion\" style=\"width: 100%;\" class=\"progress-bar progress-bar-warning\"></div>
                                            </div>
                                            <small>Análisis de datos <strong>100%</strong>. Validación de Directivas de Calidad <strong>100%</strong>.</small>
                                        </dd>
                                    </dl>
                                </div>
                            </div>


</div> <!-- fin de panle -->

            $TailDiv ";      


  }elseif ($TipoPanel=="P") {
                  //archysapiens



                  $Quincena = $HeaderArray[UNO];
                  $NomUsuario = $_SESSION['nombre_usuario'];
                  $IdOrg = $_SESSION['idorg'];
                  $Procesos= obtenProcesosPlanificadosV2($IdOrg,$Quincena,$Anio,$TipoArchivo);

                  $NumArchivos = count($Procesos);

                    //echo "NumArchivos >" . $NumArchivos . "< <br>";
                    for($Ind=CERO;$Ind < $NumArchivos; $Ind++){
                    $PathParse = explode("/", $Procesos[$Ind]['archivo_procesado']);
                    $NombreArchivo = $PathParse[DOS];
                    $NombreArchivo = substr($NombreArchivo, 14,30);
                    $Archivos .= " <a id=\"view-pdf\" 
                                      class=\"btn btn-outline btn-default view-pdf\" href=\"#\">
                                          <i class=\"fa fa-file-archive-o fa-2x\"></i>
                                          $NombreArchivo 
                                   </a> ";
                    }// fin del for    

                    $HeaderDiv= "<div class=\"ibox-content animated bounceIn\" id=\"$IdPanel\">";
                    $TailDiv= "</div>";
                    if($Icono==""){
                        $HeaderDiv= "";
                        $TailDiv= "";
                        $TituloPanel="";
                        $Descripcion= ucfirst($IdPanel) ;
                    }



                  $Body=" $HeaderDiv
                            <div class=\"row\">
                                <div class=\"col-lg-12\">
                                    <div class=\"m-b-md\">
                                        <a href=\"#\" class=\"btn btn-white btn-xs pull-right\">
                                        <i class=\"fa fa-clock-o fa-5x\"></i></a>
                                        <h2>Inicia el Proceso de Validación de Información</h2>
                                    </div>
                                    <dl class=\"dl-horizontal\">
                                        <dt>Estatus:</dt> <dd>
                                        <span class=\"label label-success-ssa\">Aplicando Directivas de Calidad</span></dd>
                                    </dl>
                                </div>
                            </div>

                            <div class=\"row\">
                                <div class=\"col-lg-5\">
                                    <dl class=\"dl-horizontal\">

                                        <dt>Tipo Archivo:</dt> <dd>$Descripcion</dd>
                                        <dt>Quincena:</dt> <dd>   $Quincena </dd>
                                        <dt>Enviada por:</dt> <dd><a href=\"#\" class=\"text-navy\"> $NomUsuario</a> </dd>
                                        <dt>Registros:</dt> <dd>  En proceso </dd>
                                        <dt>Detalle:</dt> <dd>  En proceso </dd>
                                    </dl>
                                </div>
                                <div class=\"col-lg-7\" id=\"cluster_info\">
                                    <dl class=\"dl-horizontal\">

                                        <dt>Fecha Envio:</dt> <dd>$FechaStage</dd>
                                        <dt>Percepciones:</dt> <dd>  En proceso </dd>
                                        <dt>Deducciones:</dt> <dd>  En proceso </dd>
                                        <dt>Complementarios:</dt>
                                        <dd class=\"project-people\">

                                              $Archivos

                                        </dd>
                                    </dl>
                                </div>
                            </div>

                            <div class=\"row\">
                                <div class=\"col-lg-12\">
                                    <dl class=\"dl-horizontal\">
                                        <dt>Avance:</dt>
                                        <dd>
                                        <div class=\"progress progress-striped active m-b-sm\">
                                    <div id=\"barravalidacion\" style=\"width: 10%;\" class=\"progress-bar progress-bar-info\"></div>
                                            </div>
                                            <small>Análisis de datos <strong>0%</strong>. Validación de Directivas de Calidad <strong>0%</strong>.</small>
                                        </dd>
                                    </dl>
                                </div>
                            </div>


</div> <!-- fin de panle -->
            $TailDiv ";      

  }elseif ($TipoPanel=="E" and $Descripcion =="ptfma_despliega_resultado"){
    // Seccion que crea el panel despues de haber realizado la validacion
    // llega a travez de la secciond enotificación

              $TituloPanel ="<div class=\"col-lg-12\" id=\"productos-nomina-$IdPanel\">
                    <div class=\"ibox float-e-margins\">
                      <div class=\"ibox-title animated bounceIn\">
                        <h5>
                            <i class=\"fa $Icono fa-2x\" style=\"color: #1ab394;\"></i>
                            Proceso de Aplicación de Directivas de Calidad
                        </h5>
                        <div class=\"ibox-tools\">
                            Fecha procesamiento: $FechaLim
                            <a class=\"collapse-link\">
                                <i class=\"fa fa-chevron-up\"></i>
                            </a>
                        </div>
                </div>";


                  $Quincena = $HeaderArray[UNO];
                  $NomUsuario = $_SESSION['nombre_usuario'];
                  $IdOrg = $_SESSION['idorg'];
                  $Organizacion=$_SESSION['organismo'];
                 // $Procesos= obtenProcesosPlanificadosV2($IdOrg,$Quincena,$Anio,$TipoArchivo);

                  $NumArchivos = count($HeaderArray);

                    //echo "NumArchivos >" . $NumArchivos . "< <br>";
                  print_r($HeaderArray);
                  
                    for($Ind=$NumArchivos-2;$Ind < $NumArchivos; $Ind++){

                        $PathParse = explode("|", $HeaderArray[$Ind]);
                        $TotalErrores=$PathParse[UNO];
                        $PathArchError= $PathParse[CERO];
                        $NombreArchivoAux = explode("/", $PathParse[CERO]);
                        $NombreArchivo = "";
                        if(isset($NombreArchivoAux[DOS]))
                          $NombreArchivo = $NombreArchivoAux[DOS];

                        $NombreArchivo = substr($NombreArchivo, 14,30);
                        $Archivos .= " 
                          <dt>$NombreArchivo :</dt> <dd> 
                        <a id=\"view-resultado-$TipoArchivo\"  download
                                  class=\"btn btn-outline btn-default view-pdf\" href=\"$PathArchError\">
                                   <i class=\"fa fa-file-archive-o fa-2x\"></i>
                                              $TotalErrores Errores 
                                       </a> 
                                              </dd>"
                                       ;
                    }
                     // fin del for    

                    $HeaderDiv= "<div class=\"ibox-content \" id=\"$IdPanel\">";
                    $TailDiv= "</div>";
                    /**
                    if($Icono==""){
                        $HeaderDiv= "";
                        $TailDiv= "";
                        $TituloPanel="";
                        $Descripcion= ucfirst($IdPanel) ;
                    }
**/

                  $TotalProcesados = $NumArchivos-DOS;
                  $Body=" $HeaderDiv
                            <div class=\"row\">
                                <div class=\"col-lg-10\">
                                    <div class=\"m-b-md\">
                                        <a href=\"#\" class=\"btn btn-danger btn-xs pull-right\">
                                        <i class=\"fa fa-exclamation-triangle fa-5x\"></i></a>
                                        <h2>Resultado de Validación de Datos</h2>
                                    </div>
                                    <dl class=\"dl-horizontal\">
                                        <dt>Estatus:</dt> <dd>
                                        <span class=\"label label-warning2\">
                                        Prevención </span></dd>
                                    </dl>
                                </div>
                            </div>

                            <div class=\"row\">
                                <div class=\"col-lg-6\">
                                    <dl class=\"dl-horizontal\">
                                        <dt>Organismo:</dt> <dd>$Organizacion</dd>
                                        <dt>Tipo Archivo:</dt> <dd>$TipoArchivo</dd>
                                        <dt>Quincena:</dt> <dd>   $Quincena </dd>
                                        <dt>Enviada por:</dt> <dd><a href=\"#\" class=\"text-navy\"> $NomUsuario</a> </dd>
                                        <dt>Fecha Envio:</dt> <dd>  $FechaStage </dd>
                                    </dl>
                                </div>
                                <div class=\"col-lg-6\" id=\"cluster_info\">
                                    <dl class=\"dl-horizontal\">

                                        <dt>A.Procesados:</dt> <dd>  $TotalProcesados </dd>
                                        

                                              $Archivos

                                        
                                    </dl>
                                </div>
                            </div>

                            <div class=\"row\">
                                <div class=\"col-lg-12\">
                                    <dl class=\"dl-horizontal\">
                                        <dt>Resultado:</dt>
                                        <dd>
                                        <div class=\"progress progress-striped active m-b-sm\">
                                    <div id=\"barravalidacion\" style=\"width: 100%;\" class=\"progress-bar progress-bar-warning\"></div>
                                            </div>
                                            <small>Análisis de datos <strong>100%</strong>. Validación de Directivas de Calidad <strong>100%</strong>.</small>
                                        </dd>
                                    </dl>
                                </div>
                            </div>


</div> <!-- fin de panle -->

            $TailDiv ";      



  } // fin del If        

  return $TituloPanel.$Body; 
} // fin de construyeTipoPanel

/************************************************
 * 
 * Funcion : construyePanelesCarga
 * Objetivo: Construir dinamicamente los paneles 
 *           de carga (X00,416 o 610).
 * Parametros
 * $ConfiguracionPanels: Arreglo de datos de ancabezado que tiene 
 *               lo siguiente:
 *                CERO  Año del periodo
 *                UNO   Quincena a entregar
 *                DOS   Fecha Limite de entrega de Info
 *                TRES  Numero Max de Quincenas
 *                CUATRO Fecha Lim. de Ultima quincena
 *               
 *               SECCION II Tipos de Archivos Autorizados
 *                  1  Archivos X00  
 *                  2  Archivos 416  
 *                  3  Archivos 610    
 *
*************************************************/
function construyePanelesCarga($ConfiguracionPanels){
 $MsgPanelesCarga="";   
 $DatosConfig = explode("|", $ConfiguracionPanels);
 $NumCampos =count($DatosConfig); 
// echo "NumCampos". $NumCampos ."<br>";
 $ArrayIconos =array(" fa-hospital-o ", " fa-user-md ", " fa-medkit ", " fa-user-md ");
 if(is_array($DatosConfig)) {
    
        $HeaderConfig =$DatosConfig[CERO];
        $HeaderArray = explode("@", $HeaderConfig);
        $Anio = $HeaderArray[CERO];
        $Qna = $HeaderArray[UNO];
        $FechaLim = $HeaderArray[DOS];
        $MaxQna = $HeaderArray[TRES];
        $MaxLim = $HeaderArray[CUATRO];
        $Panels ="";
        for($Contador = UNO; $Contador < $NumCampos - UNO; $Contador++){
            $TiposArchivos = $DatosConfig[$Contador];
            $DatosTipoArchivo = explode("@", $TiposArchivos);
//            echo "Campos de Archivo " . count($DatosTipoArchivo) . "<br>";
            $TipoArchivo = $DatosTipoArchivo[CERO];
            $Descripcion = $DatosTipoArchivo[UNO];
            $Estatus     = $DatosTipoArchivo[DOS];
            $FechaStage  = $DatosTipoArchivo[TRES];

/**            
            echo " TipoArchivo >". $TipoArchivo ."< ";
            echo " Descripcion >". $Descripcion ."< ";
            echo " Estatus >". $Estatus ."< ";
            echo " FechaStage >". $FechaStage ."< <br>";
**/
            $IdPanel = strtolower(str_replace(" ", "_", $Descripcion));
            //echo "Descripcion >".$Descripcion."< <br>";
            //echo "IdPanel >".$IdPanel."< <br>";

            $Icono = $ArrayIconos[$Contador-UNO];

            $Panels .= construyeTipoPanel($Estatus, $Icono,$TipoArchivo,$Descripcion,$FechaStage,$FechaLim,$IdPanel,$HeaderArray);
        }  // fin del for   
       $MsgPanelesCarga=$Panels ;
  }
  else{
    $MsgPanelesCarga="Sistema ptma_opcd.inc/construyePanelesCarga/$ConfiguracionPanels";  
  }  
return $MsgPanelesCarga;
}// fin de construyePanelesCarga

/************************************************
 * 
 * Funcion : construyeListaQnas
 * Objetivo: Construir dinamicamente la lista de acceso a 
 *           los procesos de carga (X00,416 o 610)
 * Parametros
 * $HeaderArray: Arreglo de datos de ancabezado que tiene 
 *               lo siguiente:
 *                CERO  Año del periodo
 *                UNO   Quincena a entregar
 *                DOS   Fecha Limite de entrega de Info
 *                TRES  Numero Max de Quincenas
 *                CUATRO Fecha Lim. de Ultima quincena
 *
*************************************************/
function construyeListaQnas($HeaderArray){
  if(is_array($HeaderArray)) {
    try{
        $Anio = $HeaderArray[CERO];
        $Qna = $HeaderArray[UNO];
        $FechaLim = $HeaderArray[DOS];
        $MaxQna = $HeaderArray[TRES];
        $MaxLim = $HeaderArray[CUATRO];
    }   catch (Exception $e) {

       $MsgconstruyeListaQnas="Excepción del Sistema: ".  $e->getMessage(). " <br>";

    }

    $HdrLista = "<li class=\"active\">
                    <a href=\"quincenaurl=$Qna&anioquincenaurl=$Anio\" id=\"Qhis\">
                        Anteriores 
                    </a>
                     </li>
                 <li class=\"divider\"></li>  ";

    $TailLista = "<li><a href=\"$Qna\"id=\"Q100\">Próximas 
                      <span class=\"label label-primary pull-right\">NEW
                      </span></a>
                    </li> ";                        

    $Contador  = $Qna;
    $BodyLista = "";
    while(($Contador <= ($Qna+1)) and (($Qna+1) <= $MaxQna)){
       $BodyLista.= "<li><a href=\"ptma_opcd.php?quincenaurl=$Contador&anioquincenaurl=$Anio\" id=\"Q$Contador\">Quincena $Contador</a></li>
                      <li class=\"divider\" style=\" background-color:#D8D8D8\"> </li> ";
       $Contador++;               
    }// fin del while
    $MsgconstruyeListaQnas=$HdrLista.$BodyLista.$TailLista;
  }
  else{
        $MsgconstruyeListaQnas= "Sistema ptma_opcd.inc/construyeListaQnas/Array";
  } // fin de if(is_array( 
  return  $MsgconstruyeListaQnas; 
} // fin de construyeListaQnas

/**
  
  Funcion : configuraSesion
  Objetivo: Requerimiento: Es necesario contar con una 
             interfaz gráfica que nos permita lo     siguiente:
            Consultar en las tablas organismos, usuarios, 
            archivos y privilegios, para conocer cuáles son 
            los archivos que el usuario podrá subir(X00, 416, 610, etc)
            Una vez que se tengan los tipos de archivos autorizados a subir, se debe verificar en que estatus se encuentran, ya que pueden haber sido reportados como erróneos y aun no se validan o pueden estar validados, de ahí que el panel de control se auto configura.
            Ejemplo:
            Usuario debe entregar archivos X00 y 416
            Tendrá dos paneles de carga
            Se valida que cada tipo de archivo haya realizado operaciones de validación.
            Caso I Nueva Validación
            El usuario No ha intentado validar archivos, por lo que aparece el panel libre.
            Caso II Error en validación
            Se muestra habilitado el panel de carga con la indicación que ya tiene una validación previa y el panel disponible.
            Caso III EL usuario ha validado sin errores
            El usuario realizo la validación de sus archivos, posiblemente tuvo errores y al final valido su información y esta ok
            Caso IV Al usuario le hicieron algunas recomendaciones
            El usuario realizo la validación de sus archivos, posiblemente tuvo errores y le han solicitado nuevamente suba la información, con las indicaciones aplicadas y la información actualizada.
 PARAMETROS
 $quincenaurl, Cuando se seleciona alguna quincena en especifico           

**/
function configuraSesion($QuincenaUrl,$AnioQuincenaUrl)
{
$Usuario="";
if(isset($_SESSION['inputUsuario']))
    $Usuario=$_SESSION['inputUsuario'];
$Passwd="";
if(isset($_SESSION['inputPassword']))
    $Passwd=$_SESSION['inputPassword'];
$IdOrg="";
if(isset($_SESSION['idorg']))
    $IdOrg=$_SESSION['idorg'];
$Organismo="";
if(isset($_SESSION['organismo']))
    $Organismo=$_SESSION['organismo'];

$NombreUsuario="";
if(isset($_SESSION['nombre_usuario']))
    $NombreUsuario=$_SESSION['nombre_usuario'];

$DatosConfig="XXX";
$db = new DbCnnx();    

if( ($QuincenaUrl !="") and (is_numeric($QuincenaUrl)) and (is_numeric($AnioQuincenaUrl)) ){
            $SQLPeriodo ="SELECT MIN(anio) AS anio,
                        MIN(numero) AS num_quincena,MIN(fecha_envio) AS fecha_limite,
                        MAX(numero) as max_quincena, MAX(fecha_envio) as max_limite
                        FROM periodos
                        WHERE numero >= ".$QuincenaUrl . " and anio=".$AnioQuincenaUrl;
}else{
            $SQLPeriodo ="SELECT MIN(anio) AS anio,
                        MIN(numero) AS num_quincena,MIN(fecha_envio) AS fecha_limite,
                        MAX(numero) as max_quincena, MAX(fecha_envio) as max_limite
                        FROM periodos
                        WHERE fecha_envio > CURDATE()";
}// fin de if($quincenaurl !="")

//echo "configuraSesion SQL>". $SQLPeriodo ."< <br>";

$rows = $db->select($SQLPeriodo);
//echo "Error >". $db->error() ."< <br>";
$Contador=  CERO;
$Anio="";
$NumQna="";
$FecLim="";
//print_r ($rows);
if(!is_array($rows)){
   // $DatosConfig.= "Error en la definicion de periodos <br>";
    $DatosConfig="X";
   // echo "DatosConfig=DatosConfig <br>";
}    
else
{
      //  echo "Antes del while Contador >$Contador< <br>";
        while(isset($rows[$Contador]['anio']))
        {
            $Anio = $rows[$Contador]['anio'];
            $NumQna = $rows[$Contador]['num_quincena'];
            $FecLim = $rows[$Contador]['fecha_limite'];
            $MaxQna = $rows[$Contador]['max_quincena'];
            $MaxLim = $rows[$Contador]['max_limite'];
            $Contador++;
        }// fin de while

        $Header=$Anio."@".$NumQna."@".$FecLim."@".$MaxQna."@".$MaxLim;
        if((strlen($Anio) >CERO) and (strlen($NumQna) >CERO) and (strlen($FecLim) >CERO)){
            $IdOrg = $db->quote($IdOrg);
            $SQLRemesas ="SELECT rem.id,rem.fecha_asignacion,rem.fecha_actualizacion,
                            rem.id_organismos,rem.estatus,rem.id_archivos,rem.anio_periodos,
                            rem.numero_periodos, arc.descripcion
                            FROM remesas rem, archivos arc
                            WHERE rem.id_archivos=arc.id AND 
                            rem.anio_periodos=".$Anio."  
                            AND rem.numero_periodos=".$NumQna.
                            " AND rem.id_organismos=".$IdOrg;     
            //echo "<br> SQLRemesas >$SQLRemesas< <br>";                
            $RowsRmsas = $db->select($SQLRemesas);
            $Contador=  CERO;
            if(!$RowsRmsas)
                //$DatosConfig.="Error en las Remesas <br>";
                $DatosConfig="XX";
            else{
                    while(isset($RowsRmsas[$Contador]['id']))  {
                        $IdRmsa = $RowsRmsas[$Contador]['id'];                            
                        $IdOrg = $RowsRmsas[$Contador]['id_organismos'];
                        $IdArvos = $RowsRmsas[$Contador]['id_archivos'];
                        $DescArvos = $RowsRmsas[$Contador]['descripcion'];
                        
                        $SQLBitacora= "SELECT  id_remesas,
                                    DATE_FORMAT(MAX(fecha_evento), '%d-%m-%Y %H:%i:%s') as fecha
                                    ,estatus 
                                    FROM bitacora
                                    where  id_remesas=".$IdRmsa.
                                   "  GROUP BY id_remesas, estatus
                                    ORDER BY fecha_evento DESC";
                      //  $DatosConfig .=            $SQLBitacora ."<br>";
                        $RowsBit = $db->select($SQLBitacora) ;
                        $IdRmsaBit  = "";
                        $FechaStage = "";
                        $Estatus    = "";
                        if(isset($RowsBit[CERO]['id_remesas']))
                            $IdRmsaBit  = $RowsBit[CERO]['id_remesas'];
                        if(isset($RowsBit[CERO]['fecha']))
                            $FechaStage = $RowsBit[CERO]['fecha'];
                        if(isset($RowsBit[CERO]['estatus']))
                            $Estatus    = $RowsBit[CERO]['estatus'];
                        $DatosConfig =$DatosConfig. $IdArvos."@".$DescArvos."@".$Estatus. "@". $FechaStage."|";
                        if($Contador == CERO)
                            $DatosConfig =$Header."|".$IdArvos."@".$DescArvos."@".$Estatus."@".$FechaStage."|";
                        $Contador++;
                    }// fin del while remesas    
            } // fin de if(!$RowsRmsas)
        } // fin de if((strlen($Anio) >CERO) a    
} // fin de if(!$rows) Periodos               
//echo "return >".$DatosConfig. "< <br>";    
return $DatosConfig;    

} // fin de configuraSesion.



/**
  
  Funcion : obtenResultadosValidacion
  Objetivo: Elaborar la presentacion de 
            resultados obtenidos despues del 
            proceso de validacion 
  

**/

function obtenResultadosValidacion($TipoNomina, $Estatus,$ArrArchivos, $ArrRpteValidacion, 
    $ArchivoErr, $NumRegAna)
{
    date_default_timezone_set('America/Mexico_City');
    $FechaProceso = date("d-m-Y");
    $HoraProceso = date("H:i:s");
    $Organismo= $_SESSION['organismo'] ;
    $Icono = "<i class=\"fa fa-warning fa-5x\" style=\"color:#F00404\"></i>";

    $Estat = "<span class=\"label label-primary\" 
               style=\"background-color: #F00404;\">Error</span>
                            ";
    $Archivos ="";                        

    $NumArchivos = count($ArrArchivos);

    //echo "NumArchivos >" . $NumArchivos . "< <br>";
    for($Ind=CERO;$Ind < $NumArchivos; $Ind++){
        $PathParse = explode("/", $ArrArchivos[$Ind]['archivo_procesado']);
        $NombreArchivo = $PathParse[DOS];
        $NombreArchivo = substr($NombreArchivo, 14,30);
        $Archivos .="<dd>".  $NombreArchivo . "</dd>";         
    }// fin del for    


$BtonSubir=" <div style=\" text-align:center;vertical-align:middle\">
            <button id=\"cargaotravez\" class=\"btn btn-warning btn-lg \" type=\"button\">
                <i id=\"cargaotravezicon\" class=\"fa fa-upload\">
                </i>&nbsp;&nbsp;
            <span id=\"cargaotravezspan\" class=\"bold\">Subir</span></button>
            </div>
                ";

$ReporteAnalisis =    "
                            <div class=\"row alert alert-info\">
                                <div class=\"col-xs-4\">
                                    <i class=\"fa fa-files-o fa-3x\" ></i>
                                </div>
                                <div class=\"col-xs-8 text-right\">
                                    Se recibieron $NumArchivos archivos de Nómina. 
                                </div>
                            </div>


                            <div class=\"row alert alert-success\">
                                <div class=\"col-xs-4\">
                                    <i class=\"fa fa-gears fa-3x\" ></i>
                                </div>
                                <div class=\"col-xs-8 text-right\">
                                    Se Analizan $NumArchivos archivos de Nómina. 
                                </div>
                            </div>

                            <div class=\"row alert alert-danger\">
                                <div class=\"col-xs-4\">
                                    <i class=\"fa fa-times-circle fa-3x\" ></i>
                                </div>
                                <div class=\"col-xs-8 text-right\">
                                   Después del análisis,  se detectaron $NumRegAna <a href=\"$ArchivoErr\" download> Errores.</a> 
                                </div>
                            </div>
                      ";


if ($Estatus == EXITO){
    $Icono = "<i class=\"fa fa-check-circle-o fa-5x\" style=\"color:#1ab394\"></i>";
    $Estat = "<span class=\"label label-primary\" 
            style=\"background-color: #1ab394;\">Correcto</span>";
    $ReporteAnalisis = "
                            <div class=\"row alert alert-info\">
                                <div class=\"col-xs-4\">
                                    <i class=\"fa fa-files-o fa-3x\" ></i>
                                </div>
                                <div class=\"col-xs-8 text-right\">
                                    Se recibieron $NumArchivos  archivos de Nómina. 
                                </div>
                            </div>


                            <div class=\"row alert alert-success\">
                                <div class=\"col-xs-4\">
                                    <i class=\"fa fa-gears fa-3x\" ></i>
                                </div>
                                <div class=\"col-xs-8 text-right\">
                                    Se recibieron $NumArchivos  archivos de Nómina. 
                                </div>
                            </div>             ";

     $BtonSubir = "";                   

}// fin de if ($Estatus == EXITO)    
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
                                    <dt>Entidad:</dt> <dd><strong>$Organismo</strong></dd>
                                    <dt>Fecha Validacion:</dt> <dd>  $FechaProceso</dd>
                                    <dt>Hora:</dt> <dd> $HoraProceso </dd>
                                    <dt>Estatus:</dt> <dd>
                                                    $Estat </dd>
                                    
                                    <dt>Archivos a Analizar:</dt> $Archivos

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


/*************************************************************
* 
*  Funcion : obtenProcesosPlanificadosV2
*  Objetivo: Obtiene los archivos que estan por planificarse
*            
*  Fecha   : 16-May-2016
*  Autor   : Archy Sapiens
*
*  Parametros
*   $IdPlanificacion : Identificación de la remesa
*  Valor de regreso : Vector con archivos
*
***************************************************************/   

function obtenProcesosPlanificadosV2($IdOrg, $Qna, $Anio, $TipoArchivo){
    $db = new DbCnnx();   
    $SQL= "SELECT  rem.id, rem.fecha_asignacion,
              rem.anio_periodos, rem.numero_periodos,rem.id_usuarios,
              bita.archivo_procesado
            FROM remesas rem, bitacora bita
            WHERE rem.id=bita.id_remesas AND 
            anio_periodos=$Anio AND
            numero_periodos=$Qna AND
            id_organismos='$IdOrg' AND bita.estatus='P' and
             id_archivos=$TipoArchivo";

    $Rows = $db->select($SQL);
    if(!$Rows){
        echo "<br>pfma_validacion_archivos.inc/obtenProcesosPlanificadosV2/No existe Remesa autorizada <br>";
    }   
    else{   
        return $Rows;
    }// fin de if
}// fin de obtenProcesosPlanificadosV2



/*********************************************************************
 * 
 * Funcion : fncBuildRow1
 * Objetivo: Construir los renglones osecciones  a mostrar
 *           
 * Parametros
 * $Qna:  Quincena Procesada
 * $FechaLim    :  Fecha Limite de recepcion de Archivos
 * $PanlesCarga: Paneles de carga a mostrar
 *
 **********************************************************************/

function fncBuildRow1($Qna, $FechaLim, $PanlesCarga){

$Organismo = $_SESSION['organismo'];
$IdOrg =$_SESSION['idorg'];

$Resultados = ""; 


//obtenResultadosValidacion(416,0,$ArrArchivo,$ArrResultados,"archivo1.txt",0);

	return "
    <div class=\"row wrapper border-bottom white-bg page-heading\">
                <div class=\"col-lg-10\">
                    <ol class=\"breadcrumb\" style=\"padding-top:15px;\">
                        <li>
                            <a href=\"#\">Bienvenido</a>
                        </li>
                        <li class=\"active\">
                            <strong>Alta Usuario</strong>
                        </li>
                    </ol>
                </div>
            </div>

    <div class=\"wrapper wrapper-content animated bounceIn\" id=\"main_page\">
	    <div class=\"row\">
			<div class=\"col-lg-12\">
				<div class=\"ibox float-e-margins\">
					<div class=\"ibox-title\">
						<h5>Agregar Nuevo Usuario <span class=\"glyphicon glyphicon-user\"></span></h5>
						<div class=\"ibox-tools\">
							<a class=\"collapse-link\">
								<i class=\"fa fa-chevron-up\"></i>
							</a>
							<a class=\"close-link\">
								<i class=\"fa fa-times\"></i>
							</a>
						</div>
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
										<li role=\"presentation\" >
											<a href=\"#contacto\" data-toggle=\"tab\" aria-controls=\"contacto\" role=\"tab\" title=\"Contacto\">
												<span class=\"round-tabs two\">
												<i class=\"glyphicon glyphicon-phone-alt\"></i>
												</span> 
											</a>
										</li>
										<li role=\"presentation\" >
											<a href=\"#organismo\" data-toggle=\"tab\" aria-controls=\"organismo\" role=\"tab\" title=\"Organismo\">
												<span class=\"round-tabs three\">
												<i class=\"glyphicon glyphicon-th-list\"></i>
												</span> 
											</a>
										</li>
										 <li role=\"presentation\" >
											<a href=\"#credencial\" data-toggle=\"tab\" aria-controls=\"credencial\" role=\"tab\" title=\"Credenciales\">
												<span class=\"round-tabs four\">
												<i class=\"glyphicon glyphicon-pencil\"></i>
												</span> 
											</a>
										 </li>
										
									</ul>
								</div>
								<div class=\"tab-content\">
									<div class=\"tab-pane fade in active\" role=\"tabpanel\" id=\"personal\">
										<h3 class=\"head text-center\"></h3><br>
										<p class=\"text-danger pull-left\">(*) Campos obligatorios.</p><br><br>
										<div class=\"col-sm-4 col-sm-offset-2 b-r\">
											<form role=\"form\" action=\"\" method=\"post\" enctype=\"multipart/form-data\">
												<div class=\"form-group\"><label>* Nombre</label> <input type=\"text\" placeholder=\"Pedro\" name=\"txt_nombre\" class=\"form-control text-capitalize\" required></div>
												<div class=\"form-group\"><label>* Apellido Paterno</label> <input type=\"text\" placeholder=\"Perez\" name=\"txt_app_p\" class=\"form-control text-capitalize\" required></div>
												<div class=\"form-group\"><label>* Apellido Materno</label> <input type=\"text\" placeholder=\"Perez\" name=\"txt_app_m\" class=\"form-control text-capitalize\" required></div>
												<div class=\"form-group\"><label>*Sexo</label><div class=\"i-checks\"><label><input type=\"radio\" value=\"Masculino\" name=\"sexo\" checked> <i></i> Masculino </label>&nbsp; &nbsp; <label><input type=\"radio\" value=\"Femenino\" name=\"sexo\"> <i></i> Femenino</label></div></div>
												<div class=\"form-group\"><label>Edad</label> 
												<div class=\"input-group spinner\">
													<input type=\"text\" class=\"form-control\" name=\"txt_edad\" value=\"18\" min=\"1\" max=\"100\">
													<div class=\"input-group-btn-vertical\">
													  <button class=\"btn btn-default\" type=\"button\"><i class=\"fa fa-caret-up\"></i></button>
													  <button class=\"btn btn-default\" type=\"button\"><i class=\"fa fa-caret-down\"></i></button>
													</div>
												</div></div>
												<div class=\"form-group\" id=\"data_1\">
													<label >Fecha de Nacimiento</label>
													<div class=\"input-group date\">
														<span class=\"input-group-addon\"><i class=\"fa fa-calendar\"></i></span><input type=\"text\" class=\"form-control\" name=\"txt_fech_nac\" placeholder=\"08/16/2000\" value=\"08/16/2000\">
													</div>
												</div>
										</div>
										<div class=\"col-sm-4\">
											<br>
											<div class=\"form-group\"><label>* Foto de Perfil</label> 
												<div class=\"input-group image-preview\">
													<input type=\"text\" class=\"form-control image-preview-filename\" disabled=\"disabled\" PLACEHOLDER=\"Elige una Imágen\">
													<span class=\"input-group-btn\">
														<button type=\"button\" class=\"btn btn-default image-preview-clear\" style=\"display:none;\">
															<span class=\"glyphicon glyphicon-remove\"></span> Limpiar
														</button>
														<div class=\"btn btn-default image-preview-input\">
															<span class=\"glyphicon glyphicon-folder-open\"></span>
															<span class=\"image-preview-input-title\">Buscar</span>
															<input type=\"file\" accept=\"image/png, image/jpeg, image/gif\" name=\"txt_foto\" class=\"form-control\" required/>
														</div>
													</span>
												</div>
												</div>
												<div class=\"form-group\"><label>* Usuario:</label> <input type=\"text\" placeholder=\"Usuario\" name=\"txt_usuario\" class=\"form-control\"></div>
												<div class=\"form-group\"><label>* Contraseña:</label> <input type=\"password\" placeholder=\"********\" name=\"txt_psw\" class=\"form-control\"></div>
											<div style=\"margin-top:80px;\" class=\"text-center\">
											<ul class=\"list-inline pull-right\">
												<li><a href=\"#contacto\" data-toggle=\"tab\" class=\"btn btn-primary next-step\" role=\"button\" aria-pressed=\"true\"><i class=\"glyphicon glyphicon-saved\"></i>&nbsp;&nbsp;<span class=\"bold\">Guardar y continuar</span></a></li>
											</ul>
											</div>
										</div>
									</div>
									<div class=\"tab-pane fade\"  role=\"tabpanel\" id=\"contacto\">
										<h3 class=\"head text-center\"></h3><br>
										<p class=\"text-danger pull-left\">(*) Campos obligatorios.</p><br><br>
										<div class=\"col-sm-4 col-sm-offset-2 b-r\">
											
												<div class=\"form-group\"><label>* Correo </label> <input type=\"email\" placeholder=\"ejemplo@ejemplo.com\" name=\"txt_email\" class=\"form-control\" required></div>
												<div class=\"form-group\"><label>* Telefono de oficina</label><input type=\"text\" class=\"form-control\" name=\"txt_tel_ofi\" data-mask=\"(999) 999-9999\" placeholder=\"(###) ###-####\" required></div>
												<div class=\"form-group\"><label>* Extension</label><input type=\"text\" class=\"form-control\" data-mask=\"9999\" placeholder=\"###\" name=\"txt_ext\" required></div>
												<div class=\"form-group\"><label>* Telefono Personal</label><input type=\"text\" class=\"form-control\" data-mask=\"(999) 999-9999\" name=\"txt_tel_per\" placeholder=\"(###) ###-####\" required></div>	 
											
										</div>
										<div class=\"col-sm-4\">
											<div style=\"margin-top:80px;\" class=\"text-center\">
											<ul class=\"list-inline pull-right\">
												<li><a href=\"#personal\" data-toggle=\"tab\" class=\"btn btn-default prev-step\" role=\"button\" aria-pressed=\"true\"><i class=\"glyphicon glyphicon-chevron-left\"></i>&nbsp;&nbsp;<span class=\"bold\">Anterior</span></a></li>
												<li><a href=\"#organismo\" data-toggle=\"tab\" class=\"btn btn-primary next-step\" role=\"button\" aria-pressed=\"true\"><i class=\"glyphicon glyphicon-saved\"></i>&nbsp;&nbsp;<span class=\"bold\">Guardar y continuar</span></a></li>
											</ul>
											</div>
										</div>
									</div>
									<div class=\"tab-pane fade\" role=\"tabpanel\" id=\"organismo\">
										<h3 class=\"head text-center\"></h3><br>
										<p class=\"text-danger pull-left\">(*) Campos obligatorios.</p><br><br>
										<div class=\"col-sm-4 col-sm-offset-2\">
											
												<div class=\"form-group\"><label>* Organismos:  </label>
												<select name=\"txt_organismos\" class=\"select2_demo_3 form-control\" style=\"width:350px;\" required>
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
												<select name=\"txt_uni_respon\" class=\"select2_demo_3 form-control\" style=\"width:350px;\" required>
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
												<div style=\"padding-top:50px;\" class=\"pull-right\">
												<ul class=\"list-inline pull-right\">
													<li><a href=\"#contacto\" data-toggle=\"tab\" class=\"btn btn-default prev-step\" role=\"button\" aria-pressed=\"true\"><i class=\"glyphicon glyphicon-chevron-left\"></i>&nbsp;&nbsp;<span class=\"bold\">Anterior</span></a></li>
													<li><a href=\"#credencial\" data-toggle=\"tab\" class=\"btn btn-primary next-step\" role=\"button\" aria-pressed=\"true\"><i class=\"glyphicon glyphicon-saved\"></i>&nbsp;&nbsp;<span class=\"bold\">Guardar y continuar</span></a></li>
												</ul>
												</div>
											
										</div>
										
									</div>
									<div class=\"tab-pane fade\" role=\"tabpanel\" id=\"credencial\">
										<h3 class=\"head text-center\"></h3><br>
										<p class=\"text-danger pull-left\">(*) Campos obligatorios.</p><br><br>
										<div class=\"col-sm-4 col-sm-offset-2\">
											
												<div class=\"form-group\"><label >* Credenciales</label>
													<div class=\"col-sm-10\">
														<div class=\"i-checks\"><label> <input type=\"checkbox\" value=\"10\" name=\"txt_creden1\" checked> <i></i> + Producto de Nomina </label></div>
														<div class=\"i-checks\"><label> <input type=\"checkbox\"  value=\"2\" name=\"txt_creden2\"> <i></i> + Articulo 74 </label></div>
														<div class=\"i-checks\"><label> <input type=\"checkbox\" value=\"8\" name=\"txt_creden3\"> <i></i> + Articulo 74 Frac II </label></div>
														<div class=\"i-checks\"><label> <input type=\"checkbox\" value=\"9\" name=\"txt_creden4\"> <i></i> + Articulo 74 Frac III </label></div>														
													</div>
												</div>
												<div class=\"form-group\"><label>* Pregunta de Seguridad </label>
												<select name=\"txt_pregunta_seguridad\" class=\"select2_demo_3 form-control\" style=\"width:350px;\" required>
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
												<div class=\"form-group\"><label>* Respuesta </label> <input type=\"text\" placeholder=\"escribe tu respuesta\" name=\"txt_respuesta\" class=\"form-control\" required></div>										
												<div style=\"padding-top:30px;\" class=\"pull-right\">
												<ul class=\"list-inline pull-right\">
													<li><a href=\"#organismo\" data-toggle=\"tab\" class=\"btn btn-default prev-step\" role=\"button\" aria-pressed=\"true\"><i class=\"glyphicon glyphicon-chevron-left\"></i>&nbsp;&nbsp;<span class=\"bold\">Anterior</span></a></li>
													<li><button class=\"btn btn-primary\" name=\"submitConfirmarAlta\" id=\"submitConfirmarAlta\" value=\"confirmar\" type=\"submit\"><i class=\"glyphicon glyphicon-floppy-saved\"></i>&nbsp;&nbsp;<span class=\"bold\">Guardar</span></button></li>
												</ul>
												</div>
											</form>
										</div>
									</div>
									<div class=\"clearfix\"></div>
								</div>
							</div>
					</div>
				</div>
			</div>
		</div>
	</div>
	
   
   
   
    	";
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
                    <a id=\"enc-num-msgs\" class=\"dropdown-toggle count-info\" data-toggle=\"dropdown\" href=\"#\">
                        <i class=\"fa fa-bell\"></i>  
                        <span id=\"num-msgs\" class=\"label label-primary\">8</span>
                    </a>

                    <ul id=\"ul-msgs\" class=\"dropdown-menu dropdown-alerts\">
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
                        <i class=\"fa fa-sign-out\"></i> Salir
                    </a>
                </li>
                <li>
                    <a class=\"right-sidebar-toggle\">
                        <i class=\"fa fa-tasks\"></i>
                    </a>
                </li>
            </ul>

        </nav>
        </div>";
} // fin de fncBuildTopNavBar



function fncBuildJS($Welcome,$DropZones)
{

$Biemvenida = "";
$Bandera="NO asigno";
if($Welcome === "inicial"){
$Biemvenida = " setTimeout(function() {
                toastr.options = {
                    closeButton: true,
                    progressBar: true,
                    showMethod: 'slideDown',
                    timeOut: 4000
            };
            toastr.success('Dirección General de Recursos Humanos','Secretaria de Salud');
            },1200);";
$Bandera="SI asigno";
}// fin del fin

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
	
<!--
    <script src=\"//ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js\"></script>

  -->  
 
	<script>
			
            $(document).ready(function () {
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
    <script>
        $(document).ready(function() {

            $Biemvenida

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

$DropZones


</script>


<script>

$(\"body\").click(function(e){
  //archysapiens
    var IdMsgs = event.target.id;
  //alert('>' + IdMsgs+ '<  >' );
  //  alert(document.querySelector('#cargaotravez'));

  if ((e.target.id===\"cargaotravez\" )|| (e.target.id===\"cargaotravezicon\")||(e.target.id===\"cargaotravezspan\"))
   {
       // alert('a cargar otra vez ');
        //$('#x00').load(\"../ptfma_dropzone.php\");
        //window.open(\"ptma_opcd.php\");
        window.location.href = \"ptma_opcd.php\";
   }  
   
}); // 





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



		</head>";
} // fin de fncBuildHead


function fncBuildBody($ConfiguracionPanels)
{
    $ConfiguracionPanels;
    $DatosConfig = explode("|", $ConfiguracionPanels);
    $HeaderConfig =$DatosConfig[CERO];
    $HeaderArray = explode("@", $HeaderConfig);
    $Anio = $HeaderArray[CERO];
    $Qna = $HeaderArray[UNO];
    $FechaLim = $HeaderArray[DOS];
    $MaxQna = $HeaderArray[TRES];
    $MaxLim = $HeaderArray[CUATRO];


	$PrimParte = fncBuildTopNavBar();
    $PanelesCarga = construyePanelesCarga($ConfiguracionPanels);
	$Row1= fncBuildRow1($Qna, $FechaLim, $PanelesCarga);
    $ListaQuincenas = construyeListaQnas($HeaderArray);
/**
$ConfiguracionPanels <br>
$DatosConfig[0]<br>
$Anio <br>
$Qna  <br>
$FechaLim <br>
**/

	return "

<body>

<br>


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
                                <li><a href=\"../index.php\">Salir</a></li>
                            </ul>
                        </div>
                        <div class=\"logo-element\">
                            Salud
                        </div>
                    </li>
                    <li class=\"active\">
                        <a href=\"#\">
                          <i class=\"fa fa-th-large\"></i> 
                          <span class=\"nav-label\">Productos de Nómina</span> 
                          <span class=\"fa arrow\"></span></a>
                        <ul class=\"nav nav-second-level\">

                        $ListaQuincenas                        

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
					<li>
                        <a href=\"alta_user_view.php\"><i class=\"glyphicon glyphicon-user\"></i> 
                        <span class=\"nav-label\">Alta de Usuario</span></a>
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

        var mili = 7000;
        timer = setTimeout(\"tiempo()\", mili);
        function tiempo() {

            var d = new Date();
            var n = d.getTime();
            //alert('Temporalizador');
            timer = setTimeout(\"tiempo()\", mili);
            console.log('Mandando a llamar a servidor');
            var avance = $('#barravalidacion').width();
            var incremento = avance + 5;

            //alert(incremento);
            if(incremento < 400){
                console.log(incremento);
                $('#barravalidacion').width(incremento);
            }

            
           $.post(\"ptfma_obten_num_notificacion.php\", 
                { 
                    idusuario: 'John', 
                    idorganismo: '15' 
                }
                )
                .done(function( data ) {
                    console.log(\"Data Loaded: \" + data );
                    $('#num-msgs').text(data);
                });



            $.post(\"ptfma_obten_notificacion.php\", 
                { 
                    idusuario: 'John', 
                    idorganismo: '15' 
                }
                )
                .done(function( data ) {
                  //  console.log(\"Data Loaded: \" + data );
                    $('#ul-msgs').html(data);
                });

        }// fin de function tiempo()


        $('#ul-msgs').click(function(){
                //alert('click en UL');
        });   

        $('div').click(function(){
            var PattrMsgs = new RegExp(/^[0-9]{14}-[0-9]{4}/);
            var Msg = event.target.id;
            
            if(PattrMsgs.test(Msg)){
               // alert('Identificador aceptado >>'+Msg + '<<');

              $.post(\"ptfma_despliega_resultado.php\", 
                { 
                    credencial: Msg, 
                    idorganismo: '15' 
                }
                )
                .done(function( data ) {
                    var UbicacionPanel = Msg.split('-');
                    var Panel = UbicacionPanel[4];
                    //alert('panel >>'+ Panel +'<<');
                    console.log('panel >>'+ Panel +'<<');
                    switch(Panel){
                      case '1': //alert('Primer panel');
                                $('#main_page').html(data);
                                break;
                      case '2': //alert('Segundo panel');
                                $('#productos-nomina-archivos_416').html(data);
                                break;
                      case '3': //alert('Tercer panel');
                                $('#productos-nomina-archivos_610').html(data);
                                break;
                      case '4': //alert('Cuarto panel');
                                $('#productos-nomina-archivos_pdf').html(data);
                                break;
                    }// switch

                    console.log(\"Data Loaded: \" + data );
                    //$('#num-msgs').text(data);
                    //alert(data);
                    //alert('en el done >>'+Msg+'<<');

                });
          }// FIN DEL if(PattrMsgs.test(Msg))

        });

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
                    // alert('antes');
                    var varhtml ='?'+ $('#Qhis').attr('href');
                    //alert(varhtml);
                    
                    $('#main_page').load( \"ptfma_historico.php\"+ varhtml);
                    return false;
                    }
                } // fin de if( reg.test(IdQna))
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