#pragma once
#include <iostream>
#include <conio.h>
using namespace std;

template <class type>
struct node {
	type data;
	node<type>* next;
};

template <class type>
class listIterator {
public:
	node<type>* curr;

	listIterator(node<type>* n = nullptr) {
		curr = n;
	}
	listIterator& operator++() {
		if (curr != nullptr) {
			curr = curr->next;
		}
		return *this;
	}
	type& operator*() {
		return curr->data;
	}
	bool operator!=(listIterator lit) {
		return !(curr == lit.curr);
	}
};

template <class type>
class list {
	node<type>* head;
public:
	list() {
		head = nullptr;
	}
	void destructlist() {
		node<type>* curr = head;
		node<type>* temp;
		while (curr != nullptr) {
			temp = curr;
			curr = curr->next;
			delete temp;
		}
	}

	listIterator<type> begin() {
		listIterator<type> it(head);
		return it;
	}

	listIterator<type> end() {
		listIterator<type> it; //sets to nullptr in constructor
		return it;
	}

	void insert(listIterator<type>& it, type d) {
		node<type>* temp = new node<type>;
		temp->data = d;
		if (head == nullptr) {
			temp->next = nullptr;
			head = temp;
			it.curr = head;
			return;
		}
		if (it.curr != nullptr) {
			temp->next = it.curr->next;
			it.curr->next = temp;
		}
		/*if (it.curr != nullptr) {
			temp->next = it.curr->next;
			it.curr->next = temp;
		}*/
		else {
			node<type>* curr = head;
			while (curr->next != nullptr) {
				curr = curr->next;
			}
			curr->next = temp;
			temp->next = nullptr;
			it.curr = temp;
		}
	}

	bool isEmpty() {
		return head == nullptr;
	}

	type remove(listIterator<type>& it) {
		type s = *it;
		node<type>* prev = head;
		if (it.curr == head) {
			head = it.curr->next;
			it.curr = it.curr->next;
			delete prev;
			return s;
		}
		if (head !=nullptr && head->next != nullptr) {
			node<type>* curr = head;
			while (curr->data != s) {
				prev = curr;
				curr = curr->next;
			}
			node<type>* temp = it.curr;
			prev->next = it.curr->next;
			it.curr = it.curr->next;
			delete temp;
			return s;
		}
		return s;
	}

	void insertAtStart(type d) {
		node<type>* temp = new node<type>;
		temp->data = d;
		temp->next = head;
		head = temp;
	}

	void removeFromStart() {
		if (head != nullptr) {
			node<type>* temp = head->next;
			delete head;
			head = temp;
		}
	}
};


class block {
public:
	int startSector;
	int endSector;
	int getSize() {
		int size;
		size = (endSector - startSector) + 1;
		return size;
	}
	block(int ss = 0, int es = 0) {
		startSector = ss;
		endSector = es;
	}
	block(const block &b2) {
		startSector = b2.startSector;
		endSector = b2.endSector;
	}
	bool operator!=(block b) {
		if (startSector == b.startSector && endSector == b.endSector) {
			return true;
		}
		return false;
	}
};

class file {
public:
	string name;
	int size;
	list<block> blocks;

	string getName() {
		return name;
	}
	file() {
		name = "\0";
		size = 0;
	}
	file(const file &f2) {
		name = f2.name;
		size = f2.size;
		blocks = f2.blocks;
	}
	void setName(char* ch) {
		for (int i = 0; ch[i] != '\0'; i++) {
			name[i] = ch[i];
		}
	}
	bool operator!=(file fit) {
		if (name == fit.name) {
			return true;
		}
		return false;
	}
};

class FileSystem {
public:
	list<block> pool;
	list<file> files;
	char* disk;
	int numOfSectors;
	int sizeOfSector;

