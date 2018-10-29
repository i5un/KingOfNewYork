#include "Player.h"
#include "Map.h"

#define cprint std::cout

Player* Player::celebrityHolder;
Player* Player::statueHolder;
vector<std::string> Player::Monsters;

Player::Player()
	:dm(new Dice_Manager()),currentLoc(nullptr)
{
	if (Monsters.size() == 0)setupMonsters();
}


Player::~Player()
{
	delete dm;
}

void Player::pickMonster() {
	if (Monsters.size() != 1) {
		std::string input;
		int selection;
		cout << "Choose a monster:" << endl;
		for (size_t i = 0; i < Monsters.size(); i++)
		{
			cprint << i << "-" << Monsters[i] << endl;
		}
		while (true) {
			try
			{
				std::getline(std::cin, input);
				selection = stoi(input);
				if (selection < 0 || selection>5)throw exception();
				name = Monsters[selection];
				Monsters.erase(Monsters.begin() + selection);
				break;
			}
			catch (const std::exception&)
			{
				std::cout << ">> Invalid selection, please try again..." << std::endl;
				continue;
			}
		}
	}
	else {
		name = Monsters[0];
	}
	cprint << ">> " << name << "has been chosen!" << endl;
}

void Player::RollDice() {
	map<string, int>* result = dm->rollDice();
	ResolveDice(*result);
}

void Player::ResolveDice(map<string, int>& result) {
	cout << ">>Resolving..." << endl;
	for (auto const& x:result)
	{
		if (x.first == "Energy") {
			energy += x.second;
			cout << ">>Gained " << x.second << " energy" << endl;
		}
		else if (x.first == "Heal") {
			health += x.second;
			cout << ">>Gained " << x.second << " health points" << endl;
		}
		else if (x.first == "Attack") {
			if (currentLoc->getName().find("Manhattan")!=string::npos) {
				// Player is in Manhattan and will attack everyone else
				for (auto &player : std::as_const(GameManager::getPlayers())) {
					if (player != this) {
						cout << ">>Attacking..." << endl;
						player->takeDamage(x.second);
					}
				}
			}
			else {
				//Player is not in Manhattan and will attack whoever is in Manhattan
				for (auto &target : as_const(GameManager::getPlayers())) {
					if (target->getCurrentLoc()->getName().find("Manhattan") != string::npos) {
						target->takeDamage(x.second);
					}
				}
			}			
		}
		else if (x.first=="Celebrity") {
			//check if player has Celebrity card
			if (celebrityHolder == this) {
				star += x.second;
			}
			else {
				if (x.second >= 3) {
					celebrityHolder = this;
					star += x.second - 2;
				}
			}
		}
		else if (x.first == "Destruction") {
			int points = x.second;
			int option;
			string input;
		
			while (true) {
				std::vector<Building*> units;
				std::cout << "You have " << points << " destruction points left. Choose unit to attack" << endl;
				std::cout << "Press Enter to skip this phase" << endl;

				// If current location is part of Manhattan
				if (currentLoc->getName().find("Manhattan") != string::npos) {
					vector<Node*>* ManhattanAreas = GameManager::getMap()->getManhattanArea();
					for (auto &zone : as_const(*ManhattanAreas)) {
						zone->getUnits(units);
					}
				}
				else {
					getCurrentLoc()->getUnits(units);
				}

				for (size_t i = 0; i < units.size(); i++)
				{
					std::cout << i << "-"; 
					units[i]->printInfo();
				}

				getline(cin, input);
				if (input == "") break;

				try {
					option = stoi(input);
					if (option<0 || option>units.size() - 1) {
						std::cout << ">>Invalid entry, try again." << endl;
						continue;
					}
					else {
						if (points >= units[option]->getHealth()) {
							pair<string, int>* reward = units[option]->getReward();
							points -= units[option]->getHealth();
							units[option]->destroy();
						}
						else {
							std::cout << ">>Insufficient points..." << endl;
							continue;
						}
					}
				}
				catch (invalid_argument e) {
					std::cout << ">>Invalid entry, try again." << endl;
					continue;
				}
			}	
		}
		else if (x.first == "Ouch!") {
			/*
				check if player has Statue of Liberty card

				x:1 => local military attacks player
				x:2 => local military attacks everyone inside current borough
				x:3 => all military attack all monster, gains Statue of Liberty
			*/
			switch (x.second) {
			case 1:
				currentLoc->attack(this);
				break;
			case 2:
				currentLoc->attack();
				break;
			default:
				GameManager::getMap()->globalAttack();
				break;
			}
		}
	}
}

void Player::Move(Node* des) {
	if (currentLoc != nullptr) {
		cout << ">>leaving: " << currentLoc->getName() << endl;
		currentLoc->exitZone(this);
	}
	cout << ">>Entering: " << des->getName() << endl;
	currentLoc = des;
	des->enterZone(this);
	if (des->getName().find("Manhattan") != string::npos) {
		GameManager::getMap()->setInManhattan(this);
	}
}

bool Player::BuyCards(Card* card,int index) {
	if (energy <= card->getCost()) {
		return false;
	}
	if (card->getType() == "discard") {
		card->use(this);
	}
	else {
		upgrades.push_back(card);
	}
	Deck::next(index);
}

void Player::takeDamage(int dmg) {
	cout << ">>" << getName() << " has taken " << dmg << " damage!" << endl;
	health -= dmg;
	if (health <= 0) {
		cout << ">>" << getName() << " is defeated!!" << endl;
	}
}

void Player::setupMonsters() {
	Monsters.push_back("Capitain Fish");
	Monsters.push_back("Sheriff");
	Monsters.push_back("Mantis");
	Monsters.push_back("Rob");
	Monsters.push_back("Drakonis");
	Monsters.push_back("Kong");
}