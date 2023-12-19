#include "stdafx.h"

#include "ParticleSwarmOptimalization.h"

using Population = FunctionApproxWithParticleSwarmOpt::Population;

void FunctionApproxWithParticleSwarmOpt::initAndSolve()
{
	std::cout << "Solving the Function Approximation problem with Particle Swarm Optimalization method..\n";
	known_values = { // data points
		{ 1.f, 50.f }, // 1 hour of learning gets 50 points on the exam.
		{ 2.f, 60.f },
		{ 3.f, 65.f },
		{ 4.f, 70.f },
		{ 5.f, 75.f },
	};
	constexpr SolutionSpace S = { 0.f, 20.f };
	constexpr size_t POPULATION_SIZE = 10000;
	constexpr float ACCEPTABLE_ERROR = 10.f;

	// Particle Swarm Optimalization
	Population P = initializePopulation(S, POPULATION_SIZE);
	Individual& gOpt = P.front();
	evaluation(P, gOpt);

	size_t tryCountIdx = 0;
	constexpr size_t MAX_TRY = 1000;
	auto stopCondition = [&]() {
		const float gOptFitness = objective(gOpt.position);
		if (gOptFitness <= ACCEPTABLE_ERROR) // We found an acceptable solution.
			return true;
		
		return (tryCountIdx++ == MAX_TRY);
	};
	while (!stopCondition())
	{
		calculateVelocity(P, gOpt);
		for (Individual& p : P)
		{
			for (size_t i = 0; i != p.position.size(); ++i)
				p.position[i] += p.velocity[i];
		}
		evaluation(P, gOpt);
	}
	// write out solution
	printSolution(gOpt.position);
}

Population FunctionApproxWithParticleSwarmOpt::initializePopulation(const SolutionSpace& S, size_t populationSize)
{
	Population population;
	const size_t COEFFICIENT_COUNT = 5;
	for (size_t i = 0; i != populationSize; ++i)
		population.emplace_back(S, COEFFICIENT_COUNT);

	return population;
}

void FunctionApproxWithParticleSwarmOpt::evaluation(Population& P, Individual& gOpt)
{
	for (Individual& p : P)
	{
		const float currFitness = objective(p.position);
		const float pOptFitness = objective(p.pOpt); // local optimum fitness
		if (currFitness < pOptFitness)
			p.pOpt = p.position;

		const float gOptFitness = objective(gOpt.position); // global optimum fitness
		if (currFitness < gOptFitness)
			gOpt = p;
	}
}

void FunctionApproxWithParticleSwarmOpt::calculateVelocity(Population& P, Individual& gOpt)
{
	constexpr float w = 0.1f;
	constexpr float wLocal = 0.3f;
	constexpr float wGlobal = 0.5f;

	for (Individual& p : P)
	{
		for (size_t i = 0; i != p.position.size(); ++i)
		{
			float rndLocal = randomUniform(.0f, 1.f);
			float rndGlobal = randomUniform(.0f, 1.f);
			p.velocity[i] =
				(p.velocity[i] * w) +
				((p.pOpt[i] - p.position[i]) * wLocal * rndLocal) +
				((gOpt.position[i] - p.position[i]) * wGlobal * rndGlobal);
		}
	}
}

float FunctionApproxWithParticleSwarmOpt::calculatePoint(float dataPoint, std::vector<float> solution)
{
	return
		solution[0] * pow(dataPoint - solution[1], 3.f) +
		solution[2] * pow(dataPoint - solution[3], 2.f) +
		solution[4] * dataPoint;
}

void FunctionApproxWithParticleSwarmOpt::printSolution(std::vector<float> solution)
{
	std::cout << "The found approximation:\n";
	for (auto& dataPoint : known_values)
	{
		float output = calculatePoint(dataPoint.input, solution);
		float diff = std::abs(dataPoint.output - output);
		float percent = std::abs((1.f - output / dataPoint.output) * 100.f);
		std::cout << dataPoint.input << "\t" << dataPoint.output << "\t" << output << "\t\tdiff = " << diff << "\t\tpercent = " << percent << "\n";
	}
}
