#include "Device.h"
#include "SliceAdvanced.h"
#include "cudaTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

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

SliceAdvanced::SliceAdvanced(Grid& grid, int n) :
	grid(grid), n(n)
    {
    this->pi = 0;

    this->sizeTabSM = grid.threadCounts() * sizeof(float);

    Device::malloc(&ptrResultGM, sizeof(float)); //resultat
    Device::memclear(ptrResultGM, sizeof(float));

    Device::lastCudaError("MM (end allocation)"); // temp debug, facultatif
    }

SliceAdvanced::~SliceAdvanced()
    {
    Device::free(ptrResultGM);
    }

void SliceAdvanced::run()
    {
    Device::lastCudaError("Slice (before)");

    sliceAdvancedDevice<<<grid.dg,grid.db,sizeTabSM>>>(ptrResultGM,n);

    Device::lastCudaError("Slice (after)");

    Device::memcpyDToH(&pi, ptrResultGM, sizeof(float));

    this->pi = this->pi / n;
    }

float SliceAdvanced::getPI()
    {
    return this->pi;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

