#include "stdafx.h"
#include "FunctionApproximation.h"
#include <fstream>

using namespace std;

//
// Basic IO
//
void FunctionApproximation::loadKnownValuesFromFile(string fileName) {
	ifstream fvalues(fileName);
	while (!fvalues.eof()) {
		ValuePair valuepair;
		fvalues >> valuepair.input;
		fvalues >> valuepair.output;
		known_values.push_back(valuepair);
	};
	fvalues.close();
}

//
// Objective functions
//
float FunctionApproximation::objective(std::vector<float> coefficients) {
	float sum_diff = 0;
	for (auto valuepair : known_values) {
		float x = valuepair.input;
		float y = coefficients[0] * pow(x - coefficients[1], 3.f) +
   			      coefficients[2] * pow(x - coefficients[3], 2.f) +
			      coefficients[4] * x;
		float diff = (float)pow(y - valuepair.output, 2.f);
		sum_diff += diff;
	}
	return sum_diff;
}
