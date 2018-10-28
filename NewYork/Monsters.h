#pragma once
#include<string>
#include<vector>
#include<algorithm>
#include<iostream>

using namespace std;

class Monsters
{
public:
	class Monster {
	public:
		Monster(string name) :name(name) {};
		string getName() { return name; };
	private:
		const string name;
	};
	static Monster* pickMonster(int);
	static void displayMonsters();
private:
	static vector<Monster*>* monsters;
};
