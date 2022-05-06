#include "DeepestSearch.h"
#include <iostream>
#include <vector>
#include <random>
#include <queue>
#include <algorithm>

#include <unordered_map>
#include "Graph.h"

using namespace std;


template <typename Graph, typename Vertex>
int deepFirstSearch(const Graph &graph, const Vertex &source, int time, unordered_map<Vertex, int> &in_time, unordered_map<Vertex, int>& out_time)
{
	time++;
	in_time[source] = time;

	for (auto n : graph.neighbours(source))
	{
		if (in_time.find(n) != in_time.end())
			continue;

		time = deepFirstSearch(graph, n, time, in_time, out_time);
	}

	time++;
	out_time[source] = time;

	return time;
}

template <typename Graph, typename Vertex>
void deepFirstSearch(const Graph& graph, Vertex some)
{
	unordered_map<Vertex, int> in_time;
	unordered_map<Vertex, int> out_time;
	int time = 0;
	for (auto v : graph.vertices())
	{
		if (in_time.find(v) != in_time.end())
			continue;

		time = deepFirstSearch(graph, v, time, in_time, out_time);
	}

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

	deepFirstSearch(g, 1);

	return 0;
}

