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

__global__ void rayTracingSM(uchar4* ptrDevPixels, Sphere* ptrDevTabSphere, int nbSphere, uint w, uint h, float t);

__global__ void rayTracingCM(uchar4* ptrDevPixels, Sphere* ptrDevTabSphere, int nbSphere, uint w, uint h, float t);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ void work(uchar4* ptrDevPixels, Sphere* ptrDevTabSphere, int nbSphere, uint w, uint h, float t);

__device__ void copyGMtoSM(Sphere* tabSM, Sphere* tabGM, int n);

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
    //Device::memcpyToCM(TAB_CM, ptrTabSphere, size); //Not working
    }

__global__ void rayTracingSM(uchar4* ptrDevPixels, Sphere* ptrDevTabSphere, int nbSphere, uint w, uint h, float t)
    {
    //Shared Memory
    __shared__ extern Sphere tabSM[];
    copyGMtoSM(tabSM, ptrDevTabSphere, nbSphere);
    __syncthreads();
    work(ptrDevPixels, tabSM, LENGTH_CM, w, h, t);
    }

__global__ void rayTracingCM(uchar4* ptrDevPixels, Sphere* ptrDevTabSphere, int nbSphere, uint w, uint h, float t)
    {
    //Constant memory
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

__device__ void copyGMtoSM(Sphere* tabSM, Sphere* tabGM, int n)
    {
    const int NB_THREAD_LOCAL = Indice2D::nbThreadLocal();
    const int TID_LOCAL = Indice2D::tidLocal();
    int s = TID_LOCAL;

    while(s < n)
	{
	tabSM[s] = tabGM[s];
	s += NB_THREAD_LOCAL;
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

