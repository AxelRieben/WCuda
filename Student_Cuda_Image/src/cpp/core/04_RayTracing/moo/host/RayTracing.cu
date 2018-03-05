#include <iostream>
#include <assert.h>

#include "Device.h"
#include "RayTracing.h"
#include "length_cm.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void rayTracing(uchar4* ptrDevPixels,Sphere* ptrDevTabSphere,int nbSphere,uint w, uint h,float t);
extern void uploadToCM(Sphere* ptrTabSphere);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__host__ void fillCM(Sphere* ptrTabSphere);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

RayTracing::RayTracing(const Grid& grid, uint w, uint h, float dt) :
	Animable_I<uchar4>(grid, w, h, "RayTracing_Cuda_RGBA_uchar4")
    {
    // Inputs
    this->dt = dt;

    // Tools
    this->t = 0; // protected dans Animable

    // Fabrication coté host des données
    SphereCreator* creator = new SphereCreator(LENGTH_CM, w, h);
    Sphere* ptrTabSphere = creator->getTabSphere();

    this->nbSphere = 40;
    //SphereCreator* creator = new SphereCreator(nbSphere, w, h);
    //Sphere* ptrTabSphere = creator->getTabSphere();
    //this->sizeOctetSphere = nbSphere * sizeof(Sphere);
    //Device::malloc(&ptrDevTabSphere, sizeOctetSphere);
    //Device::memcpyHToD(ptrDevTabSphere, ptrTabSphere, sizeOctetSphere);

    fillCM(ptrTabSphere);

    }

RayTracing::~RayTracing()
    {
    Device::free(ptrDevTabSphere);
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

__host__ void fillCM(Sphere* ptrTabSphere)
    {
// Appelle le service d'upload coté device
    uploadToCM(ptrTabSphere);
    }

/**
 * Override
 * Call periodicly by the API
 *
 * Note : domaineMath pas use car pas zoomable
 */
void RayTracing::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    Device::lastCudaError("RayTracing rgba uchar4 (before)"); // facultatif, for debug only, remove for release

    rayTracing<<<dg,db>>>(ptrDevPixels,ptrDevTabSphere,nbSphere,w,h,t);

    Device::lastCudaError("RayTracing rgba uchar4 (after)"); // facultatif, for debug only, remove for release
    }

/**
 * Override
 * Call periodicly by the API
 */
void RayTracing::animationStep()
    {
    t += dt;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

