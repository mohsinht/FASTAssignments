#include<iostream>
#include<conio.h>
#include<fstream>
#include<iomanip>
using namespace std;
void Show(int**arr, int size);
int* make(int* fr, int n, char ch[], int& size);
int** addUser(int** arr, int& size);
int** makefriends(int**arr, int size, bool& check, int f1, int f2);
int** RemoveFriend(int** arr, int size, bool& check, int user, int del);
void savedata(int** arr, int size, char fname[]);
void printFriends(int** arr, int size, int user);
int** DeleteUser(int** arr, int& size, int user);
void FoF(int** arr, int size, int user);
void Mutual(int** arr, int size, int user1, int user2);
void LikelyFriends(int** arr, int size, int user);

void main()
{
	cout << "\t\t\t****CP SOCIAL NETWORK****\n\n";
	int n;
	char fname[] = "friendinfo.txt";
	int numberOfFriends = 0;
	int** arr;
	ifstream fin;
	fin.open(fname);
	if (fin.is_open())
	{
		fin >> n;
		arr = new int*[n];
		char buff[100];
		fin.getline(buff, 100);
		cout << "TOTAL NUMBER OF PEOPLE = " << n << endl;
		cout << "Profiles: " << endl;
		for (int i = 0; i < n; i++)
		{
			arr[i] = new int[1];
			arr[i][0] = -1;
		}
		int i = 0;

		while (fin.getline(buff, 100)) {
			arr[i] = make(arr[i], i, buff, numberOfFriends);
			cout << " |";
				for (int q = 0; q<numberOfFriends; q++)
				{
					cout << setw(3) << arr[i][q] << " |";
				}
				cout<<endl;
			i++;
		}
	}
	int counter = 0;

	_getch();
	cout << endl;

	char sel = '\0';
	while (1) {
		cout << endl;
		cout << "Menu: " << endl;
		cout << "\t1. Add New User" << endl;
		cout << "\t2. Make Friends" << endl;
		cout << "\t3. Remove Friends" << endl;
		cout << "\t4. Remove User" << endl;
		cout << "\t5. Print Friends" << endl;
		cout << "\t6. Print Friends of Friends" << endl;
		cout << "\t7. Print Mutual Friends" << endl;
		cout << "\t8. Print Likely Friends" << endl;
		cout << "\t9. Save" << endl;
		sel = _getch();
		if (sel - 48 < 0 || sel - 48 > 10)
		{
			system("CLS");
			cout << "You must enter a number in the range 0 and 9. \nPress any key to see menu again." << endl;
			_getch();
			Show(arr, n);
			sel = _getch();
		}	
		if (sel == '1')
		{
			system("CLS");
			arr = addUser(arr, n);
			cout << "User " << n-1 << " has been added to the profiles." << endl;
			Show(arr, n);
			sel = _getch();
		}
		if (sel == '2')
		{
			system("CLS");
			cout << "\t\t\t****CP SOCIAL NETWORK****\n\n";
			cout << "MAKE FRIENDS: \n";
			bool check = true;
			int n1 = 0, n2 = 0;
			cout << "Enter First User (0-" << n-1 << ") = ";
			cin >> n1;
			if (n1<0 || n1>n - 1)
				check = false;
			cout << "Enter Second User (0-" << n-1 << ") = ";
			cin >> n2;
			if ((n2 < 0) || (n2 > n - 1) || (n2==n1))
				check = false;
			if(check)
				arr = makefriends(arr, n, check, n1, n2);
			if (!check)
			{
				cout << "ERROR : The friends could not be made." << endl;
			}
			else {
				cout << "SUCCESS: " << n1 << " and " << n2 << " are now friends!" << endl;
			}
			Show(arr, n);
			sel = _getch();
		}
		if (sel == '3')
		{
			system("CLS");
			int user, del;
			bool check = true;
			cout << "\t\t\t****CP SOCIAL NETWORK****\n\n";
			cout << "REMOVE FRIEND: \n";
			cout << "Enter a User (0-" << n - 1 << ") = ";
			cin >> user;
			cout << "Enter Friend You want to Remove = ";
			cin >> del;
			if (user<0 || user>n-1 || user==del)
				check = false;
			arr = RemoveFriend(arr, n, check, user, del);
			if (!check)
			{
				cout << "ERROR : The friend could not be deleted." << endl;
			}
			else {
				cout << "SUCCESS: " << del << " has been deleted from user " << user << "." << endl;
			}
			Show(arr, n);
			sel = _getch();
		}
		if (sel == '4')
		{
			system("CLS");
			int user = 0;
			cout << "\t\t\t****CP SOCIAL NETWORK****\n\n";
			cout << "REMOVE USER: \n";
			cout << "Enter a User (0-" << n - 1 << ") = ";
			cin >> user;
			if (user<0 || user>n - 1)
				cout << "ERROR! Could not delete the user you specified.\n";
			else
				arr = DeleteUser(arr, n, user);
			Show(arr, n);
			sel = _getch();
		}
		if (sel == '5')
		{
			system("CLS");
			int user = 0;
			cout << "Show friends of? ";
			cin >> user;
			if (user<0 || user>n - 1)
				cout << "ERROR! Could not show friends.\n";
			else
				printFriends(arr, n,user);
			cout << endl;
			cout << endl;
			Show(arr, n);
			sel = _getch();
		}
		if (sel == '6')
		{
			system("CLS");
			int user;
			cout << "\t\t\t****CP SOCIAL NETWORK****\n\n";
			cout << "FRIENDS OF FRIENDS:\n";
			cout << "Enter a User (0-" << n - 1 << ") = ";
			cin >> user;
			if (user<0 || user>n - 1)
				cout << "ERROR! Could not show the friends.\n";
			else
				FoF(arr, n, user);
			Show(arr, n);
			sel = _getch();
		}
		if (sel == '7')
		{
			system("CLS");
			cout << "\t\t\t****CP SOCIAL NETWORK****\n\n";
			cout << "MUTUAL FRIENDS: \n";
			bool check = true;
			int n1 = 0, n2 = 0;
			cout << "Enter First User (0-" << n - 1 << ") = ";
			cin >> n1;
			if (n1<0 || n1>n - 1)
				check = false;
			cout << "Enter Second User (0-" << n - 1 << ") = ";
			cin >> n2;
			if ((n2 < 0) || (n2 > n - 1) || (n2 == n1))
				check = false;
			if (!check)
			{
				cout << "ERROR : Can't show mutual friends\n" << endl;
			}
			else
			{
				Mutual(arr, n, n1, n2);
			}
			cout << endl;
			Show(arr, n);
			sel = _getch();
		}
		if (sel == '8')
		{
			system("CLS");
			int user;
			cout << "\t\t\t****CP SOCIAL NETWORK****\n\n";
			cout << "LIKELY FRIENDS:\n";
			cout << "Enter a User (0-" << n - 1 << ") = ";
			cin >> user;
			if (user<0 || user>n - 1)
				cout << "ERROR! Could not show the likely friends.\n";
			else
				LikelyFriends(arr, n, user);
			Show(arr, n);
			sel = _getch();
		}
		if (sel == '9')
		{
			system("CLS");
			cout << "\t\t\t****CP SOCIAL NETWORK****\n\n";
			savedata(arr, n, fname);
			sel = _getch();
		}
	} 
	for (int i = 0; i < n; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
}


int* make(int* fr, int n, char ch[], int& size) {
	int count=0;
	size = 0;

	for (int i = 1; ch[i] != '\0'; i++)
	{
		if(ch[i] != ',')
			size++;
	}

	int* arr2 = new int[size+1];
	arr2[size] = -1;
	int t = 0;
	for (int i = 1; ch[i]!='\0'; i++)
	{
		if (ch[i] != ',')
		{
			arr2[t] = ch[i] - 48;
			t++;
			if (ch[i + 1] != ','&&ch[i+1]!='\0')
			{
				t--;
				arr2[t] = ((ch[i] - 48) * 10) + (ch[i + 1] - 48);
				size--;

				if (ch[i + 2] != ','&&ch[i + 2] != '\0')
				{
					arr2[t] = ((ch[i] - 48) * 100) + ((ch[i + 1] - 48)*10) + (ch[i+2] - 48);
					size--;
					i++;
					t++;
				}
				i++;
				t++;
			}
		}
	}
	cout << n << " has " << size << " friend";
	if (size > 1)
		cout << "s";
	else
		cout << " ";
	cout << " => ";
	delete[] fr;
	return arr2;
}

int** addUser(int** arr, int& size)
{
	int count = 0;
	cout << "\t\t\t****CP SOCIAL NETWORK****\n\n";
	cout << "ADD NEW USER:" << endl;
	cout << endl;
	int** arrnew = new int*[size + 1];
	arrnew[size] = new int[1];
	arrnew[size][0] = -1;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; arr[i][j]!=-1; j++)
		{
			count++;
		}
		arrnew[i] = new int[count+1];
		arrnew[i][count] = -1;
		for (int j = 0; arr[i][j] != -1; j++)
		{
			arrnew[i][j] = arr[i][j];
			
		}
		count = 0;
		delete[] arr[i];
	}
	size = size + 1;
	delete[] arr;
	return arrnew;
}

