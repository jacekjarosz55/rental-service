#ifndef RENTLIST_H
#define RENTLIST_H

#include <stdbool.h>
#include "rent.h"

struct RentNode {
  struct RentNode *next; 
  struct Rent *data;
};
typedef struct RentNode RentNode;

// returns pointer to added rent, NULL if failed

RentNode *add_rent(RentNode **list, Rent *data);
bool update_rent(RentNode *head, unsigned id, Rent *new_data);
RentNode *get_rent_by_id(RentNode *head, unsigned id);
bool remove_rent_by_id(RentNode *head, unsigned id);
RentNode *find_rent(RentNode *head, unsigned car_id, unsigned client_id);
void foreach_rent(RentNode *head, void(*func)(Rent*));
void free_rent(RentNode *rent);
void free_rent_list(RentNode *head);

bool rent_list_save_to_file(RentNode *head, char *filename);
RentNode* rent_list_new_from_file(char *filename);
#endif
