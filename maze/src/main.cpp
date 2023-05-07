#include "Knihovny.h"
#include "Bludiste.h"

using namespace std;

int main()
{
	Bludiste bludiste("mapa.txt");

	bludiste.nactiMapu();

	bludiste.vykresli();
	cout << endl;

	bludiste.najdiCestu();

	bludiste.vykresli();

	bludiste.vysledekDoSouboru();

	return 0;
}