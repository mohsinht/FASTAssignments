#pragma once
#include <iostream>
using namespace std;

struct node {
	int data;
	node* next;
};
class cirList {
	node* head;
public:
	cirList(int n = 0) { //Constructor to create nodes from 1 - n.
		node* prev = nullptr;
		if (n > 0) {
			head = new node;
			head->data = 1;
			head->next = head;
			node* prev = head;
			for (int i = 2; i <= n; i++) {
				node* temp = new node;
				temp->data = i;
				temp->next = head;
				prev->next = temp;
				prev = temp;
			}
		}
		else {
			head = nullptr;
		}
	}
	void printList() { //Prints all the nodes from head to end
		if (head != nullptr) {
			node* curr = head;
			while (curr->next != head) {
				cout << curr->data << ", ";
				curr = curr->next;
			}
			cout << curr->data<< endl;
		}
	}
	void removeNode(int d) { //Delete a node with the data "d"
		if (head != nullptr) {
			node* curr = head->next;
			node* prev = head;
			while (curr != head && curr->data != d) { //searching data
				prev = curr;
				curr = curr->next;
			}
			if (head->data == d) { 
				head = curr->next;
			}
			if (curr->data == d) {
				prev->next = curr->next;
				delete curr;
			}
		}
		if (head->next == head && head->data==d) {
			head = nullptr;
		}
	}
	int MemberAtIndex(int n) { //member at nth position
		if (head != nullptr) {
			node* curr = head;
			int i = 1;
			while (i <= n) {
				curr = curr->next;
				i++;
			}
			return curr->data;
		}
	}
	int MemberAfterStart(int start, int it) { //find member starting from "start" position
		if (head != nullptr) {
			node* curr = head;
			int i = 1;
			while (i <= start) {
				curr = curr->next;
				i++;
			}
			i = 1;
			while (i <= it) {
				curr = curr->next;
				i++;
			}
			return curr->data;
		}

	}
	int getIndex(int d) {	//returns index of the node using data
		if (head != nullptr) {
			node* curr = head;
			int i = 1;
			while (curr->next!=head && curr->data != d) {
				curr = curr->next;
				i++;
			}
			return i;
		}
	}
	~cirList() { //destructor
		node* curr = head->next;
		node* temp;
		while (curr != head)
		{
			temp = curr;
			curr = curr->next;
			delete temp;
		}
	}

};
