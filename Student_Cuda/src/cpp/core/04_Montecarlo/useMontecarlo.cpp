#include <iostream>
#include "VectorTools.h"
#include "Grid.h"
#include "Device.h"
#include "MathTools.h"
#include <cmath>

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

#include "Montecarlo.h"

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useMontecarlo(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useMontecarlo()
    {
    int n = INT_MAX / 10;
    const float EPSILON = 0.001;

    // Grid cuda
    int mp = Device::getMPCount();
    int coreMP = Device::getCoreCountMP();

    dim3 dg = dim3(1, 1, 1);
    dim3 db = dim3(512, 1, 1);

    Grid grid(dg, db);

    Montecarlo montecarlo(grid, n);
    montecarlo.run();

    printf("Montecarlo : %f \n", montecarlo.getPI());
    bool isOk = MathTools::isEquals(montecarlo.getPI(), (float) PI, EPSILON);
    printf("Result : %s \n", isOk ? "OK" : "KO");
    return isOk;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

