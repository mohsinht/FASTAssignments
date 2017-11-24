#include "graph.h"

void main() {
	AdjList t;
	t.input("list.txt");
	t.output();
	if (HamiltonianCycle(t)) {
		cout << "YES, There is a solution";
	}
	else {
		cout << "NO! There is no solution";
	}
	cout << endl;
}

