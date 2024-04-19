#ifndef RENT_H
#define RENT_H
struct Rent {
  unsigned id;
  unsigned car_id;
  unsigned client_id;
  char *date;
};
typedef struct Rent Rent;

Rent *make_rent_data(unsigned id, unsigned car_id, unsigned client_id, char *date);
void free_rent_data(Rent *rent);
#endif
