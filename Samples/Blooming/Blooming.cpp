// Blooming.cpp : Defines the entry point for the application.
//

#include "Blooming.h"

#include <iostream>
#include <random>
#include <unordered_set>

using namespace std;

int main()
{
	BloomFilter filter(100, 0.5);

	auto gen = generator();
	std::vector<int> values(100);
	std::generate(values.begin(), values.end(), [&gen]() { auto val = gen(); return val* val; });

	std::unordered_set<int> set;
	for (auto i : values)
	{
		filter.add(i);
		set.insert(i);
	}

	auto seed = std::random_device{}();
	std::default_random_engine randoms(seed);
	std::uniform_int_distribution<> dis(1, 10);

	cout << std::boolalpha;
	auto result = [&](auto val)
	{
		auto filterRes = filter.contains(val);
		auto setRes = (set.find(val) != set.end());
		if (filterRes == setRes)
			return "Ok";

		if (filterRes && !setRes)
			return "False positive";

		return "FAIL";
	};

	for (int i = 0; i < 100; i++)
	{
		auto val = dis(randoms);
		cout << "Contains [" << val << "]:" << filter.contains(val) << " - " << result(val) << endl;
	}

	return 0;
}
