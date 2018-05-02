#include "MandelBrotProvider2.h"
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
Animable_I<uchar4>* MandelBrotProvider2::createAnimable()
    {
    DomaineMath domaineMath = DomaineMath(-1.39, -1.35, -0.03, 0);

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
Image_I* MandelBrotProvider2::createImageGL(void)
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
