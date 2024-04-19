#ifndef CLIENT_H
#define CLIENT_H

struct Client {
  unsigned id;
  char *first_name;
  char *last_name;
  char *phone_number;
  char *email;
};
typedef struct Client Client;

Client *make_client_data( unsigned id, char *first_name, char *last_name, char *phone_number, char *email);
void free_client_data(Client *client);

#endif
