#pragma once
#include <vector>

class Person
{
public:
	float salary;
	float quality;
};

class WorkAssignmentProblem
{
protected:
	std::vector<Person> persons;
	int requested_time;

	float sumSalary(std::vector<int> solution);
	float avgQuality(std::vector<int> solution);

public:
	virtual void loadFromFile(std::string fileName);
};