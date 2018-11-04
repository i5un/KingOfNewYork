#include"GameManager.h"

int main() {
	try {
		GameManager::instance()->OnStart();
	}
	catch (const exception& e) {
		std::cout << e.what() << endl;
	}
	std::cin.get();
}