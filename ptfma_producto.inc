<?php

function incluyeModal($Anio,$NumQna){

$FecLim ="Hoy ";
return "
<!-- inicio del modal -->


                    <div class=\"modal inmodal\" id=\"registros_error\" tabindex=\"-1\" role=\"dialog\" aria-hidden=\"true\">

                                <div class=\"modal-dialog\" style=\"width: 800px;    margin-top: 50px;\">
                                    <div class=\"modal-content animated fadeInLeftBig\">

                                        <div class=\"modal-header\">
                                            <button type=\"button\" class=\"close\" data-dismiss=\"modal\"><span aria-hidden=\"true\">&times;</span><span class=\"sr-only\">Close</span></button>
                                            <h4 id=\"modal_titulo\" class=\"modal-title\">QUINCENA  $NumQna $FecLim</h4>
                                            <small class=\"font-bold\">Productos de Nómina.</small>
                                        </div>
                                        <div class=\"modal-body\">



<!-- inicio de cuerpo -->

            <table id=\"tabla_errores\" tabindex=\"0\" cellspacing=\"0\" cellpadding=\"0\" border=\"0\" role=\"grid\" aria-multiselectable=\"false\" aria-labelledby=\"gbox_table_list_1\" class=\"ui-jqgrid-btable\" style=\"width: 935px;\">
            <tbody>

            </tbody>
            </table>
             <div id=\"pager\"></div> 
 
<!-- fin de cuerpo -->

                                        </div>
                                       
                                        <div class=\"modal-footer\">
                                            <button type=\"button\" class=\"btn btn-white\" data-dismiss=\"modal\">Cerrar</button>
                                            <button type=\"button\" class=\"btn btn-primary\">Imprimir</button>
                                        </div>
                                    </div>
                                </div>
                     </div>


<!-- fin del modal -->


";

}// fin de 



/*********************************************************************
 * 
 * Funcion : obtenUltmaEjecucion
 * Objetivo: Construir los los Dropzones y las funciones 
 *           de operacion JS
 * Parametros
 * $IdOrg:  Es el codigo del Estado con base al catalogo de la DGRH
 * $Anio   : Año del proceso
 * $Qna    : Quincena que procesa
 * $TipoArchivo : define el tipo de archivo que se procesa
 *               
 * Retorno
 * $ArrArchivos  : Forma un Arreglo con los archivos que se
 *                 procesaron 
 **********************************************************************/

function obtenUltmaEjecucion($IdOrg,$Anio, $Qna,$TipoArchivo){
  $db = new DbCnnx();  
  $SQL= "SELECT bi.fecha_evento, bi.archivo_procesado, bi.estatus, SUM(bi.total) AS total
        FROM  remesas re, archivos ar, bitacora bi 
        WHERE re.id_organismos='$IdOrg' AND re.anio_periodos=$Anio AND re.numero_periodos=$Qna
        AND re.id_archivos=ar.id AND UPPER(ar.descripcion) LIKE '%$TipoArchivo%' AND
        bi.id_remesas=re.id
        GROUP BY bi.fecha_evento, bi.archivo_procesado, bi.estatus";

$Rows = $db->select($SQL);
$FechaEvento="";
if(is_array($Rows)){
  $HeaderArray=array($Anio,$Qna );
  $Contador= CERO;
  $EstatusFinal = "K";
  $actual   = "";
  $anterior = "";
  while(isset($Rows[$Contador]['fecha_evento'])) {
      $FechaEvento = $Rows[$Contador]['fecha_evento'];
      $ArchivoProcesado = $Rows[$Contador]['archivo_procesado'];
      $Estatus = $Rows[$Contador]['estatus'];
      $Total = $Rows[$Contador]['total'];
      $actual = $FechaEvento;
      array_push($HeaderArray,$ArchivoProcesado ."|".$Total);
      if(($actual != $anterior) and ($Contador > UNO))
            break;
      if ($Estatus != "K")
          $EstatusFinal = "E";
      $anterior = $actual;
      $Contador++;
  }// fin de while
 }// fin del if 
  return $HeaderArray;
}// fin de obtenUltmaEjecucion


/*********************************************************************
 * 
 * Funcion : calculaNumArchivosRemesa
 * Objetivo: Calcular el numero de archivos en una remesa
 * Parametros
 * $Configuracion: 

 * Valor que regresa
 *  $NumArchRemesa  : Numero de archivos de la remesa           
 **********************************************************************/
function calculaNumArchivosRemesa(){
$TagEnvio ="";
if(isset($_SESSION['tagenvio']))
  $TagEnvio= $_SESSION['tagenvio'];

$IdOrg ="";
if(isset($_SESSION['idorg']))
  $IdOrg= $_SESSION['idorg'];

$ArrTagEnvio = explode("=",$TagEnvio);
$Aux1TagEnvio = $ArrTagEnvio[UNO];
$Aux2TagEnvio = str_replace(";","",str_replace("'","",$Aux1TagEnvio));
$TagEnvio=$Aux2TagEnvio;
$ArrTagEnvio = explode("-",$TagEnvio);
$AnioProceso = $ArrTagEnvio[UNO];
$QnaProceso  = $ArrTagEnvio[DOS];
$db = new DbCnnx();
$TotalArchivosRemesa= CERO;
$SQLRegistro="SELECT  COUNT(*) AS total_archivos_pn
              FROM remesas rem, logger logg
              WHERE rem.id=logg.id_remesas AND 
              id_organismos   = '$IdOrg' AND 
              id_archivos     = 5 AND
              anio_periodos   = $AnioProceso AND
              numero_periodos = $QnaProceso AND 
              tipo_archivo    = 'D' AND 
              etiqueta_envio  = '$TagEnvio' AND 
              logg.estatus NOT IN ('C','E')
              ";

$Rows = $db->select($SQLRegistro);
//echo "<br> calculaNumArchivosRemesa / SQLRegistro >>$SQLRegistro<< <br>";
if(is_array($Rows)){
  $Contador = CERO;
  if(isset($Rows[$Contador]['total_archivos_pn'])) {
    $TotalArchivosRemesa = $Rows[$Contador]['total_archivos_pn'];
  } 
} // if(is_array
return $TotalArchivosRemesa;

}//fin de calculaNumArchivosRemesa

