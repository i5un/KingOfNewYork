#include "GameManager.h"

Map* GameManager::currentMap = nullptr;
vector<Player*> GameManager::players;

#define cprint std::cout

void GameManager::StartGame(bool debug) {
	if (debug) {
		//Call the MapLoader and prompt the player to choose from a list of maps
		currentMap = MapLoader::loadMap();

		//Setup the player objects and store it in this class
		SetupPlayers();

		//Setup the deck
		Deck::setup();
		Deck::printDeck();
	}
	else {
		currentMap = MapLoader::loadMap();
		SetupPlayers();
		Deck::setup();
	}
}

void GameManager::SetupPlayers() {
	std::string input;
	int selection;
	cprint << "Enter the number of players(2-6)..." << endl;
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
			std::cout << ">> Invalid entry, please try again..." << std::endl;
			continue;
		}
	}

	for (size_t i = 0; i < selection; i++)
	{
		players.push_back(new Player);
		cprint << ">> Player " << i+1 << " is now picking..." << endl;
		players[i]->pickMonster();
	}
	cprint << ">>Monster selection completed!" << endl;
	std::random_shuffle(players.begin(), players.end());
	cprint << "The order of turns is as follow..." << std::endl;
	for (const auto& p : players) {
		cprint << " >> " << p->getName();
	}
	cprint << std::endl;
}
