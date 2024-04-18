#ifndef CARLIST_H
#define CARLIST_H

#include "clientlist.h"
#include <stdbool.h>

struct Car {
  unsigned id;
  char *model;
  char *make;
  unsigned year;
  unsigned cost;
  unsigned km_driven;
  ClientNode *current_client;
};
typedef struct Car Car;

Car *make_car_data(unsigned id, char *make, char *model, unsigned year, unsigned cost, unsigned km_driven);
void free_car_data(Car *car);


struct CarNode {
  struct CarNode *next; 
  struct Car *data;
};
typedef struct CarNode CarNode;

// returns pointer to added car, NULL if failed

CarNode *add_car(CarNode **list, Car *data);
CarNode *get_car_by_id(CarNode *head, unsigned id);

bool remove_car_by_id(CarNode *head, unsigned id);

void foreach_car(CarNode *head, void(*func)(Car*));
void free_car(CarNode *car);
#endif
