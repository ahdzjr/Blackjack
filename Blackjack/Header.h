#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <stdio.h>

using namespace std;

class PlayerCard {
public:
	PlayerCard(int cardnum, int cardval, int cardsuit);
	int cardnum;
	int cardval;
	int cardsuit;
};
class HouseCard {
public:
	HouseCard(int hcardnum, int hcardval, int hcardsuit);
	int hcardnum;
	int hcardval;
	int hcardsuit;
};

int card1checkace(vector<PlayerCard*> playercards, string cardNum[], int cardVal[], string cardSuit[], char eo, int ca, int total);
int card2checkace(vector<PlayerCard*> playercards, string cardNum[], int cardVal[], string cardSuit[], char eo, int ca, int total);
int gettotal(vector<PlayerCard*> playercards, int cardVal[]);
int hgettotal(vector<HouseCard*> housecards, int cardVal[]);

#endif