#pragma once

#include <math.h>
#include "MathTools.h"

#include "Calibreur_CPU.h"
#include "ColorTools_CPU.h"
using namespace cpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	MandelbrotMath(uint n) :
		calibreur(Interval<float>(0, n), Interval<float>(0, 1))
	    {
	    //this->n = n;
	    }

	// constructeur copie automatique car pas pointeur dans
	//	MandelbrotMath
	// 	calibreur
	// 	IntervalF

	virtual ~MandelbrotMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	void colorXY(uchar4* ptrColor, float x, float y, float n)
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

	int f(float x, float y, float n)
	    {

	    float a = 0;
	    float b = 0;

	    int i = 0;

	    while(!isDivergent(a, b) && i < n)
		{
		float aCopy = a;
		a = (a*a - b*b) + x;
		b = 2 * aCopy*b + y;

		i++;
		}

	    return i;
	    }

	bool isDivergent(float a, float b)
	    {
		//Musée des horreurs
		return (a*a + b*b > 4);
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Input
	//uint n;

	// Tools
	Calibreur<float> calibreur;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
