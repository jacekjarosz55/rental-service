#include "carlist.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CarNode *add_car(CarNode **list, Car *data) {
  CarNode *new = (CarNode *)malloc(sizeof(CarNode));
  if (new == NULL) {
    return NULL;
  }
  new->next = NULL;
  new->data = data;

  CarNode *existing = *list;
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

CarNode *get_car_by_id(CarNode *head, unsigned id) {
  CarNode *cur = head;
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

CarNode *get_car_by_make_model(CarNode *head, char *make, char *model) {
  while(head != NULL) {
    if (strcmp(head->data->make, make) == 0 && strcmp(head->data->model, model) == 0) {
      return head;
    }
    head = head->next;
  }
  return NULL;
}

bool update_car(CarNode *head, unsigned int id, Car *new_data) {
  CarNode *car = get_car_by_id(head, id);
  if(car == NULL) return false;
  free_car_data(car->data);
  car->data = new_data;
  return true;
}

void free_car(CarNode *car) {
  free_car_data(car->data);
  car->data = NULL;
  free(car);
}

bool remove_car_by_id(CarNode *head, unsigned id) {
  CarNode *car = get_car_by_id(head, id);
  if (car == NULL) {
    return false;
  }
  CarNode *cur = head;
  while (cur->next != car) {
    if (cur->next == NULL)
      return false;
    cur = cur->next;
  }
  cur->next = car->next;
  free_car(car);
  return true;
}

void foreach_car(CarNode *head, void (*func)(Car *)) {
  while (head != NULL) {
    func(head->data);
    head = head->next;
  }
}

void free_car_list(CarNode *head) {
  if(head->next) {
    free_car_list(head->next);
  }
  free_car(head);
}



