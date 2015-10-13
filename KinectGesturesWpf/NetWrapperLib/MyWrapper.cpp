#include <windows.h>

extern "C" 
{ 
	#include "HandPosition3D.h"
	#include "AngleAdvanced.h"
	#include "AA2.h"
	#include "SimpleGestures.h"
}


extern "C" __declspec(dllexport) int __stdcall HandPosition3D(float* input, float* output);
__declspec(dllexport) int __stdcall HandPosition3D(float* input, float* output)
{
	int res = classifyHandPosition(input, output, 0);
	return res;
}

extern "C" __declspec(dllexport) int __stdcall AngleAdvanced(float* input, float* output);
__declspec(dllexport) int __stdcall AngleAdvanced(float* input, float* output)
{
	  int res = classifyAngleAdvanced(input, output, 0);
	  return res;
}

extern "C" __declspec(dllexport) int __stdcall AngleAdvanced2(float* input, float* output);
__declspec(dllexport) int __stdcall AngleAdvanced2(float* input, float* output)
{
	int res = classifyAngleAdvanced2(input, output, 0);
	return res;
}

extern "C" __declspec(dllexport) int __stdcall SimpleGestures(float* input, float* output);
__declspec(dllexport) int __stdcall SimpleGestures(float* input, float* output)
{
	int res = classifySimpleGestures(input, output, 0);
	return res;
}
