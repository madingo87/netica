// RDF.h

#pragma once

class RDF
{
	public:
		//__declspec(dllexport) __stdcall RDF(const char*  input, const char*  forest_file);
		static __declspec(dllexport) int __stdcall predictRDF(const char* input, const char* forest_file);
		static __declspec(dllexport) void __stdcall createForest(const char* input_file);
	private:
};
