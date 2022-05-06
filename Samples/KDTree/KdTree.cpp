// KDTree.cpp : Defines the entry point for the application.
//

#include "KDTree.h"
#include <iostream>
#include <algorithm>

using namespace std;

void KdTree::fill(const std::vector<KdPoint<>> &points)
{
	root  = createTree(points, 0);
}

KdTree::KdNode* KdTree::createTree(const std::vector<KdPoint<>>& points, int level)
{
	if (points.size() == 0)
		return nullptr;

	if (points.size() == 1)
		return new KdNode{ level, points[0], nullptr, nullptr };

	// Partition
	auto pointsCopy = points;
	std::sort(pointsCopy.begin(), pointsCopy.end(), [level](auto& p1, auto& p2) { int pos = level % p1.size(); return p1[pos] < p2[pos]; });
	auto medianIdx = pointsCopy.size() / 2;
	auto leftBoundIt = std::next(pointsCopy.begin(), medianIdx);
	auto leftTree = createTree({ pointsCopy.begin(), leftBoundIt }, level + 1);
	auto rightBoundIt = std::next(pointsCopy.begin(), medianIdx + 1);
	auto rightTree = createTree({ rightBoundIt, pointsCopy.end() }, level + 1);

	return new KdNode{ level, pointsCopy[medianIdx], leftTree, rightTree };
}

void KdTree::insert(const KdPoint<>& point)
{
	root = insert(point, root, 0);
}

KdTree::KdNode* KdTree::insert(const KdPoint<>& point, KdNode* node, int level)
{
	if (node == nullptr)
		return new KdNode{ level, point, nullptr, nullptr };;

	if (compare(point, node->point, node->level) < 0)
		node->left = insert(point, node->left, node->level + 1);
	else
		node->right = insert(point, node->right, node->level + 1);

	return node;
}

KdTree::KdNode* KdTree::search(const KdPoint<>& point)
{
	return search(point, root);
}

KdTree::KdNode* KdTree::search(const KdPoint<>& point, KdNode* node)
{
	if (node == nullptr)
		return nullptr;

	if (point == node->point)
		return node;

	if (compare(point, node->point, node->level) < 0)
		return search(point, node->left);

	return search(point, node->right);
}

KdPoint<> KdTree::findNearest(const KdPoint<> &target)
{
	int distance = std::numeric_limits<KdPoint<>::value_type>::max();
	KdPoint<> result{};

	findNearest(target, result, distance, root);
	return result;
}

void KdTree::findNearest(const KdPoint<>& target, KdPoint<>& result, int& resdist, KdNode* node)
{
	if (node == nullptr)
		return;

	int dist = distance(target, node->point);
	if (dist < resdist)
	{
		resdist = dist;
		result = node->point;
	}

	KdNode* targetBranch = nullptr;
	KdNode* possibleBranch = nullptr;

	if (compare(target, node->point, node->level) < 0)
	{
		targetBranch = node->left;
		possibleBranch = node->right;
	}
	else
	{
		targetBranch = node->right;
		possibleBranch = node->left;
	}

	findNearest(target, result, resdist, targetBranch);
	if (distance(target, node->point, node->level) < resdist)
		findNearest(target, result, resdist, possibleBranch);
}

#include <queue>


struct QueueItem
{
	int distance;
	KdPoint<> point;
};

struct QueueItemComparer
{
	bool operator()(const QueueItem& p1, const QueueItem& p2) const { return p1.distance < p2.distance; }
};

struct Queue
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

std::vector<KdPoint<>> KdTree::findNearest(const KdPoint<>& target, int k)
{
	Queue q;
	q.k = k;

	q.push({ std::numeric_limits<KdPoint<>::value_type>::max() , {} });

	findNearest(target, q, root);

	auto topDistance = q.top().distance;
	if (topDistance == std::numeric_limits<KdPoint<>::value_type>::max())
		q.pop();

	std::vector<KdPoint<>> arr;
	std::vector<QueueItem> list;

	while (!q.empty())
	{
		list.push_back(q.top());
		arr.push_back(q.top().point);
		q.pop();
	}

	return arr;
}

