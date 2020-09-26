#!/bin/bash

#number of trials AND number of threads :

for numThread in 1 2 4 6 8 16
	do
	printf "______________________________________\n"
	printf "Changing number of threads to : \n"
	echo NUMT=$numThread
	printf "______________________________________\n"
	for numTr in 0 1000000 2000000 3000000 4000000 5000000 6000000
	do
	printf "\n"
	printf " ***Changing the number of trials to *** : \n"
	echo NUMTRIALS=$numTr
	printf " =***************************************************=  \n"
	g++ -DNUMT=$numThread -DNUMTRIALS=$numTr ConsoleApplication2.cpp -o prog01both -lm -fopenmp
	printf "\n"
	./prog01both
	done
	printf "_______________________________________\n"
done
