#pragma once
#include <vector>

class ValuePair
{
public:
	float input;
	float output;
};

class FunctionApproximation
{
protected:
	std::vector<ValuePair> known_values;

	float objective(std::vector<float> coefficients);
public:
	void loadKnownValuesFromFile(std::string fileName);
};
