######################################################################## 
#
#  Nombre	:ptfma_demon_pn.sh
#  fecha	:03-Ago-2016
#  Objetivo	: Realizar la Carga de la Remesa a Tabla Staging
# 
######################################################################## 

#echo "select id from remesas where estatus='T';"|mysql -u root -pSecnomina#2016 ssa
BASE_DATA_CTL=base_data.ctl
BASE_TRA_CTL=base_tra.ctl
STR_CNNX="-u root -pSecnomina#2016 ssa"
STR_CNN_ORA=pro_nomina/pro_nomina@pn


####################################################
#                                                  #
#      SECCION DE QUERYS                           #
#                                                  #
####################################################

SQL="select id,anio_periodos,numero_periodos,tag_envio from remesas where estatus='T' order by id;"
SQL_UPDATE_REMESA="update remesas set estatus='K'  where id="

SQL_LOG_HDR="SELECT tipo_archivo,archivo,estatus,id_tipo_nom,fecha_agregacion, etiqueta_envio" 
SQL_LOG_FROM=" FROM logger "
SQL_LOG_WHERE=" where id_remesas="

while true
do
sleep 10
echo ""
echo ""
echo ""
echo ""
echo "##############################################################"
echo "#                                                            #"
echo "# 	Fecha Ini Proceso `date`                           #"
echo "#                                                            #"
echo "##############################################################"



for row_rem in `echo "$SQL"|mysql -sN $STR_CNNX|sed 's/\t/|/g'|grep -v id`
do
	echo "remesa" $row_rem
	REMESA=`echo $row_rem|awk -F"|" '{print $1}'`
	ANIO=`echo $row_rem|awk -F"|" '{print $2}'`
	QNA=`echo $row_rem|awk -F"|" '{print $3}'`
	TAG=`echo $row_rem|awk -F"|" '{print $4}'`
	ANIO_ENVIO=`echo $TAG|awk -F"-" '{print $1}'`
	QNA_ENVIO=`echo $TAG|awk -F"-" '{print $2}'`

	echo "REMESA >"$REMESA"< ANIO>"$ANIO"< QNA >"$QNA"< TAG >"$TAG"< ANIO ENVIO >"$ANIO_ENVIO"< QNA ENVIO >"$QNA_ENVIO"<"
	SQL_DET="select etiqueta_envio from logger where id_remesas=$REMESA order by etiqueta_envio desc limit 1"
	#echo $SQL_DET|mysql $STR_CNNX
	RES=`echo $SQL_DET|mysql $STR_CNNX|grep -v etiqueta_envio`
	if [[ $RES != "" ]] 
	then
		echo " si hay datos>"$RES"<"
		
		SQL_LOG_WHERE_CMTO=$SQL_LOG_WHERE"$REMESA  and etiqueta_envio='"$RES"'"

		SQL_MAIN="$SQL_LOG_HDR $SQL_LOG_FROM $SQL_LOG_WHERE_CMTO"
		echo "SQL_MAIN LOGGER>$SQL_MAIN<"
		contador=1


		for rem_det in `echo $SQL_MAIN|mysql -sN $STR_CNNX|sed 's/\t/|/g'|sed 's/ //g'`
		do
			echo "DETALLE >"$rem_det"<"
			TIPO=`echo $rem_det|awk -F"|" '{print $1}'`
			PATT=`echo $rem_det|awk -F"|" '{print $2}'`
			STAT=`echo $rem_det|awk -F"|" '{print $3}'`
			PN=`echo $rem_det|awk -F"|" '{print $4}'`
			TAG_PROCESO=`echo $rem_det|awk -F"|" '{print $6}'`

			QNA_PROC=`echo $TAG_PROCESO|awk -F"-" '{print $3}'`
			ANIO_PROC=`echo $TAG_PROCESO|awk -F"-" '{print $2}'`

			echo "TIPO >$TIPO< PATT >$PATT< STAT >$STAT< PN >$PN<"

			NOM_ARCHIVO="`echo $PATT|awk -F"/" '{print $3}'`"
			CONSECUTIVO=`echo $contador|awk '{ printf "%03d",$0}'`
			echo "CONSECUTIVO>"$CONSECUTIVO"<"

			if [[ $TIPO == "D" ]] 
			then
				#Se crea archivo CTL para archivos de DATOS

				cat $BASE_DATA_CTL|awk -v archivo="$NOM_ARCHIVO" -v aenv="$ANIO_ENVIO" -v qenv="$QNA_ENVIO" -v pn="$PN" -v qproc="$QNA_PROC" -v aproc="$ANIO_PROC" -v consecutivo=$CONSECUTIVO '{
				
				gsub(/\#ARCHIVO_DATA\#/,archivo,$0)
				gsub(/\#QNA_ENVIO\#/,qenv,$0)
				gsub(/\#ANIO_ENVIO\#/,aenv,$0)
				gsub(/\#PN\#/,pn,$0)
				gsub(/\#QNA_PROC\#/,qproc,$0)
				gsub(/\#ANIO_PROC\#/,aproc,$0)
				gsub(/\#CONSECUTIVO\#/,consecutivo,$0)
				print $0
					}' >exec_"$contador".ctl

				#Se carga con sqlldr
				sqlldr $STR_CNN_ORA control=exec_"$contador".ctl 
			else
				#Se crea archivo CTL
				#Se carga con sqlldr
				echo "SECCION TRAIL  NOM_ARCHIVO>"$NOM_ARCHIVO"<"
				cat $BASE_TRA_CTL|awk -v archivo="$NOM_ARCHIVO" -v pn="$PN" -v qproc="$QNA_PROC" -v aproc="$ANIO_PROC" '{
				
				gsub(/\#ARCHIVO_DATA\#/,archivo,$0)
				print $0
					}' >exec_"$contador"_tra.ctl

				#Se carga con sqlldr
				sqlldr $STR_CNN_ORA control=exec_"$contador"_tra.ctl 
				echo "@update.sql"|sqlplus $STR_CNN_ORA 
					
				
			fi
			if [ -f $PATT ] 
			then
				echo "SI Existe Archivo " $PATT
			else
				echo "NO Existe Archivo " $PATT
			fi
			contador=`expr $contador + 1`
		done
		echo "$SQL_UPDATE_REMESA"$REMESA|mysql -sN $STR_CNNX
	else
		echo " NO hay REMESAS LIBERADAS"	
	fi
done
done
