#include "libs.h"
#include "Maze.h"

using namespace std;

int main()
{
	Maze maze("mapa.txt");

	maze.nactiMapu();
	maze.najdiCestu();
	maze.vykresli();
	maze.vysledekDoSouboru();

	return 0;
}