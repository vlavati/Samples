// Disjointed.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <map>

template <typename T = int>
class DisjointSet
{
public:
	void add(T item);
	void merge(T item1, T item2);
	bool disjointed(T item1, T item2);
	T find(T item);
private:
	struct Info
	{
		T parent;
		size_t rank;
	};
	std::map<T, Info> infos;
};

template<typename T>
inline void DisjointSet<T>::add(T item)
{
	if (infos.find(item) != infos.end())
		return;

	infos[item] = Info{ item, 1 };
}

template<typename T>
inline void DisjointSet<T>::merge(T item1, T item2)
{
	auto p1 = find(item1);
	auto p2 = find(item2);
	if (p1 == p2)
		return;

	if (infos[p2].rank < infos[p1].rank)
		std::swap(p1, p2);

	// Attach smallest set to bigger set
	infos[p1].parent = p2;
	infos[p2].rank += infos[p1].rank;
}

template<typename T>
inline bool DisjointSet<T>::disjointed(T item1, T item2)
{
	return find(item1) != find(item2);
}

template<typename T>
inline T DisjointSet<T>::find(T item)
{
	if (infos[item].parent == item)
		return item;

	infos[item].parent = find(infos[item].parent);
	return infos[item].parent;
}
