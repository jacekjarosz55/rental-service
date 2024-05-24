#ifndef CARLIST_H
#define CARLIST_H

#include "car.h"

#include <stdbool.h>

struct CarNode {
  struct CarNode *next; 
  struct Car *data;
};
typedef struct CarNode CarNode;

// returns pointer to added car, NULL if failed

CarNode *add_car(CarNode **list, Car *data);

bool update_car(CarNode *head, unsigned id, Car *new_data);

CarNode *get_car_by_id(CarNode *head, unsigned id);
CarNode *get_car_by_make_model(CarNode *head, char *make, char *model);

bool remove_car_by_id(CarNode *head, unsigned id);

void sort_car_list(CarNode **head, bool(*comparator)(Car*, Car*), bool descending);

bool car_make_comparator(Car* a, Car* b);
bool car_year_comparator(Car* a, Car* b);
bool car_km_driven_comparator(Car* a, Car* b);

void foreach_car(CarNode *head, void(*func)(Car*));
void free_car(CarNode *car);
void free_car_list(CarNode *head);
#endif
