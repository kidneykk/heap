#ifndef HEAP_H_
#define HEAP_H_

#include <vector>
using std::vector;

#include <algorithm>
#include <iostream>

using std::swap;
using std::less;
using std::greater;
using std::size_t;
using std::cerr;

class Heap {
private:
	int heap_size = 0;

	constexpr int PARENT(int i) { return (i - 1) / 2; }
	constexpr int LEFT_CHILD(int i) { return 2 * i + 1; }
	constexpr int RIGHT_CHILD(int i) { return 2 * i + 2; }

	template<class T, class Compare>
	constexpr void heapify(vector<T>& heap, int i, Compare comp);
	
public:
	template<class T, class Compare>
	constexpr void make_heap(vector<T>& heap, Compare comp);

	template<class T>
	constexpr void make_heap(vector<T>& heap);

	template<class T, class Compare>
	constexpr void heap_sort(vector<T>& heap, Compare comp);

	template<class T>
	constexpr void heap_sort(vector<T>& heap);

	template<class T, class Compare>
	constexpr T extract_top_key(vector<T>& heap, Compare comp);

	template<class T>
	constexpr T extract_top_key(vector<T>& heap);

	template<class T, class Compare>
	constexpr void modify_key(vector<T>& heap, int pos, T key, Compare comp);

	template<class T>
	constexpr void modify_key(vector<T>& heap, int pos, T key);

	template<class T, class Compare>
	constexpr void insert_key(vector<T>& heap, T key, Compare comp);

	template<class T>
	constexpr void insert_key(vector<T>& heap, T key);

	template<class T, class Compare>
	constexpr void pop_key(vector<T>& heap, int pos, Compare comp);

	template<class T>
	constexpr void pop_key(vector<T>& heap, int pos);
};

template<class T, class Compare>
constexpr void Heap::heapify(vector<T>& heap, int i, Compare comp)
{
	int largest = i;
	int left	= LEFT_CHILD(i);
	int right	= RIGHT_CHILD(i);

	if (left < heap_size && comp(heap[left], heap[i])) {
		largest = left;
	}

	if (right < heap_size && comp(heap[right], heap[largest])) {
		largest = right;
	}

	if (largest != i) {
		swap(heap[i], heap[largest]);
		heapify(heap, largest, comp);
	}
}

template<class T, class Compare>
constexpr void Heap::make_heap(vector<T>& heap, Compare comp)
{
	// O(n)
	heap_size = heap.size();
	for (int i = heap.size() / 2 - 1; i >= 0; --i) {
		heapify(heap, i, comp);
	}
}

template<class T>
constexpr void Heap::make_heap(vector<T>& heap)
{
	Heap::make_heap(heap, greater<T>());
}

template<class T, class Compare>
constexpr void Heap::heap_sort(vector<T>& heap, Compare comp)
{
	// O(nlogn)
	Heap::make_heap(heap, comp);
	for (size_t i = heap.size() - 1; i >= 1; --i) {
		swap(heap[0], heap[i]);
		heap_size--;
		heapify(heap, 0, comp);
	}
}

template<class T>
constexpr void Heap::heap_sort(vector<T>& heap)
{
	heap_sort(heap, greater<T>());
}

template<class T, class Compare>
constexpr T Heap::extract_top_key(vector<T>& heap, Compare comp)
{
	// O(logn)
	if (heap_size < 1) {
		cerr << "The queue is empty\n";
		return -1;
	}

	T max = heap[0];
	swap(heap[0], heap[heap_size - 1]);
	heap_size--;
	heapify(heap, 0, comp);

	return max;
}

template<class T>
constexpr T Heap::extract_top_key(vector<T>& heap)
{
	return extract_top_key(heap, greater<T>());
}

template<class T, class Compare>
constexpr void Heap::modify_key(vector<T>& heap, int pos, T key, Compare comp)
{
	// O(logn)
	if (comp(key, heap[pos])) {
		cerr << "New key is greater or less than current\n"; // ??
		return;
	}

	while (pos > 0 && comp(heap[PARENT(pos)], key)) {
		heap[pos] = heap[PARENT(pos)];
		pos = PARENT(pos);
	}
	heap[pos] = key;
}

template<class T>
constexpr void Heap::modify_key(vector<T>& heap, int pos, T key)
{
	modify_key(heap, pos, key, less<T>());
}

template<class T, class Compare>
constexpr void Heap::insert_key(vector<T>& heap, T key, Compare comp)
{
	heap_size++;
	heap.push_back(key);
	modify_key(heap, heap_size - 1, key, comp);
}


template<class T>
constexpr void Heap::insert_key(vector<T>& heap, T key)
{
	insert_key(heap, key, less<T>());
}

template<class T, class Compare>
constexpr void Heap::pop_key(vector<T>& heap, int pos, Compare comp)
{
	swap(heap[pos], heap[heap_size - 1]);
	heap_size--;
	heapify(heap, 0, comp);
}

template<class T>
constexpr void Heap::pop_key(vector<T>& heap, int pos)
{
	pop_key(heap, pos, greater<T>());
}

#endif