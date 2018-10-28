#pragma once
#include<iostream>
#include<string>
#include<map>
#include"Monsters.h"
#include"Dice_Manager.h"
#include"MapLoader.h"
#include"Node.h"
#include"Card.h"
#include"Deck.h"
#include"UnitManager.h"

using namespace std;

class Player
{
public:
	Player();
	~Player();
	void pickMonster();
	void RollDice();
	void Move(Node*);
	void takeDamage(int);

	bool BuyCards(Card*,int);
	string getName();
	Node* getCurrentLoc();
private:
	static vector<Player*> players;
	static Player* celebrityHolder;
	static Player* statueHolder;

	int energy,star,health;
	Monsters::Monster* monster;
	vector<Card*>upgrades;
	Dice_Manager* dm;
	Node* currentLoc;

	void ResolveDice(map<string, int>&);
};

