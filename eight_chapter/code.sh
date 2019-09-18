#!/bin/bash
#统计某个目录下的所有代码文件中的代码行
Dir="/home/zhangyb/"
list=$(ls -R $Dir)
for curdir in $list
do 
        if [ -f "$curdir" ]
	then
		if [[ "$curdir" == *.c ]]
		then echo "num:" $(wc -l $curdir) >> line.txt
		elif [[ "$curdir" == *.h ]]
		then echo "num:" $(wc -l $curdir) >> line.txt
		fi
        fi
done
