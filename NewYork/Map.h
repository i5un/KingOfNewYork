#pragma once
#include<vector>
#include<map>
#include<iostream>
#include<list>
#include<string>
#include"Player.h"
#include"Node.h"
#include"SpecialNode.h"
#include"TileManager.h"

using namespace std;
typedef map<std::string, Node*> vmap;

class Map
{
public:
	Map(string, vector<string>&, vector<pair<int, int>>&, vector<int>&);
	~Map();
	void printMap();
	void globalAttack();

	bool verifyMap(bool =false);
	Node* getZoneZero() { return zoneZero; }
	const vmap& getAllZones() { return battleGround; }
private:
	std::string name;
	bool valid;
	vmap battleGround;
	Node* zoneZero;
	Player* inManhattan;

	void addVertex(std::string vname);
	void addEdge(std::string source, std::string des);
};
