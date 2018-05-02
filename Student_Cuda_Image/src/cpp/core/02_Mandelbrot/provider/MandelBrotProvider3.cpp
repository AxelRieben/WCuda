#include "MandelBrotProvider3.h"
#include "MandelBrot.h"

#include "MathTools.h"
#include "Grid.h"

#include "DomaineMath_GPU.h"

using gpu::DomaineMath;

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
Animable_I<uchar4>* MandelBrotProvider3::createAnimable()
    {
    DomaineMath domaineMath = DomaineMath(-1.3968, -0.03362, -1.3578, 0.0013973);

    // Animation
    int dt = 1;
    int n = 100;

    // Dimension
    int w = 1280;
    int h = 720;

    // Grid Cuda
    int mp = Device::getMPCount();
    int coreMP = Device::getCoreCountMP();

    //Opti
//    dim3 dg = dim3(4, 6, 1);
//    dim3 db = dim3(96, 10, 1);

//Test
    dim3 dg = dim3(mp, 2, 1);
    dim3 db = dim3(coreMP, 2, 1);
    Grid grid(dg, db);

    return new MandelBrot(grid, w, h, dt, n, domaineMath);
    }

/**
 * Override
 */
Image_I* MandelBrotProvider3::createImageGL(void)
    {
    ColorRGB_01 colorTexte(1, 1, 1); // black
    return new ImageAnimable_RGBA_uchar4(createAnimable(), colorTexte);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
