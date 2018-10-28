#pragma once
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

class Map;

class MapLoader
{
public:
	static Map* currentMap;
	static void loadMap(std::string,bool=false);
};