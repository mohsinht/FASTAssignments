#pragma once
#include <iostream>
#include "stack.h"
using namespace std;


template <class T>
struct AVLnode{
	T data;
	AVLnode* left;
	AVLnode* right;
	int height;
};
template <class T>
class AVLTree{
	AVLnode<T>* root;
public:
	AVLTree() {
		root = nullptr;
	}
	int getHeight(AVLnode<T>* r) {
		if (r == nullptr) {
			return 0;
		}
		else {
			return r->height;
		}
	}
	AVLnode<T>* search(T d) {
		AVLnode<T>* curr = root;
		while (curr != nullptr) {
			if (curr->data == d) {
				return curr;
			}
			else if (curr->data > d) {
				curr = curr->left;
			}
			else {
				curr = curr->right;
			}
		}
		return nullptr;
	}
	void rotToRight(AVLnode<T>*& x) {
		AVLnode<T>* y = x->left;
		x->left = y->right;
		y->right = x;

		x->height = 1 + max(getHeight(x->left), getHeight(x->right));
		y->height = 1 + max(getHeight(y->left), getHeight(y->right));

		x = y;
	}
	void rotToLeft(AVLnode<T>*& x) {
		AVLnode<T>* y = x->right;
		x->right = y->left;
		y->left = x;

		x->height = 1 + max(getHeight(x->left), getHeight(x->right));
		y->height = 1 + max(getHeight(y->left), getHeight(y->right));

		x = y;
	}
	void DRotToRight(AVLnode<T>*& x) {
		rotToLeft(x->left);
		rotToRight(x);
	}
	void DRotToLeft(AVLnode<T>*& x) {
		rotToRight(x->right);
		rotToLeft(x);
	}
	bool insert(T d) {
		if (search(d) != nullptr) {
			return false; //This node already exists in the tree
		}

		AVLnode<T>* temp = new AVLnode<T>;
		temp->height = 1;
		temp->left = temp->right = nullptr;
		temp->data = d;

		if (root == nullptr) {
			root = temp;
		}
		else {
			AVLnode<T>* curr = root;
			stack<AVLnode<T>*> st(200);		//stack of size 200
			st.push(curr);
			bool flag = false; //flag to check whether insertion is done or not.
			while (!flag) {	//keep iterating till the node is successfully inserted
				if (curr == nullptr) {
					st.pop(curr); //popping out the nullptr
					st.top(curr); //getting pointer of parent node where leaf is to be inserted
					if (curr->data > d)
						curr->left = temp;
					else
						curr->right = temp;
					flag = true;	//insertion successful
				}
				else if (curr->data > d) {
					curr = curr->left;
					st.push(curr);
				}
				else if (curr->data < d) {
					curr = curr->right;
					st.push(curr);
				}
			}
			AVLnode<T>* temp;
			while (!st.isEmpty()) {	//backtracking
				st.pop(curr);	
				if (getHeight(curr->left) - getHeight(curr->right) == 2) {
					if (curr->left->data > d) {
						rotToRight(curr);
					}
					else { 
						DRotToRight(curr);
					}
					if (!st.isEmpty()) {	//this condition is handle the dangling pointer.
						st.top(temp);	//^which is lost when root is changed.
						if (temp->data > curr->data) {
							temp->left = curr;
						}
						else {
							temp->right = curr; //fixing dangling pointer
						}
					}
				}
				if (getHeight(curr->left) - getHeight(curr->right) == -2) {
					if (curr->right->data < d) {
						rotToLeft(curr);
					}
					else {
						DRotToLeft(curr);
					}
					if (!st.isEmpty()) {
						st.top(temp);
						if (temp->data > curr->data) {
							temp->left = curr;
						}
						else {
							temp->right = curr; //fixing dangling pointer
						}
					}
				}
				curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
				root = curr;
			}
		}
		return true;
	}

	T max(T a, T b) {
		if (a > b) {
			return a;
		}
		else {
			return b;
		}
	}



