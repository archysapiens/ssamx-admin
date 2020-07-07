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


$objPHPExcel->getProperties()->setCreator("Secretaria de Salud")
               ->setLastModifiedBy("Dirección de Automatización de Procesos y Soporte Técnico")
               ->setTitle("Sistema Nacional de Transparencia")
               ->setSubject("Sistema Integrador / Vacantes")
               ->setDescription("Plazas Vacantes del Personal de base y Confianza ")
               ->setKeywords("Dirección General de Recursos Humanos")
               ->setCategory("Archivo de Carga Masiva");
// Add some data
//echo date('H:i:s') , " Add some data" , EOL;
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
            ->setCellValue('T7', 'Periodicidad')  
			->setCellValue('U7', 'Comisiones')  
			->setCellValue('V7', 'Periodicidad')

            ->setCellValue('W7', 'Dietas.')
            ->setCellValue('X7', 'Periodicidad')
            ->setCellValue('Y7', 'Bonos.')
            ->setCellValue('Z7', 'Periodicidad')  
			->setCellValue('AA7', 'Estímulos.')  
			->setCellValue('AB7', 'Periodicidad')

            ->setCellValue('AC7', 'Apoyos económicos.')
            ->setCellValue('AD7', 'Periodicidad.')
            ->setCellValue('AE7', 'Prestaciones económicas')
            ->setCellValue('AF7', 'Prestaciones en especie.')  
			->setCellValue('AG7', 'Periodicidad')  
			->setCellValue('AH7', 'Otro tipo de percepción.')
            ->setCellValue('AI7', 'Fecha de validación')
            ->setCellValue('AJ7', 'Área responsable de la información')  
			->setCellValue('AK7', 'Año')  
			->setCellValue('AL7', 'Nota')
			->setCellValue('AM7', 'Fecha de actualización')  ;



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
and b.QNAPROC='12' and b.tipotrab!='20') ssa
group by rfc, serpub,cr,ur,puesto,denopuesto,denocargo,nombre,nivelpuesto,qnaproc,indmando,tipotrab,areaads
";

$GestorArchivo = fopen("bdac2016.txt", "w");
if (!$GestorArchivo) {
	echo "Error al abrir archivo Error >>".$Path.$Archivo.".err" ."<<";
}
else{
	$res = $db->execFetchAll($sql, "pro_nomina");
	$Contador =8;
	$MSG=	"NO APLICA DE ACUERDO AL MANUAL DE PERCEPCIONES";
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
			            and bD.QNAPROC='12' and bD.tipotrab!='20' AND 
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
			            and bD.QNAPROC='12' and bD.tipotrab!='20' AND 
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
			            and bD.QNAPROC='12' and bD.tipotrab!='20' AND 
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
			            and bD.QNAPROC='12' and bD.tipotrab!='20' AND 
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
            ->setCellValue('L'.$Contador, "NO APLICA DE ACUERDO AL MANUAL DE PERCEPCIONES")
            ->setCellValueExplicit('M'.$Contador, $MSG,PHPExcel_Cell_DataType::TYPE_STRING)
            ->setCellValueExplicit('N'.$Contador, $MSG,PHPExcel_Cell_DataType::TYPE_STRING)
			->setCellValue('O'.$Contador, $MSG)
            ->setCellValue('P'.$Contador, $MSG)
            ->setCellValue('Q'.$Contador, $MSG)
			->setCellValue('R'.$Contador, $MSG)
			->setCellValue('S'.$Contador, $Prima)
			->setCellValue('T'.$Contador, $PrimaPer)
            ->setCellValue('U'.$Contador, $MSG)
            ->setCellValue('V'.$Contador, $MSG)
			->setCellValue('W'.$Contador, $MSG)
            ->setCellValue('X'.$Contador, $MSG)
			->setCellValue('Y'.$Contador, $MSG)
            
            ->setCellValue('Z'.$Contador, $MSG)
            ->setCellValue('AA'.$Contador, $Estimulos)
            ->setCellValue('AB'.$Contador, $EstimuloPer)
            ->setCellValue('AC'.$Contador, $ApoyoEconomico)
            ->setCellValue('AD'.$Contador, $ApoyoEconomicoPer)
            ->setCellValue('AE'.$Contador, $PrestacionesEconomicas)          
            ->setCellValue('AF'.$Contador, $MSG)          
            ->setCellValue('AG'.$Contador, $MSG);

//->setCellValue('AE'.$Contador, $PrestacionesEconomicasPer)    

		}		

/**
		if ($Contador > 100)
				break;
				**/
		$Contador++;
		
	//	fwrite($GestorArchivo, $Str);
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
//$objWriter->save(str_replace('.php', '.xlsx', __FILE__));
$objWriter->save("Remuneraciones.xlsx");

//	fclose($GestorArchivo);
}

?>		        