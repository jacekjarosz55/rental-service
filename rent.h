#ifndef RENT_H
#define RENT_H

#include "car.h"
#include "carlist.h"
#include "client.h"
#include "clientlist.h"
#include <stdbool.h>

struct Rent {
  unsigned id;
  unsigned car_id;
  unsigned client_id;
  bool finished;
  char *date_start;
  char *date_end;
};
typedef struct Rent Rent;




Rent *make_rent_data(unsigned id, unsigned car_id, unsigned client_id, char *date_start, char *date_end, bool finished);
void free_rent_data(Rent *rent);

void finish_rent(Rent *rent);

Car *fetch_car(Rent *rent, CarNode *cars);
Client *fetch_client(Rent *rent, ClientNode *clients);

#endif
