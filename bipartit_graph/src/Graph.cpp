#include "Graph.h"

Graph::Graph(string fileName)
{
    this->fileName = fileName;
}

Graph::~Graph()
{
    for (int i = 0; i < this->size; i++)
    {
        delete[] this->graph[i];
    }
    delete[] this->graph;
}

void Graph::load()
{
    string line;
    ifstream file(this->fileName);

    file >> line;
    this->size = stoi(line);

    this->graph = this->doubleArray(this->size, this->size);

    int rowIndex = 0;
    while (file >> line)
    {
        if (line.length() == this->size)
        {
            int columnIndex = 0;
            const char* tmp = line.c_str();
            while (tmp[columnIndex] != '\0')
            {
                this->graph[rowIndex][columnIndex] = tmp[columnIndex] - '0';
                columnIndex++;
            }
            rowIndex++;
        }
    }

    file.close();
}

void Graph::solve()
{
    this->biparttite = this->isBipartite();
    cout << this->fileName << ": ";

    if (this->biparttite == true)
    {
        cout << "je biparttitni." << endl;
    }
    else
    {
        cout << "neni biparttitni." << endl;
    }
}

bool Graph::isBipartite()
{
    return this->isBipartite(this->graph, this->size, 0);
}

bool Graph::isBipartite(int **graph, int size, int src)
{
	int *colorArr = new int[size];
    for (int i = 0; i < size; ++i)
    {
		colorArr[i] = -1;
    }

	colorArr[src] = 1;

	queue <int> q;
	q.push(src);

	while (!q.empty())
	{
		int u = q.front();
		q.pop();

        if (graph[u][u] == 1)
        {
			return false;
        }

		for (int v = 0; v < size; ++v)
		{
			if (graph[u][v] && colorArr[v] == -1)
			{
				colorArr[v] = 1 - colorArr[u];
				q.push(v);
			}
			else if (graph[u][v] && colorArr[v] == colorArr[u])
			{
				return false;
			}
		}
	}

	return true;
}

void Graph::print()
{
    for (int y = 0; y < this->size; y++)
    {
        for (int x = 0; x < this->size; x++)
        {
            cout << this->graph[y][x] << " ";
        }
        cout << endl;
    }
}

void Graph::printInfo()
{
    cout << this->fileName << endl;
    cout << "Size: " << this->size << endl;
}

int** Graph::doubleArray(int x, int y)
{
    int** result;
    result = new int * [y];

    for (int i = 0; i < y; i++)
    {
        result[i] = new int[x];
    }

    return result;
}