	FileSystem(int Sectors = 100, int Sectorsize = 10) {
		numOfSectors = Sectors;
		sizeOfSector = Sectorsize;
		block b;
		b.startSector = 1;
		b.endSector = numOfSectors;
		pool.insertAtStart(b);
		disk = new char[numOfSectors*sizeOfSector];
		disk[0] = '\0';
	}
	bool SaveFile(string fname, char fcontent[], int fsize) {

		int SecSize = fsize / sizeOfSector;
		if (fsize%sizeOfSector > 0) {
			SecSize++;
		}
		cout << "\tTotal Sectors Occupied: " << SecSize << endl;
		listIterator<file> fit(files.begin());
		for (fit; fit != files.end(); ++fit)
		{
			string ss = (*fit).getName();
			if (fname == ss) { //if name already exists
				return false;
			}
		}

		listIterator<block> bit; //Iterator for pool
		block b;
		int tsz = 0;
		for (bit = pool.begin(); bit != pool.end(); ++bit)
		{
			b = *bit;
			int sz = b.getSize();
			tsz = tsz + sz; //collective size of available sectors in pool
		}
		if ((sizeOfSector*(tsz)) < SecSize*sizeOfSector) {
			return false;
		}
		file f;
		//f.setName(fname);
		f.name = fname;
		f.size = SecSize;

		listIterator<block> pit; //iterator for pool
		listIterator<block> fb(f.blocks.begin());  //iterator for blocks in file
		
		int SizeCount = SecSize; //this tracks the size so that it decrements when one block is allocated in file.

		for (pit = pool.begin(); pit != pool.end() && SizeCount > 0;)
		{
			if ((*pit).getSize() == SizeCount) {
				f.blocks.insert(fb, (*pit));
				pool.remove(pit);
				break;
			}
			else if ((*pit).getSize() < SizeCount) {
				f.blocks.insert(fb, (*pit));
				SizeCount = SizeCount - (*pit).getSize();
				pool.remove(pit);
				++fb;

			}
			else if ((*pit).getSize() > SizeCount) {
				block bn((*pit).startSector, (*pit).startSector + SizeCount - 1);
				f.blocks.insert(fb, bn);
				(*pit).startSector = (*pit).startSector + SizeCount;
				break;
			}
		}

		listIterator<file> ff(files.begin());
		while (ff != files.end()) {
			++ff;
		}
		files.insert(ff, f);

		listIterator<block> fIt(f.blocks.begin());
		int i = 0;
		while (fIt != f.blocks.end()) {
			for (int k = sizeOfSector*((*fIt).startSector-1); k < sizeOfSector*(*fIt).endSector; k++) {
				if (i<fsize) {
					disk[k] = fcontent[i];
				}
				else {
					disk[k] = '_';
				}
				i++;
			}
			++fIt;
		}
		return true;

	}
	file ReadFile(string fname) {
		listIterator<file> fit;
		for (fit = files.begin(); fit != files.end(); ++fit) {
			if ((*fit).name == fname) {
				return *fit;
			}
		}
		file f;
		f.name = "NULL";
		f.size = 0;
		return f;
	}

	bool deleteFile(string fname) {
		listIterator<file> fit; //iterator for files
		listIterator<block> pit(pool.begin()); //iterator for pool
		bool found = false;
		for (fit = files.begin(); fit != files.end(); ++fit) {
			if ((*fit).name == fname) {
				found = true;
				break;
			}
		}
		if (!found) {
			return false;
		}

		listIterator<block> blIt((*fit).blocks.begin()); //iterators for blocks in file

		while (blIt != (*fit).blocks.end()) {
			pool.insert(pit, (*blIt)); //inserting blocks from deleted file to pool
			++blIt;
		}

		files.remove(fit);
		return true;
	}


	~FileSystem() {
		pool.destructlist();
		files.destructlist();
		delete disk;
	}

	void print() {
		cout << "\n\n====================\n\n";
		cout << "\nFAT SYSTEM INFO\n";
		cout << "\tTotal Sectors: " << numOfSectors << endl;
		cout << "\tSize of Each Sector: " << numOfSectors << endl;
		cout << "\t=> Size of Disk: " << numOfSectors*sizeOfSector << endl;
		cout << "\nPOOL (Vacant Blocks): ";
		listIterator<block> pit(pool.begin());
		for (pit; pit != pool.end(); ++pit) {
			cout << "(" << (*pit).startSector << ", " << (*pit).endSector << ") ";
		}
		cout << endl << endl;

		_getch();
		listIterator<file> fit(files.begin());
		cout << "STORED FILES: " << endl;
		for (fit; fit != files.end(); ++fit) {
			cout << "\tFile Name = " << (*fit).name << endl;
			cout << "\tTotal Sectors Occupied = " << (*fit).size << endl;
			listIterator<block> bit((*fit).blocks.begin());
			cout << "\tFile Blocks:  ";
			for (bit; bit != (*fit).blocks.end(); ++bit) {
				cout << "(" << (*bit).startSector << ", " << (*bit).endSector << "), ";
			}
			cout << endl << "\tFile Content: ";
			listIterator<block> fIt2((*fit).blocks.begin());
			while (fIt2 != (*fit).blocks.end()) {
				for (int k = sizeOfSector*((*fIt2).startSector-1); k < sizeOfSector*(*fIt2).endSector && disk[k] != '\0'; k++) {
					cout << disk[k];
				}
				++fIt2;
			}
			cout << endl;
			cout << endl;
		}
		_getch();
		cout << endl;
		cout << "DISK: " << endl;
		cout << "\t{";
		for (int i = 0; i<sizeOfSector*numOfSectors; i++) {
			cout << disk[i] << " ";
		}
		cout << "} " << endl;
		cout << endl;
		cout << "*Disk shows all the data in the array, so there could be some special characters on unoccupied spaces.";
		cout << endl << "*The data of removed files in the array stays there and not removed. However, it can be overwritten." << endl;
		_getch();
	}
};
