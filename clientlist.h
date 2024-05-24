#ifndef CLIENTLIST_H
#define CLIENTLIST_H

#include <stdbool.h>
#include "client.h"

struct ClientNode {
  struct ClientNode *next;
  struct Client *data;
};
typedef struct ClientNode ClientNode;

ClientNode *add_client(ClientNode **list, Client *data);
bool update_client(ClientNode *head, unsigned id, Client *new_data);
ClientNode *get_client_by_id(ClientNode *head, unsigned id);
ClientNode *get_client_by_full_name(ClientNode *head, char *first_name, char *last_name);
bool remove_client_by_id(ClientNode *head, unsigned id);
void foreach_client(ClientNode *head, void(*func)(Client*));
void free_client(ClientNode *client);
void free_client_list(ClientNode *head);
void free_client_list_only(ClientNode *head);

ClientNode *client_filtered_list(ClientNode *head, char *searchTerm, bool(*filter_func)(Client*,char*));
bool client_search_filter(Client* client, char *searchTerm);

#endif
