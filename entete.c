#include <stdio.h>

#include "entete.h"
#include "fileMgmt.h"

// Crée une nouvelle instance d'entête
ENTETE creation_entete(DATE date, float solde) {
    // on crée l'instance
    ENTETE e;

    // on la remplit
    e.dateActuelle = date;
    e.solde = solde;

    // on la retourne
    return e;
}

// Crée un fichier à l'aide d'un entete donné
FILE* creation_fichier(ENTETE e, char* nomFichier) {
    // on ouvre le fichier à l'aide de la fonction déjà crée
    FILE f;
    ouvrir(&f, nomFichier);

    // on enregistre le nouvel entete dans le fichier
    fwrite(&e, sizeof(ENTETE), 1, &f);

    // on retourne le pointeur vers ce fichier
    return &f;
}

// Mets à jour l'entête du jour en fonction de l'entête précédent
// Ainsi que les transactions liées à l'entête
void mise_a_jour_solde(FILE* f, DATE date) {

}