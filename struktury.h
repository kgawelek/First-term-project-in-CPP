/** @file */
#ifndef STRUKTURY_H
#define STRUKTURY_H

#include <string>
using namespace std;

/** Struktura przechowujaca daty biegu
*	@param rok rok w ktorym odbyl sie bieg
*	@param miesiac miesiac w ktorym odbyl sie bieg
*	@param dzien dzien w ktorym odbyl sie bieg
*/
struct data_biegu {
	int rok;
	int miesiac;
	int dzien;
};


/**	Struktura przechowujaca informacje zwiazane z biegiem, jest to struktura, z ktorej tworzona jest lista biegow
*	@param nazwa_biegu nazwa biegu
*	@param data data biegu
*	@param pNext_bieg wskaznik na nastepny element listy biegow
*/
struct bieg {
	string nazwa_biegu;
	data_biegu data;
	bieg* pNext_bieg;
};


/**	Struktura opisujaca zawodnika,  jest to struktura z ktorej tworzona jest lista zawodnikow z zagniezdzona lista jego czasow
*	@param nazwisko nazwisko zawodnika
*	@param pNext_zawodnik wskaznik na nastepny element listy zawodnikow
*	@param czas1 wskaznik na zagniezdzona liste czasow
*/
struct zawodnik {
	string nazwisko;
	zawodnik* pNext_zawodnik;
	struct czas* czas1;
};

/**	Struktura opisujaca czas uzyskany przez zawodnika
*	@param godziny czas - godziny
*	@param minuty czas - minuty
*	@param sekundy czas -sekundy
*	@param pNext_czas wskaznik na nastepny element listy czasow danego zawodnika
*	@param bieg wksaznik na element listy biegow, ktory dotyczy biegu, z ktorego jest dany czas
*/
struct czas {
	int godziny;
	int minuty;
	int sekundy;
	czas* pNext_czas;
	struct bieg* bieg;

};
#endif