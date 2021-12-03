#include <stdio.h>
#include <time.h>
#include "date.h"

void now_date( struct date *date_j){
  time_t tt = time(NULL);
  struct tm *t = localtime(&tt);

    (*date_j).jour = (int)t->tm_mday;
    (*date_j).mois = (int)t->tm_mon;
    (*date_j).annee = (int)t->tm_year + 1900;
}

void ouvrir(FILE *f, char nom[])
{
  *f = fopen(nom ,"a");
}


void fermer(FILE*f)
{
  fclose(f);
}



int main(int argc, char * argv[]) {
    struct date date1;
    now_date(&date1);
    printf("%i \n",date1.jour);
    printf("%i \n",date1.mois);
    printf("%i \n",date1.annee);
    File f;
    ouvrir(*f,"oui");
    return 0;
}
