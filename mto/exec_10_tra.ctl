OPTIONS (ERRORS=1)
LOAD DATA 
INFILE '../staging/prde040.tra' 
APPEND
CONTINUEIF NEXT(1:1) = '#'
INTO TABLE "PRO_NOMINA"."BDAC"
FIELDS TERMINATED BY'|'
OPTIONALLY ENCLOSED BY '"' AND '"'
TRAILING NULLCOLS ( 
"RFC" CHAR (13),
"NUEMP" CHAR (10),
"NUMCHEQ" CHAR (9),
"TCONCEP" VARCHAR2(3),
"CONCEP" VARCHAR2(2),
"IMPORTE" NUMBER(12,2),
"ANIO" VARCHAR2(4),
"QNA"  VARCHAR2(2),
"PTAANT" VARCHAR2(2) ,
"TOTPAGOS" VARCHAR2(4) ,
"PAGOEFEC" VARCHAR2(4) ,
"NOMPROD" VARCHAR2(11) ,
"NUMCTROL" ,
"NOMARCH" constant 'prde040.tra',
"LLAVE" " :RFC ||' '||:NUEMP"
)

