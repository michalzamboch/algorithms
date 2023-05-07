#pragma once
#include "libs.h"

class Maze
{
private:
	int** area = nullptr;
	int* start = nullptr;
	int* finish = nullptr;
	int height = 0;
	int width = 0;
	bool canWritePath;
	std::string readFile;
	std::vector<std::array<int, 2>>path;

	int** twoDimArr(int x, int y);
	void findStart();
	void findFinish();
	void clearArea();
	void innerPassage(int x, int y);
	void nextStep(int x, int y);
	void directorionSet(int x, int y);
	
	bool canEnter(int x, int y);
	bool isInFinish(int x, int y);

	void blockPath(int x, int y);
	void writePath(int x, int y);
	void releasePath();

	void writeFinalPath();

public:
	Maze(std::string soubor);
	~Maze();

	void writeOut();

	void draw();
	void findPath();
	void loadMap();
	void writeResulttoFile();
};
