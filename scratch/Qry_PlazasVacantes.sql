/***
Este es un nuevo query para obtener los datos 
de las vacantes Xa

**/
select cu.descripcion as "Denominación de Area", cap.DESCRIPCION as "Denominacion de Puesto",
pv.NIV_TAB as "Clave o Nivel de Puesto",
cp.DESCRIPCION, cap.DESCRIPCION, 
nvl(
(SELECT DEN_PTO FROM RUSP where trim(RUSP.CONSECUT) = trim(pv.CONS_PTOIN) and qna=11 and trim(ur)=trim(cu.NOMBRE_UNIDAD)),
nvl((select b.DESCRIPCION from ctareasuperior a, ctareasuperior b
                        where b.ur=a.AR_INMSUP AND a.UR= cu.NOMBRE_UNIDAD), 
                        (select a.DESCRIPCION
                         from ctareasuperior a
                          where a.UR= cu.NOMBRE_UNIDAD))) as "Area de Adscripción",
cet.descripcion as "Estado",pv.CONVOCATORIA
from plazasvacantes_xa pv, ctareas ca, ctunidades cu, 
ctestadotrabajador cet, ctpuestos cp , 
CTCARGOPUESTO cap 
where pv.areas_id=ca.areas_id and 
pv.unidades_id=cu.unidades_id and
pv.ESTADOTRABAJDOR_ID=cet.estadotrabajador_id and
pv.PUESTOS_ID=cp.PUESTOS_ID and
pv.CARGOPUESTO_ID=cap.CARGOPUESTO_ID;






select ca.nombre, cu.nombre_unidad, cet.descripcion, cp.CODIGO,cp.DESCRIPCION, cap.DESCRIPCION
from plazasvacantes_xa pv, ctareas ca, ctunidades cu, ctestadotrabajador cet, ctpuestos cp , CTCARGOPUESTO cap
where pv.areas_id=ca.areas_id and 
pv.unidades_id=cu.unidades_id and
pv.ESTADOTRABAJDOR_ID=cet.estadotrabajador_id and
pv.PUESTOS_ID=cp.PUESTOS_ID and
pv.CARGOPUESTO_ID=cap.CARGOPUESTO_ID;

--
-- Con esta consulta obtenemos todos los datos que
-- Necesita el formato a entregar a SNT
--
select cu.descripcion as "Denominación de Area", cap.DESCRIPCION as "Denominacion de Puesto",
pv.NIV_TAB as "Clave o Nivel de Puesto",
cp.DESCRIPCION, cap.DESCRIPCION, 
nvl((select b.DESCRIPCION from ctareasuperior a, ctareasuperior b
                        where b.ur=a.AR_INMSUP AND a.UR= cu.NOMBRE_UNIDAD), 
                        (select a.DESCRIPCION
                         from ctareasuperior a
                          where a.UR= cu.NOMBRE_UNIDAD)) as "Area de Adscripción",
cet.descripcion as "Estado",pv.CONVOCATORIA
from plazasvacantes_xa pv, ctareas ca, ctunidades cu, 
ctestadotrabajador cet, ctpuestos cp , 
CTCARGOPUESTO cap 
where pv.areas_id=ca.areas_id and 
pv.unidades_id=cu.unidades_id and
pv.ESTADOTRABAJDOR_ID=cet.estadotrabajador_id and
pv.PUESTOS_ID=cp.PUESTOS_ID and
pv.CARGOPUESTO_ID=cap.CARGOPUESTO_ID;



