#include "Graph.h"

/* Graph::Graph(string fileName)
Konstruktor pouze na�te jmeno souboru
*/
Graph::Graph(string fileName)
{
    this->fileName = fileName;
}

/* Graph::~Graph()
destruktor
Vyma�e data grafu
*/
Graph::~Graph()
{
    for (int i = 0; i < this->size; i++)
    {
        delete[] this->graph[i];
    }
    delete[] this->graph;
}

/* void Graph::load()
otev�e soubor, p�edan� v konstruktoru
na�te prvn� ��dek, kde je velikost grafu
vytvo�� dvojt� int pole podle na�ten� velikosti
potom �te ��dek po ��dku a data se zapisuj� do pole grafu
*/
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

/* void Graph::solve()
* pouzije funkci isBipartite()
* vyp�e jestli graf je bipartitn� nebo ne
*/
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

/* bool Graph::isBipartite()
* pouze zavol� funkci isBipartite(int **graph, int size, int src)
*/
bool Graph::isBipartite()
{
    return this->isBipartite(this->graph, this->size, 0);
}

/* bool Graph::isBipartite(int **graph, int size, int src)
* Jeden p��stup je zkonrolovat, zda graf je 2-barevn� nebo ne
* pomoc� algoritmu backtracking m coloring problem.
* N�sleduje jednoduch� algoritmus, kter� pomoc� BFS (Breadth First Search) zjist�,
* zda je dan� graf bipartitn� �i nikoli.
* 1. Zdrojov�mu vrcholu p�i�a�te �ERVENOU barvu.
* 2. Vybarv�te v�echny sousedy MODROU barvou.
* 3. Vybarv�te v�echny sousedovy sousedy �ERVENOU barvou.
* 4. T�mto zp�sobem p�i�a�te barvu v�em vrchol�m tak, aby spl�ovala v�echna omezen� probl�mu barven� m zp�soby, kde m = 2.
* 5. Zat�m co p�i p�i�azov�n� barev najdeme souseda, kter� je obarven stejnou barvou jako aktu�ln� vrchol,
* nelze graf obarvit 2 vrcholy (nebo graf nen� bipartitn�)
*/
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

/* void Graph::print()
* V�p�e graf
*/
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

/* void Graph::printInfo()
* vyp�� informace o grafu
*/
void Graph::printInfo()
{
    cout << this->fileName << endl;
    cout << "Size: " << this->size << endl;
}

/* int** Graph::doubleArray(int x, int y)
* vytvo�� a vr�t� dvojt� int pole
*/
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