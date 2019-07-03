#include "Header.h"

/*
This program uses:
-------------------------
Header/Source files
Multiple Variables
Arrays
Classes
Pointers
Functions
Conditionals
STL vector
-------------------------
*/

int main() {
	//system("color 0D");
	srand(time(NULL));

	//Arrays
	string cardNum[15] = { "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace / 1", "Ace / 11" };
	int cardVal[15] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11, 0 };
	string cardSuit[4] = { "Clubs", "Diamonds", "Hearts", "Spades" };

	//Variables
	char eo = 'a';
	char yn = 'b';
	char hs = 'c';
	int ca = 3;
	int total = 0;
	int htotal = 0;
	bool playerplaying = true;
	bool stay = false;

	//vector for displaying wins and losses after user is done playing
	vector<string> winloss;

	//main game loop
	while (playerplaying == true) {
		//system("color 0D");

		//vectors for holding player and house cards
		vector<PlayerCard*> playercards;
		vector<HouseCard*> housecards;

		//card 1 randomized
		int cnum = rand() % 13;
		int cval = cnum;
		//if a card is a Jack/Queen/King the value will be set to 10
		if (cval == 10 || cval == 11 || cval == 12)
			cval = 9;
		int csuit = rand() % 4;
		playercards.push_back(new PlayerCard(cnum, cval, csuit));

		//card 2 randomized
		cnum = rand() % 13;
		cval = cnum;
		if (cval == 10 || cval == 11 || cval == 12)
			cval = 9;
		csuit = rand() % 4;
		playercards.push_back(new PlayerCard(cnum, cval, csuit));

		//total function
		total = gettotal(playercards, cardVal);

		cout << endl;
		//displays hand
		cout << "Your hand:" << endl;
		cout << cardNum[playercards[0]->cardnum] << " of " << cardSuit[playercards[0]->cardsuit] << endl;
		cout << cardNum[playercards[1]->cardnum] << " of " << cardSuit[playercards[1]->cardsuit] << endl;
		cout << endl;

		//displays total
		cout << "Total: " << gettotal(playercards, cardVal) << endl;

		//function that checks if player has an ace and brings up a choice to either have one of the aces be 1 or 11
		ca = card1checkace(playercards, cardNum, cardVal, cardSuit, eo, ca, total);
		if (ca == 0)
			card2checkace(playercards, cardNum, cardVal, cardSuit, eo, ca, total);

		//if player gets 21 off first two cards, player wins
		if (gettotal(playercards, cardVal) == 21) {
			//system("color F5");
			cout << endl;
			cout << "Blackjack! You win!!!" << endl;
		}
		//player begins hit or stay
		else {
			while (gettotal(playercards, cardVal) < 21 && stay == false) {
				//system("color 0B");
				cout << endl;
				cout << "Would you like to hit or stay? [h/s]" << endl;
				cin >> hs;
				if (hs == 'h') {
					cout << endl;
					//hit card
					cnum = rand() % 13;
					cval = cnum;
					if (cval == 10 || cval == 11 || cval == 12)
						cval = 9;
					csuit = rand() % 4;
					playercards.push_back(new PlayerCard(cnum, cval, csuit));

					cout << "Your hand:" << endl;
					for (int i = 0; i < playercards.size(); i++) {
						cout << cardNum[playercards[i]->cardnum] << " of " << cardSuit[playercards[i]->cardsuit] << endl;
					}
					cout << endl;
					cout << "Total: " << gettotal(playercards, cardVal) << endl;

				}
				else if (hs == 's') {
					cout << endl;
					//displays hand and stays
					cout << "Your hand:" << endl;
					for (int i = 0; i < playercards.size(); i++) {
						cout << cardNum[playercards[i]->cardnum] << " of " << cardSuit[playercards[i]->cardsuit] << endl;
					}
					cout << endl;
					cout << "Total: " << gettotal(playercards, cardVal) << endl;
					stay = true;
				}
				cout << endl;
			}
			//loop breaks when player busts, achieves 21, or stays then checks which one they accomplished
			//bust
			if (gettotal(playercards, cardVal) > 21) {
				winloss.push_back("Loss");
				cout << "Bust! House wins." << endl;
			}

			//blackjack
			else if (gettotal(playercards, cardVal) == 21) {
				winloss.push_back("Win");
				cout << "Blackjack! You win!!!" << endl;
			}

			//stays
			else {
				//house plays
				//card 1 randomized
				int hcnum = rand() % 13;
				int hcval = cnum;
				if (hcval == 10 || hcval == 11 || hcval == 12)
					hcval = 9;
				int hcsuit = rand() % 4;
				housecards.push_back(new HouseCard(hcnum, hcval, hcsuit));

				//card 2 randomized
				hcnum = rand() % 13;
				hcval = cnum;
				if (hcval == 10 || hcval == 11 || hcval == 12)
					hcval = 9;
				hcsuit = rand() % 4;
				housecards.push_back(new HouseCard(hcnum, hcval, hcsuit));

				//house total function
				htotal = hgettotal(housecards, cardVal);

				if (hgettotal(housecards, cardVal) <= 10) {
					//house hit card
					hcnum = rand() % 13;
					hcval = cnum;
					if (hcval == 10 || hcval == 11 || hcval == 12)
						hcval = 9;
					hcsuit = rand() % 4;
					housecards.push_back(new HouseCard(hcnum, hcval, hcsuit));
				}

				if (hgettotal(housecards, cardVal) >= 18) {
					int househs = rand() % 2;

					if (househs == 0) {
						//house hit card again
						hcnum = rand() % 13;
						hcval = cnum;
						if (hcval == 10 || hcval == 11 || hcval == 12)
							hcval = 9;
						hcsuit = rand() % 4;
						housecards.push_back(new HouseCard(hcnum, hcval, hcsuit));
					}

				}
				//determines if house or you win

				//player wins
				if (hgettotal(housecards, cardVal) > 21) {
					winloss.push_back("Win");
					cout << "You win!!!" << endl;
				}
				//house wins
				else if (hgettotal(housecards, cardVal) >= gettotal(playercards, cardVal)) {
					winloss.push_back("Loss");
					cout << "House wins." << endl;
				}
				//player wins
				else if (gettotal(playercards, cardVal) > hgettotal(housecards, cardVal)) {
					winloss.push_back("Win");
					cout << "You win!!!" << endl;
				}
			} //end of stay condition

			total = gettotal(playercards, cardVal);
			htotal = hgettotal(housecards, cardVal);

		} //end of hit or stay loop

		//End values display
		cout << endl;
		cout << "Player value: " << gettotal(playercards, cardVal) << endl;
		cout << "House value: " << hgettotal(housecards, cardVal) << endl;
		cout << endl;

		//asks user if they want to play again
		//system("color F0");
		cout << endl;
		cout << "Would you like to play again?[y/n]" << endl;
		cin >> yn;
		if (yn == 'y') {
			stay = false;
			playerplaying = true;
		}
		else if (yn == 'n')
			playerplaying = false;

	} //end of game loop

	//when user finishes game session, a win/loss record will appear
	//system("color 0A");
	cout << endl;

	for (int wl = 0; wl < winloss.size(); wl++)
		cout << winloss[wl] << endl;


	return 0;

}


