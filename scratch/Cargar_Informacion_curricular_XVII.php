<?php

//
// proceso de carga de l tabla Remuneraciones_VIII
// FASE I Descarga de Informacion.
//
ini_set('memory_limit', '1024M');
ini_set('max_execution_time', 1200);
require('ac_db_pn.php');
$db = new DbOracle("pro_nomina", "ArchiSoft");
error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);
date_default_timezone_set('America/Mexico_City');

function cellColor($objPHPExcel,$cells,$color){
//    global $objPHPExcel;

    $objPHPExcel->getActiveSheet()->getStyle($cells)->getFill()->applyFromArray(array(
        'type' => PHPExcel_Style_Fill::FILL_SOLID,
        'startcolor' => array(
             'rgb' => $color
        )
    ));
}

//define('EOL',(PHP_SAPI == 'cli') ? PHP_EOL : '<br />');

/** Include PHPExcel */
//echo dirname(__FILE__) . '/../Classes/PHPExcel.php' ." << <br>";
require_once dirname(__FILE__) . '/../transparencia/Classes/PHPExcel.php';
echo date('H:i:s') , " Inicio" , "<br>";
$styleArray = array(
    'font'  => array(
        'bold'  => true,
        'color' => array('rgb' => 'FFFFFF'),
        'size'  => 12,
        'name'  => 'Arial'
    ));
// Create new PHPExcel object
//echo date('H:i:s') , " Create new PHPExcel object" , "<br>";
$objPHPExcel = new PHPExcel();

$ArrNivEsc = file('niv_esc.txt');

$objPHPExcel->getProperties()->setCreator("Secretaria de Salud")
               ->setLastModifiedBy("Dirección de Automatización de Procesos y Soporte Técnico")
               ->setTitle("Sistema Nacional de Transparencia")
               ->setSubject("Sistema Integrador / Vacantes")
               ->setDescription("XVII. Información curricular y las sanciones administrativas definitivas de los(as) servidores(as) públicas(os) y/o personas que desempeñen un empleo, cargo o comisión")
               ->setKeywords("Dirección General de Recursos Humanos")
               ->setCategory("Archivo de Carga Masiva");
// Add some data
//echo date('H:i:s') , " Add some data" , EOL;
$objPHPExcel->setActiveSheetIndex(0)
            ->setCellValue('A7', 'Clave o nivel del puesto')
            ->setCellValue('B7', 'Denominación de puesto')
            ->setCellValue('C7', 'Denominación del cargo')
            ->setCellValue('D7', 'Nombre(s) ')
            ->setCellValue('E7', 'Primer Apellido ')
            ->setCellValue('F7', 'Segundo Apellido')
            ->setCellValue('G7', 'Área o unidad administrativa de adscripción')  
			->setCellValue('H7', 'Nivel máximo de estudios')  
			->setCellValue('I7', 'Area Estudio')
			->setCellValue('J7', 'Carrera Genérica')
            ->setCellValue('K7', 'inicio (Periodo día/mes/año)')
            ->setCellValue('L7', 'conclusión (Periodo día/mes/año) ')
            ->setCellValue('M7', 'Denominación de la Institución / empresa')
            ->setCellValue('N7', 'Cargo o puesto desempeñado')  
			->setCellValue('O7', 'Campo de experiencia')  
			->setCellValue('P7', 'Hipervínculo a la versión pública del currículum')
            ->setCellValue('Q7', 'El servidor(a) Público(a) ha tenido sanciones administrativas definitivas aplicadas por la autoridad competente al servidor público, en el sujeto obligado que labora actualmente: sí/no')
								;



