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

void implementation(string fileName)
{
	Graph graph(fileName);

	graph.load();
	graph.printInfo();
	graph.print();
	graph.solve();

	cout << endl << "----------------------------" << endl << endl;
}

int main()
{
	implementation("bipartitGraph.txt");
	implementation("bipartitGraph2.txt");
	implementation("cyclicGraph.txt");
	return 0;
}