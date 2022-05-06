#pragma once

#include <iostream>
#include <vector>
#include <cassert>

using Index = size_t;

template <int D = 2>
struct Heapify
{
	static Index firstLeafIndex(Index size);
	static inline Index parentIndex(Index currentIndex);
	static Index firstChildIndex(Index currentIndex);

	template <typename Container>
	static Index minimalChildIndex(const Container& container, Index currentIndex, Index size);
	template <typename Container>
	static void pushDown(Container& container, Index currentIndex, Index size);
	template <typename Container>
	static void bubbleUp(Container& container, Index currentIndex);

	template<typename Container>
	static void heapify(Container& container);
	template<typename Container>
	static void sort(Container& container);
};

template<int D>
typename Index Heapify<D>::firstChildIndex(Index currentIndex)
{
	return currentIndex * D + 1;
}


template<int D>
inline typename Index Heapify<D>::firstLeafIndex(Index size)
{
	assert(size > 0);

	//One item is first leaf
	if (size == 1)
		return 0;

	// pi = (chI-1)/D
	// if chI == last index then next pi has no child items
	// fli = pi(last index) + 1 = pi(si - 1) + 1 = (si - 2) / D + 1
	return parentIndex(size - 1) + 1;
}


//0 - top (size = 1)
//1,2 - children (size = 3)
//3,4;5,6 - grandchildren (size = 7) - chI = [i*D+1, i*D+2,..., i*D+D] => pi = (chI-1)/D
//7,8;9,10;11,12;13,14 - (size = 15)
template<int D>
typename Index Heapify<D>::parentIndex(Index currentIndex)
{
	assert(currentIndex > 0);

	return (currentIndex - 1) / D;
}

template<int D>
template <typename Container>
typename Index Heapify<D>::minimalChildIndex(const Container &data, Index currentIndex, Index size)
{
	Index minChildIndex = firstChildIndex(currentIndex);
	const Index lastChildIndex = firstChildIndex(currentIndex + 1);

	for (Index childIndex = minChildIndex + 1;
		childIndex < lastChildIndex && childIndex < size;
		childIndex++)
	{
		if (data[childIndex] < data[minChildIndex])
			minChildIndex = childIndex;
	}

	return minChildIndex;
}


template<int D>
template <typename Container>
void Heapify<D>::pushDown(Container& data, Index currentIndex, Index size)
{
	assert(data.size() > 0 && data.size() >= size && size > 0);

	auto item = data[currentIndex];
	const Index minLeafIdx = firstLeafIndex(size);
	while (currentIndex < minLeafIdx)
	{
		Index minChildIndex = minimalChildIndex(data, currentIndex, size);

		if (data[minChildIndex] < item)
		{
			data[currentIndex] = data[minChildIndex];
			currentIndex = minChildIndex;
		}
		else
			break;
	}

	data[currentIndex] = item;
}


template<int D>
template <typename Container>
inline void Heapify<D>::bubbleUp(Container& data, Index currentIndex)
{
	assert(currentIndex < data.size());

	auto item = data[currentIndex];
	while (currentIndex > 0)
	{
		Index parentIdx = parentIndex(currentIndex);
		if (item < data[parentIdx])
		{
			data[currentIndex] = data[parentIdx];
			currentIndex = parentIdx;
		}
		else
			break;
	}

	data[currentIndex] = item;
}

template<int D>
template<typename Container>
inline void Heapify<D>::heapify(Container& container)
{
	if (container.size() < 2)
		return;

	const Index lastParent = parentIndex(container.size() - 1);
	for (Index i = 0; i <= lastParent; i ++ )
		Heapify<D>::pushDown(container, lastParent - i, container.size());
}

template<int D>
template<typename Container>
inline void Heapify<D>::sort(Container& container)
{
	heapify(container);

	for (Index last = static_cast<Index>(container.size()) - 1;
		last > 0;
		last--)
	{
		std::swap(container[0], container[last]);
		Heapify<D>::pushDown(container, 0, last);
	}

	Index last = static_cast<Index>(container.size()) - 1;
	for (Index i = 0; i < container.size() / 2; i++)
	{
		std::swap(container[i], container[last - i]);
	}
}

template <typename T, int D = 2>
class Heap
{
	std::vector<T> _data;

public:

	template <typename Container>
	Heap& operator=(const Container& container);

	void push(T value);
	const T& top() const;
	T pop();
	bool empty() const;
	size_t size() const { return _data.size(); }
};

template<typename T, int D>
inline void Heap<T, D>::push(T value)
{
	_data.push_back(value);

	Heapify<D>::bubbleUp(_data, static_cast<Index>(_data.size()) - 1);
}

template<typename T, int D>
inline const T& Heap<T, D>::top() const
{
	assert(_data.size() > 0);
	return _data[0];
}

template<typename T, int D>
inline T Heap<T, D>::pop()
{
	assert(_data.size() > 0);
	T acc = _data.back();
	_data.pop_back();

	if (empty())
		return acc;

	std::swap(acc, _data[0]);

	Heapify<D>::pushDown(_data, 0, _data.size());

	return acc;
}

template<typename T, int D>
inline bool Heap<T, D>::empty() const
{
	return _data.empty();
}

template<typename T, int D>
template<typename Container>
inline Heap<T, D>& Heap<T, D>::operator=(const Container& container)
{
	_data = container;
	Heapify<D>::heapify(_data);
	return *this;
}

template <int K, typename Heap, typename T>
void kLargestPush(Heap& heap, T value)
{
	if (heap.size() == K && heap.top() < value)
		heap.pop();

	if (heap.size() < K)
		heap.push(value);
}