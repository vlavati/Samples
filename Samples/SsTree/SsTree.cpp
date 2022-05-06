// SsTree.cpp : Defines the entry point for the application.
//

#include "SsTree.h"
#include <iostream>
#include <cassert>
#include <algorithm>
#include <queue>

using namespace std;
int distance(const Point<>& p1, const Point<>& p2);

template<class InputIt, class T>
constexpr
T mean(InputIt first, InputIt last, T init)
{
	size_t cnt = 0;
	for (; first != last; ++first, cnt++) {
		init = std::move(init) + *first;
	}
	return init / cnt;
}

template<class InputIt, class T>
constexpr
T variance(InputIt first, InputIt last, T meanValue, T init)
{
	size_t cnt = 0;
	for (; first != last; ++first, cnt++) {
		T diff = (*first - meanValue);
		init = std::move(init) + diff * diff;
	}
	return init / cnt;
}


template<class InputIt, class T>
constexpr
T variance(InputIt first, InputIt last, T init)
{
	return variance(first, last, mean(first, last, init), init);
}


template <typename Arr1, typename Arr2>
void appendArray(Arr1& dst, Arr2& src)
{
	dst.insert(dst.end(), src.begin(), src.end());
}

int main()
{
	cout << "Hello CMake." << endl;
	SsTree tree;
	/*
	* ----------.+++++++++++
	* ------x---.+++++++++++
	* ----------.+++++++++++
	* ---------T.+x+++++++++
	* ----------x+++++++++++
	* ----------.-----------
	* ----------.+++++++++++
	* ----------.++x++++++++
	* ----------.+++++++++++
	*/


	tree.fill({ {0,1}, {1, 2}, {-4, 4}, {3, -2} });
	tree.insert({ 0, 1 });

	auto p1 = tree.findNearest({ -1, 2 });
	auto ps = tree.findNearest({ -1, 2 }, 2);
	auto psByDistance = tree.findNearestByDistance({ -1, 2 }, 3);
	auto psByArea = tree.findNearestByArea({ -1,0 }, { 3, 3 });

	auto arr = {2, 3, 4, 5};
	auto m = mean(arr.begin(), arr.end(), 0);
	auto v = variance(arr.begin(), arr.end(), m, 0);
	return 0;
}

void SsTree::fill(const std::vector<Point<>>& points)
{
	for (auto p : points)
		insert(p);
}

bool SsTree::contains(const Point<>& point)
{
	return search(point, root) != nullptr;
}

void SsTree::insert(const Point<>& point)
{
	if (root == nullptr)
	{
		auto newNode = new SsNode{};
		newNode->points.push_back(point);
		newNode->center = point;
		newNode->radius = 0;
		root = newNode;
	}
	else
	{
		insert(point, root);

		if (root->size() <= M)
			return;

		auto newRoot = new SsNode{};
		newRoot->nodes.push_back(root);
		newRoot->nodes.push_back(root->split());
		newRoot->recalcCentroids();
		root = newRoot;
	}
}


template <typename QueueT>
void findNearestT(const Point<>& target, QueueT& queue, SsNode* node)
{
	if (node == nullptr)
		return;

	if (node->isLeaf())
	{
		for (auto pt: node->points)
		{
			int dist = distance(target, pt);
			queue.push({ dist, pt });
		}
	}
	else
	{
		std::vector<std::pair<int, SsNode*>> nodes;
		for (auto nd : node->nodes)
		{
			int minimalDist = distance(target, nd->center) - nd->radius;
			nodes.push_back({ minimalDist, nd });
		}

		std::sort(nodes.begin(), nodes.end(), [](auto p1, auto p2) { return p1.first < p2.first; });

		for (auto pr : nodes)
		{
			if (pr.first > queue.top().distance)
				break;

			findNearestT(target, queue, pr.second);
		}
	}
}

namespace
{
	struct QueueItem
	{
		int distance = std::numeric_limits<int>::max();
		Point<> point;
	};

	struct FindMinimal
	{
		QueueItem minimal{};

		void push(QueueItem item)
		{
			if (item.distance < minimal.distance)
				minimal = item;
		}
		QueueItem top() { return minimal; }
		void pop() { minimal.distance = std::numeric_limits<int>::max(); }
		bool empty() { return minimal.distance == std::numeric_limits<int>::max(); }
	};

	struct QueueItemComparer
	{
		bool operator()(const QueueItem& p1, const QueueItem& p2) const { return p1.distance < p2.distance; }
	};

