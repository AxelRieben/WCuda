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

extern __global__ void rayTracingGM(uchar4* ptrDevPixels, Sphere* ptrDevTabSphere, int nbSphere, uint w, uint h, float t);
extern __global__ void rayTracingSM(uchar4* ptrDevPixels,Sphere* ptrDevTabSphere,int nbSphere,uint w, uint h,float t);
extern __global__ void rayTracingCM(uchar4* ptrDevPixels,Sphere* ptrDevTabSphere,int nbSphere,uint w, uint h,float t);

extern void uploadToCM(Sphere* ptrTabSphere);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

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

    this->nbSphere = LENGTH_CM;

    // Fabrication coté host des données
    SphereCreator* creator = new SphereCreator(nbSphere, w, h);
    Sphere* ptrTabSphere = creator->getTabSphere();
    this->ptrDevTabSphere = 0;

    //Global Memory
    fillGM(ptrTabSphere);

    //Constant Memory
    //fillCM(ptrTabSphere);
    }

RayTracing::~RayTracing()
    {
    Device::free(ptrDevTabSphere);
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

__host__ void RayTracing::fillCM(Sphere* ptrTabSphere)
    {
// Appelle le service d'upload coté device
    uploadToCM(ptrTabSphere);
    }

__host__ void RayTracing::fillGM(Sphere* ptrTabSphere)
    {
    this->sizeOctetSphere = this->nbSphere * sizeof(Sphere);
    Device::malloc(&ptrDevTabSphere, sizeOctetSphere);
    Device::memcpyHToD(ptrDevTabSphere, ptrTabSphere, sizeOctetSphere);
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

    //Global Memory
    rayTracingGM<<<dg,db>>>(ptrDevPixels,ptrDevTabSphere,nbSphere,w,h,t);

    //Constant Memory
    //rayTracingCM<<<dg,db>>>(ptrDevPixels,ptrDevTabSphere,nbSphere,w,h,t);

    //Shared Memory
    //size_t sizeOctetSM = nbSphere * sizeof(Sphere);
    //rayTracingSM<<<dg,db, sizeOctetSM>>>(ptrDevPixels,ptrDevTabSphere,nbSphere,w,h,t);

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

