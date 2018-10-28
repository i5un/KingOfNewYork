#include "TokenManager.h"


Web* TokenManager::web;
Jinx* TokenManager::jinx;
Souvenir* TokenManager::souvenir;
Carapace* TokenManager::carapace;

void TokenManager::setup() {
	web->count=13;
	jinx->count = 13;
	souvenir->count = 5;
	carapace->count = 15;
}
