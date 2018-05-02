#include <iostream>

#include "SceneCubeCreator.h"

#include "RipplingProvider.h"
#include "MandelBrotProvider.h"
#include "MandelBrotProvider2.h"
#include "MandelBrotProvider3.h"
#include "MandelBrotProvider4.h"
#include "RayTracingProvider.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructor		*|
 \*-------------------------------------*/

SceneCubeCreator::SceneCubeCreator()
    {
    createImages();
    createScene();
    }

SceneCubeCreator::~SceneCubeCreator()
    {
    delete ptrImage1;
    delete ptrImage2;
    delete ptrImage3;
    delete ptrImage4;
    delete ptrImage5;
    delete ptrImage6;

    delete ptrScene;
    }

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

SceneCube* SceneCubeCreator::getScene()
    {
    return ptrScene;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void SceneCubeCreator::createImages()
    {
    ptrImage1 = RipplingProvider().createImageGL();
    ptrImage2 = MandelBrotProvider().createImageGL();

    ptrImage3 = RayTracingProvider().createImageGL();
    ptrImage4 = MandelBrotProvider2().createImageGL();
    ptrImage5 = MandelBrotProvider3().createImageGL();
    ptrImage6 = MandelBrotProvider4().createImageGL();
    }

void SceneCubeCreator::createScene()
    {
    ptrScene = new SceneCube(ptrImage1, ptrImage2, ptrImage3, ptrImage4, ptrImage5, ptrImage6);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

