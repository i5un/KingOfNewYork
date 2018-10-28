#include "Monsters.h"

vector<Monsters::Monster*>* Monsters::monsters=new vector<Monsters::Monster*>;

Monsters::Monster* Monsters::pickMonster(int id) {
	if (id<monsters->size() && (*monsters)[id]) {
		Monster* ptr = (*monsters)[id];
		monsters->erase(monsters->begin()+id);
		return ptr;
	}
	return nullptr;
}

void Monsters::displayMonsters() {
	if (monsters->size() == 0) {
		monsters->push_back(new Monster("Capitain Fish"));
		monsters->push_back(new Monster("Sheriff"));
		monsters->push_back(new Monster("Mantis"));
		monsters->push_back(new Monster("Rob"));
		monsters->push_back(new Monster("Drakonis"));
		monsters->push_back(new Monster("Kong"));
	}
	for (size_t i = 0; i < monsters->size(); i++)
	{
		cout << i << "-" << (*monsters)[i]->getName() << endl;
	}
}
