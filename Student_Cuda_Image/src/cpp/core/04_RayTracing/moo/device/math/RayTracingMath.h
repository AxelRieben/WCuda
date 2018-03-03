#pragma once

#include <math.h>
#include "MathTools.h"
#include "Sphere.h"

#include "ColorTools_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RayTracingMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ RayTracingMath(int w, int h, Sphere* ptrDevTabSphere, int nbSphere)
	    {
	    this->ptrDevTabSphere = ptrDevTabSphere;
	    this->nbSphere = nbSphere;
	    this->ptrNearestSphere = 0;
	    this->ptrDevCurrentSphere = 0;
	    }

	__device__      virtual ~RayTracingMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorIJ(uchar4* ptrColor, int i, int j, float t)
	    {
	    //Init
	    float2 xySol;
	    xySol.x = i;
	    xySol.y = j;
	    float distance = 9999999.f;
	    float dz = 0.f;

	    //Loop in sphere array
	    for (int index = 0; index < nbSphere; index++)
		{
		ptrDevCurrentSphere = &ptrDevTabSphere[index];
		float hCarree = ptrDevCurrentSphere->hCarre(xySol);

		if (ptrDevCurrentSphere->isEnDessous(hCarree))
		    {
		    float dzCurrent = ptrDevCurrentSphere->dz(hCarree);
		    float distanceCurrent = ptrDevCurrentSphere->distance(dzCurrent);

		    if (distanceCurrent < distance)
			{
			dz = dzCurrent;
			distance = distanceCurrent;
			ptrNearestSphere = ptrDevCurrentSphere;
			}
		    }
		}

	    //Color the pixel with the color of the nearest sphere
	    if (ptrNearestSphere)
		{
		float brightness = ptrNearestSphere->brightness(dz);
		float h = ptrNearestSphere->hue(t);
		ColorTools::HSB_TO_RVB(h, 1, brightness, ptrColor);
		}
	    else
		{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		}

	    ptrColor->w = 255; // opaque
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	//Input
	int nbSphere;
	Sphere* ptrDevTabSphere;
	Sphere* ptrDevCurrentSphere;
	Sphere* ptrNearestSphere;

    }
;

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
