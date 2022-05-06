#include "BreadthestSearch.h"
#include <iostream>
#include <vector>
#include <random>
#include <queue>
#include <algorithm>

#include <unordered_map>
#include "Graph.h"

using namespace std;


template <typename Graph, typename Vertex>
vector<Vertex> breadthFirstSearch(const Graph &graph, const Vertex &source, const Vertex& destination)
{
	unordered_map<Vertex, Vertex> parents;
	queue<Vertex> queue;

	queue.push(source);
	parents[source] = Vertex{};
	bool found = false;

	while (!queue.empty())
	{
		auto v = queue.front();
		queue.pop();

		if (v == destination)
		{
			found = true;
			break;
		}

		for (auto n : graph.neighbours(v))
		{
			if (parents.find(n) != parents.end())
				continue;
	
			parents[n] = v;
			queue.push(n);
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
	Graph<> g;

	g.addEdge(1, 2);
	g.addEdge(2, 3);
	g.addEdge(3, 1);
	g.addEdge(2, 4);
	g.addEdge(4, 5);
	g.addEdge(5, 6);
	g.addEdge(6, 4);
	g.addEdge(2, 6);

	auto path = breadthFirstSearch(g, 1, 6);
	auto pathBack = breadthFirstSearch(g, 6, 1);

	return 0;
}

