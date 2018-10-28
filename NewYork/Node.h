#pragma once
#include<string>
#include<vector>
#include<algorithm>
#include<iostream>
#include"UnitManager.h"

using namespace std;

class Player;

class Node
{
public:
	Node();
	Node(string);
	~Node();
	bool enterZone(Player*);
	bool isFree(Player*);
	void exitZone(Player*);
	void addEdge(Node*);
	void attack(Player* = nullptr);

	void addUnit(Building*);
	void getUnits(vector<Building*>&);
	std::string getName();
	std::vector<Player*>* getOwners();
	std::vector<Node*>* getAdj();
private:
	string name;
	vector<Player*> owners;
	std::vector<Node*> adj;
	vector<Building*> units;
};