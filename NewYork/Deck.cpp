#include "Deck.h"

vector<Card*> Deck::cards;
vector<Card*> Deck::shop;
vector<Card*> Deck::discarded;
Card* Deck::Statue;
Card* Deck::SuperStar;

void Deck::setup() {
	/*
		Read from Cards.json and parse the content
	*/
	ifstream stream("Cards.json");
	nlohmann::json content;
	try {
		content = nlohmann::json::parse(stream);
	}
	catch (nlohmann::json::parse_error &e) {
		std::cerr << e.what() << std::endl;
	}
	for (size_t i = 0; i < content["cards"].size(); i++)
	{
		Card* c = new Card(
			content["cards"][i]["name"],
			content["cards"][i]["desc"],
			content["cards"][i]["type"],
			content["cards"][i]["id"],
			content["cards"][i]["cost"]);

		if (i == 0) {
			Statue = c;
		}
		else if (i == 1) {
			SuperStar = c;
		}
		else cards.push_back(c);
	}

	/*
		Suffle the deck and push 3 cards into the shop
	*/
	Shuffle();
	refill(3);
}

void Deck::Shuffle() {
	random_shuffle(begin(cards), end(cards));
}


void Deck::printDeck() {
	cout << ">> " << cards.size() +shop.size() << " cards created..." << endl;
	for (size_t i = 0; i < cards.size(); i++)
	{
		cout << (cards)[i]->getId() << " : " << (cards)[i]->getName() << endl;
	}
}

void Deck::refill(int stack) {
	for (size_t i = 0; i < stack; i++)
	{
		shop.push_back(cards.back());
		Deck::cards.pop_back();
	}
}

void Deck::clearBoard() {
	for (size_t i = 0; i < 3; i++)
	{
		discarded.push_back(shop.back());
		shop.pop_back();
	}
	refill(3);
}

vector<Card*>* Deck::getShopItems() {
	return &shop;
}

void Deck::next(int id) {
	Card* c = shop[id];
	if (c->getType() == "discard") {
		discarded.push_back(c);
	}
	shop.erase(shop.begin() + id);
}