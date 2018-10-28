#include "Dice_Manager.h"



Dice_Manager::Dice_Manager()
	:chances(3), diceCount(6)
{}


Dice_Manager::~Dice_Manager()
{
}

map<string, int>* Dice_Manager::rollDice() {
	// Stores user input on which dies to reroll
	string input;

	//Stores result of Rolls temporarly
	vector<int>result;

	// Indices of dice to reroll
	vector<int> reroll;

	// Skip reroll phase
	bool skip = false;

	//reroll as long as chacne is above 0 and not skipped
	while (chances > 0 && !skip) {
		chances--;
		srand(time(NULL));
		if (reroll.size() > 0) {
			// these are re-rolls
			cout << "Rerolling " << reroll.size() << " dice" << endl;
			for (size_t i = 0; i < reroll.size(); i++) {
				int newNum = rand() % 6;
				result[reroll[i]] = newNum;
				stat[getDiceName(newNum)]++;
			}
		}
		else {
			// This is the first roll
			for (int i = 0; i < diceCount; i++)
			{
				int random = rand() % 6;
				result.push_back(random);
				stat[getDiceName(random)]++;
			}
		}
		// add to history to record

		cout << "You've rolled: " << endl << endl;
		printResult(result);

		while (true && chances > 0) {
			cout << endl << "You have " << chances << " chance(s) left." << endl;
			cout << "Type in the id(s) of the dice you wish to reroll and press Enter..." << endl;
			cout << "Type in \"all\" to reroll all dice" << endl;
			cout << "To skip reroll, just press Enter" << endl;
			getline(cin, input);

			if (input.length() == 0) {
				skip = true;
				break;
			};
			if (input == "all") {
				for (int i = 0; i < diceCount; i++)
				{
					reroll.push_back(i);
				}
				break;
			}
			//checks whether the input from user is valid or not, if not prompt user to re-enter 
			if (!checkValide(input, reroll)) {
				continue;
			}
			else {
				break;
			}
		}
	}
	summarize(result);
	return &final;
}

bool Dice_Manager::checkValide(string input, vector<int>& reroll) {
	reroll.clear();
	for (size_t i = 0; i < input.length(); i++)
	{
		int t1 = input[i] - '0';
		if (i % 2 != 0) {
			if (input[i] != ' ') {
				cout << "Invalid format, must be seperated by \"space\"" << endl;
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
				cout << "Invalid format, can't reroll the same dice" << endl;
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

void Dice_Manager::summarize(vector<int>& result) {
	final.clear();
	cout << "..........Rolling stage completed..........." << endl;

	/*
		Display all dice rolled up to now with occurances
	*/
	cout << endl << "Your roll stats..." << endl;
	for (auto const& x : stat) {
		cout << x.first << " x" << x.second << endl;
	}

	/*
		Display the final result of a given turn
	*/
	cout << endl << "..........Final Result.......... " << endl;
	for (size_t i = 0; i < result.size(); i++)
	{
		switch (result[i]) {
		case 0:
			final["Energy"]++;
			break;
		case 1:
			final["Heal"]++;
			break;
		case 2:
			final["Attack"]++;
			break;
		case 3:
			final["Celebrity"]++;
			break;
		case 4:
			final["Destruction"]++;
			break;
		case 5:
			final["Ouch!"]++;
			break;
		}
	}
	// stack up the dice for easier reading
	for (auto const& x : final)
	{
		cout << x.first << " x" << x.second << endl;
	}
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
void Dice_Manager::addDice() {
	diceCount++;
}