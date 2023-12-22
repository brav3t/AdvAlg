#include "stdafx.h"

#include "Genetic.h"

using Route = TravellingSalesmanWithGenetic::Route;
using FitnessVal = TravellingSalesmanWithGenetic::FitnessVal;
using Individual = TravellingSalesmanWithGenetic::Individual;
using Population = TravellingSalesmanWithGenetic::Population;

void TravellingSalesmanWithGenetic::createTowns(size_t numOfTowns)
{
	for (size_t i = 0; i != numOfTowns; ++i)
		towns.emplace_back(randomUniform(0.f, 100.f), randomUniform(0.f, 100.f));
}

Population TravellingSalesmanWithGenetic::initializePopulation(size_t numOfPopulation)
{
	Population population;
	// Generate permutations of town sequences
	const size_t PERMUTATION_DISTANCE = 1000;
	std::vector<size_t> route = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for (size_t i = 0; i != numOfPopulation; ++i)
	{
		for (size_t i = 0; i != PERMUTATION_DISTANCE; ++i)
			std::next_permutation(route.begin(), route.end());

		population.emplace_back(Route(route), std::numeric_limits<float>::max());
	}
	return population;
}

void TravellingSalesmanWithGenetic::evaluation(Population& population)
{
	for (size_t i = 0; i < population.size(); i++)
		population[i].second = calcFitness(population[i].first);
}

Population TravellingSalesmanWithGenetic::selection(Population& population)
{
	// Select the best half of the population.
	std::sort(population.begin(), population.end(),
		[](const Individual& lhs, const Individual& rhs)
		{
			return lhs.second < rhs.second;
		});
	Population M;
	for (size_t i = 0, parentCount = population.size() / 2; i != parentCount; ++i)
	{
		M.push_back(population[i]);
	}
	// Drop the second half of the population:
	population.resize(population.size() / 2);
	return M;
}

Individual TravellingSalesmanWithGenetic::crossOver(Population& population)
{
	const auto& parent1 = population[0].first;
	const auto& parent2 = population[1].first;

	Individual child;
	child.second = std::numeric_limits<float>::max();
	auto& crossed = child.first;
	crossed.resize(mNUM_OF_TOWNS);
	crossed[0] = parent1[0];
	crossed[1] = parent1[1];
	crossed[2] = parent1[2];
	crossed[3] = parent1[3];
	crossed[4] = parent1[4];
	// Ordered crossover - OX
	size_t crossEndIdx = 5;
	size_t parent2Idx = 0;
	while (crossEndIdx != crossed.size())
	{
		size_t nextNum = parent2[parent2Idx++];
		bool found = false;
		for (size_t crossedIdx = 0; crossedIdx != crossEndIdx; ++crossedIdx)
		{
			if (nextNum == crossed[crossedIdx])
			{
				found = true;
				break;
			}
		}
		if(!found)
			crossed[crossEndIdx++] = nextNum;
	}
	return child;
}

void TravellingSalesmanWithGenetic::mutate(Individual& individual, size_t occurence)
{
	auto& towns = individual.first;
	for (size_t i = 0; i != occurence; ++i)
	{
		const size_t mutationPos1 = randomUniform(0, 9);
		const size_t mutationPos2 = randomUniform(0, 9);
		const size_t townPos1 = towns[mutationPos1];
		towns[mutationPos1] = towns[mutationPos2];
		towns[mutationPos2] = townPos1;
	}
}

void TravellingSalesmanWithGenetic::reinsertion(Population& original, Population& mutated)
{
	for (const auto& individual : mutated)
		original.push_back(individual);
}

Individual TravellingSalesmanWithGenetic::getBestIndividual(Population& population)
{
	auto pBest = population.front();
	for (const auto& solution : population)
	{
		if (solution.second < pBest.second)
			pBest = solution;
	}
	return pBest;
}

Population TravellingSalesmanWithGenetic::getKRandomParents(Population& population, size_t numOfRandomIndividuals)
{
	Population Mk;
	for (size_t i = 0; i != numOfRandomIndividuals; i++)
	{
		size_t rndIdx = randomUniform(0, population.size() - 1);
		Mk.push_back(population[rndIdx]);
	}
	return Mk;
}

FitnessVal TravellingSalesmanWithGenetic::calcFitness(Route& route)
{
	std::vector<Town> tmp;
	for (size_t i = 0; i != route.size(); ++i)
		tmp.emplace_back(towns[route[i]]);

	return objective(tmp);
}

void TravellingSalesmanWithGenetic::printSolution(Individual& individual)
{
	std::cout << "The best sequence of towns = [ ";
	auto& towns = individual.first;
	for (size_t i = 0; i != towns.size(); ++i)
	{
		std::cout << towns[i];
		if (i != towns.size() - 1)
			std::cout << ", ";
	}
	std::cout << " ] fitness value = " << individual.second << "\n\n";
}

void TravellingSalesmanWithGenetic::initAndSolve()
{
	std::cout << "Solving the Travelling Salesman problem with Genetic algorithm..\n";

	constexpr size_t POPULATION_SIZE = 1000;
	constexpr size_t k = 2; // k random parent

	createTowns(mNUM_OF_TOWNS);
	Population P = initializePopulation(POPULATION_SIZE);
	evaluation(P);
	Individual pBest = getBestIndividual(P); // argmin f(x)
	for (size_t i = 0, stopCondition = 100; i != stopCondition; ++i)
	{
		Population M = selection(P); // select parents
		Population Px; // new crossed population
		while (Px.size() != P.size())
		{
			Population Mk = getKRandomParents(M, k);
			Individual c = crossOver(Mk);
			const size_t mutationOccurence = randomUniform(0, 2);
			mutate(c, mutationOccurence);
			Px.push_back(c);
		}
		reinsertion(P, Px);
		evaluation(P);
		pBest = getBestIndividual(P);
	}
	printSolution(pBest);
}
