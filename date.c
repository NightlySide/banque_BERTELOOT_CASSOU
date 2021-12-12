#include "date.h"

// Retourne la date actuelle (aujourd'hui)
void now_date(DATE* date_j) {
	time_t tt = time(NULL);
	struct tm* t = localtime(&tt);

	(*date_j).jour = (int)t->tm_mday;
	(*date_j).mois = (int)t->tm_mon;
	(*date_j).annee = (int)t->tm_year + 1900;
}

// Compare 2 dates, retourne 0 si elles sont égales, 1 sinon
int eq_date(DATE *d1, DATE *d2) {
	if (d1->annee == d2->annee && d1->mois == d2->mois && d1->jour == d2->jour) return 0;
	return 1;
}