#include <stdlib.h>

#include "date.h"
#include "entete.h"
#include "transaction.h"
#include "fileMgmt.h"
#include "compte.h"

void ajout() {
	char* nomClient = (char*)malloc(sizeof(char) * 30);
	printf("\nVeuiller indiquer le nom du client: ");
	scanf("%s", nomClient);
	creer_utilisateur(nomClient);
}

void liste_comptes() {
	FILE f_banque;
	ouvrir(&f_banque, "banque");

	COMPTE c;
	int res;
	do {
		res = fread(&c, sizeof(COMPTE), 1, &f_banque);
		if (res != 0) {
			printf("Compte: %s, ID: %d\n", c.nom, c.id);
		}
	} while (res != 0);

	fermer(&f_banque);
}

void releve_compte() {
	char* nomClient = (char*)malloc(sizeof(char) * 30);
	printf("\nVeuiller indiquer le nom du compte a relever : ");
	scanf("%s", nomClient);
	int annee = 0, mois = 0;
	printf("\nVeuiller indiquer l'année à relever : ");
	scanf("%d", &annee);
	printf("\nVeuiller indiquer le mois à relever : ");
	scanf("%d", &annee);

	DATE d;
	d.annee = annee;
	d.mois = mois;
	imprimer_releve(nomClient, d);
}

void virement_compte_client() {
	char* compteSource = (char*)malloc(sizeof(char) * 30);
	printf("\nVeuiller indiquer le nom du compte source : ");
	scanf("%s", compteSource);

	char* compteDestination = (char*)malloc(sizeof(char) * 30);
	printf("\nVeuiller indiquer le nom du compte destination : ");
	scanf("%s", compteDestination);

	float montant;
	printf("\nVeuiller indiquer l'année à relever : ");
	scanf("%f", &montant);

	DATE d;
	now_date(&d);
	virement_de_a(compteSource, compteDestination, d, montant);
}

void maj_solde_client() {
	char* nomClient = (char*)malloc(sizeof(char) * 30);
	printf("\nVeuiller indiquer le nom du compte à mettre à jour : ");
	scanf("%c", nomClient);

	FILE fichier_client;
	ouvrir(&fichier_client, nomClient);
	DATE d;
	now_date(&d);

	mise_a_jour_solde(&fichier_client, d);

	fermer(&fichier_client);
}

void menu() {
	char choix;
	do {
		printf("\n\nAjouter un nouveau client..............: A\n");
		printf("Lister tous les comptes de clients.....: L\n");
		printf("Relevé d'un compte client..............: R\n");
		printf("Virement depuis un compte client.......: V\n");
		printf("Mise a jour du solde d'un client.......: M\n");
		printf("Quitter................................: Q\n");
		printf(" votre choix: ");
		rewind(stdin);
		scanf("%c", &choix);

		switch (choix) {
		case 'a':case 'A': ajout(); break;
		case 'l':case 'L': liste_comptes(); break;
		case 'r':case 'R': releve_compte(); break;
		case 'v':case 'V': virement_compte_client(); break;
		case 'm':case 'M': maj_solde_client(); break;
		default:
			printf("Au revoir ...\n");
			exit(0);
		}
	} while (choix != 'q' && choix != 'Q');
}

int main() {
	printf("Démarrage du programme...\n");
	menu();
}
