#include "stdafx.h"
#include "SmallestBoundaryPolygon.h"
#include <fstream>
#include <math.h>

using namespace std;

//
// Basic IO
//
void SmallestBoundaryPolygonProblem::loadPointsFromFile(string fileName) {
	ifstream fpoints(fileName);
	while (!fpoints.eof()) {
		Point pnt;
		fpoints >> pnt.x;
		fpoints >> pnt.y;
		mPoints.push_back(pnt);
	};
	fpoints.close();
}

void SmallestBoundaryPolygonProblem::savePointsToFile(string fileName, vector<Point> pointVector) {
	ofstream fpoints(fileName);
	for (Point pnt : pointVector) {
		fpoints << pnt.x << "\t" << pnt.y << endl;
	};
	fpoints.close();
}

//
// Helper functions
//
float SmallestBoundaryPolygonProblem::distanceFromLine(Point& lp1, Point& lp2, Point& p) {
	// https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
	return ((lp2.y - lp1.y)*p.x - (lp2.x - lp1.x)*p.y + lp2.x*lp1.y - lp2.y*lp1.x) / sqrt(pow(lp2.y - lp1.y, 2.f) + pow(lp2.x - lp1.x, 2.f));
}


float SmallestBoundaryPolygonProblem::outerDistanceToBoundary(vector<Point>& solution) {
	float sum_min_distances = 0;

	for (unsigned int pi = 0; pi < mPoints.size(); pi++) {
		float min_dist = std::numeric_limits<float>::max();
		for (unsigned int li = 0; li < solution.size(); li++) {
			float act_dist = distanceFromLine(solution[li], solution[(li + 1) % solution.size()], mPoints[pi]);
			if (li == 0 || act_dist < min_dist)
				min_dist = act_dist;
		}
		if (min_dist < 0.f)
			sum_min_distances += -min_dist;
	}
	return sum_min_distances;
}

float SmallestBoundaryPolygonProblem::lengthOfBoundary(vector<Point>& solution) {
	float sum_length = 0;

	for (unsigned int li = 0; li < solution.size() - 1; li++) {
		Point p1 = solution[li];
		Point p2 = solution[(li + 1) % solution.size()];
		sum_length += sqrt(pow(p1.x - p2.x, 2.f) + pow(p1.y - p2.y, 2.f));
	}
	return sum_length;
}

//
// Objective functions
//
float SmallestBoundaryPolygonProblem::objective(std::vector<Point>& solution)
{
	return lengthOfBoundary(solution);
}

float SmallestBoundaryPolygonProblem::constraint(std::vector<Point>& solution)
{
	return -outerDistanceToBoundary(solution);
}

