#pragma once
#include<vector>
#include<string>

using namespace std;
class Node
{
public:
	float cue;
	vector<pair<float, string>> vals;
	bool red;
	bool black;
	Node* left;
	Node* right;
	Node* parent;

		Node(float key, string _val) {
			cue = key;
			vals.push_back(make_pair(key, _val));
			left = nullptr;
			right = nullptr;
			parent = nullptr;
			red = true;
			black = false;
		}

		Node(float key, string _val, bool _red) {
			cue = key;
			vals.push_back(make_pair(key, _val));
			left = nullptr;
			right = nullptr;
			parent = nullptr;
			red = _red;
			black = !_red;
		}

		Node(float key, string _val, Node* _left, Node* _right, bool _red) {
			cue = key;
			vals.push_back(make_pair(key, _val));
			left = _left;
			right = _right;
			parent = nullptr;
			red = _red;
			black = !_red;
		}

		void MakeBlack() {
			red = false;
			black = true;
		}

		void MakeRed() {
			red = true;
			black = false;
		}

		const int size() { return vals.size(); }

		const pair<float, string> at(int i) { return vals.at(i); }

		const float key() { return cue; }

		void push_back(pair<float, string> in) { vals.push_back(in); }

		Node* getUncle() {
			if (this->parent->parent->left && this->parent->parent->left->key() == parent->key())
				return parent->parent->right;
			else if (this->parent->parent->right && this->parent->parent->right->key() == parent->key())
				return parent->parent->left;
			else
				return nullptr;
		}

		void AssignParent(Node* _parent) {
			if(this && _parent)
				this->parent = _parent;
		}
		
};

