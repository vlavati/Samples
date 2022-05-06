#pragma once

#include <vector>
#include <memory>

namespace kdtree {

    struct Point
    {
        double x;
        double y;
        int id;
        double at(size_t axis) const
        {
            return (axis == 0)? x: y;
        }
    };

    struct Node;

    typedef Node* NodePtr;

    struct Node
    {
        Point location;
        NodePtr leftChild;
        NodePtr rightChild;
        Node(const Point& point) : location(point), leftChild(nullptr), rightChild(nullptr) {}
    };

    class Tree
    {
    public:
        Tree() : root(nullptr) {}
        static Tree create(const std::vector<Point> &points);
        std::vector<Point> searchRange(const Point &min, const Point &max);
    private:
        std::vector<Point> searchRange(const Point &min, const Point &max, NodePtr node, size_t depth);
        struct PointComparer
        {
            PointComparer(size_t _axis) : axis(_axis) {}
            bool operator()(const Point& p1, const Point& p2) const
            {
                return p1.at(axis) < p2.at(axis);
            }
            size_t axis;
        };
        struct NodeComparer
        {
            NodeComparer(size_t _axis) : cmp(_axis) {}
            bool operator()(const Node& n1, const Node& n2) const
            {
                return cmp(n1.location, n2.location);
            }
            PointComparer cmp;
        };
        static NodePtr makeTree(std::vector<Node> &nodes, size_t begin, size_t end, size_t depth);
        std::vector<Node> nodes;
        NodePtr root;
    };

}
