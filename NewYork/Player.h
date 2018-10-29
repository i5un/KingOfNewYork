#pragma once
#include<iostream>
#include<string>
#include<map>

#include"Dice_Manager.h"
#include"Node.h"
#include"Card.h"
#include"Deck.h"
#include"UnitManager.h"
#include"GameManager.h"

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
	string getName(){ return name; }
	Node* getCurrentLoc() { return currentLoc; }
private:
	static Player* celebrityHolder;
	static Player* statueHolder;
	static vector<std::string> Monsters;

	std::string name;
	int energy,star,health;
	vector<Card*>upgrades;
	Dice_Manager* dm;
	Node* currentLoc;

	void setupMonsters();
	void ResolveDice(map<string, int>&);
};

