#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "transaction.h"
#include "date.h"

void now_date( Date *date_j){
  time_t tt = time(NULL);
  struct tm *t = localtime(&tt);

  date_j->jour = (int)t->tm_mday;
  date_j->mois = (int)t->tm_mon + 1;// Pose pas de question chacal bis
  date_j->annee = (int)t->tm_year + 1900; // Pose pas de question chacal
}

void ouvrir(FILE *f, char nom[])
{
  const char* extension = ".dat";
  char* name_with_extension; // Walla c'est moi qui est écrit ces 4 lignes je vous le jure
  name_with_extension = malloc(strlen(nom)+1+4); /* make space for the new string (should check the return value ...) */
  strcpy(name_with_extension, nom); /* copy name into the new var */
  strcat(name_with_extension, extension); /* add the extension */
  f = fopen(name_with_extension ,"a");
}


void fermer(FILE *f)
{
  fclose(f);
}

transaction creation_transaction(Date d, float m, char dest, char lab){
  transaction *new_transac;
  (*new_transac).date_transac = d;
  (*new_transac).montant = m;
  (*new_transac).nom_dest = dest;
  (*new_transac).label = lab;
  return *new_transac;
}
int ajout_transaction(FILE *f ,transaction t){
  if(fprintf(f,"%i %i %i ",t.date_transac.annee,t.date_transac.mois,t.date_transac.jour)== -1){
    printf("Erreur d'écriture de la transaction\n");
  }

  if(fprintf(f,"%f ",t.montant)== -1){
    printf("Erreur d'écriture du montant\n");
  }

  if(fprintf(f,"%s ",t.nom_dest)== -1){
    printf("Erreur d'écriture du destinataire\n");
  }

  if(fprintf(f,"%s \n",t.label)== -1){
    printf("Erreur d'écriture du label\n");
  }

  return 0;
}
int main(int argc, char * argv[]) {
    Date date1;
    now_date(&date1);
    printf("%i \n",date1.jour);
    printf("%i \n",date1.mois);
    printf("%i \n",date1.annee);
    FILE f;
    ouvrir(&f,"oui");
    fermer(&f);
    return 0;
}
