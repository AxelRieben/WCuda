#include "MontecarloMultiGPU.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

MontecarloMultiGPU::MontecarloMultiGPU(Grid& grid, int n) :
	grid(grid), n(n)
    {
    this->pi = 0;

    }

MontecarloMultiGPU::~MontecarloMultiGPU()
    {

    }

void MontecarloMultiGPU::run()
    {
    int n0 = 0;
    int nGPU = n / Device::getDeviceCount();
    int nTotEffectif = nGPU * Device::getDeviceCount();

#pragma omp parallel for reduction(+:n0)
    for (int deviceId = 0; deviceId < Device::getDeviceCount(); deviceId++)
	{
	Device::setDevice(deviceId);
	Montecarlo montecarlo(grid, nGPU);
	montecarlo.run();
	n0 += montecarlo.getN0();
	}

    this->pi = 2 * 4 * n0 / (float) nTotEffectif;
    }

float MontecarloMultiGPU::getPI()
    {
    return this->pi;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

