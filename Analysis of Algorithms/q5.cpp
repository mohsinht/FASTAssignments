//#include <iostream>
//#include <string>
//#include <stack>
//using namespace std;
//
//int* C; //1 for '(', -1 for ')' and 0 for no brackets
//
//char computeStaric(char a, char b) { //computes the given operator
//	if (a == 'x') {
//		if (b == 'x')
//			return 'y';
//		if (b == 'y')
//			return 'y';
//		if (b == 'z')
//			return 'x';
//	}
//	if (a == 'y') {
//		if (b == 'x')
//			return 'z';
//		if (b == 'y')
//			return 'y';
//		if (b == 'z')
//			return 'x';
//	}
//	if (a == 'z') {
//		if (b == 'x')
//			return 'x';
//		if (b == 'y')
//			return 'z';
//		if (b == 'z')
//			return 'z';
//	}
//
//	return '-';
//}
//
//string bracketing = "(";
//
//char findBrackets(string inp, char r, int index) {
//	if (inp.length() == 1) {
//		if (inp[0] == r) {
//			string s(1, inp[0]);
//			bracketing.append("*");
//			bracketing.append(s);
//			C[index] = 1;
//			C[index+1] = 1;
//			return inp[0];
//		}
//		else {
//			return '-';
//		}
//	}
//	if (inp.length() == 2) {
//		if (computeStaric(inp[0], inp[1]) == r) {
//			string s1(1, inp[0]);
//			string s2(1, inp[1]);
//			bracketing.append("*(");
//			bracketing.append(s1);
//			bracketing.append("*");
//			bracketing.append(s2);
//			bracketing.append(")");
//			C[index] = 1;
//			C[index+2] = -1;
//			return r;
//		}
//		else {
//			return '-'; //if desired output not found.
//		}
//	}
//	int size = inp.length();
//	char res = '-';
//
//	int cut = 1;
//	while (res == '-' && cut < inp.length()-1) {
//		if (r == 'x') {
//			res = computeStaric(findBrackets(inp.substr(0, cut), 'y', index), findBrackets(inp.substr(cut, size), 'z', index + cut));
//			if (res == '-') {//if not possible
//				res = computeStaric(findBrackets(inp.substr(0, cut), 'x', index), findBrackets(inp.substr((cut), size), 'z', index + cut));
//			}
//			if (res == '-') {//if not possible
//				res = computeStaric(findBrackets(inp.substr(0, cut), 'z', index), findBrackets(inp.substr((cut), size), 'x', index + cut));
//			}
//		}
//		if (r == 'y') {
//			res = computeStaric(findBrackets(inp.substr(0, cut), 'x', index), findBrackets(inp.substr((cut), size), 'y', index + cut));
//			if (res == '-') {//if not possible
//				res = computeStaric(findBrackets(inp.substr(0, cut), 'x', index), findBrackets(inp.substr((cut), size), 'x', index + cut));
//			}
//			if (res == '-') {//if not possible
//				res = computeStaric(findBrackets(inp.substr(0, cut), 'y', index), findBrackets(inp.substr((cut), size), 'y', index + cut));
//			}
//
//		}
//		if (r == 'z') {
//			res = computeStaric(findBrackets(inp.substr(0, cut), 'z', index), findBrackets(inp.substr((cut), size), 'y', index + cut));
//			if (res == '-') {//if not possible
//				res = computeStaric(findBrackets(inp.substr(0, cut), 'y', index), findBrackets(inp.substr((cut), size), 'x', index + cut));
//			}
//			if (res == '-') {//if not possible
//				res = computeStaric(findBrackets(inp.substr(0, cut), 'z', index), findBrackets(inp.substr((cut), size), 'z', index + cut));
//			}
//		}
//		cut++;
//	}
//	if (res != '-') {
//		//C[index] = -1;
//	}
//	return res;
//}
//
//void reconstruct(string inp) {
//	stack<int> opt1;
//	for (int i = 0; i <= inp.length(); i++) {
//		if (C[i] == -1) {
//			while (!opt1.empty()) {
//				cout << ")";
//				opt1.pop();
//			}
//		}
//		if (C[i] == 1) {
//			cout << "(";
//			opt1.push(1);
//		}
//		if(i<inp.length())
//			cout << inp.at(i);
//	}
//}
//
//void main() {
//	string inp;
//	cout << "Enter String: ";
//	cin >> inp;
//	C = new int[inp.length()+1];
//	for (int i = 0; i < inp.length()+1; i++)
//		C[i] = 0;
//
//	cout << "your input is " << inp << endl;
//	char res = findBrackets(inp, 'x', 0);
//	if (res == 'x') {
//		cout << "Result = " << res << endl; //<< bracketing << endl;
//		reconstruct(inp);
//	}
//	else
//		cout << "Bracketing not possible for x!" << endl;
//
//
//	//for (int i = 0; i < inp.length(); i++) {
//	//	if (C[i]) {
//	//		cout << " | ";
//	//	}
//	//	else {
//	//		cout << " - ";
//	//	}
//	//}
//	
//
//	cout << endl << endl;
//}
//
