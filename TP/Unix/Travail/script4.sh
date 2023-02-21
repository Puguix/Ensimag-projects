#!/bin/bash

if test -d $1
then 
for file in `ls $1`
do
echo $file
test -d
done   
else echo "Ton répertoire est pas bon"
fi 