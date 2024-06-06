#include "rent.h"
#include "util.h"
#include "carlist.h"

#include <stdbool.h>
#include <stdlib.h>

unsigned _RENT_AUTO_INCREMENT = 1;
void set_rent_auto_increment(unsigned inc) {
  _RENT_AUTO_INCREMENT = inc;
}
unsigned get_rent_auto_increment() {
  return _RENT_AUTO_INCREMENT;
}

Rent *make_rent_data(unsigned id, unsigned car_id, unsigned client_id, char *date_start, char *date_end, bool finished) {
  Rent *rent = (Rent *)malloc(sizeof(Rent));
  if (rent == NULL)
    return NULL;
  if(id == 0) {
    rent->id = _RENT_AUTO_INCREMENT++;
  } else { 
    rent->id = id;
  }
  rent->client_id = client_id;
  rent->car_id = car_id;
  rent->date_start = copied_string(date_start);
  rent->date_end = copied_string(date_end);
  rent->finished = finished;
  return rent;
}

void free_rent_data(Rent *rent) {
  free(rent->date_start);
  free(rent->date_end);
  free(rent);
}


Car *fetch_car(Rent *rent, CarNode *cars)  {
  CarNode *found = get_car_by_id(cars,rent->car_id);
  if (found) {
    return found->data;
  } else {
    return NULL;
  }
}

Client *fetch_client(Rent *rent, ClientNode *clients)  {
  ClientNode *found = get_client_by_id(clients,rent->client_id);
  if (found) {
    return found->data;
  } else {
    return NULL;
  }
}

void rent_finish(Rent *rent, CarNode *cars, int km_driven) {
  rent->finished = true;
  Car *car = fetch_car(rent, cars);
  if (car) {
    car->km_driven+=km_driven;
  }
}

