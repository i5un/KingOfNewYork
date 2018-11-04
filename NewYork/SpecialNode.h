#pragma once
#include "Node.h"
#include "TileManager.h"
#include "Helper.h"

class SpecialNode :
	public Node
{
	private:
		static vector<TileP> pillOne;
		static vector<TileP> pillTwo;
		static vector<TileP> pillThree;
		static vector<TileP> availableTiles;
		static vector<Player*> owners;
	public:
		SpecialNode(string);
		~SpecialNode();
		//void attackPlayer();
		void removeTile(int);
		void exitZone(Player* player);
		vector<TileP>* getTiles();
		vector<Player*>* getOwners() { return &owners; }
		bool isFree();
		bool isManhattan() { return true; }
};

