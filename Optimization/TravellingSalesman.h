#pragma once
#include <vector>

class Town
{
public:
	Town() = default;
	Town(float x, float y)
		: x(x)
		, y(y)
	{}

public:
	float x;
	float y;
};

class TravellingSalesmanProblem
{
protected:
	std::vector<Town> towns;
	float objective(std::vector<Town> solution);

public:
	void loadTownsFromFile(std::string fileName);
	void saveTownsToFile(std::string fileName, std::vector<Town> townVector);
};
