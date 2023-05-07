#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <sstream>

#include "Graph.h"

using namespace std;

/*
Praktická implementace pro demostraci algoritmu
*/
void implemenatce(string fileName)
{
	Graph* graph = new Graph(fileName);

	graph->load();
	graph->printInfo();
	graph->print();
	graph->solve();

	delete graph;

	cout << endl << "----------------------------" << endl << endl;
}

void BipartitniGraf()
{
	implemenatce("BipartitniGraf.txt");
}

void BipartitniGraf2()
{
	implemenatce("BipartitniGraf2.txt");
}

void CyklickyGraf()
{
	implemenatce("CyklickyGraf.txt");
}

int main()
{
	// 3 grafy k vyøešení
	BipartitniGraf();
	BipartitniGraf2();
	CyklickyGraf();

	return 0;
}