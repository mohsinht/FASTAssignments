#include <iostream>
#include "queue.h"
#include "sets.h"
#include <math.h>
using namespace std;

void allSubsets(int n) {
	int numOfSubsets = pow(2,n);
	cout << "Total Subsets must be " << numOfSubsets << endl;
	cout << "\nSUBSETS:\n";
	cout << "{}" << endl; //null set
	queue<Set> q(numOfSubsets);
	Set s;
	s.Add(1);
	q.enqueue(s);
	while (!q.isEmpty()){
			q.dequeue(s);
			s.output();
		if (s.getLast() < n) {
			Set r(s);
			r.Remove();
			r.Add(s.getLast() + 1);
			q.enqueue(r);
			s.Add(s.getLast() + 1);
			q.enqueue(s);
		}
	}

	while (!q.isEmpty()) {
		q.dequeue(s);
		if (!q.isEmpty())
			s.output();
	}
	s.destroySet();
}

void main() {
	int n;
	cout << "Enter Number of Elements in Set: ";
	cin >> n;
	while (n < 1) {
		cout << "Number must be greater than 1" << endl;
		cout << "Num of Elements: ";
		cin >> n;
	}
	allSubsets(n);
}