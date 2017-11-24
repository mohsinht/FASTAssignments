#include <iostream>
using namespace std;
bool isValid(int row, int* arr, int size);
void printQ(int size, int* arr);
void nQueens(int size, int* arr, int n = 0) {
	if (arr[0] >= size) {
		return;
	}
	if (n < 0) {
		return;
	}
	if (n == size) { // if solution is found
		//for (int i = 0; i < size - 1; i++) {
		//	cout << arr[i] + 1 << ", ";
		//}
		//
		//cout << arr[size - 1] + 1 << endl;
		printQ(size, arr);
		arr[n - 1] = arr[n - 1]++;
		return nQueens(size, arr, n - 1);
	}
	else if (arr[n] >= size) {
		arr[n] = 0;
		arr[n - 1] = arr[n - 1]++;
		return nQueens(size, arr, n - 1);
	}
	else if (isValid(n, arr, size)) {
		return nQueens(size, arr, n + 1);
	}
	else {
		arr[n] = arr[n]++;
		return nQueens(size, arr, n);
	}
}

void main() {
	cout << "Please enter board width = ";
	int n;
	cin >> n;
	cout << n << "x" << n << " Board" << endl;
	cout << "Each line represents a single row. Numbers in each row are column number" << endl;
	cout << "Rows and cols are from 1 to " << n << endl;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		arr[i] = 0;
	}
	nQueens(n, arr);
	delete arr;
}

bool isValid(int row, int* arr, int size) {
	if (row == 0) {
		return true;
	}
	if (row >= size) {
		return false;
	}
	for (int i = row - 1; i >= 0; i--) {
		if (arr[row] == arr[i] ||
			arr[row] - arr[i] == row - i ||
			arr[i] - arr[row] == row - i) {
			return false;
		}
	}
	return true;
}


void printQ(int size, int* arr) {
	cout << "SOLUTION: " << endl << endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < arr[i]; j++) {
			cout << " _ ";
		}
		cout << " Q ";
		for (int j = arr[i]; j < size-1; j++) {
			cout << " _ ";
		}
		cout << endl;
	}
	cout << endl;
}