#ifndef SRC_CPP_CORE_03_SLICE_MOO_HOST_SLICE_H_
#define SRC_CPP_CORE_03_SLICE_MOO_HOST_SLICE_H_
#include "cudaTools.h"
#include "MathTools.h"
#include "Grid.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class SliceAdvanced
    {
    public:
	SliceAdvanced(Grid& grid, int n);
	~SliceAdvanced();

	void run();

	float getPI();

    private:

	//Input
	int n;
	Grid grid;

	//Output
	float pi;

	//Tools
	float* ptrResultGM;
	size_t sizeTabSM;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
