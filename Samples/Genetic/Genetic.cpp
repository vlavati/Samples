#include "Genetic.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <random>
#include <numeric>
#include <functional>
#include <bitset>

using namespace std;

struct Thing
{
	int weight = 0;
	int calories = 0;
};

template <typename Store, typename Solution>
Thing summary(Store& store, Solution solution)
{
	Thing sum{};

	for (int t = 0; t < store.size(); t++)
	{
		if ((solution & (1 << t)) != 0)
		{
			sum.calories += store[t].calories;
			sum.weight += store[t].weight;
		}
	}

	return sum;
}

template <typename Solution, typename Store, typename Validation>
vector<Solution> bestBrutforce(Store& store, Validation isValid)
{
	int bestCalories = 0;
	vector<Solution> best;

	// hardcoded 256 variants
	// TODO use mutable generator to generate all cases of Solution

	for (Solution i = 0; i < 256; i++)
	{
		Thing sum = summary(store, i);

		// It is possible to use functional concept
		if (!isValid(sum))
			continue;

		if (sum.calories > bestCalories)
		{
			bestCalories = sum.calories;
			best = { i };
		}
		else if (sum.calories == bestCalories)
		{
			best.push_back(i);
		}
	}

	return best;
}

namespace
{
	using Solution = int;
	template<typename Solution>
	using Mutate = function<Solution(Solution)>;

	struct Knapsack
	{
		vector<Thing> store{ {10 , 10}, {1, 1}, {31 , 100}, {20 , 15}, {15 , 20}, {5 , 7}, {8 , 3}, {15 , 17} };
		const int maxWeight = 30;
		const int populationSize = 4;
		using Population_type = vector<Solution>;
		std::default_random_engine randoms;

		const bool details = false;
		int step = 0;
		Population_type sortedPopulation;
	};

	auto randoms(Knapsack& knapsack)
	{
		return [&knapsack]() -> default_random_engine& {
			return knapsack.randoms;
		};
	}

	int fitness(const Knapsack& knapsack, int solution)
	{
		auto sum = summary(knapsack.store, solution);
		return sum.weight > knapsack.maxWeight ? 0 : sum.calories;
	}

	Knapsack::Population_type initPopulation(Knapsack& knapsack)
	{
		return randomPermutation(knapsack.populationSize, 0, 256, randoms(knapsack));
	}

	void simulate(Knapsack& knapsack, Knapsack::Population_type& population)
	{
		knapsack.step++;
		knapsack.sortedPopulation = population;
		sort(knapsack.sortedPopulation.begin(), knapsack.sortedPopulation.end(), [&knapsack](auto a, auto b) { return fitness(knapsack, a) > fitness(knapsack, b); });
		auto x = knapsack.sortedPopulation[0];
		auto sumG = summary(knapsack.store, x);

		cout << "Step = " << knapsack.step 
			<< " Best"
			<< " Solution: " << hex << x << " Bin: " << bitset<8>(x)
			<< " Calories: " << dec << sumG.calories
			<< " Weight: " << sumG.weight
			<< " Fitness: " << fitness(knapsack, x)
			<< endl;

		if (knapsack.details)
			for (auto x: knapsack.sortedPopulation)
				cout << "Bin: " << bitset<8>(x)
					<< " Fitness: " << fitness(knapsack, x)
					<< endl;
	}

	Solution chooseBest(Knapsack& knapsack, Knapsack::Population_type& population)
	{
		return knapsack.sortedPopulation[0];
	}

	Solution select(Knapsack& knapsack, Knapsack::Population_type& population)
	{
		const auto bestThreshold = 0.8;
		return knapsack.sortedPopulation[uniform(0, (int)(population.size() * bestThreshold), randoms(knapsack))];
	}


	auto mutations(Knapsack& problem)
	{
		auto randomXor = [&problem](auto solution)
		{
			uint8_t bitMask = 1 << uniform(0, 7, randoms(problem));
			return solution ^ bitMask;
		};
		auto randomNew = [&problem](auto solution)
		{
			uint8_t mask = uniform(0, 255, randoms(problem));

			return solution ^ mask;
		};
		return vector<Mutate<Solution>>{ randomXor, randomNew };
	}

	Solution crossover(Knapsack& problem, Solution p1, Solution p2)
	{
		int partOfP1 = uniform(0, 7, randoms(problem));

		uint8_t maskOfP1 = 0xFF >> (8 - partOfP1);
		uint8_t maskOfP2 = 0xFF ^ maskOfP1;

		return (p1 & maskOfP1) | (p2 & maskOfP2);
	}

}

int main()
{
	Knapsack knapsack{};

	cout << "BRUTFORCE" << endl;
	auto isValid = [&knapsack](auto sum) { return sum.weight <= knapsack.maxWeight;  };
	auto best = bestBrutforce<int>(knapsack.store, isValid);
	for (auto x : best)
	{
		auto sum = summary(knapsack.store, x);
		cout << "Best:" << hex << x << " Bin: " << bitset<8>(x) << endl;
		cout << "Calories:" << dec << sum.calories << endl;
		cout << "Weight:" << sum.weight << endl;
	}

	cout << "GENETIC" << endl;
	knapsack.randoms = constantSeed(5);
	auto bestG = bestGenetic(knapsack);
	cout << "Genetic:" << hex << bestG << " Bin: " << bitset<8>(bestG) << endl;
	auto sumG = summary(knapsack.store, bestG);
	cout << "Calories:" << dec << sumG.calories << endl;
	cout << "Weight:" << sumG.weight << endl;

	cout << "RESULT" << endl;
	cout << "Genetic is " << ((find(best.begin(), best.end(), bestG) == best.end()) ? "NOT" : "") << " ABLE to find solution" << endl;

	return 0;
}
