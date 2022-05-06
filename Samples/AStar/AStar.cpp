#include "AStar.h"
#include <iostream>
#include <vector>
#include <random>
#include <queue>
#include <algorithm>

#include <unordered_map>
#include "WeightGraph.h"

using namespace std;


template <typename Graph, typename Vertex, typename Estimate>
vector<Vertex> breadthFirstSearch(const Graph& graph, const Vertex& source, const Vertex& destination, Estimate estimate)
{
	unordered_map<Vertex, Vertex> parents;
	unordered_map<Vertex, float> distances;
	struct QueueItem
	{
		Vertex v;
		float distance;
	};
	struct QueueItemComparer
	{
		bool operator()(const QueueItem& p1, const QueueItem& p2) const { return p1.distance > p2.distance; }
	};
	priority_queue<QueueItem, vector<QueueItem>, QueueItemComparer> queue;

	queue.push({ source, 0 });
	parents[source] = Vertex{};
	distances[source] = 0;
	bool found = false;

	while (!queue.empty())
	{
		auto [v, distance] = queue.top();
		queue.pop();

		if (v == destination)
		{
			found = true;
			break;
		}

		for (auto n : graph.neighbours(v))
		{
			auto weight = graph.weight(v, n);
			auto newDistance = distance + weight;

			if (distances.find(n) != distances.end() && distances[n] < newDistance)
				continue;
	
			auto score = newDistance + estimate(v, n);
			parents[n] = v;
			distances[n] = newDistance;
			queue.push({ n, score });
		}
	}

	parents.erase(source);

	if (!found)
		return {};

	vector<Vertex> path;
	Vertex current = destination;
	path.push_back(current);
	while (parents.find(current) != parents.end())
	{
		auto parent = parents[current];
		path.push_back(parent);
		current = parent;
	}

	std::reverse(path.begin(), path.end());

	return path;
}


int main()
{
	WeightGraph<> g;

	g.addEdge(1, 2, 1);
	g.addEdge(2, 3, 1);
	g.addEdge(3, 1, 1);
	g.addEdge(2, 4, 1);
	g.addEdge(4, 5, 1);
	g.addEdge(5, 6, 1);
	g.addEdge(6, 4, 1);
	g.addEdge(2, 6, 10);

	auto estimator = [](auto from, auto to) -> float { return 0.0; };
	auto path = breadthFirstSearch(g, 1, 6, estimator);
	auto pathBack = breadthFirstSearch(g, 6, 1, estimator);

	return 0;
}

