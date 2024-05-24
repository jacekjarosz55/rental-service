#include "clientlist.h"
#include <stdio.h>
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


bool client_search_filter(Client* client, char *searchTerm) {
  return (
      strstr(client->first_name ,searchTerm) != NULL
      || strstr(client->last_name ,searchTerm) != NULL
      || strstr(client->email ,searchTerm) != NULL
      || strstr(client->phone_number ,searchTerm) != NULL
  );
}

ClientNode *client_filtered_list(ClientNode *head, char* searchTerm, bool(*filter_func)(Client*, char*)) { 
  ClientNode *newList = NULL;
  while(head != NULL) {
    if(head->data && filter_func(head->data, searchTerm)) {
      add_client(&newList, head->data);
    }
    head=head->next;
  }
  return newList;
}





void free_client(ClientNode *client) {
  free_client_data(client->data);
  free(client);
}

void free_client_list_only(ClientNode *head) {
  if(head->next) {
    free_client_list_only(head->next);
  }
  free(head);
}


void free_client_list(ClientNode *head) {
  if(head->next) {
    free_client_list(head->next);
  }
  free_client(head);
}


bool client_list_save_to_file(ClientNode *head, char *filename) {
  FILE *file = fopen(filename, "w");
  if (!file) return false;
  while(head != NULL) {
    if (head->data) {
      fprintf(
        file,
        "%u,%s,%s,%s,%s\n",
        head->data->id,
        head->data->first_name,
        head->data->last_name,
        head->data->phone_number,
        head->data->email
      );
    }
    head=head->next;
  }
  fclose(file);
  return true;
}

ClientNode* client_list_new_from_file(char *filename) {
  FILE *file = fopen(filename, "r");
  if(!file) return NULL;

  ClientNode *clients = NULL;

  char buf[1024];
  while(fgets(buf,sizeof(buf), file)) {
    unsigned id;
    char first_name[50];
    char last_name[50];
    char phone_number[50];
    char email[50];

    int res = sscanf(buf, " %u,%49[^,],%49[^,],%49[^,],%49[^,]\n", &id, first_name, last_name, phone_number, email);
    if (res == 5){
      add_client(&clients, make_client_data(id, first_name, last_name, phone_number, email));
    } 
  }
  fclose(file);
  return clients;
}