/*********************************************************************
 * 
 * Funcion : construyeTagEnvio
 * Objetivo: Construir el tag de envio
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
function construyeTagEnvio($ConfiguracionPanels){
date_default_timezone_set('America/Mexico_City');
$FechaProceso = date("d-m-Y");
$HoraProceso = date("H:i:s");
$FechaProcesoTS = date("Ymd");
$HoraProcesoTS = date("His");
$DatosConfig = explode("|", $ConfiguracionPanels);
$DatosQuincena = explode("@",$DatosConfig[CERO]);
$AnioProc = $DatosQuincena[CERO];
$QnaProc = $DatosQuincena[UNO];

$IdOrg = $_SESSION['idorg'];
$IdTS = $_SESSION['idorg']."-".$DatosQuincena[CERO]."-".$DatosQuincena[UNO]."-".
                      $FechaProcesoTS.$HoraProcesoTS."-5";

$TagEnvio = "var TagEnvio ='$IdTS';";
  
$db = new DbCnnx();

$SQLRegistro="SELECT  logg.id_remesas, logg.etiqueta_envio
              FROM remesas rem, logger logg
              WHERE rem.id=logg.id_remesas AND 
              id_organismos='$IdOrg' AND 
              id_archivos=5 AND
              anio_periodos=$AnioProc AND
              numero_periodos=$QnaProc and logg.estatus not in ('C','E')
              ORDER BY logg.fecha_registro DESC";

//echo  "SQLRegistro >>$SQLRegistro<< <br><br>";

$Rows = $db->select($SQLRegistro);
if(is_array($Rows)){
  $Contador = CERO;
  if(isset($Rows[$Contador]['etiqueta_envio'])) {
    $TagEnvio = $Rows[$Contador]['etiqueta_envio'];
    $TagEnvio = "var TagEnvio ='$TagEnvio';";
  } 
} // if(is_array
return $TagEnvio;
} // fin de construyeTagEnvio

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

                                <h3 class=\"m-t-none m-b\">
                                Para un mejor envio de la Información. Envie un archivo .zip para los datos y un archivo .zip para el Detalle(Trail).
                                </h3>

                                

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
  }elseif ($TipoPanel=="K" and ($Descripcion == "ptfma_despliega_resultado")) {

//anchysapiens
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
                  
                    for($Ind=DOS;$Ind < $NumArchivos; $Ind++){

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
                        <a id=\"view-resultado-$TipoArchivo\"  
                                  class=\"btn btn-outline btn-primary view-pdf\" 
                                  href=\"#\">
                                   <i class=\"fa fa-file-text-o fa-2x\"></i>
                                              Archivo Validado 
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
                                        <a href=\"#\" class=\"btn btn-success btn-xs pull-right\">
                                        <i class=\"fa fa-check-circle fa-5x\"></i></a>
                                        <h2>Resultado de Validación de Datos</h2>
                                    </div>
                                    <dl class=\"dl-horizontal\">
                                        <dt>Estatus:</dt> <dd>
                                        <span class=\"label label-success-ssa\">
                                        Validado </span></dd>
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

                                        <dt>Archivos Procesados:</dt> <dd>
                                          <button class=\"btn btn-primary  dim \" type=\"button\">$TotalProcesados</button>
                                           </dd>
                                        

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
                                    <div id=\"barravalidacion\" style=\"width: 100%;\" class=\"progress-bar \"></div>
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
                  //print_r($HeaderArray);
                  
                    for($Ind=DOS;$Ind < $NumArchivos; $Ind++){
                       // echo "<br>for Ind >>$Ind<< <br>";

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
 } 
  elseif ($TipoPanel=="K" and ($Descripcion != "ptfma_despliega_resultado")){

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
                  $NombreArchivo="";
                  $Archivos="";
                 
                  $IdTipoArchivo =strtoupper (str_replace ("_"," ",$IdPanel));

                  $ArrayArchivos = obtenUltmaEjecucion($IdOrg,$Anio, $Quincena,$IdTipoArchivo);
                  $NumArchivos = count($ArrayArchivos);
                  print_r($ArrayArchivos);

                  for($Ind=DOS;$Ind < $NumArchivos; $Ind++){

                      $PathParse = explode("|", $ArrayArchivos[$Ind]);
                      $TotalErrores=$PathParse[UNO];
                      $PathArchError= $PathParse[CERO];
                      $NombreArchivoAux = explode("/", $PathParse[CERO]);
                      $NombreArchivo = "";
                      if(isset($NombreArchivoAux[DOS]))
                        $NombreArchivo = $NombreArchivoAux[DOS];

                      $NombreArchivo = substr($NombreArchivo, 14,30);
                      $Archivos .= " 
                        <dt>$NombreArchivo :</dt> <dd> 
                      <a id=\"view-resultado-$TipoArchivo\"  
                                class=\"btn btn-outline btn-primary view-pdf\" 
                                href=\"#\">
                                 <i class=\"fa fa-file-text-o fa-2x\"></i>
                                            Archivo Validado 
                                     </a> 
                                            </dd>"
                                     ;
                  }

                   // fin del for    
                  $HeaderDiv= "<div class=\"ibox-content \" id=\"$IdPanel\">";
                  $TailDiv= "</div>";

                  $TotalProcesados = $NumArchivos-DOS;
                  $Body=" $HeaderDiv
                            <div class=\"row\">
                                <div class=\"col-lg-12\">
                                    <div class=\"m-b-md\">
                                        <a href=\"#\" class=\"btn btn-success btn-xs pull-right\">
                                        <i class=\"fa fa-check-circle fa-5x\"></i></a>
                                        <h2>Resultado de Validación de Datos Id panel  </h2>
                                    </div>
                                    <dl class=\"dl-horizontal\">
                                        <dt>Estatus:</dt> <dd>
                                        <span class=\"label label-success-ssa dim\">
                                        Validado </span></dd>
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

                                        <dt>Archivos Procesados:</dt> <dd>
                                          <button class=\"btn btn-primary  dim \" type=\"button\">$TotalProcesados</button>
                                           </dd>

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
                                    <div id=\"barravalidacion\" style=\"width: 100%;\" class=\"progress-bar \"></div>
                                            </div>
                                            <small>Análisis de datos <strong>100%</strong>. Validación de Directivas de Calidad <strong>100%</strong>.</small>
                                        </dd>
                                    </dl>
                                </div>
                            </div>
</div> <!-- fin de panle -->
            $TailDiv ";      
  }// fin del If     tipos de paneles

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
       $BodyLista.= "<li><a href=\"ptfma_producto.php?quincenaurl=$Contador&anioquincenaurl=$Anio\" id=\"Q$Contador\">Quincena $Contador</a></li>
                      <li class=\"divider\" style=\" background-color:#D8D8D8\"> </li> ";
       $Contador++;               
    }// fin del while
    $MsgconstruyeListaQnas=$HdrLista.$BodyLista.$TailLista;
  }
  else{
        $MsgconstruyeListaQnas= "Sistema ptma_producto.inc/construyeListaQnas/Array";
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
 * Funcion : construyeListaProductoNomina
 * Objetivo: Construya la lista de productos de nomina
 *           
 * Parametros
 * $AnioProc : Anio de procesamiento
 * $QnaProc  : Quincena de procesamiento
 * $IdOrg    : Identificador del organismo
 *
 **********************************************************************/

