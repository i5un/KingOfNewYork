#include "Map.h"

bool isManhattan(string name) {
	if (name.find("Manhattan") != std::string::npos) {
		return true;
	}
	return false;
}

Map::Map(string name, vector<string>&zones, vector<pair<int, int>>&edges, vector<int>&starting)
	:name(name), valid(true),zoneZero(new Node("ZoneZero"))
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
		zoneZero->addEdge(battleGround[zones[starting[i]]]);
	}
}


Map::~Map()
{
}

void Map::printMap() {
	std::cout << "\nCurrent map layout" << std::endl;
	ls
	bool skip = false;
	for (auto it = battleGround.cbegin(); it != battleGround.cend(); ++it)
	{
		SpecialNode* sp = dynamic_cast<SpecialNode*>(it->second); 	
		if (sp == NULL) {
			//Regular zones
			std::cout << it->first << std::endl;
			if (it->second->getOwners()->size() > 0) {
				for(const auto&p : *it->second->getOwners())
					std::cout << "Owner: [" << p->getName() << "]" << std::endl;
			}
			std::cout << "Tiles: " << endl;
			for (const auto& p : *(it->second->getTiles())) {
				prt << p;
			}
			prt << nl;
		}
		else {
			//Manhattan
			if (skip)continue;
			skip = true;
			cout << "Manhattan" << endl;
			if(sp->getOwners()->size()>0)
				for (const auto&p : *sp->getOwners())
					std::cout << "Owner: [" << p->getName() << "]" << std::endl;
			std::cout << "Tiles: " << endl;
			for (const auto& p : *(sp->getTiles())) {
				prt << p;
			}
			prt << nl;
		}
	}
	le
}

void Map::addVertex(string vname) {
	if (isManhattan(vname)) {
		battleGround[vname] = new SpecialNode(vname);
	}
	else {
		battleGround[vname] = new Node(vname);
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
	visited[zoneZero] = true;
	queue.push_back(zoneZero);

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

RESOLVE:
	if (this != nullptr && valid && visited.size()-1 == battleGround.size()) {
		return true;
	}
	cout << "Map is invalid!" << endl;
	return false;
}

void Map::globalAttack() {
	std::cout << ">> Global Attack triggered!!!" << endl;
	bool attacked = false;
	for (auto const& zone : battleGround) {
		// Trigger all attacks from all zones except Manhattan
		if (zone.second->isManhattan()) {
			zone.second->attackPlayer();
		}
		else {
			// Trigget attack from Manhattan
			if (attacked) continue;
			zone.second->attackPlayer();
			attacked = true;
		}
	}
}

