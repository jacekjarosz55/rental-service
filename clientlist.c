#include "clientlist.h"
#include <stdlib.h>
#include <string.h>

ClientNode *add_client(ClientNode **list, Client *data) {
  ClientNode *new = (ClientNode *)malloc(sizeof(ClientNode));
  if (new == NULL) {
    return NULL;
  }
  new->next = NULL;
  new->data = data;

  ClientNode *existing = *list;
  if (existing == NULL) {
    *list = new;
    return new;
  }

  while (existing->next) {
    existing = existing->next;
  }
  existing->next = new;
  return new;
}

bool update_client(ClientNode *head, unsigned id, Client *new_data) {
  ClientNode *client = get_client_by_id(head, id);
  if(client == NULL) return false;
  free_client_data(client->data);
  client->data = new_data;
  return true;
}

ClientNode *get_client_by_id(ClientNode *head, unsigned id) {
  ClientNode *cur = head;
  while (cur->next) {
    if (cur->data->id == id) {
      return cur;
    }
    cur = cur->next;
  }
  if (cur->data->id == id) {
    return cur;
  }
  return NULL;
}

ClientNode *get_client_by_full_name(ClientNode *head, char *first_name, char *last_name) {
  while(head != NULL) {
    if (strcmp(head->data->first_name, first_name) == 0 && strcmp(head->data->last_name, last_name) == 0) {
      return head;
    }
    head = head->next;
  }
  return NULL;
}

bool remove_client_by_id(ClientNode *head, unsigned id) {
  ClientNode *client = get_client_by_id(head, id);
  if (client == NULL) {
    return false;
  }
  ClientNode *cur = head;
  while (cur->next != client) {
    if (cur->next == NULL)
      return false;
    cur = cur->next;
  }
  cur->next = client->next;
  free_client(client);
  return true;
}


void foreach_client(ClientNode *head, void(*func)(Client*)) {
  while (head != NULL) {
    func(head->data);
    head = head->next;
  }
}

void free_client(ClientNode *client) {
  free_client_data(client->data);
  free(client);
}

void free_client_list(ClientNode *head) {
  if(head->next) {
    free_client_list(head->next);
  }
  free_client(head);
}
