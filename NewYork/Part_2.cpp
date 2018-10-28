#include"MapLoader.h"
#include<iostream>

int main() {
	MapLoader::loadMap("KingOfNewYork.map");

	std::cout << "Press any key to test the 2nd map" << std::endl;
	std::cin.get();
	MapLoader::loadMap("map1.map");

	std::cout << "Press any key to test the 3rd map" << std::endl;
	std::cin.get();
	MapLoader::loadMap("map2.map");

	std::cin.get();
}