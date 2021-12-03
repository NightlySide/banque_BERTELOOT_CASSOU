#include "date.h"

struct transaction
{
    struct date date_transac;
    float montant;
    char nom[];
    char label[30];

};
