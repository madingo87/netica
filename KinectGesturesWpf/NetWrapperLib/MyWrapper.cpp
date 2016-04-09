#include <windows.h>

extern "C" 
{ 
#include "dist.h"
#include "orient.h"
}

extern "C" __declspec(dllexport) int __stdcall classifyDist(float* input, float* output);
__declspec(dllexport) int __stdcall classifyDist(float* input, float* output)
{
	int res = classifyDistance(input, output, 0);
	return res;
}

extern "C" __declspec(dllexport) int __stdcall classifyOrien(float* input, float* output);
__declspec(dllexport) int __stdcall classifyOrien(float* input, float* output)
{
	int res = classifyOrientation(input, output, 0);
	return res;
}
