#pragma once
#include<vector>
#include<string>

using namespace std;

struct Token {
	int count;
};
struct Web :Token {};
struct Jinx :Token {};
struct Souvenir :Token {};
struct Carapace :Token {};

class TokenManager
{
public:
	static void setup();
private:
	static Web* web;
	static Jinx* jinx;
	static Souvenir* souvenir;
	static Carapace* carapace;
};
