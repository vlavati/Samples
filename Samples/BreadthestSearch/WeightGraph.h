#pragma once

#include "Graph.h"

template <typename Vertex = int, typename Weight = float>
struct WeightGraph
{
	void addVertex(Vertex v);
	void addEdge(Vertex source, Vertex dest, Weight w);
	const std::vector<Vertex>& neighbours(Vertex v) const;
	Weight weight(Vertex source, Vertex dest) const;
	const std::vector<Vertex>& vertices() const;
private:
	Graph<Vertex> _g;
	std::unordered_map<Vertex, std::unordered_map<Vertex, Weight>> _weights;
};

template<typename Vertex, typename Weight>
void WeightGraph<Vertex, Weight>::addVertex(Vertex v)
{
	_g.addVertex(v);
}

template<typename Vertex, typename Weight>
void WeightGraph<Vertex, Weight>::addEdge(Vertex source, Vertex dest, Weight w)
{
	_g.addEdge(source, dest);
	_weights[source][dest] = w;
}

template<typename Vertex, typename Weight>
const std::vector<Vertex>& WeightGraph<Vertex, Weight>::neighbours(Vertex v) const
{
	return _g.neighbours(v);
}

template<typename Vertex, typename Weight>
inline Weight WeightGraph<Vertex, Weight>::weight(Vertex source, Vertex dest) const
{
	return _weights.at(source).at(dest);
}

template<typename Vertex, typename Weight>
const std::vector<Vertex>& WeightGraph<Vertex, Weight>::vertices() const
{
	return _g.vertices();
}
