#include <iostream>
#include <chrono>

#include "heap.h"

using namespace std;
using namespace chrono;

void print(const vector<int>& v) {
	for (const int& i : v) cout << i << ' ';
	cout << '\n';
}

void test_func() {
	vector<int> v = { 3, 2, 4, 1, 5, 9 };
	vector<int> v2(v);
	vector<int> v3(v);

	cout << "STL Heap\n";
	make_heap(v.begin(), v.end());
	cout << "after make_heap:\n";
	print(v);

	v.push_back(21);
	push_heap(v.begin(), v.end());
	cout << "after push_heap(21):\n";
	print(v);

	Heap h;
	cout << "\nHeap heap\n";
	h.make_heap(v2);
	//int max = h.extract_top_key(v2);
	//cout << "Max: " << max << '\n';
	cout << "after h.make_heap\n";
	print(v2);

	h.insert_key(v2, 21);
	cout << "after h.insert_key(21)\n";
	print(v2);

	h.pop_key(v2, 2);
	cout << "after pop_key(2):\n";
	print(v2);

	h.modify_key(v2, v2.size() - 1, 30);
	cout << "after modify_key(last->30):\n";
	print(v2);

	h.heap_sort(v3);
	cout << "initial vector heap_sort:\n";
	print(v3);
}

void test_rand(int length) {
	vector<int> v(length);
	for (int i = 0; i < v.size(); ++i) {
		v[i] = rand() % 10000 - 5000;
	}
	vector<int> v2(v);

	make_heap(v.begin(), v.end());
	auto start = high_resolution_clock::now();
	sort_heap(v.begin(), v.end());
	auto end = high_resolution_clock::now();

	cout << "TIME\n";
	cout << "sort_heap:\t " << duration_cast<microseconds>(end - start).count() << " us\n";

	Heap heap;
	start = high_resolution_clock::now();
	heap.heap_sort(v2);
	end = high_resolution_clock::now();

	cout << "Heap::heap_sort: " << duration_cast<microseconds>(end - start).count() << " us\n";
}

int main() {
	//test_func();
	test_rand(5000);

	return 0;
}