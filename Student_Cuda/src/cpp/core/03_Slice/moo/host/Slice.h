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

class Slice
    {
    public:
	Slice(Grid& grid, int n);
	~Slice();

	void run();

	float getPI();

    private:

	void reduceTab();

	//Input
	int n;
	Grid grid;

	//Output
	float pi;

	//Tools
	float* ptrTabGM;
	float* ptrTab;
	size_t sizeTab;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
