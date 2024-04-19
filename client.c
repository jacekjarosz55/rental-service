#include "util.h"
#include "client.h"
#include <stdlib.h>

unsigned _CLIENT_AUTO_INCREMENT = 1;

Client *make_client_data( unsigned id, char *first_name, char *last_name, char *phone_number, char *email) {
  Client *new = (Client *)malloc(sizeof(Client));
  if (new == NULL) return NULL;
  if(id == 0) {
    new->id = _CLIENT_AUTO_INCREMENT++;
  } else { 
    new->id = id;
  }
  new->first_name = copied_string(first_name);
  new->last_name = copied_string(last_name);
  new->phone_number = copied_string(phone_number);
  new->email = copied_string(email);
  return new;
}

void free_client_data(Client *client) {
  if(client == NULL) return;
  free(client->first_name);
  free(client->last_name);
  free(client->phone_number);
  free(client->email);
  free(client);
}
