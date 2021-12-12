#include "date.h"

#ifndef TRANSACTION_H
#define TRANSACTION_H

typedef struct
{
    DATE date;
    float montant;
    char label[30];
    char nom[];
} TRANSACTION;

TRANSACTION creation_transaction(DATE date, float montant, char* label, char* nom);
int ajout_transaction(FILE *f, TRANSACTION *t);

#endif