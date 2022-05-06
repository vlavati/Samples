#pragma once

#include <unordered_map>
#include <vector>

template <typename Vertex = int>
struct Graph
{
	void addVertex(Vertex v);
	void addEdge(Vertex source, Vertex dest);
	const std::vector<Vertex> &neighbours(Vertex v) const;
	const std::vector<Vertex> &vertices() const;
private:
	std::unordered_map<Vertex, std::vector<Vertex> > _neighbours;
	std::vector<Vertex> _vertices;
};

template<typename Vertex>
void Graph<Vertex>::addVertex(Vertex v)
{
	if (find(_vertices.begin(), _vertices.end(), v) != _vertices.end())
		return;

	_vertices.push_back(v);
	_neighbours[v] = {};
}

template<typename Vertex>
void Graph<Vertex>::addEdge(Vertex source, Vertex dest)
{
	addVertex(source);
	addVertex(dest);

	auto& arr = _neighbours[source];
	if (find(arr.begin(), arr.end(), dest) != arr.end())
		return;

	arr.push_back(dest);
}

template<typename Vertex>
const std::vector<Vertex> &Graph<Vertex>::neighbours(Vertex v) const
{
	return _neighbours.at(v);
}

template<typename Vertex>
const std::vector<Vertex> &Graph<Vertex>::vertices() const
{
	return _vertices;
}
