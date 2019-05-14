//#include <set>
//#include <string>
//#include <fstream>
//#include <iostream>
//#include <stack>
//
//using namespace std;
//class lex {
//	set <string> base;
//public:
//	lex(string filepath) {
//		ifstream ifile(filepath);
//		char buff[1000];
//		while (ifile.getline(buff, 999)) {
//			string b = buff;
//			b.resize(b.size() - 1);
//			base.insert(b);
//		}
//		ifile.close();
//	}
//	bool isword(string s) {
//		if (s.length() <= 1) {
//			return false;
//		}
//		return (base.count(s)>0);
//	}
//};
//
//
////sample, how to use
//int main() {
//	lex l("lex.txt");
//	string inp;
//	cout << "Enter a string: ";
//	cin >> inp;
//	cout << "your input is " << inp << endl;
//	int* E = new int[inp.length()+1];
//	int* S = new int[inp.length()+1];
//	for (int i = 0; i < inp.length(); i++){
//		E[i] = 0; S[i] = 0;
//	}
//	/*
//		E[k] = 1 if valid string exists from inp[0] to inp[k-1], 0 otherwise
//		S[k] = index where last word started. S[0] = 0.
//	*/
//
//	string m;
//	for (int i = 0; i < inp.length(); i++) {
//		int j = i;
//		while(j >= 1) {
//			if (l.isword(inp.substr(j, i - j + 1))) { //picks a word from arr[j] to arr[j+i]
//				if (S[j] != -1) {  //if not already marked
//					E[i] = 1;
//					S[i] = j;	//mark the starting index
//				}
//			}
//			else {
//				if (S[i] == -2)
//					S[i] = -1;
//			}
//			j--;
//		}
//	}
//
//	if (E[inp.length()-1] != 1) {
//		cout << "NOT Possible!" << endl;
//	}
//	else {
//		cout << "Split is possible!" << endl;
//	}
//
//	for (int i = 0; i < inp.length(); i++) {
//		cout << i << ". " << inp.at(i) << "  E="; cout << E[i]; cout << "   S=" << S[i] << endl;
//	}
//	
//	int g = inp.length()-1;
//	stack<string> mystack;
//	while (true) {
//		string buf = inp.substr(S[g], g-S[g]+1);
//		mystack.push(buf);
//		if (S[g] <= 0) {
//			break;
//		}
//		g = S[g] - 1;
//	}
//	cout << "Split Result: " << endl;
//	while (!mystack.empty()) {
//		cout << mystack.top() << " ";
//		mystack.pop();
//	}
//}
//
//
//
