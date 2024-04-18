#include "carlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// global
unsigned CAR_AUTOINCREMENT = 0;

Car *make_car_data(char *make, char *model, unsigned year,
                   unsigned cost, unsigned km_driven) {
  Car *car = (Car *)malloc(sizeof(Car));
  if (car == NULL)
    return NULL;
  car->id = CAR_AUTOINCREMENT;
  CAR_AUTOINCREMENT++;
  unsigned len_model = strlen(model) + 1;
  car->model = (char *)malloc(len_model);
  memcpy(car->model, model, len_model);

  unsigned len_make = strlen(make) + 1;
  car->make = (char *)malloc(len_make);
  memcpy(car->make, make, len_make);

  car->year = year;
  car->cost = cost;
  car->km_driven = km_driven;
  return car;
}

void free_car_data(Car *car) {
  free(car->make);
  free(car->model);
  free(car);
}

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

bool update_car(CarNode *head, unsigned int id, Car *new_data) {
  CarNode *car = get_car_by_id(head, id);
  if(car == NULL) return false;
  free_car_data(car->data);
  car->data = new_data;
  return true;
}

void free_car(CarNode *car) {
  free_car_data(car->data);
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
