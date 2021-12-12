#include <stdio.h>
#include <string.h>

#include "transaction.h"

TRANSACTION creation_transaction(DATE date, float montant, char* label, char* nom) {
    // on crée une nouvelle instance de transaction
    TRANSACTION t;

    // on la remplit
    t.date = date;
    t.montant = montant;
    // on oublie pas que les strings n'ont pas de fonction pour copier par défaut
    strcpy(t.label, label);
    strcpy(t.nom, nom);

    // on retourne l'objet crée
    return t;
}

int ajout_transaction(FILE* f, TRANSACTION* t) {
    // on ajoute la structure au fichier et on retourne le nombre de bytes écrits
    return (int)fwrite(t, sizeof(TRANSACTION), 1, f);
}