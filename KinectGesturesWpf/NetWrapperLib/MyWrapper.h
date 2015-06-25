

//#ifdef MYWRAPPER_EXPORTS
//#define MYWRAPPER_API __declspec(dllexport) 
//#else
//#define MYWRAPPER_API __declspec(dllimport) 
//#endif

namespace NetWrapperLib
{

	extern "C" __declspec(dllexport) int FirstNet(float* input, float* output);
	
}