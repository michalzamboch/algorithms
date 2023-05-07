#include "Knihovny.h"
#include "Bludiste.h"

using namespace std;

Bludiste::Bludiste(string soubor)
{
    this->cteciSoubor = soubor;
    string radek;
    ifstream mapaSoubor(this->cteciSoubor);

    mapaSoubor >> radek;
    this->vyska = std::stoi(radek);
    
    mapaSoubor >> radek;
    this->sirka = std::stoi(radek);
    mapaSoubor.close();

    this->plocha = this->twoDimArr(this->vyska, this->sirka);

    this->cil = new int[2];

    this->start = new int[2];

    zapisovatCestu = true;
}

Bludiste::~Bludiste()
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

void Bludiste::vykresli()
{
    for (int i = 0; i < this->vyska; i++)
    {
        for (int j = 0; j < this->sirka; j++)
        {
            switch (plocha[i][j])
            {
            case CESTA: cout << STR_CESTA;
                break;
            case ZED: cout << STR_ZED << STR_ZED;
                break;
            case START: cout << STR_START;
                break;
            case CIL: cout << STR_CIL;
                break;
            case TEMP_CESTA: cout << STR_TEMP_CESTA;
                break;
            case BLOK: cout << STR_BLOK;
                break;
            case FINALNI_CESTA: cout << STR_FINALNI_CESTA;
                break;
            }
        }
        cout << endl;
    }
}

void Bludiste::najdiCestu()
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

void Bludiste::vnitrniPruchod(int x, int y)
{
    this->nastaveniSmeru(x, y + 1);
    this->nastaveniSmeru(x, y - 1);
    this->nastaveniSmeru(x + 1, y);
    this->nastaveniSmeru(x - 1, y);
}

void Bludiste::nastaveniSmeru(int x, int y)
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

void Bludiste::dalsiKrok(int x, int y)
{
    this->zapisCestu(x, y);
    this->plocha[x][y] = TEMP_CESTA;
    this->vnitrniPruchod(x, y);
    this->blokujCestu(x, y);
    this->uvolniCestu();
}

bool Bludiste::muzuVstoupit(int x, int y)
{
    if ((x < 0) || (x >= this->sirka))
    {
        return false;
    }
    if ((y < 0) || (y >= this->vyska))
    {
        return false;
    }

    if (plocha[x][y] == CESTA)
    {
        return true;
    }

    return false;
}

bool Bludiste::jeVCili(int x, int y)
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

void Bludiste::blokujCestu(int x, int y)
{
    if (this->plocha[x][y] != FINALNI_CESTA && this->plocha[x][y] != START
        && this->plocha[x][y] != ZED && this->plocha[x][y] != CIL)
    {
        this->plocha[x][y] = BLOK;
    }
}

void Bludiste::zapisCestu(int x, int y)
{
    if (this->zapisovatCestu == true)
    {
        array<int, 2>tmp{x, y};
        this->cesta.push_back(tmp);
    }
}

void Bludiste::uvolniCestu()
{
    if (this->zapisovatCestu == true)
    {
        this->cesta.pop_back();
    }
}

void Bludiste::zapisFinalniCestu()
{
    for (unsigned int i = 0; i < this->cesta.size(); i++)
    {
        this->plocha[this->cesta.at(i)[0]][this->cesta.at(i)[1]] = FINALNI_CESTA;
    }
}

void Bludiste::najdiStart()
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

void Bludiste::vypisBludiste()
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

void Bludiste::najdiCil()
{
    for (int i = 0; i < this->vyska; i++)
    {
        for (int j = 0; j < this->sirka; j++)
        {
            if (plocha[i][j] == CIL)
            {
                this->cil[0] = i;
                this->cil[1] = j;
            }
        }
    }
}

void Bludiste::vycistiPlochu()
{
    for (int i = 0; i < this->vyska; i++)
    {
        for (int j = 0; j < this->sirka; j++)
        {
            if (plocha[i][j] != CIL && plocha[i][j] != START && plocha[i][j] != ZED)
            {
                plocha[i][j] = CESTA;
            }
        }
    }
}

int** Bludiste::twoDimArr(int x, int y)
{
    int** vysledek;
    vysledek = new int * [x];

    for (int i = 0; i < x; i++)
    {
        vysledek[i] = new int[y];
    }

    return vysledek;
}

void Bludiste::nactiMapu()
{
    string radek;
    ifstream mapaSoubor(this->cteciSoubor);
    mapaSoubor >> radek;
    mapaSoubor >> radek;

    int i = 0;
    while (mapaSoubor >> radek)
    {
        if (radek.length() == this->sirka)
        {
            int j = 0;
            for (const auto &c : radek)
            {
                this->plocha[i][j] = c - '0';
                j++;
            }
        }
        i++;
    }

    mapaSoubor.close();
}

void Bludiste::vysledekDoSouboru()
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
