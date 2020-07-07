<?php

function fncIntegraTablaResumen()
{

return "
	<table class=\"table table-hover\">
       <tbody>
                                    <tr>
                                        <td class=\"project-status\">
                                            <span class=\"label label-primary2\">Aceptado</span>
                                        </td>

                                        <td class=\"project-title\">
                                            <a href=\"#\">Aguascalientes</a>
                                            <br>
                                            <small>Act. 13-Abr-2016 12:34:18</small>
                                        </td>
                                        <td class=\"project-completion\">
                                        	<strong>	 416 $ 200,000,00.00</strong>
                                             <div>   
        										     <small> Perc.: $ 180,000,00.00 </small><br>
        										      <small> Dedus.: $ 20,000,00.00 </small>
										     </div>

                                        </td>
                                        <td class=\"project-completion\">
                                              <strong>   X00 $ 200,000,00.00 </strong>
                                             <div>   
										     <small> P.: $ 180,000,00.00 </small><br>
										      <small> D.: $ 20,000,00.00 </small>
										     </div>
                                        </td>
                                        <td class=\"project-completion\">
                                              <strong>   610 $ 200,000,00.00 </strong>
                                             <div>   
										     <small> Perc.: $ 180,000,00.00 </small><br>
										      <small> D.: $ 20,000,00.00 </small>
										     </div>
                                        </td>

                                        <td class=\"project-people\">
	                                            <a id=\"view-pdf1\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test.pdf\">
	                                            <i class=\"fa fa-file-pdf-o fa-2x\"></i>
	                                            </a>
	                                            <a id=\"view-pdf2\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test2.pdf\">
	                                            <i class=\"fa fa-file-image-o fa-2x\"></i>
	                                            </a>

	                                            <a id=\"view-pdf3\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test.jpg\">
	                                            <i class=\"fa fa-file-image-o fa-2x\"></i>
	                                            </a>
                                        </td>
                                        <td class=\"project-actions\">
                                            <a id=\"timeline\" href=\"ptfma_timeline.php?id=Aguascalientes\" class=\"btn btn-w-m btn-outline btn-info\"><i class=\"fa fa-calendar fa-2x \"></i></a>
                                        </td>
                                    </tr>
                                    <tr>
                                        <td class=\"project-status\">
                                            <span class=\"label label-primary2\">Aceptado</span>
                                        </td>
                                        <td class=\"project-title\">
                                            <a href=\"#\">Baja California</a>
                                            <br>
                                            <small>Act. 12-Abr-2016 10:34:18</small>
                                        </td>
                                        <td class=\"project-title\">
                                        		
                                              <strong>   416 $ 200,000,00.00 </strong>
                                             <div>   
										     <small> P.: $ 180,000,00.00 </small><br>
										      <small> D.: $ 20,000,00.00 </small>
										     </div>

                                        </td>
                                        <td class=\"project-completion\">
                                              <strong>   X00 $ 200,000,00.00 </strong>
                                             <div>   
										     <small> P.: $ 180,000,00.00 </small><br>
										      <small> D.: $ 20,000,00.00 </small>
										     </div>
                                        </td>
                                        <td class=\"project-completion\">
                                              <strong>   610 $ 200,000,00.00 </strong>
                                             <div>   
										     <small> Ingresos: $ 180,000,00.00 </small><br>
										      <small> D.: $ 20,000,00.00 </small>
										     </div>
                                        </td>


                                        <td class=\"project-people\">


                                              <a id=\"view-pdf\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test.pdf\">
                                              <i class=\"fa fa-file-pdf-o fa-2x\"></i>
                                              </a>
                                              <a id=\"view-pdf\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test2.pdf\">
                                              <i class=\"fa fa-file-image-o fa-2x\"></i>
                                              </a>

                                        </td>
                                        <td class=\"project-actions\">
                                     <a id=\"timeline1\" href=\"ptfma_timeline.php?id=Baja_California\" class=\"btn btn-w-m btn-outline btn-info\"><i class=\"fa fa-calendar fa-2x\"></i></a>
                                            
                                        </td>
                                    </tr>
                                    <tr>
                                        <td class=\"project-status\">
                                            <span class=\"label label-warning2\">Pendiente</span>
                                        </td>
                                        <td class=\"project-title\">
                                            <a href=\"#\">Baja California Sur</a>
                                            <br>
                                            <small>Act. 13-Abr-2016 12:34:18</small>
                                        </td>
                                        <td class=\"project-title\">
                                        		
                                              <strong>   416 $ 200,000,00.00 </strong>
                                             <div>   
										     <small> P.: $ 180,000,00.00 </small><br>
										      <small> D.: $ 20,000,00.00 </small>
										     </div>

                                        </td>
                                        <td class=\"project-completion\">
                                              <strong>   X00 $ 200,000,00.00 </strong>
                                             <div>   
										     <small> P.: $ 180,000,00.00 </small><br>
										      <small> D.: $ 20,000,00.00 </small>
										     </div>
                                        </td>
                                        <td class=\"project-completion\">
                                              <strong>   610 $ 200,000,00.00 </strong>
                                             <div>   
										     <small> Ingresos: $ 180,000,00.00 </small><br>
										      <small> D.: $ 20,000,00.00 </small>
										     </div>
                                        </td>




                                        <td class=\"project-people\">

                                              <a id=\"view-pdf\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test.pdf\">
                                              <i class=\"fa fa-file-pdf-o fa-2x\"></i>
                                              </a>
                                              <a id=\"view-pdf\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test2.pdf\">
                                              <i class=\"fa fa-file-image-o fa-2x\"></i>
                                              </a>
                                        </td>
                                        <td class=\"project-actions\">
                                            <a id=\"timeline2\" href=\"ptfma_timeline.php?id=Baja_California_Sur\" class=\"btn btn-w-m btn-outline btn-info\"><i class=\"fa fa-calendar fa-2x\"></i> </a>
                                        </td>
                                    </tr>
                                    <tr>
                                        <td class=\"project-status\">
                                            <span class=\"label label-primary2\">Aceptado</span>
                                        </td>
                                        <td class=\"project-title\">
                                            <a href=\"#\">Campeche</a>
                                            <br>
                                            <small>Created 22.07.2014</small>
                                        </td>
                                        <td class=\"project-title\">
                                        		
                                              <strong>   416 $ 200,000,00.00 </strong>
                                             <div>   
										     <small> P.: $ 180,000,00.00 </small><br>
										      <small> D.: $ 20,000,00.00 </small>
										     </div>

                                        </td>
                                        <td class=\"project-completion\">
                                              <strong>   X00 $ 200,000,00.00 </strong>
                                             <div>   
										     <small> P.: $ 180,000,00.00 </small><br>
										      <small> D.: $ 20,000,00.00 </small>
										     </div>
                                        </td>
                                        <td class=\"project-completion\">
                                              <strong>   610 $ 200,000,00.00 </strong>
                                             <div>   
										     <small> Ingresos: $ 180,000,00.00 </small><br>
										      <small> D.: $ 20,000,00.00 </small>
										     </div>
                                        </td>



                                        <td class=\"project-people\">

                                              <a id=\"view-pdf\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test.pdf\">
                                              <i class=\"fa fa-file-pdf-o fa-2x\"></i>
                                              </a>
                                              <a id=\"view-pdf\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test2.pdf\">
                                              <i class=\"fa fa-file-image-o fa-2x\"></i>
                                              </a>
                                        </td>
                                        <td class=\"project-actions\">
                                            <a id=\"timeline3\" href=\"ptfma_timeline.php?id=Campeche\" class=\"btn btn-w-m btn-outline btn-info\"><i class=\"fa fa-calendar fa-2x\"></i> </a>
                                            
                                        </td>
                                    </tr>
                                    <tr>
                                        <td class=\"project-status\">
                                            <span class=\"label label-primary2\">Aceptado</span>
                                        </td>
                                        <td class=\"project-title\">
                                            <a href=\"#\">Coahuila</a>
                                            <br>
                                            <small>Act. 13-Abr-2016 12:04:18</small>
                                        </td>
                                        <td class=\"project-title\">
                                        		
                                              <strong>   416 $ 200,000,00.00 </strong>
                                             <div>   
										     <small> P.: $ 180,000,00.00 </small><br>
										      <small> D.: $ 20,000,00.00 </small>
										     </div>

                                        </td>
                                        <td class=\"project-completion\">
                                              <strong>   X00 $ 200,000,00.00 </strong>
                                             <div>   
										     <small> P.: $ 180,000,00.00 </small><br>
										      <small> D.: $ 20,000,00.00 </small>
										     </div>
                                        </td>
                                        <td class=\"project-completion\">
                                              <strong>   610 $ 200,000,00.00 </strong>
                                             <div>   
										     <small> Ingresos: $ 180,000,00.00 </small><br>
										      <small> D.: $ 20,000,00.00 </small>
										     </div>
                                        </td>



                                        <td class=\"project-people\">

                                              <a id=\"view-pdf\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test.pdf\">
                                              <i class=\"fa fa-file-pdf-o fa-2x\"></i>
                                              </a>
                                              <a id=\"view-pdf\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test2.pdf\">
                                              <i class=\"fa fa-file-image-o fa-2x\"></i>
                                              </a>


                                        </td>
                                        <td class=\"project-actions\">

                                            <a id=\"timeline4\" href=\"ptfma_timeline.php?id=Coahuila\" class=\"btn btn-w-m btn-outline btn-info\"><i class=\"fa fa-calendar fa-2x\"></i></a>


                                        </td>
                                    </tr>
                                    <tr>
                                        <td class=\"project-status\">
                                            <span class=\"label label-primary2\">Aceptado</span>
                                        </td>
                                        <td class=\"project-title\">
                                            <a href=\"#\">Colima</a>
                                            <br>
                                            <small>Act. 10-Abr-2016 12:34:18</small>
                                        </td>
                                        <td class=\"project-title\">
                                        		
                                              <strong>   416 $ 200,000,00.00 </strong>
                                             <div>   
										     <small> P.: $ 180,000,00.00 </small><br>
										      <small> D.: $ 20,000,00.00 </small>
										     </div>

                                        </td>
                                        <td class=\"project-completion\">
                                              <strong>   X00 $ 200,000,00.00 </strong>
                                             <div>   
										     <small> P.: $ 180,000,00.00 </small><br>
										      <small> D.: $ 20,000,00.00 </small>
										     </div>
                                        </td>
                                        <td class=\"project-completion\">
                                              <strong>   610 $ 200,000,00.00 </strong>
                                             <div>   
										     <small> Ingresos: $ 180,000,00.00 </small><br>
										      <small> D.: $ 20,000,00.00 </small>
										     </div>
                                        </td>


                                        <td class=\"project-people\">

                                              <a id=\"view-pdf\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test.pdf\">
                                              <i class=\"fa fa-file-pdf-o fa-2x\"></i>
                                              </a>
                                              <a id=\"view-pdf\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test2.pdf\">
                                              <i class=\"fa fa-file-image-o fa-2x\"></i>
                                              </a>
                                        </td>
                                        <td class=\"project-actions\">
                                            <a id=\"timeline5\" href=\"ptfma_timeline.php?id=Colima\" class=\"btn btn-w-m btn-outline btn-info\"><i class=\"fa fa-calendar fa-2x\"></i></a>
                                        </td>
                                    </tr>
                                    <tr>
                                        <td class=\"project-status\">
                                            <span class=\"label label-primary2\">Aceptado</span>
                                        </td>
                                        <td class=\"project-title\">
                                            <a href=\"#\">Chiapas</a>
                                            <br>
                                            <small>Created 11.08.2014</small>
                                        </td>
                                        <td class=\"project-title\">
                                        		
                                              <strong>   416 $ 200,000,00.00 </strong>
                                             <div>   
										     <small> P.: $ 180,000,00.00 </small><br>
										      <small> D.: $ 20,000,00.00 </small>
										     </div>

                                        </td>
                                        <td class=\"project-completion\">
                                              <strong>   X00 $ 200,000,00.00 </strong>
                                             <div>   
										     <small> P.: $ 180,000,00.00 </small><br>
										      <small> D.: $ 20,000,00.00 </small>
										     </div>
                                        </td>
                                        <td class=\"project-completion\">
                                              <strong>   610 $ 200,000,00.00 </strong>
                                             <div>   
										     <small> Ingresos: $ 180,000,00.00 </small><br>
										      <small> D.: $ 20,000,00.00 </small>
										     </div>
                                        </td>



                                        <td class=\"project-people\">

                                              <a id=\"view-pdf\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test.pdf\">
                                              <i class=\"fa fa-file-pdf-o fa-2x\"></i>
                                              </a>
                                              <a id=\"view-pdf\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test2.pdf\">
                                              <i class=\"fa fa-file-image-o fa-2x\"></i>
                                              </a>


                                        </td>
                                        <td class=\"project-actions\">
                                            <a id=\"timeline6\" href=\"ptfma_timeline.php?id=Chiapas\" class=\"btn btn-w-m btn-outline btn-info\"><i class=\"fa fa-calendar fa-2x\"></i></a>
                                        </td>
                                    </tr>
                                    <tr>
                                        <td class=\"project-status\">
                                            <span class=\"label label-success\">Proceso</span>
                                        </td>
                                        <td class=\"project-title\">
                                            <a href=\"#\">Chihuaha</a>
                                            <br>
                                            <small>Act. 12-Abr-2016 11:34:18</small>
                                        </td>
                                        <td class=\"project-title\">
                                        		
                                              <strong>   416 $ 200,000,00.00 </strong>
                                             <div>   
										     <small> P.: $ 180,000,00.00 </small><br>
										      <small> D.: $ 20,000,00.00 </small>
										     </div>

                                        </td>
                                        <td class=\"project-completion\">
                                              <strong>   X00 $ 200,000,00.00 </strong>
                                             <div>   
										     <small> P.: $ 180,000,00.00 </small><br>
										      <small> D.: $ 20,000,00.00 </small>
										     </div>
                                        </td>
                                        <td class=\"project-completion\">
                                              <strong>   610 $ 200,000,00.00 </strong>
                                             <div>   
										     <small> Ingresos: $ 180,000,00.00 </small><br>
										      <small> D.: $ 20,000,00.00 </small>
										     </div>
                                        </td>



                                        <td class=\"project-people\">

                                              <a id=\"view-pdf\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test.pdf\">
                                              <i class=\"fa fa-file-pdf-o fa-2x\"></i>
                                              </a>
                                              <a id=\"view-pdf\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test2.pdf\">
                                              <i class=\"fa fa-file-image-o fa-2x\"></i>
                                              </a>


                                        </td>
                                        <td class=\"project-actions\">
                                            <a id=\"timeline7\" href=\"ptfma_timeline.php?id=Chihuahua\" class=\"btn btn-w-m btn-outline btn-info\"><i class=\"fa fa-calendar fa-2x\"></i> </a>
                                        </td>
                                    </tr>
                                    <tr>
                                        <td class=\"project-status\">
                                            <span class=\"label label-primary2\">Aceptado</span>
                                        </td>
                                        <td class=\"project-title\">
                                            <a href=\"#\">Durango</a>
                                            <br>
                                            <small>Act. 13-Abr-2016 12:34:18</small>
                                        </td>
                                        <td class=\"project-title\">
                                        		
                                              <strong>   416 $ 200,000,00.00 </strong>
                                             <div>   
										     <small> P.: $ 180,000,00.00 </small><br>
										      <small> D.: $ 20,000,00.00 </small>
										     </div>

                                        </td>
                                        <td class=\"project-completion\">
                                              <strong>   X00 $ 200,000,00.00 </strong>
                                             <div>   
										     <small> P.: $ 180,000,00.00 </small><br>
										      <small> D.: $ 20,000,00.00 </small>
										     </div>
                                        </td>
                                        <td class=\"project-completion\">
                                              <strong>   610 $ 200,000,00.00 </strong>
                                             <div>   
										     <small> P.: $ 180,000,00.00 </small><br>
										      <small> D.: $ 20,000,00.00 </small>
										     </div>
                                        </td>
                                        <td class=\"project-people\">

                                              <a id=\"view-pdf\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test.pdf\">
                                              <i class=\"fa fa-file-pdf-o fa-2x\"></i>
                                              </a>
                                              <a id=\"view-pdf\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test2.pdf\">
                                              <i class=\"fa fa-file-image-o fa-2x\"></i>
                                              </a>

                                        </td>
                                        <td class=\"project-actions\">
                                            <a id=\"timeline8\" href=\"ptfma_timeline.php?id=Durango\" class=\"btn btn-w-m btn-outline btn-info\"><i class=\"fa fa-calendar fa-2x\"></i> </a>
                                        </td>
                                    </tr>
                                    <tr>
                                        <td class=\"project-status\">
                                            <span class=\"label label-primary2\">Aceptado</span>
                                        </td>
                                        <td class=\"project-title\">
                                            <a href=\"#\">Guanajuato</a>
                                            <br>
                                            <small>Created 14.07.2014</small>
                                        </td>
                                        <td class=\"project-completion\">
                                            <small>Completion with: 97%</small>
                                            <div class=\"progress progress-mini\">
                                                <div style=\"width: 97%;\" class=\"progress-bar\"></div>
                                            </div>
                                        </td>
                                        <td class=\"project-completion\">
                                                <small>Completion with: 48%</small>
                                                <div class=\"progress progress-mini\">
                                                    <div style=\"width: 48%;\" class=\"progress-bar\"></div>
                                                </div>
                                        </td>
                                        <td class=\"project-completion\">
                                                <small>Completion with: 48%</small>
                                                <div class=\"progress progress-mini\">
                                                    <div style=\"width: 48%;\" class=\"progress-bar\"></div>
                                                </div>
                                        </td>


                                        <td class=\"project-people\">

                                              <a id=\"view-pdf\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test.pdf\">
                                              <i class=\"fa fa-file-pdf-o fa-2x\"></i>
                                              </a>
                                        </td>
                                        <td class=\"project-actions\">
                                            <a href=\"#\" class=\"btn btn-w-m btn-outline btn-info\"><i class=\"fa fa-calendar\"></i> View </a>
                                        </td>
                                    </tr>
                                    <tr>
                                        <td class=\"project-status\">
                                            <span class=\"label label-primary2\">Aceptado</span>
                                        </td>
                                        <td class=\"project-title\">
                                            <a href=\"#\">Guerrero</a>
                                            <br>
                                            <small>Act. 11-Abr-2016 13:40:20</small>
                                        </td>
                                        <td class=\"project-completion\">
                                            <small>Completion with: 28%</small>
                                            <div class=\"progress progress-mini\">
                                                <div style=\"width: 28%;\" class=\"progress-bar\"></div>
                                            </div>
                                        </td>

                                        <td class=\"project-completion\">
                                                <small>Completion with: 48%</small>
                                                <div class=\"progress progress-mini\">
                                                    <div style=\"width: 48%;\" class=\"progress-bar\"></div>
                                                </div>
                                        </td>
                                        <td class=\"project-completion\">
                                                <small>Completion with: 48%</small>
                                                <div class=\"progress progress-mini\">
                                                    <div style=\"width: 48%;\" class=\"progress-bar\"></div>
                                                </div>
                                        </td>


                                        <td class=\"project-people\">

                                              <a id=\"view-pdf\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test.pdf\">
                                              <i class=\"fa fa-file-pdf-o fa-2x\"></i>
                                              </a>
                                              <a id=\"view-pdf\" class=\"btn btn-outline btn-default view-pdf\" href=\"../ods/test2.pdf\">
                                              <i class=\"fa fa-file-image-o fa-2x\"></i>
                                              </a>

                                        </td>
                                        <td class=\"project-actions\">
                                            <a href=\"#\" class=\"btn btn-w-m btn-outline btn-info\"><i class=\"fa fa-calendar\"></i> View </a>
                                        </td>
                                    </tr>
                                    </tbody>
                                </table>
		";

} // fin de fncIntegraTablaResumen



