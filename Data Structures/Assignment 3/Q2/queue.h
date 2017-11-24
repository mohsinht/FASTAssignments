#pragma once
#include <iostream>
using namespace std;

template <class type>
class queue {
	type* q;
	int start;
	int end;
	int maxsize;
	int size;
public:
	queue(int s = 10) {
		q = new type[s];
		maxsize = s;
		start = -1;
		end = 0;
		size = 0;
	}
	bool isEmpty() {
		if (size == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	bool isFull() {
		return (size == maxsize);
	}
	bool enqueue(type d) {
		if (!isFull()) {
			q[end] = d;
			end++;
			if (end == maxsize) {
				end = 0;
			}
			size++;
			return true;
		}
		else {
			return false;
		}
	}
	bool dequeue(type& d) {
		if (!isEmpty()) {
			d = q[start+1];
			start++;
			size--;
			if (start == maxsize) {
				start = -1;
			}
			return true;
		}
		else {
			return false;
		}
	}
	~queue() {
		delete q;
	}
};
