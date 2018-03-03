#include "RayTracing.h"

#include "MathTools.h"
#include "Grid.h"
#include "RayTracingProvider.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

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

/**
 * Override
 */
Animable_I<uchar4>* RayTracingProvider::createAnimable()
    {
    // Animation;
    float dt = 0;

    // Dimension
    int w = 16 * 48;
    int h = 16 * 48;

    // Grid Cuda
    int mp = Device::getMPCount();
    int coreMP = Device::getCoreCountMP();

    dim3 dg = dim3(mp, 2, 1);  		// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
    dim3 db = dim3(coreMP, 2, 1);   	// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
    Grid grid(dg, db);

    return new RayTracing(grid, w, h, dt);
    }

/**
 * Override
 */
Image_I* RayTracingProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(1, 1, 1); // red
    return new ImageAnimable_RGBA_uchar4(createAnimable(), colorTexte);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
