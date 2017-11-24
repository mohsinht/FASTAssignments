#include <iostream>
#include <conio.h>
#include "AVLTree.h"
using namespace std;
void main() {
	AVLTree<int> avl;
	int n = 0;

	char sel;

	while (1) {
		system("CLS");
		cout << "1.\tINSERTION\n2.\tDELETION\n3.\tSEARCH\n4.\tPRINT\n0.\tEXIT"<<endl;
		sel = _getch();
		if (sel == '0') {
			break;
		}
		if (sel == '1') {
			cout << endl << "Keep Entering numbers (Enter -1 to terminate)." << endl;
			while (n != -1) {
				cin >> n;
				if (n != -1) {
					if (avl.insert(n)) {
						cout << "Success" << endl;
					}
					else {
						cout << "Failed" << endl;
					}
				}
			}
		}
		if (sel == '2') {
			cout << endl << "Enter a number to remove = ";
			cin >> n;
			if (avl.Remove(n)) {
				cout << "Success" << endl;
			}
			else {
				cout << "Failed" << endl;
			}
			getch();
		}
		if (sel == '3') {
			cout << endl << "Search = ";
			cin >> n;
			if (avl.search(n) != nullptr) {
				cout << "Found" << endl;
			}
			else {
				cout << "NOT Found" << endl;
			}
			getch();
		}
		if (sel == '4') {
			cout << endl << "Nodes Inorder = ";
			avl.inOrder(avl.R());
			getch();
		}
	}

}