function construyeListaProductoNomina($IdLista,$ProdNomina){
//echo "<br> Inicia funcion construyeListaProductoNomina <br><br>" ;
$db = new DbCnnx(); 
$HeadLista ="                  <select id=\"$IdLista\" class=\"form-control m-b\" 
                          name=\"account\" style=\"margin-bottom:0px;width: 226.22222px; margin-top: 10px;padding-left: 3px;\">
            ";

$TailLista ="                  </select>";

$SQLProdNomDetalle ="SELECT   TIPO,  DESCRIPCION
                      FROM ssa.cat_tipnom
                      ORDER BY TIPO ";
//echo "  construyeListaProductoNomina/antes execucion <br>" ;
$Rows = $db->select($SQLProdNomDetalle);
//echo "<br>  construyeListaProductoNomina/despues execucion <br>" ;
$BodyLista="";
if(is_array($Rows)){
  $Contador = CERO;
  //echo "<br>  construyeListaProductoNomina/antes del while <br>" ;
  while(isset($Rows[$Contador]['TIPO'])) {
    //echo "<br>  construyeListaProductoNomina/dentro del while <br>" ;
      $IdTipoNomina = $Rows[$Contador]['TIPO'];
      $Descripcion = $Rows[$Contador]['DESCRIPCION'];
      //echo "IdTipoNomina >>$IdTipoNomina<< Descripcion >>$Descripcion<< <br>";
      if($IdTipoNomina==$ProdNomina)
          $BodyLista .=utf8_encode("<option value='$IdTipoNomina' selected>$IdTipoNomina $Descripcion</option>");
      else 
          $BodyLista .=utf8_encode("<option value='$IdTipoNomina'>$IdTipoNomina $Descripcion</option>");
      $Contador++;  
  }// fin de while
}// fin de if(is_array($Rows))
return $HeadLista . $BodyLista . $TailLista;
}// fin de construyeListaProductoNomina

/*********************************************************************
 * 
 * Funcion : obtenArchivoPN
 * Objetivo: Construi la lista de archivos que pertenecen a la remesa
 *           de productos de nomina
 * Parametros
 * $AnioProc : Anio de procesamiento
 * $QnaProc  : Quincena de procesamiento
 * $IdOrg    : Identificador del organismo
 *
 **********************************************************************/

function obtenArchivoPN($AnioProc, $QnaProc,$IdOrg){
$ArchivoPN="";  
$ArchivoError="";
$HeaderTabla ="<table class=\"table table-hover\"  id=\"tabla_pn\"  >
                <tbody id=\"tabla_pn\">";

$TailTabla = " </tbody>
                                </table>";

$db = new DbCnnx(); 
$SQLProdNom ="SELECT  logg.id_remesas, logg.tipo_archivo,logg.archivo,logg.registros,
                logg.observaciones, logg.etiqueta_envio, logg.archivo_error,
                logg.registros_error, logg.estatus, logg.id_tipo_nom, 
                (SELECT COUNT(*) FROM logger logg2 WHERE rem.id=logg2.id_remesas  AND
                rem.id_organismos='$IdOrg' AND 
                rem.id_archivos=5 AND 
                rem.anio_periodos=$AnioProc AND
                rem.numero_periodos=$QnaProc AND
                logg2.archivo LIKE CONCAT(CHAR(39),'%', CONCAT(CONCAT(SUBSTRING_INDEX(SUBSTRING_INDEX(logg.archivo,'/',-1),'.',1),'.tra'),'%'),CHAR(39))) AS total_tra
              FROM remesas rem, logger logg
              WHERE rem.id=logg.id_remesas AND 
              id_organismos='$IdOrg' AND 
              id_archivos=5 AND
              anio_periodos=$AnioProc AND
              numero_periodos=$QnaProc  
              ORDER BY logg.fecha_agregacion  ";

//echo "obtenArchivoPN SQL>>$SQLProdNom<< <br>";
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
      $NumRegistrosTra  = $Rows[$Contador]['total_tra'];
      $Observaciones    = $Rows[$Contador]['observaciones'];
      $ArchivoError     = $Rows[$Contador]['archivo_error'];
      //echo "obtenArchivoPN<br>";
      //echo "Contador >>$Contador<< TagEnvioActual >>$TagEnvioActual<< <br><br>";
      $RegistrosArchivoError = $Rows[$Contador]['registros_error'];

      $Estatus          = $Rows[$Contador]['estatus'];
      $TipoNomina       = $Rows[$Contador]['id_tipo_nom'];
      //echo "Antes de construyeListaProductoNomina ArchivoProcesado >>$ArchivoProcesado<< <br>";

      $ArrArchivoProcesado =explode(".", $ArchivoProcesado);
      $ArrArchivoProcesado2 = explode("/", $ArrArchivoProcesado[DOS]);
      
      $IdArchivoProdNomina = $ArrArchivoProcesado2[count($ArrArchivoProcesado2)-UNO];

      $IdLista = $IdRemesa."-".$IdArchivoProdNomina;

      $ArrNombreArchivoProcesado =explode("/", $ArchivoProcesado);
      $NombreArchivoProcesado =$ArrNombreArchivoProcesado[DOS];
      
      if($TipoArchivo=="D"){
        $ListaProdNom= construyeListaProductoNomina($IdLista,$TipoNomina);
      // I-Inicial    , Cunaod ingresa por primera vez
      // A-Analizado  , Cuando ya ingresado se analiza y se encuentran Erroree
      // K analizado y sin errorees
        $Icono ="";
        $Habilitado="";
        if($Estatus == "I"){
            $Icono ="
            <button class=\"btn btn-success  btn-circle btn-lg\" 
                                  type=\"button\" style=\" padding-left: 8px;padding-top: 7px;\"><i class=\"fa fa-clock-o fa-2x\" ></i>
                            </button>";
            $Habilitado=" disabled ";     

            $BtnOperacionAnaInfo= "<button id=\"btnana-$IdLista\" class=\"btn btn-success btn-outline\" type=\"button\"
        style=\"margin-top: 10px;\" target=\"#myModal4\"><i  id=\"icoana-$IdLista\" class=\"fa fa-cogs fa-2x\" target=\"#myModal4\"></i> 
        <span id=\"spaana-$IdLista\" class=\"bold\">Analizar</span></button>
                    ";                           
        }elseif ($Estatus == "K") {
          $Icono ="
            <button class=\"btn btn-primary  btn-circle btn-lg\" 
                                  type=\"button\" style=\" padding-left: 6px;padding-top: 7px;\"><i class=\"fa fa-check fa-2x\"  ></i>
                            </button>";          
        }else{
          $Icono ="
            <button class=\"btn btn-warning  btn-circle btn-lg\" 
                                  type=\"button\" style=\" padding-left: 6px;padding-top: 7px;\"><i class=\"fa  fa-exclamation-triangle fa-2x\" ></i>
                            </button>";          
             //$Habilitado=" download ";                  
             $Habilitado="  ";                  
/**             
             $BtnOperacionAnaInfo="
        <a $Habilitado id=\"ainfo-$IdLista\" href=\"$ArchivoError\" 
     class=\"btn btn-w-m btn-outline btn-info\" style=\"margin-top: 10px;\" >
      <i id=\"icoinfo-$IdLista\" class=\"fa fa-info-circle fa-2x\"></i></a>
                                      ";
**/                                      
             $BtnOperacionAnaInfo="
        <a $Habilitado id=\"ainfo-$IdLista\" href=\"#\" 
     class=\"btn btn-w-m btn-outline btn-info\" style=\"margin-top: 10px;\" >
      <i id=\"icoinfo-$IdLista\" class=\"fa fa-info-circle fa-2x\"></i></a>
                                      ";

        }  

        $ListaArchivoProdNomina .="
                                            <tr>


                                        <td class=\"project-status\">

                                            $Icono

                                        </td>
                                        
                                        <td class=\"project-title\" 
                                        style=\"width: 166px;\">
                                            <a href=\"#\">$NombreArchivoProcesado</a>
                                            <br>
                                            <small>R.Datos: $NumRegistros </small><br>
                                            <small>R.Trail: $NumRegistrosTra</small>
                                        </td>
                                        <td class=\"project-completion\" style=\"width: 166px;\">

                                            
                                              <strong>   Totales </strong>
                                             <div>   
                         <small> Datos: 0</small><br>
                          <small> Trail: 0 </small>
                         </div>

                                        </td>

                                        <td class=\"project-completion\">
<div class=\"form-group\">
     

              <div class=\"col-sm-10\">
<!-- Lista de Productos de nomina -->
          $ListaProdNom


         </div>
 </div>


                                        </td>

                                        <td class=\"project-completion\">

<button id=\"btneli-$IdLista\" class=\"btn btn-warning btn-outline\" type=\"button\" 
            style=\"margin-top: 10px;\">
            <i id=\"icoeli-$IdLista\" class=\"fa fa-trash fa-2x\"></i> <span id=\"spaeli-$IdLista\" class=\"bold\">Eliminar</span></button>


                                        </td>


                                        <td class=\"project-people\">

<!-- Analizar/Info -->
$BtnOperacionAnaInfo
                                        </td>

                                    </tr>
        ";
      }// fin de if($TipoArchivo=="D")
      if(($TagEnvioActual != $TagEnvioAnterior) and ($Contador > UNO))
            break;
      $TagEnvioAnterior = $TagEnvioActual;
      $Contador++;
  }// fin del while    
  return $HeaderTabla.$ListaArchivoProdNomina.$TailTabla;
}// fin deif(is_array($Rows))
}//fin funcion obtenArchivoPN



