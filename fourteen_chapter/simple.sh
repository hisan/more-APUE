#!/bin/bash
c='c'
i=0
var=1
path="./a.txt"
for(( i = 0; i < 600000; i++ ))
 do
	echo $c >> $path
 done 