	bool Remove(T d) {
		if (search(d) == nullptr) {
			return false;	//no node found with the specified data
		}
		if (root->data == d && root->left == nullptr && root->right == nullptr) { // a root alone is an exception
			delete root;
			root = nullptr;
			return true;
		}
		AVLnode<T>* curr = root;
		stack<AVLnode<T>*> st;
		st.push(curr);
		while (curr->data != d) {
			if (d > curr->data) {
				curr = curr->right;
			}
			else {
				curr = curr->left;
			}
			st.push(curr); //pushing the node to keep track of the path
		}

		AVLnode<T>* parent;
		st.pop(curr);
		st.top(parent);
		if (st.isEmpty()) {
			parent = nullptr;
		}
		if (curr->left == nullptr && curr->right == nullptr && parent != nullptr) {
			if (curr->data < parent->data) { //fixing dangling pointer
				parent->left = nullptr;
			}
			else {
				parent->right = nullptr;
			}		
			delete curr;
			curr = nullptr;
		}
		else if (curr->left != nullptr && curr->right == nullptr && parent != nullptr) {
			if (curr->data < parent->data) {
				parent->left = curr->left;
			}
			else {
				parent->right = curr->left;
			}
			delete curr;
			curr = nullptr;
		}
		else if (curr->left == nullptr && curr->right != nullptr && parent!=nullptr) {
			if (curr->data < parent->data) {
				parent->left = curr->right;
			}
			else {
				parent->right = curr->right;
			}
			delete curr;
			curr = nullptr;
		}
		else {
			curr->data = removePredecessor(curr->left); //swaps node with its predecessor
		}
		if (parent == nullptr) {
			st.push(curr);
		}
		AVLnode<T>* temp;
		while (!st.isEmpty()) {	//backtracking
			st.pop(curr);
			if (getHeight(curr->left) - getHeight(curr->right) == 2) {	//removal taken place in right side
				if (curr->right == nullptr || getHeight(curr->left->left) - getHeight(curr->left->right) >= 0) {
					rotToRight(curr);
				}
				else {
					DRotToRight(curr);
				}
				if (!st.isEmpty()) {
					st.top(temp);
					if (temp->data > curr->data) {
						temp->left = curr;
					}
					else {
						temp->right = curr; //fixing dangling pointer
					}
				}
			}
			else if (getHeight(curr->left) - getHeight(curr->right) == -2) { //removal taken place in left side
				if (curr->left == nullptr || (curr->left->left) - getHeight(curr->left->right) >= 0) {
					rotToLeft(curr);
				}
				else {
					DRotToLeft(curr);
				}
				if (!st.isEmpty()) {
					st.top(temp);
					if (temp->data > curr->data) {
						temp->left = curr;
					}
					else {
						temp->right = curr; //fixing dangling pointer
					}
				}
			}
			curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
			root = curr;
		}
		
		return true;
	}

	T removePredecessor(AVLnode<T>*& r) {	//Utility function to get predecessor value
		AVLnode<T>* child = r;
		while (child->right != nullptr) {
			child = child->right;
		}
		T temp = child->data;
		Remove(temp);
		return temp;
	}

	~AVLTree() {
		AVLnode<T>* curr = root;
		stack<AVLnode<T>*> st(200);
		st.push(curr);
		while (!st.isEmpty() && root!=nullptr) {
			if (curr->left == nullptr && curr->right == nullptr) {
				int temp = curr->data;
				delete curr;
				st.pop(curr);
				curr = nullptr;
				if(!st.isEmpty())
					st.top(curr);
				if (curr!=nullptr && temp < curr->data) {
					curr->left = nullptr;
				}
				else if(curr != nullptr && temp > curr->data){
					curr->right = nullptr;
				}
			}				
			else if (curr->left != nullptr && curr->right == nullptr) {
				curr = curr->left;
				st.push(curr);
			}
			else if (curr->right != nullptr && curr->left == nullptr) {
				curr = curr->right;
				st.push(curr);
			}
			else {
				curr = curr->left;
				st.push(curr);
			}
		}
	}


	void inOrder(AVLnode<T>* r) {	//Recursive
		if (r != nullptr) {
			inOrder(r->left);
			cout << r->data << ", ";
			inOrder(r->right);
		}
		else {
			cout << " ";
			return;
		}
	}
	AVLnode<T>* R() {	//Utility function to access root
		return root;
	}
};