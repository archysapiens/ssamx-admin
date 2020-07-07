
STR_CNNX=pro_nomina/pro_nomina@pn
PATH_MIDD_ORACLE="../staging/oracle"

for archivo in `find $PATH_MIDD_ORACLE|grep "ora$"`
do
	echo $archivo
	echo "@$archivo"|sqlplus -s  $STR_CNNX|grep -v "^$" |grep -v "^-" > $archivo".res"
	mv $archivo $archivo".fin"
	echo $archivo > $archivo".bnd"

done

