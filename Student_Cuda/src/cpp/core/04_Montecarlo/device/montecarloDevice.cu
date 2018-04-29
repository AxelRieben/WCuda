#include "Indice1D.h"
#include "cudaTools.h"
#include "reductionADD.h"
#include "Calibreur_GPU.h"
#include <curand_kernel.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

__device__ float f(float x);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void montecarloDevice(float* ptrResultGM, int n, curandState* tabDevGeneratorGM);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void montecarloDevice(float* ptrResultGM, int n, curandState* tabDevGeneratorGM)
    {
    //Shared Memory
    __shared__ extern float tabSM[];

    //Montecarlo
    int n0 = 0;
    const int a = -1;
    const int b = 1;
    const int m = 2;

    const int TID = Indice1D::tid();
    const int TID_LOCAL = Indice1D::tidLocal();

    // Global Memory -> Register (optimization)
    curandState localGenerator = tabDevGeneratorGM [TID];
    float xAlea;
    float yAlea;

    for (long i = 1; i <= n; i++)
    {
    xAlea = a + (b-a) * curand_uniform(&localGenerator);
    yAlea = m * curand_uniform(&localGenerator);

    if(yAlea < f(xAlea))
	{
	    n0++;
	}

    }

    tabDevGeneratorGM[TID] = localGenerator;
    tabSM[TID_LOCAL] = n0;

    __syncthreads();

    reductionADD(tabSM, ptrResultGM);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ float f(float x)
    {
    return sqrt(1-(x*x));
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

