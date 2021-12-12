#include <stdio.h>
#include <stdlib.h>
#include "entete.h"
#include "fileMgmt.h"
#include "date.h"
#include "transaction.h"

// fonction privées -> on définit juste les prototypes de fonction
int get_transaction_somme(FILE* f, DATE date);

// Crée une nouvelle instance d'entête
ENTETE creation_entete(DATE date, float solde) {
    // on crée l'instance
    ENTETE e;

    // on la remplit
    e.dateActuelle = date;
    e.solde = solde;

    // on la retourne
    return e;
}

// Crée un fichier à l'aide d'un entete donné
FILE* creation_fichier(ENTETE e, char* nomFichier) {
    // on ouvre le fichier à l'aide de la fonction déjà crée
    FILE* f = ouvrir(nomFichier);

    // on enregistre le nouvel entete dans le fichier
    fwrite(&e, sizeof(ENTETE), 1, f);

    // on ferme le fichier
    fermer(f);

    // on retourne le pointeur vers ce fichier
    return f;
}

// Mets à jour l'entête du jour en fonction de l'entête précédent
// Ainsi que les transactions liées à l'entête
void mise_a_jour_solde(FILE* f, DATE date) {
    ENTETE e_actuel;
    ENTETE e_precedent;

    // on déplace le curseur au niveau de la date renseignée
    int result = get_entetes_from_date(f, date, &e_actuel, &e_precedent);
    if (result == 1) {
        printf("La date demandée n'a pas été trouvée!");
        exit(1);
    }
    else if (result == 2) {
        printf("La date demandée est le 1er entête, on ne fait rien");
        return;
    }

    // on parcoure les transactions précédentes
    int somme_transactions = get_transaction_somme(f, date);
    // après la fonction, ici, le curseur est juste avant l'entete de la date demandée

    // on met à jour le solde
    int nouvelle_solde = e_precedent.solde + somme_transactions;
    e_actuel.solde = nouvelle_solde;

    // Attention à bien placer le curseur
    fwrite(&e_actuel, sizeof(ENTETE), 1, f);
}

// Déplace le curseur à l'entête spécifié par la date
// retourne 1 si la date n'a pas été trouvée
// retourne 2 si la date est le 1er entete
int get_entetes_from_date(FILE* f, DATE date, ENTETE* e_actuel, ENTETE* e_precedent) {
    // on déplace le curseur au début du fichier
    fseek(f, 0, SEEK_SET);

    // on lit le premier en-tête
    fread(&e_actuel, sizeof(ENTETE), 1, f);

    // si on est à la bonne date on sort
    if (eq_date(&(*e_actuel).dateActuelle, &date) == 0) {
        // fseek(f, -sizeof(ENTETE), SEEK_CUR);
        return 2;
    }

    DATE* currentDate;
    currentDate = &(*e_actuel).dateActuelle;

    // sinon on itère sur les transactions jusqu'à trouver la prochaine date
    TRANSACTION t;
    do {
        int result = fread(&t, sizeof(TRANSACTION), 1, f);
        if (result == 0) {
            // on a atteint la fin du fichier
            return 1;
        }

        // si la date lue est différente de la précédente
        if (eq_date(&t.date, currentDate) == 1) {
            // on change l'en-tete
            e_precedent = e_actuel;

            // on remonte le curseur
            fseek(f, -sizeof(TRANSACTION), SEEK_CUR);
            // on lis une nouvelle entete
            fread(e_actuel, sizeof(ENTETE), 1, f);
            // on met à jour la date actuelle
            currentDate = &(*e_actuel).dateActuelle;
        }
    } while (eq_date(&(*e_actuel).dateActuelle, &date) != 0); // tant qu'on a pas trouvé notre date

    // fseek(f, -sizeof(ENTETE), SEEK_CUR);
    return 0;
}

// Retourne la somme des transactions du jour
int get_transaction_somme(FILE* f, DATE date) {
    int somme = 0;
    int nb_transactions = 0;

    TRANSACTION t;
    do {
        // on lit les données
        fread(&t, sizeof(TRANSACTION), 1, f);
        nb_transactions++;

        // si les dates sont différentes
        if (eq_date(&t.date, &date) == 0) {
            // on ajoute le montant de la transaction
            somme += t.montant;
        }
    } while (eq_date(&t.date, &date) == 0); // tant qu'on est sur le meme jour

    // on remonte le curseur
    for (int k = 0; k < nb_transactions; k++)
        fseek(f, -sizeof(TRANSACTION), SEEK_CUR);
    fseek(f, -sizeof(ENTETE), SEEK_CUR);

    // on retourne la somme
    return somme;
}