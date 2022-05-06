#include "Canopying.h"
#include <iostream>
#include <vector>
#include <random>

using namespace std;

struct Canopy
{
	int center = -1;
	vector<int> indices;
};

int distance(const Point& p1, const Point& p2)
{
	int sum = 0;

	for (int i = 0; i < p1.size(); i++)
	{
		int diff = p1[i] - p2[i];
		sum += diff * diff;
	}

	return sqrt(sum);
}

template <typename Container, typename T>
int indexOf(Container container, T value)
{
	return find(container.begin(), container.end(), value) - container.begin();
}



vector<Canopy> canopying(const vector<Point>& points, int DistCore, int DistMax)
{
	auto centroids = points;

	auto seed = std::random_device{}();
	std::default_random_engine randoms(seed);

	vector<Canopy> canopies;

	while (!centroids.empty())
	{
		std::uniform_int_distribution<> indexDist(0, centroids.size() - 1);
		auto p = centroids[indexDist(randoms)];
		int pIdx = indexOf(points, p);
		Canopy canopy{ pIdx };

		for (int i = 0; i < points.size(); i++)
		{
			auto dist = distance(points[i], p);
			if (dist < DistMax)
			{
				canopy.indices.push_back(i);
				if (dist < DistCore)
				{
					centroids.erase(find(centroids.begin(), centroids.end(), points[i]));
				}
			}
		}

		canopies.push_back(canopy);
	}

	return canopies;
}

int main()
{
	vector<Point> points{ {0,0}, {0,1}, {1,0}, {5,5}, {5,6}, {6,5} };

	auto c = canopying(points, 2, 5);

	return 0;
}
