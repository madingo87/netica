// Dies ist die Haupt-DLL.
#include <windows.h>

extern "C"
{
	#include "segmentationNet.h"
}

extern "C" __declspec(dllexport) int __stdcall classifyPx(float* input, float* output);
int __stdcall classifyPx(float* input, float* output)
{
	int res = classifyPixel(input, output, 0);
	return res;
}