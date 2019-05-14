//#include<iostream>
//using namespace std;
//
//int matFloor(int k){
//	int prev1 = 1, prev2 = 2;	// for vertical case(2x1) and 2x2 case (2 horizontal or 2 vertical)
//	int val = 0;
//	if (k == 1)
//		return prev1;
//	else if (k == 2)
//		return prev2;
//	else{
//		for (int i = 3; i <= k; i++){
//			val = prev1 + prev2;
//			prev1 = prev2;
//			prev2 = val;
//		}
//		return val;
//	}
//}
//
//int main(){
//	int k = -1;
//	cout << "Enter value of k: ";
//	cin >> k;
//	cout << "Ther are " << matFloor(k) << " posssible ways to mat a 2x" << k << " floor"<<endl;
//	system("Pause");
//	return 0;
//}