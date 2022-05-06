// RandomTreap.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <tuple>

template <typename T>
struct TreeNode
{
	TreeNode* parent = nullptr;
	TreeNode* left = nullptr;
	TreeNode* right = nullptr;
	T element;
	TreeNode(T _element) : element(_element) {}
	~TreeNode() { delete left; delete right; }
	void setRight(TreeNode* _right) { right = _right; if (right) right->parent = this; }
	void setLeft(TreeNode* _left) { left = _left; if (left) left->parent = this; }
};

template <typename T,
	typename Prio = double>
struct Treap
{
	using Element = std::tuple<T, Prio>;
	using Node = TreeNode<Element>;
	Node* root = nullptr;
	Treap() = default;
	~Treap();
	Node* search(T value) const;
	void insert(T value, Prio prio);
	void remove(T value);
	void rotateLeft(Node* node);
	void rotateRight(Node* node);
	template <typename F>
	void traverse(F f);
	template <typename F>
	void traverse(Node* node, int level, F f);
};

template<typename T, typename Prio>
inline Treap<T, Prio>::~Treap()
{
	delete root;
}

template<typename T, typename Key>
inline typename Treap<T, Key>::Node* Treap<T, Key>::search(T value) const
{
	auto node = root;
	while (node != nullptr)
	{
		auto &[elValue, prio] = node->element;

		if (elValue == value)
			return node;

		if (value < elValue)
			node = node->left;
		else
			node = node->right;
	}

	return node;
}

template<typename T, typename Prio>
inline void Treap<T, Prio>::insert(T value, Prio prio)
{
	auto newNode = new Node({ value, prio });
	if (root == nullptr)
	{
		root = newNode;
		return;
	}

	// Find parent which leaf should be used to insert new node
	auto node = root;
	Node* parent = nullptr;
	while (node != nullptr)
	{
		auto& [nodeValue, prio] = node->element;
		parent = node;
		if (value < nodeValue)
			node = node->left;
		else
			node = node->right;
	}

	if (value < std::get<0>(parent->element))
		parent->setLeft(newNode);
	else
		parent->setRight(newNode);

	// Fix heap invariant
	while (newNode->parent != nullptr && prio < std::get<1>(newNode->parent->element))
	{
		if (newNode->parent->left == newNode)
			rotateRight(newNode);
		else
			rotateLeft(newNode);
	}

	if (newNode->parent == nullptr)
		root = newNode;
}

template<typename T, typename Prio>
inline void Treap<T, Prio>::remove(T value)
{
	auto node = search(value);
	if (node == nullptr)
		return;

	auto isLeaf = [](auto _node) { return _node->left == nullptr && _node->right == nullptr; };
	if (node == root && isLeaf(node))
	{
		root = nullptr;
		delete node;
		return;
	}

	while (!isLeaf(node))
	{
		if (node->left != nullptr &&
			(node->right == nullptr ||
				std::get<1>(node->left->element) < std::get<1>(node->right->element)))
			rotateRight(node->left);
		else
			rotateLeft(node->right);

		// Root could be updated by rotate on first step
		if (node->parent->parent == nullptr)
			root = node->parent;
	}

	// Cut leaf
	if (node->parent->left == node)
		node->parent->left = nullptr;
	else
		node->parent->right = nullptr;

	delete node;
}

template<typename T, typename Prio>
inline void Treap<T, Prio>::rotateLeft(Node* node) 
{
	auto pushDownParent = node->parent;
	auto grand = pushDownParent->parent;
	if (grand)
	{
		if (grand->left == pushDownParent)
			grand->setLeft(node);
		else
			grand->setRight(node);
	}
	else
	{
		node->parent = nullptr;
	}

	pushDownParent->setRight(node->left);
	node->setLeft(pushDownParent);
}

template<typename T, typename Prio>
inline void Treap<T, Prio>::rotateRight(Node* node)
{
	auto pushDownParent = node->parent;
	auto grand = pushDownParent->parent;
	if (grand)
	{
		if (grand->left == pushDownParent)
			grand->setLeft(node);
		else
			grand->setRight(node);
	}
	else
	{
		node->parent = nullptr;
	}

	pushDownParent->setLeft(node->right);
	node->setRight(pushDownParent);
}

template<typename T, typename Prio>
template<typename F>
inline void Treap<T, Prio>::traverse(F f)
{
	traverse(root, 0, f);
}

template<typename T, typename Prio>
template<typename F>
inline void Treap<T, Prio>::traverse(Node* node, int level, F f)
{
	if (node == nullptr)
		return;

	traverse(node->left, level + 1, f);
	f(level, std::get<0>(node->element), std::get<1>(node->element));
	traverse(node->right, level + 1, f);
}


#include <random>

template <typename T>
struct RandomTreap
{
	Treap<T> treap;
	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen;
	std::uniform_real_distribution<> dis;
	RandomTreap() : gen(rd()), dis(0.0, 1.0) {}
	void insert(T value);
	void remove(T value);
};

template<typename T>
inline void RandomTreap<T>::insert(T value)
{
	treap.insert(value, dis(gen));
}

template<typename T>
inline void RandomTreap<T>::remove(T value)
{
	treap.remove(value);
}
