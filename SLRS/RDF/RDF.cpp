// Dies ist die Haupt-DLL.

#include "stdafx.h"

#include "RDF.h"

#include "DataDouble.h"
#include "Forest.h"
#include "ForestClassification.h"

extern "C" __declspec(dllexport) int predictRDF(const char* input, const char* forest_file);
int RDFWrapperLib::predictRDF(const char* input, const char* forest_file)
{
	ForestClassification* forest = new ForestClassification();
	DataDouble* data = new DataDouble();

	std::string header_line = "f1 f2 Class";
	data->loadFromStringWhitespace(input,header_line);

	forest->loadFromFile(forest_file);
	forest->predict();

	int out = prediction(forest->getPredictions());

	return out;
}

double RDFWrapperLib::prediction(std::vector<std::vector<double>> predictions) {

	std::vector<double> first = predictions[0];
	double sec = first[0];
	return sec; //predictions[0][0];

	/*for (size_t i = 0; i < predictions.size(); ++i) {
		for (size_t j = 0; j < predictions[i].size(); ++j) {
			outfile << predictions[i][j] << " ";
		}
		outfile << std::endl;
	}*/
}
