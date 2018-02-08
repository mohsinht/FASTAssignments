/*
Created By: Mohsin Hayat
Roll No. : 16L-4333
Section: CS-E
Submitted To: Sir Sarim Baig
*/


#include <iostream>
#include <Windows.h>
#include <stdlib.h> 
#include <time.h>  
#include <conio.h>
#include <iomanip>
using namespace std;
int* shrink(int* arr, int& k, int i);
int* extend(int* arr, int& k, int n);
void main()
{
	int n, k, p, r, sel, count=0, kill=0, killcount=0;
	cout << "Enter a number = ";
	cin >> n; //Initial Size of the Circle
	int* arr = new int[n]; //Creating new array in heap
	for (int i = 0; i < n; i++)
	{
		arr[i] = i + 1; //storing n-1 numbers in the array
	}
	k = n; //K is counter for heap extension and shrinking
	int cm = 0; //cm is counter to count numbers in reverse direction during clockwise rotation
	srand(time(0));
	r = rand() % (2 * k - 1) + 1; //r is the first kill here
	srand(time(0));
	sel = rand() % n; //Randomly choosing a starting point
	while (k > 1)
	{
		if (k % 2 != 0)
		{
			cout << " "; //These spaces make the rectangle more flexible for odd values of k
		}
		p = rand() % 4 + 5; //p defines the number of iteration after which some new people are added
		for (int i = 0; i < k; i++)
		{
			if (i == sel)
			{
				if (count != r) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1); //blue colour
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //red colour
					kill = i; //saving the index of the person killed
					killcount++; //counting the kills
				}
			}

			if (i < (k/2)-1)
			{
				cout << setw(3);
				cout << arr[i]; //output of first line
				cm = 0;

			}
			else if (i == (k / 2) - 1)
			{
				cout << endl;
				if (sel == k - 1)
				{
					if (count != r) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1); //blue
					}
					else {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //red
						kill = i;
						killcount++;
					}
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //normal
				}
				cout << setw(3);
				cout << arr[k - 1];
				for (int spc = 0; spc < (k/2)-2; spc++)
				{
					cout << "   ";
				}
				if (k <= 4)
				{
					cout << "  ";
				}
				if (k % 2 != 0)
				{
					cout << "  ";
				}
				if (sel == (k/2) - 1)
				{
					if (count != r) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1); //blue
					}
					else {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //red
						kill = (k/2)-1;
						killcount++;
					}
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //normal
				}
				cout << arr[(k/2) - 1];
				cout << endl;
				cm = 0;
			}
			else if(((cm<=(k/2) -1) && (k%2!=0)) || (cm<(k / 2) - 1)) {
				if (sel == k - cm - 2)
				{
					if (count != r) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1); //blue
					}
					else {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //red
						kill = k - cm - 2;
						killcount++;
					}
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //normal
				}
				cout << setw(3);
				cout << arr[k - cm - 2];
				cm++;
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //normal
		}

		if (count == r)
		{
			count = 0;
			srand(time(0));
			r = rand() % (2*k - 1) + 1;
			arr = shrink(arr, k, kill);
			sel = -1;
		}

		if (count == p && killcount < 7)
		{
			arr = extend(arr, k, n);
			p = rand() % 4 + 5;
		}

		cout << endl;
		Sleep(500);
		sel++;
		if (sel == k)
		{
			sel = 0;
		}
		system("CLS");
		count++;
	}
	if (k == 1)
	{
		cout << arr[0] << " is the winner!";
		cout << endl;
	}
	delete[] arr;
}

int* shrink(int* arr, int& k, int i) {
	k = k - 1;
	int j = 0;
	int* arr2 = new int[k];
	for (int q = 0; q < k+1; q++)
	{
		if (arr[q] != arr[i]) {
			arr2[j] = arr[q];
			j++;
		}
	}
	delete[] arr;
	return arr2;
}

int* extend(int* arr, int& k, int n) {
	int q=0, j=0;
	int max, sum;
	srand(time(0));
	q = rand() % (5) + 1;
	j = rand() % k;
	k = k + q;
	int* arr2 = new int[k];
	for (int t = 0; t < k - q; t++)
	{
		sum = 0;
		for (int r = 0; r < k - q; r++)
		{
			if (arr[t] >= arr[r])
			{
				sum++;
			}
		}
		if (sum >= k - q)
		{
			max = arr[t];
			break;
		}
		else
		{
			max = arr[k - q];
		}

	}
	int u = 0;
	for (int i = 0; i < k; i++)
	{
		if (i == j)
		{
			for (int y = 1; y < q+1; y++)
			{
				arr2[i] = max + y;
				i++;
			}
		}
		arr2[i] = arr[u];
		u++;
	}
	delete[] arr;
	return arr2;
}
