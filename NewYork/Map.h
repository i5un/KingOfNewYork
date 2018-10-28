#pragma once
#include<vector>
#include<map>
#include<iostream>
#include<list>
#include<string>
#include"Player.h"
#include"Node.h"
#include"UnitManager.h"

using namespace std;

class Map
{
public:
	Map(string, vector<string>&, vector<pair<int, int>>&, vector<int>&, bool=false);
	~Map();
	void printMap();
	bool verifyMap(bool =false);
	void globalAttack();

	void setInManhattan(Player*);
	vector<Node*>* getManhattanArea();
	void getPath(Player*, vector<Node*>&);
private:
	std::string name;
	bool valid;
	typedef map<std::string, Node*> vmap;
	vmap battleGround;
	Node* nodeZero;
	vector<Node*>ManhattanArea;
	Player* inManhattan;

	void addUnits();
	void addVertex(std::string vname);
	void addEdge(std::string source, std::string des);
};
