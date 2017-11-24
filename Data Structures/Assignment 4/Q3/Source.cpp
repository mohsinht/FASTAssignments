#include<iostream>
#include "bst.h"
using namespace std;
void main() {
	BST<int> b;
	int n = 0;
	while (1) {
		cout << "Insert = ";
		cin >> n;
		if (n == -1) {
			break;
		}
		if (b.insert(n))
			cout << "Done" << endl;
		else {
			cout << "Failed" << endl;
		}
	}
	cout << "Remove = ";
	cin >> n;
	if (b.remove(n)) {
		cout << "Successful";
	}
	else {
		cout << "Unsuccessful";
	}
	cout << endl;
	cout << "Search = ";
	cin >> n;
	Bnode<int>* res = b.Search(n);
	if (res != nullptr) {
		cout << "Successful";
	}
	else {
		cout << "Unsuccessful";
	}
	cout << endl;
	cout << "In Order: " << endl;
	b.inOrder();
	cout << endl;
	cout << "Post Order: " << endl;
	b.PostOrder();
	cout << endl;
	cout << "Pre Order: " << endl;
	b.PreOrder();
	cout << endl;
}