void Show(int**arr, int size)
{
	int count = 0, friends=0;
	cout << "TOTAL NUMBER OF PEOPLE = " << size << endl;
	cout << "Profiles: " << endl;
	while (count < size) {
		for (int j = 0; arr[count][j] != -1; j++)
		{
			friends++;
		}
		cout << count << " has " << friends << " friend";
		if (friends > 1)
			cout << "s";
		else
			cout << " ";
		if (count <= 9)
			cout << " ";
		cout << " => ";
		cout << " |";

		for (int q = 0; arr[count][q] != -1; q++)
		{
			cout << setw(3) << arr[count][q] << " |";
		}
		cout << endl;
		count++;
		friends = 0;
	}
}

int** makefriends(int**arr, int size, bool& check, int f1, int f2)
{
	int count = 0;
	check = true;
	int** arrnew = new int*[size];

	for (int i = 0; i < size && check; i++)
	{
		for (int j = 0; arr[i][j] != -1 && check; j++)
		{
			if (arr[f2][j] == f1 || arr[f1][j] == f2)
			{
				check = false;
				cout << f1 << " is already a friend with " << f2 << endl;
				return arr;
				break;
			}
		}
	}

	for (int i = 0; i < size && check; i++)
	{
		for (int j = 0; arr[i][j] != -1 && check; j++)
		{
			count++;

		}
		if (i == f1&& check)
		{
			arrnew[i] = new int[count + 2];
			arrnew[i][count] = f2;
			arrnew[i][count+1] = -1;
		}
		else if (i == f2&& check)
		{
			arrnew[i] = new int[count + 2];
			arrnew[i][count] = f1;
			arrnew[i][count+1] = -1;
		}
		else {
			arrnew[i] = new int[count + 1];
			arrnew[i][count] = -1;
		}
		for (int j = 0; j<count&& check; j++)
		{
			arrnew[i][j] = arr[i][j];
		}
		count = 0;
		delete[] arr[i];
	}
	delete[] arr;
	return arrnew;
}

