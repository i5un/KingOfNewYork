#include "GameManager.h"

GameManager* GameManager::m_instance = nullptr;

GameManager::GameManager() 
	:currentPos(0)
{
}

GameManager* GameManager::instance() {
	if (m_instance==nullptr) {
		m_instance = new GameManager();
	}
	return m_instance;
}

#define prt std::cout

void GameManager::OnStart(bool test) {
	if (test) {
		//Call the MapLoader and prompt the player to choose from a list of maps then load it
		currentMap = MapLoader::loadMap();

		//Setup the player objects and all related functionalities
		setupPlayers();

		//Setup the deck
		Deck::setup();
		Deck::printDeck();
	}
	else {
		//This portion is called to test the "King of New York map"
		currentMap = MapLoader::loadMap("KingOfNewYork.map");
		setupPlayers();
		Deck::setup();

		//Game can only be played with "King of New York map"
		gameLoop();
	}
}

void GameManager::setupPlayers() {
	std::string input;
	int selection;
	prt << "Enter the number of players(2-6)..." << endl;
	while (true) {
		std::getline(std::cin, input);
		try
		{
			selection = stoi(input);
			if (selection < 2 || selection>6) throw exception();
			break;
		}
		catch (const std::exception&)
		{
			pres << "Invalid entry, please try again..." << std::endl;
			continue;
		}
	}

	for (size_t i = 0; i < selection; i++)
	{
		players.push_back(new Player);
		pres << "Player " << i+1 << " is now picking..." << endl;
		players[i]->pickMonster();
	}
	prt << "\n>>Monster selection completed!\n" << endl;
	prt << "Setting up play turn order..." << endl;
	currentPos = GetFirst();
	startPos = currentPos;

	currentMap->printMap();
	/*
		Each player now picks a bourough to start
	*/
	while (true) {
		players[currentPos++]->Move(true);
		currentPos = currentPos % players.size();
		if ( currentPos== startPos) break;
	}
}

void GameManager::gameLoop() {
	prt << "\nGame Started!\n" << std::endl;
	while (true) {
		ls
		for (const auto& p : players) {
			if (p == players[currentPos]) {
				pres << "[>" << p->getName() << "<] ";
			}
			else {
				pres << p->getName() << " ";
			}
		}
		prt << nl;
		le
		if (players[currentPos]->PlayTurn() || checkWinCond()) break;
		currentPos++;
		currentPos = currentPos % (players.size());
	}
}

bool GameManager::checkWinCond(Player* player) {
	Player* winner = nullptr;
	if (player == nullptr) {
		int alive = 0;
		for (const auto& p : instance()->players) {
			if (!p->isDead()) {
				alive++;
				winner = p;
			}
		}
		if (alive > 1) {
			return false;
		}
	}
	else {
		if (player->getStar() >= 20 || player == instance()->statueHolder && player->getStar() >= 17)
			winner=player;
		return false;
	}
	cout << "Congratulation! " << winner->getName() << " has won the game!!!" << endl;
	return true;
}

int GameManager::GetFirst() {
	vector<pair<Player*,int>> pool;
	for (const auto& p : players) pool.push_back(make_pair(p, 0));

	do {
		int max = -1;
		//Each player rolls once
		for (int i = 0; i < pool.size(); i++) {
			int num= pool[i].first->getRank();
			pool[i].second = num;
			if (num > max) max = num;
			prt << pool[i].first->getName() << " rolled " << num << " Attack" << std::endl;
		}

		for (int i = 0; i < pool.size(); i++) {
			if (pool[i].second < max) {
				pool.erase(pool.begin() + i);
			}
		}
		prt << std::endl;
	} while (pool.size() > 1);

	prt << "\n>> "<<pool[0].first->getName() << " will start first\n" << std::endl;
	return distance(players.begin(), find(players.begin(), players.end(), pool[0].first));
}