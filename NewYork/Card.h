#pragma once
#include<string>
#include"Player.h"

using namespace std;

class Card
{
private:
	int id, cost;
	string name, desc, type;
public:
	Card(string name, string desc, string type, int id, int cost);
	~Card();
	int getId() { return id; }
	int getCost() { return cost; }
	string getName() { return name; }
	string getDesc() { return desc; }
	string getType() { return type; }
	void use(Player*);
};

