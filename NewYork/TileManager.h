#pragma once
#include<vector>
#include<fstream>
#include<map>
#include"Tile.h"

using namespace std;

class TileManager {
public:
	static TileManager* instance();
	shared_ptr<Tile> drawTile(string&);
private:
	static TileManager* m_instance;
	TileManager();
	vector<shared_ptr<Tile>> tiles;
	int index;
};