$sql = " select rfc, serpub,cr,ur,puesto,denopuesto,denocargo,
nombre,nivelpuesto,qnaproc,indmando,tipotrab,areaads, count(*)
from (select rfc, 'Servidor Público' as serpub, b.cr, b.ur, b.puesto ,
(select descripcion from cat_puestos where codigo=b.puesto) as denopuesto,
case   when indmando in ('10', '20', '30') or puesto like '%CFP%' then 
			(select den_pto from rusp_remu where rfc=b.rfc and rownum=1)
            else
              NULL
            end   as denocargo,
b.nombre,
case   when indmando in ('10', '20', '30') or puesto like '%CFP%' then 
              substr(PUESTO,3,1) ||substr(PUESTO,4,1)|| substr(PUESTO,7,1)
            else
              PUESTO
            end  as nivelpuesto,
b.QNAPROC, b.LLAVE, b.INDMANDO,b.TIPOTRAB ,           
(select descripcion from cat_UR where UR=b.UR) as AREAADS
from bdac2016 b
where b.partida ='11301' and b.INDMANDO not in ('90','80') and b.tipnom IN ('11','6L')  
and b.QNAPROC='12' and b.tipotrab!='20') ssa
group by rfc, serpub,cr,ur,puesto,denopuesto,denocargo,nombre,nivelpuesto,qnaproc,indmando,tipotrab,areaads
";

$res = $db->execFetchAll($sql, "pro_nomina");
$Contador =8;
$MSG=	"NO APLICA DE ACUERDO AL MANUAL DE PERCEPCIONES";
foreach ($res as $row) {
		$SerPub =$row['SERPUB'];
		$UR=$row['UR'];
		$CveNiv =$row['NIVELPUESTO'];
		$Puesto=$row['DENOPUESTO'];
		$Denocargo=$row['DENOCARGO'];
		$Nombre=$row['NOMBRE'];
		$ArrNombre = explode("/",$Nombre);
		if(is_array($ArrNombre)){
			
			if (!isset($ArrNombre[1])){
				//print_r ($ArrNombre);
				$NombreEmpleado = "XXXXXXX";
				$ArrApellidos = "XXXXXXX";
				$ApePaterno =$Nombre;
				$ApeMaterno =$Nombre;
			}
			else{
				$NombreEmpleado = $ArrNombre[1];
				$ArrApellidos = explode(",",$ArrNombre[0]);
				if(is_array($ArrApellidos)){

					$ApePaterno =$ArrApellidos[0]  ;
					if(isset($ArrApellidos[1]))
						$ApeMaterno =$ArrApellidos[1]  ;
					else{
							$NombreEmpleado = "XXXXXXX";
							$ApePaterno =$Nombre ;
							$ApeMaterno =$Nombre ;
						}
				}
				else{
					$NombreEmpleado = "XXXXXXX";
					$ApePaterno =$Nombre ;
					$ApeMaterno =$Nombre ;
				}
			}
		}
		else{
			$NombreEmpleado=$Nombre;
			$ApePaterno =$Nombre;
			$ApeMaterno =$Nombre;
		}
		$AreaAds=$row['AREAADS'];
		$TIPOTRAB=$row['TIPOTRAB'];
		$QNAPROC = $row['QNAPROC'];	

		$RFC =$row['RFC'];
		$ApoEcoPer="";
		$PrimaPer="";
		$EstimuloPer="";
		
		$PrestacionesEconomicasPer="";
		if ($NombreEmpleado!="XXXXXXX"){
		  	$NivId=$MSG;
		  	$NivelEscolaridad=$MSG;
		  	echo "$RFC|";
		
		 	$sqlIN = "select case when TRIM(UPPER(NIV_ESC)) <> 'NULL'	THEN
		 					NIV_ESC
		 					else 
		 						'0'
		 					end NIVEL
					from rusp
					where rfc=:rfcv and qna='11'";
	    	$res = $db->execFetchAll($sqlIN, "Query Example", array(array(":rfcv", $RFC, -1)));
	        foreach ($res as $rowIN) {
	        //	echo "id Puestos >". $row['PUESTOS_ID'] ."| <BR>";
	        		
	        	$NivId =$rowIN['NIVEL'];
	        	$NivelEscolaridad ="";
	        	if ($NivId > 0)
	        		//$NivelEscolaridad = "-" . $NivId ;
	        		$NivelEscolaridad = utf8_encode($ArrNivEsc[$NivId])  ;
	        	break;
	        }	
     	    echo "$NivId|$NivelEscolaridad| <br>";  

		  $currencyFormat = '_($* #,##0.00_);_($* (#,##0.00);_($* "-"??_);_(@_)';
		  $objPHPExcel->getActiveSheet()->getStyle('J'.($Contador))->getNumberFormat()->setFormatCode($currencyFormat);	

	      $objPHPExcel->setActiveSheetIndex(0)
            ->setCellValueExplicit('A'.$Contador, $CveNiv,PHPExcel_Cell_DataType::TYPE_STRING)
            ->setCellValueExplicit('B'.$Contador, $Puesto,PHPExcel_Cell_DataType::TYPE_STRING)
            ->setCellValue('C'.$Contador, $Denocargo)
            ->setCellValueExplicit('D'.$Contador, $NombreEmpleado,PHPExcel_Cell_DataType::TYPE_STRING)
            ->setCellValueExplicit('E'.$Contador, $ApePaterno,PHPExcel_Cell_DataType::TYPE_STRING)
            ->setCellValue('F'.$Contador, $ApeMaterno)
            ->setCellValue('G'.$Contador, $AreaAds)
            ->setCellValue('H'.$Contador, $NivelEscolaridad)
            ->setCellValue('J'.($Contador), $MSG)
            ->setCellValue('k'.($Contador), $MSG)
            ->setCellValue('L'.$Contador, $MSG)
            ->setCellValueExplicit('M'.$Contador, $MSG,PHPExcel_Cell_DataType::TYPE_STRING)
            ->setCellValueExplicit('N'.$Contador, $MSG,PHPExcel_Cell_DataType::TYPE_STRING)
			->setCellValue('O'.$Contador, $MSG)
            ->setCellValue('P'.$Contador, $MSG)
            ->setCellValue('Q'.$Contador, $MSG);
          $Contador++;  
		}		
	}	// fin del for reach

