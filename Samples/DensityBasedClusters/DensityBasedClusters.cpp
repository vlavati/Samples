// DensityBasedClusters.cpp : Defines the entry point for the application.
//

#include "DensityBasedClusters.h"
#include <iostream>
#include <queue>

#include "KdTree.h"

using namespace std;



vector<int> makeClusters(const vector<Point> &points)
{
	const int NonCluster = 0;
	const int Outlier = -1;
	vector<int> clusters(points.size(), NonCluster);

	KdTree tree;
	tree.fill(points);
	const int Distance = 2;
	const int MinNeighbors = 3;
	int clusterIndex = 0;
	for (int i = 0; i < points.size(); i++)
	{
		if (clusters[i] != NonCluster)
			continue;
		queue<Point> toProcess;
		toProcess.push(points[i]);
		clusters[i] = Outlier;
		clusterIndex++;
		while(!toProcess.empty())
		{
			auto q = toProcess.front();
			toProcess.pop();
			auto neighbors = tree.findNearestByDistance(q, Distance);
			if (neighbors.size() < MinNeighbors)
				continue;

			auto qIndex = find(points.begin(), points.end(), q) - points.begin();
			clusters[qIndex] = clusterIndex;
			for (auto n : neighbors)
			{
				auto nIndex = find(points.begin(), points.end(), n) - points.begin();
				if (clusters[nIndex] <= NonCluster)
					toProcess.push(n);
			}
		}
	}

	return clusters;
}



int main()
{
	vector<Point> points{ {0,0}, {0,1}, {1,0}, {5,5}, {5,6}, {6,5} };
	vector<int> clusters = makeClusters(points);
	return 0;
}
