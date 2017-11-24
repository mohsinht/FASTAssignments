#include <iostream>
#include "stack.h"
#include <conio.h>
using namespace std;

bool checkAllRows(int arr[], int c, int n, int size); //n is total board rows while size is the number of rows which are filled
bool addPermissibleCol(int arr[], int& c, int n, int size); //c1 is a column and c2 is the column preceeding it. n is total cols in a board.
bool checkCol(int c1, int r1, int c2, int r2); //checks whether a col is valid or not

void NQueen(int n) {
	int* sol = new int[n];
	for (int i = 0; i < n; i++) {
		sol[i] = 0;
	}
	stack<int> s(n);
	int row = 0;
	int col = 0;
	sol[row] = col; //starting with placement at 1st row, 1st column
	s.push(sol[row]);
	bool check = false;
	int total = n;
	int prevVal = -1;
	int k = 1;

	int i = 1;
	cout << "ADDED: Row" << i<< " => col" << sol[i] + 1 << endl;
	int temp;
	while (i < n) {
		if (s.isEmpty()) {
			sol[i] = k;
			cout << "ADDED: Row" << i + 1 << " => col" << sol[i] + 1 << endl;
			k++;
			s.push(sol[i]);
		}
		else if (addPermissibleCol(sol, sol[i], n, i)) {
			s.push(sol[i]);
			cout << "ADDED: Row" << i + 1 << " => col" << sol[i] + 1 << endl;
		}
		else {
			s.pop(sol[i]);
			if(i<n-1)
				sol[i + 1] = -1;
			cout << "REMOVED: Row" << i << " => col" << sol[i] + 1 << endl; 
			i -= 2;
		}
		_getch();
		i++;
	}

	for (int i = 0; i < n; i++) {
		cout << "Row" << i + 1 << " => Col" << sol[i] + 1 << endl;
	} 

	delete[] sol;
}

void main() {
	NQueen(6);
}

/*
- addPermissibleCol() function returns true if there is some column available
- returns false if there's no column permissible in the row
*/


bool addPermissibleCol(int arr[], int& c, int n, int size) {
	int count = 0;
	if (c == n - 1) {
		c = 0;
		return false;
	}
	for (int i = c+1; i <= n+1; i++) {
		i = i%n;

		if (checkAllRows(arr, i, n, size)) {
			c = i;
			return true;
		}
		else {
			count++;
		}
		if (count == n-1) {
			return false;
		}
	}
	return false;
}

bool checkAllRows(int arr[], int c, int n, int size) {
	for (int i = size-1; i >= 0; i--) {
		if (!checkCol(arr[i], i, c, size)) {
			return false;
		}
	}
	return true;
}

bool checkCol(int c1, int r1, int c2, int r2) {
	if (c2 != c1 && r2-r1 != c2-c1 && r2-r1 != c1-c2) {
			return true;
	}
	else 
		return false;
}