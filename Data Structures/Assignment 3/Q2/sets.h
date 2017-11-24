#pragma once
#include <iostream>
#include "queue.h"
using namespace std;

int*& extendArray(int* arr, int& size) {
	size++;
	int* temp = new int[size];
	for (int i = 0; i < size-1; i++) {
		temp[i] = arr[i];
	}
	if(arr!=nullptr)
		delete arr;
	return temp;
}

int*& shrinkArray(int* arr, int& size) {
	size--;
	int* temp = new int[size];
	for (int i = 0; i < size; i++) {
		temp[i] = arr[i];
	}
	delete arr;
	return temp;
}



class Set {
	int* arr;
	int size;
public:
	Set(int s=0) {
		arr = new int[s];
		size = s;
	}
	void output() {
		cout << "{";
		for (int i = 0; i < size-1; i++) {
			cout << arr[i] << ", ";
		}
		cout << arr[size-1] << "}" << endl;
	}
	void Add(int x) {
		arr = extendArray(arr, size);
		arr[size - 1] = x;
	}
	void Remove() {
		if (size > 0)
			arr = shrinkArray(arr, size);
		else {
			arr[0] = 0;
			size = 0;
		}
	}
	int getLast() {
		if (size > 0) {
			return arr[size - 1];
		}
	}
	void destroySet() {
		if(size>0 && arr!=nullptr)
			delete arr;
	}
	Set(const Set &s){
		size = s.size;
		if (s.arr != nullptr) {
			arr = new int[size];
			for (int i = 0; i < size; i++) {
				arr[i] = s.arr[i];
			}
		}
	}
};

