nclude <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <cstdlib>
#include <stdio.h>

#define XMIN     -1.
#define XMAX      1.
#define YMIN     -1.
#define YMAX      1.

#ifndef NUMNODES
#define NUMNODES 100
#endif

#ifndef NUMTHREADS
#define NUMTHREADS 4
#endif // !NUMTHREADS


#ifndef N
#define N 2
#endif // !N


double Height(int iu, int iv)	// iu,iv = 0 .. NUMNODES-1
{
	double x = -1. + 2.*(double)iu / (double)(NUMNODES - 1);	// -1. to +1.
	double y = -1. + 2.*(double)iv / (double)(NUMNODES - 1);	// -1. to +1.

	double xn = pow(fabs(x), (double)N);
	double yn = pow(fabs(y), (double)N);
	double r = 1. - xn - yn;
	if (r < 0.)
		return 0.;
	double height = pow(1. - xn - yn, 1. / (double)N);
	return height;
}


double Height(int, int);
double volumeSum = 0.;

int main(int argc, char *argv[])
{

#ifndef _OPENMP
		fprintf(stderr, "No OpenMP support!\n");
		return 1;
#endif
		omp_set_num_threads(NUMTHREADS);
		double timer0 = omp_get_wtime();
		
		double volume = 0.;
		double numMegaHeightsCalculated = 0.;
		double MaxMegaHeightsPerSecond = 0.;
		double calc = 0.;

		double fullTileArea = (((XMAX - XMIN) / (double)(NUMNODES - 1))  * ((YMAX - YMIN) / (double)(NUMNODES - 1)));

#pragma omp parallel for default(none) reduction(+:volumeSum) shared(fullTileArea)				//Volume reduction and sharing full tile area
		for (int i = 0; i < NUMNODES*NUMNODES; i++)
		{
			int iu = i % NUMNODES;
			int iv = i / NUMNODES;
			double z = Height(iu, iv) * 2;									//Multiplying height by 2

// the area of a single full-sized tile:
// 		//if edge statement
// 					if (iu >= 1 && iu < NUMNODES-1 && iv >= 1 && iv < NUMNODES-1) {
// 									double fullTileArea = (((XMAX - XMIN) / (double)(NUMNODES - 1))  *
// 														((YMAX - YMIN) / (double)(NUMNODES - 1)));
// 																		printf("Center Tile detected : %f iu: %d\tiv: %d\tHeight: %f\t \n ", fullTileArea, iu, iv, z);
// 																						volumeSum += (fullTileArea)*z;
// 																						//				numMegaHeightsCalculated += 1;
// 																									}
// 																												else if (iu == 0 && iv == 0 || iu == 0 && iv >= NUMNODES-1 || iu >= NUMNODES-1 && iv == 0) {
// 																																double quarterTileArea = (((XMAX - XMIN) / (double)(NUMNODES - 1))  *
// 																																					((YMAX - YMIN) / (double)(NUMNODES - 1)));
// 																																									printf("Corner Tile detected : %f iu: %d\tiv: %d\tHeight: %f\t \n ", quarterTileArea/4, iu, iv, z);
// 																																													volumeSum += (quarterTileArea/4) * z;
// 																																													//				numMegaHeightsCalculated += 1;
// 																																																}
// 																																																			else if (iu >= NUMNODES-1 && iv >= NUMNODES-1) {
// 																																																							double quarterTileArea = (((XMAX - XMIN) / (double)(NUMNODES - 1))  *
// 																																																												((YMAX - YMIN) / (double)(NUMNODES - 1)));
// 																																																																printf("Corner Tile detected : %f iu: %d\tiv: %d\tHeight: %f\t \n ", quarterTileArea / 4, iu, iv, z);
// 																																																																				volumeSum += (quarterTileArea/4) * z;
// 																																																																				//				numMegaHeightsCalculated += 1;
// 																																																																							}
// 																																																																										else {
// 																																																																														double halfTileArea = (((XMAX - XMIN) / (double)(NUMNODES - 1))  *
// 																																																																																			((YMAX - YMIN) / (double)(NUMNODES - 1)));
// 																																																																																							printf("Edge Tile detected : %f iu: %d\tiv: %d\tHeight: %f\t \n ", halfTileArea / 2, iu, iv, z);
// 																																																																																											volumeSum += (halfTileArea/2) * z;
// 																																																																																											//				numMegaHeightsCalculated += 1;
// 																																																																																														}
// 																																																																																																double timer1 = omp_get_wtime();
// 																																																																																																		double megaHeightperformance = NUMNODES*NUMNODES / (timer1-timer0)/1000000.;
// 																																																																																																			//	numMegaHeightsCalculated += 1;
// 																																																																																																					double completeTime = timer1 - timer0;
// 																																																																																																							calc += megaHeightperformance;
// 																																																																																																									
//
// 																																																																																																											if (megaHeightperformance > MaxMegaHeightsPerSecond)
// 																																																																																																														MaxMegaHeightsPerSecond = megaHeightperformance;
// 																																																																																																																}
//
//
//
// 																																																																																																																		printf("Volume total = %8f \n", volumeSum);
// 																																																																																																																				printf("MegaHeights per second = %f \n", MaxMegaHeightsPerSecond);
// 																																																																																																																					//	printf("Time total = %8f \n", (numMegaHeightsCalculated));
// 																																																																																																																							
// 																																																																																																																								// sum up the weighted heights into the variable "volume"
// 																																																																																																																									// using an OpenMP for loop and a reduction:
//
//
// 																																																																																																																									//	? ? ? ? ?
// 																																																																																																																									}
