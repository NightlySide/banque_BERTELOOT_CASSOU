#include <stdio.h>
#include "date.h"


#ifndef ENTETE_H
#define ENTETE_H

typedef struct {
    DATE dateActuelle;
    float solde;
} ENTETE;


ENTETE creation_entete(DATE date, float solde);
FILE *creation_fichier(ENTETE e, char* nomFichier);
void mise_a_jour_solde(FILE *f, DATE date);


#endif