/*********************************************************************
 * 
 * Funcion : contruyeTablaArchivos
 * Objetivo: Construir La Tabla que contendra los archivos
 *           a analizar
 * Parametros
 * Pendientes
 * Pendiente
 * Pendiente
 *
 **********************************************************************/

function contruyeTablaArchivos($Qna, $FechaLim,$ConfiguracionPanels){
$ArrConfiguracion = explode("@", $ConfiguracionPanels);  
$AnioProc = $ArrConfiguracion[CERO];
$QnaProc = $ArrConfiguracion[UNO];
$AuxFecha = $ArrConfiguracion[DOS];
$FechaLimite =new DateTime($AuxFecha);
$FechaLimiteFmto =$FechaLimite->format('d-m-Y');
$Usuario="";
if(isset($_SESSION['inputUsuario']))
    $Usuario=$_SESSION['inputUsuario'];
$IdOrg="";
if(isset($_SESSION['idorg']))
    $IdOrg=$_SESSION['idorg'];
$NombreUsuario="";
if(isset($_SESSION['nombre_usuario']))
    $NombreUsuario=$_SESSION['nombre_usuario'];

//$ConfiguracionPanels
$HeaderTabla="
<div id=\"output\"></div>
<ul id=\"fileList\"><li>No Files Selected</li></ul>

<div class=\"row\" id=\"tabla_remesa\">

                    <div class=\"col-lg-12\">

                        <div class=\"ibox float-e-margins\">
                            <div class=\"ibox-title\">
                                <h5>Quincena Proceso $QnaProc </h5>
                                <div class=\"pull-right\">

                                Fecha Limite $FechaLimiteFmto
                             </div>
                        </div>


                <div class=\"ibox-content\">
                         <div class=\"row\">

                           <div id=\"tablamain\" class=\"col-lg-12\">
<!--                                  
  <table class=\"table table-hover\">
       <tbody>
-->

              ";

$TailTabla="  <!--                                   </tbody>
                                </table>
-->    
                                </div>

                        </div>
                </div>

            </div>
        </div>
    </div>

          ";              

$BodyTabla =obtenArchivoPN($AnioProc, $QnaProc,$IdOrg);

/**
for($Ind=UNO;$Ind < 25; $Ind++){

$BodyTabla .="
                                    <tr>


                                        <td class=\"project-status\">

                          <button class=\"btn btn-primary  btn-circle btn-lg\" 
                                  type=\"button\"><i class=\"fa fa-check\"></i>
                            </button>


                                        </td>

                                        <td class=\"project-title\" 
                                        style=\"width: 166px;\">
                                            <a href=\"#\">prdee$Ind.dat</a>
                                            <br>
                                            <small>Tam.: 50K</small><br>
                                            <small>Tam.: 50K</small>
                                        </td>
                                        <td class=\"project-title\">

                                            
                                              <strong>   Totales </strong>
                                             <div>   
                         <small> Datos: 25550 </small><br>
                          <small> Trail: 500000 </small>
                         </div>

                                        </td>

                                        <td class=\"project-completion\">
<div class=\"form-group\">
     

              <div class=\"col-sm-10\">
                  <select id=\"TipoNomina\" class=\"form-control m-b\" 
                          name=\"account\" style=\"margin-bottom:0px;width: 226.22222px; margin-top: 10px;\">
<option value='XX'>Selecione Producto de Nómina</option>
<option value='00'>00 REXPEDICIÓN</option>
<option value='11'>11 ORDINARIA</option>
<option value='22'>22 RETROACTIVO</option>
<option value='44'>44 RETIRO VOLUNTARIO NO PRESUPUESTADO</option>
<option value='55'>55 AGUINALDO</option>
<option value='6A'>6A EXTRAORDINARIA DE PENSIÓN</option>
<option value='6E'>6E ENFERMERAS</option>
<option value='6H'>6H EXTRAORDINARIO DE HONORARIOS</option>
<option value='6I'>6I SALARIOS CAIDOS</option>
<option value='6L'>6L MEDIDAS LABORALES CONTINGENTE</option>
<option value='6M'>6M DÍA DE MADRES</option>
<option value='6O'>6O ANTIGÜEDAD Y RECOMPENSAS</option>
<option value='6P'>6P EXT PENSIÓN RETIRO VOLUNTARIO</option>
<option value='6R'>6R DÍA DE REYES</option>
<option value='6S'>6S ESTÍMULO</option>
<option value='6T'>6T DÍA DE TRABAJADOR SSA</option>
<option value='6W'>6W RETIRO VOLUNTARIO</option>
<option value='66'>66 EXTRAORDINARIA</option>
<option value='7B'>7B CANCELADOS DE PENSIÓN</option>
<option value='7C'>7C CANC. CONTIGENTES LAB</option>
<option value='7F'>7F CANCELADOS DE SALARIOS CAIDOS</option>
<option value='7I'>7I CANCELADOS DE SALARIOS CAIDOS</option>
<option value='7U'>7U CANCELADO DE PENSIÓN DE RETIRO VOLUNTARIO</option>
<option value='7V'>7V CANC. RETIRO VOLUNTARIO</option>
<option value='7W'>7W CANCELADOS DE RETIRO VOLUNTARIO</option>
<option value='73'>73 CANCELADOS DE PENSION DE RETIRO VOLUNTARIO NO PRESUPUESTADO</option>
<option value='74'>74 CANCELADOS DE RETIRO VOLUNTARIO NO PRESUPUESTADO</option>
<option value='77'>77 CANCELADOS</option>
<option value='88'>88 RECALCULO</option>
<option value='9D'>9D PENSION DE SALARIOS CAIDOS</option>
<option value='9E'>9E PENSION DE ENFERMERAS</option>
<option value='9I'>9I PENSION DE SALARIOS CAIDOS</option>
<option value='9L'>9L PENSION MEDIDAS LABORALES CONTINGENTE</option>
<option value='9M'>9M PENSION DE DIA DE MADRES</option>
<option value='9N'>9N PENSION DE DIA DE MADRES</option>
<option value='9O'>9O PENSION ANTIGUEDAD Y RECOMPENSAS</option>
<option value='9R'>9R PENSION DIA DE REYES</option>
<option value='9S'>9S PENSION DE ESTIMULOS</option>
<option value='9T'>9T PENSION DIA DEL TRABAJADOR</option>
<option value='9W'>9W PENSION RETIRO VOLUNTARIO PRESUPUESTADO</option>
<option value='9X'>9X PENSIÓN DE REYES</option>
<option value='9Y'>9Y PENSION DE DIA DEL TRABAJADOR</option>
<option value='9Z'>9Z PENSIÓN DE AGUINALDO</option>
<option value='93'>93 PENSION DE RETIRO VOLUNTARIO PRESUPUESTADO</option>
<option value='94'>94 PENSION DE RETIRO VOLUNTARIO NO PRESUPUESTADO</option>
<option value='95'>95 PENSION DE AGUINALDO</option>
<option value='98'>98 PENSION DE RECALCULO</option>
<option value='99'>99 PENSIÓN</option>
                  </select>
         </div>
 </div>


                                        </td>

                                        <td class=\"project-completion\">

<button class=\"btn btn-warning btn-outline\" type=\"button\" 
            style=\"margin-top: 10px;\">
            <i class=\"fa fa-trash fa-2x\"></i> <span class=\"bold\">Eliminar</span></button>


                                        </td>


                                        <td class=\"project-people\">

<button class=\"btn btn-success btn-outline\" type=\"button\"
        style=\"margin-top: 10px;\"><i class=\"fa fa-cogs fa-2x\"></i> <span class=\"bold\">Analizar</span></button>


                                        </td>
                                        <td class=\"project-actions\">
                                     <a id=\"timeline1\" href=\"ptfma_timeline.php?id=Baja_California\" 
                                     class=\"btn btn-w-m btn-outline btn-info\" style=\"margin-top: 10px;\"><i class=\"fa fa-info-circle fa-2x\"></i></a>
                                            
                                        </td>




                                    </tr>

      ";


}
**/


  return " $HeaderTabla

$BodyTabla
$TailTabla
        ";


}// fin de contruyeTablaArchivos


