#pragma once

#include "ShapeDrawer_I.h"

#include <opencv2/opencv.hpp>
#include <highgui.hpp>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class ShapeDrawer: public ShapeDrawer_I
    {
	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

    public:

	ShapeDrawer(cv::Mat overlay);

	virtual ~ShapeDrawer();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	// Override
	virtual void draw(ShapeGroup* ptrShapeGroup);


	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    protected:

	// Inputs
	cv::Mat overlay;

    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
