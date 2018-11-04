#pragma once
#include<iostream>
#include<string>
#include"Player.h"
#include"Helper.h"

/*
	The Unit class and its subclasses usess the "Composition" design pattern
*/

using namespace std;

class Unit;
class Tile;
typedef shared_ptr<Unit> UnitP;
typedef shared_ptr<Tile> TileP;

class Unit {
private:
	int health;
	bool destroyed=false;
	string name,type;
	pair<string, int> reward;
public:
	Unit(string name, int health, string rewardName, int rewardAmount, string type)
		:name(name), health(health), reward(make_pair(rewardName, rewardAmount)),type(type)
	{
	}
	~Unit() {}
	bool isHostile() { if (type == "m") return true;  return false; }
	const string& getName() { return name; }
	const int getHp() { return health; }
	const pair<string, int>& getReward() { return reward; }
	friend class Tile;
};

class Tile
{
public:
	Tile(UnitP, UnitP);
	~Tile();

	const UnitP getUnit() const;
	void destroyUnit(Player*,int);
	friend ostream& operator<<(ostream& os, const TileP& tile);
private:
	const UnitP army;
	const UnitP building;
};