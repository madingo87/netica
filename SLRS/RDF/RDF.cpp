// Dies ist die Haupt-DLL.

#include "stdafx.h"

//#include "RDF.h"

#include "DataDouble.h"
#include "Forest.h"
#include "ForestClassification.h"

int num_trees = 7;

extern "C" __declspec(dllexport) Forest* __stdcall initRDF(const char* forest_file);
Forest* __stdcall initRDF(const char* forest_file)
{
	//nessicities for initCpp
	std::ostream* verbose_out = &std::cout;
	std::vector<std::string> catvars;
	std::vector<std::string> alwayssplitvars;

	Data* data = new DataDouble();
	Forest* f = new ForestClassification;

	//give dummy data
	bool error = data->loadFromStringWhitespace(
		"0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0", 
		"f1 f2 f3 f4 f5 f6 f7 f8 f9 f10 f11 f12 f13 f14 f15 f16 f17 f18 f19 f20 f21 f22 f23 f24 Class");

	f->initCpp("Class", MEM_DOUBLE, data, 0, "ranger", num_trees, verbose_out, 0, 8, forest_file, DEFAULT_IMPORTANCE_MODE, DEFAULT_MIN_NODE_SIZE_CLASSIFICATION, "", alwayssplitvars,
		"", true, catvars, false, DEFAULT_SPLITRULE, "", false, 1, DEFAULT_ALPHA, DEFAULT_MINPROP, false, DEFAULT_PREDICTIONTYPE);

	return f;
}

extern "C" __declspec(dllexport) void __stdcall predictFileRDF(const char* input_file, const char* forest_file);
void __stdcall predictFileRDF(const char* input_file, const char* forest_file)
{
	//nessicities for initCpp
	std::ostream* verbose_out = &std::cout;
	std::vector<std::string> catvars;
	std::vector<std::string> alwayssplitvars;

	Data* data = new DataDouble();
	Forest* f = new ForestClassification;

	f->initCpp("Class", MEM_DOUBLE, input_file, 0, "ranger", num_trees, verbose_out, 0, 8, forest_file, DEFAULT_IMPORTANCE_MODE, DEFAULT_MIN_NODE_SIZE_CLASSIFICATION, "", alwayssplitvars,
		"", true, catvars, false, DEFAULT_SPLITRULE, "", false, 1, DEFAULT_ALPHA, DEFAULT_MINPROP, false, DEFAULT_PREDICTIONTYPE);

	f->run(false);

	f->writeOutput();
}

extern "C" __declspec(dllexport) int __stdcall predictRDF(const char* input, Forest* forest);
int __stdcall predictRDF(const char* input, Forest* forest)
{
	Data* d = new DataDouble();
	bool error = d->loadFromStringWhitespace(input, "f1 f2 f3 f4 f5 f6 f7 f8 f9 f10 f11 f12 f13 f14 f15 f16 f17 f18 f19 f20 f21 f22 f23 f24 Class");

	forest->data = d;
	forest->run(false);

	std::vector<std::vector<double>> predictions = forest->getPredictions();
	return predictions[0][0];
}

extern "C" __declspec(dllexport) void __stdcall createForest(const char* input_file);
void __stdcall createForest(const char* input_file)
{
	Forest* forest = new ForestClassification;
	Data* data = new DataDouble();

	//nessicities for initCpp
	std::ostream* verbose_out = &std::cout;
	std::vector<std::string> catvars;
	std::vector<std::string> alwayssplitvars;

	forest->initCpp("Class", MEM_DOUBLE, input_file, 0, "ranger", num_trees, verbose_out, 0, 8, "", DEFAULT_IMPORTANCE_MODE, DEFAULT_MIN_NODE_SIZE_CLASSIFICATION, "", alwayssplitvars,
		"", true, catvars, false, DEFAULT_SPLITRULE, "", true, 1, DEFAULT_ALPHA, DEFAULT_MINPROP, false, DEFAULT_PREDICTIONTYPE);

	forest->run(false);

	forest->saveToFile();

	forest->writeOutput();
	*verbose_out << "Finished Ranger." << std::endl;
}