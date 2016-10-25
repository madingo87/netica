// Dies ist die Haupt-DLL.

#include "stdafx.h"

#include "DataDouble.h"
#include "Forest.h"
#include "ForestClassification.h"
#include "ForestProbability.h"

extern "C" __declspec(dllexport) int predictRDF(const char* input, const char* forest_file);
int predictRDF(const char* input, const char* forest_file)
{
	Forest* forest = new ForestClassification;
	Data* data = new DataDouble();

	//nessicities for initCpp
	std::ostream* verbose_out = &std::cout;
	std::vector<std::string> catvars;
	std::vector<std::string> alwayssplitvars;


	bool error = data->loadFromStringWhitespace(input, "f1 f2 f3 f4 f5 f6 f7 f8 f9 f10 f11 f12 f13 f14 f15 f16 f17 f18 f19 f20 f21 f22 f23 f24 Class");

	forest->initCpp("Class", MEM_DOUBLE, data, 0, "ranger", 9, verbose_out, 0, 8, forest_file, DEFAULT_IMPORTANCE_MODE, DEFAULT_MIN_NODE_SIZE_CLASSIFICATION, "", alwayssplitvars, 
		"", true, catvars, false, DEFAULT_SPLITRULE, "", true, 1, DEFAULT_ALPHA, DEFAULT_MINPROP, false, DEFAULT_PREDICTIONTYPE);

	forest->predict();

	std::vector<double> first = forest->getPredictions()[0];
	return (int)first[0];
}

//double prediction(std::vector<std::vector<double>> predictions) {
//
//	std::vector<double> first = predictions[0];
//	double sec = first[0];
//	return sec; //predictions[0][0];
//
//	/*for (size_t i = 0; i < predictions.size(); ++i) {
//		for (size_t j = 0; j < predictions[i].size(); ++j) {
//			outfile << predictions[i][j] << " ";
//		}
//		outfile << std::endl;
//	}*/
//}
