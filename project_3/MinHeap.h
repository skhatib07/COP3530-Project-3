#pragma once
#include <vector>
#include <string>

using namespace std;
class MinHeap
{
	vector<pair<float,string>> heap;

	void HeapifyUp(pair<float, string>* node);
	void HeapifyDown(int idx);

	public:
		MinHeap();
		MinHeap(pair<float,string> node);
		MinHeap(vector<pair<float,string>> nodes);
		~MinHeap();

		bool isEmpty();
		const int& size();
		void clear();

		const pair<float, string>& top();
		pair<float, string> pop();

		void insert(vector<pair<float,string>> nodes);
		void insert(pair<float,string>);
};

