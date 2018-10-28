#include "MapLoader.h"
#include "Map.h"
#include<map>

Map* MapLoader::currentMap=nullptr;

void MapLoader::loadMap(string fileName,bool verifyLog)
{
	cout << "opening file: " << fileName << endl;
	fstream mapFile;
	string line;
	string name;

	// Each section of the map file should terminate with a string "end"
	bool startNewSection = true, error = false;
	bool isZone, isEdge, isStart;

	// These sections are required to be present
	map<string, bool> completeCheck;
	completeCheck["name"] = false;
	completeCheck["zone"] = false;
	completeCheck["edge"] = false;
	completeCheck["starting"] = false;

	// These are the arguments that will be passed to the map constructor
	vector<int>starting;
	vector<string> zones;
	vector<pair<int, int>> edges;

	try {
		mapFile.open(fileName);
		if (mapFile.is_open()) {
			while (getline(mapFile, line)) {
				// A line should never be empty
				if (line.length() == 0) {
					error = true;
					break;
				};
				int index = line.find(":");
				if (index >= 0) {
					if (line.substr(0, index) == "name") {
						completeCheck["name"] = true;
						name = line.substr(index + 1, -1);
					}
					else if (line.substr(0, index) == "zones") {
						if (!startNewSection) {
							error = true;
							break;
						}
						completeCheck["zone"] = true;
						startNewSection = false;
						isZone = true;
					}
					else if (line.substr(0, index) == "edges") {
						if (!startNewSection) {
							error = true;
							break;
						}
						completeCheck["edge"] = true;
						startNewSection = false;
						isEdge = true;
					}
					else if (line.substr(0, index) == "starting") {
						if (!startNewSection) {
							error = true;
							break;
						}
						completeCheck["starting"] = true;
						startNewSection = false;
						isStart = true;
					}
					continue;
				}
				else if (line == "end") {
					startNewSection = true;
					isStart = isZone = isEdge = false;
					continue;
				}

				if (isZone) {
					zones.push_back(line.substr(2));
				}
				else if (isEdge) {
					int index = line.find("-");
					try {
						int src = stoi(line.substr(0, index));
						int des = stoi(line.substr(index + 1));
						if (index<0 || src > zones.size() - 1 || des > zones.size() - 1) {
							error = true;
							break;
						};
						edges.push_back(make_pair(src, des));
					}
					catch (invalid_argument e) {
						error = true;
						break;
					}
				}
				else if (isStart) {
					int des = stoi(line);
					if (des > zones.size() - 1 || des < 0) {
						error = true;
						break;
					}
					starting.push_back(des);
				}
			}
			for (auto const& x:completeCheck)
			{
				if (!x.second) {
					error = true;
					break;
				}
			}
			mapFile.close();
		}
		else cout << "Unable to open file" << endl;
	}
	catch (fstream::failure e) {
		std::cerr << "Exception opening/reading/closing file\n";
	}

	/*
		Create a new map if no error has occured
	*/
	if (!error) {
		currentMap = new Map(name, zones, edges, starting,name=="KingOfNewYork"? false:true);
		cout << "Map: "<<name << " loaded" << endl;
		currentMap->verifyMap();
	}
	else {
		cout << "Error occured during loading" << endl;
		delete currentMap;
	}
}