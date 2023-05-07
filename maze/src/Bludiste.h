#pragma once
#include "Knihovny.h"

class Bludiste
{
private:
	int** plocha = nullptr;
	int* start = nullptr;
	int* cil = nullptr;
	int vyska = 0;
	int sirka = 0;
	bool zapisovatCestu;
	string cteciSoubor;
	vector<array<int, 2>>cesta;

	int** twoDimArr(int x, int y);
	void najdiStart();
	void najdiCil();
	void vycistiPlochu();
	void vnitrniPruchod(int x, int y);
	void dalsiKrok(int x, int y);
	void nastaveniSmeru(int x, int y);
	
	bool muzuVstoupit(int x, int y);
	bool jeVCili(int x, int y);

	void blokujCestu(int x, int y);
	void zapisCestu(int x, int y);
	void uvolniCestu();

	void zapisFinalniCestu();

public:
	Bludiste(string soubor);
	~Bludiste();

	void vypisBludiste();

	void vykresli();
	void najdiCestu();
	void nactiMapu();
	void vysledekDoSouboru();
};
