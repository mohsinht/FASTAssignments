#include <iostream>
#include "Header.h"
#include <time.h>
#include <conio.h>
using namespace std;
void main() {
	int n = 0;
	
	while (n <= 0) {
		cout << "Enter Number of Members = ";
		cin >> n;
	}
	cirList l(n); //Creating Circular list from 1 to n members
	cout << "Members: ";
	l.printList();
	char s = 0;
	int i = 0, count = n;
	int start = 0, k = 0;
	while (i < n-1 && s!='q') { //Pressing "q" terminates loop. (For testing only).
		s = getch();
		system("CLS");
		if (i > 0)
			cout << "*Last removed: " << k << endl << endl; 
		cout << "PHASE " << i + 1 << ":" <<  endl;
		cout << "Members: ";
		l.printList();
		srand(time(0));
		int m = (rand() % 10) + 1; //Generates Random number from 1 to 10
		cout << "Bucket is passed " << m << " times." << " | ";
		k = l.MemberAfterStart(start, m); //Stores member at m iterations after starting node 
		int idxOfK = l.getIndex(k); //Stores the last removed member index
		cout << l.MemberAfterStart(0, start) << "->" << k << endl;
		cout << "Bucket is in the hands of " << k << "." << endl;
		start = idxOfK-1;
		l.removeNode(k); //Removing the node
		count--;
		i++;
		cout << endl << "Press a key for next phase.";
	}

	cout <<endl << endl << "===========" << endl << endl;
	cout << "The winner is: " << l.MemberAtIndex(1) << endl;
	cout << endl << "===========" << endl << endl;
}