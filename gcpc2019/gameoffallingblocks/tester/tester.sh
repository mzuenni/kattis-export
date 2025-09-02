#!/bin/bash

if [ $# -ne 1 ]
then
	echo "Usage: ./tester.sh <number-of-runs>"
	exit 0
fi

runs=$1
submissions=`find ../submissions -name "*.cpp"`

g++ -std=c++14 ../output_validators/validate/validate.cpp -o validate

for sub in $submissions; do
	g++ -std=c++14 $sub -o solution || (echo "Failed"; exit 1)
	echo -n $sub ""
	for use_bag in `seq 0 1`; do
		fails=0
		for i in `seq 1 $runs`; do
			# echo $i
			echo $i $use_bag > 1.in
			touch 1.ans
			socat EXEC:"./validate 1.in 1.ans ." EXEC:"./solution" >& /dev/null
			if [ "`tail -n1 judgemessage.txt`" != "Correct!" ]
			then
				#if [ $fails -le 10 ]
				#then
				#	echo $i
				#	cat judgemessage.txt
				#fi
				fails=$((fails + 1))
			fi
			# cat judgemessage.txt
			rm judgemessage.txt
		done
		echo -n $fails ""
	done
	echo
done | sort | column -t

rm validate solution 1.in 1.ans
