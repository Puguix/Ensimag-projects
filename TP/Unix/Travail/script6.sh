#!/bin/bash

if test -d $1
then 
`mkdir all`
for d in $@
do
for file in `ls $d`
do
`mv $d/$file ./all/$d$file`
done
done
`rmdir $@`
else echo "Ton répertoire est pas bon"
fi 