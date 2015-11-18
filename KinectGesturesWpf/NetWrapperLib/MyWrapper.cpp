#include <windows.h>

extern "C" 
{ 
#include "v51.h"
#include "position.h"
}

extern "C" __declspec(dllexport) int __stdcall position(float* input, float* output);
__declspec(dllexport) int __stdcall position(float* input, float* output)
{
	int res = classifyPosition(input, output, 0);
	return res;
}

extern "C" __declspec(dllexport) int __stdcall v51(float* input, float* output);
__declspec(dllexport) int __stdcall v51(float* input, float* output)
{
	int res = classify51(input, output, 0);
	return res;
}
