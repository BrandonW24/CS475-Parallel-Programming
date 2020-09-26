#!/bin/bash
#number of nodes :
for numNode in 100 250 500 1000 2500 5000 10000
	do
	printf "Changing number of NODEs to : \n"
	echo NUMNODES=$numNode
	g++ -DNUMNODES=$numNode ConsoleApplication2.cpp -o prog02numNodesRun -lm -fopenmp
	printf "\n"
	./prog02numNodesRun
	printf "_________________________\n"
done

