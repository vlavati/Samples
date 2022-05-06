// KMeans.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <array>

template <typename T = int, int K = 2>
using PointT = std::array<T, K>;

using Point = PointT<>;
