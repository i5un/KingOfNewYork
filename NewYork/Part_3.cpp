#include"Dice_Manager.h"

int main() {
	cout << "Testing with 6 dice" << endl;
	Dice_Manager dm;
	dm.rollDice();
	
	cout << "Press any key to test with 8 dice" << endl;
	cin.get();
	Dice_Manager dm2;
	dm2.addDice();
	dm2.addDice();
	dm2.rollDice();
	cin.get();
}