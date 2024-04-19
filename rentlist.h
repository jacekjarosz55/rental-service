#ifndef RENTLIST_H
#define RENTLIST_H

#include "clientlist.h"
#include "carlist.h"

#include <stdbool.h>

struct Rent {
  unsigned id;
  char *model;
  char *make;
  unsigned year;
  unsigned cost;
  unsigned km_driven;
  unsigned client_id;
};
typedef struct Rent Rent;

Rent *make_rent_data(unsigned id, char *make, char *model, unsigned year, unsigned cost, unsigned km_driven);
void free_rent_data(Rent *rent);


struct RentNode {
  struct RentNode *next; 
  struct Rent *data;
};
typedef struct RentNode RentNode;

// returns pointer to added rent, NULL if failed

RentNode *add_rent(RentNode **list, Rent *data);

bool update_rent(RentNode *head, unsigned id, Rent *new_data);

RentNode *get_rent_by_id(RentNode *head, unsigned id);
RentNode *get_rent_by_make_model(RentNode *head, char *make, char *model);

bool remove_rent_by_id(RentNode *head, unsigned id);

void foreach_rent(RentNode *head, void(*func)(Rent*));
void free_rent(RentNode *rent);
void free_rent_list(RentNode *head);
#endif
