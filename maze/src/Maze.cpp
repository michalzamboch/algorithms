#include "libs.h"
#include "Maze.h"

using namespace std;

Maze::Maze(string soubor)
{
    this->cteciSoubor = soubor;
    string line;
    ifstream mapaSoubor(this->cteciSoubor);

    mapaSoubor >> line;
    this->vyska = std::stoi(line);
    
    mapaSoubor >> line;
    this->sirka = std::stoi(line);
    mapaSoubor.close();

    this->plocha = this->twoDimArr(this->vyska, this->sirka);

    this->cil = new int[2];

    this->start = new int[2];

    zapisovatCestu = true;
}

Maze::~Maze()
{
    this->cesta.clear();

    delete[] this->cil;
    this->cil = nullptr;

    delete[] this->start;
    this->start = nullptr;

    for (int i = 0; i < this->vyska; i++)
    {
        delete[] this->plocha[i];
    }
    delete[] this->plocha;
}

void Maze::vykresli()
{
    for (int i = 0; i < this->vyska; i++)
    {
        for (int j = 0; j < this->sirka; j++)
        {
            switch (plocha[i][j])
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

void Maze::najdiCestu()
{
    this->zapisovatCestu = true;
    this->cesta.clear();
    this->najdiStart();
    this->najdiCil();
    this->vycistiPlochu();

    vnitrniPruchod(this->start[0], this->start[1]);
    
    this->vycistiPlochu();
    this->zapisFinalniCestu();
}

void Maze::vnitrniPruchod(int x, int y)
{
    this->nastaveniSmeru(x, y + 1);
    this->nastaveniSmeru(x, y - 1);
    this->nastaveniSmeru(x + 1, y);
    this->nastaveniSmeru(x - 1, y);
}

void Maze::nastaveniSmeru(int x, int y)
{
    if (this->jeVCili(x, y) == true)
    {
        this->zapisovatCestu = false;
    }

    if (this->muzuVstoupit(x, y) == true)
    {
        this->dalsiKrok(x, y);
    }
}

void Maze::dalsiKrok(int x, int y)
{
    this->zapisCestu(x, y);
    this->plocha[x][y] = TEMP_PATH;
    this->vnitrniPruchod(x, y);
    this->blokujCestu(x, y);
    this->uvolniCestu();
}

bool Maze::muzuVstoupit(int x, int y)
{
    if ((x < 0) || (x >= this->sirka))
    {
        return false;
    }
    if ((y < 0) || (y >= this->vyska))
    {
        return false;
    }

    if (plocha[x][y] == PATH)
    {
        return true;
    }

    return false;
}

bool Maze::jeVCili(int x, int y)
{
    if ((x == this->cil[0]) && (y == this->cil[1]))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Maze::blokujCestu(int x, int y)
{
    if (this->plocha[x][y] != FINAL_PATH && this->plocha[x][y] != START
        && this->plocha[x][y] != WALL && this->plocha[x][y] != FINISH)
    {
        this->plocha[x][y] = BLOCK;
    }
}

void Maze::zapisCestu(int x, int y)
{
    if (this->zapisovatCestu == true)
    {
        array<int, 2>tmp{x, y};
        this->cesta.push_back(tmp);
    }
}

void Maze::uvolniCestu()
{
    if (this->zapisovatCestu == true)
    {
        this->cesta.pop_back();
    }
}

void Maze::zapisFinalniCestu()
{
    for (unsigned int i = 0; i < this->cesta.size(); i++)
    {
        this->plocha[this->cesta.at(i)[0]][this->cesta.at(i)[1]] = FINAL_PATH;
    }
}

void Maze::najdiStart()
{
    for (int i = 0; i < this->vyska; i++)
    {
        for (int j = 0; j < this->sirka; j++)
        {
            if (plocha[i][j] == START)
            {
                this->start[0] = i;
                this->start[1] = j;
            }
        }
    }
}

void Maze::vypisMaze()
{
    for (int i = 0; i < this->vyska; i++)
    {
        for (int j = 0; j < this->sirka; j++)
        {
            cout << plocha[i][j];
        }
        cout << endl;
    }
}

void Maze::najdiCil()
{
    for (int i = 0; i < this->vyska; i++)
    {
        for (int j = 0; j < this->sirka; j++)
        {
            if (plocha[i][j] == FINISH)
            {
                this->cil[0] = i;
                this->cil[1] = j;
            }
        }
    }
}

void Maze::vycistiPlochu()
{
    for (int i = 0; i < this->vyska; i++)
    {
        for (int j = 0; j < this->sirka; j++)
        {
            if (plocha[i][j] != FINISH && plocha[i][j] != START && plocha[i][j] != WALL)
            {
                plocha[i][j] = PATH;
            }
        }
    }
}

int** Maze::twoDimArr(int x, int y)
{
    int** vysledek;
    vysledek = new int * [x];

    for (int i = 0; i < x; i++)
    {
        vysledek[i] = new int[y];
    }

    return vysledek;
}

void Maze::nactiMapu()
{
    string line;
    ifstream mapaSoubor(this->cteciSoubor);
    mapaSoubor >> line;
    mapaSoubor >> line;

    int i = 0;
    while (mapaSoubor >> line)
    {
        if (line.length() == this->sirka)
        {
            int j = 0;
            for (const auto &c : line)
            {
                this->plocha[i][j] = c - '0';
                j++;
            }
        }
        i++;
    }

    mapaSoubor.close();
}

void Maze::vysledekDoSouboru()
{
    if (this->cesta.size() == 0)
    {
        cout << "Cesta nejde zapsat do souboru." << endl;
        cout << "Musite nejprve cestu najit." << endl;
        return;
    }
    
    string zapisovaciSoubor = this->cteciSoubor;
    zapisovaciSoubor.insert(zapisovaciSoubor.length() - 4, "-vysledna_cesta");

    ofstream zapis;
    zapis.open(zapisovaciSoubor);
    zapis << this->vyska << "\n";
    zapis << this->sirka << "\n";
    for (int i = 0; i < this->vyska; i++)
    {
        for (int j = 0; j < this->sirka; j++)
        {
            zapis << plocha[i][j];
        }
        zapis << "\n";
    }

    zapis.close();
}
