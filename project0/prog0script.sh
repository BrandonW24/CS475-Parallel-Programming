#!/bin/bash

#number of threads:
for t in  1 2 4 6 8
	do 
	echo NUMT=$t
	g++ -DNUMT=$t prog0.cpp -o prog0 -lm -fopenmp
	./prog0	
done
