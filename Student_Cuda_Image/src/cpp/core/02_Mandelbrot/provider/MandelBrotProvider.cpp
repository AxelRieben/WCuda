#include "MandelBrotProvider.h"
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
Animable_I<uchar4>* MandelBrotProvider::createAnimable()
    {
    DomaineMath domaineMath = DomaineMath(-2.1, -1.3, 0.8, 1.3);

    // Animation
    float dt = 1;
    int n = 100;

    // Dimension
    int w = 16 * 32 * 2;
    int h = 16 * 32;

    // Grid Cuda
    int mp = Device::getMPCount();
    int coreMP = Device::getCoreCountMP();

    dim3 dg = dim3(4, 6, 1);
    dim3 db = dim3(96, 10, 1);
    Grid grid(dg, db);

    return new MandelBrot(grid, w, h, dt, n, domaineMath);
    }

/**
 * Override
 */
Image_I* MandelBrotProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(0, 0, 0); // black
    return new ImageAnimable_RGBA_uchar4(createAnimable(), colorTexte);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
