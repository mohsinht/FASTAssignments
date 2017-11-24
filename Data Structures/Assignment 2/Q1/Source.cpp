#include <iostream>
#include <conio.h>
#include <string>
#include "Header.h"
using namespace std;
void main() {
	int numOfSectors = 100; 
	int sizeOfSector = 10; //Total bytes in a sector


	cout << "FAT System" << endl << endl;
	cout << "\tSize of a Sector: ";
	cin >> sizeOfSector;
	cout << "\tNumber of Sectors: ";
	cin >> numOfSectors;
	char* f = new char[1];
	//cin.getline(f, 1);
	FileSystem fat(numOfSectors, sizeOfSector);
	char sel;
	while (1) {
		system("CLS");
		cout << "FAT System - Menu" << endl << endl;
		cout << "*Size of Sector= " << sizeOfSector << " | *Number of Sectors = "
			<< numOfSectors << " | *Disk Size = " << sizeOfSector*numOfSectors << endl;
		cout << endl << "\t1. Save A File" << endl;
		cout << endl << "\t2. Delete A File" << endl;
		cout << endl << "\t3. Read A File" << endl;
		cout << endl << "\t4. See Disk Data" << endl;
		cout << endl << "\t- Press q to quit" << endl;
		sel = _getch();

		if (sel == '1') {
			system("CLS");
			//char fname[100] = {'\0'};
			//char fcontent[100] = { '\0' };
			char* fname = new char[100];
			char* fcontent = new char[100];
			int size = -1;
			cin.getline(fname, 100);
			cout << "\tEnter Name of File: ";
			cin.getline(fname, 100);
			cout << "\tEnter Content Of File: ";
			//cin >> fcontent;
			cin.getline(fcontent, 100);
			
			while (size <= 0) {
				cout << "\tEnter Size of File: ";
				cin >> size;
			}
			if (fat.SaveFile(fname, fcontent, size)) {
				cout << "\nSUCCESS:";
				cout << endl<< "\tSuccessfully saved \'" << fname << "\' in disk";
				_getch();
			}
			else {
				cout << "\nFAILED:";
				cout << "\n\tSaving file failed! Try again next time!";
				_getch();
			}
		}
		if (sel == '3') {
			system("cls");
			string name;
			cout << "Enter Name of File: ";
			cin >> name;
			file fs;
			fs = fat.ReadFile(name);
			if (fs.name == "NULL") {
				cout << "Sorry No such file found!";
			}
			else {
				cout << endl << "File Found!";
				cout << endl << "\tFile Name: " << fs.name;
				cout << endl << "\tTotal Sectors Occupied: " << fs.size;
				listIterator<block> fIt(fs.blocks.begin());
				cout << endl << "\tFile Blocks: ";
				while (fIt != fs.blocks.end()) {
					cout << "(" << (*fIt).startSector << ", " << (*fIt).endSector << ")  ";
					++fIt;
				}
				cout << endl << "\tFile Content: ";
				listIterator<block> fIt2(fs.blocks.begin());
				while (fIt2 != fs.blocks.end()) {
					for (int k = sizeOfSector*((*fIt2).startSector-1); k < sizeOfSector*(*fIt2).endSector && fat.disk[k]!='\0'; k++) {
						cout << fat.disk[k];
					}
					++fIt2;
				}
				cout << endl;
			}
			_getch();
		}
		if (sel == '2') {
			system("cls");
			string name;
			cout << "Enter Name of File: ";
			//cin.getline(name, 100);
			cin >> name;
			if (fat.deleteFile(name)) {
				cout << name << " has been deleted!" << endl;
			}
			else {
				cout << name << " not found. Deletion not successful!" << endl;
			}
			_getch();
		}
		if (sel == '4') {
			fat.print();
		}
		if (sel == 'q') {
			break;
		}
	}
	cout << endl;
}