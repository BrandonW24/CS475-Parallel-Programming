#!/bin/csh

#number of threads:
foreach t ( 1 2 4 6 8 )
	echo NUMT =$t
	g++ -DNUMT=$t prog0.cpp -o prog0 -lm -fopenmp
	./prog0
end