int** RemoveFriend(int** arr, int size, bool& check, int user, int del) {
	int count = 0;
	check = false;
	int** arrnew = new int*[size];

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; arr[i][j] != -1; j++)
		{
			if (arr[user][j] == del)
			{
				check = true;
			}
		}
	}
	if (!check || user==del)
	{
		cout << "The user " << user << " is not a friend with " << del << ".\n";
		delete[] arrnew;
		return arr;
	}
	for (int i = 0; i < size && check; i++)
	{
		for (int j = 0; arr[i][j] != -1 && check; j++)
		{
			count++;
		}
		if ((i == user || i==del) && check)
		{
			arrnew[i] = new int[count];
			arrnew[i][count-1] = -1;
		}
		else {
			arrnew[i] = new int[count + 1];
			arrnew[i][count] = -1;
		}
		int t = 0;
		if (i == user) {
			for (int j = 0; j < count && check;j++)
			{
				if (arr[i][j] != del) {
					arrnew[i][t] = arr[i][j];
					t++;
				}
			}
		}
		else if (i == del) {
			for (int j = 0; j < count && check;j++)
			{
				if (arr[i][j] != user) {
					arrnew[i][t] = arr[i][j];
					t++;
				}
			}
		}
		else {
			for (int j = 0; j < count && check;j++)
			{
					arrnew[i][j] = arr[i][j];
					t++;
			}

		}
		if (i == user) {
			arrnew[user][count - 1] = -1;
		}
		if (i == del) {
			arrnew[del][count - 1] = -1;
		}
		count = 0;
		delete[] arr[i];
	}
	delete[] arr;
	return arrnew;
}

