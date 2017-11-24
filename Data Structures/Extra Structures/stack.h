#pragma once
#include <iostream>
using namespace std;

template <class type>
class stack {
	type* s;
	int stkptr;
	int size;
public:
	stack(int sz = 10) {
		s = new type[sz];
		size = sz;
		stkptr = 0;
	}
	bool isEmpty() {
		return (stkptr == 0);
	}
	bool isFull() {
		return (stkptr == size);
	}
	bool push(type d) {
		if (!isFull()) {
			s[stkptr] = d;
			stkptr++;
			return true;
		}
		else {
			return false;
		}
	}
	bool pop(type& a) { //by reference return the last element
		if(!isEmpty()) {
			stkptr--;
			a = s[stkptr];
			return true;
		}
		else
			return false;
	}
	bool top(type& a) {
		if (!isEmpty()) {
			a = s[stkptr - 1];
			return true;
		}
		else
			return false;
	}
	void print() {
		if (!isEmpty()) {
			cout << "{";
			for (int i = 0; i+1 < stkptr; i++)
				cout << s[i] << ", ";
			cout << s[stkptr - 1] << "}" << endl;
		}
		else {
			cout << "{null}" << endl;
		}
	}
	~stack() {
		delete s;
	}
};