#include <iostream>
using namespace std;

void Turn(int& p, int c) { //it is for output and changing player turn
	cout << "Player " << p + 1 << " picks " << c << " coin";
	if (c > 1)
		cout << "s.";
	else
		cout << ".";
	cout << endl;
	p = !p;
}


void CoinsGame(int tcoins, int player = 0) { //0 for P1, 1 for P2
	if (tcoins == 0) {
		cout << "Player ";
		if (player == 0)
			cout << "2";
		else
			cout << "1";
		cout << " wins" << endl;
		return;
	}
	if (tcoins == 1) {
		Turn(player, tcoins);
		CoinsGame(tcoins - 1, player);
	}
	else if (tcoins == 2) {
		Turn(player, tcoins);
		CoinsGame(tcoins - 2, player);
	}
	else if (tcoins == 4) {
		Turn(player, tcoins);
		CoinsGame(tcoins - 4, player);
	}
	else {
		if ((tcoins - 4) % 3 == 0) {
			Turn(player, 4);
			CoinsGame(tcoins - 4, player);
		}
		else if ((tcoins - 2) % 3 == 0) {
			Turn(player, 2);
			CoinsGame(tcoins - 2, player);
		}
		else {
			Turn(player, 1);
			CoinsGame(tcoins - 1, player);
		}
	}
}


void main() {
	while (1) {
		cout << "Enter number of Coins = ";
		int n;
		cin >> n;
		if(n>0)
			CoinsGame(n);
	}
}


