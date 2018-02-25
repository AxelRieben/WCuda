#pragma once

#include <math.h>
#include "MathTools.h"

#include "Calibreur_GPU.h"
#include "ColorTools_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelBrotMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ MandelBrotMath(int n) :
		calibreur(Interval<float>(0, n), Interval<float>(0, 1))
	    {
		this->n = n;
	    }

	// constructeur copie automatique car pas pointeur dans VagueMath

	__device__
	           virtual ~MandelBrotMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorXY(uchar4* ptrColor, int x, int y, float n)
	    {
	    float z = f(x, y, n);

	    if (z == n)
		{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		}
	    else
		{
		float hue01 = z;
		calibreur.calibrer(&hue01);
		ColorTools::HSB_TO_RVB(hue01, ptrColor); // update color
		}

	    ptrColor->w = 255; // opaque
	    }

    private:

	__device__
	int f(float x, float y, float n)
	    {

	    float a = 0;
	    float b = 0;

	    int i = 0;

	    while (!isDivergent(a, b) && i < n)
		{
		float aCopy = a;
		a = (a * a - b * b) + x;
		b = 2 * aCopy * b + y;

		i++;
		}

	    return i;
	    }

	__device__
	bool isDivergent(float a, float b)
	    {
	    //Musée des horreurs
	    return (a * a + b * b > 4);
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Input
	int n;

	// Tools
	Calibreur<float> calibreur;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
