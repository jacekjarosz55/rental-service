#include <stdio.h>
#include <assert.h>
#include "carlist.h"
#include "clientlist.h"
#include "rent.h"
#include "rentlist.h"

void print_car(Car *car) {
  printf("Car: #%u %s %s, year: %u, cost: %u, km: %u", car->id, car->make, car->model, car->year, car->cost, car->km_driven);
  puts("");
}

void print_client(Client *client) {
  printf("Client: %s %s, email: %s\n", client->first_name, client->last_name, client->email);
}

int main() {
  CarNode *car_list = NULL;
  add_car(&car_list, make_car_data(0, "Ford", "Focus", 2004, 10000, 20345));
  add_car(&car_list, make_car_data(0, "Honda", "Jazz", 2002, 5000, 10933));
  //assert(get_car_by_make_model(car_list, "Ford", "Focus") != NULL);

  ClientNode *client_list = NULL;
  add_client(&client_list, make_client_data(0, "Marcin", "Furmańczyk", "997", "marcin@o2.pl"));
  add_client(&client_list, make_client_data(0, "Jacek", "Jarosz", "333", "andrzejduda@gov.pl"));
  add_client(&client_list, make_client_data(0, "Pablo", "Escobar", "zastrzezony", "pablo@pabloscartel.es"));

  ClientNode *jacek = get_client_by_full_name(client_list, "Jacek", "Jarosz");
  CarNode *focus = get_car_by_make_model(car_list, "Ford", "Focus");
  RentNode *rent_list = NULL;
  add_rent(&rent_list, make_rent_data(0, focus->data->id, jacek->data->id, "10-02-2020"));

  /*
  foreach_car(car_list, print_car);
  foreach_client(client_list, print_client);
  */

  RentNode *rent = rent_list;
  while(rent != NULL) {
    CarNode *car_node = get_car_by_id(car_list, rent->data->car_id);
    ClientNode *client_node = get_client_by_id(client_list, rent->data->client_id);
    if(car_node == NULL || client_node == NULL) {
      continue;
    }
    Car *car = car_node->data;
    Client *client = client_node->data;

    printf("Wypozyczenie: auto %s %s dla %s %s, data: %s\n",
           car->make,
           car->model,
           client->first_name,
           client->last_name,
           rent->data->date);
    rent = rent->next;
  }
  
  free_rent_list(rent_list);
  free_car_list(car_list);
  free_client_list(client_list);
  return 0;
}
