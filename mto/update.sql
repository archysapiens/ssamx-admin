update bdat
set llave= (select distinct bd.llave 
            from bdac bd 
            where bd.rfc=bdat.rfc and 
            bd.nuemp=bdat.numemp and 
            bd.nomprod=bdat.nomprod and
            bd.numcheq=bdat.numcheq and
            bd.numctrol=bdat.numctrol
            )
where llave is null;
commit;
