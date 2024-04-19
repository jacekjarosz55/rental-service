#ifndef CAR_H
#define CAR_H

struct Car {
  unsigned id;
  char *model;
  char *make;
  unsigned year;
  unsigned cost;
  unsigned km_driven;
  unsigned client_id;
};
typedef struct Car Car;

Car *make_car_data(unsigned id, char *make, char *model, unsigned year, unsigned cost, unsigned km_driven);
void free_car_data(Car *car);
typedef struct Car Car;





#endif
