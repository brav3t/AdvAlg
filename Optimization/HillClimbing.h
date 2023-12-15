#pragma once

class SmallestBoundaryPolyWithHillClimbing : public SmallestBoundaryPolygonProblem
{
public:
	using Polygon = std::vector<Point>;
	using ProblemSpaceSize = std::pair<float, float>;
	using DistSFn = std::function<Polygon(Polygon&, ProblemSpaceSize&, float)>;
	using FitnessFn = std::function<float(Polygon&)>;
	using Solution = std::pair<bool, Polygon>;

public:
	void initAndSolve();

private:
	Solution solveSBP(ProblemSpaceSize aS, DistSFn, float aEpsilon, FitnessFn, size_t aStopCond);
	void fillWithRandomPoints(Polygon&, ProblemSpaceSize&, size_t aPointCount);
	void printSolution(Solution&);

private:
	size_t mSPointCount = 10;
	size_t mBoundingPolygonPointCount = 4;
};
