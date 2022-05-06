// SsTree.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <array>
#include <vector>

template <typename T = int, int K = 2>
using Point = std::array<T, K>;

struct SsNode
{
	Point<> center;
	int radius = 0;

	std::vector<SsNode*> nodes;
	std::vector<Point<>> points;

	bool isLeaf() const { return points.size() > 0; }
	void recalcCentroids();
	int size() const { return isLeaf() ? points.size() : nodes.size(); }
	SsNode* split();
	std::vector<Point<>> centroids() const;
	SsNode* closestNode(const Point<> &point) const;
	const Point<> & centroid(int i) const;
};


struct SsTree
{
	SsNode* root = nullptr;

	void fill(const std::vector<Point<>>& points);
	bool contains(const Point<>& point);
	void insert(const Point<>& point);
	Point<> findNearest(const Point<>& target);
	std::vector<Point<>> findNearest(const Point<>& target, int k);
	std::vector<Point<>> findNearestByDistance(const Point<>& target, int distance);
	std::vector<Point<>> findNearestByArea(const Point<>& min, const Point<>& max);
	static const int M = 3;
	static const int m = M / 2;
private:
	SsNode* search(const Point<>& point, SsNode *node);
	SsNode* insert(const Point<>& point, SsNode* node);
};
