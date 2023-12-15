#pragma once

class TravellingSalesmanWithGenetic: public TravellingSalesmanProblem
{
public:
	using Route = std::vector<size_t>;
	using FitnessVal = float;
	using Individual = std::pair<Route, FitnessVal>;
	using Population = std::vector<Individual>;

public:
	void initAndSolve();

private:
	void createTowns(size_t numOfTowns);
	Population initializePopulation(size_t numOfPopulation);
	void evaluation(Population&);
	Population selection(Population&);
	Individual crossOver(Population&);
	void mutate(Individual&, size_t occurence);
	void reinsertion(Population&, Population&);
	Individual getBestIndividual(Population&); // argmin f(x)
	Population getKRandomParents(Population&, size_t numOfRandomIndividuals); // (p1, p2,.., pk) <--random-- M
	FitnessVal calcFitness(Route&);
	void printSolution(Individual&);

private:
	const size_t mNUM_OF_TOWNS = 10;
};
