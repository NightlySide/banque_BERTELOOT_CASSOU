#include "date.h"
#include <string.h>

typedef struct transaction
{
    Date date_transac;
    float montant;
    char label[30];
    char *nom_dest;
}transaction;
