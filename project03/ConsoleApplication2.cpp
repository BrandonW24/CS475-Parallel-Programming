#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <cstdlib>
#include <stdio.h>
#include <cmath>
#include <iostream>

const float GRAIN_GROWS_PER_MONTH = 9.0;
const float ONE_DEER_EATS_PER_MONTH = 1.0;

const float AVG_PRECIP_PER_MONTH = 7.0;	// average
const float AMP_PRECIP_PER_MONTH = 6.0;	// plus or minus
const float RANDOM_PRECIP = 2.0;		// plus or minus noise

const float AVG_TEMP = 60.0;	// average
const float AMP_TEMP = 20.0;	// plus or minus
const float RANDOM_TEMP = 10.0;	// plus or minus noise

const float MIDTEMP = 40.0;
const float MIDPRECIP = 10.0;

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

int		NowYear = 2020, NowMonth=0;		// 0 - 11

//Change to starting numbers
float	NowPrecip;		// inches of rain per month
float	NowTemp;		// temperature this month
float	NowHeight	= 100;		// grain height in inches
int		NowNumDeer	= 10;		// number of deer in the current population
int		NowGoats	= 1;			//number of aggressive goats.

float Ranf(unsigned int *seedp, float low, float high) {
	float r = (float)rand_r(seedp);              // 0 - RAND_MAX

	return(low + r * (high - low) / (float)RAND_MAX);
}

int Ranf(unsigned int *seedp, int ilow, int ihigh)
{
	float low = (float)ilow;
	float high = (float)ihigh + 0.9999f;

	return (int)(Ranf(seedp, low, high));
}

unsigned int seed = 0;  // a thread-private variable
float x = Ranf(&seed, -1.f, 1.f);

omp_lock_t	Lock;
int		NumInThreadTeam;
int		NumAtBarrier;
int		NumGone;

void InitBarrier(int n)
{
	NumInThreadTeam = n;
	NumAtBarrier = 0;
	omp_init_lock(&Lock);
}

void WaitBarrier()
{
	omp_set_lock(&Lock);
	{
		NumAtBarrier++;
		if (NumAtBarrier == NumInThreadTeam)
		{
			NumGone = 0;
			NumAtBarrier = 0;
			// let all other threads get back to what they were doing
			// before this one unlocks, knowing that they might immediately
			// call WaitBarrier( ) again:
			while (NumGone != NumInThreadTeam - 1);
			omp_unset_lock(&Lock);
			return;
		}
	}
	omp_unset_lock(&Lock);

	while (NumAtBarrier != 0);	// this waits for the nth thread to arrive

#pragma omp atomic
	NumGone++;			// this flags how many threads have returned
}
float SQR(float x)
{
	return x*x;
}

void	InitBarrier(int);
void	WaitBarrier();

void GrainDeerTrial() {

	while (NowYear < 2026)
	{
		int NewgrainDeer = NowNumDeer;
		if (NewgrainDeer != NowHeight) {
			if (NewgrainDeer > NowHeight) {
				NewgrainDeer -= 1;
			}
			else if (NewgrainDeer <= NowHeight) {
				NewgrainDeer += 1;
			}
			}
		#pragma omp barrier
			//	. . .
			NowNumDeer = NewgrainDeer;
			// DoneAssigning barrier:
		#pragma omp barrier
			//	. . .

			// DonePrinting barrier:
		#pragma omp barrier
		//. . .
	}
}


void GrainTrial() {

	while (NowYear < 2026)
	{
		// compute a temporary next-value for this quantity
		// based on the current state of the simulation:
		float tempHeight = NowHeight;
		float tempFactor = exp(-SQR((NowTemp - MIDTEMP) / 10.0));
		float precipFactor = exp(-SQR((NowPrecip - MIDPRECIP) / 10.0));
		tempHeight += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
		tempHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;
		if (tempHeight <= 0) {
			tempHeight = 0;
		}
		// DoneComputing barrier:
#pragma omp barrier
		NowHeight = tempHeight;

		// DoneAssigning barrier:
#pragma omp barrier

		// DonePrinting barrier:
#pragma omp barrier
	}

}


