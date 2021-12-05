
#include <stdlib.h> 
#include <iostream>

#include "client.h"

struct Client* client_new(const char* nom, const char* prenom, int num_client) {

	/* Allouer un espace memoire pour un nouveau client */

	struct Client* p_new = (struct Client*)malloc(sizeof(*p_new));

	/* Verifier si la call malloc a fonctionné */

	if (p_new != NULL) {

		/* Initialiser les données membres du nouveau client avec les parametres */

		strcpy(p_new->nom, nom);
		strcpy(p_new->prenom, prenom);
		p_new->num_client = num_client;

	}

	/* Retourner l'adresse du nouveau client */

	return p_new;

}

int client_compare(void* p_client1, void* p_client2) {

	struct Client* p_cli1 = (struct Client*)p_client1;
	struct Client* p_cli2 = (struct Client*)p_client2;

	return p_cli1->num_client - p_cli2->num_client;

}

void client_display(void* p_client) {

	struct Client* p_cli = (struct Client*) p_client;

	printf("\nNom: %s\n", p_cli->nom);
	printf("Prenom: %s\n", p_cli->prenom);
	printf("Numero_client: %d\n", p_cli->num_client);

}

void client_del(void* p_client) {

	struct Client* p_cli = (struct Client*)p_client;

	free(p_cli);
	p_cli = NULL;

}