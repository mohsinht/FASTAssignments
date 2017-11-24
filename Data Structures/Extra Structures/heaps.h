#pragma once
#include <iostream>
using namespace std;
class MaxHeap{
	int* arr;
	int maxSize;
	int heapSize;
public:
	MaxHeap(int s = 10) {
		arr = new int[s];
		maxSize = s;
		heapSize = 0;
	}
	int ExtractMax() {
		if (heapSize != 0) {
			int temp = arr[1];
			arr[1] = arr[heapSize];
			MaxHeapify(1);
			return temp;
		}
	}
	void MaxHeapify(int i) {
		if (heapSize != 0) {
			int left = 2 * i;
			int right = left + 1;
			int max = i;
			if (left <= heapSize && arr[left] > arr[max]) {
				max = left;
			}
			if (right <= heapSize && arr[right] > arr[max]) {
				max = right;
			}
			if (max != i) {
				int temp = arr[i];
				arr[i] = arr[max];
				arr[max] = temp;
				MaxHeapify(max);
			}
		}
	}
	void insert(int d) {
		heapSize++;
		arr[heapSize] = d;
		int i = heapSize;
		while (i > 1 && arr[i] > arr[i / 2]) {
			int temp = arr[i];
			arr[i] = arr[i/2];
			arr[i/2] = temp;
			i = i / 2;
		}
	}
	void print() {
		cout << "{";
		for (int i = 1; i < heapSize-1; i++) {
			cout << arr[i] << ", ";
		}
		cout << arr[heapSize - 1] << "}" << endl;
	}
};