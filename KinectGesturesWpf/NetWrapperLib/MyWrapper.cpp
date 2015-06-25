#include <windows.h>

extern "C" { 
	#include "MyFirstNet.h" 
}



extern "C" __declspec(dllexport) int __stdcall FirstNet(float* input, float* output);


__declspec(dllexport) int __stdcall FirstNet(float* input, float* output)
{			
	int res = classifyHandPos(input, output, 0);
	return res;
}
