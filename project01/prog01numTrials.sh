#!/bin/bash

#number of trials :
for numTr in 1000000 2000000 3000000 4000000 5000000 6000000
	do
	printf "Changing number of trials to : \n"
	echo NUMTRIALS=$numTr
	g++ -DNUMTRIALS=$numTr ConsoleApplication2.cpp -o prog01numTr -lm -fopenmp
	printf "\n"
	./prog01numTr
	printf "_________________________\n"
done
