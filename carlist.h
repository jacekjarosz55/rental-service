#ifndef CARLIST_H
#define CARLIST_H

#include "clientlist.h"

struct CarNode {
  struct CarNode *next; 
  char *model;
  char *make;
  unsigned year;
  unsigned cost;
  ClientNode *current_client;
};

typedef struct CarNode Carnode;




#endif
