#pragma once
#include<vector>

#include"MapLoader.h"
#include"Map.h"
#include"Player.h"
#include"Deck.h"

class GameManager
{
public:
	class Game {

	};
	void static StartGame(bool debug=false);
	static Map* getMap() { return currentMap; }
	static vector<Player*>& getPlayers() { return players; }
private:
	static int activePlayer;
	static Map* currentMap;
	static vector<Player*> players;
	void static SetupPlayers();
	void static GameLoop();
};

