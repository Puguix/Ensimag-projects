#!/bin/bash

if test $1 -eq $2
then echo "Le nombre" $1 "est égal au nombre" $2
elif test $1 -le $2
then echo "Le nombre" $1 "est inférieur au nombre" $2
else echo "Le nombre" $1 "est supérieur au nombre" $2
fi