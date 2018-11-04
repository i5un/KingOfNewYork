#include "TileManager.h"
#include"json.hpp"

TileManager* TileManager::m_instance = nullptr;

TileManager::TileManager() :index(0){
	ifstream stream(".\\Resources\\Tiles.json");
	nlohmann::json content;
	try {
		content = nlohmann::json::parse(stream);
	}
	catch (nlohmann::json::parse_error &e) {
		std::cerr << e.what() << std::endl;
	}

	map<int, shared_ptr<Unit>> allUnits;

	for (size_t i = 0; i < content["units"].size(); i++)
	{
		allUnits[content["units"][i]["id"]] = make_shared<Unit>(
			content["units"][i]["name"],
			content["units"][i]["health"],
			content["units"][i]["reward"][0],
			content["units"][i]["reward"][1],
			content["units"][i]["type"]
			);
	}
	for (size_t i = 0; i < content["tiles"].size(); i++)
	{
		int first = content["tiles"][i]["type"][0];
		int second = content["tiles"][i]["type"][1];
		int stack = content["tiles"][i]["stack"];

		for (size_t i = 0; i < stack; i++)
		{
			tiles.push_back(make_shared<Tile>(allUnits[first], allUnits[second]));
		}
	}

	random_shuffle(begin(tiles), end(tiles));
}

TileManager* TileManager::instance() {
	if (m_instance == nullptr) {
		m_instance = new TileManager();
	}
	return m_instance;
}

shared_ptr<Tile> TileManager::drawTile(string& name) {
	return tiles[index++];
}