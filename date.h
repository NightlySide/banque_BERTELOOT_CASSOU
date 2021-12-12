#include "time.h"


#ifndef TIME_H
#define TIME_H

typedef struct {
    int jour;
    int mois;
    int annee;
} DATE;

void now_date(DATE *date_j);
int eq_date(DATE *d1, DATE *d2);

#endif