	struct FindKNearest
	{
		std::priority_queue<QueueItem, std::vector<QueueItem>, QueueItemComparer> q;
		int k = 0;

		void push(QueueItem item)
		{
			if (q.size() == k && QueueItemComparer{}(item, q.top()))
				q.pop();

			if (q.size() < k)
				q.push(item);
		}
		QueueItem top() { return q.top(); }
		void pop() { q.pop(); }
		bool empty() { return q.empty(); }
	};

	struct FindByDistance
	{
		std::priority_queue<QueueItem, std::vector<QueueItem>, QueueItemComparer> q;
		int distance = 0;

		void push(QueueItem item)
		{
			if (item.distance < distance)
				q.push(item);
		}
		QueueItem top() { return q.top(); }
		void pop() { q.pop(); }
		bool empty() { return q.empty(); }
	};

}

Point<> SsTree::findNearest(const Point<>& target)
{
	FindMinimal findMinimal{};

	findNearestT(target, findMinimal, root);

	return findMinimal.minimal.point;
}

std::vector<Point<>> SsTree::findNearest(const Point<>& target, int k)
{
	FindKNearest q;
	q.k = k;
	q.push({ std::numeric_limits<Point<>::value_type>::max() , {} });

	findNearestT(target, q, root);

	auto topDistance = q.top().distance;
	if (topDistance == std::numeric_limits<Point<>::value_type>::max())
		q.pop();

	std::vector<Point<>> arr;
	std::vector<QueueItem> list;

	while (!q.empty())
	{
		list.push_back(q.top());
		arr.push_back(q.top().point);
		q.pop();
	}

	return arr;
}

std::vector<Point<>> SsTree::findNearestByDistance(const Point<>& target, int distance)
{
	FindByDistance q;
	q.distance = distance;
	q.q.push({ distance , {} });

	findNearestT(target, q, root);

	q.pop();

	std::vector<Point<>> arr;
	std::vector<QueueItem> list;

	while (!q.empty())
	{
		list.push_back(q.top());
		arr.push_back(q.top().point);
		q.pop();
	}

	return arr;
}

namespace
{
	bool isInside(const Point<>& target, const Point<>& min, const Point<>& max)
	{
		for (int i = 0; i < min.size(); i++)
		{
			if (target[i] < min[i] || max[i] < target[i])
				return false;
		}
		return true;
	}

	struct RectRegion
	{
		Point<> min;
		Point<> max;

		bool contains(const Point<>& point)
		{
			return isInside(point, min, max);
		}

		bool intersects(const Point<>& point, int radius)
		{
			Point<> nearestPointOfBorder;

			for (int i = 0; i < min.size(); i++)
			{
				nearestPointOfBorder[i] = std::clamp(point[i], min[i], max[i]);
			}

			return distance(nearestPointOfBorder, point) < radius;
		}
	};

	template <typename Region>
	std::vector<Point<>> findNearestByRegionT(Region region, SsNode* node)
	{
		std::vector<Point<>> arr;

		if (node->isLeaf())
		{
			for (auto pt : node->points)
			{
				if (region.contains(pt))
					arr.push_back(pt);
			}
		}
		else
		{
			for (auto child : node->nodes)
			{
				if (region.intersects(child->center, child->radius))
					appendArray(arr, findNearestByRegionT(region, child));
			}
		}

		return arr;
	}

}

std::vector<Point<>> SsTree::findNearestByArea(const Point<>& min, const Point<>& max)
{
	if (root == nullptr)
		return {};

	RectRegion region{ min, max };
	std::vector<Point<>> arr;
	appendArray(arr, findNearestByRegionT(region, root));
	return arr;
}


int distance(const Point<>& p1, const Point<>& p2)
{
	int sum = 0;

	for (int i = 0; i < p1.size(); i++)
	{
		int diff = p1[i] - p2[i];
		sum += diff * diff;
	}

	return sqrt(sum);
}

SsNode* SsTree::search(const Point<>& point, SsNode* node)
{
	if (node == nullptr)
		return nullptr;

	if (distance(point, node->center) > node->radius)
		return nullptr;

	if (node->isLeaf())
	{
		for (auto pt : node->points)
		{
			if (pt == point)
				return node;
		}
	}
	else
	{
		for (auto child : node->nodes)
		{
			auto ret = search(point, child);
			if (ret != nullptr)
				return ret;
		}
	}

	return nullptr;
}

