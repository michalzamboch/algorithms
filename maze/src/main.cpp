#include "libs.h"
#include "Maze.h"

using namespace std;

int main()
{
	Maze maze("map.txt");

	maze.loadMap();
	maze.findPath();
	maze.draw();
	maze.writeResulttoFile();

	return 0;
}