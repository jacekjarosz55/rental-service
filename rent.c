#include "rent.h"
#include "util.h"

#include <stdlib.h>

unsigned _RENT_AUTO_INCREMENT = 1;
Rent *make_rent_data(unsigned id, unsigned car_id, unsigned client_id, char *date) {
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
  rent->date = copied_string(date);
  return rent;
}

void free_rent_data(Rent *rent) {
  free(rent->date);
  free(rent);
}

