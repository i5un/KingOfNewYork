#pragma once
#include<string>
#include<vector>
#include<algorithm>
#include<iostream>

using namespace std;

class Player;
class Tile;
typedef shared_ptr<Tile> TileP;

class Node
{
private:
	string name;
	vector<Player*> owners;
	vector<Node*> adj;
	vector<TileP> pillOne;
	vector<TileP> pillTwo;
	vector<TileP> pillThree;
	vector<TileP> availableTiles;
public:
	Node();
	Node(string,bool=false);
	~Node();
	string getName() { return name; };
	vector<Node*>* getAdj() { return &adj; };
	
	void enterZone(Player* player) { owners.push_back(player); };
	void addEdge(Node*);

	virtual bool isFree();
	virtual bool isManhattan() { return false; }
	virtual void exitZone(Player* player);
	virtual void attackPlayer(Player* = nullptr);
	virtual vector<Player*>* getOwners() { return &owners; };
	virtual void removeTile(int);
	virtual vector<TileP>* getTiles();
};