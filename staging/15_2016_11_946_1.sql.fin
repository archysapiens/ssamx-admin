set @fecha_evento='20160523181114';
set @id_remesas=946;
set @archivo_procesado='../staging/20160523181114BT161508.txt.err';
set @IdDir =1;
set @Estatus='E';
set @Evidencia='Evidencia';
load data local infile '../staging/20160523181114BT161508.txt.err'
INTO TABLE bitacora
FIELDS TERMINATED BY '|' ENCLOSED BY '"'
LINES TERMINATED BY '\n'
(registro,	error, campo, descripcion)
set fecha_evento=STR_TO_DATE(@fecha_evento,'%Y%m%d%H%i%s'), id_remesas=@id_remesas,
archivo_procesado=@archivo_procesado,
evidencia=@Evidencia, id_directiva=@IdDir,estatus=@Estatus;
