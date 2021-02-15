#include "Annealing.h"
#include <iostream>
#include <vector>

namespace
{
	using ArrayState = std::vector<int>;

	struct UniformPositionMutation
	{
		std::uniform_int_distribution<> distribution;
		UniformPositionMutation(int size, int base = 0, float scale = 0) :
			distribution(0, size - 1) {}
	};

	struct CauchyPositionMutation
	{
		std::cauchy_distribution<> distribution;
		CauchyPositionMutation(int size, int base, float scale) :
			distribution(base, scale) {}
	};

	struct NormalPositionMutation
	{
		std::normal_distribution<> distribution;
		NormalPositionMutation(int size, int base, float scale) :
			distribution(base, scale) {}
	};

	template <typename Temperature = float,
			typename PositionMutation = UniformPositionMutation>
	struct Mutation
	{
		std::default_random_engine generator;

		ArrayState operator()(const ArrayState& state, Temperature temperature)
		{
			ArrayState result = state;

			UniformPositionMutation startPosition((int)result.size());

			int swapPosition1 = startPosition.distribution(generator);
			int swapPosition2 = swapPosition1;

			PositionMutation positionMutation((int)result.size(), swapPosition1, temperature);

			while (swapPosition2 == swapPosition1 || swapPosition2 < 0 || swapPosition2 >= result.size())
			{
				swapPosition2 = (int)positionMutation.distribution(generator);
			}

			std::swap(result[swapPosition1], result[swapPosition2]);

			return result;
		}
	};

	float Energy(const ArrayState& state)
	{
		int collisions = 0;

		for (int i = 0; i < state.size() - 1; i++)
		{
			for (int j = i + 1; j < state.size(); j++)
			{
				if (state[i] > state[j])
					collisions++;
			}
		}

		return (float)collisions;
	}
}

struct AcceptedEnergyReached
{
	ArrayState state;
};

int main()
{
	std::default_random_engine generator;
	std::uniform_int_distribution<> dis(1, 100);

	std::vector<int> values(100);
	std::generate(values.begin(), values.end(), [&]() { return dis(generator); });

	ArrayState initial = values;

    auto onIteration = [](auto iteration, auto& state, auto energy, auto temperature)
	{
		std::cout << iteration << ";" << temperature << ";" << energy << std::endl;
		if (energy == 0)
			throw AcceptedEnergyReached{ state };
	};

	ArrayState out;

	try
	{
		out = algorithm::Annealing(initial, Mutation<>(), Energy, onIteration);
	}
	catch (AcceptedEnergyReached& ex)
	{
		out = ex.state;
	}

	std::sort(initial.begin(), initial.end());

	std::cout << "Result: " << ((out == initial) ? "Ok" : "Fail") << std::endl;

	return 0;
}