$objPHPExcel->getActiveSheet()
                ->getColumnDimension('A')
                ->setAutoSize(true);
$objPHPExcel->getActiveSheet()
                ->getColumnDimension('B')
                ->setAutoSize(true);
$objPHPExcel->getActiveSheet()
                ->getColumnDimension('C')
                ->setAutoSize(true);
$objPHPExcel->getActiveSheet()
                ->getColumnDimension('D')
                ->setAutoSize(true);
$objPHPExcel->getActiveSheet()
                ->getColumnDimension('E')
                ->setAutoSize(true);
$objPHPExcel->getActiveSheet()
                ->getColumnDimension('F')
                ->setAutoSize(true);

cellColor($objPHPExcel,'A7:AL7', '0A0765');
$objPHPExcel->getActiveSheet()->getStyle('A1')->applyFromArray($styleArray);
$objPHPExcel->getActiveSheet()->getStyle('B1')->applyFromArray($styleArray);
$objPHPExcel->getActiveSheet()->getStyle('c1')->applyFromArray($styleArray);
$objPHPExcel->getActiveSheet()->getStyle('D1')->applyFromArray($styleArray);
$objPHPExcel->getActiveSheet()->getStyle('E1')->applyFromArray($styleArray);
$objPHPExcel->getActiveSheet()->getStyle('F1')->applyFromArray($styleArray);
$objPHPExcel->getActiveSheet()->getStyle('G1')->applyFromArray($styleArray);

$objWriter = PHPExcel_IOFactory::createWriter($objPHPExcel, 'Excel2007');
$objWriter->save("XVII_Informacion.xlsx");
echo date('H:i:s') , " Fin" , "<br>";

?>		        