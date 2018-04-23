#include "Indice1D.h"
#include "cudaTools.h"
#include "reductionADD.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

__device__ float fpiAdvanced(float x);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void sliceAdvancedDevice(float* ptrResultGM, int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void sliceAdvancedDevice(float* ptrResultGM, int n)
    {
    //Shared Memory
    extern __shared__ float tabSM[];

    const int NB_THREAD = Indice1D::nbThread();
    const int TID = Indice1D::tid();
    const int TID_LOCAL = Indice1D::tidLocal();
    int s = TID;

    const float DX = 1 / (float) n;
    float sommeThread = 0;
    float xs = 0;

    while (s < n)
	{
	xs = s * DX;
	sommeThread += fpiAdvanced(xs);
	s += NB_THREAD;
	}

    tabSM[TID_LOCAL] = sommeThread;

    __syncthreads();

    reductionADD(tabSM, ptrResultGM);

    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ float fpiAdvanced(float x)
    {
    return 4 / (1 + x * x);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

