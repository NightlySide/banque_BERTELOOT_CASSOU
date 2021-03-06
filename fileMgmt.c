#include <stdio.h>
#include "fileMgmt.h"
#include <string.h>
#include <stdlib.h>

// Ouvre un fichier d'après son nom
// Si le fichier n'existe pas, il sera crée
FILE* ouvrir(char nom[]) {
    const char* extension = ".dat";
    char* name_with_extension = (char*)malloc(strlen(nom) + 1 + 4); /* make space for the new string (should check the return value ...) */
    strcpy(name_with_extension, nom);                  /* copy name into the new var */
    strcat(name_with_extension, extension);            /* add the extension */
    return fopen(name_with_extension, "ab+");
}

// Ferme le fichier
void fermer(FILE* f) {
    fclose(f);
}