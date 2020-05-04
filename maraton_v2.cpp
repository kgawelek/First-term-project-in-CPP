/** @file */
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "struktury.h"
#include "deklaracje_v2.h"


using namespace std;

int main(int argc, char* argv[])
{

	ifstream plik_wejscia;
	string i = "-i";
	string h = "-h";
	string przelacznik;
	if (argc > 1) {
		przelacznik = argv[1];
	}
	bieg* biegGlowa = nullptr;
	zawodnik* zawodnikGlowa = nullptr;
	if (argc > 1) {
		if (i.compare(przelacznik) == 0)
		{
			for (int i = 2; i < argc; i++)
			{	
				przepisz_do_list(argv[i], biegGlowa, zawodnikGlowa);
			}
		}
		else if (h.compare(przelacznik) == 0) {
			cout << "Program generuje pliki z wynikami zawodnikow dla biegow podanych przy uruchomieniu programu." << endl;
			cout << "Program nalezy uruchamiac z przelacznikiem -i, a po nim podac nazwy plikow tekstowych z protokolami biegow." << endl;
			cout << "Przykladowe wywolanie programu: maraton_v2 -i bieg1.txt bieg2.txt" << endl;
		}
		else
			cout << "Nie prawidlowe uruchomienie aplikacji, wywolaj z przelacznikiem -h w celu uzyskania opisu programu." << endl;
	}
	else
		cout << "Uzyj -h w celu uzyskania informacji na temat programu" << endl;
	
	zapisz_do_plikow(zawodnikGlowa);

	usun_liste_biegow(biegGlowa);

	usun_liste_zawodnikow(zawodnikGlowa);
	return 0;
}