#include "MinHeap.h"

MinHeap::MinHeap() {
	clear();
}
MinHeap::MinHeap(pair<float, string> node) {
	clear();
	heap.at(0) = node;
}
MinHeap::MinHeap(vector<pair<float, string>> nodes) {
	clear();
	insert(nodes);
}

MinHeap::~MinHeap() { clear(); }

bool MinHeap::isEmpty() { return heap.empty(); }
const int& MinHeap::size() { return heap.size(); }
void MinHeap::clear(){
	heap.clear();
}
pair<float, string> MinHeap::pop() {
	pair<float, string> ret = heap.front();
	pair<float, string> last = heap.back();
	heap.at(0) = last;
	heap.erase(heap.end()-1);
	HeapifyDown(0);
	return ret;

}
const pair<float, string>& MinHeap::top() { return heap.front(); }

void MinHeap::insert(vector<pair<float, string>> nodes) {
	for (pair<float, string> i : nodes)
		insert(i);
}
void MinHeap::insert(pair<float, string> node) {
	heap.push_back(node);
	HeapifyUp(&node);
}



void MinHeap::HeapifyDown(int idx) {
	if (heap.empty())
		return;

	int interIdx = idx;
	int left = (2 * idx) + 1;
	int right = (2 * idx) + 2;
	if (left <= heap.size() - 1 && heap.at(left).first < heap.at(interIdx).first)
		interIdx = left;
	if (right <= heap.size() - 1 && heap.at(right).first < heap.at(interIdx).first)
		interIdx = right;
	if (interIdx != idx) {
		pair<float, string> tempInt;
		tempInt = heap.at(idx);
		heap.at(idx) = heap.at(interIdx);
		heap.at(interIdx) = tempInt;
		HeapifyDown(interIdx);
	}
}
void MinHeap::HeapifyUp(pair<float, string>* node) {
	int idx = heap.size() - 1;
	int parent = (idx - 1) / 2;
	while (heap.at(idx).first < heap.at(parent).first) {
		pair<float, string> child_swap = heap.at(idx);
		heap.at(idx) = heap.at(parent);
		heap.at(parent) = child_swap;
		idx = parent;
		parent = (idx - 1) / 2;
	}
}
