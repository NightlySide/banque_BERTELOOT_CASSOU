//#include "date.h"

typedef struct
{
    DATE date_transac;
    float montant;
    char label[30];
    char nom[];
} TRANSACTION;
