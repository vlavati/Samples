#pragma once

#include <random>

// Definitions for random
inline auto defaultRandom()
{
	std::random_device rd;
	auto seed = rd();
	return std::default_random_engine(seed);
}

template <typename Seed>
inline auto constantSeed(Seed seed)
{
	return std::default_random_engine(seed);
}

template <typename Random = decltype(defaultRandom)>
int uniform(int min, int max, Random&& random = defaultRandom)
{
	std::uniform_int_distribution<> distribution(min, max);

	return distribution(random());
}

template <typename Random = decltype(defaultRandom)>
std::vector<int> randomPermutation(int count = 4, int start = 0, int max = 256, Random&& random = defaultRandom)
{
	//TODO: it is possible to generate permutation without generating the whole range
	std::vector<int> permutation(max);
	std::iota(permutation.begin(), permutation.end(), start);

	std::shuffle(permutation.begin(), permutation.end(), random());

	std::vector<int> ret;
	std::copy(permutation.begin(), permutation.begin() + count, std::back_inserter(ret));

	return ret;
}

// Definitions for Genetic
template <
	typename Problem,
	typename Population,
	typename Solution = typename Population::value_type>
Solution chooseBest(Problem&& problem, Population population)
{
	auto bestFitness = 0;
	auto bestSolution = Solution{};
	for (auto solution : population)
	{
		auto currentFitness = fitness(problem, solution);
		if (currentFitness > bestFitness)
		{
			bestFitness = currentFitness;
			bestSolution = solution;
		}
	}
	//TODO: in case of all invalid - result is solution 0
	return bestSolution;
}

template <
	typename Problem,
	typename Population>
Population elitism(Problem&& problem, Population population)
{
	return { chooseBest(problem, population) };
}

template <
	typename Problem,
	typename Population,
	typename Solution = typename Population::value_type>
Solution select(Problem&& problem, Population population)
{
	sort(population.begin(), population.end(), [&problem](auto a, auto b) { return fitness(problem, a) > fitness(problem, b); });
	const auto bestThreshold = 0.8;
	return population[uniform(0, (int)(population.size() * bestThreshold), randoms(problem))];
}

template <
	typename Problem,
	typename Population,
	typename Solution = typename Population::value_type>
Population naturalSelection(Problem&& problem, Population population)
{
	auto newPopulation = elitism(problem, population);

	while (newPopulation.size() < population.size())
	{
		auto p1 = select(problem, population);
		auto p2 = select(problem, population);
		auto newSolution = crossover(problem, p1, p2);
		for (auto mutate : mutations(problem))
		{
			newSolution = mutate(newSolution);
		}
		newPopulation.push_back(newSolution);
	}

	return newPopulation;
}

template <
	typename Problem,
	typename Population = typename remove_reference_t<Problem>::Population_type,
	typename Solution = typename Population::value_type>
Solution bestGenetic(Problem &&problem, const int MaxIterations = 100)
{
	auto population = initPopulation(problem);
	simulate(problem, population);

	for (int i = 0; i < MaxIterations; i++)
	{
		population = naturalSelection(problem, population);
		simulate(problem, population);
	}

	return chooseBest(problem, population);
}