#include "date.h"
#include <string.h>

typedef struct transaction
{
    date date_transac;
    float montant;
    char label[30];
    char *nom_dest;
}transaction;
