#include "stdafx.h"
#include "WorkAssignment.h"
#include <fstream>

using namespace std;

//
// Basic IO
//
void WorkAssignmentProblem::loadFromFile(std::string fileName)
{
	ifstream fpersons(fileName);
	fpersons >> requested_time;
	while (!fpersons.eof()) {
		Person person;
		fpersons >> person.salary;
		fpersons >> person.quality;
		persons.push_back(person);
	};
	fpersons.close();
}

//
// Objective functions
//
float WorkAssignmentProblem::sumSalary(std::vector<int> solution)
{
	float sum = 0;
	for (unsigned int i = 0; i < solution.size(); i++)
		sum += solution[i] * persons[i].salary;
	return sum;
}

float WorkAssignmentProblem::avgQuality(std::vector<int> solution)
{
	float sum = 0;
	for (unsigned int i = 0; i < solution.size(); i++)
		sum += solution[i] * persons[i].quality;
	return sum / requested_time;
}