/*********************************************************************
 * 
 * Funcion : construyePanelMain
 * Objetivo: Construir La interfaz Main de carga
 *           
 * Parametros
 * $Qna:  Quincena Procesada
 * $FechaLim    :  Fecha Limite de recepcion de Archivos
 * $PanlesCarga: Paneles de carga a mostrar
 *
 **********************************************************************/

function construyePanelMain($Qna,$IdOrg){

  $TotalNumeroArchivosRemesa = calculaNumArchivosRemesa();
$ContadorQuincenas=UNO;
$BodyListaQna ="";
while($ContadorQuincenas < 25) {
      $ContQuin = sprintf("%02d\n", $ContadorQuincenas);

      if($ContadorQuincenas==$Qna)
          $BodyListaQna .=utf8_encode("<option value='$ContQuin' selected>$ContQuin</option>");
      else 
          $BodyListaQna .=utf8_encode("<option value='$ContQuin' >$ContQuin</option>");
      $ContadorQuincenas++;  
  }// fin de while

$BodyListaAnio ="";
$ContadorAnio=2016;
while($ContadorAnio < 2020) {
      $ContAnio = sprintf("%04d\n", $ContadorAnio);

      if($ContadorQuincenas==$Qna)
          $BodyListaAnio .=utf8_encode("<option value='$ContAnio' selected>$ContAnio</option>");
      else 
          $BodyListaAnio .=utf8_encode("<option value='$ContAnio' >$ContAnio</option>");
      $ContadorAnio++;  
  }// fin de while



return "
                    <div class=\"col-lg-3\">
                        <div class=\"ibox float-e-margins\">
                            <div class=\"ibox-title\">
                            <span class=\"label label-success-ssa pull-right\">Productos</span>
                                <h5>Selecciona </h5>
                            </div>
                            <div class=\"ibox-content\" style=\" text-align:center;vertical-align:middle ; padding-bottom:10px;padding-top: 10px;\">
                              




                                <button class=\"btn btn-primary \" type=\"file\" 
                                    id=\"SelectArchivoProducto\">
                                  <i class=\"fa fa-cloud-upload fa-3x\">
                                  </i>&nbsp; &nbsp; &nbsp; Archivo
                                  </button>
<form enctype=\"multipart/form-data\" method=\"post\" name=\"fileinfo\">

                                  <input id=\"SelectArchivoProductoBase\"  name=\"SelectArchivoProductoBase\" type=\"file\" multiple=\"\"  style=\"visibility: hidden; position: absolute; top: 0px; left: 0px; height: 0px; width: 0px;\" onchange=\"makeFileList();\">

 
  <input id=\"Enviar\" type=\"submit\" value=\"Stash the file!\" style=\"visibility: hidden; position: absolute; top: 0px; left: 0px; height: 0px; width: 0px;\"/>
</form>  

                            </div>
                        </div>
                    </div>
                    <div class=\"col-lg-3\">
                        <div class=\"ibox float-e-margins\">
                            <div class=\"ibox-title\">
                                <span class=\"label label-warning2-light pull-right\">Envío</span>
                                <h5>Fecha</h5>
                            </div>
                            <div class=\"ibox-content\">


                                


  <div class=\"form-group\">
      <label class=\"col-sm-1 control-label\" style=\"padding-left: 5px;padding-right: 25px;padding-top: 5px;\">Año</label>

              <div class=\"col-sm-10\">
                  <select class=\"form-control m-b\" 
                          name=\"account\" style=\"margin-bottom:0px;\" id=\"anio_envio\">
$BodyListaAnio

                  </select>
              </div>
 </div>





                                <div class=\"stat-percent font-bold text-info\">2016

                            </div>
                                <small>Año Proceso</small>
                            </div>
                        </div>
                    </div>

                    <div class=\"col-lg-3\">
                        <div class=\"ibox float-e-margins\">
                            <div class=\"ibox-title\">
                                <span class=\"label label-warning2-light pull-right\">Envío</span>
                                <h5>Quincena</h5>
                            </div>
                            <div class=\"ibox-content\">



  <div class=\"form-group\">
      <label class=\"col-sm-1 control-label\" style=\"padding-left: 5px;padding-right: 25px;padding-top: 5px;\">Qna</label>

              <div class=\"col-sm-10\">

                  <select class=\"form-control m-b\" 

                          name=\"account\" style=\"margin-bottom:0px;\" id=\"quincena_envio\">
                          $BodyListaQna

                  </select>
         </div>
 </div>







                                <div class=\"stat-percent font-bold text-navy\">$Qna </div>
                                <small>Quincena Proceso</small>
                            </div>
                        </div>
                    </div>
                    <div class=\"col-lg-3\">
                        <div class=\"ibox float-e-margins\">
                            <div class=\"ibox-title\">
                                <span class=\"label label-success pull-right\">En proceso</span>
                                <h5>Archivos</h5>
                            </div>
                            <div class=\"ibox-content\">
                                <h1 id=\"num_archivos_remesa\" class=\"no-margins\">$TotalNumeroArchivosRemesa</h1>
                                <div class=\"stat-percent font-bold text-info\">78% <i class=\"fa fa-level-up\"></i></div>
                                <small>En proceso</small>
                            </div>
                        </div>
                    </div>
";

}// fin de construyePanelMain


