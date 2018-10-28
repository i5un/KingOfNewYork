#include "Card.h"



Card::Card(string name, string desc, string type, int id, int cost)
	:name(name), desc(desc), type(type), id(id), cost(cost)
{}


Card::~Card()
{
}

void Card::use(Player* player) {
	cout << player->getName() << " used " << name<<endl;
}
