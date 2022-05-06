// KMeans.cpp : Defines the entry point for the application.
//

#include "KMeans.h"

#include <iostream>
#include <vector>
#include <random>

//auto seed = std::random_device{}();
//std::default_random_engine randoms(seed);
//std::uniform_int_distribution<> dis(1, 10);
//auto val = dis(randoms);
using namespace std;

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


vector<int> initClusters(int numPoints, int numClusters)
{
	return vector<int>(numPoints, 0);
}

vector<Point> initCenters(const vector<Point> &points, int numClusters)
{
	vector<Point> centers(numClusters);

	auto seed = std::random_device{}();
	std::default_random_engine randoms(seed);
	const int MaxNoise = 2;
	std::uniform_int_distribution<> indexDist(0, points.size() - 1);
	std::uniform_int_distribution<> noiseDist(-MaxNoise, MaxNoise);

	//TODO provide non-repeatable values of index

	auto generator = [&indexDist, &noiseDist, &randoms, &points]()
	{
		auto point = points[indexDist(randoms)];

		for (int i = 0; i < point.size(); i++)
			point[i] += noiseDist(randoms);

		return point;
	};

	std::generate(centers.begin(), centers.end(), generator);

	return centers;
}

int movePoints(const vector<Point>& points, const vector<Point> &centers, vector<int> &clusters)
{
	int movedPoints = 0;

	for (int i = 0; i < points.size(); i++)
	{
		//TODO use KdTree with centers to check which center is closer to each point
		int nearestCenter = 0;
		auto nearestDistance = distance(centers[nearestCenter], points[i]);

		for (int c = 1; c < centers.size(); c++)
		{
			auto distanceC = distance(centers[c], points[i]);
			if (distanceC < nearestDistance)
			{
				nearestDistance = distanceC;
				nearestCenter = c;
			}
		}

		if (clusters[i] != nearestCenter)
		{
			clusters[i] = nearestCenter;
			movedPoints++;
		}
	}

	return movedPoints;
}


/////////////

template<class InputIt, class T>
constexpr
T mean(InputIt first, InputIt last, T init)
{
	size_t cnt = 0;
	for (; first != last; ++first, cnt++) {
		init = std::move(init) + *first;
	}
	return init / cnt;
}

std::vector<Point::value_type> selectAxis(const std::vector<Point>& points, int axis)
{
	std::vector<Point::value_type> values;

	for (auto pt : points)
		values.push_back(pt[axis]);

	return values;
}


Point mean(const std::vector<Point>& points)
{
	Point meanPoint;
	
	for (int i = 0; i < meanPoint.size(); i++)
	{
		auto values = selectAxis(points, i);
		meanPoint[i] = mean(values.begin(), values.end(), 0);
	}

	return meanPoint;
}


/////////////


void updateCenters(const vector<Point>& points, vector<Point>& centers, const vector<int>& clusters)
{
	for (int c = 0; c < centers.size(); c++)
	{
		vector<Point> clusterPoints;

		for (int cl = 0; cl < clusters.size(); cl++)
		{
			if (clusters[cl] == c)
				clusterPoints.push_back(points[cl]);
		}

		centers[c] = mean(clusterPoints);
	}
}


int main()
{
	const int MaxIterations = 10;
	const int CountClusters = 2; // K

	vector<Point> points{ {0,0}, {0,1}, {1,0}, {5,5}, {5,6}, {6,5} };

	vector<int> clusters = initClusters(points.size(), CountClusters);
	vector<Point> centers = initCenters(points, CountClusters);

	for (int i = 0; i < MaxIterations; i++)
	{
		int movedPoints = movePoints(points, centers, clusters);
		if (movedPoints == 0)
			break;

		updateCenters(points, centers, clusters);
	}

	return 0;
}
