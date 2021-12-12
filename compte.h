
#include "date.h"

#ifndef COMPTE_H
#define COMPTE_H

typedef struct {
  int id;
  char nom[];
} COMPTE;

int creer_utilisateur(char* nom);
int compte_de(char* nom);
float solde_de(char* nom, DATE date);
int mise_a_jour_solde_client(char* nom, DATE date);
int virement_de_compte_a_compte(int id_src, int id_dst, DATE date, float montant);
int virement_de_a(char* nom_src, char* nom_dst, DATE date, float montant);
int imprimer_releve(char* nom, DATE date);

#endif
