#include <iostream>

using namespace std;

int defaultValue()
{
	return -1;
}


template <typename Random = decltype(defaultValue)>
int value(Random&& random = defaultValue)
{
	return random();
}

struct Some
{
	int val = 0;
	int getVal()
	{
		val++;
		return val;
	}
};

auto values(Some& some)
{
	return [&some]() {
		return some.getVal();
	};
}

template <typename Problem>
void update(Problem&& problem)
{
	auto gen = values(problem);

	for (int i = 0; i < 10; i++)
		cout << "I= " << i << " Val= " << gen() << endl;
}


template <typename Problem>
void bestDo(Problem&& problem)
{
	for (int i = 0; i < 2; i++)
	{
		cout << "DO = " << i << endl;
		update(problem);
	}
}


void ValueTest()
{
	Some some{};

	cout << "In" << some.getVal() << endl;

	bestDo(some);

	cout << "Ret" << some.getVal() << endl;
}