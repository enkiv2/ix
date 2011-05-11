#!/bin/sh
for i in *.c *.asm ../include/*.h
do
	echo "$i:"
	cat $i | grep '//@'  | sed -e 's/\/\/\@/\n\t/g' | sed -e 's/\:/\t/g'
	echo

done

