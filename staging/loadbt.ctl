OPTIONS (SKIP=1) 
load data
 APPEND
into table BT
fields terminated by '|' optionally enclosed by '"'
TRAILING NULLCOLS
(
RFC ,
NUMEMP ,
NUMCHEQ, 
TCONCEP, 
CONCEP , 
IMPORTE , 
ANIO , 
QNA , 
PTAANT , 
TOTPAGOS , 
PAGOEFEC , 
NOMPROD , 
NUMCTROL , 
NOMARCH , 
LLAVE ,
FECHA_PROCESO sysdate
)