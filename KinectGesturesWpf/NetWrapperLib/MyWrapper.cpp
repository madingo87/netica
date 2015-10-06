#include <windows.h>

extern "C" 
{ 
	#include "HandPosition3D.h"
	//#include "angleSimple.h"
}


extern "C" __declspec(dllexport) int __stdcall HandPosition3D(float* input, float* output);
__declspec(dllexport) int __stdcall HandPosition3D(float* input, float* output)
{
	int res = classifyHandPosition(input, output, 0);
	return res;
}

//extern "C" __declspec(dllexport) int __stdcall AngleSimple(float* input, float* output);
//__declspec(dllexport) int __stdcall AngleSimple(float* input, float* output)
//{
//	  int res = classifyAngleSimple(input, output, 0);
//	  return res;
//}

