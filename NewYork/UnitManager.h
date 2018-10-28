#pragma once
#include<vector>
#include<string>
#include<iostream>
#include"json.hpp"

using namespace std;

struct Building
{
public:
	Building(pair<string, string> type, pair<pair<string, int>, pair<string, int>> rewards, pair<int, int> health)
		: type(type), reward(rewards), health(health)
	{
	};
	void printInfo() {
		std::cout << getName() << " - " << "Hp:" << getHealth() << " | Reward:" << getReward()->first << " x" << getReward()->second << endl;
	}
	string getName() {
		if (!armed) return type.first;
		return type.second;
	}
	pair<string, int>* getReward() {
		if (!armed) return &(reward.first);
		return &(reward.second);
	}
	int getHealth() {
		if (!armed) return health.first;
		return health.second;
	}
	void destroy() {
		if (!armed) armed = true;
		destroyed = true;
	}
	~Building() {
	};
private:
	pair<pair<string, int>, pair<string, int>> reward;
	pair<string, string> type;
	pair<int, int> health;
	bool armed=false,destroyed=false;
};

class UnitManager
{
public:
	void static setup();
	void static Shuffle();
	static Building* drawBuilding();
private:
	static vector<Building*> buildings;
};

