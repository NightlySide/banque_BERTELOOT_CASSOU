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

char* nom_de_compte(int id) {
    // on ouvre le fichier de banque
    FILE f_banque;
    ouvrir(&f_banque, "banque");

    COMPTE c;
    do {
        fread(&c, sizeof(COMPTE), 1, &f_banque);
    } while (c.id != id);

    fermer(&f_banque);

    return c.nom;
}

// Retourne la solde du client à partir de la date donnée
float solde_de(char* nom, DATE date) {
    // on ouvre le fichier client
    FILE f_client;
    ouvrir(&f_client, nom);

    ENTETE e;
    int res = get_entetes_from_date(&f_client, date, &e, NULL);
    if (res == 1) {
        printf("La date demandée n'a pas été trouvée!");
        exit(1);
    }

    // on ferme le fichier
    fermer(&f_client);

    // on retourne le solde du dernier entete
    return e.solde;
}

int mise_a_jour_solde_client(char* nom, DATE date) {
    // on ouvre le fichier client
    FILE f_client;
    ouvrir(&f_client, nom);

    // on maj la solde
    mise_a_jour_solde(&f_client, date);

    // on ferme le fichier client
    fermer(&f_client);
}

int virement_de_a(char* nom_src, char* nom_dst, DATE date, float montant) {
    FILE f_src;
    FILE f_dst;
    ouvrir(&f_src, nom_src);
    ouvrir(&f_dst, nom_dst);

    TRANSACTION t_src;
    TRANSACTION t_dst;

    // on fixe la date
    DATE d;
    now_date(&d);
    t_src.date = d;
    t_dst.date = d;

    // on fixe le montant
    t_src.montant = -montant;
    t_dst.montant = montant;

    // on fixe le nom de l'autre
    strcpy(t_src.nom, nom_dst);
    strcpy(t_dst.nom, nom_src);

    // on fixe le label
    strcpy(t_src.label, "Transaction");
    strcpy(t_dst.label, "Transaction");

    ajout_transaction(&f_src, &t_src);
    ajout_transaction(&f_dst, &t_dst);

    // on ferme les fichiers
    fermer(&f_src);
    fermer(&f_dst);

    // on dit que tout s'est bien passé
    return 0;
}

int virement_de_compte_a_compte(int id_src, int id_dst, DATE date, float montant) {
    char* nom_src = nom_de_compte(id_src);
    char* nom_dst = nom_de_compte(id_dst);

    return virement_de_a(nom_src, nom_dst, date, montant);
}

int imprimer_releve(char* nom, DATE date) {
    // on ouvre le fichier client
    FILE f_client;
    ouvrir(&f_client, nom);

    // on récupère tous les soldes du mois donné
    int somme = 0;

    ENTETE e_actuel;
    ENTETE e_precedent;
    DATE* currentDate;
    currentDate = &e_actuel.dateActuelle;

    // sinon on itère sur les transactions jusqu'à trouver la prochaine date
    TRANSACTION t;
    do {
        int result = fread(&t, sizeof(TRANSACTION), 1, &f_client);
        if (result == 0) {
            // on a atteint la fin du fichier
            return 1;
        }

        // si la date lue est différente de la précédente
        if (eq_date(&t.date, currentDate) == 1) {
            // on change l'en-tete
            e_precedent = e_actuel;

            // on remonte le curseur
            fseek(&f_client, -sizeof(TRANSACTION), SEEK_CUR);
            // on lis une nouvelle entete
            fread(&e_actuel, sizeof(ENTETE), 1, &f_client);
            // on met à jour la date actuelle
            currentDate = &e_actuel.dateActuelle;
        }
    } while (date.annee > currentDate->annee && date.mois >= currentDate->mois);

    // on ferme le fichier
    fermer(&f_client);

    // on affiche le relevé
    printf("Relevé du compte : %s\n", nom);
    printf("  -- Solde: %f\n", e_precedent.solde);

    // tout s'est bien passé
    return 0;
}