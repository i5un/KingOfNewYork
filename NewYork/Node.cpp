#include "Node.h"
#include "Player.h"
#include "TileManager.h"

Node::Node(){}

Node::Node(string name,bool isManhattan)
	:name(name)
{
	//If currently constructing Manhattan, let SpecialNode class handle the following code
	if (isManhattan || name=="ZoneZero")return;

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

Node::~Node()
{
}

void Node::addEdge(Node* node) {
	adj.push_back(node);
}

bool Node::isFree() {
	if (owners.size()<2) {
		return true;
	}
	return false;
}

void Node::exitZone(Player* player) {
	vector<Player*>::iterator index;
	index = find(owners.begin(), owners.end(), player);
	if(index!=owners.end()) owners.erase(index);
}

void Node::attackPlayer(Player* specialTarget) {
	// 1.Calculate damage
	int dmg = 0;
	for (const auto& tile : *getTiles()) {
		if (tile->getUnit()->isHostile()) {
			dmg++;
		}
	}
	// 2.Attack players within borough

	if (specialTarget != nullptr) {
		cout << ">> Army is attacking " << specialTarget->getName() << " inside " << name << endl;
		specialTarget->takeDamage(dmg);
	}
	else {
		for (const auto& p : owners) {
			cout << ">> Army is attacking " << p->getName() << " inside " << name << endl;
			p->takeDamage(dmg);
		}
	}
}

void Node::removeTile(int pillId) {
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

vector<TileP>* Node::getTiles() {
	availableTiles.clear();
	if (pillOne.size() > 0) availableTiles.push_back(pillOne.back());
	if (pillTwo.size() > 0) availableTiles.push_back(pillTwo.back());
	if (pillThree.size() > 0) availableTiles.push_back(pillThree.back());
	return &availableTiles;
}