/*********************************************************************
 * 
 * Funcion : fncBuildRow1CargaPdcto
 * Objetivo: Construir La interfaz de carga
 *           
 * Parametros
 * $Qna:  Quincena Procesada
 * $FechaLim    :  Fecha Limite de recepcion de Archivos
 * $PanlesCarga: Paneles de carga a mostrar
 *
 **********************************************************************/

function fncBuildRow1CargaPdcto($Qna, $Anio,$FechaLim, $ConfiguracionPanels){

$ArrArchivo = "archivo1.zip";

$ArrResultados = "2 Archivos Analizados";

$Organismo = $_SESSION['organismo'];
$IdOrg =$_SESSION['idorg'];
$PanelMain= construyePanelMain($Qna,$IdOrg);
$Resultados = ""; 
$PanlesArchivosProductoNomina = contruyeTablaArchivos($Qna, $FechaLim,$ConfiguracionPanels);

//obtenResultadosValidacion(416,0,$ArrArchivo,$ArrResultados,"archivo1.txt",0);

	return "
    <div class=\"row wrapper border-bottom white-bg page-heading\">
                <div class=\"col-lg-10\">
                    
                    <ol class=\"breadcrumb\">
                        <li>
                            <a href=\"#\">Quincena $Qna </a>
                        </li>
                        <li>
                            <a href=\"#\"> $Organismo</a>
                        </li>
                        <li class=\"active\">
                            <strong>Recepción de Productos </strong>
                        </li>
                    </ol>
                </div>
            </div>

   <div class=\"wrapper wrapper-content animated fadeInRight\" id=\"main_page\" style=\"
    padding-top: 10px;\">

        <div class=\"row\">
              $PanelMain                        
        </div>

    <div class=\"row\">



            $PanlesArchivosProductoNomina




   <!-- SECCION DE RESULTADOS -->
<!--
        <div id=\"resultados\"  class=\"wrapper wrapper-content animated fadeInRight\">
-->
                $Resultados
                <div class=\"col-lg-12\" id=\"x00\"  style=\" text-align:center;vertical-align:middle\">
                <div>
<!--
                    <button class=\"btn btn-primary btn-lg\" type=\"button\" 
                          id=\"EnviarRemesa\">
                    <i class=\"fa fa-upload\"></i>&nbsp;Enviar Archivos</button>

-->
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
}// fin de fncBuildRow1CargaPdcto


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
    <!-- jqGrid -->
    <script src=\"../grid/js/plugins/jqGrid/i18n/grid.locale-en.js\"></script>
    <script src=\"../grid/js/plugins/jqGrid/jquery.jqGrid.min.js\"></script>


     <!-- DROPZONE -->
<!--     
    <script src=\"../js/plugins/dropzone/dropzone.js\"></script>
 -->     
