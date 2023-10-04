#include "stdafx.h"

#include "HillClimbing.h"

void HillClimbingStochasticSBP::initAndSolve()
{
    // Problem and solution space limits. Point coordinate limits.
    Interval S = std::make_pair(.0f, 100.f);

    // Create points in problem space that needs to be bounded.
    fillWithRandomPoints(mPoints, S, mSPointCount);

    float epsilon = 10.f;

    // Distance function: create a new polygon from P polygon.
    // Each new point of the new polygon is in epsilon radius but limited to S interval aka solution space.
    auto distSFn = [](Polygon& aP, Interval& aS, float aEpsilon) -> Polygon {
        Polygon q;
        float min, max;
        std::tie(min, max) = aS;
        for (Point& point : aP)
        {
            float randX = randomUniform(-aEpsilon, aEpsilon);
            float randY = randomUniform(-aEpsilon, aEpsilon);
            randX = std::min(std::max(min, point.x + randX), max);
            randY = std::min(std::max(min, point.y + randY), max);
            q.emplace_back(randX, randY);
        }
        return q;
    };

    // Fitness function
    // If the new polygon is acceptable aka constraint is not negative.
    // Returns the length of boundary.
    auto fitnessFn = [this](Polygon& aSolution) -> float {
        float constr = constraint(aSolution);
        if (constr < 0)
            return std::numeric_limits<float>::max();
        float obj = objective(aSolution);
        return obj;
    };

    size_t stopCondition = 100; // iteration count

    // Solution first: the algorithm found an acceptable solution.
    // Solution second: the most acceptable solution polygon.
    auto solution = solveSBP(S, distSFn, epsilon, fitnessFn, stopCondition);
}

HillClimbingStochasticSBP::Solution HillClimbingStochasticSBP::solveSBP(
    Interval aS,
    DistSFn aDistS,
    float aEpsilon,
    FitnessFn aFitness,
    size_t aStopCond)
{
    Polygon p;
    fillWithRandomPoints(p, aS, mBoundingPolygonPointCount);
    // Not a random start, start from the problem space corners:
    // This is a worst case but working solution.
    //p.emplace_back(0.f, 0.f);
    //p.emplace_back(0.f, 100.f);
    //p.emplace_back(100.f, 100.f);
    //p.emplace_back(100.f, 0.f);

    for (size_t i = 0; i != aStopCond; ++i)
    {
        Polygon q = aDistS(p, aS, aEpsilon);
        float fitQ = aFitness(q);
        float fitP = aFitness(p);
        if (fitQ < fitP)
            p = q;
    }
    bool isSolutionAcceptable = !(constraint(p) < 0);
    auto solution = std::make_pair(isSolutionAcceptable, p);
    return solution;
}

void HillClimbingStochasticSBP::fillWithRandomPoints(Polygon& aPolygon, Interval& aInterval, size_t aPointCount)
{
    aPolygon.reserve(aPointCount);
    float min, max;
    std::tie(min, max) = aInterval;
    for (size_t i = 0; i != aPointCount; ++i)
    {
        aPolygon.emplace_back(randomUniform(min, max), randomUniform(min, max));
    }
}
