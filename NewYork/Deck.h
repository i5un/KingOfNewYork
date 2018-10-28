#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include"json.hpp"
#include"Player.h"

using namespace std;
class Card;
class Deck
{
public:
	static void Shuffle();
	static void printDeck();
	static void clearBoard();
	static vector<Card*>* getShopItems();
	static void setup();
	static void next(int);
private:
	static Card* Statue;
	static Card* SuperStar;
	static vector<Card*> cards;
	static vector<Card*> shop;
	static vector<Card*> discarded;
	static void refill(int);
};

