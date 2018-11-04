#include "Player.h"
#include "Map.h"

vector<std::string> Player::Monsters;

Player::Player()
	:dm(new Dice_Manager()),currentLoc(GameManager::instance()->getMap()->getZoneZero()),dead(false),health(10)
{
	if (Monsters.size() == 0) setupMonsters();
	options["roll"] = false;
	options["move"] = false;
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
			prt << i << "-" << Monsters[i] << nl;
		}
		while (true) {
			try
			{
				std::getline(std::cin, input);
				selection = stoi(input);
				if (selection < 0 || selection>5) throw exception();
				name = Monsters[selection];
				Monsters.erase(Monsters.begin() + selection);
				break;
			}
			catch (const std::exception& e)
			{
				pres << e.what() << nl;
			}
		}
	}
	else {
		name = Monsters[0];
	}
	pres<< name << "has been chosen!" << nl;
}

bool Player::PlayTurn() {
	prt << getName() <<"'s turn..."<< nl;
	//Evaluate card effects

	std::string input;
	int selection;
	bool endTurn = false;
	for (auto& p : options) p.second = false;

	while (!endTurn) {		
		prt << "Choose from the following options..." << nl;
		prt << " 0-Roll Dice\n 1-Move\n 2-Buy Cards\n 3-End Turn" << nl;

		try {
			std::getline(std::cin, input);
			selection = stoi(input);

			switch (selection) {
			case 0:
				if (options["roll"]) {
					pres << "You've already rolled this turn!" << nl;
				}
				else {
					RollDice();
				}
				break;
			case 1:
				if (options["move"]) {
					pres << "You've already moved this turn!" << nl;
				}
				else if (!options["roll"]) {
					pres << "You have to roll your dice first before moving!" << nl;
				}
				else {
					Move();
				}
				break;
			case 2:
				if (!options["roll"] ) {
					pres << "You must roll your dice before buying cards!" << nl;
				}
				else {
					BuyCards();
				}
				break;
			case 3:
				endTurn = true;
				break;
			default:
				throw exception();
			}
		}
		catch (const exception& e) {
			pres << e.what() << nl;
		}
	}
	if (star >= 20) return true;
	pres << getName() << " finished his/her turn!" << nl;
	return false;
}

void Player::RollDice() {
	ls
	options["roll"] = true;
	map<string,int> result = dm->rollDice(); //get the reference of the result from Dice_Manager
	ResolveDice(result);
}

int Player::getRank() {
	map<string, int> result = dm->rollDice(2,false);
	return result["Attack"];
}

