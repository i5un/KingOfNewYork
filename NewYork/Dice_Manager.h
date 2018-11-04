#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<time.h>
#include<map>
#include<ctime>

using namespace std;
typedef map<string, int> rollResult;

class Dice_Manager
{
public:
	Dice_Manager();
	~Dice_Manager();
	const rollResult& rollDice(int extraDice=0,bool canReroll=true);
private:
	static int counter;
	const int chances=3;
	const int diceCount=6;
	bool checkValide(string, vector<int>&);
	void printResult(vector<int>&);

	rollResult finalResult;
	rollResult stat;
	string getDiceName(int);
};

