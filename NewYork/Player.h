#pragma once
#include<iostream>
#include<string>
#include<map>

#include"Helper.h"
#include"Dice_Manager.h"
#include"Node.h"
#include"Deck.h"
#include "Card.h"
#include"TileManager.h"
#include"GameManager.h"

class Player
{
public:
	Player();
	~Player();
	void pickMonster();
	void Move(bool start=false);
	void takeDamage(int);
	void collectResources(const std::pair<string, int>&);
	bool PlayTurn();
	bool const isDead() { return dead; }
	int getRank();
	int const getStar() { return star; }
	std::string getName(){ return name; }
	Node* getCurrentLoc() { return currentLoc; }
private:
	static std::vector<std::string> Monsters;
	std::map<string, bool> options;
	std::vector<Card*>upgrades;
	Dice_Manager* dm;
	Node* currentLoc;
	std::string name;
	bool dead;
	int energy, star, health;
	int extraStar;

	void BuyCards();
	void RollDice();
	void setupMonsters();
	void ResolveDice(std::map<string, int>&);
};

