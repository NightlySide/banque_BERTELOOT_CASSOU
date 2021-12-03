#include <stdio.h>

#include "date.h"

void now_date( struct date){
    time_t timestamp = time(NULL);
    struct tm * now = localtime( &timestamp);
    int jour = now->tm_mday;
    int mois = now ->tm_mon;
    int annee = now ->tm_year;
}
int main(int argc, char * argv[]) {
    struct date vendr;
    now_date(vendr);
    printf(vendr.annee);
    printf(vendr.mois);
    printf(vendr.mois);
    printf(vendr.mois);
    return 1;
}
