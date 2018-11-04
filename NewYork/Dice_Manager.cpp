#include "Dice_Manager.h"

int Dice_Manager::counter = 0;

Dice_Manager::Dice_Manager()
{
	counter++;
	srand(time(0)+counter);
}


Dice_Manager::~Dice_Manager()
{
}

const rollResult& Dice_Manager::rollDice(int extraDice, bool canReroll) {
	string input;
	vector<int> tempResult;
	vector<int> discardIndices;
	bool skip = false;
	int rerollCount = chances;
	finalResult.clear();
	int newDice;

	while (rerollCount > 0 && !skip) {
		rerollCount--;
		if (discardIndices.size() > 0) {
			// these are re-rolls
			cout << ">> Rerolling " << discardIndices.size() << " dice" << endl;
			for (size_t i = 0; i < discardIndices.size(); i++) {
				newDice = rand() % 6;
				tempResult[discardIndices[i]] = newDice;
				stat[getDiceName(newDice)]++;
			}
		}
		else {
			// This is the first roll
			for (int i = 0; i < diceCount + extraDice; i++)
			{
				newDice = rand() % 6;
				tempResult.push_back(newDice);
				if (!canReroll) {
					skip = true;
					rerollCount = 0;
				}
				else {
					stat[getDiceName(newDice)]++;
				}
			}
		}
		// add to history to record

		if (canReroll) {
			cout << "You've rolled: " << endl;
			printResult(tempResult);
		}

		while (true && rerollCount > 0) {
			cout << endl << ">> You have " << rerollCount << " chance(s) left." << endl;
			cout << "Type in the id(s) of the dice you wish to reroll and press Enter..." << endl;
			cout << "Type in \"all\" to reroll all dice" << endl;
			cout << "To skip reroll, just press Enter" << endl;
			getline(cin, input);

			//To skip the re-roll phase
			if (input.length() == 0) {
				skip = true;
				break;
			};

			//To re-roll all dice
			if (input == "all") {
				for (int i = 0; i < diceCount + extraDice; i++)
				{
					discardIndices.push_back(i);
				}
				break;
			}

			//checks whether the input from user is valid or not, if not prompt user to re-enter 
			if (!checkValide(input, discardIndices)) {
				continue;
			}
			else {
				break;
			}
		}
	}

	// stack up the dice for easier reading
	for (size_t i = 0; i < tempResult.size(); i++)
	{
		switch (tempResult[i]) {
		case 0:
			finalResult["Energy"]++;
			break;
		case 1:
			finalResult["Heal"]++;
			break;
		case 2:
			finalResult["Attack"]++;
			break;
		case 3:
			finalResult["Celebrity"]++;
			break;
		case 4:
			finalResult["Destruction"]++;
			break;
		case 5:
			finalResult["Ouch!"]++;
			break;
		}
	}

	if (canReroll) {
		cout << "\n..........Rolling stage completed...........\n" << endl;
		cout << "Your roll stats..." << endl;
		for (auto const& x : stat) {
			cout << x.first << " x" << x.second << endl;
		}
	}
	return finalResult;
}


bool Dice_Manager::checkValide(string input, vector<int>& reroll) {
	reroll.clear();
	for (size_t i = 0; i < input.length(); i++)
	{
		int t1 = input[i] - '0';
		if (i % 2 != 0) {
			if (input[i] != ' ') {
				cout << ">> Invalid format, must be seperated by \"space\"" << endl;
				return false;
			}
			continue;
		}
		else if (t1<0 || t1>diceCount - 1) {
			cout << "Out of range" << endl;
			return false;
		}

		for (size_t i = 0; i < reroll.size(); i++)
		{
			if (reroll[i] == t1) {
				cout << ">> Invalid format, can't reroll the same dice" << endl;
				return false;
			}
		}
		reroll.push_back(t1);
	}
	return true;
}

void Dice_Manager::printResult(vector<int>& arr) {
	for (size_t i = 0; i < arr.size(); i++)
	{
		cout << i << "-" << getDiceName(arr[i]) << "  ";
	}
	cout << endl;
}
string Dice_Manager::getDiceName(int d) {
	switch (d) {
	case 0:
		return "Energy";
	case 1:
		return "Heal";
	case 2:
		return "Attack";
	case 3:
		return "Celebrity";
	case 4:
		return "Destruction";
	default:
		return "Ouch!";
	}
}