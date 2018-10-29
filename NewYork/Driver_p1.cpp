#include"GameManager.h"
#include<iostream>
#include<string>

int main() {
	try
	{
		//enables debug mode
		GameManager::StartGame(true);
	}
	catch (const std::exception e)
	{
		std::cout << e.what() << endl;
	}

	std::cout << "Press any key to terminate game...";
	std::cin.get();
}