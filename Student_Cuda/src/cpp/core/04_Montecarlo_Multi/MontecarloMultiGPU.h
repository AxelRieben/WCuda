#ifndef SRC_CPP_CORE_04_MONTECARLO_MULTI_MONTECARLOMULTIGPU_H_
#define SRC_CPP_CORE_04_MONTECARLO_MULTI_MONTECARLOMULTIGPU_H_

#include "cudaTools.h"
#include "MathTools.h"
#include "Grid.h"
#include "Device.h"
#include "Montecarlo.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MontecarloMultiGPU
    {
    public:
	MontecarloMultiGPU(Grid& grid, int n);
	~MontecarloMultiGPU();

	void run();
	float getPI();

    private:
	//Input
	Grid grid;
	int n;

	//Output
	float pi;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