void savedata(int** arr, int size, char fname[]) {
	ofstream fout(fname);
	if (fout.is_open())
	{
		cout << "The data has been saved.\n";
		fout << size;
		fout << endl;
		for (int i = 0; i < size; i++)
		{
			fout << i << ",";
			for (int j = 0; arr[i][j] != -1; j++)
			{
				fout << arr[i][j] << ",";
			}
			fout << endl;
		}
	}
	else {
		cout << "Problem loading the file.\n";
	}
}

void printFriends(int** arr, int size, int user)
{
	int friends = 0;
	for (int j = 0; arr[user][j] != -1; j++)
	{
		friends++;
	}
	cout << user << " has " << friends << " friend";
	if (friends > 1)
		cout << "s";
	else
		cout << " ";
	if (friends <= 9)
		cout << " ";
	cout << " => ";
	cout << " |";

	for (int q = 0; arr[user][q] != -1; q++)
	{
		cout << setw(3) << arr[user][q] << " |";
	}
	cout << endl;
}

int** DeleteUser(int** arr, int& size, int user)
{
	size = size - 1;
	int** arrnew = new int*[size];
	int count = 0, dec=0;
	int t = 0;
	for (int i = 0; i <= size; i++)
	{
		if(i!=user) {
			for (int j = 0; arr[i][j] != -1; j++)
			{
					count++;
					if (arr[i][j] == user)
						count--;
			}
			arrnew[t] = new int[count + 1];
			int p = 0;
			for (int j = 0; j <= count;j++)
			{
				if (arr[i][j] != user) {
					arrnew[t][p] = arr[i][j];
					if(arr[i][j]>user)
						arrnew[t][p] = arr[i][j]-1;
					p++;
				}
			}
			arrnew[t][count] = -1;
			t++;

		}
		count = 0;
	}


	cout << user << " has been successfully removed.\n";
	delete[] arr;
	return arrnew;
}

void FoF(int** arr, int size, int user) {
	int friends = 0;
	for (int j = 0; arr[user][j] != -1; j++)
	{
		friends++;
	}
	if (friends > 0)
	{
		cout << user << " has " << friends << " friend";
		if (friends > 1)
			cout << "s";
		else
			cout << " ";
		cout << endl;
		cout << "FRIENDS OF FRIENDS OF " << user << " : \n";
		for (int p = 0; p < friends; p++)
		{
			printFriends(arr, size, arr[user][p]);
		}
		cout << endl;
	}
	else {
		cout << user << " has no friends.\n";
	}
}

void Mutual(int** arr, int size, int user1, int user2)
{
	int* mut = new int[size];
	mut[size-1] = -1;
	int s = 0;
	for (int i = 0; i < size; i++)
	{
		if (i == user1) {
			for (int j = 0; arr[user1][j] != -1; j++)
			{
				for (int p = 0; arr[user2][p] != -1; p++)
				{
					if (arr[user1][j] == arr[user2][p])
					{
						mut[s] = arr[user1][j];
						s++;
					}
				}
			}
		}
	}
	cout << "Mutual friends of " << user1 << " and " << user2 << " : ";
	for (int i = 0; i < s; i++)
	{
		cout << mut[i] << ", ";
	}
	delete[] mut;

}

void LikelyFriends(int** arr, int size, int user)
{
	int* lf = new int[4];
	lf[4] = -1;
	int s = 0, friends=0;
	for (int i = 0; arr[user][i] != -1; i++)
	{
		friends++;
	}
	bool check = true;
	int c = 0;
	if (friends < 1)
	{
		cout << "You must have at least 1 friend\n ";
	}
	else {
		cout << "Likely friends of " << user << " are: | ";
		for (int i = 0; arr[user][i] != -1 && c<3; i++)
		{
			for (int j = 0; arr[arr[user][i]][j] != -1 && c<4;j++)
			{
				for (int p = 0; p < friends; p++)
				{
					if (arr[arr[user][i]][j] == arr[user][p] || arr[arr[user][i]][j] == user || arr[arr[user][i]][j] == lf[p])
						check = false;
				}
				if (check)
				{
					lf[c] = arr[arr[user][i]][j];
					
					cout << lf[c] << " | ";
					c++;
				}
				check = true;
			}
		
		}
	}
	if (c < 1)
		cout << "NO Likely Friends.";
	cout << endl;
}