<!--
    <script src=\"//ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js\"></script>

  -->  
 

    <script>
        $(document).ready(function() {

               $(\"#tabla_errores\").jqGrid({
                url: 'ptfma_listar_errorres.php?callback=?&qwery=longorders',
                datatype: \"json\",
                mtype: \"GET\",
                height: 400,
                autowidth: true,
                shrinkToFit: true,
                rowNum: 50,
                rowList: [50, 100, 150],
                ajaxGridOptions: { contentType:'application/json;charset=utf-8',cache: false },
                colNames: ['#', 'Campo', 'Evidencia', 'Descripcion'],
                colModel: [
                    {name: 'numero_registro', index: 'numero_registro', width: 30, sorttype: \"int\",align: \"right\"},
                    {name: 'campo', index: 'campo', width: 180,align: \"left\"},
                    {name: 'evidencia', index: 'evidencia', width: 150,align: \"left\" },
                    {name: 'descripcion', index: 'descripcion', width: 400, align: \"left\", },
                ],
                pager: \"#pager\",
                viewrecords: true,
                caption: \"Información Actualizada\",
                hidegrid: false,
                onSelectRow: function(id){
                   // alert(id);
                    /*
                        if(id && id!==lastsel3){
                            jQuery('#rowed6').jqGrid('restoreRow',lastsel3);
                            jQuery('#rowed6').jqGrid('editRow',id,true,pickdates);
                            lastsel3=id;
                        }
                   */     
                }

            }).navGrid(\"#pager\",{edit:false,add:false,del:false});;








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
/**
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
**/
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
        <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"> 
		    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">

		    <title>Secretaria de Salud</title>

		    <link href=\"../css/bootstrap.min.css\" rel=\"stylesheet\">
		    <link href=\"../font-awesome/css/font-awesome.css\" rel=\"stylesheet\">

		    <!-- Toastr style -->
		    <link href=\"../css/plugins/toastr/toastr.min.css\" rel=\"stylesheet\">

		    <!-- Gritter -->
		    <link href=\"../js/plugins/gritter/jquery.gritter.css\" rel=\"stylesheet\">

<link href=\"../css/plugins/jQueryUI/jquery-ui-1.10.4.custom.min.css\" rel=\"stylesheet\">
<link href=\"../css/plugins/jqGrid/ui.jqgrid.css\" rel=\"stylesheet\">


            <link href=\"../css/animate.css\" rel=\"stylesheet\">
            <link href=\"../css/style.css\" rel=\"stylesheet\">            

            <link href=\"../css/plugins/dropzone/basic.css\" rel=\"stylesheet\">
            <link href=\"../css/plugins/dropzone/dropzone.css\" rel=\"stylesheet\">
<!--          
            <link href=\"../css/plugins/jqGrid/ui.jqgrid.css\" rel=\"stylesheet\">
-->            
          



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
    $Modal = incluyeModal($Anio,$Qna);

    $PrimParte = fncBuildTopNavBar();
    $PanelesCarga = construyePanelesCarga($ConfiguracionPanels);
    //$Row1 = fncBuildRow1($Qna, $FechaLim, $PanelesCarga);
    $Row1 = fncBuildRow1CargaPdcto($Qna,$Anio, $FechaLim, $ConfiguracionPanels );
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
$Modal



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
                <ul class=\"nav metismenu \" id=\"side-menu\" 
                                    style=\"padding-top: 10px;padding-bottom: 10px;\">
                    <li class=\"nav-header\" style=\"padding-top: 10px;padding-bottom: 10px;\">
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
  







			$JS


<script>
/**
var form = document.forms.namedItem(\"fileinfo\");
form.addEventListener('submit', function(ev) {

      alert('addEventListener');
      var
        oOutput = document.getElementById(\"output\"),
        oData = new FormData(document.forms.namedItem(\"fileinfo\"));

      oData.append(\"CustomField\", \"This is some extra data\");

      console.log('Agrega CustomField');

      var oReq = new XMLHttpRequest();

      oReq.open(\"POST\", \"http://localhost/scratch/test_httpr.php\", true);

      oReq.onload = function(oEvent) {
        if (oReq.status == 200) {
          oOutput.innerHTML = \"Uploaded!\";
        } else {
          oOutput.innerHTML = \"Error \" + oReq.status + \" occurred uploading your file.<br \/>\";
        }
      };

      oReq.send(oData);
      ev.preventDefault();
    }, false);
          
**/


        var mili = 77000;
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
/*****************************
 * SECCIONDE OPERACIONES
 *
 *****************************/
  $('#tabla_remesa').on('mousedown', 'button', function(){

      var IdBtn = event.target.id;
      var ArrIdBtn = IdBtn.split(\"-\");
      var IdRemesa = ArrIdBtn[1];
      var IdArchivoPN = ArrIdBtn[2];

      //alert('mousedown >' + IdBtn +'< ' );
      //  $('#myModal4').modal('show');
      // console.log('#myModal4 show');  
      //   $(IdBtn).trigger(\"click\");
    }
    );



    $('#tabla_remesa').on('click', 'a', function(){
      var IdBtn = event.target.id;

      var ArrIdBtn = IdBtn.split(\"-\");
      var IdRemesa = ArrIdBtn[1];
      var IdArchivoPN = ArrIdBtn[2];
      var ArrTagEnvio = TagEnvio.split(\"-\");
      var QuincenaProceso =ArrTagEnvio[2];

     // alert('botton >' + IdBtn +'< ' );

      //$('#registros_error').html(' <div class=\"modal-dialog\"> <h1> probando <h1> <br> <h1> probando 2<h1></div>');
/**
       var OperacionArchivosErrorPN = new XMLHttpRequest();
       var FrmArchivosErrorPN = new FormData();
       OperacionArchivosErrorPN.open(\"POST\", \"/ptma_opcd/ptfma_regresa_errores.php\",false);

       FrmArchivosErrorPN.append(\"TagEnvio\", TagEnvio);
       FrmArchivosErrorPN.append(\"idremesa\", IdRemesa);
       FrmArchivosErrorPN.append(\"idarchivopn\", IdArchivoPN);
  
       OperacionArchivosErrorPN.send(FrmArchivosErrorPN);
       var RespuestaError=OperacionArchivosErrorPN.responseText;

      $('#registros_error').html(RespuestaError);
**/
      
      var newUrl= 'ptfma_listar_errorres.php?callback=?&qwery=longorders&tagenvio='+ TagEnvio+'&idremesa=' + IdRemesa +'&idarchivopn='+ IdArchivoPN;

      $('#tabla_errores').setGridParam({url:newUrl,datatype:\"json\",page:1});
      $('#tabla_errores').trigger('reloadGrid');
      $('#modal_titulo').html('Quincena :'+ QuincenaProceso +' Archivo Analizado :'+IdArchivoPN);
      $('#registros_error').modal('show');


    }
    );

    $('#tabla_remesa').on('click', 'button', function(){
        var IdBtn = event.target.id;
        var ProcesaEliminar = new RegExp(/eli-[0-9]{1,6}/);
        var ProcesaAnalizar = new RegExp(/ana-[0-9]{1,6}/);
        var ProcesaInformar = new RegExp(/eli-[0-9]{1,6}/);
        var ArrIdBtn = IdBtn.split(\"-\");
        var IdRemesa = ArrIdBtn[1];
        var IdArchivoPN = ArrIdBtn[2];

//        $('#registros_error').modal('show');

        var OperacionArchivosPN = new XMLHttpRequest();
        var FrmArchivosPN = new FormData();


        FrmArchivosPN.append(\"TagEnvio\", TagEnvio);
        FrmArchivosPN.append(\"idremesa\", IdRemesa);
        FrmArchivosPN.append(\"idarchivopn\", IdArchivoPN);

        OperacionArchivosPN.open(\"POST\", \"/ptma_opcd/ptfma_cruda_archivo.php\", false);



        // alert('botton >' + IdBtn +'< estatus >' + ProcesaEliminar.test(IdBtn) +'<');
        //  alert('botton >' + IdQna +'< estatus >' + ProcesaAnalizar.test(IdQna) +'<');

        if(ProcesaEliminar.test(IdBtn)){
            //alert('botton Eliminar >' + IdBtn +'<' );
            FrmArchivosPN.append(\"operacion\", 'eliminar');

        }
        else
          if(ProcesaAnalizar.test(IdBtn)){
            console.log('botton Analizar >' + IdBtn +'<' );

            FrmArchivosPN.append(\"operacion\", 'analizar');

          }
          else
              if(ProcesaInformar.test(IdBtn)){
                alert('botton Informar >' + IdBtn +'<' );
                FrmArchivosPN.append(\"operacion\", 'informar');
              }
              else
                console.log('No se identifica el boton'+ IdBtn +'<');
        // fin del if test

        OperacionArchivosPN.send(FrmArchivosPN);
        var RespuestaCRUDA=OperacionArchivosPN.responseText;

        $('#myModal4').modal('hide');
        console.log('#myModal4 hide');
        //console.log('RespuestaCRUDA >>'+RespuestaCRUDA +'<<');

        $('#tablamain').html(RespuestaCRUDA);
        var regtabla=$('#tabla_pn  tr').length;
        console.log('regtabla >'+regtabla+'<');
        $('#num_archivos_remesa').html(regtabla);

    } );



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

        $('#SelectArchivoProducto').click(function(){
            $('#SelectArchivoProductoBase').click();
            //$('#Enviar').click()

/**
                var form = document.forms.namedItem(\"fileinfo\");
                var file_data = document.getElementById('#SelectArchivoProductoBase');   
                var archivo =file_data.files[0].name;

                alert('Tamanio >>'+ file_data.length +'<<')
                var datos='';
                for (var x = 0; x < file_data.length; x++) {
                  
                  datos= datos + file_data[x].name + '<bR>';
                  
                }
                alert(datos);

**/

                //var form_data = new FormData();                  
                //form_data.append('file', file_data);
                //alert(form_data);  
/**
                var formData = new FormData();
                formData.append(\"username\", \"Noe Alvarez\");
                formData.append(\"accountnum\", \"123456\");
                var request = new XMLHttpRequest();
                request.open(\"POST\", \"http://localhost/scratch/test_httpr.php\");
                request.send(formData);
**/

            }
        );




</script>
<script type=\"text/javascript\">
    function makeFileList() {
      var input = document.getElementById(\"SelectArchivoProductoBase\");
      var ul = document.getElementById(\"fileList\");

      var form = document.forms.namedItem(\"fileinfo\");

      //alert(TagEnvio);
      oData = new FormData(document.forms.namedItem(\"fileinfo\"));
      oData.append(\"CustomField\", \"This is some extra data\");
      console.log('Agrega CustomField');
      while (ul.hasChildNodes()) {
        ul.removeChild(ul.firstChild);
      }
      console.log('input.files.length >>'+ input.files.length +'<<');
      if( input.files.length == 2){
          for (var i = 0; i < input.files.length; i++) {  
            if(i==0){
              var Archivo1 = input.files[i].name;
              var ArrArchivo1 = Archivo1.split(\".\");

              var NomArch1 =ArrArchivo1[0];
              var ArrArchivoExt1 = ArrArchivo1[1];
            }  
            else{
              var Archivo2 = input.files[i].name;
              var ArrArchivo2 = Archivo2.split(\".\");
              var NomArch2 =ArrArchivo2[0];
              var ArrArchivoExt2 = ArrArchivo2[1];
            }
          }// fin de primer for

          //alert('1 >>'+NomArch1.valueOf() +'<< >>'+NomArch2.valueOf() +'<<');
          if (NomArch1.valueOf()==NomArch2.valueOf()){
              // Validar si existe archivo
            for (var i = 0; i < input.files.length; i++) {  
               var NomArchivo = input.files[i].name
               var ExisteArchivo = new XMLHttpRequest();
               var FrmExiste = new FormData();
               FrmExiste.append(\"TagEnvio\", TagEnvio);
               FrmExiste.append(\"archivo_existe\", NomArchivo);
               ExisteArchivo.open(\"POST\", \"/ptma_opcd/ptfma_existe_archivo.php\", false);
               ExisteArchivo.send(FrmExiste);
               var RespuestaExiste=ExisteArchivo.responseText;
               console.log('RespuestaExiste >>'+RespuestaExiste +'<<');

               if(RespuestaExiste==0){
                    console.log('El Archivo >>'+NomArchivo +'<< se registra');
               }  
               else{
                    console.log('El Archivo >>'+NomArchivo +'<< ya existe');
                    break;
               }
             }// fin de for para validar existencia

             if(RespuestaExiste==0){
              for (var i = 0; i < input.files.length; i++) {
                var oReq = new XMLHttpRequest();
                var li = document.createElement(\"li\");
                li.innerHTML = input.files[i].name;
                ul.appendChild(li);
                oOutput = document.getElementById(\"output\");
                oData.append(\"afile\"+i, input.files[i]);
                console.log(input.files[i]);
                var formData = new FormData();
                formData.append(\"TagEnvio\", TagEnvio);
                formData.append(\"producto_nomina\", input.files[i]);
                oReq.open(\"POST\", \"/ptma_opcd/ptfma_registra_archivo.php\", false);
                oReq.send(formData);
                console.log(oReq.getAllResponseHeaders());

                console.log(oReq.responseText);
                $('#tablamain').html(oReq.responseText);
        

               var regtabla=$('#tabla_pn  tr').length;
                console.log('regtabla >'+regtabla+'<');
                $('#num_archivos_remesa').html(regtabla);

                oReq.onload = function(oEvent) {
                if (oReq.status == 200) {
                    oOutput.innerHTML = \"Uploaded!\" +i;
                    console.log('Uploaded!' + i);
                } else {
                    oOutput.innerHTML = \"Error \" + oReq.status + \" occurred uploading your file.<br \/>\";
                    console.log('Error' +oReq.status + 'occurred uploading your file.<br>');
                }
                };

              }// fin del for
            }else{
                alert('El archivo ya existe');  
            }


          }
          else{
                alert('Los nombres de los archivos Datos y Trailers debe ser el mismo');  
          }
      }
      else{
          alert('Debe Seleccionar dos archivo(Datos y Trailers)');
      }
      if(!ul.hasChildNodes()) {
        var li = document.createElement(\"li\");
        li.innerHTML = 'No Files Selected';
        ul.appendChild(li);
      }
      form.reset();
    }
  </script>


			</body>
			</html>
	";
} // fin de fncBuildTail


?>    