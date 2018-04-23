#include "Montecarlo.h"

#include "Device.h"
#include "cudaTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

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

Montecarlo::Montecarlo(Grid& grid, int n) :
	grid(grid), n(n)
    {
    this->pi = 0;

    ptrResult = 0;

    this->sizeTabSM = n * sizeof(float);

    Device::malloc(&ptrResultGM, sizeof(float)); //resultat
    Device::memclear(ptrResultGM, sizeof(float));
    }

Montecarlo::~Montecarlo()
    {
    Device::free(ptrResultGM);
    }

void Montecarlo::run()
    {
    Device::lastCudaError("Slice (before)");

    dim3 dg = grid.dg;
    dim3 db = grid.db;

    montecarloDevice<<<dg,db,sizeTabSM>>>(ptrResultGM,n);

    Device::lastCudaError("Slice (after)");

    Device::memcpyDToH(ptrResult, ptrResultGM, sizeof(float));

    this->pi = *ptrResult;
    }

float Montecarlo::getPI()
    {
    return this->pi;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

