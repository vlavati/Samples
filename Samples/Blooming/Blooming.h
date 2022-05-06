// Blooming.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <vector>
#include <functional>
#include <algorithm>

using HashFunc = std::function<std::size_t(size_t)>;
inline static std::vector<HashFunc> makeHashFuncs(size_t num, size_t mod);

auto generator()
{
	int i = 0;
	return [=]() mutable
	{
		return ++i;
	};
}

auto hashFunc(size_t i, size_t mod)
{
	return [=](size_t hashValue) mutable
	{
		return (i * hashValue + i * i) % mod;
	};
}

inline std::vector<HashFunc> makeHashFuncs(size_t num, size_t mod)
{
	std::vector<HashFunc> funcs(num);
	auto gen = generator();
	std::generate(funcs.begin(), funcs.end(), [&]() { return hashFunc(gen(), mod); });
	return funcs;
}


template <typename T = int>
class BloomFilter
{
public:
	BloomFilter(size_t maxSize, float tolerance = 0.01);
	void add(T item);
	bool contains(T item) const;
private:
	std::vector<HashFunc> hashFuncs;
	std::vector<bool> bits;
	std::vector<size_t> positions(T value) const;
	bool contains(const std::vector<size_t>& indices) const;
};


template<typename T>
inline BloomFilter<T>::BloomFilter(size_t maxSize, float tolerance)
{
	auto numBits = static_cast<size_t>(-ceil(maxSize * log(tolerance) / log(2) / log(2)));
	auto numHashFuncs = static_cast<size_t>(-ceil(log(tolerance) / log(2)));
	bits.resize(numBits);
	hashFuncs = makeHashFuncs(numHashFuncs, numBits);
}

template<typename T>
inline std::vector<size_t> BloomFilter<T>::positions(T value) const
{
	auto hash = std::hash<T>{}(value);
	std::vector<std::size_t> indices(hashFuncs.size());
	std::transform(hashFuncs.begin(), hashFuncs.end(), indices.begin(),
		[hash](const auto& f) -> std::size_t { return f(hash); });
	return indices;
}
 
template<typename T>
inline void BloomFilter<T>::add(T value)
{
	auto indices = positions(value);
	if (contains(indices))
		return;
	std::for_each(indices.begin(), indices.end(),
		[this](auto idx) { bits[idx] = true; });
}

template<typename T>
inline bool BloomFilter<T>::contains(T value) const
{
	return contains(positions(value));
}

template<typename T>
inline bool BloomFilter<T>::contains(const std::vector<size_t>& indices) const
{
	return std::all_of(indices.begin(), indices.end(),
		[this](auto idx) { return bits[idx]; });
}
