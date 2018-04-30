#include "Montecarlo.h"
#include "Device.h"
#include "cudaTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void montecarloDevice(float* ptrResultGM, int n, curandState* tabDevGeneratorGM);
__global__ void createGenerator(curandState* tabDevGeneratorGM, int deviceId);

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
    this->n0 = 0;

    tabDevGenerator = new curandState[grid.threadCounts()];

    this->sizeTabSM = grid.threadCounts() * sizeof(float);
    this->sizeTabGenerator = grid.threadCounts() * sizeof(curandState);

    Device::malloc(&ptrResultGM, sizeof(float));
    Device::memclear(ptrResultGM, sizeof(float));

    Device::malloc(&tabDevGeneratorGM, sizeTabGenerator);
    Device::memclear(tabDevGeneratorGM, sizeTabGenerator);
    }

Montecarlo::~Montecarlo()
    {
    Device::free(ptrResultGM);
    Device::free(tabDevGeneratorGM);
    delete[] tabDevGenerator;
    }

void Montecarlo::run()
    {
    Device::lastCudaError("Slice (before)");

    dim3 dg = grid.dg;
    dim3 db = grid.db;

    createGenerator<<<dg, db>>>(tabDevGeneratorGM, 0);

    Device::memcpyDToH(tabDevGenerator, tabDevGeneratorGM, sizeof(float));

    int nPerThread = n / grid.threadCounts();
    montecarloDevice<<<dg,db,sizeTabSM>>>(ptrResultGM,nPerThread,tabDevGeneratorGM);

    Device::lastCudaError("Slice (after)");

    Device::memcpyDToH(&pi, ptrResultGM, sizeof(float));

    this->n0 = pi;
    this->pi = 2 * 4 * n0 / (float) n;
    }

float Montecarlo::getPI()
    {
    return this->pi;
    }

int Montecarlo::getN0()
    {
    return this->n0;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

