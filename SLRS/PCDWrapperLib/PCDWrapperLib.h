// PCDWrapperLib.h

#pragma once

class PCDWrapperLib
{
	public:
		static __declspec(dllexport) int evaluatePCD(const char* filename, bool print, const char* exportFile, int offset, bool plot);
};