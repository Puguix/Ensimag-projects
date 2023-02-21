#!/bin/bash

for file in `ls $1`
do
echo `stat -c%y $1/$file` >$1/$file
done