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
  add_car(&car_list, make_car_data(0, "Bonda", "Kazz", 2002, 5000, 10933));
  add_car(&car_list, make_car_data(0, "Londa", "Dazz", 2002, 5000, 10933));

  //sort_car_list_by_make(&car_list);
  sort_car_list(&car_list, car_year_comparator,false);
  foreach_car(car_list, print_car);
  printf("\n");
  sort_car_list(&car_list, car_year_comparator,true);
  foreach_car(car_list, print_car);
  //assert(get_car_by_make_model(car_list, "Ford", "Focus") != NULL);

  ClientNode *client_list = NULL;
  add_client(&client_list, make_client_data(0, "Marcin", "Furmańczyk", "997", "marcin@o2.pl"));
  add_client(&client_list, make_client_data(0, "Jacek", "Jarosz", "333", "andrzejduda@gov.pl"));
  add_client(&client_list, make_client_data(0, "Pablo", "Escobar", "zastrzezony", "pablo@pabloscartel.es"));

  ClientNode *filtered_list = client_filtered_list(
    client_list,
    "Marcin",
    client_search_filter);

  foreach_client(filtered_list, print_client);

  free_client_list_only(filtered_list);


  ClientNode *jacek = get_client_by_full_name(client_list, "Jacek", "Jarosz");
  CarNode *focus = get_car_by_make_model(car_list, "Ford", "Focus");

  RentNode *rent_list = NULL;
  add_rent(&rent_list, make_rent_data(0, focus->data->id, jacek->data->id, "10-02-2024", "11-02-2024", false));


  //cleanup
  free_rent_list(rent_list);
  free_car_list(car_list);
  free_client_list(client_list);
  return 0;
}



