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

#include "SliceAdvanced.h"

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useSliceAdvanced(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useSliceAdvanced()
    {
    int n = INT_MAX / 10;
    const float EPSILON = 0.0001;

    dim3 dg = dim3(1, 1, 1);
    dim3 db = dim3(512, 1, 1); //Utiliser soit 128, 256, 512 ou 1024 selon hypothèses

    Grid grid(dg, db);

    SliceAdvanced sliceAdvanced(grid, n);
    sliceAdvanced.run();

    printf("SliceAdvanced : %f \n", sliceAdvanced.getPI());
    bool isOk = MathTools::isEquals(sliceAdvanced.getPI(), (float) PI, EPSILON);
    printf("Result : %s \n", isOk ? "OK" : "KO");
    return isOk;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

