#include<iostream>
#include<vector>
#include"Player.h"
#include"MapLoader.h"
#include"Map.h"
#include"Node.h"
#include"Deck.h"

void moveTest(Player&);
void shopTest(Player&);
void diceTest(Player&);

int main() {
	MapLoader::loadMap("KingOfNewYork.map");
	Player p1;

	string input;
	int option;

	while (true) {
		std::cout << "Pick the feature you wish to test" << endl;
		std::cout << "0-Move 1-Buy Cards 2-Roll Dice 3-Pick a monster" << endl;
		std::cout << "Press Enter to terminate" << endl;

		getline(cin, input);
		if (input == "")break;

		try {
			option = stoi(input);
			switch (option) {
			case 0:
				moveTest(p1);
				break;
			case 1:
				shopTest(p1);
				break;
			case 2:
				diceTest(p1);
				break;
			case 3:
				p1.pickMonster();
				break;
			default:
				cout << "Out of range, try again..." << endl;
				continue;
			}
		}
		catch (invalid_argument e) {
			cout << "Invalid entry, try again..." << endl;
		}
	}
}

void moveTest(Player& player) {
	string rawInput;
	int option;
	vector<Node*> locations;
	while (true)
	{
		MapLoader::currentMap->getPath(&player,locations);
		cout << "Free zones that you can move to: " << endl;
		for (size_t i = 0; i < locations.size(); i++)
		{
			Node* node = locations[i];
			cout << i << "-" << node->getName() << endl;
		}
		cout << "Press Enter to end move test" << endl;
		getline(cin, rawInput);
		if (rawInput == "") break;

		try {
			option = stoi(rawInput);
			if (option > locations.size() - 1) {
				cout << ">>Invalid entry. Please try again" << endl;
			}
			else {
				player.Move(locations[option]);
				break;
			}
		}
		catch (invalid_argument e) {
			cout << ">>Invalid entry. Please try again" << endl;
		}
	}	
}
void shopTest(Player& player) {
	Deck::setup();
	string rawInput;
	int option;
	while (true) {
		vector<Card*>* shop = Deck::getShopItems();
		for (size_t i = 0; i < shop->size(); i++)
		{
			cout << i << "-" << (*shop)[i]->getName() << endl;
		}

		cout << "Type in the id of the card you wish to purchase" << endl;
		cout << "Or just press Enter to skip" << endl;
		getline(std::cin, rawInput);
		if (rawInput == "")break;

		option = stoi(rawInput);
		if (option > 3 || option < 0) {
			cout << ">>Invalid entry" << endl;
			continue;
		}
		bool result = player.BuyCards((*shop)[option], option);
		if (!result) {
			cout << ">>Insufficient energy" << endl;
		}
	}
}
void diceTest(Player& player) {
	// These steps must be completed before testing the dice 
	player.pickMonster();
	moveTest(player);
	player.RollDice();
}