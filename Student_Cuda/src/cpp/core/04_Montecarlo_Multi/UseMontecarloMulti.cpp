#include "VectorTools.h"
#include "Grid.h"
#include "Device.h"
#include "MathTools.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

#include "MontecarloMultiGPU.h"

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useMontecarloMulti(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useMontecarloMulti()
    {
    int n = INT_MAX/10;
    const float EPSILON = 0.001;

    // Grid cuda
    dim3 dg = dim3(1, 1, 1);
    dim3 db = dim3(512, 1, 1);

    Grid grid(dg, db);

    MontecarloMultiGPU montecarlomulti(grid, n);
    montecarlomulti.run();

    printf("MontecarloMulti : %f \n", montecarlomulti.getPI());
    bool isOk = MathTools::isEquals(montecarlomulti.getPI(), (float) PI, EPSILON);
    printf("Result : %s \n", isOk ? "OK" : "KO");
    return isOk;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


