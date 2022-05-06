// RandomTreap.cpp : Defines the entry point for the application.
//

#include "RandomTreap.h"
#include <iostream>
using namespace std;

int main()
{
	cout << "Hello RandomTreap." << endl;
	auto testData = { 9, 2, 15, 9, 10, 3};
	Treap<int> treap;

	int i = 0;
	for (auto val: testData)
		treap.insert(val, i++);

	auto printTreap = [](auto& treap)
	{
		treap.traverse([](auto level, auto val, auto prio)
			{
				cout << "Level: " << level << " Value: " << val << " Prio: " << prio << endl;
			});
	};

	printTreap(treap);
	treap.remove(9);
	cout << "Print after remove 9" << endl;
	printTreap(treap);

	treap.remove(9);
	cout << "Print after another remove 9" << endl;
	printTreap(treap);

	RandomTreap<int> rTreap;
	for (auto val : testData)
		rTreap.insert(val);


	return 0;
}
