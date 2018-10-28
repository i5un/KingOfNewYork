#include "Map.h"

Map::Map(string name, vector<string>&zones, vector<pair<int, int>>&edges, vector<int>&starting,bool test)
	:name(name), valid(true),nodeZero(new Node("*** Zone Zero ***"))
{
	if (zones.size() == 0 || edges.size() == 0) {
		valid = false;
		return;
	}
	for (size_t i = 0; i < zones.size(); i++) {
		addVertex(zones[i]);
	}

	for (size_t i = 0; i < edges.size(); i++)
	{
		addEdge(zones[edges[i].first], zones[edges[i].second]);
	}

	for (size_t i = 0; i < starting.size(); i++)
	{
		nodeZero->addEdge(battleGround[zones[starting[i]]]);
	}
	if(!test) addUnits();
}


Map::~Map()
{
}

void Map::printMap() {
	for (auto it = battleGround.cbegin(); it != battleGround.cend(); ++it)
	{
		cout << it->second->getName();
		if (it->second->getOwners()->size()>0) {
			cout << " | [";
			for (auto &player : as_const(*(it->second->getOwners())))
			{
				cout << player->getName() << " ";
			}
		}
		else {
			cout <<"]"<< endl;
		}
	}
}

void Map::addVertex(string vname) {
	battleGround[vname] = new Node(vname);
	if (vname.find("Manhattan") != string::npos) {
		ManhattanArea.push_back(battleGround[vname]);
	}
}

void Map::addEdge(string source, string des) {
	Node* src_node = battleGround[source];
	Node* des_node = battleGround[des];
	src_node->addEdge(des_node);
}

bool Map::verifyMap(bool log) {
	/*
		1) check if the graph is connected using BFS
		2) check if each vertex is a node
	*/
	// creates a queue to perform BFS
	list<Node*> queue;

	// To track all the visited vertices
	map<Node*, bool> visited;

	// Check if map object was properly constructed 
	if (this == nullptr || !valid) goto RESOLVE;

	// Mark the first vertex as visited and starts and search from there
	visited[nodeZero] = true;
	queue.push_back(nodeZero);

	if(log) cout << "Traversing all zones..." << endl;

	//repeat the following until the end
	while (!queue.empty()) {
		// Get the current vertext to start traversing
		Node* current = queue.front();

		// Check if it's a node

		if (current->getName() == "") break;

		if(log)cout <<"*" <<current->getName() << endl;
		queue.pop_front();

		for (size_t i = 0; i < current->getAdj()->size(); i++) {
			if (!visited[(*current->getAdj())[i]]) {
				visited[(*current->getAdj())[i]] = true;
				queue.push_back((*current->getAdj())[i]);
			}
		}
	}

RESOLVE:cout << "Check completed" << endl;
	if (this != nullptr && valid && visited.size()-1 == battleGround.size()) {
		cout << "Map constructed successfuly!" << endl;
		return true;
	}
	cout << "Map is invalid!" << endl;
	return false;
}

void Map::getPath(Player* player, vector<Node*>& destination) {
	if (player->getCurrentLoc() == nullptr) {
		//Player hasn't moved to any location yet, return all available zones
		vector<Node*>* zones = nodeZero->getAdj();
		for (auto &node : as_const(*zones))
		{
			if (node->isFree(player)) {
				destination.push_back(node);
			}
		}
	}
	else {
		//Player is moving from a borrowth to a new one
		vector<Node*>* zones = player->getCurrentLoc()->getAdj();
		for (auto &node : as_const(*zones)) {
			if (node->isFree(player)) {
				destination.push_back(node);
			}
		}
	}
}

void Map::globalAttack() {
	for (auto const& zone : battleGround) {
		// Trigger all attacks from all zones except Manhattan
		if (zone.first.find("Manhattan") == string::npos) {
			zone.second->attack();
		}
	}
	// Trigget attack from Manhattan
	for (auto &zone : as_const(ManhattanArea))
	{
		zone->attack(inManhattan);
	}
}

void Map::setInManhattan(Player* player) { inManhattan=player; }
vector<Node*>* Map::getManhattanArea() { return &ManhattanArea; }

void Map::addUnits() {
	UnitManager::setup();
	for (auto const& key : battleGround) {
		// Fill the zones that aren't part of Manhattan
		if (key.first.find("Manhattan") == string::npos) {
			for (size_t i = 0; i < 9; i++)
			{
				key.second->addUnit(UnitManager::drawBuilding());
			}
		}
	}
	for (auto &zone : as_const(ManhattanArea)) {
		for (size_t i = 0; i < 3; i++)
		{
			zone->addUnit(UnitManager::drawBuilding());
		}
	}
}