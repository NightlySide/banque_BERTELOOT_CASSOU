#include <stdio.h>
#include <string.h>

#include "transaction.h"

// Crée une nouvelle instance de transaction
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

// Ajoute une transaction au fichier et retourne le résultat d'écriture
int ajout_transaction(FILE* f, TRANSACTION* t) {
    return (int)fwrite(t, sizeof(TRANSACTION), 1, f);
}