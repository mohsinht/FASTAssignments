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
	type getFirst() {
		return s[0];
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
			cout << "";
			for (int i = 0; i < stkptr; i++)
				cout << s[i];
		}
		else {
			cout << "" << endl;
		}
	}
	stack(const stack& st) {
		size = st.size;
		stkptr = st.stkptr;
		s = new type[size];
		for (int i = 0; i < stkptr; i++) {
			s[i] = st.s[i];
		}
	}
	int getSize() {
		return size;
	}
	~stack() {
		delete s;
	}
};

class Cell {
public:
	int row;
	int col;
	Cell() {
		row = 1;
		col = 1;
	}
	void operator=(const Cell& c2) {
		row = c2.row;
		col = c2.col;
	}
	void print() {
		cout << "\t" << row << " => " << col << endl;
	}
	friend ostream& operator<<(ostream& out, const Cell& s);
};

ostream& operator<<(ostream& out, const Cell& s) {
	out << "\t" << s.row << " => " <<  s.col << "\n";
	return out;
}