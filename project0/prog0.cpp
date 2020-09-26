// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <cstdio>
#include <float.h>

//#define NUMT 		4	//Change this to NUMT 1 for the first part, take the timing, then back to 4 and take the runs.
#define SIZE       	55000	// you decide
#define NUMTRIES        6798	// you decide

float A[SIZE];
float B[SIZE];
float C[SIZE];

void getNumProcs()
{
	int numprocs = omp_get_num_procs();
	fprintf(stderr, "Number of available threads : %d \n", numprocs); //(For testing purposes) 
	fprintf(stderr, "\n");
}


void reserveThreads()
{
	omp_set_num_threads(NUMT);
	fprintf(stderr, "Reserving %d threads to be used \n", NUMT);
}

int main()
{

#ifndef _OPENMP
	fprintf(stderr, "OpenMP is not set here -- sorry. Set OpenMP and try again. \n");
	return 1;
#endif

	// inialize the arrays:
	for (int i = 0; i < SIZE; i++)
	{
		A[i] = 1.;
		B[i] = 2.;
	}

	getNumProcs();

	reserveThreads();

	double maxiMult = 0., sumMult = 0.;

	for (int t = 0; t < NUMTRIES; t++)
	{
		double time0 = omp_get_wtime();

#pragma omp parallel for
		for (int i = 0; i < SIZE; i++)		//Multiplying two arrays together
		{
			C[i] = A[i] * B[i];
		}

		double time1 = omp_get_wtime(), megaMults = (double)SIZE / (time1 - time0) / 1000000.;
		sumMult = sumMult + megaMults;
		if (megaMults > maxiMult)
		{
			maxiMult = megaMults;
		}

	}


	printf("Peak performance is = %8.2lf MegaMults/sec\n", maxiMult);
	printf("Average performance = %8.2lf MegaMults/sec\n", sumMult / (double)NUMTRIES);
	printf("\n");
	printf("___________\n");
	return 0;
}
