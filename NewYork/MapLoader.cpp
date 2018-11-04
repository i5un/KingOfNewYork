#include"MapLoader.h"
#include"Map.h"

#include<map>
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<iostream>
#include<Windows.h>
#include<vector>
#include<stdexcept>

Map* MapLoader::loadMap(std::string mapName)
{
	/*
		This portion will go to the "map" folder inside the project directory and display all files with a
		".map" extension
	*/
	std::vector<std::string> files;
	WIN32_FIND_DATA data;
	std::string st;
	HANDLE hFind = FindFirstFile(".\\map\\*", &data);

	//skip map selection process if a map name is already provided
	if (mapName.length() > 0) goto constructMap;

	int selection;

	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			st = data.cFileName;
			if (st.length() > 3 && st.substr(st.length() - 4, -1) == ".map") {
				files.push_back(data.cFileName);
			}
		} while (FindNextFile(hFind, &data));
		FindClose(hFind);
	}

	if (files.size() > 0) {
		std::cout << "Here are the list of maps available..." << std::endl;
		int counter = 0;
		for (const std::string& st : files) {
			std::cout << counter++ << "-" << st << std::endl;
		}
		std::cout << "Select the map you wish to load..." << std::endl;
		do {
			std::getline(std::cin, st);
			try {
				selection = stoi(st);
				if (selection >= files.size()) {
					throw exception();
				}
			}
			catch (...) {
				std::cout << ">> Invalid selection, please try again..." << std::endl;
				continue;
			}		
			std::cout << ">> Loading... " << files[selection] << std::endl;
			break;
		} while (true);
	}
	else {
		std::cout << "Your map folder is empty..." << std::endl;
		std::cout << "Game will now exit..." << std::endl;
		return nullptr;
	}

	/*
		This portion executes after a map has been selected by the player.  The program will then read the content of
		the file and tries to build a map.
	*/
constructMap:
	fstream mapFile;
	string line;
	string name;

	// Each section of the map file should terminate with a string "end"
	bool startNewSection = true;
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
	
	string fileName = mapName.length() > 0 ? mapName : files[selection];
	try {
		mapFile.open(".\\map\\"+fileName);
		if (mapFile.is_open()) {
			while (getline(mapFile, line)) {
				// A line should never be empty
				if (line.length() == 0) {
					throw exception();
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
							throw exception();
							break;
						}
						completeCheck["zone"] = true;
						startNewSection = false;
						isZone = true;
					}
					else if (line.substr(0, index) == "edges") {
						if (!startNewSection) {
							throw exception();
							break;
						}
						completeCheck["edge"] = true;
						startNewSection = false;
						isEdge = true;
					}
					else if (line.substr(0, index) == "starting") {
						if (!startNewSection) {
							throw exception();
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
							throw exception();
							break;
						};
						edges.push_back(make_pair(src, des));
					}
					catch (...) {
						throw exception();
						break;
					}
				}
				else if (isStart) {
					int des = stoi(line);
					if (des > zones.size() - 1 || des < 0) {
						throw exception();
						break;
					}
					starting.push_back(des);
				}
			}
			for (auto const& x:completeCheck)
			{
				if (!x.second) {
					throw exception();
					break;
				}
			}
			mapFile.close();
		}else throw exception(">> Unable to open file");
	}
	catch (const std::exception e) {
		//std::cout << e.what() << std::endl;
		throw exception(">> Invalid map file format!");
	}

	/*
		Create a new map if no error has occured
	*/
	Map* currentMap = new Map(name, zones, edges, starting);
	cout << "\n>> Map: " << name << " loaded\n" << endl;
	if (currentMap->verifyMap()) return currentMap;
	
	//Validation failled
	delete currentMap;
	throw exception(">> Invalid map created.");
}