void KdTree::findNearest(const KdPoint<>& target, Queue& queue, KdNode* node)
{
	if (node == nullptr)
		return;

	int dist = distance(target, node->point);
	queue.push({ dist, node->point });

	KdNode* targetBranch = nullptr;
	KdNode* possibleBranch = nullptr;

	if (compare(target, node->point, node->level) < 0)
	{
		targetBranch = node->left;
		possibleBranch = node->right;
	}
	else
	{
		targetBranch = node->right;
		possibleBranch = node->left;
	}

	findNearest(target, queue, targetBranch);
	if (distance(target, node->point, node->level) < queue.top().distance)
		findNearest(target, queue, possibleBranch);
}

template <typename QueueT>
void findNearestT(const KdPoint<>& target, QueueT& queue, KdTree::KdNode* node)
{
	if (node == nullptr)
		return;

	int dist = distance(target, node->point);
	queue.push({ dist, node->point });

	KdTree::KdNode* targetBranch = nullptr;
	KdTree::KdNode* possibleBranch = nullptr;

	if (compare(target, node->point, node->level) < 0)
	{
		targetBranch = node->left;
		possibleBranch = node->right;
	}
	else
	{
		targetBranch = node->right;
		possibleBranch = node->left;
	}

	findNearestT(target, queue, targetBranch);
	if (distance(target, node->point, node->level) < queue.top().distance)
		findNearestT(target, queue, possibleBranch);
}


struct QueueDistance
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

std::vector<KdPoint<>> KdTree::findNearestByDistance(const KdPoint<>& target, int distance)
{
	QueueDistance q;
	q.distance = distance;

	q.q.push({ distance , {} });

	findNearestT(target, q, root);

	q.pop();

	std::vector<KdPoint<>> arr;
	std::vector<QueueItem> list;

	while (!q.empty())
	{
		list.push_back(q.top());
		arr.push_back(q.top().point);
		q.pop();
	}

	return arr;
}


std::vector<KdPoint<>> KdTree::findNearestByArea(const KdPoint<>& min, const KdPoint<>& max)
{
	return findNearestByArea(min, max, root);
}

bool isInside(const KdPoint<>& target, const KdPoint<>& min, const KdPoint<>& max)
{
	for (int i = 0; i < min.size(); i++)
	{
		if (target[i] < min[i] || max[i] < target[i])
			return false;
	}
	return true;
}

template <typename Arr1, typename Arr2>
void appendArray(Arr1 &dst, Arr2 &src)
{
	dst.insert(dst.end(), src.begin(), src.end());
}

std::vector<KdPoint<>> KdTree::findNearestByArea(const KdPoint<>& min, const KdPoint<>& max, KdNode* node)
{
	if (node == nullptr)
		return {};

	std::vector<KdPoint<>> points;
	if (isInside(node->point, min, max))
		points.push_back(node->point);

	if (compare(min, node->point, node->level) < 0)
		appendArray(points, findNearestByArea(min, max, node->left));

	if (compare(node->point, max, node->level) < 0)
		appendArray(points, findNearestByArea(min, max, node->right));

	return points;
}



int distance(const KdPoint<>& p1, const KdPoint<>& p2)
{
	int sum = 0;

	for (int i = 0; i < p1.size(); i++)
	{
		auto delta = abs(p1[i] - p2[i]);
		sum += delta * delta;
	}

	return sqrt(sum);
}


int distance(const KdPoint<>& p1, const KdPoint<>& p2, int level)
{
	int pos = level % p1.size();

	return abs(p1[pos] - p2[pos]);
}

int compare(const KdPoint<>& p1, const KdPoint<>& p2, int level)
{
	int pos = level % p1.size();

	if (p1[pos] == p2[pos])
		return (level % 2 == 0) ? -1 : +1;

	return p1[pos] - p2[pos];
}
