#include <iostream>
#include "Grid.h"
#include "Device.h"
#include <cmath>
#include <limits.h>
#include "MathTools.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

#include "Slice.h"

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useSlice(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useSlice()
    {
    int n = INT_MAX / 10;
    const float EPSILON = 0.0001;

    // Grid cuda
    int mp = Device::getMPCount();
    int coreMP = Device::getCoreCountMP();

    dim3 dg = dim3(mp, 1, 1);
    dim3 db = dim3(coreMP, 1, 1);

    Grid grid(dg, db);

    Slice slice(grid, n);
    slice.run();

    printf("Slice : %f \n", slice.getPI());
    bool isOk = MathTools::isEquals(slice.getPI(), (float) PI, EPSILON);
    printf("Result : %s \n", isOk ? "OK" : "KO");
    return isOk;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

