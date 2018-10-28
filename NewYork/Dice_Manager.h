#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<time.h>
#include<map>

using namespace std;

class Dice_Manager
{
public:
	Dice_Manager();
	~Dice_Manager();
	map<string, int>* rollDice();
	void addDice();
private:
	int chances;
	int diceCount;
	bool checkValide(string, vector<int>&);
	void printResult(vector<int>&);
	void summarize(vector<int>&);

	map<string,int> final;
	map<string,int> stat;
	string getDiceName(int);
};

