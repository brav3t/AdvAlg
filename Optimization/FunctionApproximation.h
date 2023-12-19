#pragma once
#include <vector>

class ValuePair
{
public:
	ValuePair() = default;
	ValuePair(float input_, float output_)
		: input(input_)
		, output(output_)
	{
	}

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
