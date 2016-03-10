#include <windows.h>

extern "C" 
{ 
#include "v2.h"
#include "position.h"
}

extern "C" __declspec(dllexport) int __stdcall position(float* input, float* output);
__declspec(dllexport) int __stdcall position(float* input, float* output)
{
	int res = classifyPosition(input, output, 0);
	return res;
}

extern "C" __declspec(dllexport) int __stdcall classify(float* input, float* output);
__declspec(dllexport) int __stdcall classify(float* input, float* output)
{
	int res = classify2(input, output, 0);
	return res;
}
