#include<iostream>
#include<vector>
#include<map>
#include"Map.h"

using namespace std;

int main() {
	cout << "Testing map 1" << endl;
	/*
		The first map is a valid one
	*/
	vector<string> zones;
	zones.push_back("Lower Manhattan");
	zones.push_back("Middle Manhattan");
	zones.push_back("Upper Manhattan");
	zones.push_back("Staten Island");
	zones.push_back("Brooklyn");
	zones.push_back("Queens");
	zones.push_back("Brownx");

	vector<pair<int, int>> edges;
	edges.push_back(make_pair(3, 4));
	edges.push_back(make_pair(3, 5));
	edges.push_back(make_pair(3, 6));
	edges.push_back(make_pair(4, 3));
	edges.push_back(make_pair(4, 5));
	edges.push_back(make_pair(4, 6));
	edges.push_back(make_pair(5, 3));
	edges.push_back(make_pair(5, 4));
	edges.push_back(make_pair(5, 6));
	edges.push_back(make_pair(6, 3));
	edges.push_back(make_pair(6, 4));
	edges.push_back(make_pair(6, 5));
	edges.push_back(make_pair(0, 1));
	edges.push_back(make_pair(0, 3));
	edges.push_back(make_pair(0, 4));
	edges.push_back(make_pair(0, 5));
	edges.push_back(make_pair(0, 6));
	edges.push_back(make_pair(1, 2));
	edges.push_back(make_pair(1, 3));
	edges.push_back(make_pair(1, 4));
	edges.push_back(make_pair(1, 5));
	edges.push_back(make_pair(1, 6));
	edges.push_back(make_pair(2, 3));
	edges.push_back(make_pair(2, 4));
	edges.push_back(make_pair(2, 5));
	edges.push_back(make_pair(2, 6));
	edges.push_back(make_pair(3, 0));
	edges.push_back(make_pair(4, 0));
	edges.push_back(make_pair(5, 0));
	edges.push_back(make_pair(6, 0));

	vector<int> starting1 = { 0, 1 ,2 };
	Map m1("New York", zones, edges,starting1);
	m1.verifyMap();
	
	cout <<endl<< "Press any key to test map 2" << endl;
	cin.get();
	

	/*
		The second is invalid
	*/
	vector<string> zones2;
	zones2.push_back("Staten Island");
	zones2.push_back("Brooklyn");
	zones2.push_back("Queens");
	zones2.push_back("Brownx");

	vector<pair<int, int>> edges2;
	edges2.push_back(make_pair(0, 1));
	edges2.push_back(make_pair(0, 3));
	
	vector<int> starting2 = { 0 };

	Map m2("New York alt", zones2, edges2,starting2);
	m2.verifyMap();
	cin.get();
}