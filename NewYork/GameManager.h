#pragma once
#include<vector>
#include"MapLoader.h"
#include"Map.h"
#include"Player.h"
#include"Deck.h"
#include"TileManager.h"

/*
	This class uses the Singleton design pattern
*/
class GameManager
{
public:
	Player* celebrityHolder;
	Player* statueHolder;

	static GameManager* instance();
	static bool checkWinCond(Player* =nullptr);
	void OnStart(bool test=false);
	bool isAdvanced() { return advancedRule; }
	Map* getMap() { return currentMap; }
	vector<Player*>& getPlayers() { return players; }
private:
	static GameManager* m_instance;
	int currentPos, startPos, endPos;
	bool advancedRule = false;
	Map* currentMap;
	vector<Player*> players;

	GameManager();
	void gameLoop();
	void setupPlayers();
	int GetFirst();
};

