<?php

//
// proceso de carga de l tabla Remuneraciones_VIII
// FASE I Descarga de Informacion.
//
ini_set('memory_limit', '1024M');
ini_set('max_execution_time', 1200);
require('../general/generales.inc');
require('ac_db_pn.php');
$db = new DbOracle("pro_nomina", "ArchiSoft");
error_reporting(E_ALL);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);
date_default_timezone_set('Europe/London');

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


$Trimestres = array("06" , "09","12"); 

$styleArray = array(
    'font'  => array(
        'bold'  => true,
        'color' => array('rgb' => 'FFFFFF'),
        'size'  => 12,
        'name'  => 'Arial'
    ));
// Create new PHPExcel object
//echo date('H:i:s') , " Create new PHPExcel object" , "<br>";

foreach ($Trimestres as $Trim) { 

	$objPHPExcel = new PHPExcel();
	$objPHPExcel->getProperties()->setCreator("Secretaria de Salud")
	               ->setLastModifiedBy("Dirección de Automatización de Procesos y Soporte Técnico")
	               ->setTitle("Sistema Nacional de Transparencia")
	               ->setSubject("Sistema Integrador / Vacantes")
	               ->setDescription("Plazas Vacantes del Personal de base y Confianza ")
	               ->setKeywords("Dirección General de Recursos Humanos")
	               ->setCategory("Archivo de Carga Masiva");
	// Add some data
	//echo date('H:i:s') , " Add some data" , EOL;

	$objPHPExcel->createSheet();
	$objPHPExcel->createSheet();
	$objPHPExcel->createSheet();
	$objPHPExcel->createSheet();
	$objPHPExcel->createSheet();
	$objPHPExcel->createSheet();

	PHPExcel_Cell::setValueBinder( new PHPExcel_Cell_AdvancedValueBinder() );


	$objPHPExcel->setActiveSheetIndex(0)
	            ->setCellValue('A7', 'Tipo de integrante del Sujeto obligado')
	            ->setCellValue('B7', 'Clave o nivel del puesto ')
	            ->setCellValue('C7', 'Denominación del puesto')
	            ->setCellValue('D7', 'Denominación del cargo')
	            ->setCellValue('E7', 'Área de adscripción')
	            ->setCellValue('F7', 'Nombre completo')
	            ->setCellValue('G7', 'Primer apellido')  
				->setCellValue('H7', 'Segundo apellido')  
				->setCellValue('I7', 'Sexo (femenino/Masculino')


	            ->setCellValue('J7', 'Remuneración mensual bruta')
	            ->setCellValue('K7', 'Remuneración mensual neta.')
	            ->setCellValue('L7', 'Percepciones en efectivo:')
	            ->setCellValue('M7', 'Percepciones adicionales o en especie')  
				->setCellValue('N7', 'Periodicidad')  
				->setCellValue('O7', 'Ingresos')

	            ->setCellValue('P7', 'Sistemas de compensación')
	            ->setCellValue('Q7', 'Gratificaciones.')
	            ->setCellValue('R7', 'Periodicidad')
	            ->setCellValue('S7', 'Primas')  


				->setCellValue('T7', 'Comisiones')  
				->setCellValue('U7', 'Periodicidad')

	            ->setCellValue('V7', 'Dietas.')
	            ->setCellValue('W7', 'Periodicidad')
	            ->setCellValue('X7', 'Bonos.')
	            ->setCellValue('Y7', 'Periodicidad')  
				->setCellValue('Z7', 'Estímulos.')  
				->setCellValue('AA7', 'Periodicidad')

	            ->setCellValue('AB7', 'Apoyos económicos.')
	            ->setCellValue('AC7', 'Periodicidad.')
	            ->setCellValue('AD7', 'Prestaciones económicas')
	            ->setCellValue('AE7', 'Prestaciones en especie.')  
				->setCellValue('AF7', 'Periodicidad')  
				->setCellValue('AG7', 'Otro tipo de percepción.')
	            ->setCellValue('AH7', 'Fecha de validación')
	            ->setCellValue('AI7', 'Área responsable de la información')  
				->setCellValue('AJ7', 'Año')  
				->setCellValue('AK7', 'Fecha de actualización')
				->setCellValue('AL7', 'Nota')  ;

	$objPHPExcel->getActiveSheet()->setTitle('Reporte de Formatos');

	$objPHPExcel->setActiveSheetIndex(UNO)
	            ->setCellValue('A1', 'Miembro del poder judicial')
	            ->setCellValue('A2', 'Representante popular')
	            ->setCellValue('A3', 'Prestador de servicios profesionales')
	            ->setCellValue('A4', 'Funcionario')
	            ->setCellValue('A5', 'Otro')
	            ->setCellValue('A6', 'Servidor público')
	            ->setCellValue('A7', 'Miembro de órgano autónomo')
	            ->setCellValue('A8', 'Empleado')
	            ->setCellValue('A9', 'Personal de confianza');

	$objPHPExcel->getActiveSheet()->setTitle('hidden1');            

	$objPHPExcel->setActiveSheetIndex(DOS)
	            ->setCellValue('A1', 'Femenino')
	            ->setCellValue('A2', 'Masculino');

	$objPHPExcel->getActiveSheet()->setTitle('hidden2');            


	$objPHPExcel->setActiveSheetIndex(TRES)
	            ->setCellValueExplicit('B1', '3',PHPExcel_Cell_DataType::TYPE_STRING)
	            ->setCellValueExplicit('B2', '2121',PHPExcel_Cell_DataType::TYPE_STRING)
	            ->setCellValueExplicit('C1', '1',PHPExcel_Cell_DataType::TYPE_STRING)   
	            ->setCellValueExplicit('C2', '2122',PHPExcel_Cell_DataType::TYPE_STRING)
	            ->setCellValueExplicit('D1', '1',PHPExcel_Cell_DataType::TYPE_STRING)
	            ->setCellValueExplicit('D2', '2123',PHPExcel_Cell_DataType::TYPE_STRING)   
	            ->setCellValue('A3', 'ID')
	            ->setCellValue('B3', 'Percepción (monto)')
	            ->setCellValue('C3', 'Periodicidad')
	            ->setCellValue('D3', 'Moneda (especificar)')               ;
	$objPHPExcel->getActiveSheet()->getRowDimension(UNO)->setVisible(false);
	$objPHPExcel->getActiveSheet()->getRowDimension(DOS)->setVisible(false);
	$objPHPExcel->getActiveSheet()->setTitle('Tabla 10180');            



	$objPHPExcel->setActiveSheetIndex(CUATRO)
	            ->setCellValueExplicit('B1', '1',PHPExcel_Cell_DataType::TYPE_STRING)
	            ->setCellValueExplicit('B2', '2115',PHPExcel_Cell_DataType::TYPE_STRING)
	            ->setCellValueExplicit('C1', '1',PHPExcel_Cell_DataType::TYPE_STRING)   
	            ->setCellValueExplicit('C2', '2116',PHPExcel_Cell_DataType::TYPE_STRING)
	            ->setCellValueExplicit('D1', '3',PHPExcel_Cell_DataType::TYPE_STRING)
	            ->setCellValueExplicit('D2', '2117',PHPExcel_Cell_DataType::TYPE_STRING)   
	            ->setCellValue('A3', 'ID')
	            ->setCellValue('B3', 'Moneda (especifique)')
	            ->setCellValue('C3', 'Periodicidad')
	            ->setCellValue('D3', 'Ingresos')               ;
	$objPHPExcel->getActiveSheet()->getRowDimension(UNO)->setVisible(false);
	$objPHPExcel->getActiveSheet()->getRowDimension(DOS)->setVisible(false);
	$objPHPExcel->getActiveSheet()->setTitle('Tabla 10150');            


	$objPHPExcel->setActiveSheetIndex(CINCO)
	            ->setCellValueExplicit('B1', '3',PHPExcel_Cell_DataType::TYPE_STRING)
	            ->setCellValueExplicit('B2', '2118',PHPExcel_Cell_DataType::TYPE_STRING)
	            ->setCellValueExplicit('C1', '1',PHPExcel_Cell_DataType::TYPE_STRING)   
	            ->setCellValueExplicit('C2', '2119',PHPExcel_Cell_DataType::TYPE_STRING)
	            ->setCellValueExplicit('D1', '1',PHPExcel_Cell_DataType::TYPE_STRING)
	            ->setCellValueExplicit('D2', '2120',PHPExcel_Cell_DataType::TYPE_STRING)   
	            ->setCellValue('A3', 'ID')
	            ->setCellValue('B3', 'Sistema de compensación')
	            ->setCellValue('C3', 'Periodicidad')
	            ->setCellValue('D3', 'Moneda (especifique)')               ;
	$objPHPExcel->getActiveSheet()->getRowDimension(UNO)->setVisible(false);
	$objPHPExcel->getActiveSheet()->getRowDimension(DOS)->setVisible(false);
	$objPHPExcel->getActiveSheet()->setTitle('Tabla 10160');            

	$objPHPExcel->setActiveSheetIndex(SEIS)
	            ->setCellValueExplicit('B1', '1',PHPExcel_Cell_DataType::TYPE_STRING)
	            ->setCellValueExplicit('B2', '2124',PHPExcel_Cell_DataType::TYPE_STRING)
	            ->setCellValueExplicit('C1', '3',PHPExcel_Cell_DataType::TYPE_STRING)   
	            ->setCellValueExplicit('C2', '2125',PHPExcel_Cell_DataType::TYPE_STRING)
	            ->setCellValueExplicit('D1', '1',PHPExcel_Cell_DataType::TYPE_STRING)
	            ->setCellValueExplicit('D2', '2126',PHPExcel_Cell_DataType::TYPE_STRING)   
	            ->setCellValue('A3', 'ID')
	            ->setCellValue('B3', 'Moneda (especifique)')
	            ->setCellValue('C3', 'Primas')
	            ->setCellValue('D3', 'Periodicidad')               ;
	$objPHPExcel->getActiveSheet()->getRowDimension(UNO)->setVisible(false);
	$objPHPExcel->getActiveSheet()->getRowDimension(DOS)->setVisible(false);
	$objPHPExcel->getActiveSheet()->setTitle('Tabla 10181');            



	$sql = " select rfc, serpub,cr,ur,puesto,denopuesto,denocargo,nombre,nivelpuesto,qnaproc,indmando,tipotrab,areaads, 
	sum(Sueldo) sueldo,sum(dEDUCCIONES) deducciones,sum(PRIMA) prima, sum(Estimulos) estimulos, sum(ApoyoEconomico) apoyoeconomico,sum(PrestacionesEconomicas) prestacioneseconomicas
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
	(select descripcion from cat_UR where UR=b.UR) as AREAADS,
	(select sum(importe) from btac2016 where llave=b.llave and  tconcep=1 and  CONCEP in('06', '07','42','55') and PTAANT in ('00','CG','AG')) as Sueldo,
	(select sum(importe) from btac2016 where llave=b.llave and  tconcep=2 and  CONCEP in('01','02','04') and PTAANT in ('52','SI','SR','SP','SS')) as dEDUCCIONES,
	(select sum(importe) from btac2016 where llave=b.llave and  tconcep=1 and  CONCEP in('32','A1','A2','A3','A4','A5') and PTAANT in ('00','PD','PV','VD')) as PRIMA,
	(select sum(importe) from btac2016 where llave=b.llave and  tconcep=1 and  CONCEP in('68','69','75') and PTAANT in ('TR','AN','AP','EA')) as Estimulos,
	(select sum(importe) from btac2016 where llave=b.llave and  tconcep=1 and  CONCEP ='24' and PTAANT='GA') as PeriodicidadEstimulo,
	(select sum(importe) from btac2016 where llave=b.llave and  tconcep=1 and  CONCEP in('37','45','57') and PTAANT in ('TP','AL','LM') ) as ApoyoEconomico,
	(select sum(importe) from btac2016 where llave=b.llave and  tconcep=1 and  CONCEP in('59','73') and PTAANT in ('DT','DR','DM') ) as PrestacionesEconomicas
	from bdac2016 b
	where b.partida ='11301' and b.INDMANDO not in ('90','80') and b.tipnom IN ('11','6L')  
	and b.QNAPROC='$Trim' and b.tipotrab!='20') ssa
	where ur=ur
	group by rfc, serpub,cr,ur,puesto,denopuesto,denocargo,nombre,nivelpuesto,qnaproc,indmando,tipotrab,areaads
	";

	$GestorArchivo = fopen("bdac2016.txt", "w");
	if (!$GestorArchivo) {
		echo "Error al abrir archivo Error >>".$Path.$Archivo.".err" ."<<";
	}
	else{
		$res = $db->execFetchAll($sql, "pro_nomina");
		$Contador =8;
		$MSG=	"";
		//$MSG=	"NO APLICA DE ACUERDO AL MANUAL DE PERCEPCIONES";
		foreach ($res as $row) {
		//	echo "id uNIDAD >". $row['UNIDADES_ID'] ."<< <BR>";

			//print_r ($row);
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
			$PER=$row['SUELDO'] *2;
			$NETO=($row['SUELDO'] * 2) - ($row['DEDUCCIONES'] * 2);
			$Prima=$row['PRIMA'];
			$TIPOTRAB=$row['TIPOTRAB'];
			$Gratificaciones=$row['DEDUCCIONES'];
			$Estimulos=$row['ESTIMULOS'];	
			//$PeriodicidadEstimulo=$row['PERIODICIDADESTIMULO'];	
			$ApoyoEconomico=$row['APOYOECONOMICO'];	
			$QNAPROC = $row['QNAPROC'];	
			$PrestacionesEconomicas = $row['PRESTACIONESECONOMICAS'];	
			$RFC =$row['RFC'];
			$ApoEcoPer="";
			$PrimaPer="";
			$EstimuloPer="";
			$ApoyoEconomicoPer ="";
			$PrestacionesEconomicasPer="";
			if ($NombreEmpleado!="XXXXXXX"){

				if($PrestacionesEconomicas > 0){
				 $sqlIN = "select bt.importe, pr.CONCEPTO, pr.PARTIDA_ANTECEDENTE,  pr.DENOMINACION
							from bdac2016 bd, btac2016 bt, partida_remu pr
							where bd.rfc=:rfcv and BD.partida ='11301' AND
				            bD.INDMANDO not in ('90','80') and bD.tipnom IN ('11','6L')  
				            and bD.QNAPROC='$Trim' and bD.tipotrab!='20' AND 
				            bd.llave=bt.llave and          
				            bt.tconcep=1 and  
							bt.CONCEP=pr.CONCEPTO and bt.ptaant = pr.PARTIDA_ANTECEDENTE and 
							bt.CONCEP in('59','73') and bt.PTAANT in ('DT','DR','DM')";
		        	$res = $db->execFetchAll($sqlIN, "Query Example", array(array(":rfcv", $RFC, -1)));
		       
			        foreach ($res as $rowIN) {
			        //	echo "id Puestos >". $row['PUESTOS_ID'] ."| <BR>";
			        	$PrestacionesEconomicasPer =$PrestacionesEconomicasPer." " .$rowIN['DENOMINACION']."\n";
			        }	
		     	}
		     	else {
		     	   	$PrestacionesEconomicas= $MSG;
		     	   	$PrestacionesEconomicasPer = $MSG;
		     	   }   


				if($Prima > 0){
				 $sqlIN = "select bt.importe, pr.CONCEPTO, pr.PARTIDA_ANTECEDENTE,  pr.DENOMINACION
							from bdac2016 bd, btac2016 bt, partida_remu pr
							where bd.rfc=:rfcv and BD.partida ='11301' AND
				            bD.INDMANDO not in ('90','80') and bD.tipnom IN ('11','6L')  
				            and bD.QNAPROC='$Trim' and bD.tipotrab!='20' AND 
				            bd.llave=bt.llave and          
				            bt.tconcep=1 and  
							bt.CONCEP=pr.CONCEPTO and bt.ptaant = pr.PARTIDA_ANTECEDENTE and 
							bt.CONCEP in('32','A1','A2','A3','A4','A5') and bt.PTAANT in ('00','PD','PV','VD')
					";
		        	$res = $db->execFetchAll($sqlIN, "Query Example", array(array(":rfcv", $RFC, -1)));
		       
			        foreach ($res as $rowIN) {
			        //	echo "id Puestos >". $row['PUESTOS_ID'] ."| <BR>";
			        	$PrimaPer =$PrimaPer." " .$rowIN['DENOMINACION']."\n";
			        }	
		     	} 
		     	else{
		     	  	$Prima=$MSG;
		     	  	$PrimaPer=$MSG;
		     	  }  
		     	  
				if($Estimulos > 0){
				 $sqlIN = "select bt.importe, pr.CONCEPTO, pr.PARTIDA_ANTECEDENTE,  pr.DENOMINACION
							from bdac2016 bd, btac2016 bt, partida_remu pr
							where bd.rfc=:rfcv and BD.partida ='11301' AND
				            bD.INDMANDO not in ('90','80') and bD.tipnom IN ('11','6L')  
				            and bD.QNAPROC='$Trim' and bD.tipotrab!='20' AND 
				            bd.llave=bt.llave and          
				            bt.tconcep=1 and  
							bt.CONCEP=pr.CONCEPTO and bt.ptaant = pr.PARTIDA_ANTECEDENTE and 
							bt.CONCEP in('68','69','75') and bt.PTAANT in ('TR','AN','AP','EA')
					";
		        	$res = $db->execFetchAll($sqlIN, "Query Example", array(array(":rfcv", $RFC, -1)));
		       
			        foreach ($res as $rowIN) {
			        //	echo "id Puestos >". $row['PUESTOS_ID'] ."| <BR>";
			        	$EstimuloPer =$EstimuloPer." " .$rowIN['DENOMINACION']."\n";
			        }	
		     	} 
		     	else{
		     	  	$Estimulos=$MSG;
		     	  	$EstimuloPer=$MSG;
		     	  }  

				if($ApoyoEconomico > 0){
				 $sqlIN = "select bt.importe, pr.CONCEPTO, pr.PARTIDA_ANTECEDENTE,  
				 			case when bt.PTAANT = 'TP' then 
				 			 			pr.DENOMINACION ||' (Unica Vez)'
				 			when bt.PTAANT in ('AL','LM') then 
				 			 			pr.DENOMINACION ||' (Anual)' 			
				 			 end  as 	DENOMINACION2		
							from bdac2016 bd,btac2016 bt, partida_remu pr
							where bd.rfc=:rfcv and BD.partida ='11301' AND
				            bD.INDMANDO not in ('90','80') and bD.tipnom IN ('11','6L')  
				            and bD.QNAPROC='$Trim' and bD.tipotrab!='20' AND 
				            bd.llave=bt.llave and   
				            bt.tconcep=1 and  
							bt.CONCEP=pr.CONCEPTO and bt.ptaant = pr.PARTIDA_ANTECEDENTE and 
							bt.CONCEP in('37','45','57') and bt.PTAANT in ('TP','AL','LM')
							";
		        	$res = $db->execFetchAll($sqlIN, "Query Example", array(array(":rfcv", $RFC, -1)));
		       
			        foreach ($res as $rowIN) {
			        //	echo "id Puestos >". $row['PUESTOS_ID'] ."| <BR>";
			        	$ApoyoEconomicoPer =$ApoyoEconomicoPer." ".$rowIN['DENOMINACION2']."\n";
			        }	
		     	} 
		     	else{
		     	  	$ApoyoEconomico=$MSG;
		     	  	$ApoyoEconomicoPer=$MSG;
		     	  }  






			  $currencyFormat = '_($* #,##0.00_);_($* (#,##0.00);_($* "-"??_);_(@_)';
			  $objPHPExcel->getActiveSheet()->getStyle('J'.($Contador))->getNumberFormat()->setFormatCode($currencyFormat);	
			  
			  //$currencyFormat = '_($* #,##0.00_);_($* (#,##0.00);_($* "-"??_);_(@_)';
			  //$objPHPExcel->getActiveSheet()->getStyle('K'.($Contador))->getNumberFormat()->setFormatCode($currencyFormat);	

		      $objPHPExcel->setActiveSheetIndex(0)
	            ->setCellValue('A'.($Contador), $SerPub)
	            ->setCellValueExplicit('B'.$Contador, $CveNiv,PHPExcel_Cell_DataType::TYPE_STRING)
	            ->setCellValue('C'.$Contador, $Puesto)
	            ->setCellValueExplicit('D'.$Contador, $Denocargo,PHPExcel_Cell_DataType::TYPE_STRING)
	            ->setCellValueExplicit('E'.$Contador, $AreaAds,PHPExcel_Cell_DataType::TYPE_STRING)
	            ->setCellValue('F'.$Contador, $NombreEmpleado)
	            ->setCellValue('G'.$Contador, $ApePaterno)
	            ->setCellValue('H'.$Contador, $ApeMaterno)
	            ->setCellValue('J'.($Contador), $PER)
	            ->setCellValue('k'.($Contador), $NETO)
	            ->setCellValue('L'.$Contador, $Contador-SIETE)
	            ->setCellValueExplicit('M'.$Contador, $MSG,PHPExcel_Cell_DataType::TYPE_STRING)
	            ->setCellValueExplicit('N'.$Contador, $MSG,PHPExcel_Cell_DataType::TYPE_STRING)
				->setCellValue('O'.$Contador, $Contador-SIETE)
	            ->setCellValue('P'.$Contador, $Contador-SIETE)
	            ->setCellValue('Q'.$Contador, $MSG)
				->setCellValue('R'.$Contador, $MSG)
				->setCellValue('S'.$Contador, $Contador-SIETE)
				->setCellValue('T'.$Contador, $PrimaPer)
	            ->setCellValue('U'.$Contador, $MSG)
	            ->setCellValue('V'.$Contador, $MSG)
				->setCellValue('W'.$Contador, $MSG)
	            ->setCellValue('X'.$Contador, $MSG)
				->setCellValue('Y'.$Contador, $MSG)
	            
	            ->setCellValue('Z'.$Contador, $Estimulos)
	            ->setCellValue('AA'.$Contador, $EstimuloPer)
	            ->setCellValue('AB'.$Contador, $ApoyoEconomico)
	            ->setCellValue('AC'.$Contador, $ApoyoEconomicoPer)
	            ->setCellValue('AD'.$Contador, $PrestacionesEconomicas)
	            ->setCellValue('AE'.$Contador, $PrestacionesEconomicas)          
	            ->setCellValue('AF'.$Contador, $MSG)          
	            ->setCellValue('AG'.$Contador, $MSG)
			->setCellValue('AH'.$Contador, '2016-06-30')
			->setCellValue('AI'.$Contador, 'DIRECCIÓN GENERAL DE RECURSOS HUMANO')
			->setCellValue('AJ'.$Contador, '2016')                        
			->setCellValue('AK'.$Contador, '2016-06-30')                        
			->setCellValue('AL'.$Contador, 'Se tienen campos pendientes de integrar información');

		$objPHPExcel->getActiveSheet()->getStyle('AH'.$Contador)->getNumberFormat()->setFormatCode(PHPExcel_Style_NumberFormat::FORMAT_DATE_YYYYMMDDSLASH);
		$objPHPExcel->getActiveSheet()->getStyle('AK'.$Contador)->getNumberFormat()->setFormatCode(PHPExcel_Style_NumberFormat::FORMAT_DATE_YYYYMMDDSLASH);

	//->setCellValue('AE'.$Contador, $PrestacionesEconomicasPer)    

	// Tabla 10180
	            
	         $objPHPExcel->setActiveSheetIndex(TRES)   
	          ->setCellValue('A'.($Contador-4), $Contador-SIETE)
	          ->setCellValue('B'.($Contador-4), CERO)
	          ->setCellValue('C'.($Contador-4), 'Mensual')
	          ->setCellValue('D'.($Contador-4), 'Pesos');
	// Tabla 10150

	         $objPHPExcel->setActiveSheetIndex(CUATRO)   
	          ->setCellValue('A'.($Contador-4), $Contador-SIETE)
	          ->setCellValue('B'.($Contador-4), 'Pesos')
	          ->setCellValue('C'.($Contador-4), 'Mensual')
	          ->setCellValue('D'.($Contador-4), CERO);
	//Tabla 10160


	         $objPHPExcel->setActiveSheetIndex(CINCO)   
	          ->setCellValue('A'.($Contador-4), $Contador-SIETE)
	          ->setCellValue('B'.($Contador-4), 'Pago')
	          ->setCellValue('C'.($Contador-4), 'Mensual')
	          ->setCellValue('D'.($Contador-4), 'Pesos');

	// Tabla 10181


	         $objPHPExcel->setActiveSheetIndex(SEIS)   
	          ->setCellValue('A'.($Contador-4), $Contador-SIETE)
	          ->setCellValue('B'.($Contador-4), 'Pesos')
	          ->setCellValue('C'.($Contador-4), $Prima)
	          ->setCellValue('D'.($Contador-4), 'Mensual');



	$Contador++;
			}		

	/**
			if ($Contador > 100)
					break;
					**/
			
			
		//	fwrite($GestorArchivo, $Str);
		}	// fin del for reach

	$objPHPExcel->setActiveSheetIndex(0);
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
	$objPHPExcel->getActiveSheet()
	                ->getColumnDimension('T')
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
	//$objWriter->save(str_replace('.php', '.xlsx', __FILE__));
	$objWriter->save($Trim."_Remuneraciones.xlsx");

	//	fclose($GestorArchivo);
	}
}// foreach
?>		        