function fncBuildJSAdmin()
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
    <script src=\"../js/plugins/flot/jquery.flot.symbol.js\"></script>
    <script src=\"../js/plugins/flot/jquery.flot.time.js\"></script>

    <!-- Peity -->
    <script src=\"../js/plugins/peity/jquery.peity.min.js\"></script>
    <script src=\"../js/demo/peity-demo.js\"></script>

    <!-- Custom and plugin javascript -->
    <script src=\"../js/inspinia.js\"></script>
    <script src=\"../js/plugins/pace/pace.min.js\"></script>

    <!-- jQuery UI -->
    <script src=\"../js/plugins/jquery-ui/jquery-ui.min.js\"></script>

    <!-- Jvectormap -->
    <script src=\"../js/plugins/jvectormap/jquery-jvectormap-2.0.2.min.js\"></script>
    <script src=\"../js/plugins/jvectormap/jquery-jvectormap-world-mill-en.js\"></script>

    <!-- EayPIE -->
    <script src=\"../js/plugins/easypiechart/jquery.easypiechart.js\"></script>

    <!-- Sparkline -->
    <script src=\"../js/plugins/sparkline/jquery.sparkline.min.js\"></script>

    <!-- Sparkline demo data  -->
    <script src=\"../js/demo/sparkline-demo.js\"></script>

    <script>
        $(document).ready(function() {
            $('.chart').easyPieChart({
                barColor: '#f8ac59',
//                scaleColor: false,
                scaleLength: 5,
                lineWidth: 4,
                size: 80
            });

            $('.chart2').easyPieChart({
                barColor: '#1c84c6',
//                scaleColor: false,
                scaleLength: 5,
                lineWidth: 4,
                size: 80
            });

            var data2 = [
                [gd(2012, 1, 1), 7], [gd(2012, 1, 2), 6], [gd(2012, 1, 3), 4], [gd(2012, 1, 4), 8],
                [gd(2012, 1, 5), 9], [gd(2012, 1, 6), 7], [gd(2012, 1, 7), 5], [gd(2012, 1, 8), 4],
                [gd(2012, 1, 9), 7], [gd(2012, 1, 10), 8], [gd(2012, 1, 11), 9], [gd(2012, 1, 12), 6],
                [gd(2012, 1, 13), 4], [gd(2012, 1, 14), 5], [gd(2012, 1, 15), 11], [gd(2012, 1, 16), 8],
                [gd(2012, 1, 17), 8], [gd(2012, 1, 18), 11], [gd(2012, 1, 19), 11], [gd(2012, 1, 20), 6],
                [gd(2012, 1, 21), 6], [gd(2012, 1, 22), 8], [gd(2012, 1, 23), 11], [gd(2012, 1, 24), 13],
                [gd(2012, 1, 25), 7], [gd(2012, 1, 26), 9], [gd(2012, 1, 27), 9], [gd(2012, 1, 28), 8],
                [gd(2012, 1, 29), 5], [gd(2012, 1, 30), 8], [gd(2012, 1, 31), 25]
            ];

            var data3 = [
                [gd(2012, 1, 1), 800], [gd(2012, 1, 2), 500], [gd(2012, 1, 3), 600], [gd(2012, 1, 4), 700],
                [gd(2012, 1, 5), 500], [gd(2012, 1, 6), 456], [gd(2012, 1, 7), 800], [gd(2012, 1, 8), 589],
                [gd(2012, 1, 9), 467], [gd(2012, 1, 10), 876], [gd(2012, 1, 11), 689], [gd(2012, 1, 12), 700],
                [gd(2012, 1, 13), 500], [gd(2012, 1, 14), 600], [gd(2012, 1, 15), 700], [gd(2012, 1, 16), 786],
                [gd(2012, 1, 17), 345], [gd(2012, 1, 18), 888], [gd(2012, 1, 19), 888], [gd(2012, 1, 20), 888],
                [gd(2012, 1, 21), 987], [gd(2012, 1, 22), 444], [gd(2012, 1, 23), 999], [gd(2012, 1, 24), 567],
                [gd(2012, 1, 25), 786], [gd(2012, 1, 26), 666], [gd(2012, 1, 27), 888], [gd(2012, 1, 28), 900],
                [gd(2012, 1, 29), 178], [gd(2012, 1, 30), 555], [gd(2012, 1, 31), 993]
            ];


            var dataset = [
                {
                    label: \"Number of orders\",
                    data: data3,
                    color: \"#1ab394\",
                    bars: {
                        show: true,
                        align: \"center\",
                        barWidth: 24 * 60 * 60 * 600,
                        lineWidth:0
                    }

                }, {
                    label: \"Payments\",
                    data: data2,
                    yaxis: 2,
                    color: \"#1C84C6\",
                    lines: {
                        lineWidth:1,
                            show: true,
                            fill: true,
                        fillColor: {
                            colors: [{
                                opacity: 0.2
                            }, {
                                opacity: 0.4
                            }]
                        }
                    },
                    splines: {
                        show: false,
                        tension: 0.6,
                        lineWidth: 1,
                        fill: 0.1
                    },
                }
            ];


            var options = {
                xaxis: {
                    mode: \"time\",
                    tickSize: [3, \"day\"],
                    tickLength: 0,
                    axisLabel: \"Date\",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Arial',
                    axisLabelPadding: 10,
                    color: \"#d5d5d5\"
                },
                yaxes: [{
                    position: \"left\",
                    max: 1070,
                    color: \"#d5d5d5\",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Arial',
                    axisLabelPadding: 3
                }, {
                    position: \"right\",
                    clolor: \"#d5d5d5\",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: ' Arial',
                    axisLabelPadding: 67
                }
                ],
                legend: {
                    noColumns: 1,
                    labelBoxBorderColor: \"#000000\",
                    position: \"nw\"
                },
                grid: {
                    hoverable: false,
                    borderWidth: 0
                }
            };

            function gd(year, month, day) {
                return new Date(year, month - 1, day).getTime();
            }

            var previousPoint = null, previousLabel = null;

            $.plot($(\"#flot-dashboard-chart\"), dataset, options);

            var mapData = {
                \"US\": 298,
                \"SA\": 200,
                \"DE\": 220,
                \"FR\": 540,
                \"CN\": 120,
                \"AU\": 760,
                \"BR\": 550,
                \"IN\": 200,
                \"GB\": 120,
            };




            $('#world-map').vectorMap({
                map: 'world_mill_en',
                backgroundColor: \"transparent\",
                regionStyle: {
                    initial: {
                        fill: '#e4e4e4',
                        \"fill-opacity\": 0.9,
                        stroke: 'none',
                        \"stroke-width\": 0,
                        \"stroke-opacity\": 0
                    }
                },

                series: {
                    regions: [{
                        values: mapData,
                        scale: [\"#1ab394\", \"#22d6b1\"],
                        normalizeFunction: 'polynomial'
                    }]
                },
            });
        });
    </script>

<script>

(function(a){a.createModal=function(b){defaults={title:\"\",message:\"Your Message Goes Here!\",closeButton:true,scrollable:false};var b=a.extend({},defaults,b);var c=(b.scrollable===true)?'style=\"max-height: 420px;overflow-y: auto;\"':\"\";html='<div class=\"modal fade\" id=\"myModal\">';html+='<div class=\"modal-dialog\">';html+='<div class=\"modal-content\">';html+='<div class=\"modal-header\">';html+='<button type=\"button\" class=\"close\" data-dismiss=\"modal\" aria-hidden=\"true\">×</button>';if(b.title.length>0){html+='<h4 class=\"modal-title\">'+b.title+\"</h4>\"}html+=\"</div>\";html+='<div class=\"modal-body\" '+c+\">\";html+=b.message;html+=\"</div>\";html+='<div class=\"modal-footer\">';if(b.closeButton===true){html+='<button type=\"button\" class=\"btn btn-primary\" data-dismiss=\"modal\">Cerrar</button>'}html+=\"</div>\";html+=\"</div>\";html+=\"</div>\";html+=\"</div>\";a(\"body\").prepend(html);a(\"#myModal\").modal().on(\"hidden.bs.modal\",function(){a(this).remove()})}})(jQuery);

 $('a').on('click',function(event){
 	   // alert('lanza pdf');
        var nombreHref =$(this).attr('id');
        var patt = new RegExp(\"view-pdf\");
        var tm = new RegExp(\"timeline\");

        //alert(nombreHref);
        var pdf_link = $(this).attr('href');
        //alert(pdf_link);
        if (patt.test(nombreHref))
        {  
              
              var iframe = '<div class=\"iframe-container\"><h1> Resultado </h1><iframe src=\"'+pdf_link+'\"></iframe></div>'
              $.createModal({
              title:'Dirección General de Recursos Humanos',
              message: iframe,
              closeButton:true,
              scrollable:false
              });
        }
        else if(tm.test(nombreHref)){
            //alert('timeline');
            $(\"#tablamain\").load(pdf_link);
        }  
        else {
          //alert('Carga total');
           window.location.href = \"ptfma_admin.php\";

        }


        return false;        
    });    

</script>
<style type=\"text/css\">
        .iframe-container {    
		    padding-bottom: 60%;
		    padding-top: 30px; height: 0; overflow: hidden;
		}
 
.iframe-container iframe,
.iframe-container object,
.iframe-container embed {
	position: absolute;
	top: 0;
	left: 0;
	width: 100%;
	height: 100%;
}
    </style>



		";


} // fin de fncBuildJSAdmin()



function fncBuildBodyAdmin()
{

$Tabla = fncIntegraTablaResumen();


return "
    <table align=\"center\" height=\"60\" style=\"width: 100%\">
  <tbody><tr>
     <td width=\"40%\" align=\"left\"><img src=\"../images/logoSALUD_hoz.png\" width=\"289\" height=\"95\"></td>
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
</tbody></table>

    <div id=\"wrapper\">
    <nav class=\"navbar-default navbar-static-side\" role=\"navigation\">
        <div class=\"sidebar-collapse\">
            <ul class=\"nav metismenu\" id=\"side-menu\">
                <li class=\"nav-header\">
                    <div class=\"dropdown profile-element\"> <span>
                            <img alt=\"image\" class=\"img-circle\" src=\"../img/profile_small.jpg\" />
                             </span>
                        <a data-toggle=\"dropdown\" class=\"dropdown-toggle\" href=\"#\">
                            <span class=\"clear\"> <span class=\"block m-t-xs\"> <strong class=\"font-bold\">Noe Alvarez Salvador</strong>
                             </span> <span class=\"text-muted text-xs block\">Art Director <b class=\"caret\"></b></span> </span> </a>
                        <ul class=\"dropdown-menu animated fadeInRight m-t-xs\">
                            <li><a href=\"profile.html\">Profile</a></li>
                            <li><a href=\"contacts.html\">Contacts</a></li>
                            <li><a href=\"mailbox.html\">Mailbox</a></li>
                            <li class=\"divider\"></li>
                            <li><a href=\"../index.php\">Logout</a></li>
                        </ul>
                    </div>
                    <div class=\"logo-element\">
                        IN+
                    </div>
                </li>
                <li class=\"active\">
                    <a href=\"index.html\"><i class=\"fa fa-th-large\"></i> <span class=\"nav-label\">Productos de Nómina</span> <span class=\"fa arrow\"></span></a>
                    <ul class=\"nav nav-second-level\">
                        <li><a href=\"#\">Anteriores</a></li>
                        <li ><a href=\"ptfma_admin.php\">Quincena 7</a></li>
                        <li><a href=\"ptfma_admin.php\">Quincena 8</a></li>
                        <li class=\"active\"><a href=\"#\">Proximos</a></li>
                        
                    </ul>
                </li>
                <li>
                    <a href=\"#\"><i class=\"fa fa-bar-chart-o\"></i> <span class=\"nav-label\">Articulo 74</span><span class=\"fa arrow\"></span></a>
                    <ul class=\"nav nav-second-level collapse\">
                        <li><a href=\"#\">Anteriores</a></li>
                        <li><a href=\"#ptfma_admin.php\">Quincena 7 </a></li>
                        <li><a href=\"#ptfma_admin.php\">Quincena 8</a></li>
                        <li class=\"active\"><a href=\"#\">Proximos</a></li>
                    </ul>
                </li>
            </ul>

        </div>
    </nav>

        <div id=\"page-wrapper\" class=\"gray-bg\">
        <div class=\"row border-bottom\">
        <nav class=\"navbar navbar-static-top\" role=\"navigation\" style=\"margin-bottom: 0\">
        <div class=\"navbar-header\">
            <a class=\"navbar-minimalize minimalize-styl-2 btn btn-primary \" href=\"#\"><i class=\"fa fa-bars\"></i> </a>
            <form role=\"search\" class=\"navbar-form-custom\" action=\"#\">
                <div class=\"form-group\">
              
                </div>
            </form>
        </div>
            <ul class=\"nav navbar-top-links navbar-right\">



                <li>
                    <span class=\"m-r-sm text-muted welcome-message\">Dirección General de Recursos Humanos</span>
                </li>
                <li class=\"dropdown\">
                    <a class=\"dropdown-toggle count-info\" data-toggle=\"dropdown\" href=\"#\">
                        <i class=\"fa fa-envelope\"></i>  <span class=\"label label-warning2\">16</span>
                    </a>
                    <ul class=\"dropdown-menu dropdown-messages\">



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
                <li class=\"dropdown\">
                    <a class=\"dropdown-toggle count-info\" data-toggle=\"dropdown\" href=\"#\">
                        <i class=\"fa fa-bell\"></i>  <span class=\"label label-primary2\">8</span>
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

        </nav>
        </div>
            <div class=\"wrapper wrapper-content\">
        <div class=\"row\">
                    <div class=\"col-lg-3\">
                        <div class=\"ibox float-e-margins\">
                            <div class=\"ibox-title\">
                                <span class=\"label label-success pull-right\" style=\"background-color:#1ABF04\";>Completado</span>
                                <h5>Nómina 416</h5>
                            </div>
                            <div class=\"ibox-content\">
                                <h1 class=\"no-margins\">6,200 </h1>
                                <div class=\"stat-percent font-bold text-success\">100% 
                                    <i class=\"fa fa-bolt\"></i></div>
                                <small>Empleados</small>
                            </div>
                        </div>
                    </div>
                    <div class=\"col-lg-3\">
                        <div class=\"ibox float-e-margins\">
                            <div class=\"ibox-title\">
                                <span class=\"label label-warning2-light pull-right\">Pendiente</span>
                                <h5>Nómina X00</h5>
                            </div>
                            <div class=\"ibox-content\">
                                <h1 class=\"no-margins\">5,800</h1>
                                <div class=\"stat-percent font-bold text-info\">20% <i class=\"fa fa-level-up\"></i></div>
                                <small>Empleados</small>
                            </div>
                        </div>
                    </div>
                    <div class=\"col-lg-3\">
                        <div class=\"ibox float-e-margins\">
                            <div class=\"ibox-title\">
                                <span class=\"label label-warning2-light pull-right\">Pendiente</span>
                                <h5>Nomina 610</h5>
                            </div>
                            <div class=\"ibox-content\">
                                <h1 class=\"no-margins\">106,120</h1>
                                <div class=\"stat-percent font-bold text-navy\">44% <i class=\"fa fa-level-up\"></i></div>
                                <small>Empleados</small>
                            </div>
                        </div>
                    </div>
                    <div class=\"col-lg-3\">
                        <div class=\"ibox float-e-margins\">
                            <div class=\"ibox-title\">
                                <span class=\"label label-success pull-right\">En proceso</span>
                                <h5>Estados</h5>
                            </div>
                            <div class=\"ibox-content\">
                                <h1 class=\"no-margins\">24</h1>
                                <div class=\"stat-percent font-bold text-info\">78% <i class=\"fa fa-level-up\"></i></div>
                                <small>Terminados</small>
                            </div>
                        </div>
            </div>
        </div>


        <div class=\"row\">
                    <div class=\"col-lg-12\">

                        <div class=\"ibox float-e-margins\">

                            <div class=\"ibox-title\">


                                <h5>Quincena 7 Resumen de Envios</h5>
                                <div class=\"pull-right\">

                                Fecha Limite 22 de Abril del 2016
                                </div>

                            </div>


                <div class=\"ibox-content\">
                         <div class=\"row\">

                                <div id=\"tablamain\" class=\"col-lg-12\">
                                	$Tabla
                                </div>

                        </div>
                </div>

            </div>
        </div>
    </div>


        <div class=\"footer\">
            <div class=\"pull-right\">
                10GB of <strong>250GB</strong> Free.
            </div>
            <div>
                <strong>Copyright</strong> Example Company &copy; 2014-2015
            </div>
        </div>
        </div>
        <div id=\"right-sidebar\">
            <div class=\"sidebar-container\">

                <ul class=\"nav nav-tabs navs-3\">

                    <li class=\"active\"><a data-toggle=\"tab\" href=\"#tab-1\">
                        Notes
                    </a></li>
                    <li><a data-toggle=\"tab\" href=\"#tab-2\">
                        Projects
                    </a></li>
                    <li class=\"\"><a data-toggle=\"tab\" href=\"#tab-3\">
                        <i class=\"fa fa-gear\"></i>
                    </a></li>
                </ul>

                <div class=\"tab-content\">


                    <div id=\"tab-1\" class=\"tab-pane active\">

                        <div class=\"sidebar-title\">
                            <h3> <i class=\"fa fa-comments-o\"></i> Latest Notes</h3>
                            <small><i class=\"fa fa-tim\"></i> You have 10 new message.</small>
                        </div>

                        <div>

                            <div class=\"sidebar-message\">
                                <a href=\"#\">
                                    <div class=\"pull-left text-center\">
                                        <img alt=\"image\" class=\"img-circle message-avatar\" src=\"../img/a1.jpg\">

                                        <div class=\"m-t-xs\">
                                            <i class=\"fa fa-star text-warning\"></i>
                                            <i class=\"fa fa-star text-warning\"></i>
                                        </div>
                                    </div>
                                    <div class=\"media-body\">

                                        There are many variations of passages of Lorem Ipsum available.
                                        <br>
                                        <small class=\"text-muted\">Today 4:21 pm</small>
                                    </div>
                                </a>
                            </div>
                            <div class=\"sidebar-message\">
                                <a href=\"#\">
                                    <div class=\"pull-left text-center\">
                                        <img alt=\"image\" class=\"img-circle message-avatar\" src=\"../img/a2.jpg\">
                                    </div>
                                    <div class=\"media-body\">
                                        The point of using Lorem Ipsum is that it has a more-or-less normal.
                                        <br>
                                        <small class=\"text-muted\">Yesterday 2:45 pm</small>
                                    </div>
                                </a>
                            </div>
                            <div class=\"sidebar-message\">
                                <a href=\"#\">
                                    <div class=\"pull-left text-center\">
                                        <img alt=\"image\" class=\"img-circle message-avatar\" src=\"../img/a3.jpg\">

                                        <div class=\"m-t-xs\">
                                            <i class=\"fa fa-star text-warning\"></i>
                                            <i class=\"fa fa-star text-warning\"></i>
                                            <i class=\"fa fa-star text-warning\"></i>
                                        </div>
                                    </div>
                                    <div class=\"media-body\">
                                        Mevolved over the years, sometimes by accident, sometimes on purpose (injected humour and the like).
                                        <br>
                                        <small class=\"text-muted\">Yesterday 1:10 pm</small>
                                    </div>
                                </a>
                            </div>
                            <div class=\"sidebar-message\">
                                <a href=\"#\">
                                    <div class=\"pull-left text-center\">
                                        <img alt=\"image\" class=\"img-circle message-avatar\" src=\"../img/a4.jpg\">
                                    </div>

                                    <div class=\"media-body\">
                                        Lorem Ipsum, you need to be sure there isn't anything embarrassing hidden in the
                                        <br>
                                        <small class=\"text-muted\">Monday 8:37 pm</small>
                                    </div>
                                </a>
                            </div>
                            <div class=\"sidebar-message\">
                                <a href=\"#\">
                                    <div class=\"pull-left text-center\">
                                        <img alt=\"image\" class=\"img-circle message-avatar\" src=\"../img/a8.jpg\">
                                    </div>
                                    <div class=\"media-body\">

                                        All the Lorem Ipsum generators on the Internet tend to repeat.
                                        <br>
                                        <small class=\"text-muted\">Today 4:21 pm</small>
                                    </div>
                                </a>
                            </div>
                            <div class=\"sidebar-message\">
                                <a href=\"#\">
                                    <div class=\"pull-left text-center\">
                                        <img alt=\"image\" class=\"img-circle message-avatar\" src=\"../img/a7.jpg\">
                                    </div>
                                    <div class=\"media-body\">
                                        Renaissance. The first line of Lorem Ipsum, \"Lorem ipsum dolor sit amet..\", comes from a line in section 1.10.32.
                                        <br>
                                        <small class=\"text-muted\">Yesterday 2:45 pm</small>
                                    </div>
                                </a>
                            </div>
                            <div class=\"sidebar-message\">
                                <a href=\"#\">
                                    <div class=\"pull-left text-center\">
                                        <img alt=\"image\" class=\"img-circle message-avatar\" src=\"../img/a3.jpg\">

                                        <div class=\"m-t-xs\">
                                            <i class=\"fa fa-star text-warning\"></i>
                                            <i class=\"fa fa-star text-warning\"></i>
                                            <i class=\"fa fa-star text-warning\"></i>
                                        </div>
                                    </div>
                                    <div class=\"media-body\">
                                        The standard chunk of Lorem Ipsum used since the 1500s is reproduced below.
                                        <br>
                                        <small class=\"text-muted\">Yesterday 1:10 pm</small>
                                    </div>
                                </a>
                            </div>
                            <div class=\"sidebar-message\">
                                <a href=\"#\">
                                    <div class=\"pull-left text-center\">
                                        <img alt=\"image\" class=\"img-circle message-avatar\" src=\"../img/a4.jpg\">
                                    </div>
                                    <div class=\"media-body\">
                                        Uncover many web sites still in their infancy. Various versions have.
                                        <br>
                                        <small class=\"text-muted\">Monday 8:37 pm</small>
                                    </div>
                                </a>
                            </div>
                        </div>

                    </div>

                    <div id=\"tab-2\" class=\"tab-pane\">

                        <div class=\"sidebar-title\">
                            <h3> <i class=\"fa fa-cube\"></i> Latest projects</h3>
                            <small><i class=\"fa fa-tim\"></i> You have 14 projects. 10 not completed.</small>
                        </div>

                        <ul class=\"sidebar-list\">
                            <li>
                                <a href=\"#\">
                                    <div class=\"small pull-right m-t-xs\">9 hours ago</div>
                                    <h4>Business valuation</h4>
                                    It is a long established fact that a reader will be distracted.

                                    <div class=\"small\">Completion with: 22%</div>
                                    <div class=\"progress progress-mini\">
                                        <div style=\"width: 22%;\" class=\"progress-bar progress-bar-warning\"></div>
                                    </div>
                                    <div class=\"small text-muted m-t-xs\">Project end: 4:00 pm - 12.06.2014</div>
                                </a>
                            </li>
                            <li>
                                <a href=\"#\">
                                    <div class=\"small pull-right m-t-xs\">9 hours ago</div>
                                    <h4>Contract with Company </h4>
                                    Many desktop publishing packages and web page editors.

                                    <div class=\"small\">Completion with: 48%</div>
                                    <div class=\"progress progress-mini\">
                                        <div style=\"width: 48%;\" class=\"progress-bar\"></div>
                                    </div>
                                </a>
                            </li>
                            <li>
                                <a href=\"#\">
                                    <div class=\"small pull-right m-t-xs\">9 hours ago</div>
                                    <h4>Meeting</h4>
                                    By the readable content of a page when looking at its layout.

                                    <div class=\"small\">Completion with: 14%</div>
                                    <div class=\"progress progress-mini\">
                                        <div style=\"width: 14%;\" class=\"progress-bar progress-bar-info\"></div>
                                    </div>
                                </a>
                            </li>
                            <li>
                                <a href=\"#\">
                                    <span class=\"label label-primary2 pull-right\">NEW</span>
                                    <h4>The generated</h4>
                                    <!--<div class=\"small pull-right m-t-xs\">9 hours ago</div>-->
                                    There are many variations of passages of Lorem Ipsum available.
                                    <div class=\"small\">Completion with: 22%</div>
                                    <div class=\"small text-muted m-t-xs\">Project end: 4:00 pm - 12.06.2014</div>
                                </a>
                            </li>
                            <li>
                                <a href=\"#\">
                                    <div class=\"small pull-right m-t-xs\">9 hours ago</div>
                                    <h4>Business valuation</h4>
                                    It is a long established fact that a reader will be distracted.

                                    <div class=\"small\">Completion with: 22%</div>
                                    <div class=\"progress progress-mini\">
                                        <div style=\"width: 22%;\" class=\"progress-bar progress-bar-warning\"></div>
                                    </div>
                                    <div class=\"small text-muted m-t-xs\">Project end: 4:00 pm - 12.06.2014</div>
                                </a>
                            </li>
                            <li>
                                <a href=\"#\">
                                    <div class=\"small pull-right m-t-xs\">9 hours ago</div>
                                    <h4>Contract with Company </h4>
                                    Many desktop publishing packages and web page editors.

                                    <div class=\"small\">Completion with: 48%</div>
                                    <div class=\"progress progress-mini\">
                                        <div style=\"width: 48%;\" class=\"progress-bar\"></div>
                                    </div>
                                </a>
                            </li>
                            <li>
                                <a href=\"#\">
                                    <div class=\"small pull-right m-t-xs\">9 hours ago</div>
                                    <h4>Meeting</h4>
                                    By the readable content of a page when looking at its layout.

                                    <div class=\"small\">Completion with: 14%</div>
                                    <div class=\"progress progress-mini\">
                                        <div style=\"width: 14%;\" class=\"progress-bar progress-bar-info\"></div>
                                    </div>
                                </a>
                            </li>
                            <li>
                                <a href=\"#\">
                                    <span class=\"label label-primary2 pull-right\">NEW</span>
                                    <h4>The generated</h4>
                                    <!--<div class=\"small pull-right m-t-xs\">9 hours ago</div>-->
                                    There are many variations of passages of Lorem Ipsum available.
                                    <div class=\"small\">Completion with: 22%</div>
                                    <div class=\"small text-muted m-t-xs\">Project end: 4:00 pm - 12.06.2014</div>
                                </a>
                            </li>

                        </ul>

                    </div>

                    <div id=\"tab-3\" class=\"tab-pane\">

                        <div class=\"sidebar-title\">
                            <h3><i class=\"fa fa-gears\"></i> Settings</h3>
                            <small><i class=\"fa fa-tim\"></i> You have 14 projects. 10 not completed.</small>
                        </div>

                        <div class=\"setings-item\">
                    <span>
                        Show notifications
                    </span>
                            <div class=\"switch\">
                                <div class=\"onoffswitch\">
                                    <input type=\"checkbox\" name=\"collapsemenu\" class=\"onoffswitch-checkbox\" id=\"example\">
                                    <label class=\"onoffswitch-label\" for=\"example\">
                                        <span class=\"onoffswitch-inner\"></span>
                                        <span class=\"onoffswitch-switch\"></span>
                                    </label>
                                </div>
                            </div>
                        </div>
                        <div class=\"setings-item\">
                    <span>
                        Disable Chat
                    </span>
                            <div class=\"switch\">
                                <div class=\"onoffswitch\">
                                    <input type=\"checkbox\" name=\"collapsemenu\" checked class=\"onoffswitch-checkbox\" id=\"example2\">
                                    <label class=\"onoffswitch-label\" for=\"example2\">
                                        <span class=\"onoffswitch-inner\"></span>
                                        <span class=\"onoffswitch-switch\"></span>
                                    </label>
                                </div>
                            </div>
                        </div>
                        <div class=\"setings-item\">
                    <span>
                        Enable history
                    </span>
                            <div class=\"switch\">
                                <div class=\"onoffswitch\">
                                    <input type=\"checkbox\" name=\"collapsemenu\" class=\"onoffswitch-checkbox\" id=\"example3\">
                                    <label class=\"onoffswitch-label\" for=\"example3\">
                                        <span class=\"onoffswitch-inner\"></span>
                                        <span class=\"onoffswitch-switch\"></span>
                                    </label>
                                </div>
                            </div>
                        </div>
                        <div class=\"setings-item\">
                    <span>
                        Show charts
                    </span>
                            <div class=\"switch\">
                                <div class=\"onoffswitch\">
                                    <input type=\"checkbox\" name=\"collapsemenu\" class=\"onoffswitch-checkbox\" id=\"example4\">
                                    <label class=\"onoffswitch-label\" for=\"example4\">
                                        <span class=\"onoffswitch-inner\"></span>
                                        <span class=\"onoffswitch-switch\"></span>
                                    </label>
                                </div>
                            </div>
                        </div>
                        <div class=\"setings-item\">
                    <span>
                        Offline users
                    </span>
                            <div class=\"switch\">
                                <div class=\"onoffswitch\">
                                    <input type=\"checkbox\" checked name=\"collapsemenu\" class=\"onoffswitch-checkbox\" id=\"example5\">
                                    <label class=\"onoffswitch-label\" for=\"example5\">
                                        <span class=\"onoffswitch-inner\"></span>
                                        <span class=\"onoffswitch-switch\"></span>
                                    </label>
                                </div>
                            </div>
                        </div>
                        <div class=\"setings-item\">
                    <span>
                        Global search
                    </span>
                            <div class=\"switch\">
                                <div class=\"onoffswitch\">
                                    <input type=\"checkbox\" checked name=\"collapsemenu\" class=\"onoffswitch-checkbox\" id=\"example6\">
                                    <label class=\"onoffswitch-label\" for=\"example6\">
                                        <span class=\"onoffswitch-inner\"></span>
                                        <span class=\"onoffswitch-switch\"></span>
                                    </label>
                                </div>
                            </div>
                        </div>
                        <div class=\"setings-item\">
                    <span>
                        Update everyday
                    </span>
                            <div class=\"switch\">
                                <div class=\"onoffswitch\">
                                    <input type=\"checkbox\" name=\"collapsemenu\" class=\"onoffswitch-checkbox\" id=\"example7\">
                                    <label class=\"onoffswitch-label\" for=\"example7\">
                                        <span class=\"onoffswitch-inner\"></span>
                                        <span class=\"onoffswitch-switch\"></span>
                                    </label>
                                </div>
                            </div>
                        </div>

                        <div class=\"sidebar-content\">
                            <h4>Settings</h4>
                            <div class=\"small\">
                                I belive that. Lorem Ipsum is simply dummy text of the printing and typesetting industry.
                                And typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s.
                                Over the years, sometimes by accident, sometimes on purpose (injected humour and the like).
                            </div>
                        </div>

                    </div>
                </div>

            </div>



        </div>
    </div>


	";

}// fin de fncBuildBodyAdmin()


?>
