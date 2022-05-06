// KDTree.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <vector>
#include <array>

template <typename T = int, int K = 2>
using KdPoint = std::array<T, K>;

using Point = KdPoint<>;

int compare(const KdPoint<>& p1, const KdPoint<>& p2, int level);
int distance(const KdPoint<>& p1, const KdPoint<>& p2);
int distance(const KdPoint<>& p1, const KdPoint<>& p2, int level);

struct Queue;

struct KdTree
{

	struct KdNode
	{
		int level = 0;
		KdPoint<> point;
		KdNode* left = nullptr;
		KdNode* right = nullptr;
	};

	KdNode* root = nullptr;

	void fill(const std::vector<KdPoint<>> &points);
	KdNode* createTree(const std::vector<KdPoint<>>& points, int level);

	void insert(const KdPoint<>& point);
	KdNode* insert(const KdPoint<>& point, KdNode* node, int level);
	KdNode* search(const KdPoint<>& point);
	KdNode* search(const KdPoint<>& point, KdNode* node);

	KdPoint<> findNearest(const KdPoint<> &target);
	void findNearest(const KdPoint<>& target, KdPoint<> &result, int &distance, KdNode* node);

	std::vector<KdPoint<>> findNearest(const KdPoint<>& target, int k);
	void findNearest(const KdPoint<>& target, Queue& queue, KdNode* node);

	std::vector<KdPoint<>> findNearestByDistance(const KdPoint<>& target, int distance);

	std::vector<KdPoint<>> findNearestByArea(const KdPoint<> &min, const KdPoint<> &max);
	std::vector<KdPoint<>> findNearestByArea(const KdPoint<>& min, const KdPoint<>& max, KdNode* node);
};
