#ifndef SRC_CPP_CORE_03_SLICE_MOO_HOST_SLICE_H_
#define SRC_CPP_CORE_03_SLICE_MOO_HOST_SLICE_H_
#include "cudaTools.h"
#include "MathTools.h"
#include "Grid.h"
#include <curand_kernel.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Montecarlo
    {
    public:
	Montecarlo(Grid& grid, int n);
	~Montecarlo();

	void run();

	float getPI();

    private:

	//Input
	int n;
	Grid grid;

	//Output
	float pi;

	//Tools
	size_t sizeTabGenerator;
	curandState* tabDevGeneratorGM;
	curandState* tabDevGenerator;
	float* ptrResultGM;
	size_t sizeTabSM;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
