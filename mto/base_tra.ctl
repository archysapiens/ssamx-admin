OPTIONS (ERRORS=1)
LOAD DATA 
INFILE '../staging/#ARCHIVO_DATA#' 
APPEND
INTO TABLE "PRO_NOMINA"."BDAT"
FIELDS TERMINATED BY'|'
OPTIONALLY ENCLOSED BY '"' AND '"'
TRAILING NULLCOLS ( 
"RFC" CHAR (13),
"NUMEMP" CHAR (10),
"NUMCHEQ" CHAR (9),
"TCONCEP" CHAR(3),
"CONCEP" CHAR(2),
"IMPORTE" ,
"ANIO" CHAR(4),
"QNA"  CHAR(2),
"PTAANT" CHAR(2) ,
"TOTPAGOS" CHAR(4) ,
"PAGOEFEC" CHAR(4) ,
"NOMPROD" CHAR(11) ,
"NUMCTROL" ,
"NOMARCH" constant '#ARCHIVO_DATA#'
)

