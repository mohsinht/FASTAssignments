#pragma once
#include "singlyLinkedList.h"
#include<fstream>
struct wNode{
	int vertex;
	int weight;
};
class AdjList {
	singlyLinkedList<wNode*>* l;
	int v;
	bool isWeighted;
public:
	AdjList(int n = 0) {
		if (n == 0) {
			v = 0;
			l = nullptr;
		}
		else {
			v = n;
			l = new singlyLinkedList<wNode*>[v];
		}
	}

	bool input(char* fname) {	//takes filename. Returns true if file successfully read and false if not.
		ifstream fin;
		int temp;
		fin.open(fname);
		if (fin.is_open()) {
			fin >> v;	//list size
			fin >> temp;
			if (temp == 0)
				isWeighted = false;
			else
				isWeighted = true;


			l = new singlyLinkedList<wNode*>[v];

			char buff[100];
			fin.getline(buff, 100);
			int i = 0;
			int NUM = 0;
			while (fin.getline(buff, 100)) {
				if (buff[1] == NULL) {
					i++;
					continue;
				}
				int wIn = false;
				for (int k = 1; buff[k] != '\0'; k++)
				{
					if (buff[k] != ',' && buff[k] != '\0' && buff[k]!= ' ') {
						NUM = (NUM) + buff[k] - 48;
						if (buff[k+1] != ',' && buff[k+1] != '\0' && buff[k+1] != ' ') {
							NUM = NUM * 10;
						}
						else {
							if (!isWeighted) { 
								wNode* newNode = new wNode;
								newNode->weight = 0;
								newNode->vertex = NUM;
								l[i].insertAtEnd(newNode);
							}								
							else {
								if(wIn){
									wNode* newNode = new wNode;
									newNode->weight = NUM;
									newNode->vertex = temp;
									l[i].insertAtEnd(newNode);
									wIn = false;
								}
								else {
									wIn = true; 
									temp = NUM;
								}
							}
							NUM = 0;
						}				
					}
				}
				i++;
			}
			
		}
		else {
			return false; //file can't be opened
		}
	}
	void output() {
		ListIterator<wNode*> it;
		cout << "SIZE = " << v << endl;
		cout << "Weighted = ";
		if (isWeighted) {
			cout << "Yes" << endl;
		}else{
			cout << "No" << endl;
		}
		cout << "LIST:-" << endl;
		for (int i = 0; i < v; i++) {
			cout << i << " -> ";
			if (isWeighted) {
				for (it = l[i].Begin(); it != l[i].End(); ++it) {
					cout << "(" << (*it)->vertex << ", "<< (*it)->weight << "), ";
				}
			}
			else {
				for (it = l[i].Begin(); it != l[i].End(); ++it) {
					cout << (*it)->vertex << ", ";
				}
			}
			cout << endl;
		}
	}
	friend bool HamiltonianCycle(AdjList AL);
	friend void hamVisit(AdjList AL, int* sol, int& solSize, int i, bool* visit);
};


bool HamiltonianCycle(AdjList AL) {
	bool* visited = new bool[AL.v];
	for (int i = 0; i < AL.v; i++) {
		visited[i] = false;			// initially no node is visited
	}
	int* sol = new int[AL.v];		// array to store one solution
	sol[0] = 0;						
	int solSize = 1;
	for (int i = 0; i < AL.v; i++) {
		if (!visited[i]) {
			hamVisit(AL, sol, solSize, i, visited);
		}
	}
	if (solSize == AL.v) {			// solution has traversed all nodes
		cout << "Solution: ";
		for (int i = 0; i < AL.v-1; i++) {
			cout << sol[i] << " -> ";
		}
		cout << sol[AL.v - 1] << endl;
		return true;
	}
	else {							// some nodes were skipped
		return false;
	}
}

void hamVisit(AdjList AL, int* sol, int& solSize, int i, bool* visit){
	visit[i] = true;
	ListIterator<wNode*> it;
	for (it = AL.l[i].Begin(); it != AL.l[i].End(); ++it) {		
		if (!visit[(*it)->vertex]) {
			visit[(*it)->vertex] = true;
			sol[solSize] = (*it)->vertex;		// saving path
			solSize++;
			hamVisit(AL, sol, solSize, (*it)->vertex, visit);
		}
		else {
			solSize--;			// path going in a cycle
			return;				// backtrack
		}
	}
}
