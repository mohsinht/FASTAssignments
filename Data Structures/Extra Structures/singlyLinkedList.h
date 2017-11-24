#pragma once
#include <iostream>
using namespace std;

template <class type>
struct node {
	type data;
	node<type>* next;
};

template <class type>
class ListIterator {
	node<type>* curr;
public:
	ListIterator(node<type>* in = nullptr) {
		curr = in;
	}
	ListIterator& operator++() {
		if(curr!=nullptr)
			curr = curr->next;
		return *this;
	}
	type operator*() {
			return curr->data;
	}
	bool operator!=(ListIterator it) {
		return !(curr == it.curr);
	}
};

template <class type>
class singlyLinkedList {
	node<type>* head;
public:
	singlyLinkedList() {
		head = nullptr;
	}
	void insertAtStart(type d) {
		node<type>* temp = new node<type>;
		temp->data = d;
		temp->next = head;
		head = temp;
	}
	void removeFromStart() {
		if (head != nullptr) {
			node<type>* temp = head;
			head = head->next;
			delete temp;
		}
	}
	void insertAtEnd(type d) {
		node<type>* temp = new node<type>;
		temp->data = d;
		temp->next = nullptr;
		node<type>* curr = head;
		if (head != nullptr) {
			while (curr->next != nullptr) {
				curr = curr->next;
			}
			curr->next = temp;
		}
		else {
			head = temp;
		}
	}

	void removeFromEnd() {
		if (head != nullptr) {
			node<type>* curr = head;
			if (head->next != nullptr) {
				while (curr->next->next != nullptr) {
					curr = curr->next;
				}
				delete curr->next;
				curr->next = nullptr;
			}
			else {
				delete head;
				head = nullptr;
			}
		}
	}

	void remove(type d) {
		if (head != nullptr) {
			node<type>* curr = head;
			node<type>* prev = curr;
			while (curr != nullptr && curr->data != d) {
				prev = curr;
				curr = curr->next;
			}
			if (curr == head) {
				removeFromStart();
				return;
			}
			if (curr != nullptr) {
				prev->next = curr->next;
				delete curr;
			}
		}
	}
	
	void print() {
		if (head == nullptr) {
			cout << "NULL";
			return;
		}
		else {
			node<type>* curr = head;
			cout << "{";
			while (curr->next != nullptr) {
				cout << curr->data << ", ";
				curr = curr->next;
			}
			cout << curr->data << "}" << endl;
		}
	}
	
	ListIterator<type> Begin() {
		ListIterator<type> it(head);
		return it;
	}

	ListIterator<type> End() {
		ListIterator<type> it;
		return it;
	}

	~singlyLinkedList() {
		if (head != nullptr) {
			node<type>* temp;
			node<type>* curr = head;
			
			while (curr != nullptr) {
				temp = curr;
				curr = curr->next;
				delete temp;
			}
		}
	}
};

