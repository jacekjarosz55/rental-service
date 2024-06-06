#include "rentlist.h"
#include "rent.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

RentNode *add_rent(RentNode **list, Rent *data) {
  RentNode *new = (RentNode *)malloc(sizeof(RentNode));
  if (new == NULL) {
    return NULL;
  }
  new->next = NULL;
  new->data = data;

  RentNode *existing = *list;
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

RentNode *get_rent_by_id(RentNode *head, unsigned id) {
  RentNode *cur = head;
  while (cur->next) {
    if(cur->data == NULL) { continue; }
    if (cur->data->id == id) {
      return cur;
    }
    cur = cur->next;
  }
  if (cur->data && cur->data->id == id) {
    return cur;
  }
  return NULL;
}

RentNode *find_rent(RentNode *head, unsigned car_id, unsigned client_id) {
  while(head != NULL) {
    if ((head->data->car_id == car_id || car_id == 0) && (head->data->client_id == client_id || client_id == 0))  {
      return head;
    }
    head = head->next;
  }
  return NULL;
}

bool update_rent(RentNode *head, unsigned int id, Rent *new_data) {
  RentNode *rent = get_rent_by_id(head, id);
  if(rent == NULL) return false;
  free_rent_data(rent->data);
  rent->data = new_data;
  return true;
}

void free_rent(RentNode *rent) {
  free_rent_data(rent->data);
  rent->data = NULL;
  free(rent);
}

bool remove_rent_by_id(RentNode **head, unsigned id) {
  if(head == NULL && *head == NULL) return false;
  RentNode *rent = get_rent_by_id(*head, id);
  if (rent == NULL) {
    return false;
  }
  if (rent == *head) {
    RentNode *tmp = *head;
    *head = (*head)->next;
    free_rent(tmp);
    return true;
  }
  RentNode *cur = *head;
  while (cur->next != rent) {
    if (cur->next == NULL)
      return false;
    cur = cur->next;
  }
  cur->next = rent->next;
  free_rent(rent);
  return true;
}


void foreach_rent(RentNode *head, void (*func)(Rent *)) {
  while (head != NULL) {
    func(head->data);
    head = head->next;
  }
}

void free_rent_list(RentNode *head) {
  if(head->next) {
    free_rent_list(head->next);
  }
  free_rent(head);
}

bool rent_list_save_to_file(RentNode *head, char *filename) {
  FILE *file = fopen(filename, "w");
  if (!file) return false;
  while(head != NULL) {
    if (head->data) {
      fprintf(
        file,
        "%u,%u,%u,%u,%s,%s\n",
        head->data->id,
        head->data->car_id,
        head->data->client_id,
        head->data->finished,
        head->data->date_start,
        head->data->date_end
      );
    }
    head=head->next;
  }
  fclose(file);
  return true;
}



RentNode *rent_list_new_from_file(char *filename) {
  FILE *file = fopen(filename, "r");
  if(!file) return NULL;

  RentNode *rents = NULL;

  char buf[1024];
  while(fgets(buf,sizeof(buf), file)) {
    unsigned id;
    unsigned car_id;
    unsigned client_id;
    int finished;
    char date_start[50];
    char date_end[50];
    int res = sscanf(buf, " %u,%u,%u,%d,%49[^,],%49[^,]\n", &id, &car_id, &client_id, &finished, date_start, date_end);
    if (res == 6){
      if (id >= get_rent_auto_increment()) {
        set_rent_auto_increment(id+1);
      }
      add_rent(&rents, make_rent_data(id, car_id, client_id, date_start, date_end, finished));
    } 
  }
  fclose(file);
  return rents;
}


