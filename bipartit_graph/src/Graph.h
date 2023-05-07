#pragma once

#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Graph
{
private:
	int** graph = nullptr;
	int size = 0;
	string fileName;
	bool biparttite;

	int** doubleArray(int x, int y);
	bool isBipartite(int** graph, int size, int src);
	bool isBipartite();

public:
	Graph(std::string fileName);
	~Graph();

	void load();
	void solve();

	void print();
	void printInfo();
};