void Player::ResolveDice(map<string,int>& result) {
	string input;
	int selection;
	bool done = false;
	
	//Keeps track which dice got resolved
	vector<pair<pair<string,int>, bool>> tracker;
	for (const auto& d : result) {
		tracker.push_back(make_pair(make_pair(d.first,d.second), false));
	}

	while (!done) {
		prt << "Choose one to resolve..." << nl;
		for (size_t i = 0; i < tracker.size(); i++)
		{
			if(!tracker[i].second)
				prt << i << "-[" << tracker[i].first.first << "] x" << tracker[i].first.second << nl;
		}

		//Inner loop to get user selection
		while (true) {
			try
			{
				getline(std::cin, input);
				selection = stoi(input);
				if (selection > tracker.size() || tracker[selection].second)
					throw InputException();
				break;
			}
			catch (const std::exception& e)
			{
				pres << e.what() << nl;
			}
		}

		//Resolving...

		string type = tracker[selection].first.first;
		tracker[selection].second = true;

		if (type == "Energy") {
			energy += result[type];
			pres << "Gained " << result[type] << " Energy points!" << nl;
		}
		else if (type == "Heal") {
			if (health >= 10) {
				pres << "Already at max health!" << nl;
			}
			else {
				int diff = 10 - health;
				if (result[type] > diff) {
					health = 10;
				}
				else {
					diff = result[type];
					health += diff;
				}
				pres << "Gained " << diff << " Health points!" << nl;
			}
		}
		else if (type == "Attack") {
			/*
				1) check if Player is in Manhattan
				2) if in Manhattan, attack others
				3) else attack player(s) in Manhattan
			*/

			if (currentLoc->isManhattan()) {
				for (const auto& p : GM->getPlayers()) {
					if (!p->getCurrentLoc()->isManhattan())
						p->takeDamage(result[type]);
				}
			}
			else {
				for (const auto& p : GM->getPlayers()) {
					if (p->getCurrentLoc()->isManhattan())
						p->takeDamage(result[type]);
				}
			}
		}
		else if (type == "Celebrity") {
			if (GM->celebrityHolder == this) { //If player has Celebrity card
				star += result[type];
			}
			else {
				if (result[type] >= 3) {
					pres << name << " has acquired the [Celebrity] card!"<< nl;
					GM->celebrityHolder = this;
					star += result[type] - 2;
				}
			}
		}
		else if (type == "Destruction") {
			/*
				Conditions:
				1) Must destroy Units if player has enough points to do so
				2) Cannot destroy Unit on the same turn it appears
			*/

			//Get potential targets
			vector<pair<TileP, bool>> targets;
			int minCost = 100;
			for (const auto& t : *currentLoc->getTiles()) {
				targets.push_back(make_pair(t, false));
				if (t->getUnit()->getHp() < minCost) minCost = t->getUnit()->getHp();
			}
			
			while (true) {
				prt << "Here are all the Tiles in [" << currentLoc->getName() << "]" << nl;
				for (size_t i = 0; i < targets.size(); i++)
				{
					prt << i << "-" << targets[i].first << nl;
				}

				if (result[type] < minCost) {
					//Resolving Destruction will end automatically
					prt << "Not enough Destruction points to do anything..." << nl;
					break;
				}
				else {
					prt << "Choose a Tile to attack..." << nl;
					try {
						getline(std::cin, input);
						selection = stoi(input);

						if (targets[selection].second) throw FailException("You've already attacked this tile!");
						targets[selection].first->destroyUnit(this, result[type]);
						targets[selection].second = true;
					}
					catch (const exception& e) {
						pres << e.what() << nl;
					}
				}
			}

		}
		else if (type == "Ouch!") {
			/*
				check if player has Statue of Liberty card
				case 1 => local military attacks player
				case 2 => local military attacks everyone inside current borough
				case 3 => all military attack all monster, gains Statue of Liberty
			*/
			switch (result[type]) {
			case 1:
				currentLoc->attackPlayer(this);
				break;
			case 2:
				currentLoc->attackPlayer();
				break;
			default:
				GM->statueHolder = this;
				GM->getMap()->globalAttack();
			}
		}
		done = true;
		for (const auto& d : tracker) {
			//End resolving if all types have been resolved.
			done = d.second ? done : false;
		}
	}

	pres << "Dice resolving finished." << nl;
	le
	GameManager::checkWinCond(this); //Check win condition after each resolve
}

void Player::Move(bool start) {
	prt << "\n>> " << name << " is moving..." << endl;
	if (start) {
		prt << "Pick a starting zone from the following..." << std::endl;
	}
	else {
		prt << "Pick a zone to travel to from the following..." << std::endl;
	}

	//Get the list of zones connected to where the player is at
	vector<Node*> destinations;

	for (const auto& z : *currentLoc->getAdj()) {
		if (z->isFree()) {
			destinations.push_back(z);
			prt << destinations.size()-1 << "-" << z->getName() << std::endl;
		}
	}

	/*
		If no one is in Manhattan then player must move there
	*/

	//Read input from user
	std::string input;
	int selection;

	while (true) {
		try {
			std::getline(std::cin, input);
			selection = stoi(input);
			if (selection<0 || selection>=destinations.size()) throw exception();
			break;
		}
		catch (...) {
			prt << ">> Invalid entry, please try again..." << std::endl;
		}
	}
	
	prt << ">> " << getName() << " left [" << currentLoc->getName() <<"]"<< std::endl;
	currentLoc->exitZone(this);

	currentLoc = destinations[selection];
	currentLoc->enterZone(this);
	prt << ">> " << getName() << " entered [" << currentLoc->getName()<<"]" << std::endl;

	prt << ">> " << getName() << " finished moving." << std::endl;
}

void Player::BuyCards() {
	//if (energy <= card->getCost()) {
	//	return false;
	//}
	//if (card->getType() == "discard") {
	//	card->use(this);
	//}
	//else {
	//	upgrades.push_back(card);
	//}
	//Deck::next(index);
}

void Player::takeDamage(int dmg) {
	pres << getName() << " has taken " << dmg << " damage!" << nl;
	health -= dmg;
	if (health <= 0) {
		pres << getName() << " is defeated!!" << nl;
	}

	//If in Manhattan, has the option to stay or leave
}

void Player::collectResources(const pair<string, int>& resource) {
	if (resource.first == "Health") {
		health += resource.second;
	}
	else if (resource.first == "Star") {
		star += resource.second;
	}
	else if (resource.first == "Energy") {
		energy += resource.second;
	}
	pres << "Collected " << resource.first << " x" << resource.second << nl;
}

void Player::setupMonsters() {
	Monsters.push_back("Capitain Fish");
	Monsters.push_back("Sheriff");
	Monsters.push_back("Mantis");
	Monsters.push_back("Rob");
	Monsters.push_back("Drakonis");
	Monsters.push_back("Kong");
}