SsNode* SsTree::insert(const Point<>& point, SsNode* node)
{
	assert(node != nullptr);

	if (node->isLeaf())
	{
		node->points.push_back(point);
	}
	else
	{
		SsNode* choosen = node->closestNode(point);

		insert(point, choosen);

		if (choosen->size() > M)
		{
			// Split oversized node
			SsNode* newNode = choosen->split();
			node->nodes.push_back(newNode);
		}
	}
	node->recalcCentroids();

	return nullptr;
}

std::vector<Point<>::value_type> selectAxis(const std::vector<Point<>>& points, int axis)
{
	std::vector<Point<>::value_type> values;

	for (auto pt : points)
		values.push_back(pt[axis]);

	return values;
}

void SsNode::recalcCentroids()
{
	center = {};
	radius = 0;

	auto centroids_ = centroids();

	// Mean of points is center
	for (int i = 0; i < center.size(); i++)
	{
		auto values = selectAxis(centroids_, i);
		center[i] = mean(values.begin(), values.end(), 0);
	}

	// Max distance is radius
	for (int ch = 0; ch < size(); ch++)
	{
		auto dist = distance(centroids_[ch], center);

		if (!isLeaf())
			dist += nodes[ch]->radius;

		if (dist > radius)
			radius = dist;
	}
}


int varianceByAxis(const std::vector<Point<>>& points, int axis)
{
	auto values = selectAxis(points, axis);
	int mean_ = mean(values.begin(), values.end(), 0);
	return variance(values.begin(), values.end(), mean_, 0);
}

int maxVarianceAxis(const std::vector<Point<>>& points)
{
	int axis = -1;
	int maxVariance = 0;
	const int k = Point<>{}.size();

	for (int i = 0; i < k; i++)
	{
		int variance_ = varianceByAxis(points, i);
		if (variance_ > maxVariance)
		{
			maxVariance = variance_;
			axis = i;
		}
	}

	return axis;
}

int minVarianceIndex(const std::vector<Point<>::value_type>& values, int m, int M)
{
	int index = -1;
	int minVariance = std::numeric_limits<int>::max();
	const int k = Point<>{}.size();

	for (int i = m; i < values.size() - m; i++)
	{
		int variance1 = variance(values.begin(), values.begin() + i, 0);
		int variance2 = variance(values.begin() + i, values.end(), 0);
		if (variance1 + variance2 < minVariance)
		{
			minVariance = variance1 + variance2;
			index = i;
		}
	}

	return index;
}

SsNode* SsNode::split()
{
	SsNode* newNode = new SsNode;

	// Sort by max variance axis
	int axis = maxVarianceAxis(centroids());
	// Sort 
	if (isLeaf())
	{
		std::sort(points.begin(), points.end(), [axis](auto p1, auto p2) { return p1[axis] < p2[axis]; });
	}
	else
	{
		std::sort(nodes.begin(), nodes.end(), [axis](auto p1, auto p2) { return p1->center[axis] < p2->center[axis]; });
	}
	// Minimize variance of new nodes
	auto values = selectAxis(centroids(), axis);
	int splitIndex = minVarianceIndex(values, SsTree::m, SsTree::M);

	// Split
	if (isLeaf())
	{
		newNode->points.insert(newNode->points.begin(), std::next(points.begin(), splitIndex), points.end());
		points.erase(std::next(points.begin(), splitIndex), points.end());
	}
	else
	{
		newNode->nodes.insert(newNode->nodes.begin(), std::next(nodes.begin(), splitIndex), nodes.end());
		nodes.erase(std::next(nodes.begin(), splitIndex), nodes.end());
	}

	recalcCentroids();
	newNode->recalcCentroids();

	return newNode;
}

std::vector<Point<>> SsNode::centroids() const
{
	if (isLeaf())
		return points;

	std::vector<Point<>> arr;
	for (auto ch : nodes)
		arr.push_back(ch->center);

	return arr;
}

SsNode* SsNode::closestNode(const Point<>& point) const
{
	SsNode* closest = nodes[0];
	int minDist = distance(point, closest->center);

	for (auto child : nodes)
	{
		auto dist = distance(point, child->center);
		if (dist < minDist)
		{
			minDist = dist;
			closest = child;
		}
	}

	return closest;
}

const Point<>& SsNode::centroid(int i) const
{
	if (isLeaf())
		return points[i];

	return nodes[i]->center;
}
