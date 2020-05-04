/** @file */
#ifndef DEKLARACJE_V2_H
#define DEKLARACJE_V2_H

#include <iostream> 
#include <string>
#include <vector>

#include "struktury.h"
using namespace std;



/** Funckja porownuje dwie daty, zapisane w strukturach
* @param d1 pierwsza data
* @param d2 druga data
* @return funkcja zwraca true jesli data d1 jest wczesniejsza niz d2
*/
bool data_wczesniejsza(data_biegu d1, data_biegu d2);

/** Funkcja tworzaca liste biegow oraz liste zawodnikow z zagniezdzonymi listami czasow danego zawodnika.
*	@param nazwa_pliku nazwa pliku tekstowego z protokolem biegu
*	@param biegHead wskaznik na poczatek listy biegow
*	@param zawodnikHead wskaznik na poczatek listy zawodnikow
*/
void przepisz_do_list(string nazwa_pliku, bieg*& biegHead, zawodnik*& zawodnikHead);

/**	Funkcja sprawdza czy zawodnik znajduje sie juz na liscie, a jesli tak to w ktorym miejscu listy.
*	@param nazwisko nazwisko zawodnika wczytane z pliku
*	@param zawodnikHead wskaznik na pierwszy element listy zawodnikow
*	@return funkcja zwroci wskaznik na zawodnika o danym nazwisku, a jesli nie ma zawodnika o danym nazwisku na liscie - zwroci nullptr
*/
zawodnik* znajdz_zawodnika(string nazwisko, zawodnik* zawodnikHead);

/**	Funkcja zapisuje wyniki maratonczykow do osobnych plikow.
*	@param zawodnikHead wskaznik na poczatek listy zawodnikow
*/
void zapisz_do_plikow(zawodnik* zawodnikHead);

/**	Funkcja usuwajaca liste biegow rekurencyjnie.
*	@param biegHead wskaznik na poczatek listy biegow
*/
void usun_liste_biegow(bieg* biegHead);

/**	Funkcja usuwajaca liste zawodnikow razem z zagniezdzona lista czasow. Lista zawodnikow jest usuwana rekurencyjnie, a zagniezdzona lista czasow jest usuwana iteracyjnie.
*	@param zawodnikHead wskaznik na poczatek listy zawodnikow
*/
void usun_liste_zawodnikow(zawodnik* zawodnikHead);
#endif