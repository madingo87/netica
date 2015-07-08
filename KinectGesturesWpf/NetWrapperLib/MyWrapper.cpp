#include <windows.h>

extern "C" 
{ 
	#include "MyFirstNet.h" 
	#include "HandPosition3D.h"
}



extern "C" __declspec(dllexport) int __stdcall FirstNet(float* input, float* output);
extern "C" __declspec(dllexport) int __stdcall HandPosition3D(float* input, float* output);


__declspec(dllexport) int __stdcall FirstNet(float* input, float* output)
{			
	int res = classifyFirstNet(input, output, 0);
	return res;
}

__declspec(dllexport) int __stdcall HandPosition3D(float* input, float* output)
{
	int res = classifyHandPosition(input, output, 0);
	return res;
}
