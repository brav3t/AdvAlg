#pragma once

class FunctionApproxWithParticleSwarmOpt: public FunctionApproximation
{
public:
	using SolutionSpace = std::pair<float, float>;
	class Individual
	{
	public:
		Individual(const SolutionSpace& S, size_t dimension)
		{
			for (size_t i = 0; i != dimension; ++i)
				position.emplace_back(randomUniform(S.first, S.second));

			for (size_t i = 0; i != dimension; ++i)
				velocity.emplace_back(randomUniform(S.first, S.second / 10.f));

			pOpt = position;
		}

	public:
		std::vector<float> position;
		std::vector<float> velocity;
		std::vector<float> pOpt; // local optimum
	};
	using Population = std::vector<Individual>;

public:
	void initAndSolve();

private:
	Population initializePopulation(const SolutionSpace&, size_t populationSize);
	void evaluation(Population&, Individual& gOpt);
	void calculateVelocity(Population&, Individual& gOpt);
	float calculatePoint(float dataPoint, std::vector<float> solution);
	void printSolution(std::vector<float> solution);
};
