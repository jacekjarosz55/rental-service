#include "rentlist.h"

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

bool remove_rent_by_id(RentNode *head, unsigned id) {
  RentNode *rent = get_rent_by_id(head, id);
  if (rent == NULL) {
    return false;
  }
  RentNode *cur = head;
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



