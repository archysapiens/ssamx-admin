OPTIONS (SKIP=1) 
load data
 APPEND
  into table BD
  fields terminated by '|' optionally enclosed by '"'
  TRAILING NULLCOLS
  (
NUMEMP ,
RFC ,
CURP ,
NOMBRE ,
SAR ,
BANCOA ,
BANCON ,
NUMCTA  ,
CLABE  ,
CVESPC  , 
CP , 
CALLE , 
COLONIA  , 
DELEG   , 
UR   , 
GF   ,  
FN   ,  
SF   ,  
PG   ,  
AI  ,
PP   ,
PARTIDA   ,
PUESTO   ,
NUMPTO   ,
EDO   ,
MPIO  ,
CR    ,
CI    ,
PAGADURI   ,
AHISA   ,
TABPTO   ,
NIVEL   ,
RANGO    ,
INDMANDO  ,
HORAS   ,
PORCENT  ,
TIPOTRAB ,
NIVELPTO ,
INDEMP   ,
FIGF    ,
FSSA   ,
FREING ,
TIPOMOV ,
FPAGO   ,
PPAGOI  ,
PPAGOF  ,
PQNAI   ,
PQNAF   ,
QNAREAL ,
ANIOREAL ,
TIPOPAGO ,
INSTRUA  ,
INSTRUN  ,
PER   ,
DED   ,
NETO  ,
NOTRAIL ,
DIASLAB ,
NOMPROD ,
NUMCTROL,
NUMCHEQ ,
DIGVER  ,
TESOFE ,
DIASPD ,
CICLOF ,
NUMAPORT ,
ACUMF ,
FALTAS ,
LSGS  ,
PORPEN01 ,
PORPEN02 ,
PORPEN03 ,
PORPEN04 ,
PORPEN05 ,
ISSSTE ,
TIPOUNI ,
CRESPDES ,
VERSION ,
ESTADO ,
TIPNOM ,
QNAPROC ,
ANIOPROC ,
QNAENVIO ,
ANIOENV ,
NOMARCH ,
TIPOPER ,
LLAVE ,
fecha_proceso sysdate
  )