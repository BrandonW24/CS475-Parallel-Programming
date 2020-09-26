
#number of threads :
for numThrd in 1 2 3 4 5 6 7 8
	do
	printf "Changing number of threads to : \n"
	echo NUMTHREADS=$numThrd
	g++ -DNUMTHREADS=$numThrd ConsoleApplication2.cpp -o prog02numThrds -lm -fopenmp
	printf "\n"
	./prog02numThrds
	printf "_________________________\n"
done

