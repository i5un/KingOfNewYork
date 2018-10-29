#include "GameManager.h"



GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::StartGame() {
	WIN32_FIND_DATA data;
	HANDLE hFind = FindFirstFile("C:\\semester2", &data);      // DIRECTORY

	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			std::cout << data.cFileName << std::endl;
		} while (FindNextFile(hFind, &data));
		FindClose(hFind);
	}
}
