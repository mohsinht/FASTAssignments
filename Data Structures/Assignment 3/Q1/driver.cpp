#include <iostream>
#include "stack.h"
using namespace std;

bool checkTwoCells(Cell c1, Cell c2);
bool checkAllCells(stack<Cell> st, Cell c);
void NQueens(int n) {
	stack<Cell> s(n);
	Cell c1;
	c1.row = 1; 
	c1.col = 1;
	s.push(c1); //Row 1 and Col 1 are assigned to Q1 initially
	Cell temp;
	int i = 2;
	int count = 1;
	while (!s.isEmpty() && s.getFirst().col <= n) {
		if (!s.isFull()) {
			temp.row = i;
			temp.col = 1;
		}
		else
		{
			s.pop(temp);
			temp.col++;
			i--;
		}
		while (!checkAllCells(s, temp)) {
			if (temp.col >= n) {
				temp.col = 1;
				s.pop(temp);
				temp.col++;
				i--;
				while (temp.col > n && !s.isEmpty()) {
					s.pop(temp);
					temp.col++;
					i--;
				}
				if (i < 0)
					i++;
				if (temp.col > n) {
					break;
				}
				continue;
			}
			temp.col++; 
		}
		if (n == 1) {
			temp.col = 1;
		}
		s.push(temp);
		if (temp.row >= n) {
			cout << "Solution " << count << ": \n";
			s.print(); //Printing all the cells of the Queens
			count++;
			cout << endl;
		}
		if (temp.row == 1 && count == 1 && temp.col == n) { //if the row ends and no solution is found
			cout << "No solutions found" << endl;
		}
		if (n == 1) { //1 is an exception, and it must not check the next row
			break;
		}
		i++;
	}
}

void main() {
	int n = 0;
	cout << "Enter Width of Board = ";
	cin >> n;
	while (n <= 0 || n>=16) {
		cout << "Value must be less than 15 and greater than 0" << endl;
		cout << "Enter Width of Board again = ";
		cin >> n;
	}
	cout << "Board is " << n << "x" << n << endl;
	cout << "ROW => COL" << endl << endl;
	NQueens(n);
}


bool checkTwoCells(Cell c1, Cell c2) { //Checks whether two cells are placed at permissible order
	if (c1.col != c2.col && c1.row != c2.row &&
		c1.row - c2.row != c1.col - c2.col &&
		c1.row - c2.row != c2.col - c1.col) {
		return true;
	}
	else {
		return false;
	}
}

bool checkAllCells(stack<Cell> st, Cell c) { //Checks whether a cell is at a permissibile location in the board
	if (c.col > st.getSize()) {
		return false;
	}
	stack<Cell> temp(st);
	Cell tempCell;
	while (!temp.isEmpty()) {
		temp.pop(tempCell);
		if (!checkTwoCells(tempCell, c)) {
			return false;
		}
	}
	return true;
}