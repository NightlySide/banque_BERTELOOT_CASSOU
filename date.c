#include "date.h"
void now_date(DATE *date_j)
{
  	time_t tt = time(NULL);
	struct tm *t = localtime(&tt);

    	(*date_j).jour = (int)t->tm_mday;
    	(*date_j).mois = (int)t->tm_mon;
    	(*date_j).annee = (int)t->tm_year + 1900;
}