void printerhelperFunc() {
	printf("NowMonth : %d, NowYear : %d, \n, NowNumDeer : %d, \n NowPrecip : %f, NowTemp : %f \n NowHeight : %f, NowGoats : %d \n",
		NowMonth, NowYear, NowNumDeer, NowPrecip, NowTemp, NowHeight, NowGoats);
}

void WatcherTrial() {

	while (NowYear < 2026)
	{
		// compute a temporary next-value for this quantity
		// based on the current state of the simulation:
		//	. . .
		float ang = (30.*(float)NowMonth + 15.) * (M_PI / 180.);

		float temp = AVG_TEMP - AMP_TEMP * cos(ang);
		NowTemp = temp + Ranf(&seed, -RANDOM_TEMP, RANDOM_TEMP);
		float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin(ang);
		NowPrecip = precip + Ranf(&seed, -RANDOM_PRECIP, RANDOM_PRECIP);
		// DoneComputing barrier:
		#pragma omp barrier
		//	. . .

		// DoneAssigning barrier:

		#pragma omp barrier
		printerhelperFunc();
		if (NowMonth == 12) {
			NowMonth = 0;
			NowYear += 1;
		}
		else if (NowMonth < 12) {
			NowMonth += 1;
		}
		// DonePrinting barrier:

		#pragma omp barrier
		//. . .
}
}
//CHANGE THIS!!!!
void GoatTrial() {
	while (NowYear < 2026)
	{
		int newGoat = NowGoats;
		int deerGoatTrial = NowNumDeer;
		int tempHeight = NowHeight;
		// compute a temporary next-value for this quantity
		// based on the current state of the simulation:
		int headbutts = Ranf(&seed, 0, 5);
		//Goat has 2/6 chance of headbutting a deer. This guarantees that the goat kills the deer. Goat population increases. The goat gets two chances to headbutt.
		if (deerGoatTrial >= 1) {
			if (headbutts == 4 || headbutts == 5) {
				deerGoatTrial -= 1;
				newGoat += 1;
			}
			else if (headbutts == 0) { //Goat has 1/6 chance of encountering a deer, trying to headbutt it and missing. 0 is a critical failure. This case, the deer lives, two goats die chasing one deer.
				newGoat -= 2;
				deerGoatTrial += 1;
			}
			else if (headbutts == 2 && NowTemp <= 45 || headbutts == 1 && NowTemp >= 50) { //Goat has a 2/6 chance of clipping a deer with their headbutt move. This damages the deer and it dies after it runs away from the goat.
				deerGoatTrial--;		    // The goat does not get to eat.
				newGoat -= 1;
			}
			else if (headbutts == 3) {
				//Nothing happens, the goat just misses and eats grain.

			}
		}
		else {
			if (tempHeight > 0) {
				tempHeight -= newGoat / 7.;
			}
			else if (tempHeight <= 0) {
				newGoat -= 1;
				}
			}
		

		// DoneComputing barrier:
#pragma omp barrier
		NowNumDeer = deerGoatTrial;
		NowGoats = newGoat;
		NowHeight = tempHeight;
		// DoneAssigning barrier:
#pragma omp barrier


		// DonePrinting barrier:
#pragma omp barrier

	}
}


int main(int argc, char *argv[])
{

#ifndef _OPENMP
		fprintf(stderr, "There is no OpenMP support!\n");
		return 1;
#endif
		omp_set_num_threads(4);    // same as # of sections
		InitBarrier(4);

#pragma omp parallel sections
		{
	#pragma omp section
			{
				GrainDeerTrial();
			}

	#pragma omp section
			{
				GrainTrial();
			}

	#pragma omp section
			{
				WatcherTrial();
			}

	#pragma omp section
			{
				GoatTrial();    // your own can change this 
			}
		}       // implied barrier -- all functions must return in order
				// to allow any of them to get past here

		return 0;
}