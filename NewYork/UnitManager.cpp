#include "UnitManager.h"

vector<Building*> UnitManager::buildings;

void UnitManager::setup() {
	for (size_t i = 0; i < 22; i++)
	{
		buildings.push_back(
			new Building(
				make_pair("Small Office", "Jeep"),
				make_pair(make_pair("Star", 1), make_pair("Health", 2)),
				make_pair(1, 2)
			)
		);
	}
	for (size_t i = 0; i < 8; i++)
	{
		buildings.push_back(
			new Building(
				make_pair("Medium Office", "Jet"),
				make_pair(make_pair("Star", 2), make_pair("Energy", 3)),
				make_pair(2, 3)
			)
		);
	}
	for (size_t i = 0; i < 3; i++)
	{
		buildings.push_back(
			new Building(
				make_pair("Small Hospital", "Jet"),
				make_pair(make_pair("Star", 2), make_pair("Energy", 3)),
				make_pair(2, 3)
			)
		);
	}
	for (size_t i = 0; i < 3; i++)
	{
		buildings.push_back(
			new Building(
				make_pair("Power Plant", "Jet"),
				make_pair(make_pair("Energy", 2), make_pair("Energy", 3)),
				make_pair(2, 3)
			)
		);
	}
	for (size_t i = 0; i < 3; i++)
	{
		buildings.push_back(
			new Building(
				make_pair("Large Office", "Tank"),
				make_pair(make_pair("Star", 3), make_pair("Star", 3)),
				make_pair(3, 4)
			)
		);
	}
	for (size_t i = 0; i < 3; i++)
	{
		buildings.push_back(
			new Building(
				make_pair("Large Hospital", "Tank"),
				make_pair(make_pair("Health", 3), make_pair("Star", 3)),
				make_pair(3, 4)
			)
		);
	}
	for (size_t i = 0; i < 3; i++)
	{
		buildings.push_back(
			new Building(
				make_pair("Large Power Plant", "Tank"),
				make_pair(make_pair("Energy", 3), make_pair("Star", 3)),
				make_pair(3, 4)
			)
		);
	}
	Shuffle();
}

void UnitManager::Shuffle() {
	random_shuffle(begin(buildings), end(buildings));
}

Building* UnitManager::drawBuilding() {
	Building* target = buildings.back();
	buildings.pop_back();
	return target;
}