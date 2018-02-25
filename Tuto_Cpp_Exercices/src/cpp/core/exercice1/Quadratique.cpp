#include "Quadratique.h"
#include <math.h>
#include "ABC.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructor		*|
 \*-------------------------------------*/

Quadratique::Quadratique(ABC abc)
    {
    this->abc = abc;
    results = new double[2];
    }

Quadratique::~Quadratique()
    {

    }

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int Quadratique::solve()
    {
    if (abc.a == 0)
	{
	results[0] = -abc.b / abc.a;
	return 1;
	}
    else
	{
	double discriminant = abc.b * abc.b - 4 * abc.a * abc.c;

	if (discriminant == 0)
	    {
	    results[0] = -abc.b / (2 * abc.a);
	    return 1;
	    }
	else
	    {
	    if (discriminant < 0)
		{
		return 0;
		}
	    else
		{
		results[0] = (-abc.b + sqrt(discriminant)) / 2 * abc.a;
		results[1] = (-abc.b - sqrt(discriminant)) / 2 * abc.a;
		return 2;
		}
	    }
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

