#include <iostream>	
#include <conio.h>

using namespace std;
struct node {
	//numerator and denominator
	int neu, dem;
	//pointer to next node
	node * next;
};

void genseq(node* &head, node* &tail, int lvl);
void printList(node* head);
void incby1(node* head, int &lvl);
void decby1(node* head, int &lvl);
void nyalvl(node* head, int &lvl, int newlvl);
void remove1(node* head, int key);
void cleanup(node* &head);

void main()
{
	int lvl=0, nlvl=0;
	char sel = '\0';
	node* head = nullptr, *tail = nullptr;
	cout << "Level of Sequence = ";
	cin >> lvl;
	if (lvl > 0) {
		while (1) {
			genseq(head, tail, lvl);
			printList(head);
			cout << "Choose: \n\t1. Generate a new List \n\t2. Increase by 1\n\t3. Decrease by 1\n\t4. Change Level\n\t5. Quit & Clean List\n";
			sel = _getch();
			if (sel < 49 || sel>53)
			{
				system("cls");
				cout << "ERROR! Enter a valid selection";
				getch();
				system("cls");
				continue;
			}
			if (sel == '1')
			{
				cleanup(head);
				cout << "Level of Sequence = ";
				cin >> lvl;
				genseq(head, tail, lvl);
			}
			if (sel == '2')
			{
				cout << "Increase by 1: ";
				incby1(head, lvl);
				printList(head);
				getch();
				system("cls");
				continue;
			}
			if (sel == '3')
			{
				cout << "Decrease by 1: ";
				decby1(head, lvl);
				printList(head);
				getch();
				system("cls");
				continue;
			}
			if (sel == '4')
			{
				cout << "New Level: ";
				cin >> nlvl;
				cout << "List changed to " << nlvl << " from " << lvl << ":";
				nyalvl(head, lvl, nlvl);
				
				printList(head);
				getch();
				system("cls");
				continue;
			}
			if (sel == '5')
			{
				system("cls");
				cout << "Cleaning The list";
				_sleep(400);
				cout << ".";
				_sleep(400);
				cout << ".";
				_sleep(400);
				cout << ".";
				cleanup(head);
				cout << endl;
				cout << "Quiting";
				_sleep(400);
				cout << ".";
				_sleep(400);
				cout << ".";
				_sleep(400);
				cout << ".";
				break;
				
			}
		}
		//cleanup(head);
	}
	else {
		cout << "bad input" << endl;
		getch();
	}
	
}

void genseq(node* &head, node* &tail, int lvl) //Function to generate Farey's Sequence of Level 'lvl'
{
	if (lvl > 0)
	{
		head = new node; tail = new node; //initially an empty list of nodes.
		head->next = tail; tail->next = nullptr;
		head->neu = 0; head->dem = 1;
		tail->neu = 1; tail->dem = 1;
		int dany = 0;
		int i = 0;
		node* curr = head;
		while (dany != lvl && lvl > 1) {
			node* prev = nullptr, *curr = head, *temp = new node;
			while (curr != nullptr)
			{
				prev = curr;
				curr = curr->next;

				if (prev != nullptr && curr != nullptr && (curr->dem + prev->dem <= lvl))
				{
					temp = new node;
					temp->neu = curr->neu + prev->neu;
					temp->dem = curr->dem + prev->dem;
					temp->next = curr;
					prev->next = temp;
					i++;
				}
				dany = temp->dem;
			}
		}
	}
	else {
		cout << "Level must be greater than 0";
	}
}


void printList(node* head) {
	node* curr = head;
	if (head != nullptr)
	{
		cout << endl;
		cout << "Sequence: ";
		while (curr != nullptr)
		{
			cout << curr->neu << "/" << curr->dem;
			if (curr->next != nullptr)
				cout << ", ";
			curr = curr->next;
		}
	}
	cout << endl;
	cout << endl;
}


void incby1(node* head, int &lvl)
{
	int i = 0;
	lvl++;
		node* prev = nullptr, *curr = head, *temp = new node;
		while (curr != nullptr)
		{
			prev = curr;
			curr = curr->next;

			if (prev != nullptr && curr != nullptr && (curr->dem + prev->dem <= lvl))
			{
				temp = new node;
				temp->neu = curr->neu + prev->neu;
				temp->dem = curr->dem + prev->dem;
				temp->next = curr;
				prev->next = temp;
			}
	}
	
}


void decby1(node* head, int &lvl) {
	if (lvl > 1) {
		node* curr = head;
		while (curr != nullptr) {
			remove1(head, lvl);
			curr = curr->next;
		}
		lvl--;
	}
	else
	{
		cout << "ERROR! the sequence level is decreased beyond its range";
		return;
	}
}

void nyalvl(node* head, int &lvl, int newlvl)
{
	if (newlvl < 0)
	{
		cout << "ERROR. You must enter a number greater than 0.";
		return;
	}
	else
	{
		int i = 0;
		if (newlvl > lvl)
		{
			while (lvl!=newlvl)
			{
				incby1(head, lvl);
			}
		}
		else if (newlvl < lvl)
		{
			while (lvl != newlvl)
			{
				decby1(head, lvl);
			}
		}
	}
}


void cleanup(node* &head)
{
	node * temp1 = head;
	node * temp2;

	while (temp1 != NULL)
	{
		temp2 = temp1->next;
		delete temp1;
		temp1 = temp2;
	}
}

void remove1(node* head, int key)
{
	node* prev = nullptr, *curr = head;
	while (curr != nullptr && curr->dem != key)
	{
		prev = curr;
		curr = curr->next;
	}
	if (prev != nullptr && curr != nullptr)
	{
		prev->next = curr->next;
		delete curr;
	}
}