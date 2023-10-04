#pragma once

class HillClimbingStochasticSBP : public SmallestBoundaryPolygonProblem
{
	using Polygon = std::vector<Point>;
	using Interval = std::pair<float, float>;
	using DistSFn = std::function<Polygon(Polygon&, Interval&, float)>;
	using FitnessFn = std::function<float(Polygon&)>;
	using Solution = std::pair<bool, Polygon>;

public:
	void initAndSolve();

private:
	Solution solveSBP(
		Interval aS,
		DistSFn,
		float aEpsilon,
		FitnessFn,
		size_t aStopCond);
	void fillWithRandomPoints(Polygon&, Interval&, size_t aPointCount);

private:
	size_t mSPointCount = 10;
	size_t mBoundingPolygonPointCount = 4;
};
