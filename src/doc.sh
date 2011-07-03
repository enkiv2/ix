#!/bin/sh
for i in */*.c */*.asm */*.h
do
	echo "$i:"
	cat $i | grep '//@'  | sed -e 's/\/\/\@/\n\t/g;s/\:/\t/g;s/[\;\{][\t\ ]*\t/\t/g'
	echo

done

