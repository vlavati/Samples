#include "kdtree.h"
#include <algorithm>

using namespace kdtree;

Tree Tree::create(const std::vector<Point> &points)
{
    Tree tree;
    tree.nodes = std::vector<Node>(points.begin(), points.end());
    tree.root = makeTree(tree.nodes, 0, points.size(), 0);
    return tree;
}

std::vector<Point> kdtree::Tree::searchRange(const Point &min, const Point &max)
{
    return searchRange(min, max, root, 0);
}

std::vector<Point> kdtree::Tree::searchRange(const Point & min, const Point & max, NodePtr node, size_t depth)
{
    std::vector<Point> found;
    if (!node)
        return found;
    const int ndim = 2;
    int axis = depth % ndim;
    PointComparer cmp(axis);
    if (cmp(max, node->location))
    {
        auto res = searchRange(min, max, node->leftChild, depth + 1);
        found.insert(found.end(), res.begin(), res.end());
    }
    else if (cmp(node->location, min))
    {
        auto res = searchRange(min, max, node->rightChild, depth + 1);
        found.insert(found.end(), res.begin(), res.end());
    }
    else
    {
        if (min.x <= node->location.x
            && node->location.x <= max.x
            && min.y <= node->location.y
            && node->location.y <= max.y)
            found.push_back(node->location);

        auto res1 = searchRange(min, max, node->leftChild, depth + 1);
        found.insert(found.end(), res1.begin(), res1.end());
        auto res2 = searchRange(min, max, node->rightChild, depth + 1);
        found.insert(found.end(), res2.begin(), res2.end());
    }

    return found;
}

NodePtr Tree::makeTree(std::vector<Node> &nodes, size_t begin, size_t end, size_t depth)
{
    if (end <= begin)
        return nullptr;

    const int ndim = 2;
    int axis = depth % ndim;

    size_t median = begin + (end - begin) / 2;
    std::nth_element(&nodes[begin], &nodes[median], &nodes[0] + end, NodeComparer(axis));

    nodes[median].leftChild = makeTree(nodes, begin, median, depth + 1);
    nodes[median].rightChild = makeTree(nodes, median + 1, end, depth + 1);
    return &nodes[median];
}
