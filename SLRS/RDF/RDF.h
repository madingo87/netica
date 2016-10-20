// RDF.h

#pragma once

#include <vector>
#include <stdio.h>

class RDFWrapperLib
{
	public:
		static __declspec(dllexport) int predictRDF(const char*  input, const char*  forest_file);
	private:
		static double prediction(std::vector<std::vector<double>> predictions);

};
