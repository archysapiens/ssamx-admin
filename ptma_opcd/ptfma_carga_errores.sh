User=root
Pwd=Secnomina#2016
Host=localhost
DB=ssa
while true
do
sleep 10
	contador=0
	for arch in `find ../staging/|grep ".sql$"`
	do
		echo "arch >>"$arch"<<"
		mysql --show-warnings --host=$Host -u $User -p$Pwd $DB <$arch
		mv $arch $arch".fin"
		contador=`expr $contador + 1`
	done
	echo "archivos procesados >"$contador
done

