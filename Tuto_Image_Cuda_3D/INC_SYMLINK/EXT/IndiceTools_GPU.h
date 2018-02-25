#pragma once

#include "both_define.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace gpu
    {
    class IndiceTools
	{

	    /*--------------------------------------*\
	    |*		Constructor		    *|
	     \*--------------------------------------*/

	public:

	    /*--------------------------------------*\
	    |*		Methodes		    *|
	     \*--------------------------------------*/

	public:

	    /**
	     * s[0,W*H[ --> i[0,H[ j[0,W[
	     * w = largeur
	     * h = hauteur
	     */
	    __BOTH__
	    static  void toIJ( int s, int w, int* ptrI, int* ptrJ)
		{
		*ptrI = s / w;
		*ptrJ = s - w * (*ptrI);
		}

	    /**
	     * i[0,H[ j[0,W[ --> s[0,W*H[
	     * w = largeur
	     * h = hauteur
	     */
	    __BOTH__
	    static  int toS(int w, int i, int j)
		{
		return (i * w) + j;
		}

	    /*-------------------------------------*\
	     |*		Attributs		    *|
	     \*-------------------------------------*/

	private:

	};
    }



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
