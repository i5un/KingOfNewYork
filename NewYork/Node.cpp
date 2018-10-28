#include "Node.h"
#include "Player.h"

Node::Node(){}

Node::Node(string name)
	:name(name)
{
}


Node::~Node()
{
}

string Node::getName() {
	return name;
}

bool Node::enterZone(Player* player) {
	if (isFree(player)) {
		owners.push_back(player);
		return true;
	}
	else {
		return false;
	}
}

void Node::exitZone(Player* player) {
	owners.erase(remove(owners.begin(), owners.end(), player), owners.end());
}

vector<Node*>* Node::getAdj() {
	return &adj;
}

void Node::addEdge(Node* node) {
	adj.push_back(node);
}

vector<Player*>* Node::getOwners() {
	return &owners;
}

bool Node::isFree(Player* player) {
	if (name.find("Manhattan")!=string::npos) {
		// This node is part of Manhattan, can only have 1 player
		if (owners.size() == 1) {
			// A player is already present or player is already in this particular zone, cannt move here. 
			return false;
		}
	}
	else {
		// This node is not part of Manhattan
		if (owners.size() >= 2) {
			return false;
		}
	}
	return true;
}

void Node::addUnit(Building* unit) {
	units.push_back(unit);
}

void Node::attack(Player* target) {
	// 1.Calculate damage

	// 2.Attack players within borough

	// Attack from Manhattan will be handled by the Map class
	if (name.find("Manhattan") == string::npos) {
		if (target == nullptr) {
			cout << "Army is attacking all players inside " << name << endl;
			// No target is provided, will attack all monsters within this borough
		}
		else {
			// A target is provided. All military units will attack this target even if it's not inside this borough
			cout << "Army is attacking " << target->getName() << " inside " << name << endl;
		}
	}
}

void Node::getUnits(vector<Building*>& targets) {
	for (auto &item : as_const(units)) {
		targets.push_back(item);
	}
}