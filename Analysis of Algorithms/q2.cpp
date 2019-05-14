#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stack>
using namespace std;

/*
E[i][j] = minimum number of edits while aligning str1[0...i] to str1[0...j]
S[i][j] => -1 for left, 0 for diagonal, 1 for up
*/


vector<vector<int>> E, S;
int p_i = 0, p_d = 0, p_s = 0; //penalties for insert delete and substitute


int editDistance(string s1, string s2, int size_s1, int size_s2) {
	if (size_s1 == 0) {
		return size_s2;
	}
	if (size_s2 == 0) {
		return size_s1;
	}
	if (E[size_s1 - 1][size_s2 - 1] != -1) {
		return E[size_s1 - 1][size_s2 - 1]; //memoization
	}
	if (s1[size_s1 - 1] == s2[size_s2 - 1]) {
		int computedValue = editDistance(s1, s2, size_s1 - 1, size_s2 - 1); //0 penalty for matching
		E[size_s1 - 1][size_s2 - 1] = computedValue;
		return E[size_s1 - 1][size_s2 - 1];
	}

	int c_i = 0, c_d = 0, c_s = 0; //costs for insert delete and substitute

	c_i = p_i + editDistance(s1, s2, size_s1, size_s2 - 1); //insert
	c_d = p_d + editDistance(s1, s2, size_s1 - 1, size_s2); //delete
	c_s = p_s + editDistance(s1, s2, size_s1 - 1, size_s2 - 1); //substitute

	if (c_i < c_s && c_i < c_d) {
		S[size_s1 - 1][size_s2 - 1] = -1;
		E[size_s1 - 1][size_s2 - 1] = c_i;
	}
	else if (c_d < c_i && c_d < c_s) {
		S[size_s1 - 1][size_s2 - 1] = 1;
		E[size_s1 - 1][size_s2 - 1] = c_d;
	}
	else {
		S[size_s1 - 1][size_s2 - 1] = 0;
		E[size_s1 - 1][size_s2 - 1] = c_s;
	}

	return E[size_s1 - 1][size_s2 - 1];
}


void reconstructSolution(string s1, string s2, int min) {
	int min_index = -1;
	for (int i = s1.length() - 1; i >= 0; i--) {
		if (E[i][s2.length() - 1] == min) {
			min_index = i;
			break;
		}
	}

	if (min_index == -1) {
		cout << "Not possible to reconstruct!" << endl;
		return;
	}

	//cout << "minimum distance at "  << min_index << endl;

	stack<char> opt1;
	stack<char> opt2;

	int indOp1 = 0, indOp2 = 0;
	int row = min_index, col = s2.length() - 1;
	while (row >= 0 && col >= 0) {
		if (S[row][col] == 0) { //match
			opt1.push(s1.at(row));
			opt2.push(s2.at(col));
			row--;
			col--;
		}
		else if (S[row][col] == -1) {
			opt1.push('_');
			opt2.push(s2.at(col));
			col--;
		}
		else {
			opt1.push(s1.at(row));
			opt2.push('_');
			row--;
		}
	}

	if (row >= 0) {
		for (int i = row; i >= 0; i--) {
			opt1.push(s1.at(i));
			opt2.push('_');
		}
	}

	if (col >= 0) {
		for (int i = col; i >= 0; i--) {
			opt2.push(s2.at(i));
			opt1.push('_');
		}
	}

	while (!opt1.empty()) {
		cout << opt1.top() << " ";
		opt1.pop();
	}
	cout << endl;
	while (!opt2.empty()) {
		cout << opt2.top() << " ";
		opt2.pop();
	}

	cout << endl;

}

void main() {
	ifstream fin("config.txt");

	while (!fin.eof()) {
		fin >> p_i;
		fin >> p_d;
		fin >> p_s;
	}

	cout << "The penalties are " << p_i << ", " << p_d << " and " << p_s << " for insert, delete and substitute respectively" << endl;

	string string1, string2;
	cout << "Enter String1: ";
	cin >> string1;
	cout << "Enter String2: ";
	cin >> string2;

	cout << "you entered " << string1 << " and " << string2 << endl;
	vector<int> c, b;
	for (int i = 0; i<string1.length(); i++) {
		c.clear();
		b.clear();
		for (int j = 0; j<string2.length(); j++) {
			c.push_back(-1);
			b.push_back(0);
		}
		E.push_back(c);
		S.push_back(b);
	}

	int cost = editDistance(string1, string2, string1.length(), string2.length());

	cout << "Optimal Cost = " << cost << endl;

	reconstructSolution(string1, string2, cost);
}