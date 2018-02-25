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
	    }

	__device__  virtual ~RayTracingMath()
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
	    float distance = 0;
	    float dz = 0;
	    bool isBlack = true;

	    //Loop in sphere array
	    for (int a = 0; a < nbSphere; a++)
		{
		ptrDevCurrentSphere = &ptrDevTabSphere[a];
		float hCarree = ptrDevCurrentSphere->hCarre(xySol);

		if (ptrDevCurrentSphere->isEnDessous(hCarree))
		    {
		    isBlack = false;
		    float dzCurrent = ptrDevCurrentSphere->dz(hCarree);
		    float distanceCurrent = ptrDevCurrentSphere->distance(dzCurrent);

		    if (distanceCurrent < distance || a == 0)
			{
			dz = dzCurrent;
			distance = distanceCurrent;
			ptrNearestSphere = ptrDevCurrentSphere;
			}
		    }
		}

	    //Color the pixel qith the color of the nearest sphere
	    colorPixel(t, dz, ptrColor, isBlack);
	    }

    private:
	__device__
	void colorPixel(float t, float dz, uchar4* ptrColor, bool isBlack)
	    {
	    if (!isBlack)
		{
		float brightness = ptrNearestSphere->brightness(dz);
		float h = ptrNearestSphere->getHueStart() + ptrNearestSphere->hue(t);
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