PlayerCard::PlayerCard(int cardnum, int cardval, int cardsuit) {
	this->cardnum = cardnum;
	this->cardval = cardval;
	this->cardsuit = cardsuit;
}

HouseCard::HouseCard(int hcardnum, int hcardval, int hcardsuit) {
	this->hcardnum = hcardnum;
	this->hcardval = hcardval;
	this->hcardsuit = hcardsuit;
}

int card1checkace(vector<PlayerCard*> playercards, string cardNum[], int cardVal[], string cardSuit[], char eo, int ca, int total) {

	if (cardNum[playercards[0]->cardnum] == cardNum[0]) {
		cout << "Card 1: " << "Is your ace's value eleven or one? [e/o]" << endl;
		cin >> eo;
		if (eo == 'e') {
			playercards[0]->cardnum = 14;
			playercards[0]->cardval = 13;

			cout << "Your new hand:" << endl;
			cout << cardNum[playercards[0]->cardnum] << " of " << cardSuit[playercards[0]->cardsuit] << endl;
			cout << cardNum[playercards[1]->cardnum] << " of " << cardSuit[playercards[1]->cardsuit] << endl;
			cout << endl;
			cout << "Total: " << gettotal(playercards, cardVal) << endl;

			ca = 1;
		}
		else if (eo == 'o') {
			playercards[0]->cardnum = 13;
			playercards[0]->cardval = 0;

			cout << "Your new hand:" << endl;
			cout << cardNum[playercards[0]->cardnum] << " of " << cardSuit[playercards[0]->cardsuit] << endl;
			cout << cardNum[playercards[1]->cardnum] << " of " << cardSuit[playercards[1]->cardsuit] << endl;
			cout << endl;
			cout << "Total: " << gettotal(playercards, cardVal) << endl;

			ca = 1;
		}
	}
	else
		ca = 0;

	return ca;
}

int card2checkace(vector<PlayerCard*> playercards, string cardNum[], int cardVal[], string cardSuit[], char eo, int ca, int total) {

	if (cardNum[playercards[1]->cardnum] == cardNum[0]) {
		cout << "Card 2: " << "Is your ace's value eleven or one? [e/o]" << endl;
		cin >> eo;
		if (eo == 'e') {
			playercards[1]->cardnum = 14;
			playercards[1]->cardval = 13;

			cout << "Your new hand:" << endl;
			cout << cardNum[playercards[0]->cardnum] << " of " << cardSuit[playercards[0]->cardsuit] << endl;
			cout << cardNum[playercards[1]->cardnum] << " of " << cardSuit[playercards[1]->cardsuit] << endl;
			cout << endl;
			cout << "Total: " << gettotal(playercards, cardVal) << endl;

			ca = 1;
		}
		else if (eo == 'o') {
			playercards[1]->cardnum = 13;
			playercards[1]->cardval = 0;

			cout << "Your new hand:" << endl;
			cout << cardNum[playercards[0]->cardnum] << " of " << cardSuit[playercards[0]->cardsuit] << endl;
			cout << cardNum[playercards[1]->cardnum] << " of " << cardSuit[playercards[1]->cardsuit] << endl;
			cout << endl;
			cout << "Total: " << gettotal(playercards, cardVal) << endl;

			ca = 1;
		}
	}
	else
		ca = 0;

	return ca;
}

int gettotal(vector<PlayerCard*> playercards, int cardVal[]) {
	int total = 0;
	for (int i = 0; i < playercards.size(); i++)
		total += cardVal[playercards[i]->cardval];

	return total;
}

int hgettotal(vector<HouseCard*> housecards, int cardVal[]) {
	int htotal = 0;
	for (int i = 0; i < housecards.size(); i++)
		htotal += cardVal[housecards[i]->hcardval];

	return htotal;
}