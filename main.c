#include <stdio.h>
#include "carlist.h"


void print_car(Car *car) {
  printf("Car: #%u %s %s, year: %u, cost: %u, km: %u\n", car->id, car->make, car->model, car->year, car->cost, car->km_driven);
}


int main() {
  CarNode *list = NULL;
  add_car(&list, make_car_data("Ford", "Focus", 2004, 10000, 20345));
  add_car(&list, make_car_data("Honda", "Jazz", 2002, 5000, 10933));
  foreach_car(list, print_car);
  return 0;
}
