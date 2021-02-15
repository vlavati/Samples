#pragma once

#include <functional>
#include <random>
#include <type_traits>

namespace algorithm
{
	template <typename Value = float>
	struct UniformDistribution
	{
		std::default_random_engine generator;
		std::uniform_real_distribution<Value> distribution{ 0.0f, 1.0f };

		Value operator()()
		{
			return distribution(generator);
		}
	};

	template <typename Energy = float,
		typename Temperature = Energy,
		typename Probability = float>
	struct ApproximatedAcception
	{
		static Probability Get(Energy delta, Temperature temperature)
		{
			return exp(-delta / temperature);
		}
	};

	template <typename Temperature = float,
		int InitialTemperature = 10,
		int ConstProcent = 99>
	struct SimulatedQuenching
	{
		static constexpr Temperature Initial = InitialTemperature;
		static constexpr Temperature Const = ConstProcent/100.f;

		static Temperature Get(Temperature previous, int iteration)
		{
			return previous * Const;
		}
	};

	template <typename Temperature = float,
		int InitialTemperature = 10>
	struct BoltzmanAnnealing
	{
		static constexpr Temperature Initial = InitialTemperature;

		static Temperature Get(Temperature previous, int iteration)
		{
			return Initial / (Temperature)log(2 + iteration);
		}
	};

	template <typename Temperature = float,
		int InitialTemperature = 10>
	struct CauchyAnnealing
	{
		static constexpr Temperature Initial = InitialTemperature;

		static Temperature Get(Temperature previous, int iteration)
		{
			return Initial / (1 + iteration);
		}
	};

	template <
		typename TemperatureLaw = SimulatedQuenching<>,
		typename State,
		typename Energy = float,
		typename Temperature = Energy,
		typename Mutation = std::function<State(const State&, Temperature)>,
		typename CalcEnergy = std::function<Energy(const State&)>,
		typename ProbeLaw = UniformDistribution<>,
		typename AcceptionLaw = ApproximatedAcception<>,
		typename OnIteration = void*
	>
	State Annealing(const State& initial,
		Mutation mutate,
		CalcEnergy calcEnergy,
		OnIteration onIteration = nullptr)
	{
		ProbeLaw probeLaw;

		const int MaxIteration = 1000000;
		const Temperature MinimalTemperature = 0;

		State state = initial;
		Energy energy = calcEnergy(state);

		State minimalState = state;
		Energy minimalStateEnergy = energy;
		Temperature temperature = TemperatureLaw::Initial;

		if constexpr (std::is_invocable<OnIteration, int, const State&, Energy, Temperature>::value)
			onIteration(-1, state, energy, temperature);

		for (int iteration = 0;
			temperature > MinimalTemperature && iteration < MaxIteration;
			iteration++)
		{
			State newState = mutate(state, temperature);
			Energy newEnergy = calcEnergy(newState);

			float probability = 1.0;
			Energy deltaEnergy = newEnergy - energy;

			if (deltaEnergy >= 0.0)
			{
				probability = AcceptionLaw::Get(deltaEnergy, temperature);
			}

			float probe = probeLaw();

			if (probe < probability)
			{
				state = newState;
				energy = newEnergy;

				temperature = TemperatureLaw::Get(temperature, iteration);
			}

			if (energy < minimalStateEnergy)
			{
				minimalStateEnergy = energy;
				minimalState = state;
			}

			if constexpr (std::is_invocable<OnIteration, int, const State&, Energy, Temperature>::value)
				onIteration(iteration, state, energy, temperature);
		}

		return minimalState;
	}
}