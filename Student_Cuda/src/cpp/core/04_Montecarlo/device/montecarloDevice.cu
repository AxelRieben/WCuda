#include "Indice1D.h"
#include "cudaTools.h"
#include "reductionADD.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

__device__ float f(float x);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void montecarloDevice(float* ptrResultGM, int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/


__global__ void montecarloDevice(float* ptrResultGM, int n)
    {
    //Shared Memory
    __shared__ extern float tabSM[];

    const int NB_THREAD = Indice1D::nbThread();
    //const int NB_THREAD_BLOCK = Indice1D::nbThreadBlock();
    const int TID = Indice1D::tid();
    const int TID_LOCAL = Indice1D::tidLocal();
    int s = TID;

    const float DX = 1 / (float) n;
    float sommeThread = 0;
    float xs = 0;

    while (s < n)
	{
	xs = s * DX;
	sommeThread += f(xs);
	s += NB_THREAD;
	}

    tabSM[TID_LOCAL] = sommeThread;

    __syncthreads();

    reductionADD(tabSM, ptrResultGM);

    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ float f(float x)
    {
    return sqrt(1-x*x);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

