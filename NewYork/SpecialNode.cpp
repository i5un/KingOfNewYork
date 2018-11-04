#include "SpecialNode.h"
#include "GameManager.h"

vector<TileP> SpecialNode::pillOne;
vector<TileP> SpecialNode::pillTwo;
vector<TileP> SpecialNode::pillThree;
vector<TileP> SpecialNode::availableTiles;
vector<Player*> SpecialNode::owners;

SpecialNode::SpecialNode(string name)
	:Node(name,true)
{
	//If getTiles() returns 3 elements, the Manhattan area has already been populated with Tiles
	if (getTiles()->size() == 3) return;

	for (size_t i = 0; i < 9; i++)
	{
		if (i < 3) {
			pillOne.push_back(TileManager::instance()->drawTile(name));
		}
		else if (i < 6) {
			pillTwo.push_back(TileManager::instance()->drawTile(name));
		}
		else {
			pillThree.push_back(TileManager::instance()->drawTile(name));
		}
	}
	availableTiles.push_back(pillOne.back());
	availableTiles.push_back(pillTwo.back());
	availableTiles.push_back(pillThree.back());
}

SpecialNode::~SpecialNode()
{
}

//void SpecialNode::attackPlayer() {
//	// 1.Calculate damage
//	int dmg = 0;
//	for (const auto& tile : *getTiles()) {
//		if (tile->getUnit()->isHostile()) {
//			dmg++;
//		}
//	}
//	// 2.Attack players within borough
//	for (const auto& p : owners) {
//		cout << "Army is attacking " << p->getName() << " inside " << getName() << endl;
//		p->takeDamage(dmg);
//	}
//}

void SpecialNode::removeTile(int pillId) {
	switch (pillId) {
	case 1:
		pillOne.pop_back();
		break;
	case 2:
		pillOne.pop_back();
		break;
	default:
		pillThree.pop_back();
		break;
	}
}

vector<TileP>* SpecialNode::getTiles() {
	availableTiles.clear();
	if (pillOne.size() > 0) availableTiles.push_back(pillOne.back());
	if (pillTwo.size() > 0) availableTiles.push_back(pillTwo.back());
	if (pillThree.size() > 0) availableTiles.push_back(pillThree.back());
	return &availableTiles;
}

bool SpecialNode::isFree() {
	if (GameManager::instance()->isAdvanced()) {
		if (owners.size() == 2) return false;
		return true;
	}
	else {
		if (owners.size() == 1) return false;
		return true;
	}
}

void SpecialNode::exitZone(Player* player) {
	vector<Player*>::iterator index;
	index = find(owners.begin(), owners.end(), player);
	owners.erase(index);
}
