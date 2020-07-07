OPTIONS (ERRORS=1)
LOAD DATA 
INFILE '../staging/prdo.dat' 
APPEND
CONTINUEIF NEXT(1:1) = '#'
INTO TABLE "PRO_NOMINA"."BDAC"
FIELDS TERMINATED BY'|'
OPTIONALLY ENCLOSED BY '"' AND '"'
TRAILING NULLCOLS ( 
"NUEMP" CHAR (10),
"RFC" CHAR (13),
"CURP" CHAR (18),
"NOMBRE" CHAR (55),
"SAR" CHAR (20),
"BANCOA" CHAR (2),
"BANCON" CHAR (5),
"NUMCTA" CHAR (16),
"CLABE" CHAR (20),
"CVESPC" CHAR (50),
"CP" CHAR (5),
"CALLE" CHAR (254),
"COLONIA" CHAR (254),
"DELEG" CHAR (254),
"UR" CHAR (3),
"GF" CHAR (1),
"FN" CHAR (1),
"SF" CHAR (2),
"PG" CHAR (2),
"AL" CHAR (3),
"PP" CHAR (4),
"PARTIDA" CHAR (5),
"PUESTO" CHAR (7),
"NUMPTO" CHAR (4),
"EDO" CHAR (2),
"MPIO" CHAR (3),
"CR" CHAR (10),
"CI" CHAR (15),
"PAGADURI" CHAR (5),
"AHISA" CHAR (12),
"TABPTO" CHAR (3),
"NIVEL" CHAR (2),
"RANGO" CHAR (1),
"INDMANDO" CHAR (2),
"HORAS" CHAR (1),
"PORCENT" CHAR (8),
"TIPOTRAB" CHAR (2),
"NIVELPTO" CHAR (10),
"INDEMP" CHAR (1),
"FIGF" CHAR (8),
"FSSA" CHAR (8),
"FREING" CHAR (8),
"TIPOMOV" CHAR (4),
"FPAGO" CHAR (10),
"PPAGOI" CHAR (8),
"PPAGOF" CHAR (8),
"PQNAI" CHAR (8),
"PQNAF" CHAR (8),
"QNAREAL" CHAR (2),
"ANIOREAL" CHAR (4),
"TIPOPAGO" ,
"INSTRUA" CHAR (2),
"INSTRUN" CHAR (2),
"PER" ,
"DED" ,
"NETO" ,
"NOTRIAL" ,
"DIASLAB" ,
"NOMPROD" CHAR (11),
"NUMCTROL" ,
"NUMCHEQ" CHAR (9),
"DIGVER" CHAR (1),
"TESOFE" ,
"DIASPD" CHAR (2),
"CICLOF" CHAR (5),
"NUMAPORT" CHAR (2),
"ACUMF" ,
"FALTAS" ,
"LSGS" "DECODE(TRANSLATE(':LSGS','0123456789',' '),NULL,':LSGS',0)" ,
"PORPEN01" "TO_NUMBER(:PORPEN01)",
"PORPEN02" ,
"PORPEN03" ,
"PORPEN04" ,
"PORPEN05" ,
"ISSSTE" ,
"TIPOUNI" ,
"CRESPDES" CHAR (100),
"VERSION" "'prdo.dat'||:VERSION",
"ESTADO" constant '02',
"TIPNOM"  constant '6W',
"QNAPROC" constant '18',
"ANIOPROC" constant '2016',
"QNAENVIO" constant '18',
"ANIOENV" constant '2016',
"NOMARCH" constant '02',
"TIPOPER" constant '02',
"LLAVE" "'prdo.dat'||' '|| :RFC ||' '||:CURP"
)

