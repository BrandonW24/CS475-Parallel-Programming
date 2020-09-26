#!/bin/bash

#number of threads :
for t in 1 2 4 6 8 16
	do
	printf "________________________________________\n"
	echo Changing number of threads to NUMT=$t
	g++ -DNUMT=$t ConsoleApplication2.cpp -o prog01 -lm -fopenmp
	printf "\n"
	./prog01
	printf "_________________________________________\n"
done
