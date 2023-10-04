#pragma once

const float PI = 3.14159265358979f;

class Point
{
public:
	Point() : x(0.f), y(0.f) {}
	Point(float aX, float aY) : x(aX), y(aY) {}

public:
	float x;
	float y;
};

class SmallestBoundaryPolygonProblem
{
public:
	void loadPointsFromFile(std::string fileName);
	void savePointsToFile(std::string fileName, std::vector<Point> pointVector);

protected:
	std::vector<Point> mPoints;

	float distanceFromLine(Point& lp1, Point& lp2, Point& p);
	float outerDistanceToBoundary(std::vector<Point>& solution);
	float lengthOfBoundary(std::vector<Point>& solution);

	float objective(std::vector<Point>& solution);
	float constraint(std::vector<Point>& solution);
};
