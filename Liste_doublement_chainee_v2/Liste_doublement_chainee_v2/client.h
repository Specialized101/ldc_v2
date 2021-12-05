#pragma once

#define MAX_LENGTH_NOM 40
#define MAX_LENGTH_PRENOM 30


struct Client* client_new(const char* nom, const char* prenom, int num_client);
/* p_client1 < p_client2 -> -1
   p_client1 = p_client2 -> 0
   p_client1 > p_client2 -> 1
*/
int client_compare(void* p_client1, void* p_client2);
void client_display(void* p_client);
void client_del(void* p_client);

struct Client {

	int num_client;
	char nom[MAX_LENGTH_NOM];
	char prenom[MAX_LENGTH_PRENOM];

};