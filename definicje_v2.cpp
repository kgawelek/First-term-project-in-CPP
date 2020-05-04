/** @file */
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <vector>
#include <climits>
#include <string>
#include <iomanip>
#include <fstream>

#include "struktury.h"
#include "deklaracje_v2.h"


bool data_wczesniejsza(data_biegu d1, data_biegu d2) {
	if (d1.rok < d2.rok)
		return true;
	else if (d1.rok == d2.rok) {
		if (d1.miesiac < d2.miesiac)
			return true;
		else if (d1.miesiac == d2.miesiac) {
			if (d1.dzien < d2.dzien)
				return true;
		}
	}

	return false;
}



void przepisz_do_list(string nazwa_pliku, bieg* & biegHead, zawodnik*& zawodnikHead) {
	ifstream in;
	in.open(nazwa_pliku);
	
	if (in) {
		string nazwa_biegu_z_pliku;
		getline(in, nazwa_biegu_z_pliku);
		int rok, miesiac, dzien;
		in >> rok >> miesiac >> dzien;
		miesiac = -miesiac;
		dzien = -dzien;
		data_biegu data_z_pliku{ rok, miesiac, dzien };
		auto b = biegHead;
		if (not biegHead) { // lista pusta
			biegHead = new bieg { nazwa_biegu_z_pliku, data_z_pliku, nullptr };
			b = biegHead;
		}
		else {
			
			while (b->pNext_bieg)
				b = b->pNext_bieg;

			// p wskazuje ostatni element listy
			b->pNext_bieg = new bieg{ nazwa_biegu_z_pliku, data_z_pliku, nullptr };
			b = b->pNext_bieg;
		}

		string t;
		while (getline(in, t, ' ')) {	// to wczytuje numer porzadkowy ktory i tak nie jest do nieczego potrzebny i spacje przed nazwiskiem
			string nazwisko;
			string temp;
			int godziny, minuty, sekundy;

			getline(in, nazwisko, ',');
			getline(in, temp, ',');
			getline(in, temp, ':');
			godziny = atoi(temp.c_str());
			getline(in, temp, ':');
			minuty = atoi(temp.c_str());
			getline(in, temp);
			sekundy = atoi(temp.c_str());

			auto x = znajdz_zawodnika(nazwisko, zawodnikHead); // x to wskaznik na zawodnika o podanym nazwisku
			auto p = zawodnikHead;
			if (not x) {

				if (not zawodnikHead) { // lista pusta
					zawodnikHead = new zawodnik{ nazwisko, nullptr, nullptr };
					p = zawodnikHead;
				}
				else
				{

					while (p->pNext_zawodnik)
						p = p->pNext_zawodnik;

					// p wskazuje ostatni element listy
					p->pNext_zawodnik = new zawodnik{ nazwisko, nullptr, nullptr };
					p = p->pNext_zawodnik;
				}
				// jezeli jest nowy zawodnik to trzeba stworzyc nowa liste jego czasow
				p->czas1 = new czas{ godziny, minuty, sekundy, nullptr, b };

			}
			else {
				if (data_wczesniejsza(data_z_pliku, x->czas1->bieg->data)) {
					auto temp = x->czas1;
					x->czas1 = new czas{ godziny, minuty, sekundy , temp, b };
				}
				else {
					auto p = x->czas1;
					while (p->pNext_czas) {
						if (data_wczesniejsza(data_z_pliku, p->pNext_czas->bieg->data)) {
							auto temp = p->pNext_czas;
							p->pNext_czas = new czas{ godziny, minuty, sekundy , temp, b };
							break;
						}

						p = p->pNext_czas;
					}
					if(!p->pNext_czas)
						p->pNext_czas = new czas{ godziny, minuty, sekundy, nullptr, b };
				}

			}
		
		}
		in.close();
	}
	else
		cout << "Plik o nazwie " << nazwa_pliku << " nie istnieje." << endl;
}


zawodnik* znajdz_zawodnika(string nazwisko_zawodnika, zawodnik* zawodnikHead) {
	if (zawodnikHead)
	{
		if (zawodnikHead->nazwisko.compare(nazwisko_zawodnika) == 0)
			return zawodnikHead;
		else
			return znajdz_zawodnika(nazwisko_zawodnika, zawodnikHead->pNext_zawodnik);
	}
	else
		return nullptr;
}

void zapisz_do_plikow(zawodnik* zawodnikHead) {
	while (zawodnikHead)
	{
		ofstream plikw;
		plikw.open(zawodnikHead->nazwisko);
		if (plikw) {
			auto czasHead = zawodnikHead->czas1;
			plikw << zawodnikHead->nazwisko << endl;
			plikw << endl;
			while (czasHead) {
				plikw << czasHead->bieg->data.rok << "-";

				if (czasHead->bieg->data.miesiac < 10)
					plikw << "0" << czasHead->bieg->data.miesiac << "-";
				else
					plikw << czasHead->bieg->data.miesiac << "-";

				if (czasHead->bieg->data.dzien < 10)
					plikw << "0" << czasHead->bieg->data.dzien << " ";
				else
					plikw << czasHead->bieg->data.dzien << " ";

				plikw << czasHead->bieg->nazwa_biegu << " ";

				if (czasHead->godziny < 10)
					plikw << "0" << czasHead->godziny << ":";
				else
					plikw << czasHead->godziny << ":";

				if (czasHead->minuty < 10)
					plikw << "0" << czasHead->minuty << ":";
				else
					plikw << czasHead->minuty << ":";

				if (czasHead->sekundy < 10)
					plikw << "0" << czasHead->sekundy << endl;
				else
					plikw << czasHead->sekundy << endl;

				czasHead = czasHead->pNext_czas;
			}
			zawodnikHead = zawodnikHead->pNext_zawodnik;
			plikw.close();
		}
	}
}

void usun_liste_biegow(bieg* biegHead) {
	if (biegHead)
	{
		auto p = biegHead->pNext_bieg;
		delete biegHead;
		biegHead = nullptr;
		usun_liste_biegow(p);
	}
}


void usun_liste_zawodnikow(zawodnik* zawodnikHead) {
	if (zawodnikHead) {
		auto z = zawodnikHead->pNext_zawodnik;
		auto c = zawodnikHead->czas1;
		// usuniecie zagniezdzonej listy czasow
		while (c) {
			auto p = c;
			c = c->pNext_czas;
			delete p;
			p = nullptr;
		}
		delete zawodnikHead;
		zawodnikHead = nullptr;
		usun_liste_zawodnikow(z);
	}
}