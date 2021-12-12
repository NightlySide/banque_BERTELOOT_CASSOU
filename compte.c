#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "compte.h"
#include "date.h"
#include "fileMgmt.h"
#include "entete.h"
#include "transaction.h"

// Crée un utilisateur et l'ajoute au registre de la banque
int creer_utilisateur(char* nom) {
    // on créer un id aléatoire
    srand(time(NULL));
    int id = rand();

    // on crée le compte
    COMPTE c;
    c.id = id;
    strcpy(c.nom, nom);

    // on l'ajoute au fichier banque
    FILE f_banque;
    ouvrir(&f_banque, "banque");
    fwrite(&c, sizeof(COMPTE), 1, &f_banque);
    fermer(&f_banque);

    // il n'y a pas eu de problèmes
    return 0;
}

// Cherche le compte avec le nom donné et retourne son identifiant
int compte_de(char* nom) {
    // on ouvre le fichier
    FILE f_banque;
    ouvrir(&f_banque, "banque");

    // on va chercher le compte avec le nom donné
    COMPTE c;
    do {
        fread(&c, sizeof(COMPTE), 1, &f_banque);
    } while (strcmp(c.nom, nom) != 0);

    // on ferme le fichier
    fermer(&f_banque);

    // on retourne l'id du compte
    return c.id;
}


float solde_de(char* nom, DATE date) {
    // on ouvre le fichier client
    FILE f_client;
    ouvrir(&f_client, nom);

    // on récupère le dernier entete
    ENTETE e;
    TRANSACTION t;

    fread(&e, sizeof(ENTETE), 1, &f_client);

    int res_lecture;
    DATE* currentDate = &e.dateActuelle;
    do {
        res_lecture = fread(&t, sizeof(TRANSACTION), 1, &f_client);
        if (eq_date(&t.date, currentDate) == 1) {
            // on remonte le curseur
            fseek(&f_client, -sizeof(TRANSACTION), SEEK_CUR);
            // on lis une nouvelle entete
            fread(&e, sizeof(ENTETE), 1, &f_client);
            // on met à jour la date actuelle
            currentDate = &e.dateActuelle;
        }
    } while (res_lecture != 0);

    // on pense à fermer le fichier client
    fermer(&f_client);

    // on retourne le solde du dernier entete
    return e.solde;
}


int mise_a_jour_solde_client(char* nom, DATE date) { return 0; }
int virement_de_compte_a_compte(int id_src, int id_dst, DATE date, float montant) { return 0; }
int virement_de_a(char* nom_src, char* nom_dst, DATE date, float montant) { return 0; }
int imprimer_releve(char* nom, DATE date) { return 0; }