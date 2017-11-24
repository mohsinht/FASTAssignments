#pragma once
#pragma once
#include <iostream>
using namespace std;

template <class type>
struct Bnode {
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
	Bnode<type>*& start() {
		return root;
	}
	Bnode<type>* Search(type d) {
		Bnode<type>* temp = Search(root, d);
		return temp;
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
	bool insert(type d) {
		if (Search(root, d) != nullptr) {
			return false;
		}
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
		return true;
	}
	void inOrder() {
		inOrder(root);
	}
	void inOrder(Bnode<type>* r) {
		if (r != nullptr) {
			inOrder(r->left);
			cout << r->data << ", ";
			inOrder(r->right);
		}
		else {
			return;
		}
	}
	void PostOrder() {
		PostOrder(root);
	}
	void PostOrder(Bnode<type>*r) {
		if (r != nullptr) {
			PostOrder(r->left);
			PostOrder(r->right);
			cout << r->data << ", ";
		}
		else {
			return;
		}
	}
	void PreOrder() {
		PreOrder(root);
	}
	void PreOrder(Bnode<type>* r ) {
		if (r != nullptr) {
			cout << r->data << ", ";
			PreOrder(r->left);
			PreOrder(r->right);
		}
		else {
			return;
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
	bool remove(type d) {
		return remove(root, d);
	}
	bool remove(Bnode<type>*& r, type d) {
		if (Search(r, d) == nullptr) {
			return false;
		}
		if (r == nullptr) {
			return false;
		}
		if (r->data == d) {
			if (r->left == r->right) {
				delete r;
				r = nullptr;
				return true;
			}
			Bnode<type>* temp = r;
			if (r->left == nullptr && r->right != nullptr) {
				r = r->right;
				delete temp;
				return true;
			}
			if (r->left != nullptr && r->right == nullptr) {
				r = r->left;
				delete temp;
				return true;
			}
			if (r->left != nullptr && r->right != nullptr) {
				r->data = removePredecessor(root->left);
				return true;
			}
		}
		else {

			if (r->data > d) {
				remove(r->left, d);
			}
			else {
				remove(r->right, d);
			}
		}
	}
	type removePredecessor(Bnode<type>*& r) {
		Bnode<type>* child = r;
		while (child->right != nullptr) {
			child = child->right;
		}
		type temp = child->data;
		remove(r, temp);
		return temp;
	}
};
