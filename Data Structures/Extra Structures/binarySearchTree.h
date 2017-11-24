#pragma once
#include <iostream>
#include <iomanip>  
using namespace std;

template <class type>
struct Bnode{
	type data;
	Bnode* right;
	Bnode* left;
};

template <class type>
class BST {
	Bnode<type>* root;
public:
	BST() {
		root = nullptr;
	}
	Bnode<type>* start() {
		return root;
	}
	Bnode<type>* Search(Bnode<type>* b, type d) {
		if (b == nullptr) {
			return b; //search unsuccessful
		}
		if (d == b->data) {
			return b;
		}
		if (d > b->data) {
			return Search(b->right, d);
		}
		else {
			return Search(b->left, d);
		}
	}
	void insert(type d) {
		Bnode<type>* temp = new Bnode<type>;
		temp->data = d;
		temp->left = temp->right = nullptr;
		if (root == nullptr) {
			root = temp;
		}
		else {
			Bnode<type>* curr = root;
			Bnode<type>* parent = root;
			while (curr != nullptr) {
				parent = curr;
				if (curr->data > d) {
					curr = curr->left;
				}
				else {
					curr = curr->right;
				}
			}
			if (parent->data > d) {
				parent->left = temp;
			}
			else {
				parent->right = temp;
			}
		}
	}
	void insert(type d, Bnode<type>& r) {
		if (r == nullptr) {
			Bnode<type>* temp = new Bnode<type>;
			temp->data = d;
			temp->left = temp->right = nullptr;
			r = temp;
			return;
		}
		else {
			if (r->data > d) {
				insert(d, r->left);
			}
			else {
				insert(d, r->right);
			}
		}
	}
	void printSorted(Bnode<type>* r) {
		if (r != nullptr) {
			printSorted(r->left);
			cout << r->data << ", ";
			printSorted(r->right);
		}
	}
	void destroy(Bnode<type>* r) {
		if (r == nullptr) {
			return;
		}
		destroy(r->left);
		destroy(r->right);
		delete r;
	}
	~BST() {
		destroy(root);
	}

	void remove(Bnode*& root, T d) {
		if (root == nullptr) {
			return;
		}
		if (root->data == d) {
			if (root->left == root->right == nullptr) {
				delete root;
				root = nullptr;
				return;
			}
			Bnode* temp = root;
			if (root->left == nullptr && root->right != nullptr) {
				root = root->right;
				delete temp;
				return;
			}
			if (root->left != nullptr && root->right == nullptr) {
				root = root->left;
				delete temp;
				return;
			}
			if (root->left != nullptr && root->right != nullptr) {
				root->data = removePredecessor(root->left);
				return;
			}
		}
		else {
		
			if (root->data > d) {
				remove(root->left, d);
			}
			else {
				remove(root->right, d);
			}		 
		}
	}
	T removePredecessor(Bnode* r) {
		Bnode* par = r;
		Bnode* child = par->left;
		while (child->right != nullptr) {
			par = child;
			child = child->right;
		}
		T temp = child->data;

		r = child->data;
	}
};
