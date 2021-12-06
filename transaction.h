#include "date.h"
#include <string.h>

typedef struct transaction
{
    date date_transac;
    float montant;
    char nom_dest[];
    char label[30];
}transaction;
