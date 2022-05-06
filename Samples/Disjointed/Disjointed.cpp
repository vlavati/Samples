// Disjointed.cpp : Defines the entry point for the application.
//

#include "Disjointed.h"

#include <iostream>

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
	DisjointSet set;

	set.add(1);
	set.add(2);
	set.add(3);
	set.add(4);
	set.add(5);

	set.merge(1, 2);
	set.merge(1, 3);

	set.merge(4, 5);

	set.merge(1, 5);

	cout << set.find(1) << endl;


	return 0;
}
