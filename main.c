#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "date.h"
#include <string.h>

void now_date( struct date *date_j){
  time_t tt = time(NULL);
  struct tm *t = localtime(&tt);

    (*date_j).jour = (int)t->tm_mday;
    (*date_j).mois = (int)t->tm_mon;
    (*date_j).annee = (int)t->tm_year + 1900;
}

void ouvrir(FILE *f, char nom[])
{
  const char* extension = ".dat";
  char* name_with_extension;
  name_with_extension = malloc(strlen(nom)+1+4); /* make space for the new string (should check the return value ...) */
  strcpy(name_with_extension, nom); /* copy name into the new var */
  strcat(name_with_extension, extension); /* add the extension */
  f = fopen(name_with_extension ,"a");
}


void fermer(FILE *f)
{
  fclose(f);
}

struct transaction creation_transaction(struct date d, float m, char* dest, char* lab){
  struct transaction new_transac;
  new_transac.date = d;
  new_transac.montant = m;
  new_transac.nom = dest;
  new_transac.label = lab;
  return &new_transac;
}

int main(int argc, char * argv[]) {
    struct date date1;
    now_date(&date1);
    printf("%i \n",date1.jour);
    printf("%i \n",date1.mois);
    printf("%i \n",date1.annee);
    FILE f;
    ouvrir(&f,"oui");
    fermer(&f);
    return 1;
}
