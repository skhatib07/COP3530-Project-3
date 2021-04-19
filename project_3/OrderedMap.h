#pragma once
#include <vector>
#include "Node.h"

class OrderedMap
{
	Node* root;

	void insert(Node* node, Node* insert, float key);
	Node* RotateLeft(Node* node);
	Node* RotateRight(Node* node);
	void traverseInorder(Node* node, vector<Node*>* traversal);
	void TreeBalance(Node* node);
	void TreeRecolor(Node* node);

public:
	OrderedMap();
	OrderedMap(float key, string val);
	OrderedMap(Node* _root);
	vector<Node*> inorderVector();
	void insert(float key, string val);
	void insert(vector<pair<float, string>> inserts);
};

