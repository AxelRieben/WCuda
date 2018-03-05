#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"
#include "RayTracingMath.h"

#include "IndiceTools_GPU.h"
#include "length_cm.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

// Déclaration Constante globale
__constant__ Sphere TAB_CM[LENGTH_CM];

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void rayTracing(uchar4* ptrDevPixels, Sphere* ptrDevTabSphere, int nbSphere, uint w, uint h, float t);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ void work(uchar4* ptrDevPixels, Sphere* ptrDevTabSphere, int nbSphere, uint w, uint h, float t);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__host__ void uploadToCM(Sphere* ptrTabSphere)
    {
    size_t size = LENGTH_CM * sizeof(Sphere);
    int offset = 0;
    HANDLE_ERROR(cudaMemcpyToSymbol(TAB_CM, ptrTabSphere, size, offset, cudaMemcpyHostToDevice));
    //Device::memcpyToCM(TAB_CM, ptrTabSphere, size);
    }

__global__ void rayTracing(uchar4* ptrDevPixels, Sphere* ptrDevTabSphere, int nbSphere, uint w, uint h, float t)
    {
    work(ptrDevPixels, TAB_CM, LENGTH_CM, w, h, t);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ void work(uchar4* ptrDevPixels, Sphere* ptrDevTabSphere, int nbSphere, uint w, uint h, float t)
    {
    RayTracingMath rayTracingMath = RayTracingMath(w, h, ptrDevTabSphere, nbSphere);

    const int WH = w * h;
    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();

    int i;	// in [0,h[
    int j; 	// in [0,w[

    int s = TID;  // in [0,...
    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &i, &j); 	// update (i, j)
	rayTracingMath.colorIJ(&ptrDevPixels[s], i, j, t); 	// update ptrDevPixels[s]
	s += NB_THREAD;
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

