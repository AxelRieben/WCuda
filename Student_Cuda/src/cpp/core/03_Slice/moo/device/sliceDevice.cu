#include "Indice2D.h"
#include "Indice1D.h"
#include "cudaTools.h"

#include <stdio.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

__device__ double fpi(double x);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void sliceDevice(float* ptrTabGM, int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void sliceDevice(float* ptrTabGM, int n)
    {
    const int NB_THREAD = Indice2D::nbThread();
    const int TID = Indice2D::tid();
    int s = TID;

    const double DX = 1 / (double) n;
    double sommeThread = 0;
    double xs = 0;

    while (s < n)
	{
	xs = s * DX;
	sommeThread += fpi(xs);
	s += NB_THREAD;
	}

    ptrTabGM[TID] = sommeThread;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ double fpi(double x)
    {
    return 4 / (1 + x * x);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

