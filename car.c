#include "car.h"
#include "util.h"
#include <stdlib.h>

unsigned _CAR_AUTO_INCREMENT = 1;
Car *make_car_data(unsigned id, char *make, char *model, unsigned year,
                   unsigned cost, unsigned km_driven) {
  Car *car = (Car *)malloc(sizeof(Car));
  if (car == NULL)
    return NULL;
  if(id == 0) {
    car->id = _CAR_AUTO_INCREMENT++;
  } else { 
    car->id = id;
  }
  car->model = copied_string(model);
  car->make = copied_string(make);
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

