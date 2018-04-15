#include "Slice.h"
#include "Device.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

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

Slice::Slice(Grid& grid, int n) : grid(grid), n(n)
    {
    this->pi = 0;

    ptrTab = new float[n];

    this->sizeTab = n * sizeof(float);
    Device::malloc(&ptrTabGM, sizeTab);
    Device::memcpyHToD(ptrTabGM, ptrTab, sizeTab);
    }

Slice::~Slice()
    {
    Device::free(ptrTabGM);
    delete[] ptrTab;
    }

void Slice::run()
    {
    Device::lastCudaError("Slice (before)");

    dim3 dg = grid.dg;
    dim3 db = grid.db;

    sliceDevice<<<dg,db>>>(ptrTabGM,n);

    Device::lastCudaError("Slice (after)");

    Device::memcpyDToH(ptrTab, ptrTabGM, sizeTab);

    reduceTab();
    }

float Slice::getPI()
    {
    return this->pi;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void Slice::reduceTab()
    {
    float sum = 0;

#pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++)
	{
	sum += ptrTab[i];
	}

    this->pi = sum * (1 / (double) n);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

