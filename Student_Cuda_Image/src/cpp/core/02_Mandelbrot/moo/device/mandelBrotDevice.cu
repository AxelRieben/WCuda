#include "MandelBrotMath.h"
#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"

#include "IndiceTools_GPU.h"
#include "DomaineMath_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void mandelBrot(uchar4* ptrDevPixels, uint w, uint h, uint n, DomaineMath domaineMath, float t);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void mandelBrot(uchar4* ptrDevPixels, uint w, uint h, uint n, DomaineMath domaineMath, float t)
    {
    MandelBrotMath mandelBrotMath;

    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();
    const int WH = w * h;

    double x = 0;
    double y = 0;

    int i;
    int j;

    int s = TID;
    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &i, &j);

	domaineMath.toXY(i, j, &x, &y); // fill (x,y) from (i,j)

	mandelBrotMath.colorXY(&ptrDevPixels[s], x, y, t); // in [01]

	s += NB_THREAD;
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

