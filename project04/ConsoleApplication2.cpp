#include <omp.h>
#include <stdio.h>
#include <xmmintrin.h>
#define SSE_WIDTH		4
#include <limits.h>

//#ifndef arraySize
//#define arraySize 1024
//#endif

//float *in1 = new float[size];
//float *in2 = new float[size];
//float *in3 = new float[size];
//float *out = new float[size];
float c;

float SimdMulSum(float *a, float *b, int len)
{
	float sum[4] = { 0., 0., 0., 0. };
	int limit = (len / SSE_WIDTH) * SSE_WIDTH;
	register float *pa = a;
	register float *pb = b;

	__m128 ss = _mm_loadu_ps(&sum[0]);
	for (int i = 0; i < limit; i += SSE_WIDTH)
	{
		ss = _mm_add_ps(ss, _mm_mul_ps(_mm_loadu_ps(pa), _mm_loadu_ps(pb)));
		pa += SSE_WIDTH;
		pb += SSE_WIDTH;
	}
	_mm_storeu_ps(&sum[0], ss);

	for (int i = limit; i < len; i++)
	{
		sum[0] += a[i] * b[i];
	}

	return sum[0] + sum[1] + sum[2] + sum[3];
}


float MulReduc(float *ar1, float *ar2, int len) {
	float mulSum = 0;
	for (int i = 0; i < len; i++) {
		mulSum += ar1[i] * ar2[i];
	}
	return mulSum;
}


int main() {
	printf("Array Size,                        SIMD megamults ,                     C++ Reduction SIMD,             SPEED UP \n");
	printf("_________________\n");

	for (int arraySize = 64; arraySize <= 496 * 496 * 64;  arraySize = arraySize * 2 ) {
		printf("Array Size : %d    |", arraySize);

		//Initialization
		float *array1 = new float[arraySize], *array2 = new float[arraySize], *outputArray = new float[arraySize];

		//Starting the timer for the SIMD multiplication and summation
		double startTimer = omp_get_wtime();
		SimdMulSum(array1, array2, arraySize);
		double endTimer = omp_get_wtime();

		//Ended timer, getting performance of SIMD multiplication & summation
		printf("|  Simd mul sum megaMulsPerSecond == %f  |", (float)arraySize / (-startTimer + endTimer) / 1000000.0);
		double SimdSpeed = (float)arraySize / (-startTimer + endTimer) / 1000000.0;

		//Starting the timer on the C++ mul / reduc code
		startTimer = omp_get_wtime();
		MulReduc(array1, array2, arraySize);
		endTimer = omp_get_wtime();

		//Ended timer, getting performance of array multi (without simd)
		printf("|   C++ Reduction %f   |", (float)arraySize / (-startTimer + endTimer) / 1000000.0);
		double MulSpeed = (float)arraySize / (-startTimer + endTimer) / 1000000.0;

		//Calculating Speed up
		printf("| Speed up ratio : %f \n", (SimdSpeed / MulSpeed));
		
	}
	printf("* Window needs to be expanded * \n");
	printf("\n");
	return 0;
}
