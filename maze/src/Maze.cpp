#include "libs.h"
#include "Maze.h"

using namespace std;

Maze::Maze(string soubor)
{
    this->readFile = soubor;
    string line;
    ifstream mapFile(this->readFile);

    mapFile >> line;
    this->height = std::stoi(line);
    
    mapFile >> line;
    this->width = std::stoi(line);
    mapFile.close();

    this->area = this->twoDimArr(this->height, this->width);

    this->finish = new int[2];

    this->start = new int[2];

    canWritePath = true;
}

Maze::~Maze()
{
    this->path.clear();

    delete[] this->finish;
    this->finish = nullptr;

    delete[] this->start;
    this->start = nullptr;

    for (int i = 0; i < this->height; i++)
    {
        delete[] this->area[i];
    }
    delete[] this->area;
}

void Maze::draw()
{
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            switch (area[i][j])
            {
            case PATH: cout << STR_PATH;
                break;
            case WALL: cout << STR_WALL << STR_WALL;
                break;
            case START: cout << STR_START;
                break;
            case FINISH: cout << STR_FINISH;
                break;
            case TEMP_PATH: cout << STR_TEMP_PATH;
                break;
            case BLOCK: cout << STR_BLOCK;
                break;
            case FINAL_PATH: cout << STR_FINAL_PATH;
                break;
            }
        }
        cout << endl;
    }
}

void Maze::findPath()
{
    this->canWritePath = true;
    this->path.clear();
    this->findStart();
    this->findFinish();
    this->clearArea();

    innerPassage(this->start[0], this->start[1]);
    
    this->clearArea();
    this->writeFinalPath();
}

void Maze::innerPassage(int x, int y)
{
    this->directorionSet(x, y + 1);
    this->directorionSet(x, y - 1);
    this->directorionSet(x + 1, y);
    this->directorionSet(x - 1, y);
}

void Maze::directorionSet(int x, int y)
{
    if (this->isInFinish(x, y) == true)
    {
        this->canWritePath = false;
    }

    if (this->canEnter(x, y) == true)
    {
        this->nextStep(x, y);
    }
}

void Maze::nextStep(int x, int y)
{
    this->writePath(x, y);
    this->area[x][y] = TEMP_PATH;
    this->innerPassage(x, y);
    this->blockPath(x, y);
    this->releasePath();
}

bool Maze::canEnter(int x, int y)
{
    if ((x < 0) || (x >= this->width))
    {
        return false;
    }
    if ((y < 0) || (y >= this->height))
    {
        return false;
    }

    if (area[x][y] == PATH)
    {
        return true;
    }

    return false;
}

bool Maze::isInFinish(int x, int y)
{
    if ((x == this->finish[0]) && (y == this->finish[1]))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Maze::blockPath(int x, int y)
{
    if (this->area[x][y] != FINAL_PATH && this->area[x][y] != START
        && this->area[x][y] != WALL && this->area[x][y] != FINISH)
    {
        this->area[x][y] = BLOCK;
    }
}

void Maze::writePath(int x, int y)
{
    if (this->canWritePath == true)
    {
        array<int, 2>tmp{x, y};
        this->path.push_back(tmp);
    }
}

void Maze::releasePath()
{
    if (this->canWritePath == true)
    {
        this->path.pop_back();
    }
}

void Maze::writeFinalPath()
{
    for (unsigned int i = 0; i < this->path.size(); i++)
    {
        this->area[this->path.at(i)[0]][this->path.at(i)[1]] = FINAL_PATH;
    }
}

void Maze::findStart()
{
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            if (area[i][j] == START)
            {
                this->start[0] = i;
                this->start[1] = j;
            }
        }
    }
}

void Maze::writeOut()
{
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            cout << area[i][j];
        }
        cout << endl;
    }
}

void Maze::findFinish()
{
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            if (area[i][j] == FINISH)
            {
                this->finish[0] = i;
                this->finish[1] = j;
            }
        }
    }
}

void Maze::clearArea()
{
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            if (area[i][j] != FINISH && area[i][j] != START && area[i][j] != WALL)
            {
                area[i][j] = PATH;
            }
        }
    }
}

int** Maze::twoDimArr(int x, int y)
{
    int** result;
    result = new int * [x];

    for (int i = 0; i < x; i++)
    {
        result[i] = new int[y];
    }

    return result;
}

void Maze::loadMap()
{
    string line;
    ifstream mapFile(this->readFile);
    mapFile >> line;
    mapFile >> line;

    int i = 0;
    while (mapFile >> line)
    {
        if (line.length() == this->width)
        {
            int j = 0;
            for (const auto &c : line)
            {
                this->area[i][j] = c - '0';
                j++;
            }
        }
        i++;
    }

    mapFile.close();
}

void Maze::writeResulttoFile()
{
    if (this->path.size() == 0)
    {
        cout << "Path can not be written to file." << endl;
        cout << "Path have not been found yet." << endl;
        return;
    }
    
    string writeFile = this->readFile;
    writeFile.insert(writeFile.length() - 4, "-path");

    ofstream output;
    output.open(writeFile);
    output << this->height << "\n";
    output << this->width << "\n";
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            output << area[i][j];
        }
        output << "\n";
    }

    output.close();
}
