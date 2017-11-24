#include <iostream>
#include <Windows.h>
#include <stdlib.h> 
#include <time.h>  
#include <conio.h>
using namespace std;
int* makerect(int size);
void displayrect(int val[], int size);
int* shrinkrect(int val[], int size);
void main()
{
	int n, k, p, r;
	int* val;
	cout << "Enter a number = ";
	cin >> n;
	k = n;
	while (true) {
		val = makerect(k);
		cout << endl;
		Sleep(500);
		for (int s = 0; s < k; s++)
		{
			val[s] = s + 1;
		}
		k = n;
		srand(time(0));
		p = rand() % 3 + 5;
		r = rand() % (2 * k) + 1;
		cout << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
		cout << p << " " << r << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		displayrect(val, k);
		cout << endl;
		k--;
		val = shrinkrect(val, k);
	}
}

int* makerect(int size)
{
	int* arr = new int[size];
	return arr;
}

void displayrect(int val[], int size) {
	for (int h = 0; h < (size / 2)-1; h++)
	{
		cout << val[h] << " ";
	}
	cout << endl;
	cout << val[size-1];
	for (int h = 0; h < (size / 2) - 4; h++)
	{
		cout << "    ";
	}
	cout << val[(size / 2)-1];
	cout << endl;
	for (int h = size-2; h > (size / 2)-1; h--)
	{
		cout << val[h] << " ";
	}
}

int* shrinkrect(int val[], int size)
{
	int* arr = new int[size - 1];
	for (int m = 0; m < size - 1; m++)
	{
		arr[m] = val[m];
	}
	return arr;
}
