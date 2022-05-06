#include <iostream>
#include <algorithm>

#include "KDTree.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
	KdTree tree;
	/*
	* ----------.+++++++++++
	* ------x---.+++++++++++
	* ----------.+++++++++++
	* ---------T.+x+++++++++
	* ----------x+++++++++++
	* ----------.-----------
	* ----------.+++++++++++
	* ----------.++x++++++++
	* ----------.+++++++++++
	*/


	tree.fill({ {0,1}, {1, 2}, {-4, 4}, {3, -2} });
	tree.insert({ 0, 1 });

	auto p1 = tree.findNearest({ -1, 2 });
	auto ps = tree.findNearest({ -1, 2 }, 2);
	auto psByDistance = tree.findNearestByDistance({ -1, 2 }, 3);
	auto psByArea = tree.findNearestByArea({ -1,0 }, { 3, 3});

	return 0;
}
